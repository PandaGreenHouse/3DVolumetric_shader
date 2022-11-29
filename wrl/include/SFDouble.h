/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFDouble.h
*
******************************************************************/

#ifndef _MYVRML_SFDOUBLE_H_
#define _MYVRML_SFDOUBLE_H_

#include <iostream>
#include <stdio.h>
#include <Field.h>

namespace MyVrml {

class SFDouble : public Field {

	double mValue; 

public:

	SFDouble();
	SFDouble(double value);
	SFDouble(SFDouble *value);

	void setValue(double value);
	void setValue(SFDouble *fvalue);
	double getValue() const;

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	friend std::ostream& operator<<(std::ostream &s, const SFDouble &value);
	friend std::ostream& operator<<(std::ostream &s, const SFDouble *value);

	////////////////////////////////////////////////
	//	String
	////////////////////////////////////////////////

	void setValue(const char *value);
	const char *getValue(char *buffer, int bufferLen) const;

	int getValueCount() const 
	{
		return 1;
	}

	////////////////////////////////////////////////
	//	Compare
	////////////////////////////////////////////////

	bool equals(Field *field) const;

};

}

#endif
