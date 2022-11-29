/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File: ShapeNode.h
*
*	Revisions:
*
*	12/02/02
*		- Changed the super class from Node to BoundedNode.
*		- Added the follwing new X3D fields.
*			appearance, geometry
*
******************************************************************/

#ifndef _MYVRML_SHAPENODE_H_
#define _MYVRML_SHAPENODE_H_

#include <VRML97Fields.h>
#include <BoundedNode.h>
#include <AppearanceNode.h>
#include <Geometry3DNode.h>

namespace MyVrml {

class ShapeNode : public BoundedNode {

	SFNode *appField;
	SFNode *geomField;

public:

	ShapeNode();
	virtual ~ShapeNode();

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

	ShapeNode *next() const;
	ShapeNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	Geometry
	////////////////////////////////////////////////

	Geometry3DNode *getGeometry3D() const;

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

