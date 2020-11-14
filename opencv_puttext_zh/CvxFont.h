#ifndef OPENCVUNICODE_CVXFONT_H
#define OPENCVUNICODE_CVXFONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>

#include <typeinfo>
#include <codecvt>
#include <string>
#include <locale>

namespace cvx {
    struct FontProperty {
        int fontSize;           // font size (pixel)
        double spaceRatio;       // ratio of distance when meet a space, base on font size
        double fontRatio;        // ratio of distance between each character, base on font size
        double fontRotateAngle;  // rotate angle
        double fontDiaphaneity;  // merge ratio
        bool fontIsUnderline;   // underline
        bool fontIsVertical;    // put text in vertical
    };

    class CvxFont
    {
    public:

        explicit CvxFont(const cv::String& fontType);
        virtual ~CvxFont();

        void setFontSize(int fontSize);
        void setSpaceRatio(const double spaceRatio) { m_font->spaceRatio = spaceRatio; }
        void setFontRatio(const double fontRatio) { m_font->fontRatio = fontRatio; }
        void setRotateAngle(const double angle) { m_font->fontRotateAngle = angle; }
        void setUnderline(const bool isUnderline) { m_font->fontIsUnderline = isUnderline; }
        void setDiaphaneity(const double diaphaneity) { m_font->fontDiaphaneity = diaphaneity; }
        void setVertical(const bool vertical) { m_font->fontIsVertical = vertical; }

        [[nodiscard]] int getFontSize() const { return m_font->fontSize; }
        [[nodiscard]] double getSpaceRatio() const { return m_font->spaceRatio; }
        [[nodiscard]] double getFontRatio() const { return m_font->fontRatio; }
        [[nodiscard]] double getAngle() const { return m_font->fontRotateAngle; }
        [[nodiscard]] bool getUnderline() const { return m_font->fontIsUnderline; }
        [[nodiscard]] double getDiaphaneity() const { return m_font->fontDiaphaneity; }
        [[nodiscard]] bool getVertical() const { return m_font->fontIsVertical; }

    private:
        void initFont();
        void rotateFont(double angle);
        void putTextStr(cv::Mat& img, const cv::String& text, cv::Point pos, const cv::Scalar& color);
        void putWChar(cv::Mat& img, uint32_t wc, cv::Point& pos, const cv::Scalar& color);

        friend void putText(cv::Mat&, const std::string&, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);
        friend void putSymbols(cv::Mat&, std::vector<uint32_t>&, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);
        friend void putOneSymbol(cv::Mat&, uint32_t, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);

        FT_Library   m_library{};   // font library
        FT_Face      m_face{};      // font type
        FT_Matrix    m_matrix{};
        FT_Vector    m_pen{};
        FT_Error     m_error;

        FontProperty* m_font;
        long m_maxDiffHeight{ 0 };

    };

    void putText(cv::Mat& img, const std::string& text, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color);
    void putSymbols(cv::Mat& img, std::vector<uint32_t>& symbols, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color);
    void putOneSymbol(cv::Mat& img, uint32_t symbol, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color);
}

#endif //OPENCVUNICODE_CVXFONT_H
