#include "CvxText.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>


static cv::Scalar randomColor(cv::RNG& rng)
{
	int icolor = (unsigned)rng;
	return cv::Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

std::vector<std::string> fontText{
    "msjh.ttc",      // 0 - 繁体
    "Deng.ttf",      // 1 - 等线简体
    "blodblack.ttf", // 2 - 方正粗黑简体
    "FZSTK.TTF",     // 3 - 方正舒体
    "FZYTK.TTF",     // 4 - 方正姚体
    "simfang.ttf",   // 5 - 仿宋
    "simhei.ttf",    // 6 - 黑体
    "STCAIYUN.TTF",  // 7 - 华文彩云
    "STFANGSO.TTF",  // 8 - 华文仿宋
    "STXINGKA.TTF",  // 9 - 华文行楷
    "STHUPO.TTF",    // 10 - 华文琥珀
    "STKAITI.TTF",   // 11 - 华文楷体
    "STLITI.TTF",    // 12 - 华文隶书
    "STSONG.TTF",    // 13 - 华文宋体
    "STXIHEI.TTF",   // 14 - 华文细黑
    "STXINWEI.TTF",  // 15 - 华文新魏
    "STZHONGS.TTF",  // 16 - 华文中宋
    "simkai.ttf",    // 17 - 楷体
    "SIMLI.TTF",     // 18 - 隶书
    "msyh.ttc",      // 19 - 微软雅黑
    "SIMYOU.TTF",    // 20 - 幼圆
};

// https://zh.wikipedia.org/wiki/%E5%B9%B3%E5%81%87%E5%90%8D
void testJanpaese() {
    cv::RNG rng(0xFFFFFFFF);

    // create a black background
    cv::Mat img(400, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/msgothic.ttc";

    // be careful to use the font that support Chinese 
    CvxText text(fontPath);

    cv::String s = "\u3042\u3044\u3057\u3066\u308b";
    text.putTextHorizon(img, s, cv::Point(500, 150), 32, randomColor(rng));

    cv::imshow("test1", img);
}

// http://www.kreativekorp.com/charset/font/SegoeUISymbol/
void testSegoeUISymbol() {
    cv::RNG rng(0xFFFFFFFF);

    // create a black background
    cv::Mat img(400, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/seguisym.ttf";

    // be careful to use the font that support Chinese 
    CvxText text(fontPath);

    cv::String s = "\ue181\ue006\ue007\ue00a\ue284\u262f";
    text.putTextHorizon(img, s, cv::Point(50, 150), 32, randomColor(rng));

    cv::imshow("test2", img);
    cv::waitKey();
}

void testChinese() {
    cv::RNG rng(0xFFFFFFFF);

    // create a black background
    cv::Mat img(400, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/simhei.ttf";

    // be careful to use the font that support Chinese 
    CvxText text(fontPath);

    cv::String s = "可以显示中文";
    text.putTextHorizon(img, s, cv::Point(50, 150), 32, randomColor(rng));

    cv::imshow("test3", img);
    cv::waitKey();
}

int main(int argc, char *argv[])
{
	cv::RNG rng(0xFFFFFFFF);

    testJanpaese();

	// create a black background
	cv::Mat img(400, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/" + fontText[7];
	
	// be careful to use the font that support Chinese 
    CvxText text(fontPath);

	cv::String msg = "abcdefghijklmnopqrstuvwxyz";
    int fontSize = 32;
	text.putTextHorizon(img, msg, cv::Point(40, 20), fontSize, cv::Scalar(0, 255, 0));

    cv::String msg1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text.putTextHorizon(img, msg1, cv::Point(40, 100), fontSize, randomColor(rng));

    cv::String msg2 = "这是水平字符abcgf發";
	text.putTextHorizon(img, msg2, cv::Point(40, 200), fontSize, randomColor(rng));

    cv::String msg3 = "这是竖直字符ada";
    text.putTextVertical(img, msg3, cv::Point(0, 40), fontSize, randomColor(rng));

    cv::String msg4 = "This is a rotate string!";
    text.setFontSize(32);
    float angle = 30;
    text.putTextRotateH(img, msg4, cv::Point(40, 250), fontSize, randomColor(rng), angle);

    cv::String msg5 = "这是旋转字符";
    angle = -30;
    text.putTextRotateV(img, msg5, cv::Point(700, 100), fontSize, randomColor(rng), angle);

    cv::String msg6 = "字符可以被截断";
    text.putTextHorizon(img, msg6, cv::Point(600, 40), fontSize, cv::Scalar(111, 123, 205));

    cv::String msg7 = "这是16号字体";
    fontSize = 16;
    text.putTextHorizon(img, msg7, cv::Point(40, 350), fontSize, cv::Scalar(111, 123, 205));

    cv::String msg8 = "这是32号字体";
    fontSize = 32;
    text.putTextHorizon(img, msg8, cv::Point(160, 350), fontSize, randomColor(rng));

    cv::String msg9 = "有空 格时";
    text.putTextHorizon(img, msg9, cv::Point(500, 300), fontSize, randomColor(rng));

    cv::String msg10 = "更大的字间距";
    float ratio = text.getFontRatio();
    text.setFontRatio(0.3f);
    text.putTextHorizon(img, msg10, cv::Point(500, 350), fontSize, randomColor(rng));
    text.setFontRatio(ratio);  // if you don't want to change it forever, you'd better to change it back

    cv::String msg11 = "设置透明度";
    float transparency = text.getDiaphaneity();
    text.setDiaphaneity(0.3f);
    text.putTextHorizon(img, msg11, cv::Point(500, 200), fontSize, randomColor(rng));
    text.setDiaphaneity(transparency);

    cv::String msg12 = "加下划线";
    bool isUnderline = text.getUnderline();
    text.setUnderline(true);
    text.putTextHorizon(img, msg12, cv::Point(500, 150), fontSize, randomColor(rng));
    text.setUnderline(isUnderline);

	cv::imshow("test", img);
	cv::waitKey();

	return 0;
}