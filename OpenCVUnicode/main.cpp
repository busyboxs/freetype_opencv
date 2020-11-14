#include "CvxFont.h"
#include "Chinese_test.h"
#include "Japanese_test.h"

extern void testSymbols();

cv::Scalar randomColor(cv::RNG& rng)
{
    auto icolor = (unsigned)rng;
    return cv::Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

std::vector<std::string> fontText{
        "msjh.ttc",      // 0 - ����
        "Deng.ttf",      // 1 - ���߼���
        "blodblack.ttf", // 2 - �����ֺڼ���
        "FZSTK.TTF",     // 3 - ��������
        "FZYTK.TTF",     // 4 - ����Ҧ��
        "simfang.ttf",   // 5 - ����
        "simhei.ttf",    // 6 - ����
        "STCAIYUN.TTF",  // 7 - ���Ĳ���
        "STFANGSO.TTF",  // 8 - ���ķ���
        "STXINGKA.TTF",  // 9 - �����п�
        "STHUPO.TTF",    // 10 - ��������
        "STKAITI.TTF",   // 11 - ���Ŀ���
        "STLITI.TTF",    // 12 - ��������
        "STSONG.TTF",    // 13 - ��������
        "STXIHEI.TTF",   // 14 - ����ϸ��
        "STXINWEI.TTF",  // 15 - ������κ
        "STZHONGS.TTF",  // 16 - ��������
        "simkai.ttf",    // 17 - ����
        "SIMLI.TTF",     // 18 - ����
        "msyh.ttc",      // 19 - ΢���ź�
        "SIMYOU.TTF",    // 20 - ��Բ
};




int main(int argc, char* argv[])
{
    testChinese();
    testJapanese();
    testOthers();
    testSymbols();

    return 0;
}