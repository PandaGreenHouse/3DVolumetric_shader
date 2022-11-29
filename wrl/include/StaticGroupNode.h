/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	StaticGroupNode.h
*
******************************************************************/

#ifndef _MYVRML_STATICGROUPNODE_H_
#define _MYVRML_STATICGROUPNODE_H_

#include <BoundedGroupingNode.h>

namespace MyVrml {

class StaticGroupNode : public BoundedGroupingNode 
{

public:

	StaticGroupNode();
	virtual ~StaticGroupNode();

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

	StaticGroupNode *next() const;
	StaticGroupNode *nextTraversal() const;

};

}

#endif
