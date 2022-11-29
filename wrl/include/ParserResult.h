/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ParserResult.h
*
******************************************************************/

#ifndef _MYVRML_PARSERRESULT_H_
#define _MYVRML_PARSERRESULT_H_

#include <StringUtil.h>

namespace MyVrml {

class ParserResult {

	int						mErrorLineNumber;
	String					mErrorMsg;
	String					mErrorToken;
	String					mErrorLineString;
	bool					mIsOK;

public:

	ParserResult()
	{
	}

	virtual ~ParserResult()
	{
	}

	void init()
	{
		setParserResult(false);
		setErrorLineNumber(0);
		setErrorMessage("");
		setErrorToken("");
		setErrorLineString(""); 
	}

	void setParserResult(bool bOK) { 
		mIsOK = bOK; 
	}
	bool getParserResult() const { 
		return mIsOK; 
	}
	bool isOK(void) const {
		return getParserResult(); 
	}

	void setErrorLineNumber(int n) { 
		mErrorLineNumber = n; 
	}
	int	getErrorLineNumber(void) const{
		return mErrorLineNumber; 
	}

	void setErrorMessage(const char *msg) {
		mErrorMsg.setValue(msg); 
	}
	const char *getErrorMessage(void) const { 
		return mErrorMsg.getValue(); 
	}

	void setErrorToken(const char *error) {
		mErrorToken.setValue(error); 
	}
	const char *getErrorToken(void) const { 
		return mErrorToken.getValue(); 
	}

	void setErrorLineString(const char *error) { 
		mErrorLineString.setValue(error); 
	}
	const char *getErrorLineString(void) const {
		return mErrorLineString.getValue(); 
	}
};

}

#endif


