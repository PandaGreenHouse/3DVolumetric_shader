/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SequencerNode.cpp
*
******************************************************************/

#include <VRML97Fields.h>
#include <SequencerNode.h>

using namespace MyVrml;

SequencerNode::SequencerNode() 
{
	// key exposed field
	keyField = new MFFloat();
	addExposedField(keyFieldString, keyField);

	// set_fraction eventIn field
	fractionField = new SFFloat(0.0f);
	addEventIn(fractionFieldString, fractionField);
}

SequencerNode::~SequencerNode() 
{
}

////////////////////////////////////////////////
//	key
////////////////////////////////////////////////

MFFloat *SequencerNode::getKeyField() const
{
	if (isInstanceNode() == false)
		return keyField;
	return (MFFloat *)getExposedField(keyFieldString);
}
	
void SequencerNode::addKey(float value) 
{
	getKeyField()->addValue(value);
}

int SequencerNode::getNKeys() const
{
	return getKeyField()->getSize();
}

float SequencerNode::getKey(int index) const
{
	return getKeyField()->get1Value(index);
}


////////////////////////////////////////////////
//	fraction
////////////////////////////////////////////////

SFFloat *SequencerNode::getFractionField() const
{
	if (isInstanceNode() == false)
		return fractionField;
	return (SFFloat *)getEventIn(fractionFieldString);
}
	
void SequencerNode::setFraction(float value) 
{
	getFractionField()->setValue(value);
}

float SequencerNode::getFraction() const
{
	return getFractionField()->getValue();
}
