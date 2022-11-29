/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	UrlFile.h
*
******************************************************************/

#ifndef _MYVRML_URLFILE_H_
#define _MYVRML_URLFILE_H_

#include <JavaVM.h>
#include <StringUtil.h>

#if defined(MYVRML_SUPPORT_URL)

namespace MyVrml {

class UrlFile : public JavaVM {

	static jclass		mUrlGetStreamClassID;
	static jmethodID	mUrlGetStreamInitMethodID;
	static jmethodID	mUrlGetStreamGetStreamMethodID;
	static jobject		mUrlGetStreamObject;		

	String				*mUrl;	
	String				*mUrlString;

public:

	UrlFile();
	virtual ~UrlFile();
	void	initialize();
	void	setUrl(char *urlString);
	const char	*getUrl() const;
	bool	getStream(const char *urlString) const;
	char	*getOutputFilename();
	bool	deleteOutputFilename();
};

}

#endif

#endif
