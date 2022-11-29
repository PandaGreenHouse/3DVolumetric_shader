/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	XMLElement.h
*
******************************************************************/

#ifndef _MYVRML_XMLELEMENT_H_
#define _MYVRML_XMLELEMENT_H_

#include <iostream>
#include <Field.h>
#include <StringUtil.h>

namespace MyVrml {

class XMLElement : public Field {

	static	int	mInit;

	String	mValue;

public:

	XMLElement();
	XMLElement(const char *value);
	XMLElement(XMLElement *value);

	virtual ~XMLElement();

	void setValue(const char *value);
	void setValue(XMLElement *value);
	const char *getValue() const;

	int getValueCount() const
	{
		return 1;
	}

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	friend std::ostream& operator<<(std::ostream &s, const XMLElement &string);
	friend std::ostream& operator<<(std::ostream &s, const XMLElement *string);

	////////////////////////////////////////////////
	//	String
	////////////////////////////////////////////////

	const char *getValue(char *buffer, int bufferLen) const;
	const char *getValue(String &buffer) const;

	////////////////////////////////////////////////
	//	Compare
	////////////////////////////////////////////////

	bool equals(Field *field) const;

};

}

#endif
