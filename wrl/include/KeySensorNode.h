/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	KeySensorNode.h
*
******************************************************************/

#ifndef _MYVRML_KEYSENSORNODE_H_
#define _MYVRML_KEYSENSORNODE_H_

#include <KeyDeviceSensorNode.h>

namespace MyVrml {

class KeySensorNode : public KeyDeviceSensorNode 
{

public:

	KeySensorNode();
	virtual ~KeySensorNode();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	KeySensorNode *next() const;
	KeySensorNode *nextTraversal() const;

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

