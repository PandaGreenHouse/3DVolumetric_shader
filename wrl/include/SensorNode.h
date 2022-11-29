/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SensorNode.h
*
******************************************************************/

#ifndef _MYVRML_SENSORNODE_H_
#define _MYVRML_SENSORNODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

class SensorNode : public Node {
	
	SFBool *enabledField;
	SFBool *isActiveField;

public:

	SensorNode();
	virtual ~SensorNode();

	////////////////////////////////////////////////
	//	Enabled
	////////////////////////////////////////////////

	SFBool *getEnabledField() const;
	
	void setEnabled(bool  value);
	void setEnabled(int value);
	bool  getEnabled() const;
	bool  isEnabled() const;

	////////////////////////////////////////////////
	//	isActive
	////////////////////////////////////////////////
	
	SFBool *getIsActiveField() const;

	void setIsActive(bool  value);
	void setIsActive(int value);
	bool  getIsActive() const;
	bool isActive() const;

};

}

#endif

