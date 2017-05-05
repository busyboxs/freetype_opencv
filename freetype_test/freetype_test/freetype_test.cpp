
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "CvxText.h"
using namespace std;

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg");
	const char* msg = " ‰»Î∫∫◊÷";
	IplImage *image = &IplImage(img);
	CvxText text("C:\\Windows\\Fonts\\simkai.ttf");
	text.putText(image, msg, cv::Point(100, 100), cv::Scalar(0, 255, 255));
	cv::Mat image_mat = cv::cvarrToMat(image);
	cv::imshow("test", image_mat); 
	cvWaitKey(-1);
	//cvReleaseImage(&image);
	return 0;
}