/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Polypoint2DNode.h
*
******************************************************************/

#ifndef _MYVRML_POLYPOINT2D_H_
#define _MYVRML_POLYPOINT2D_H_

#include <Geometry2DNode.h>

namespace MyVrml {

class Polypoint2DNode : public Geometry2DNode {

	MFVec2f *pointsField;

public:

	Polypoint2DNode();
	virtual ~Polypoint2DNode();

	////////////////////////////////////////////////
	//	Points
	////////////////////////////////////////////////

	MFVec2f *getPointsField() const;
	
	int getNPoints() const;
	void addPoint(float point[]);
	void addPoint(float x, float y);
	void getPoint(int index, float point[]) const;
	void setPoint(int index, float point[]);
	void setPoint(int index, float x, float y);
	void removePoint(int index);
	void removeAllPoints();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Polypoint2DNode *next() const;
	Polypoint2DNode *nextTraversal() const;

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
