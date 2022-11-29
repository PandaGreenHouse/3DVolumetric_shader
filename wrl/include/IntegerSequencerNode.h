/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	IntegerSequencer.h
*
******************************************************************/

#ifndef _MYVRML_INTEGERSEQUENCERNODE_H_
#define _MYVRML_INTEGERSEQUENCERNODE_H_

#include <SequencerNode.h>
#include <X3DFields.h>

namespace MyVrml {

class IntegerSequencerNode : public SequencerNode {

	MFInt32 *keyValueField;
	SFInt32 *valueField;

public:

	IntegerSequencerNode();
	virtual ~IntegerSequencerNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFInt32 *getKeyValueField() const;

	void addKeyValue(int value);
	int getNKeyValues() const;
	int getKeyValue(int index) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFInt32 *getValueField() const;

	void setValue(int vector);
	int getValue() const;

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

	IntegerSequencerNode *next() const;
	IntegerSequencerNode *nextTraversal() const;
};

}

#endif
