/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SoundNode.h
*
******************************************************************/

#ifndef _MYVRML_SOUNDNODE_H_
#define _MYVRML_SOUNDNODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

class SoundNode : public Node {

	SFFloat *minFrontField;
	SFFloat *maxFrontField;
	SFFloat *minBackField;
	SFFloat *maxBackField;
	SFFloat *intensityField;
	SFFloat *priorityField;
	SFVec3f *directionField;
	SFVec3f *locationField;
	SFBool *spatializeField;
	SFNode *sourceField;
	
public:

	SoundNode();
	virtual ~SoundNode();

	////////////////////////////////////////////////
	//	Source
	////////////////////////////////////////////////

	SFNode *getSourceField() const;

	////////////////////////////////////////////////
	//	Direction
	////////////////////////////////////////////////

	SFVec3f *getDirectionField() const;

	void setDirection(float value[]);
	void setDirection(float x, float y, float z);
	void getDirection(float value[]) const;

	////////////////////////////////////////////////
	//	Location
	////////////////////////////////////////////////

	SFVec3f *getLocationField() const;

	void setLocation(float value[]);
	void setLocation(float x, float y, float z);
	void getLocation(float value[]) const;

	////////////////////////////////////////////////
	//	MinFront
	////////////////////////////////////////////////

	SFFloat *getMinFrontField() const;
	
	void setMinFront(float value);
	float getMinFront() const;

	////////////////////////////////////////////////
	//	MaxFront
	////////////////////////////////////////////////

	SFFloat *getMaxFrontField() const;
	
	void setMaxFront(float value);
	float getMaxFront() const;

	////////////////////////////////////////////////
	//	MinBack
	////////////////////////////////////////////////

	SFFloat *getMinBackField() const;
	
	void setMinBack(float value);
	float getMinBack() const;

	////////////////////////////////////////////////
	//	MaxBack
	////////////////////////////////////////////////

	SFFloat *getMaxBackField() const;
	
	void setMaxBack(float value);
	float getMaxBack() const;

	////////////////////////////////////////////////
	//	Intensity
	////////////////////////////////////////////////

	SFFloat *getIntensityField() const;
	
	void setIntensity(float value);
	float getIntensity() const;

	////////////////////////////////////////////////
	//	Priority
	////////////////////////////////////////////////

	SFFloat *getPriorityField() const;
	
	void setPriority(float value);
	float getPriority() const;

	////////////////////////////////////////////////
	//	Spatialize
	////////////////////////////////////////////////

	SFBool *getSpatializeField() const;
	
	void setSpatialize(bool value);
	void setSpatialize(int value);
	bool getSpatialize() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	SoundNode *next() const;
	SoundNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

