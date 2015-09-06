#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <stdio.h>
#include "mkl_vsl.h"
using namespace cv;
int n = 100000;

std::shared_ptr<Mat> readImage()
{
    Mat image = Mat::zeros(n, n, CV_8U) + 255;
 
    //change the color image to grayscale image
    cvtColor(image, image, CV_BGR2GRAY);
    std::shared_ptr<Mat> pImage;
    pImage.reset(new Mat(image));
    return pImage;
}

bool draw(unsigned char * bits)
{
    for (int i = 0; i < n*n; i++)
    {
        auto draw =  ((double) rand() / ((double)RAND_MAX));
        if(draw > 0.05)
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

    unsigned char * bits = (unsigned char *)calloc(n*n, sizeof(unsigned char));
    draw(bits);

	Size size(1000, 1000);//the dst image size,e.g.100x100
    Mat image(n, n, CV_8UC1, bits);
	resize(image, image, size);//resize image
    displayImage(image);
    return 0;
}
