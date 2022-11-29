/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	AnchorNode.h
*
******************************************************************/

#ifndef _MYVRML_ANCHORNODE_H_
#define _MYVRML_ANCHORNODE_H_

#include <VRML97Fields.h>
#include <BoundedGroupingNode.h>

namespace MyVrml {

class AnchorNode : public BoundedGroupingNode {

	SFString *descriptionField;
	MFString *parameterField;
	MFString *urlField;

	SFBool *enabledField;
	SFVec3f *centerField;

public:

	AnchorNode();
	virtual ~AnchorNode(); 

	////////////////////////////////////////////////
	//	Description
	////////////////////////////////////////////////

	SFString *getDescriptionField() const;

	void	setDescription(const char *value);
	const char *getDescription() const;

	////////////////////////////////////////////////
	// Parameter
	////////////////////////////////////////////////

	MFString *getParameterField() const;

	void	addParameter(const char *value);
	int		getNParameters() const;
	const char *getParameter(int index) const;

	////////////////////////////////////////////////
	// Url
	////////////////////////////////////////////////

	MFString *getUrlField() const;

	void	addUrl(const char *value);
	int		getNUrls() const;
	const char *getUrl(int index) const;
	void	setUrl(int index, const char *urlString);

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	AnchorNode	*next() const;
	AnchorNode	*nextTraversal() const;

	////////////////////////////////////////////////
	//	Center (X3D)
	////////////////////////////////////////////////

	SFVec3f *getCenterField() const ;

	void setCenter(float value[]);
	void setCenter(float x, float y, float z);
	void setCenter(String value);
	void getCenter(float value[]) const;
	
	////////////////////////////////////////////////
	//	Enabled (X3D)
	////////////////////////////////////////////////

	SFBool *getEnabledField() const;

	void setEnabled(bool value);
	bool getEnabled() const;
	bool isEnabled() const;

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
