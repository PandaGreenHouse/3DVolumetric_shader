/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriggerNode.h
*
******************************************************************/

#ifndef _MYVRML_TRIGGERNODE_H_
#define _MYVRML_TRIGGERNODE_H_

#include <VRML97Fields.h>
#include <SensorNode.h>

namespace MyVrml {

class TriggerNode : public SensorNode {
	
	SFTime *set_triggerTimeField;
	SFTime *triggerTimeField;

public:

	TriggerNode();
	virtual ~TriggerNode();

	////////////////////////////////////////////////
	//	SetTriggerTime
	////////////////////////////////////////////////

	SFTime *getSetTriggerTimeField() const;
	
	void setSetTriggerTime(double value);
	double getSetTriggerTime() const;

	////////////////////////////////////////////////
	//	TriggerTime
	////////////////////////////////////////////////

	SFTime *getTriggerTimeField() const;
	
	void setTriggerTime(double value);
	double getTriggerTime() const;

};

}

#endif

