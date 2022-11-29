/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	DirectionalLightNode.h
*
******************************************************************/

#ifndef _MYVRML_DIRECTIONALLIGHTNODE_H_
#define _MYVRML_DIRECTIONALLIGHTNODE_H_

#include <VRML97Fields.h>
#include <LightNode.h>

namespace MyVrml {

class DirectionalLightNode : public LightNode {

	SFVec3f *directionField;
	
public:

	DirectionalLightNode();
	virtual ~DirectionalLightNode();

	////////////////////////////////////////////////
	//	Direction
	////////////////////////////////////////////////

	SFVec3f *getDirectionField() const;

	void setDirection(float value[]);
	void setDirection(float x, float y, float z);
	void getDirection(float value[]) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	DirectionalLightNode *next() const;
	DirectionalLightNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

