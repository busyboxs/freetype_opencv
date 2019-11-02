#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "CvxText.h"

using namespace std;

static cv::Scalar randomColor(cv::RNG& rng)
{
	int icolor = (unsigned)rng;
	return cv::Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

int main(int argc, char *argv[])
{
	cv::RNG rng(0xFFFFFFFF);

	// create a white background
	cv::Mat img(400, 800, CV_8UC3, cv::Scalar(255, 255, 255));
	
	// be careful to use the font that support Chinese 
	CvxText text("./font/msyh.ttc");
	text.setFontSize(32);

	const char* msg = "abcdefghijklmnopqrstuvwxyz";
	text.putText(img, msg, cv::Point(40, 20), cv::Scalar(0, 255, 0));

	const char* msg1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text.putText(img, msg1, cv::Point(40, 100), randomColor(rng));

	const char* msg2 = "这是水平字符";
	text.putText(img, msg2, cv::Point(40, 200), randomColor(rng));

	const char* msg3 = "这是竖直字符";
	text.putText(img, msg3, cv::Point(0, 40), randomColor(rng), true);

	const char* msg4 = "This is rotate string!";
	text.setFontSize(32, 30);
	text.putText(img, msg4, cv::Point(40, 250), randomColor(rng));

	const char* msg5 = "这是旋转字符";
	text.setFontSize(32, -30);
	text.putText(img, msg5, cv::Point(40, 300), randomColor(rng));

	const char* msg6 = "字符可以被截断";
	text.setFontSize(32);
	text.putText(img, msg6, cv::Point(600, 40), cv::Scalar(111, 123, 205));

	const char* msg7 = "这是16号字体";
	text.setFontSize(16);
	text.putText(img, msg7, cv::Point(40, 350), cv::Scalar(111, 123, 205));

	const char* msg8 = "这是32号字体";
	text.setFontSize(32);
	text.putText(img, msg8, cv::Point(160, 350), randomColor(rng));

	cv::imshow("test", img);
	cv::waitKey();
	return 0;
}