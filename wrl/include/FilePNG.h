/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	FilePNG.h
*
******************************************************************/

#ifndef _MYVRML_FILEPNG_H_
#define _MYVRML_FILEPNG_H_

#include <FileImage.h>

#ifdef MYVRML_SUPPORT_PNG

namespace MyVrml {

class FilePNG : public FileImage {
	int			mWidth;
	int			mHeight;
	RGBColor24	*mImgBuffer;
	bool		mHasTransparencyColor;
	RGBColor24	mTransparencyColor;
public:	

	FilePNG(const char *filename);
	virtual ~FilePNG();
	
	bool load(const char *filename);

	int getFileType() const {
		return FILE_FORMAT_PNG;
	}

	int getWidth() const {
		return mWidth;
	}

	int getHeight() const {
		return mHeight;
	}
	
	RGBColor24 *getImage() const {
		return mImgBuffer;
	}

	bool hasTransparencyColor() const {
		return mHasTransparencyColor;
	}

	void setTransparencyColor(RGBColor24 color);

	void getTransparencyColor(RGBColor24 color) const;

};

}

#endif

#endif
