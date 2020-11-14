#include "CvxFont.h"

extern cv::Scalar randomColor(cv::RNG& rng);
static cv::RNG rng(0xFFFFFFFF);

// http://www.kreativekorp.com/charset/font/SegoeUISymbol/
void testSymbols() {
    // create a black background
    cv::Mat img(700, 1200, CV_8UC3, cv::Scalar(0, 0, 0));
    std::string fontPath = "../font/seguisym.ttf";

    // be careful to use the font that support Chinese
    cvx::CvxFont font(fontPath);
    int i = 0, page = 0, x = 10, y = 40;
    std::vector<uint32_t> symbols{};
    for (uint32_t c = 0x1f300; c <= 0x1f6cf; ++c) {
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
            x = 10, y = 40;
            if (k == 'q') {  // press q to quite
                return;
            }
        }
        i++;
    }

    cv::imshow("test2", img);
    cv::waitKey();
}