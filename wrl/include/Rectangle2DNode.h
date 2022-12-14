/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Rectangle2DNode.h
*
******************************************************************/

#ifndef _MYVRML_RECTANGLE2D_H_
#define _MYVRML_RECTANGLE2D_H_

#include <Geometry2DNode.h>

namespace MyVrml {

class Rectangle2DNode : public Geometry2DNode {

	MFVec2f *sizeField;
	SFBool *isFilledField;

public:

	Rectangle2DNode();
	virtual ~Rectangle2DNode();

	////////////////////////////////////////////////
	//	Size
	////////////////////////////////////////////////

	MFVec2f *getSizeField() const;
	
	int getNSize() const;
	void addSize(float point[]);
	void addSize(float x, float y);
	void getSize(int index, float point[]) const;
	void setSize(int index, float point[]);
	void setSize(int index, float x, float y);
	void removeSize(int index);
	void removeAllSize();

	////////////////////////////////////////////////
	//	side
	////////////////////////////////////////////////

	SFBool *getIsFilledField() const;

	void setIsFilled(bool value);
	void setIsFilled(int value);
	bool getIsFilled() const;
	bool isFilled() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	Rectangle2DNode *next() const;
	Rectangle2DNode *nextTraversal() const;

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
