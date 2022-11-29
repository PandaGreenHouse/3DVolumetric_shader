/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NormalNode.h
*
******************************************************************/

#ifndef _MYVRML_NORMALNODE_H_
#define _MYVRML_NORMALNODE_H_

#include <VRML97Fields.h>
#include <GeometricPropertyNode.h>

namespace MyVrml {

class NormalNode : public GeometricPropertyNode
{

	MFVec3f *vectorField;

public:

	NormalNode();
	virtual ~NormalNode();

	////////////////////////////////////////////////
	//	vector
	////////////////////////////////////////////////
	
	MFVec3f *getVectorField() const;

	void addVector(float value[]);
	int getNVectors() const;
	void getVector(int index, float value[]) const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	NormalNode *next() const;
	NormalNode *nextTraversal() const;
};

}

#endif

