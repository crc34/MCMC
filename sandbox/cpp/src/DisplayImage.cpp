#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

using namespace cv;

std::shared_ptr<Mat> readImage(std::string imageName)
{
    Mat image;
    image = imread(imageName, 1);
 
    //change the color image to grayscale image
    cvtColor(image, image, CV_BGR2GRAY);
    std::shared_ptr<Mat> pImage;
    pImage.reset(new Mat(image));
    return pImage;
}


bool displayImage(std::shared_ptr<Mat> image)
{
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", *(image.get()));
    waitKey(0);
    return false;
}

bool thresholdImage(Mat & image)
{
	cv::threshold(image, image, 120, 1,3);
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    else
    {
        std::shared_ptr<Mat> image = readImage(argv[1]);
        double nRows = image->rows;
        double nCols = image->cols;
        std::cout << nCols << std::endl;
        std::cout << nRows << std::endl;
	    thresholdImage(*image); 
        return displayImage(image);
    }
}
