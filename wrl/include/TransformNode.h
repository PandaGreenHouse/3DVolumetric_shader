/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TransformNode.h
*
******************************************************************/

#ifndef _MYVRML_TRANSFORMNODE_H_
#define _MYVRML_TRANSFORMNODE_H_

#include <VRML97Fields.h>
#include <Node.h>
#include <BoundedGroupingNode.h>

namespace MyVrml {

class TransformNode : public BoundedGroupingNode {

	SFVec3f *translationField;
	SFVec3f *scaleField;
	SFVec3f *centerField;
	SFRotation *rotationField;
	SFRotation *scaleOrientationField;

public:

	TransformNode();
	virtual ~TransformNode();

	////////////////////////////////////////////////
	//	Translation
	////////////////////////////////////////////////

	SFVec3f *getTranslationField() const;

	void setTranslation(float value[]);
	void setTranslation(float x, float y, float z);
	void getTranslation(float value[]) const;

	////////////////////////////////////////////////
	//	Scale
	////////////////////////////////////////////////

	SFVec3f *getScaleField() const;

	void setScale(float value[]);
	void setScale(float x, float y, float z);
	void getScale(float value[]) const;

	////////////////////////////////////////////////
	//	Center
	////////////////////////////////////////////////

	SFVec3f *getCenterField() const;

	void setCenter(float value[]);
	void setCenter(float x, float y, float z);
	void getCenter(float value[]) const;

	////////////////////////////////////////////////
	//	Rotation
	////////////////////////////////////////////////

	SFRotation *getRotationField() const;

	void setRotation(float value[]);
	void setRotation(float x, float y, float z, float w);
	void getRotation(float value[]) const;

	////////////////////////////////////////////////
	//	ScaleOrientation
	////////////////////////////////////////////////

	SFRotation *getScaleOrientationField() const;

	void setScaleOrientation(float value[]);
	void setScaleOrientation(float x, float y, float z, float w);
	void getScaleOrientation(float value[]) const;

	////////////////////////////////////////////////
	//	Matrix
	////////////////////////////////////////////////

	void getSFMatrix(SFMatrix *mOut) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TransformNode *next() const;
	TransformNode *nextTraversal() const;

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

