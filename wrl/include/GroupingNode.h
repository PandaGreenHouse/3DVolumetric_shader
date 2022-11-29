/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GroupingNode.h
*
******************************************************************/

#ifndef _MYVRML_GROUPINGNODE_H_
#define _MYVRML_GROUPINGNODE_H_

#include <Node.h>

namespace MyVrml {

class GroupingNode : public Node {

public:

	GroupingNode();
	virtual ~GroupingNode();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	GroupingNode *next() const;
	GroupingNode *nextTraversal() const;
};

}

#endif

