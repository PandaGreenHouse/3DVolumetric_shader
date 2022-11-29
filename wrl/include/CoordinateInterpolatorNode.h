/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	CoordinateInterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_COORDINATEINTERPOLATOR_H_
#define _MYVRML_COORDINATEINTERPOLATOR_H_

#include <InterpolatorNode.h>

namespace MyVrml {

class CoordinateInterpolatorNode : public InterpolatorNode {

	MFVec3f *keyValueField;
	SFVec3f *valueField;

public:

	CoordinateInterpolatorNode();
	virtual ~CoordinateInterpolatorNode();

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

	CoordinateInterpolatorNode *next() const;
	CoordinateInterpolatorNode *nextTraversal() const;
};

}

#endif

