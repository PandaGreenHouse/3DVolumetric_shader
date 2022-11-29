/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	CollisionNode.h
*
******************************************************************/

#ifndef _MYVRML_COLLISIONNODE_H_
#define _MYVRML_COLLISIONNODE_H_

#include <BoundedGroupingNode.h>

namespace MyVrml {

class CollisionNode : public BoundedGroupingNode {

	SFBool *collideField;
	SFTime *collideTimeField;

public:

	CollisionNode();
	virtual ~CollisionNode();

	////////////////////////////////////////////////
	//	collide
	////////////////////////////////////////////////

	SFBool *getCollideField() const;

	void setCollide(bool  value);
	void setCollide(int value);
	bool getCollide() const;

	////////////////////////////////////////////////
	//	collideTime
	////////////////////////////////////////////////

	SFTime *getCollideTimeField() const;

	void setCollideTime(double value);
	double getCollideTime() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	CollisionNode *next() const;
	CollisionNode *nextTraversal() const;

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

