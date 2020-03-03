#include "CvxText.h"

#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>

CvxText::CvxText(const cv::String& fontType)
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
	initFont();

	setlocale(LC_ALL, "");
}

// release freetype resource
CvxText::~CvxText()
{
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}

void CvxText::setFontSize(int fontSize)
{
    m_font.fontSize = fontSize;
    FT_Set_Pixel_Sizes(m_face, m_font.fontSize, 0);
}

// initial font 
void CvxText::initFont()
{
	m_font.fontSize = 16;
	m_font.spaceRatio = 0.5f;
	m_font.fontRatio = 0.1f;
    m_font.fontRotateAngle = 0;
    m_font.fontDiaphaneity = 1;
	m_font.fontIsUnderline = false;

	// set font 
	FT_Set_Pixel_Sizes(m_face, m_font.fontSize, 0);
}

void CvxText::rotateFont(float angle) {
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

void CvxText::putTextHorizon(cv::Mat & img, const cv::String & text, cv::Point pos, int fontSize, cv::Scalar color)
{
    int size = getFontSize();
    setFontSize(fontSize);
    putText(img, text, pos, color, false);
    setFontSize(size);
}

void CvxText::putTextVertical(cv::Mat & img, const cv::String & text, cv::Point pos, int fontSize, cv::Scalar color)
{
    int size = getFontSize();
    setFontSize(fontSize);
    putText(img, text, pos, color, true);
    setFontSize(size);
}

void CvxText::putTextRotateH(cv::Mat & img, const cv::String & text, cv::Point pos, int fontSize, cv::Scalar color, float rotateAngle)
{
    int size = getFontSize();
    float angle = getAngle();
    setFontSize(fontSize);
    setRotateAngle(rotateAngle);
    putText(img, text, pos, color, false);
    setFontSize(size);
    setRotateAngle(angle);
}

void CvxText::putTextRotateV(cv::Mat & img, const cv::String & text, cv::Point pos, int fontSize, cv::Scalar color, float rotateAngle)
{
    int size = getFontSize();
    float angle = getAngle();
    setFontSize(fontSize);
    setRotateAngle(rotateAngle);
    putText(img, text, pos, color, true);
    setFontSize(size);
    setRotateAngle(angle);
}

void CvxText::putText(cv::Mat& img, const cv::String& text, cv::Point pos, cv::Scalar color, bool vertical)
{
    if (img.empty()) {
        //std::cerr << "img can't be empty" << '\n';
        return;
    }

    if (text.empty()) {
        return ;
    }

    int xStart = pos.x;
    int yStart = pos.y;

	int i;
	for (i = 0; text[i] != '\0'; ++i)
	{
		wchar_t wc = text[i];

		// parse multi-byte character 
        if (!isascii(wc)) {
            static int bytelen = mblen(&text[i], 3);
            mbtowc(&wc, &text[i], bytelen);
            i += bytelen - 1;
        }

		// put character on image
		putWChar(img, wc, pos, color, vertical);
	}

    int xEnd = pos.x;
    int yEnd = pos.y;
    if (m_font.fontIsUnderline) {
        if (vertical) {
            cv::line(img, cv::Point(xStart + m_font.fontSize, yStart), cv::Point(xStart + m_font.fontSize, yEnd), color, 2);
        }
        else {
            cv::line(img, cv::Point(xStart, yStart + m_font.fontSize), cv::Point(xEnd, yStart + m_font.fontSize), color, 2);
        }
    }
    
}

void CvxText::putWChar(cv::Mat& img, wchar_t wc, cv::Point &pos, cv::Scalar color, bool vertical)
{

	rotateFont(m_font.fontRotateAngle);

	// Converting a Character Code Into a Glyph Index
	FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
	FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

	FT_GlyphSlot slot = m_face->glyph;

	bool isspace = wc == ' ' ? true : false;

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
				int r = vertical ? pos.y + i : pos.y + i + (m_font.fontSize - rows); // to make align to bottom
				int c = pos.x + j;


				if (r >= 0 && r < img.rows && c >= 0 && c < img.cols)
				{
					cv::Vec3b scalar = img.at<cv::Vec3b>(cv::Point(c, r));

					// merge set color with origin color
					float p = m_font.fontDiaphaneity;
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

	double space = m_font.fontSize * m_font.spaceRatio;
	double sep = m_font.fontSize * m_font.fontRatio;

	// vertical string or not, default not vertical
	if (vertical) {
		pos.y += (int)((isspace ? space : rows) + sep);
	}
	else {
		pos.x += (int)((isspace ? space : cols) + sep);
	}
}