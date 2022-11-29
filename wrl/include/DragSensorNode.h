/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	DragSensorNode.h
*
******************************************************************/

#ifndef _MYVRML_DRAGSENSORNODE_H_
#define _MYVRML_DRAGSENSORNODE_H_

#include <PointingDeviceSensorNode.h>

namespace MyVrml {

class DragSensorNode : public PointingDeviceSensorNode
{
	SFBool *autoOffsetField;
	SFVec3f *trackPointField;

public:

	DragSensorNode();
	virtual ~DragSensorNode();

	////////////////////////////////////////////////
	//	AutoOffset
	////////////////////////////////////////////////

	SFBool *getAutoOffsetField() const;
	
	void setAutoOffset(bool  value);
	void setAutoOffset(int value);
	bool  getAutoOffset() const;
	bool  isAutoOffset() const;

	////////////////////////////////////////////////
	//	TrackPoint
	////////////////////////////////////////////////

	SFVec3f *getTrackPointChangedField() const;
	
	void setTrackPointChanged(float value[]);
	void setTrackPointChanged(float x, float y, float z);
	void getTrackPointChanged(float value[]) const;

};

}

#endif

