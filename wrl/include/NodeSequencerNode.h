/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NodeSequencer.h
*
******************************************************************/

#ifndef _MYVRML_NODESEQUENCERNODE_H_
#define _MYVRML_NODESEQUENCERNODE_H_

#include <X3DFields.h>
#include <SequencerNode.h>

namespace MyVrml {

class NodeSequencerNode : public SequencerNode {

	MFNode *keyValueField;
	SFNode *valueField;

public:

	NodeSequencerNode();
	virtual ~NodeSequencerNode();

	////////////////////////////////////////////////
	//	keyValue
	////////////////////////////////////////////////
	
	MFNode *getKeyValueField() const;

	void addKeyValue(Node *value);
	int getNKeyValues() const;
	Node *getKeyValue(int index) const;

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////
	
	SFNode *getValueField() const;

	void setValue(Node *value);
	Node *getValue() const;

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

	NodeSequencerNode *next() const;
	NodeSequencerNode *nextTraversal() const;
};

}

#endif
