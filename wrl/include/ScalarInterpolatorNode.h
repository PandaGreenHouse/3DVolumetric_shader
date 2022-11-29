/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ScalarInterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_SCALARINTERPOLATOR_H_
#define _MYVRML_SCALARINTERPOLATOR_H_

#include <InterpolatorNode.h>

namespace MyVrml {

class ScalarInterpolatorNode : public InterpolatorNode {

	MFFloat *keyValueField;
	SFFloat *valueField;

public:

	ScalarInterpolatorNode();
	virtual ~ScalarInterpolatorNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFFloat *getKeyValueField() const;

	void addKeyValue(float value);
	int getNKeyValues() const;
	float getKeyValue(int index) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFFloat *getValueField() const;

	void setValue(float vector);
	float getValue() const;

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

	ScalarInterpolatorNode *next() const;
	ScalarInterpolatorNode *nextTraversal() const;
};

}

#endif
