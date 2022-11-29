/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	DEFNode.cpp
*
******************************************************************/

#include <DEFNode.h>

using namespace MyVrml;

DEFNode::DEFNode() 
{
	setHeaderFlag(false);
	setType(DEF_NODE);
}

DEFNode::~DEFNode() 
{
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

DEFNode *DEFNode::next() const 
{
	return (DEFNode *)Node::next(getType());
}

DEFNode *DEFNode::nextTraversal() const 
{
	return (DEFNode *)Node::nextTraversalByType(getType());
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool DEFNode::isChildNodeType(Node *node) const
{
	return false;
}

void DEFNode::initialize()
{
}

void DEFNode::uninitialize()
{
}

void DEFNode::update() 
{
}

void DEFNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}

