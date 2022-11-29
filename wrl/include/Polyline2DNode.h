/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Polyline2DNode.h
*
******************************************************************/

#ifndef _MYVRML_POLYLINE2D_H_
#define _MYVRML_POLYLINE2D_H_

#include <Geometry2DNode.h>

namespace MyVrml {

class Polyline2DNode : public Geometry2DNode {

	MFVec2f *lineSegmentsField;

public:

	Polyline2DNode();
	virtual ~Polyline2DNode();

	////////////////////////////////////////////////
	//	LineSegments
	////////////////////////////////////////////////

	MFVec2f *getLineSegmentsField() const;
	
	int getNLineSegments() const;
	void addLineSegment(float point[]);
	void addLineSegment(float x, float y);
	void getLineSegment(int index, float point[]) const;
	void setLineSegment(int index, float point[]);
	void setLineSegment(int index, float x, float y);
	void removeLineSegment(int index);
	void removeAllLineSegments();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Polyline2DNode *next() const;
	Polyline2DNode *nextTraversal() const;

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
