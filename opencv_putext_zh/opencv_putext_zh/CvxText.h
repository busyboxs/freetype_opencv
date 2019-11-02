#include <ft2build.h> 
#include FT_FREETYPE_H

#pragma comment(lib, "freetype.lib")

#include <opencv2/opencv.hpp>  

class CvxText
{
	CvxText& operator=(const CvxText&);
public:

	CvxText(const char *fontType);
	virtual ~CvxText();

	void getFont(cv::Scalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);
	void setFont(cv::Scalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);
	void setFontSize(int font_size, double rotate_angle = 0, double space_ratio = 0.5, double sep_ratio = 0.1);
	void initFont();

	void rotateFont(double angle);

	int putText(cv::Mat& img, const char *text, cv::Point pos, 
		cv::Scalar color = CV_RGB(25, 255, 255), bool vertical = false);
	int putText(cv::Mat& img, const wchar_t *text, cv::Point pos, 
		cv::Scalar color = CV_RGB(25, 255, 255), bool vertical = false);

private: 
	void putWChar(cv::Mat& img, wchar_t wc, cv::Point &pos, cv::Scalar color, bool vertical = false);

private:

	FT_Library   m_library;   // font library  
	FT_Face      m_face;      // font type
	FT_Matrix    m_matrix;
	FT_Vector    m_pen;
	FT_Error     m_error;

	cv::Scalar   m_fontSize;
	bool         m_fontUnderline;
	float        m_fontDiaphaneity;

};