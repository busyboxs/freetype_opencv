#include <ft2build.h>  
#include FT_FREETYPE_H  

#include <opencv2/opencv.hpp>  

class CvxText
{
	CvxText& operator=(const CvxText&);
public:

	/**
	* 装载字库文件
	*/
	CvxText(const char *freeType);
	virtual ~CvxText();

	void getFont(int *type, CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);
	void setFont(int *type, CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);
	void restoreFont();

	int putText(IplImage *img, const char *text, CvPoint pos);
	int putText(IplImage *img, const wchar_t *text, CvPoint pos);
	int putText(IplImage *img, const char *text, CvPoint pos, CvScalar color);
	int putText(IplImage *img, const wchar_t *text, CvPoint pos, CvScalar color);

private:

	// 输出当前字符, 更新m_pos位置  

	void putWChar(IplImage *img, wchar_t wc, CvPoint &pos, CvScalar color);

private:

	FT_Library   m_library;   // 字库  
	FT_Face      m_face;      // 字体  

	int         m_fontType;
	CvScalar   m_fontSize;
	bool      m_fontUnderline;
	float      m_fontDiaphaneity;

};
