/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	LODNode.h
*
******************************************************************/

#ifndef _MYVRML_LODNODE_H_
#define _MYVRML_LODNODE_H_

#include <VRML97Fields.h>
#include <BoundedGroupingNode.h>

namespace MyVrml {

class LODNode : public BoundedGroupingNode {

	SFVec3f *centerField;
	MFFloat *rangeField;

public:

	LODNode();
	virtual ~LODNode();
	
	////////////////////////////////////////////////
	//	center
	////////////////////////////////////////////////

	SFVec3f *getCenterField() const;

	void setCenter(float value[]);
	void setCenter(float x, float y, float z);
	void getCenter(float value[]) const;

	////////////////////////////////////////////////
	//	range 
	////////////////////////////////////////////////

	MFFloat *getRangeField() const;

	void addRange(float value);
	int getNRanges() const;
	float getRange(int index) const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	LODNode *next() const;
	LODNode *nextTraversal() const;

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

void UpdateLod(LODNode *lod);
void InitializeLod(LODNode *lod);
void UninitializeLod(LODNode *lod);

}

#endif

