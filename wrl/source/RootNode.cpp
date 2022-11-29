/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	RouteNode.cpp
*
******************************************************************/

#include <RootNode.h>

using namespace MyVrml;

RootNode::RootNode() 
{
	setHeaderFlag(true);
	setType(ROOT_NODE);
}

RootNode::~RootNode() 
{
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool RootNode::isChildNodeType(Node *node) const
{
	if (node->isCommonNode() || node->isBindableNode() ||node->isInterpolatorNode() || node->isSensorNode() || node->isGroupingNode() || node->isSpecialGroupNode())
		return true;
	else
		return false;
}

void RootNode::initialize() 
{
}

void RootNode::uninitialize() 
{
}

void RootNode::update() 
{
}

////////////////////////////////////////////////
//	infomation
////////////////////////////////////////////////

void RootNode::outputContext(std::ostream& printStream, const char * indentString) const
{
}
