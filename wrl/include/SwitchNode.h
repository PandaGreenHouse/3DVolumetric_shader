/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SwitchNode.h
*
******************************************************************/

#ifndef _MYVRML_SWITCHNODE_H_
#define _MYVRML_SWITCHNODE_H_

#include <VRML97Fields.h>
#include <BoundedGroupingNode.h>

namespace MyVrml {

class SwitchNode : public BoundedGroupingNode {

	SFInt32 *whichChoiceField;

public:

	SwitchNode();
	virtual ~SwitchNode();

	////////////////////////////////////////////////
	//	whichChoice
	////////////////////////////////////////////////

	SFInt32 *getWhichChoiceField() const;

	void setWhichChoice(int value);
	int getWhichChoice() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	SwitchNode *next() const;
	SwitchNode *nextTraversal() const;

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

