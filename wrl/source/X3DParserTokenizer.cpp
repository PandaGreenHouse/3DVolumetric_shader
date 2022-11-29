/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	X3DParserTokenizer.cpp
*
******************************************************************/

#include <X3DParserTokenizer.h>

#ifdef MYVRML_SUPPORT_X3D

using namespace MyVrml;
using namespace xercesc;

////////////////////////////////////////////////
//	X3DParserTokenizer
////////////////////////////////////////////////

static const char *tokenDelim = " ,\"\t\r\n";

X3DParserTokenizer::X3DParserTokenizer(const XMLCh *const srcStr) : XMLStringTokenizer(srcStr, XMLString::transcode(tokenDelim))
{
}

////////////////////////////////////////////////
//	~X3DParserTokenizer
////////////////////////////////////////////////

X3DParserTokenizer::~X3DParserTokenizer()
{
}

#endif

