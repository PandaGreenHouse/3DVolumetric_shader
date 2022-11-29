/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	IndexedFaceSetNode.h
*
******************************************************************/

#ifndef _MYVRML_INDEXEDFACESETNODE_H_
#define _MYVRML_INDEXEDFACESETNODE_H_

#include <ComposedGeometryNode.h>
#include <NormalNode.h>
#include <ColorNode.h>
#include <CoordinateNode.h>
#include <TextureCoordinateNode.h>

namespace MyVrml {

class IndexedFaceSetNode : public ComposedGeometryNode 
{
	SFBool *convexField;
	SFFloat *creaseAngleField;
	MFInt32 *coordIdxField;
	MFInt32 *texCoordIndexField;
	MFInt32 *colorIndexField;
	MFInt32 *normalIndexField;
	
public:

	IndexedFaceSetNode();
	virtual ~IndexedFaceSetNode();
	
	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	IndexedFaceSetNode *next() const;
	IndexedFaceSetNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	Convex
	////////////////////////////////////////////////

	SFBool *getConvexField() const;
	
	void setConvex(bool value);
	void setConvex(int value);
	bool getConvex() const;

	////////////////////////////////////////////////
	//	CreaseAngle
	////////////////////////////////////////////////

	SFFloat *getCreaseAngleField() const;
	
	void setCreaseAngle(float value);
	float getCreaseAngle() const;

	////////////////////////////////////////////////
	// CoordIndex
	////////////////////////////////////////////////

	MFInt32 *getCoordIndexField() const;

	void addCoordIndex(int value);
	int getNCoordIndexes() const;
	int getCoordIndex(int index) const;
	
	////////////////////////////////////////////////
	// TexCoordIndex
	////////////////////////////////////////////////

	MFInt32 *getTexCoordIndexField() const;

	void addTexCoordIndex(int value);
	int getNTexCoordIndexes() const;
	int getTexCoordIndex(int index) const;
	
	////////////////////////////////////////////////
	// ColorIndex
	////////////////////////////////////////////////

	MFInt32 *getColorIndexField() const;

	void addColorIndex(int value);
	int getNColorIndexes() const;
	int getColorIndex(int index) const;

	////////////////////////////////////////////////
	// NormalIndex
	////////////////////////////////////////////////

	MFInt32 *getNormalIndexField() const;

	void addNormalIndex(int value);
	int getNNormalIndexes() const;
	int getNormalIndex(int index) const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	BoundingBox
	////////////////////////////////////////////////

	void recomputeBoundingBox();

	////////////////////////////////////////////////
	//	recomputeDisplayList
	////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL
	void recomputeDisplayList();
#endif

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	Polygon
	////////////////////////////////////////////////

	int getNPolygons() const;

	////////////////////////////////////////////////
	//	Normal
	////////////////////////////////////////////////

	bool generateNormals();

	////////////////////////////////////////////////
	//	TextureCoordinate
	////////////////////////////////////////////////
	
	bool generateTextureCoordinate();

};

}

#endif

