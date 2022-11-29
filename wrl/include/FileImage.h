/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	FileImage.h
*
******************************************************************/

#ifndef _MYVRML_FILEIMAGE_H_
#define _MYVRML_FILEIMAGE_H_

#include <MyVrmlConfig.h>

#ifdef MYVRML_SUPPORT_OLDCPP
#include <OldCpp.h>
#endif

#include <FileUtil.h>

namespace MyVrml {

#if !R && !G && !B
#define R	0
#define G	1
#define B	2
#endif

typedef unsigned char RGBColor24[3];
typedef unsigned char RGBAColor32[4];

class FileImage {

public:

	FileImage();
	virtual ~FileImage();

	bool isOk() const;
	
	virtual int			getFileType() const = 0;

	virtual int			getWidth() const = 0;
	virtual int			getHeight() const = 0;
	virtual RGBColor24	*getImage() const = 0;

	virtual bool hasTransparencyColor() const {
		return false;
	}

	virtual void getTransparencyColor(RGBColor24 color) const {
	};

	RGBColor24	*getImage(int newx, int newy) const;
	RGBAColor32	*getRGBAImage() const;
	RGBAColor32	*getRGBAImage(int newx, int newy) const;
};

}

#endif
