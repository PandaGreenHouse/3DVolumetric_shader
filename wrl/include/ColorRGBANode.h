/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ColorRGBANode.h
*
******************************************************************/

#ifndef _MYVRML_COLORRGBANODE_H_
#define _MYVRML_COLORRGBANODE_H_

#include <GeometricPropertyNode.h>

namespace MyVrml {

class ColorRGBANode : public GeometricPropertyNode 
{

	MFColorRGBA *colorField;

public:

	ColorRGBANode();
	virtual ~ColorRGBANode();

	////////////////////////////////////////////////
	//	color
	////////////////////////////////////////////////
	
	MFColorRGBA *getColorField() const;

	void addColor(float color[]);
	int getNColors() const;
	void getColor(int index, float color[]) const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	ColorRGBANode *next() const;
	ColorRGBANode *nextTraversal() const;
};

}

#endif
