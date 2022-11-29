/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TimeTriggerNode.h
*
******************************************************************/

#ifndef _MYVRML_TIMETRIGGERNODE_H_
#define _MYVRML_TIMETRIGGERNODE_H_

#include <VRML97Fields.h>
#include <TriggerNode.h>

namespace MyVrml {

class TimeTriggerNode : public TriggerNode {
	
	SFBool *set_booleanField;
	SFTime *triggerTimeField;

public:

	TimeTriggerNode();
	virtual ~TimeTriggerNode();

	////////////////////////////////////////////////
	//	Boolean
	////////////////////////////////////////////////

	SFBool *getBooleanField() const;
	
	void setBoolean(bool value);
	bool getBoolean() const;
	bool isBoolean() const;

	////////////////////////////////////////////////
	//	triggerTime
	////////////////////////////////////////////////

	SFTime* getTriggerTimeField() const;
	
	void setTriggerTime(double value);
	double getTriggerTime() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TimeTriggerNode *next() const;
	TimeTriggerNode *nextTraversal() const;

};

}

#endif
