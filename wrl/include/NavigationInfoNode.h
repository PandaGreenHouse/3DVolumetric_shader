/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NavigationInfoNode.h
*
******************************************************************/

#ifndef _MYVRML_NAVIGATIONINFO_H_
#define _MYVRML_NAVIGATIONINFO_H_

#include <BindableNode.h>

namespace MyVrml {

class NavigationInfoNode : public BindableNode {

	SFFloat *visibilityLimitField;
	MFFloat *avatarSizeField;
	MFString *typeField;
	SFBool *headlightField;
	SFFloat *speedField;
	
public:

	NavigationInfoNode();
	virtual ~NavigationInfoNode();

	////////////////////////////////////////////////
	// Type
	////////////////////////////////////////////////

	MFString *getTypeField() const;

	void addType(const char *value);
	int getNTypes() const;
	const char *getType(int index) const;

	////////////////////////////////////////////////
	// avatarSize
	////////////////////////////////////////////////

	MFFloat *getAvatarSizeField() const;

	void addAvatarSize(float value);
	int getNAvatarSizes() const;
	float getAvatarSize(int index) const;

	////////////////////////////////////////////////
	//	Headlight
	////////////////////////////////////////////////

	SFBool *getHeadlightField() const;
	
	void setHeadlight(bool value);
	void setHeadlight(int value);
	bool getHeadlight() const;

	////////////////////////////////////////////////
	//	VisibilityLimit
	////////////////////////////////////////////////

	SFFloat *getVisibilityLimitField() const;

	void setVisibilityLimit(float value);
	float getVisibilityLimit() const;

	////////////////////////////////////////////////
	//	Speed
	////////////////////////////////////////////////
	
	SFFloat *getSpeedField() const;

	void setSpeed(float value);
	float getSpeed() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	bool isChildNodeType(Node *node) const;
	NavigationInfoNode *next() const;
	NavigationInfoNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

