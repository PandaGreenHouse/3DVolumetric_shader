/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	PositionInterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_POSITIONINTERPOLATOR_H_
#define _MYVRML_POSITIONINTERPOLATOR_H_

#include <InterpolatorNode.h>

namespace MyVrml {

class PositionInterpolatorNode : public InterpolatorNode {

	MFVec3f *keyValueField;
	SFVec3f *valueField;

public:

	PositionInterpolatorNode();
	virtual ~PositionInterpolatorNode();

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
	//	Virtual functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	PositionInterpolatorNode *next() const;
	PositionInterpolatorNode *nextTraversal() const;
};

}

#endif

