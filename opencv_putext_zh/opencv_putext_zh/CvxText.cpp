#include <wchar.h>  
#include <assert.h>  
#include <locale.h>  
#include <ctype.h>  

#include "CvxText.h"   

CvxText::CvxText(const char *fontType)
{
	assert(fontType != NULL);  

	m_error = FT_Init_FreeType(&m_library);
	if (m_error)
	{
		std::cout << "library initial error!" << std::endl;
	}

	m_error = FT_New_Face(m_library, fontType, 0, &m_face);
	if (m_error == FT_Err_Unknown_File_Format)
	{
		std::cout << "unsupported font format!" << std::endl;
	}
	else if (m_error)
	{
		std::cout << " can not open font files" << std::endl;
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

void CvxText::getFont(cv::Scalar *size, bool *underline, float *diaphaneity)
{
	if (size) *size = m_fontSize;
	if (underline) *underline = m_fontUnderline;
	if (diaphaneity) *diaphaneity = m_fontDiaphaneity;
}

void CvxText::setFont(cv::Scalar *size, bool *underline, float *diaphaneity)
{ 
	if (size)
	{
		m_fontSize.val[0] = fabs(size->val[0]);
		m_fontSize.val[1] = fabs(size->val[1]);
		m_fontSize.val[2] = fabs(size->val[2]);
		m_fontSize.val[3] = fabs(size->val[3]);
	}
	if (underline)
	{
		m_fontUnderline = *underline;
	}
	if (diaphaneity)
	{
		m_fontDiaphaneity = *diaphaneity;
	}
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

void CvxText::setFontSize(int font_size, double rotate_angle, double space_ratio, double sep_ratio) {
	m_fontSize.val[0] = fabs(font_size);
	m_fontSize.val[1] = fabs(space_ratio);
	m_fontSize.val[2] = fabs(sep_ratio);
	m_fontSize.val[3] = rotate_angle;

	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

// initial font 
void CvxText::initFont()
{ 
	m_fontSize.val[0] = 16;    // font size 
	m_fontSize.val[1] = 0.5;   // ratio of distance when meet a space, base on font size 
	m_fontSize.val[2] = 0.1;   // ratio of distance between each character, base on font size
	m_fontSize.val[3] = 0;     // rotate angle

	m_fontUnderline = false;   // underline (not support yet)  

	m_fontDiaphaneity = 1.0;   // merge ratio

	// set font 
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

void CvxText::rotateFont(double angle) {
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

int CvxText::putText(cv::Mat& img, const char *text, cv::Point pos, cv::Scalar color, bool vertical)
{
	if (img.empty()) 
		return -1;
	if (text == NULL) 
		return -1;

	int i;
	for (i = 0; text[i] != '\0'; ++i)
	{
		wchar_t wc = text[i];

		// parse double-byte character 
		if (!isascii(wc)) 
			mbtowc(&wc, &text[i++], 2);

		// put character on image
		putWChar(img, wc, pos, color, vertical);
	}
	return i;
}

int CvxText::putText(cv::Mat& img, const wchar_t *text, cv::Point pos, cv::Scalar color, bool vertical)
{
	if (img.empty()) 
		return -1;
	if (text == NULL) 
		return -1; 

	int i;
	for (i = 0; text[i] != '\0'; ++i)
	{
		putWChar(img, text[i], pos, color, vertical);
	}
	return i;
} 

void CvxText::putWChar(cv::Mat& img, wchar_t wc, cv::Point &pos, cv::Scalar color, bool vertical)
{

	rotateFont(m_fontSize.val[3]);
	
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
				int r = vertical? pos.y + i: pos.y + i + ((int)m_fontSize.val[0] - rows); // to make align to bottom
				int c = pos.x + j;


				if (r >= 0 && r < img.rows && c >= 0 && c < img.cols)
				{
					cv::Vec3b scalar = img.at<cv::Vec3b>(cv::Point(c, r));

					// merge set color with origin color
					float p = m_fontDiaphaneity;
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

	double space = m_fontSize.val[0] * m_fontSize.val[1];
	double sep = m_fontSize.val[0] * m_fontSize.val[2];

	// vertical string or not, default not vertical
	if (vertical) {
		pos.y += (int)((isspace ? space : rows) + sep);
	}
	else {
		pos.x += (int)((isspace ? space : cols) + sep);
	}
}