/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	StaticGroupNode.cpp
*
*	11/20/02
*		- The first revison.
*
******************************************************************/

#include <StaticGroupNode.h>

using namespace MyVrml;

StaticGroupNode::StaticGroupNode() 
{
	setHeaderFlag(false);
	setType(STATICGROUP_NODE);
}

StaticGroupNode::~StaticGroupNode() 
{
}

////////////////////////////////////////////////
//	Output
////////////////////////////////////////////////

void StaticGroupNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool StaticGroupNode::isChildNodeType(Node *node) const
{
	if (node->isCommonNode() || node->isBindableNode() ||node->isInterpolatorNode() || node->isSensorNode() || node->isGroupingNode() || node->isSpecialGroupNode())
		return true;
	else
		return false;
}

void StaticGroupNode::initialize() 
{
	recomputeBoundingBox();
}

void StaticGroupNode::uninitialize() 
{
}

void StaticGroupNode::update() 
{
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

StaticGroupNode *StaticGroupNode::next() const
{
	return (StaticGroupNode *)Node::next(getType());
}

StaticGroupNode *StaticGroupNode::nextTraversal() const
{
	return (StaticGroupNode *)Node::nextTraversalByType(getType());
}

