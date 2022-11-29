/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	InterpolatorNode.cpp
*
******************************************************************/

#include <VRML97Fields.h>
#include <InterpolatorNode.h>

using namespace MyVrml;

InterpolatorNode::InterpolatorNode() 
{
	// key exposed field
	keyField = new MFFloat();
	addExposedField(keyFieldString, keyField);

	// set_fraction eventIn field
	fractionField = new SFFloat(0.0f);
	addEventIn(fractionFieldString, fractionField);
}

InterpolatorNode::~InterpolatorNode() 
{
}

////////////////////////////////////////////////
//	key
////////////////////////////////////////////////

MFFloat *InterpolatorNode::getKeyField() const
{
	if (isInstanceNode() == false)
		return keyField;
	return (MFFloat *)getExposedField(keyFieldString);
}
	
void InterpolatorNode::addKey(float value) 
{
	getKeyField()->addValue(value);
}

int InterpolatorNode::getNKeys() const
{
	return getKeyField()->getSize();
}

float InterpolatorNode::getKey(int index) const
{
	return getKeyField()->get1Value(index);
}


////////////////////////////////////////////////
//	fraction
////////////////////////////////////////////////

SFFloat *InterpolatorNode::getFractionField() const
{
	if (isInstanceNode() == false)
		return fractionField;
	return (SFFloat *)getEventIn(fractionFieldString);
}
	
void InterpolatorNode::setFraction(float value) 
{
	getFractionField()->setValue(value);
}

float InterpolatorNode::getFraction() const
{
	return getFractionField()->getValue();
}


