#ifndef OPENCVTEXTZH_CVXFONT_H
#define OPENCVTEXTZH_CVXFONT_H

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
        float spaceRatio;       // ratio of distance when meet a space, base on font size
        float fontRatio;        // ratio of distance between each character, base on font size
        float fontRotateAngle;  // rotate angle
        float fontDiaphaneity;  // merge ratio
        bool fontIsUnderline;   // underline
        bool fontIsVertical;    // put text in vertical
    };

    class CvxFont
    {
    public:

        explicit CvxFont(const cv::String& fontType);
        virtual ~CvxFont();

        void setFontSize(int fontSize);
        void setSpaceRatio(float spaceRatio) { m_font->spaceRatio = spaceRatio; }
        void setFontRatio(float fontRatio) { m_font->fontRatio = fontRatio; }
        void setRotateAngle(float angle) { m_font->fontRotateAngle = angle; }
        void setUnderline(bool isUnderline) { m_font->fontIsUnderline = isUnderline; }
        void setDiaphaneity(float diaphaneity) { m_font->fontDiaphaneity = diaphaneity; }
        void setVertical(bool vertical) { m_font->fontIsVertical = vertical; }

        int getFontSize() const { return m_font->fontSize; }
        float getSpaceRatio() const { return m_font->spaceRatio; }
        float getFontRatio() const { return m_font->fontRatio; }
        float getAngle() const { return m_font->fontRotateAngle; }
        bool getUnderline() const { return m_font->fontIsUnderline; }
        float getDiaphaneity() const { return m_font->fontDiaphaneity; }
        bool getVertical() const { return m_font->fontIsVertical; }

    private:
        void initFont_();
        void rotateFont_(double angle);
#if defined _MSC_VER
        void putTextStr_(cv::Mat& img, const cv::String& text, cv::Point pos, const cv::Scalar& color);
#else
        void putTextu32Str_(cv::Mat& img, const std::u32string& ws, cv::Point pos, const cv::Scalar& color);
#endif
        void putWChar_(cv::Mat& img, uint32_t wc, cv::Point &pos, const cv::Scalar& color);

        friend void putText(cv::Mat&, const std::string&, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);
        friend void putSymbols(cv::Mat&, std::vector<uint32_t>&, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);
        friend void putOneSymbol(cv::Mat&, uint32_t, cv::Point, cvx::CvxFont&, int, const cv::Scalar&);

        FT_Library   m_library;   // font library
        FT_Face      m_face;      // font type
        FT_Matrix    m_matrix;
        FT_Vector    m_pen;
        FT_Error     m_error;

        FontProperty *m_font;

    };

#ifndef _MSC_VER
    std::u32string strToU32String(const std::string& s);
#endif
    void putText(cv::Mat& img, const std::string& text, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color);
    void putSymbols(cv::Mat& img, std::vector<uint32_t>& symbols, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color);
    void putOneSymbol(cv::Mat& img, uint32_t symbol, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar &color);
}

#endif //OPENCVTEXTZH_CVXFONT_H
