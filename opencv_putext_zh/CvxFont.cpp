#include "CvxFont.h"

#include <cwchar>
#include <cassert>
#include <clocale>
#include <cctype>
#include <utility>

cvx::CvxFont::CvxFont(const cv::String& fontType)
{
    assert(!fontType.empty());

    m_error = FT_Init_FreeType(&m_library);
    if (m_error)
    {
        std::cerr << "library initial error!" << std::endl;
        return;
    }

    m_error = FT_New_Face(m_library, fontType.c_str(), 0, &m_face);
    if (m_error == FT_Err_Unknown_File_Format)
    {
        std::cerr << "unsupported font format!" << std::endl;
        return;
    }
    else if (m_error)
    {
        std::cerr << " can not open font files" << std::endl;
        return;
    }

    // use default parameters
    m_font = new FontProperty;
    initFont_();

    setlocale(LC_ALL, "");
}

// release freetype resource
cvx::CvxFont::~CvxFont()
{
    delete m_font;
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_library);
}

void cvx::CvxFont::setFontSize(int fontSize)
{
    m_font->fontSize = fontSize;
    FT_Set_Pixel_Sizes(m_face, fontSize, 0);
}

// initial font
void cvx::CvxFont::initFont_()
{
    setFontSize(16);
    setSpaceRatio(0.5f);
    setFontRatio(0.1f);
    setRotateAngle(0);
    setDiaphaneity(1);
    setUnderline(false);
    setVertical(false);
    // set font
    FT_Set_Pixel_Sizes(m_face, getFontSize(), 0);
}

void cvx::CvxFont::rotateFont_(double angle) {
    angle = (angle / 360) * 3.14159 * 2;
    /* set up matrix */
    m_matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
    m_matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
    m_matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
    m_matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

    m_pen.x = 0;
    m_pen.y = 0;

    FT_Set_Transform(m_face, &m_matrix, &m_pen);
}

#if defined(_MSC_VER)
void cvx::CvxFont::putTextStr_(cv::Mat& img, const cv::String& text, cv::Point pos, const cv::Scalar& color)
{
    CV_Assert(!img.empty());
    CV_Assert(!text.empty());

    int xStart = pos.x;
    int yStart = pos.y;

    for (int i = 0; text[i] != '\0'; ++i)
    {
        wchar_t wc = text[i];

        // parse multi-byte character
        if (!isascii(wc)) {
            static int bytelen = mblen(&text[i], 3);
            mbtowc(&wc, &text[i], bytelen);
            i += bytelen - 1;
        }

        // put character on image
        putWChar_(img, (wc & 0xffffffff), pos, color);
    }

    int xEnd = pos.x;
    int yEnd = pos.y;
    if (getUnderline()) {
        int size = getFontSize();
        if (getVertical()) {
            cv::line(img, cv::Point(xStart + size, yStart), cv::Point(xStart + size, yEnd), color, 2);
        }
        else {
            cv::line(img, cv::Point(xStart, yStart + size), cv::Point(xEnd, yStart + size), color, 2);
        }
    }

}
#else
void cvx::CvxFont::putTextu32Str_(cv::Mat& img, const std::u32string& ws, cv::Point pos, const cv::Scalar& color)
{
    CV_Assert(!img.empty());
    CV_Assert(!ws.empty());

    int xStart = pos.x, yStart = pos.y;

    for (auto& wc : ws) {
        putWChar_(img, (wc & 0xffffffff), pos, color);
    }

    int xEnd = pos.x, yEnd = pos.y;
    if (getUnderline()) {
        int size = getFontSize();
        if (getVertical()) {
            cv::line(img, cv::Point(xStart + size, yStart), cv::Point(xStart + size, yEnd), color, 2);
        }
        else {
            cv::line(img, cv::Point(xStart, yStart + size), cv::Point(xEnd, yStart + size), color, 2);
        }
    }
}
#endif

void cvx::CvxFont::putWChar_(cv::Mat& img, uint32_t wc, cv::Point &pos, const cv::Scalar& color) {
    rotateFont_(getAngle());
    bool vertical = getVertical();
    int size = getFontSize();

    // Converting a Character Code Into a Glyph Index
    FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
    FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

    FT_GlyphSlot slot = m_face->glyph;

    bool isspace = wc == ' ';

    // get rows and cols of current wide char
    int rows = slot->bitmap.rows;
    int cols = slot->bitmap.width;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int off = i * slot->bitmap.pitch + j / 8;

            if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8)))
            {
                int r = vertical ? pos.y + i : pos.y + i + (size - rows); // to make align to bottom
                int c = pos.x + j;


                if (r >= 0 && r < img.rows && c >= 0 && c < img.cols)
                {
                    cv::Vec3b scalar = img.at<cv::Vec3b>(cv::Point(c, r));

                    // merge set color with origin color
                    float p = getDiaphaneity();
                    for (int k = 0; k < 3; ++k)
                    {
                        scalar.val[k] = (uchar)(scalar.val[k] * (1 - p) + color.val[k] * p);
                    }

                    img.at<cv::Vec3b>(cv::Point(c, r)) = cv::Vec3b(scalar[0], scalar[1], scalar[2]);
                }
            }
        }
    }

    // modify position to next character

    double space = size * getSpaceRatio();
    double sep = size * getFontRatio();

    // vertical string or not, default not vertical
    if (vertical) {
        pos.y += (int)((isspace ? space : rows) + sep);
    }
    else {
        pos.x += (int)((isspace ? space : cols) + sep);
    }
}

#ifndef _MSC_VER
std::u32string cvx::strToU32String(const std::string& s) {
    // https://github.com/antlr/antlr4/commit/de6f04be0beebd17ea6232f554635c5262127aaa#diff-5943b2afc50fefa7b41c7d2527af9b39
#if defined(_MSC_VER) && _MSC_VER >= 1900 && _MSC_VER < 2000
    static std::wstring_convert<std::codecvt_utf8<__int32>, __int32> utfConverter;
#else
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
#endif

#if _MSC_VER > 1900 && _MSC_VER < 2000
    auto r = utfConverter.from_bytes(s.data(), s.data() + s.size());
    std::u32string u32str = reinterpret_cast<const char32_t *>(r.data());
    return u32str;
#else
    return utfConverter.from_bytes(s);
#endif
}
#endif

void cvx::putText(cv::Mat &img, const std::string &text, cv::Point pos, cvx::CvxFont &fontFace, int fontSize, const cv::Scalar &color) {
    fontFace.setFontSize(fontSize);
#if defined(_MSC_VER)
    fontFace.putTextStr_(img, text, std::move(pos), color);
#else
    fontFace.putTextu32Str_(img, strToU32String(text), std::move(pos), color);
#endif
    fontFace.initFont_();
}

void cvx::putOneSymbol(cv::Mat &img, uint32_t symbol, cv::Point pos, cvx::CvxFont &fontFace, int fontSize, const cv::Scalar &color) {
    fontFace.setFontSize(fontSize);
    fontFace.putWChar_(img, symbol, pos, color);
    fontFace.initFont_();
}

void cvx::putSymbols(cv::Mat& img, std::vector<uint32_t>& symbols, cv::Point pos, cvx::CvxFont& fontFace, int fontSize, const cv::Scalar& color) {
    fontFace.setFontSize(fontSize);
    for (auto& symbol : symbols) {
        fontFace.putWChar_(img, symbol, pos, color);
    }
    fontFace.initFont_();
}
