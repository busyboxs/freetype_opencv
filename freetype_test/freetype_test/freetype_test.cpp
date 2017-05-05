
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "CvxText.h"
using namespace std;

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg");
	const char* msg = "这里可以输入中文哦";//如果这里乱码就自行修改一下，可能是我的编码的问题
	IplImage *image = &IplImage(img);
	CvxText text("C:\\Windows\\Fonts\\simkai.ttf");//windows中字体的位置，注意查看有没有，可以右键属性查看字体名称
	text.putText(image, msg, cv::Point(100, 100), cv::Scalar(0, 255, 255));
	cv::Mat image_mat = cv::cvarrToMat(image);
	cv::imshow("test", image_mat); 
	cvWaitKey(-1);
	//cvReleaseImage(&image);
	return 0;
}
