/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	DEF.cpp
*
******************************************************************/

#include <DEF.h>

using namespace MyVrml;

DEF::DEF(const char *name, const char *string) 
{
	setName(name);
	setString(string);
}

DEF::~DEF() 
{
	remove();
}

////////////////////////////////////////////////
//	Name
////////////////////////////////////////////////

void DEF::setName(const char *name) 
{
	mName.setValue(name);
}

const char *DEF::getName() const
{
	return mName.getValue();
}

////////////////////////////////////////////////
//	String
////////////////////////////////////////////////

void DEF::setString(const char *string) 
{
	mString.setValue(string);
}

const char *DEF::getString() const
{
	return mString.getValue();
}
