/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	RouteNode.h
*
******************************************************************/

#ifndef _MYVRML_ROOTNODE_H_
#define _MYVRML_ROOTNODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

class RootNode : public Node {

public:

	RootNode();
	virtual ~RootNode();

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream& printStream, const char * indentString) const;
};

}

#endif
