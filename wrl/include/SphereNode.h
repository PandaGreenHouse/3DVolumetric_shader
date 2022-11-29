/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SphereNode.h
*
******************************************************************/

#ifndef _MYVRML_SPHERENODE_H_
#define _MYVRML_SPHERENODE_H_

#include <Geometry3DNode.h>

namespace MyVrml {

const int DEFAULT_SPHERE_SLICES = 16;

class SphereNode : public Geometry3DNode {

	SFFloat *radiusField;

public:

	SphereNode();
	virtual ~SphereNode();

	////////////////////////////////////////////////
	//	Radius
	////////////////////////////////////////////////

	SFFloat *getRadiusField() const;
	
	void setRadius(float value);
	float getRadius() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	SphereNode *next() const;
	SphereNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	BoundingBox
	////////////////////////////////////////////////

	void recomputeBoundingBox();

	////////////////////////////////////////////////
	//	Polygons
	////////////////////////////////////////////////

	int getNPolygons() const;

	////////////////////////////////////////////////
	//	recomputeDisplayList
	////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL
	void recomputeDisplayList();
#endif

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

