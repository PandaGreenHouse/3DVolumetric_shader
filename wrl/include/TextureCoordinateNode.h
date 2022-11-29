/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TextureCoordinateNode.h
*
******************************************************************/

#ifndef _MYVRML_TEXTURECOORDINATENODE_H_
#define _MYVRML_TEXTURECOORDINATENODE_H_

#include <VRML97Fields.h>
#include <GeometricPropertyNode.h>

namespace MyVrml {

class TextureCoordinateNode : public GeometricPropertyNode 
{
	
	MFVec2f *pointField;

public:

	TextureCoordinateNode();
	virtual ~TextureCoordinateNode();

	////////////////////////////////////////////////
	//	point 
	////////////////////////////////////////////////

	MFVec2f *getPointField() const;

	void addPoint(float point[]);
	int getNPoints() const;
	void getPoint(int index, float point[]) const;

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

	TextureCoordinateNode *next() const;
	TextureCoordinateNode *nextTraversal() const;

};

}

#endif

