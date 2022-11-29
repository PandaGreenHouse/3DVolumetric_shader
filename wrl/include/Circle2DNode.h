/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Circle2DNode.h
*
******************************************************************/

#ifndef _MYVRML_CIRCLE2D_H_
#define _MYVRML_CIRCLE2D_H_

#include <Geometry2DNode.h>

namespace MyVrml {

class Circle2DNode : public Geometry2DNode {

	SFFloat *radiusField;

public:

	Circle2DNode();
	virtual ~Circle2DNode();

	////////////////////////////////////////////////
	//	Radius
	////////////////////////////////////////////////

	SFFloat *getRadiusField() const;
	
	void setRadius(float value);
	float getRadius() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Circle2DNode *next() const;
	Circle2DNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

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

