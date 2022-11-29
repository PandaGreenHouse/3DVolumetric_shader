/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	PointSetNode.h
*
******************************************************************/

#ifndef _MYVRML_POINTSET_H_
#define _MYVRML_POINTSET_H_

#include <Geometry3DNode.h>
#include <ColorNode.h>
#include <CoordinateNode.h>

namespace MyVrml {

class PointSetNode : public Geometry3DNode {

public:

	PointSetNode();
	virtual ~PointSetNode();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	PointSetNode *next() const;
	PointSetNode *nextTraversal() const;

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

	int getNPolygons() const {
		return 0;
	}

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

