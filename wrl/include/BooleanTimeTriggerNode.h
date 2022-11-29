/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	BooleanTimeTriggerNode.h
*
******************************************************************/

#ifndef _MYVRML_BOOLEANTIMETRIGGERNODE_H_
#define _MYVRML_BOOLEANTIMETRIGGERNODE_H_

#include <VRML97Fields.h>
#include <TriggerNode.h>

namespace MyVrml {

class BooleanTimeTriggerNode : public TriggerNode {
	
	SFBool *set_booleanTrueField;
	SFBool *set_booleanFalseField;
	SFBool *trueTriggerField;
	SFBool *falseTriggerField;

public:

	BooleanTimeTriggerNode();
	virtual ~BooleanTimeTriggerNode();

	////////////////////////////////////////////////
	//	SetBooleanTrue
	////////////////////////////////////////////////

	SFBool *getSetBooleanTrueField() const;
	
	void setSetBooleanTrue(bool value);
	bool getSetBooleanTrue() const;

	////////////////////////////////////////////////
	//	SetBooleanFalse
	////////////////////////////////////////////////

	SFBool *getSetBooleanFalseField() const;
	
	void setSetBooleanFalse(bool value);
	bool getSetBooleanFalse() const;

	////////////////////////////////////////////////
	//	TrueTrigger
	////////////////////////////////////////////////

	SFBool *getTrueTriggerField() const;
	
	void setTrueTrigger(bool value);
	bool getTrueTrigger() const;

	////////////////////////////////////////////////
	//	FalseTrigger
	////////////////////////////////////////////////

	SFBool *getFalseTriggerField() const;
	
	void setFalseTrigger(bool value);
	bool getFalseTrigger() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	BooleanTimeTriggerNode *next() const;
	BooleanTimeTriggerNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

