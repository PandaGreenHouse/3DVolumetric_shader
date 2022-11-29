/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GroupNode.h
*
*	06/06/03
*		- The first release
*
******************************************************************/

#ifndef _MYVRML_SCENENODE_H_
#define _MYVRML_SCENENODE_H_

#include <Node.h>

namespace MyVrml {

class SceneNode : public Node {

public:

	SceneNode();
	virtual ~SceneNode();

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	SceneNode *next() const;
	SceneNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
