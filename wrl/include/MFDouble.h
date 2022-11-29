/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	MFDouble.h
*
******************************************************************/

#ifndef _MYVRML_MFDOUBLE_H_
#define _MYVRML_MFDOUBLE_H_

#include <MField.h>
#include <SFDouble.h>

namespace MyVrml {

class MFDouble : public MField {

public:

	MFDouble();

	void addValue(double value);
	void addValue(SFDouble *sfvalue);
	void addValue(const char *value);

	void insertValue(int index, double value);
	double get1Value(int index) const;
	void set1Value(int index, double value);

	void setValue(MField *mfield);
	void setValue(MFDouble *values);
	void setValue(int size, double values[]);

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
