/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Grouping2DNode.h
*
******************************************************************/

#ifndef _MYVRML_GROUPING2DNODE_H_
#define _MYVRML_GROUPING2DNODE_H_

#include <Node.h>
#include <BoundingBox.h>

namespace MyVrml {

class Grouping2DNode : public Node {

	SFVec2f *bboxCenterField;
	SFVec2f *bboxSizeField;

public:

	Grouping2DNode();
	virtual ~Grouping2DNode();

	////////////////////////////////////////////////
	//	BoundingBoxSize
	////////////////////////////////////////////////

	SFVec2f *getBoundingBoxSizeField() const;

	void setBoundingBoxSize(float value[]);
	void setBoundingBoxSize(float x, float y);
	void getBoundingBoxSize(float value[]) const;

	////////////////////////////////////////////////
	//	BoundingBoxCenter
	////////////////////////////////////////////////

	SFVec2f *getBoundingBoxCenterField() const;

	void setBoundingBoxCenter(float value[]);
	void setBoundingBoxCenter(float x, float y);
	void getBoundingBoxCenter(float value[]) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Grouping2DNode *next() const;
	Grouping2DNode *nextTraversal() const;
};

}

#endif

