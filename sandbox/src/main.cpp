#include <opencv2/opencv.hpp>
#include <memory>
#include <thread>
#include <map>
#include <cmath>
#include <mpi.h>
using namespace cv;

int n = 2000;
double p = 0.05;

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
			bits[i] = 255*draw;
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


int main(int argc, char** argv )
{
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    gethostname(hostname, 255);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    if (rank == 0)
    {
        unsigned char* bits =  (unsigned char *)calloc(n*n, sizeof(unsigned char));
        auto retVal = MPI_Send( &bits[0], n*n, MPI_UNSIGNED_CHAR, 1, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD  );
        MPI_Recv(bits, n*n, MPI_UNSIGNED_CHAR, 1, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD, status);
        Mat image(n, n, CV_8UC1, bits);
        resize(image, image, size);
        displayImage(image);
        delete(bits);
        return 0;
    }
    else
    {
        unsigned char* bits =  (unsigned char *)calloc(n*n, sizeof(unsigned char));
        MPI_Recv(bits, n*n, MPI_UNSIGNED_CHAR, 0, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD, status);
        draw(bits, 0, n*n);
        auto retVal = MPI_Send( &bits[0], n*n, MPI_UNSIGNED_CHAR, 0, static_cast<int>(TAGS::BITS), MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
