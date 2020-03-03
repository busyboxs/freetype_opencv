#include <ft2build.h> 
#include FT_FREETYPE_H

#pragma comment(lib, "freetype.lib")

#include <opencv2/opencv.hpp>

struct FontProperty {
    int fontSize;           // font size (pixel)
    float spaceRatio;       // ratio of distance when meet a space, base on font size
    float fontRatio;        // ratio of distance between each character, base on font size
    float fontRotateAngle;  // rotate angle
    float fontDiaphaneity;  // merge ratio
    bool fontIsUnderline;   // underline (not support yet)
};

class CvxText
{
	CvxText& operator=(const CvxText&);
public:

	CvxText(const cv::String& fontType);
	virtual ~CvxText();

    void setFontSize(int fontSize);
    void setSpaceRatio(float spaceRatio) { m_font.spaceRatio = spaceRatio; }
    void setFontRatio(float fontRatio) { m_font.fontRatio = fontRatio; }
    void setRotateAngle(float angle) { m_font.fontRotateAngle = angle; }
    void setUnderline(bool isUnderline) { m_font.fontIsUnderline = isUnderline; }
    void setDiaphaneity(float diaphaneity) { m_font.fontDiaphaneity = diaphaneity; }

    int getFontSize() { return m_font.fontSize; }
    float getSpaceRatio() { return m_font.spaceRatio; }
    float getFontRatio() { return m_font.fontRatio; }
    float getAngle() { return m_font.fontRotateAngle; }
    bool getUnderline() { return m_font.fontIsUnderline; }
    float getDiaphaneity() { return m_font.fontDiaphaneity; }

	void initFont();
    void rotateFont(float angle);

    void putTextHorizon(cv::Mat& img, const cv::String& text, cv::Point pos, int fontSize, cv::Scalar color);
    void putTextVertical(cv::Mat& img, const cv::String& text, cv::Point pos, int fontSize, cv::Scalar color);
    void putTextRotateH(cv::Mat& img, const cv::String& text, cv::Point pos, int fontSize, cv::Scalar color, float rotateAngle);
    void putTextRotateV(cv::Mat& img, const cv::String& text, cv::Point pos, int fontSize, cv::Scalar color, float rotateAngle);
    void putText(cv::Mat& img, const cv::String& text, cv::Point pos, cv::Scalar color, bool vertical = false);

private: 
	void putWChar(cv::Mat& img, wchar_t wc, cv::Point &pos, cv::Scalar color, bool vertical = false);
    
private:

	FT_Library   m_library;   // font library  
	FT_Face      m_face;      // font type
	FT_Matrix    m_matrix;
	FT_Vector    m_pen;
	FT_Error     m_error;

	FontProperty m_font;

};