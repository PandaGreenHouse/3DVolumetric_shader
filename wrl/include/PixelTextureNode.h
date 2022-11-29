/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	PixelTextureNode.h
*
******************************************************************/

#ifndef _MYVRML_PIXELTEXTURENODE_H_
#define _MYVRML_PIXELTEXTURENODE_H_

#include <VRML97Fields.h>
#include <Texture2DNode.h>

namespace MyVrml {

class PixelTextureNode : public Texture2DNode {

	SFImage *imageField;
	
public:

	PixelTextureNode();
	virtual ~PixelTextureNode();

	////////////////////////////////////////////////
	// Image
	////////////////////////////////////////////////

	SFImage *getImageField() const;

	void addImage(int value);
	int getNImages() const;
	int getImage(int index) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	PixelTextureNode *next() const;
	PixelTextureNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Imagemation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

