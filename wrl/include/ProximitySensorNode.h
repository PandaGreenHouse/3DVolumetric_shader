/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ProximitySensorNode.h
*
******************************************************************/

#ifndef _MYVRML_PROXIMITYSENSORNODE_H_
#define _MYVRML_PROXIMITYSENSORNODE_H_

#include <EnvironmentalSensorNode.h>

namespace MyVrml {

class ProximitySensorNode : public EnvironmentalSensorNode
{
	SFVec3f *positionField;
	SFRotation *orientationField;
	SFBool *inRegionField;
	
public:

	ProximitySensorNode();
	virtual ~ProximitySensorNode();

	////////////////////////////////////////////////
	//	Position
	////////////////////////////////////////////////

	SFVec3f *getPositionChangedField() const;
	
	void setPositionChanged(float value[]);
	void setPositionChanged(float x, float y, float z);
	void getPositionChanged(float value[]) const;

	////////////////////////////////////////////////
	//	Orientation
	////////////////////////////////////////////////

	SFRotation *getOrientationChangedField() const;
	
	void setOrientationChanged(float value[]);
	void setOrientationChanged(float x, float y, float z, float rot);
	void getOrientationChanged(float value[]) const;

	////////////////////////////////////////////////
	//	inRegion
	////////////////////////////////////////////////

	SFBool *getInRegionField() const;

	void setInRegion(bool value);
	bool inRegion() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	ProximitySensorNode *next() const;
	ProximitySensorNode *nextTraversal() const;

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

