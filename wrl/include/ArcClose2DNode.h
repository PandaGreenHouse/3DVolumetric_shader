/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ArcClose2DNode.h
*
******************************************************************/

#ifndef _MYVRML_ARCCLOSE2DNODE_H_
#define _MYVRML_ARCCLOSE2DNODE_H_

#include <Arc2DNode.h>

namespace MyVrml {

class ArcClose2DNode : public Arc2DNode {

	SFString *closureTypeField;

public:

	ArcClose2DNode();
	virtual ~ArcClose2DNode();

	////////////////////////////////////////////////
	//	ClosureType
	////////////////////////////////////////////////

	SFString *getClosureTypeField() const;
	
	void setClosureType(const char *value);
	const char *getClosureType() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	ArcClose2DNode *next() const;
	ArcClose2DNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	recomputeDisplayList
	////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL
	void recomputeDisplayList();
#endif

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
