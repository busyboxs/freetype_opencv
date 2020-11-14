#include "Japanese_test.h"
#include "CvxFont.h"

extern cv::Scalar randomColor(cv::RNG& rng);
static cv::RNG rng(0xFFFFFFFF);

// https://zh.wikipedia.org/wiki/%E5%B9%B3%E5%81%87%E5%90%8D
void testJapanese() {
    // create a black background
    cv::Mat img(400, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/msgothic.ttc";

    // be careful to use the font that support Chinese
    cvx::CvxFont font(fontPath);

    cv::String s = "\u3042\u3044\u3057\u3066\u308b";
    putText(img, s, cv::Point(500, 150), font, 32, randomColor(rng));

    cv::imshow("test1", img);
    cv::waitKey();
}

void testOthers() {
    // create a black background
    cv::Mat img(700, 1200, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "./font/msgothic.ttc";

    // be careful to use the font that support Chinese
    cvx::CvxFont font(fontPath);
    int i = 0, page = 0, x = 10, y = 40;
    std::vector<uint32_t> symbols{};
    for (uint32_t c = 0x3040; c <= 0x309f; ++c) {
        symbols.push_back(c);
        if ((i + 1) % 16 == 0) {
            if ((i + 1) % 32 == 0) {
                cvx::putSymbols(img, symbols, cv::Point(x, y), font, 32, randomColor(rng));
                y += 50;
                x = 10;
                symbols.clear();
            }
            else {
                cvx::putSymbols(img, symbols, cv::Point(x, y), font, 32, randomColor(rng));
                x += 600;
                symbols.clear();
            }
        }
        if ((i + 1) % (14 * 32) == 0) {
            cv::imshow("test2", img);
            cv::Mat black(700, 1200, CV_8UC3, cv::Scalar(0, 0, 0));
            img = black;
            char k = cv::waitKey();
            x = 10, y = 10;
            if (k == 'q') {  // press q to quite
                return;
            }
        }
        i++;

    }

    cv::imshow("test2", img);
    cv::waitKey();
}