/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	MultiTextureTransformNode.h
*
******************************************************************/

#ifndef _MYVRML_MULTITEXTURETRANSFORMNODE_H_
#define _MYVRML_MULTITEXTURETRANSFORMNODE_H_

#include <X3DFields.h>
#include <Node.h>

namespace MyVrml {

class MultiTextureTransformNode : public Node
{
	MFNode *textureTransformField;

public:

	MultiTextureTransformNode();
	virtual ~MultiTextureTransformNode();

	////////////////////////////////////////////////
	//	textureTransform
	////////////////////////////////////////////////
	
	MFNode *getTextureTransformField() const;

	void addTextureTransform(Node *value);
	int getNTextureTransforms() const;
	Node *getTextureTransform(int index) const;

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

	MultiTextureTransformNode *next() const;
	MultiTextureTransformNode *nextTraversal() const;
};

}

#endif
