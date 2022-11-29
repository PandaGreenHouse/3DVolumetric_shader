/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	X3DParser.h
*
******************************************************************/

#ifndef _MYVRML_X3DPARSER_H_
#define _MYVRML_X3DPARSER_H_

#ifdef MYVRML_SUPPORT_X3D

#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>

#include <Parser.h>

namespace MyVrml {

class X3DParser : public Parser {

public:

	xercesc::XMLFormatter::UnRepFlags unRepFlags;
	xercesc::SAX2XMLReader::ValSchemes valScheme;

	char *encodingName;
	bool expandNamespaces;
	bool doNamespaces;
	bool doValidation;
	bool doSchema;
	bool schemaFullChecking;
	bool namespacePrefixes;

public:

	X3DParser();
	virtual ~X3DParser();

	bool loadA(const char *fileName, void (*callbackFn)(int nLine, void *info) = NULL, void *callbackFnInfo = NULL);
	bool loadW(const wchar_t *fileName, void (*callbackFn)(int nLine, void *info) = NULL, void *callbackFnInfo = NULL);
};

}

#endif

#endif
