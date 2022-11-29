/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriangleSetNode.h
*
******************************************************************/

#ifndef _MYVRML_TRIANGLESETNODE_H_
#define _MYVRML_TRIANGLESETNODE_H_

#include <ComposedGeometryNode.h>
#include <NormalNode.h>
#include <ColorNode.h>
#include <CoordinateNode.h>
#include <TextureCoordinateNode.h>

namespace MyVrml {

class TriangleSetNode : public ComposedGeometryNode 
{
	SFBool *convexField;
	SFFloat *creaseAngleField;
	
public:

	TriangleSetNode();
	virtual ~TriangleSetNode();
	
	////////////////////////////////////////////////
	//	Convex
	////////////////////////////////////////////////

	SFBool *getConvexField() const;
	
	void setConvex(bool value);
	void setConvex(int value);
	bool getConvex() const;

	////////////////////////////////////////////////
	//	CreaseAngle
	////////////////////////////////////////////////

	SFFloat *getCreaseAngleField() const;
	
	void setCreaseAngle(float value);
	float getCreaseAngle() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TriangleSetNode *next() const;
	TriangleSetNode *nextTraversal() const;

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
	//	Polygon
	////////////////////////////////////////////////

	int getNPolygons() const;

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

};

}

#endif

