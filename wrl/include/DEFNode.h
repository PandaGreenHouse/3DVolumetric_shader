/******************************************************************
*
*	VRML library for C++
*
*	
*
*	File:	DEFNode.h
*
******************************************************************/

#ifndef _DEFNODE_H_
#define _DEFNODE_H_

#include <Node.h>

namespace MyVrml {

class DEFNode : public Node {

public:

	DEFNode();
	virtual ~DEFNode();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	DEFNode *next() const;
	DEFNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

