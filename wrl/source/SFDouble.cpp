/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFDouble.cpp
*
******************************************************************/

#include <stdio.h>
#include <SFDouble.h>

using namespace MyVrml;

SFDouble::SFDouble() 
{
	setType(fieldTypeSFDouble);
	setValue(0.0);
}

SFDouble::SFDouble(double value) 
{
	setType(fieldTypeSFDouble);
	setValue(value);
}

SFDouble::SFDouble(SFDouble *value) 
{
	setType(fieldTypeSFDouble);
	setValue(value);
}

void SFDouble::setValue(double value) 
{
	mValue = value;
}

void SFDouble::setValue(SFDouble *fvalue) 
{
	mValue = fvalue->getValue();
}

double SFDouble::getValue() const
{
	return mValue;
}

////////////////////////////////////////////////
//	Output
////////////////////////////////////////////////

std::ostream& MyVrml::operator<<(std::ostream &s, const SFDouble &value) 
{
	return s << value.getValue();
}

std::ostream& MyVrml::operator<<(std::ostream &s, const SFDouble *value) 
{
	return s << value->getValue();
}

////////////////////////////////////////////////
//	String
////////////////////////////////////////////////

void SFDouble::setValue(const char *value) 
{
	if (!value)
		return;
	setValue(atof(value));
}

const char *SFDouble::getValue(char *buffer, int bufferLen) const
{
	snprintf(buffer, bufferLen, "%g", getValue());
	return buffer;
}

////////////////////////////////////////////////
//	Compare
////////////////////////////////////////////////

bool SFDouble::equals(Field *field) const
{
	SFDouble *doubleField = (SFDouble *)field;
	if (getValue() == doubleField->getValue())
		return true;
	else
		return false;
}
