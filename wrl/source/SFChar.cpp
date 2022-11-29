/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFChar.cpp
*
******************************************************************/

#include <stdio.h>
#include <SFChar.h>

using namespace MyVrml;

SFChar::SFChar() 
{
	setType(fieldTypeSFChar);
	setValue(' ');
}

SFChar::SFChar(char value) 
{
	setType(fieldTypeSFChar);
	setValue(value);
}

SFChar::SFChar(SFChar *value) 
{
	setType(fieldTypeSFChar);
	setValue(value);
}

void SFChar::setValue(char value) 
{
	mValue = value;
}

void SFChar::setValue(SFChar *fvalue) 
{
	mValue = fvalue->getValue();
}

char SFChar::getValue() const
{
	return mValue;
}

////////////////////////////////////////////////
//	Output
////////////////////////////////////////////////

std::ostream& MyVrml::operator<<(std::ostream &s, const SFChar &value) 
{
	return s << value.getValue();
}

std::ostream& MyVrml::operator<<(std::ostream &s, const SFChar *value) 
{
	return s << value->getValue();
}

////////////////////////////////////////////////
//	String
////////////////////////////////////////////////

void SFChar::setValue(const char *value) 
{
	if (!value)
		return;
	if (strlen(value) <= 0)
		return;
	setValue((char)value[0]);
}

const char *SFChar::getValue(char *buffer, int bufferLen) const
{
	snprintf(buffer, bufferLen, "%c", getValue());
	return buffer;
}

////////////////////////////////////////////////
//	Compare
////////////////////////////////////////////////

bool SFChar::equals(Field *field) const
{
	SFChar *charField = (SFChar *)field;
	if (getValue() == charField->getValue())
		return true;
	return false;
}
