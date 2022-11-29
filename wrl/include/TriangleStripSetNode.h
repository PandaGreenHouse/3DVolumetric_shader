/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TriangleStripSetNode.h
*
******************************************************************/

#ifndef _MYVRML_TRIANGLESTRIPSETNODE_H_
#define _MYVRML_TRIANGLESTRIPSETNODE_H_

#include <TriangleSetNode.h>

namespace MyVrml {

class TriangleStripSetNode : public TriangleSetNode {

	MFInt32 *stripCountField;
	
public:

	TriangleStripSetNode();
	virtual ~TriangleStripSetNode();
	
	////////////////////////////////////////////////
	// StripCount
	////////////////////////////////////////////////

	MFInt32 *getStripCountField() const;

	void addStripCount(int value);
	int getNStripCountes() const;
	int getStripCount(int index) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TriangleStripSetNode *next() const;
	TriangleStripSetNode *nextTraversal() const;

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

