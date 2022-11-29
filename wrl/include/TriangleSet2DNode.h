/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriangleSet2DNode.h
*
******************************************************************/

#ifndef _MYVRML_TRIANGLESET2D_H_
#define _MYVRML_TRIANGLESET2D_H_

#include <Geometry2DNode.h>

namespace MyVrml {

class TriangleSet2DNode : public Geometry2DNode {

	MFVec2f *verticesField;

public:

	TriangleSet2DNode();
	virtual ~TriangleSet2DNode();

	////////////////////////////////////////////////
	//	Vertices
	////////////////////////////////////////////////

	MFVec2f *getVerticesField() const;
	
	int getNVertices() const;
	void addVertex(float point[]);
	void addVertex(float x, float y);
	void getVertex(int index, float point[]) const;
	void setVertex(int index, float point[]);
	void setVertex(int index, float x, float y);
	void removeVertex(int index);
	void removeAllVertices();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TriangleSet2DNode *next() const;
	TriangleSet2DNode *nextTraversal() const;

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
