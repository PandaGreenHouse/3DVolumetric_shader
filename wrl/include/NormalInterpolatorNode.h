/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NormalInterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_NORMALINTERPOLATOR_H_
#define _MYVRML_NORMALINTERPOLATOR_H_

#include <InterpolatorNode.h>

namespace MyVrml {

class NormalInterpolatorNode : public InterpolatorNode {

	MFVec3f *keyValueField;
	SFVec3f *valueField;

public:

	NormalInterpolatorNode();
	virtual ~NormalInterpolatorNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFVec3f *getKeyValueField() const;

	void addKeyValue(float vector[]);
	int getNKeyValues() const;
	void getKeyValue(int index, float vector[]) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFVec3f *getValueField() const;

	void setValue(float vector[]);
	void getValue(float vector[]) const;

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

	NormalInterpolatorNode *next() const;
	NormalInterpolatorNode *nextTraversal() const;

};

}

#endif

