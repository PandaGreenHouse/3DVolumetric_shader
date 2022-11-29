/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ParserNode.h
*
******************************************************************/

#ifndef _MYVRML_PARSERNODE_H_
#define _MYVRML_PARSERNODE_H_

#include <LinkedList.h>
#include <Node.h>

namespace MyVrml {

class ParserNode : public LinkedListNode<ParserNode> {
	Node		*mNode;
	int			mType;
public:

	ParserNode(Node *node, int type);
	virtual ~ParserNode();
	
	Node *getNode() const; 
	int getType() const;
};

}

#endif

