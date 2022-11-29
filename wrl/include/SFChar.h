/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFChar.h
*
******************************************************************/

#ifndef _MYVRML_SFCHAR_H_
#define _MYVRML_SFCHAR_H_

#include <iostream>
#include <stdio.h>
#include <Field.h>

namespace MyVrml {

class SFChar : public Field {

	char mValue; 

public:

	SFChar();
	SFChar(char value);
	SFChar(SFChar *value);

	void setValue(char value);
	void setValue(SFChar *fvalue);
	char getValue() const;

	int getValueCount() const 
	{
		return 1;
	}

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	friend std::ostream& operator<<(std::ostream &s, const SFChar &value);
	friend std::ostream& operator<<(std::ostream &s, const SFChar *value);

	////////////////////////////////////////////////
	//	String
	////////////////////////////////////////////////

	void setValue(const char *value);
	const char *getValue(char *buffer, int bufferLen) const;

	////////////////////////////////////////////////
	//	Compare
	////////////////////////////////////////////////

	bool equals(Field *field) const;

};

}

#endif
