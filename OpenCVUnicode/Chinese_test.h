#pragma once
#include "CvxFont.h"

void testLowerAlpha(cvx::CvxFont& font, cv::Mat& img);
void testUpperAlpha(cvx::CvxFont& font, cv::Mat& img);
void testHorizon(cvx::CvxFont& font, cv::Mat& img);
void testVertical(cvx::CvxFont& font, cv::Mat& img);
void testHorizonRotate(cvx::CvxFont& font, cv::Mat& img);
void testVerticalRotate(cvx::CvxFont& font, cv::Mat& img);
void testTruncate(cvx::CvxFont& font, cv::Mat& img);
void testFontSize(cvx::CvxFont& font, cv::Mat& img);
void testSpace(cvx::CvxFont& font, cv::Mat& img);
void testBetweenSpace(cvx::CvxFont& font, cv::Mat& img);
void testTransparency(cvx::CvxFont& font, cv::Mat& img);
void testUnderline(cvx::CvxFont& font, cv::Mat& img);
void testChinese();