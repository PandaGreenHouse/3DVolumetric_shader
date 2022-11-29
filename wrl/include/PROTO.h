/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	PROTO.h
*
******************************************************************/

#ifndef _MYVRML_PROTO_H_
#define _MYVRML_PROTO_H_

#include <LinkedList.h>
#include <StringUtil.h>
#include <Field.h>
#include <Vector.h>

namespace MyVrml {

class PROTO : public LinkedListNode<PROTO> {
	String				mName;
	String				mString;
	Vector<Field>		mDefaultFieldVector;
	Vector<Field>		mFieldVector;
public:

	PROTO(const char *name, const char *string, const char *fieldString);
	virtual ~PROTO(void);

	void		setName(const char *name);
	const char		*getName(void) const;

	void		setString(const char *string);
	const char		*getString() const;
	void		getString(String &returnString) const;

	void		addDefaultField(Field *field);
	void		addField(Field *field);

	int			getNDefaultFields() const;
	int			getNFields() const;

	Field		*getDefaultField(int n) const;
	Field		*getField(int n) const;

	void		addFieldValues(const char *fieldString, int bDefaultField);
	void		addDefaultFields(const char *fieldString);
	void		addFields(const char *fieldString);
	void		deleteDefaultFields(void);
	void		deleteFields(void);

	Field		*getField(const char *name) const;
	int			getFieldType(const char *name) const;
};

}

#endif


