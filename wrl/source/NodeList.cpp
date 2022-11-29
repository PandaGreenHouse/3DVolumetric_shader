/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NodeList.cpp
*
******************************************************************/

#include <NodeList.h>

using namespace MyVrml;

NodeList::NodeList() 
{
	RootNode *rootNode = new RootNode();
	setRootNode(rootNode);
}

NodeList::~NodeList() 
{
}
