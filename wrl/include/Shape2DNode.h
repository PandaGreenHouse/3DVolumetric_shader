/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File: Shape2DNode.h
*
*	Revisions:
*
*	12/02/02
*		- The first revision.
*
******************************************************************/

#ifndef _MYVRML_SHAPE2DNODE_H_
#define _MYVRML_SHAPE2DNODE_H_

#include <VRML97Fields.h>
#include <Bounded2DNode.h>

namespace MyVrml {

class Shape2DNode : public Bounded2DNode {

	SFNode *appField;
	SFNode *geomField;

public:

	Shape2DNode();
	virtual ~Shape2DNode();

	////////////////////////////////////////////////
	//	Appearance
	////////////////////////////////////////////////

	SFNode *getAppearanceField() const;

	////////////////////////////////////////////////
	//	Geometry
	////////////////////////////////////////////////

	SFNode *getGeometryField() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Shape2DNode *next() const;
	Shape2DNode *nextTraversal() const;

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

