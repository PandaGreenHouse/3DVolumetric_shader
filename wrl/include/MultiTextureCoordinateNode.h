/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	MultiTextureCoordinateNode.h
*
******************************************************************/

#ifndef _MYVRML_MULTITEXTURECOORDINATENODE_H_
#define _MYVRML_MULTITEXTURECOORDINATENODE_H_

#include <X3DFields.h>
#include <Node.h>

namespace MyVrml {

class MultiTextureCoordinateNode : public Node
{
	MFNode *texCoordField;

public:

	MultiTextureCoordinateNode();
	virtual ~MultiTextureCoordinateNode();

	////////////////////////////////////////////////
	//	texCoord
	////////////////////////////////////////////////
	
	MFNode *getTexCoordField() const;

	void addTexCoord(Node *value);
	int getNTexCoords() const;
	Node *getTexCoord(int index) const;

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

	MultiTextureCoordinateNode *next() const;
	MultiTextureCoordinateNode *nextTraversal() const;
};

}

#endif
