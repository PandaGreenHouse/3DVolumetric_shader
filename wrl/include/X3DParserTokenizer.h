/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	X3DParserTokenizer.h
*
******************************************************************/

#include <MyVrmlConfig.h>

#ifdef MYVRML_SUPPORT_X3D

#ifndef _MYVRML_X3DPARSERTOKENIZER_H_
#define _MYVRML_X3DPARSERTOKENIZER_H_

#include <xercesc/util/XMLStringTokenizer.hpp>

namespace MyVrml {

class X3DParserTokenizer : public xercesc::XMLStringTokenizer {

public:

	X3DParserTokenizer(const XMLCh *const srcStr);
	virtual ~X3DParserTokenizer();

};

}

#endif

#endif
