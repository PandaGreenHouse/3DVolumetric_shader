/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	CoordinateInterpolator2DNode.h
*
******************************************************************/

#ifndef _MYVRML_COORDINATEINTERPOLATOR2D_H_
#define _MYVRML_COORDINATEINTERPOLATOR2D_H_

#include <X3DFields.h>
#include <InterpolatorNode.h>

namespace MyVrml {

class CoordinateInterpolator2DNode : public InterpolatorNode {

	MFVec2f *keyValueField;
	SFVec2f *valueField;

public:

	CoordinateInterpolator2DNode();
	virtual ~CoordinateInterpolator2DNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFVec2f *getKeyValueField() const;

	void addKeyValue(float vector[]);
	int getNKeyValues() const;
	void getKeyValue(int index, float vector[]) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFVec2f *getValueField() const;

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

	CoordinateInterpolator2DNode *next() const;
	CoordinateInterpolator2DNode *nextTraversal() const;
};

}

#endif

