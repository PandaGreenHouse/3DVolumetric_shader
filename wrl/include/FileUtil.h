/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	FileUtil.h
*
******************************************************************/

#ifndef _MYVRML_FILEUTIL_H_
#define _MYVRML_FILEUTIL_H_

#include <MyVrmlConfig.h>

namespace MyVrml {

enum {
FILE_FORMAT_NONE,
FILE_FORMAT_VRML,
FILE_FORMAT_XML,
FILE_FORMAT_X3D,
FILE_FORMAT_GIF,
FILE_FORMAT_JPEG,
FILE_FORMAT_TARGA,
FILE_FORMAT_PNG
};

int GetFileFormatA(const char *filename);
int GetFileFormatW(const wchar_t *filename);
}

#endif
