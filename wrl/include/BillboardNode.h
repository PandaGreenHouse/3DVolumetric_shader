/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	BillboardNode.h
*
******************************************************************/

#ifndef _MYVRML_BILLBOARDNODE_H_
#define _MYVRML_BILLBOARDNODE_H_

#include <VRML97Fields.h>
#include <BoundedGroupingNode.h>

namespace MyVrml {
	
class BillboardNode : public BoundedGroupingNode {

	SFVec3f *axisOfRotationField;

public:

	BillboardNode();
	virtual ~BillboardNode();

	////////////////////////////////////////////////
	//	axisOfRotation
	////////////////////////////////////////////////

	SFVec3f *getAxisOfRotationField() const;

	void setAxisOfRotation(float value[]);
	void setAxisOfRotation(float x, float y, float z);
	void getAxisOfRotation(float value[]) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	BillboardNode *next() const;
	BillboardNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	actions
	////////////////////////////////////////////////

	void	getBillboardToViewerVector(float vector[3]) const;
	void	getViewerToBillboardVector(float vector[3]) const;
	void	getPlaneVectorOfAxisOfRotationAndBillboardToViewer(float vector[3]) const;
	void	getZAxisVectorOnPlaneOfAxisOfRotationAndBillboardToViewer(float vector[3]) const;
	float	getRotationAngleOfZAxis() const;
	void	getRotationZAxisRotation(float rotation[4]) const;
	void	getSFMatrix(SFMatrix *mOut) const;

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
