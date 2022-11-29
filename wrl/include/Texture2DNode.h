/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Texture2DNode.h
*
******************************************************************/

#ifndef _MYVRML_TEXTURE2DNODE_H_
#define _MYVRML_TEXTURE2DNODE_H_

#include <VRML97Fields.h>
#include <TextureNode.h>
#include <FileImage.h>

#ifdef MYVRML_SUPPORT_OPENGL
const char textureNamePrivateFieldString[] = "oglTextureName";
const char hasTransparencyColorPrivateFieldString[] = "hasTransparencyColor";
#endif

namespace MyVrml {

class Texture2DNode : public TextureNode
{
	SFBool *repeatSField;
	SFBool *repeatTField;

	SFInt32 *texNameField;
	SFBool *hasTransColorField;

public:

	Texture2DNode();
	virtual ~Texture2DNode();

	////////////////////////////////////////////////
	//	RepeatS
	////////////////////////////////////////////////
	
	SFBool *getRepeatSField() const;

	void setRepeatS(bool value);
	void setRepeatS(int value);
	bool getRepeatS() const;

	////////////////////////////////////////////////
	//	RepeatT
	////////////////////////////////////////////////
	
	SFBool *getRepeatTField() const;

	void setRepeatT(bool value);
	void setRepeatT(int value);
	bool getRepeatT() const;

	////////////////////////////////////////////////
	//	Virtual Methods
	////////////////////////////////////////////////

	virtual int getWidth() const {
		return 0;
	}

	virtual int getHeight() const {
		return 0;
	}

	virtual RGBAColor32	*getImage() const {
		return NULL;
	}

#ifdef MYVRML_SUPPORT_OPENGL

	////////////////////////////////////////////////
	//	TextureName
	////////////////////////////////////////////////

	SFInt32 *getTextureNameField() const;

	void setTextureName(unsigned int n);
	unsigned int getTextureName() const;

	////////////////////////////////////////////////
	//	Transparency
	////////////////////////////////////////////////

	SFBool *getHasTransparencyColorField() const;

	void setHasTransparencyColor(bool value);
	bool hasTransparencyColor() const;

#endif

};

#ifdef MYVRML_SUPPORT_OPENGL
int GetOpenGLTextureSize(int size);
#endif

}

#endif

