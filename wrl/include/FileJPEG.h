/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	FileJPEG.h
*
******************************************************************/

#ifndef _MYVRML_FILEJPEG_H_
#define _MYVRML_FILEJPEG_H_

#include <FileImage.h>

#ifdef MYVRML_SUPPORT_JPEG

namespace MyVrml {

class FileJPEG : public FileImage {
	int			width;
	int			height;
	RGBColor24	*imgBuffer;

public:	

	FileJPEG(const char *filename);
	virtual ~FileJPEG();
	
	bool load(const char *filename);

	int getFileType() const {
		return FILE_FORMAT_JPEG;
	}

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}
	
	RGBColor24 *getImage() const {
		return imgBuffer;
	}
};

}

#endif

#endif
