/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	KeySensorNode.cpp
*
******************************************************************/

#include <KeySensorNode.h>

using namespace MyVrml;

KeySensorNode::KeySensorNode() 
{
	setHeaderFlag(false);
	setType(KEYSENSOR_NODE);
}

KeySensorNode::~KeySensorNode() 
{
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

KeySensorNode *KeySensorNode::next() const
{
	return (KeySensorNode *)Node::next(getType());
}

KeySensorNode *KeySensorNode::nextTraversal() const
{
	return (KeySensorNode *)Node::nextTraversalByType(getType());
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool KeySensorNode::isChildNodeType(Node *node) const
{
	return false;
}

void KeySensorNode::initialize() 
{
}

void KeySensorNode::uninitialize() 
{
}

void KeySensorNode::update() 
{
}

////////////////////////////////////////////////
//	Infomation
////////////////////////////////////////////////

void KeySensorNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}
