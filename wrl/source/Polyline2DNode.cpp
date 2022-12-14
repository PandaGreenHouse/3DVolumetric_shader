/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Polyline2DNode.cpp
*
******************************************************************/

#include <Polyline2DNode.h>
#include <Graphic3D.h>

using namespace MyVrml;

static const char lineSegmentsFieldString[] = "lineSegments";

Polyline2DNode::Polyline2DNode() 
{
	setHeaderFlag(false);
	setType(POLYLINE2D_NODE);

	///////////////////////////
	// Field 
	///////////////////////////

	// lineSegments field
	lineSegmentsField = new MFVec2f();
	addField(lineSegmentsFieldString, lineSegmentsField);
}

Polyline2DNode::~Polyline2DNode() 
{
}

////////////////////////////////////////////////
//	LineSegments
////////////////////////////////////////////////

MFVec2f *Polyline2DNode::getLineSegmentsField() const
{
	if (isInstanceNode() == false)
		return lineSegmentsField;
	return 	(MFVec2f *)getField(lineSegmentsFieldString);
}

int Polyline2DNode::getNLineSegments() const
{
	return getLineSegmentsField()->getSize();
}

void Polyline2DNode::addLineSegment(float point[]) 
{
	getLineSegmentsField()->addValue(point);
}

void Polyline2DNode::addLineSegment(float x, float y) 
{
	getLineSegmentsField()->addValue(x, y);
}

void Polyline2DNode::getLineSegment(int index, float point[]) const
{
	getLineSegmentsField()->get1Value(index, point);
}

void Polyline2DNode::setLineSegment(int index, float point[]) 
{
	getLineSegmentsField()->set1Value(index, point);
}

void Polyline2DNode::setLineSegment(int index, float x, float y) 
{
	getLineSegmentsField()->set1Value(index, x, y);
}

void Polyline2DNode::removeLineSegment(int index) 
{
	getLineSegmentsField()->remove(index);
}

void Polyline2DNode::removeAllLineSegments() 
{
	getLineSegmentsField()->clear();
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

Polyline2DNode *Polyline2DNode::next() const
{
	return (Polyline2DNode *)Node::next(getType());
}

Polyline2DNode *Polyline2DNode::nextTraversal() const
{
	return (Polyline2DNode *)Node::nextTraversalByType(getType());
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool Polyline2DNode::isChildNodeType(Node *node) const
{
	return false;
}

void Polyline2DNode::initialize() 
{
	recomputeBoundingBox();
#ifdef MYVRML_SUPPORT_OPENGL
		recomputeDisplayList();
#endif
}

void Polyline2DNode::uninitialize() 
{
}

void Polyline2DNode::update() 
{
}

////////////////////////////////////////////////
//	Infomation
////////////////////////////////////////////////

void Polyline2DNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}

////////////////////////////////////////////////
//	Polyline2DNode::recomputeDisplayList
////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL

void Polyline2DNode::recomputeDisplayList() 
{
};

#endif
