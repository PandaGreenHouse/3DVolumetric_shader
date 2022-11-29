/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	TextureCoordinateGeneratorNode.h
*
******************************************************************/

#ifndef _MYVRML_TEXCOORDGENNODE_H_
#define _MYVRML_TEXCOORDGENNODE_H_

#include <Node.h>

namespace MyVrml {

class TextureCoordinateGeneratorNode : public Node 
{
	MFFloat *parameterField;
	SFString *modeField;

public:

	TextureCoordinateGeneratorNode();
	virtual ~TextureCoordinateGeneratorNode();

	////////////////////////////////////////////////
	//	parameter
	////////////////////////////////////////////////

	MFFloat *getParameterField() const;
	
	void addParameter(float value);
	int getNParameters() const;
	float getParameter(int index) const;

	////////////////////////////////////////////////
	//	mode
	////////////////////////////////////////////////
	
	SFString *getModeField() const;

	void setMode(const char *value);
	const char *getMode() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	TextureCoordinateGeneratorNode	*next() const;
	TextureCoordinateGeneratorNode	*nextTraversal() const;

	////////////////////////////////////////////////
	//	virtual functions
	////////////////////////////////////////////////

	bool	isChildNodeType(Node *node) const;
	void	initialize();
	void	uninitialize();
	void	update();
	void	outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
