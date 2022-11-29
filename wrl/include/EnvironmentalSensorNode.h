/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	EnvironmentalSensorNode.h
*
******************************************************************/

#ifndef _MYVRML_ENVIRONMENTALSENSORNODE_H_
#define _MYVRML_ENVIRONMENTALSENSORNODE_H_

#include <SensorNode.h>

namespace MyVrml {

class EnvironmentalSensorNode : public SensorNode 
{

	SFVec3f *centerField;
	SFVec3f *sizeField;
	SFTime *enterTimeField;
	SFTime *exitTimeField;

public:

	EnvironmentalSensorNode();
	virtual ~EnvironmentalSensorNode();

	////////////////////////////////////////////////
	//	Center
	////////////////////////////////////////////////
	
	SFVec3f *getCenterField() const;

	void	setCenter(float value[]);
	void	setCenter(float x, float y, float z);
	void	getCenter(float value[]) const;

	////////////////////////////////////////////////
	//	Size
	////////////////////////////////////////////////

	SFVec3f *getSizeField() const;
	
	void	setSize(float value[]);
	void	setSize(float x, float y, float z);
	void	getSize(float value[]) const;

	////////////////////////////////////////////////
	//	EnterTime
	////////////////////////////////////////////////

	SFTime *getEnterTimeField() const;
	
	void	setEnterTime(double value);
	double	getEnterTime() const;

	////////////////////////////////////////////////
	//	ExitTime
	////////////////////////////////////////////////
	
	SFTime *getExitTimeField() const;

	void	setExitTime(double value);
	double	getExitTime() const;
};

}

#endif

