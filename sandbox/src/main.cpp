#include <opencv2/opencv.hpp>
#include <memory>
#include <thread>
#include <map>
#include <cmath>
#include <mpi.h>
using namespace cv;

int n = 30000;
double p = 0.05;

int nElementsPerProcess;
int leftOverElements;

Size size(1000, 1000);
int rank;
char hostname[256];
MPI_Status* status;
int nProcesses;
enum class TAGS {BITS}; 

std::shared_ptr<Mat> readImage()
{
    Mat image = Mat::zeros(n, n, CV_8U) + 255;
 
    //change the color image to grayscale image
    cvtColor(image, image, CV_BGR2GRAY);
    std::shared_ptr<Mat> pImage;
    pImage.reset(new Mat(image));
    return pImage;
}

bool draw(unsigned char * bits, int startIndex, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        auto draw =  ((double) rand() / ((double)RAND_MAX));
        if(draw > p)
		{
			bits[i] = rank*draw*255;
		}
    }
    return true;
}

bool displayImage(const Mat image)
{

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return false;
}

bool displayImageFromCharArray(unsigned char* bits)
{
        Mat image(n, n, CV_8UC1, bits);
        //resize(image, image, size);
        //displayImage(image);
        return true;
}

bool processSlaves()
{
        unsigned char* bits =  (unsigned char *)calloc(nElementsPerProcess, sizeof(unsigned char));
        MPI_Recv(bits, nElementsPerProcess, MPI_UNSIGNED_CHAR, 0, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD, status);
        draw(bits, 0, nElementsPerProcess);
        auto retVal = MPI_Send( &bits[0], nElementsPerProcess, MPI_UNSIGNED_CHAR, 0, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD);
        delete(bits);
}

bool delegateBits(unsigned char* bits)
{
    for (int i = 1; i < nProcesses; i++)
    {
        unsigned char* startChar = &bits[(i-1)*nElementsPerProcess];
        auto retVal =
            MPI_Send(startChar, nElementsPerProcess, MPI_UNSIGNED_CHAR, i, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD);
    }
    for (int i = 1; i < nProcesses; i++)
    {
        unsigned char* startChar = &bits[(i-1)*nElementsPerProcess];
        MPI_Recv(startChar, nElementsPerProcess, MPI_UNSIGNED_CHAR, i, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD, status);
    }
}

bool processMaster()
{
        unsigned char* bits =  (unsigned char *)calloc(n*n, sizeof(unsigned char));
        delegateBits(bits);
        displayImageFromCharArray(bits);  
        delete(bits);
        return true;
}

int main(int argc, char** argv )
{
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    gethostname(hostname, 255);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    nElementsPerProcess = (n*n)/(nProcesses-1);
    leftOverElements = (n*n) % nProcesses;
 
    if (rank == 0)
    {
        processMaster();
    }
    else
    {
        processSlaves();
    }
    MPI_Finalize();
}
