/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	VisibilitySensorNode.h
*
******************************************************************/

#ifndef _MYVRML_VISIBILITYSENSORNODE_H_
#define _MYVRML_VISIBILITYSENSORNODE_H_

#include <EnvironmentalSensorNode.h>

namespace MyVrml {

class VisibilitySensorNode : public EnvironmentalSensorNode 
{

public:

	VisibilitySensorNode();
	virtual ~VisibilitySensorNode();

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	VisibilitySensorNode *next() const;
	VisibilitySensorNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool	isChildNodeType(Node *node) const;
	void	initialize();
	void	uninitialize();
	void	update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void	outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

