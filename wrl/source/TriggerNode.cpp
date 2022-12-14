/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriggerNode.cpp
*
******************************************************************/

#include <TriggerNode.h>

using namespace MyVrml;

static const char set_triggerTimeFieldString[] = "set_triggerTime";
static const char triggerTimeFieldString[] = "triggerTime";

TriggerNode::TriggerNode() 
{
	// triggerTimeField eventIn field
	set_triggerTimeField = new SFTime();
	addEventIn(set_triggerTimeFieldString, set_triggerTimeField);

	// triggerTimeField eventOut field
	triggerTimeField = new SFTime();
	addEventOut(triggerTimeFieldString, triggerTimeField);
}

TriggerNode::~TriggerNode() 
{
}

////////////////////////////////////////////////
//	SetTriggerTime
////////////////////////////////////////////////

SFTime *TriggerNode::getSetTriggerTimeField() const
{
	if (isInstanceNode() == false)
		return set_triggerTimeField;
	return (SFTime *)getEventIn(set_triggerTimeFieldString);
}
	
void TriggerNode::setSetTriggerTime(double value) 
{
	getSetTriggerTimeField()->setValue(value);
}

double TriggerNode::getSetTriggerTime() const
{
	return getSetTriggerTimeField()->getValue();
}

////////////////////////////////////////////////
//	TriggerTime
////////////////////////////////////////////////

SFTime *TriggerNode::getTriggerTimeField() const
{
	if (isInstanceNode() == false)
		return triggerTimeField;
	return (SFTime *)getEventOut(triggerTimeFieldString);
}
	
void TriggerNode::setTriggerTime(double value) 
{
	getTriggerTimeField()->setValue(value);
}

double TriggerNode::getTriggerTime() const
{
	return getTriggerTimeField()->getValue();
}
