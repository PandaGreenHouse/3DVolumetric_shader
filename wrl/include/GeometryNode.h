/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GeometryNode.h
*
******************************************************************/

#ifndef _MYVRML_GEOMETRYNODE_H_
#define _MYVRML_GEOMETRYNODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

#ifdef MYVRML_SUPPORT_OPENGL
const char displayListPrivateFieldString[] = "oglDisplayList";
#endif

class GeometryNode : public Node 
{

#ifdef MYVRML_SUPPORT_OPENGL
	SFInt32 *dispListField;
#endif

public:

	GeometryNode();
	virtual ~GeometryNode();

	////////////////////////////////////////////////
	//	DisplayList
	////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL

	SFInt32 *getDisplayListField() const;
	void setDisplayList(unsigned int n);
	unsigned int getDisplayList() const;
	virtual void draw() const;

#endif
};

}

#endif
