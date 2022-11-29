/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriangleFanSetNode.h
*
******************************************************************/

#ifndef _MYVRML_TRIANGLEFANSETNODE_H_
#define _MYVRML_TRIANGLEFANSETNODE_H_

#include <TriangleSetNode.h>

namespace MyVrml {

class TriangleFanSetNode : public TriangleSetNode {

	MFInt32 *fanCountField;
	
public:

	TriangleFanSetNode();
	virtual ~TriangleFanSetNode();
	
	////////////////////////////////////////////////
	// FanCount
	////////////////////////////////////////////////

	MFInt32 *getFanCountField() const;

	void addFanCount(int value);
	int getNFanCountes() const;
	int getFanCount(int index) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TriangleFanSetNode *next() const;
	TriangleFanSetNode *nextTraversal() const;

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

