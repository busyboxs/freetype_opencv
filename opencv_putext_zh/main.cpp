#include "CvxFont.h"

#include <iostream>

cv::Scalar randomColor(cv::RNG& rng)
{
    auto icolor = (unsigned)rng;
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




int main(int argc, char *argv[])
{
    extern void testChinese();
    extern void testJapanese();
    extern void testOthers();
    extern void testSymbols();
    testChinese();
    testJapanese();
    testOthers();
    testSymbols();
    return 0;
}