/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SphereSensorNode.h
*
******************************************************************/

#ifndef _MYVRML_SPHERESENSOR_H_
#define _MYVRML_SPHERESENSOR_H_

#include <DragSensorNode.h>

namespace MyVrml {

class SphereSensorNode : public DragSensorNode {

	SFRotation *offsetField;
	SFRotation *rotationField;
	
public:

	SphereSensorNode();
	virtual ~SphereSensorNode();

	////////////////////////////////////////////////
	//	Offset
	////////////////////////////////////////////////

	SFRotation *getOffsetField() const;
	
	void setOffset(float value[]);
	void getOffset(float value[]) const;

	////////////////////////////////////////////////
	//	Rotation
	////////////////////////////////////////////////

	SFRotation *getRotationChangedField() const;
	
	void setRotationChanged(float value[]);
	void setRotationChanged(float x, float y, float z, float rot);
	void getRotationChanged(float value[]) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	SphereSensorNode *next() const;
	SphereSensorNode *nextTraversal() const;

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

