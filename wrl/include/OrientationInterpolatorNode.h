/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	OrientationInterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_ORIENTATIONINTERPOLATOR_H_
#define _MYVRML_ORIENTATIONINTERPOLATOR_H_

#include <InterpolatorNode.h>

namespace MyVrml {

class OrientationInterpolatorNode : public InterpolatorNode {

	MFRotation *keyValueField;
	SFRotation *valueField;

public:

	OrientationInterpolatorNode();
	virtual ~OrientationInterpolatorNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFRotation *getKeyValueField() const;

	void addKeyValue(float rotation[]);
	int getNKeyValues() const;
	void getKeyValue(int index, float rotation[]) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFRotation *getValueField() const;

	void setValue(float rotation[]);
	void getValue(float rotation[]) const;

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

	void outputContext(std::ostream& printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	OrientationInterpolatorNode *next() const;
	OrientationInterpolatorNode *nextTraversal() const;
};

}

#endif

