/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Polypoint2DNode.cpp
*
******************************************************************/

#include <Polypoint2DNode.h>
#include <Graphic3D.h>

using namespace MyVrml;

static const char pointsFieldString[] = "points";

Polypoint2DNode::Polypoint2DNode() 
{
	setHeaderFlag(false);
	setType(POLYPOINT2D_NODE);

	///////////////////////////
	// Field 
	///////////////////////////

	// points field
	pointsField = new MFVec2f();
	addField(pointsFieldString, pointsField);
}

Polypoint2DNode::~Polypoint2DNode() 
{
}

////////////////////////////////////////////////
//	Points
////////////////////////////////////////////////

MFVec2f *Polypoint2DNode::getPointsField() const
{
	if (isInstanceNode() == false)
		return pointsField;
	return 	(MFVec2f *)getField(pointsFieldString);
}

int Polypoint2DNode::getNPoints() const
{
	return getPointsField()->getSize();
}

void Polypoint2DNode::addPoint(float point[]) 
{
	getPointsField()->addValue(point);
}

void Polypoint2DNode::addPoint(float x, float y) 
{
	getPointsField()->addValue(x, y);
}

void Polypoint2DNode::getPoint(int index, float point[]) const
{
	getPointsField()->get1Value(index, point);
}

void Polypoint2DNode::setPoint(int index, float point[]) 
{
	getPointsField()->set1Value(index, point);
}

void Polypoint2DNode::setPoint(int index, float x, float y) 
{
	getPointsField()->set1Value(index, x, y);
}

void Polypoint2DNode::removePoint(int index) 
{
	getPointsField()->remove(index);
}

void Polypoint2DNode::removeAllPoints() 
{
	getPointsField()->clear();
}

////////////////////////////////////////////////
//	List
////////////////////////////////////////////////

Polypoint2DNode *Polypoint2DNode::next() const
{
	return (Polypoint2DNode *)Node::next(getType());
}

Polypoint2DNode *Polypoint2DNode::nextTraversal() const
{
	return (Polypoint2DNode *)Node::nextTraversalByType(getType());
}

////////////////////////////////////////////////
//	functions
////////////////////////////////////////////////
	
bool Polypoint2DNode::isChildNodeType(Node *node) const
{
	return false;
}

void Polypoint2DNode::initialize() 
{
	recomputeBoundingBox();
#ifdef MYVRML_SUPPORT_OPENGL
		recomputeDisplayList();
#endif
}

void Polypoint2DNode::uninitialize() 
{
}

void Polypoint2DNode::update() 
{
}

////////////////////////////////////////////////
//	Infomation
////////////////////////////////////////////////

void Polypoint2DNode::outputContext(std::ostream &printStream, const char *indentString) const
{
}

////////////////////////////////////////////////
//	Polypoint2DNode::recomputeDisplayList
////////////////////////////////////////////////

#ifdef MYVRML_SUPPORT_OPENGL

void Polypoint2DNode::recomputeDisplayList() 
{
};

#endif
