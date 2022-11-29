/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	AppearanceNode.h
*
******************************************************************/

#ifndef _MYVRML_APPEARANCENODE_H_
#define _MYVRML_APPEARANCENODE_H_

#include <VRML97Fields.h>
#include <Node.h>
#include <MaterialNode.h>
#include <TextureTransformNode.h>

namespace MyVrml {

class AppearanceNode : public Node {

	SFNode *materialField;
	SFNode *textureField;
	SFNode *texTransformField;
	SFNode *linePropertiesField;
	SFNode *fillPropertiesField;

public:

	AppearanceNode();
	virtual ~AppearanceNode();

	////////////////////////////////////////////////
	//	SFNode Field
	////////////////////////////////////////////////

	SFNode *getMaterialField() const;
	SFNode *getTextureField() const ;
	SFNode *getTextureTransformField() const;
	SFNode *getLinePropertiesField() const;
	SFNode *getFillPropertiesField() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	AppearanceNode *next() const;
	AppearanceNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	virtual functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();
	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
