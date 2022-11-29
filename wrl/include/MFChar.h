/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	MFChar.h
*
******************************************************************/

#ifndef _MYVRML_MFCHAR_H_
#define _MYVRML_MFCHAR_H_

#include <MField.h>
#include <SFChar.h>

namespace MyVrml {

class MFChar : public MField {

public:

	MFChar();

	void addValue(char value);
	void addValue(SFChar *sfvalue);
	void addValue(const char *value);

	void insertValue(int index, char value);
	char get1Value(int index) const;
	void set1Value(int index, char value);

	void setValue(MField *mfield);
	void setValue(MFChar *values);
	void setValue(int size, char values[]);

	int getValueCount() const 
	{
		return 1;
	}

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream& printStream, const char *indentString) const;

};

}

#endif
