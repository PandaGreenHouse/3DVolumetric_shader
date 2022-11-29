/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ComposedGeometryNode.h
*
******************************************************************/

#ifndef _MYVRML_COMPOSEDGEOMETRYNODE_H_
#define _MYVRML_COMPOSEDGEOMETRYNODE_H_

#include <Geometry3DNode.h>
#include <NormalNode.h>
#include <ColorNode.h>
#include <CoordinateNode.h>
#include <TextureCoordinateNode.h>

namespace MyVrml {

class ComposedGeometryNode : public Geometry3DNode 
{
	SFBool *ccwField;
	SFBool *colorPerVertexField;
	SFBool *normalPerVertexField;
	SFBool *solidField;

	SFNode *colorField;
	SFNode *coordField;
	SFNode *normalField;
	SFNode *texCoordField;
	
public:

	ComposedGeometryNode();
	virtual ~ComposedGeometryNode();

	////////////////////////////////////////////////
	//	Color
	////////////////////////////////////////////////

	SFNode *getColorField() const;
	
	////////////////////////////////////////////////
	//	Coord
	////////////////////////////////////////////////

	SFNode *getCoordField() const;

	////////////////////////////////////////////////
	//	Normal
	////////////////////////////////////////////////

	SFNode *getNormalField() const;
	
	////////////////////////////////////////////////
	//	texCoord
	////////////////////////////////////////////////

	SFNode *getTexCoordField() const;
	
	////////////////////////////////////////////////
	//	CCW
	////////////////////////////////////////////////

	SFBool *getCCWField() const;
	
	void setCCW(bool value);
	void setCCW(int value);
	bool getCCW() const;

	////////////////////////////////////////////////
	//	ColorPerVertex
	////////////////////////////////////////////////

	SFBool *getColorPerVertexField() const;
	
	void setColorPerVertex(bool value);
	void setColorPerVertex(int value);
	bool getColorPerVertex() const;

	////////////////////////////////////////////////
	//	NormalPerVertex
	////////////////////////////////////////////////
	
	SFBool *getNormalPerVertexField() const;

	void setNormalPerVertex(bool value);
	void setNormalPerVertex(int value);
	bool getNormalPerVertex() const;

	////////////////////////////////////////////////
	//	Solid
	////////////////////////////////////////////////

	SFBool *getSolidField() const;
	
	void setSolid(bool value);
	void setSolid(int value);
	bool getSolid() const;

	////////////////////////////////////////////////
	//	BoundingBox
	////////////////////////////////////////////////

	void recomputeBoundingBox();
};

}

#endif

