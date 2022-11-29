/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ParserNode.cpp
*
******************************************************************/

#include <ParserNode.h>

using namespace MyVrml;

ParserNode::ParserNode(Node *node, int type) 
{ 
	setHeaderFlag(false); 
	mNode = node; 
	mType = type;
}

ParserNode::~ParserNode() 
{ 
	remove();
}
	
Node *ParserNode::getNode() const
{ 
	return mNode; 
}
	
int ParserNode::getType() const
{ 
	return mType; 
}
