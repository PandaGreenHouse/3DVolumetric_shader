/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	InterpolatorNode.h
*
******************************************************************/

#ifndef _MYVRML_INTERPOLATOR_H_
#define _MYVRML_INTERPOLATOR_H_

#include <Node.h>

namespace MyVrml {

class InterpolatorNode : public Node {

	MFFloat *keyField;
	SFFloat *fractionField;

public:

	InterpolatorNode();
	virtual ~InterpolatorNode();

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
