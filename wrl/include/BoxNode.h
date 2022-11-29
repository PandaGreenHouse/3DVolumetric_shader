/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	BoxNode.h
*
******************************************************************/

#ifndef _MYVRML_BOX_H_
#define _MYVRML_BOX_H_

#include <VRML97Fields.h>
#include <Geometry3DNode.h>

namespace MyVrml {

class BoxNode : public Geometry3DNode {

	SFVec3f *sizeField;
	
public:

	BoxNode();
	virtual ~BoxNode();

	////////////////////////////////////////////////
	//	size
	////////////////////////////////////////////////

	SFVec3f *getSizeField() const;

	void setSize(float value[]);
	void setSize(float x, float y, float z);
	void getSize(float value[]) const;
	float getX() const;
	float getY() const;
	float getZ() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	BoxNode *next() const;
	BoxNode *nextTraversal() const;

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
		return 6;
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
