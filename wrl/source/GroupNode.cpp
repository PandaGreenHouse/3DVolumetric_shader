/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GroupNode.cpp
*
*	11/19/02
*		- Changed the super class from GroupingNode to BoundedGroupingNode.
*
******************************************************************/

#include <GroupNode.h>

using namespace MyVrml;

GroupNode::GroupNode() 
{
	setHeaderFlag(false);
	setType(GROUP_NODE);
}

GroupNode::~GroupNode() 
{
}

////////////////////////////////////////////////
//	Output
////////////////////////////////////////////////

void GroupNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool GroupNode::isChildNodeType(Node *node) const
{
	if (node->isCommonNode() || node->isBindableNode() ||node->isInterpolatorNode() || node->isSensorNode() || node->isGroupingNode() || node->isSpecialGroupNode())
		return true;
	else
		return false;
}

void GroupNode::initialize() 
{
	recomputeBoundingBox();
}

void GroupNode::uninitialize() 
{
}

void GroupNode::update() 
{
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

GroupNode *GroupNode::next() const
{
	return (GroupNode *)Node::next(getType());
}

GroupNode *GroupNode::nextTraversal() const
{
	return (GroupNode *)Node::nextTraversalByType(getType());
}

