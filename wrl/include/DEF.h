/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	DEF.h
*
******************************************************************/

#ifndef _MYVRML_DEF_H_
#define _MYVRML_DEF_H_

#include <StringUtil.h>
#include <LinkedListNode.h>

namespace MyVrml {

class DEF : public LinkedListNode<DEF> {

	String		mName;
	String		mString;

public:

	DEF (const char *name, const char *string);
	virtual ~DEF();

	////////////////////////////////////////////////
	//	Name
	////////////////////////////////////////////////

	void setName(const char *name);
	const char *getName() const;

	////////////////////////////////////////////////
	//	Name
	////////////////////////////////////////////////

	void setString(const char *string);
	const char *getString() const;
};

}

#endif


