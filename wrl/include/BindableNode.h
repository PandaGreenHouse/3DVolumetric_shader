/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	BindableNode.h
*
******************************************************************/

#ifndef _MYVRML_BINDABLENODE_H_
#define _MYVRML_BINDABLENODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

class BindableNode : public Node {

	SFBool *setBindField;
	SFTime *bindTimeField;
	SFBool *isBoundField;

public:

	BindableNode();
	virtual ~BindableNode();

	////////////////////////////////////////////////
	//	bind
	////////////////////////////////////////////////

	SFBool *getBindField() const;

	void setBind(bool value);
	bool  getBind() const;
	bool  isBind() const;

	////////////////////////////////////////////////
	//	bindTime
	////////////////////////////////////////////////
	
	SFTime *getBindTimeField() const;

	void setBindTime(double value);
	double getBindTime() const;

	////////////////////////////////////////////////
	//	isBound
	////////////////////////////////////////////////

	SFBool *getIsBoundField() const;

	void setIsBound(bool  value);
	bool  getIsBound() const;
	bool  isBound() const;
};

}

#endif
