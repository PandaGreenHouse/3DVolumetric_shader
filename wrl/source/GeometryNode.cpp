/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	GeometryNode.cpp
*
******************************************************************/

#include <GeometryNode.h>
#include <Graphic3D.h>

using namespace MyVrml;

GeometryNode::GeometryNode() 
{
#ifdef MYVRML_SUPPORT_OPENGL
	// display list field
	dispListField = new SFInt32(0);
	dispListField->setName(displayListPrivateFieldString);
	addPrivateField(dispListField);

	setDisplayList(0);
#endif
}

GeometryNode::~GeometryNode() 
{
}

////////////////////////////////////////////////
//	OpenGL
////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL

SFInt32 *GeometryNode::getDisplayListField() const
{
	if (isInstanceNode() == false)
		return dispListField;
	return (SFInt32 *)getPrivateField(displayListPrivateFieldString);
}

void GeometryNode::setDisplayList(unsigned int n) 
{
	getDisplayListField()->setValue((int)n);
}

unsigned int GeometryNode::getDisplayList() const
{
	return (unsigned int)getDisplayListField()->getValue();
} 

void GeometryNode::draw() const
{
	unsigned int nDisplayList = getDisplayList();
	if (0 < nDisplayList)
		glCallList(nDisplayList);
}

#endif
