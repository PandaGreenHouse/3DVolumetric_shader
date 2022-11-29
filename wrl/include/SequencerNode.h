/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SequencerNode.h
*
******************************************************************/

#ifndef _MYVRML_SEQUENCERNODE_H_
#define _MYVRML_SEQUENCERNODE_H_

#include <Node.h>

namespace MyVrml {

class SequencerNode : public Node {

	MFFloat *keyField;
	SFFloat *fractionField;

public:

	SequencerNode();
	virtual ~SequencerNode();

	////////////////////////////////////////////////
	//	key
	////////////////////////////////////////////////

	MFFloat *getKeyField() const;
	
	void addKey(float value);
	int getNKeys() const;
	float getKey(int index) const;

	////////////////////////////////////////////////
	//	fraction
	////////////////////////////////////////////////
	
	SFFloat *getFractionField() const;

	void setFraction(float value);
	float getFraction() const;
};

}

#endif
