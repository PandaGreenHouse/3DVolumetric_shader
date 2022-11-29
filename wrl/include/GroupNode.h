/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GroupNode.h
*
******************************************************************/

#ifndef _MYVRML_GROUPNODE_H_
#define _MYVRML_GROUPNODE_H_

#include <BoundedGroupingNode.h>

namespace MyVrml {

class GroupNode : public BoundedGroupingNode {

public:

	GroupNode();
	virtual ~GroupNode();

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	GroupNode *next() const;
	GroupNode *nextTraversal() const;

};

}

#endif
