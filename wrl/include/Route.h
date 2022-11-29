/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Route.h
*
******************************************************************/

#ifndef _MYVRML_ROUTE_H_
#define _MYVRML_ROUTE_H_

#include <iostream>
#include <LinkedList.h>
#include <VRML97Fields.h>
#include <VRML97Nodes.h>
#include <JavaVM.h>

namespace MyVrml {

#if defined(MYVRML_SUPPORT_JSAI)
class Route : public LinkedListNode<Route>, public CJavaVM {
#else
class Route : public LinkedListNode<Route> {
#endif

	Node	*mEventOutNode;
	Node	*mEventInNode;
	Field	*mEventOutField;
	Field	*mEventInField;
	
	bool	mIsActive;
	void	*mValue;

public:

	Route(Node *eventOutNode, Field *eventOutField, Node *eventInNode, Field *eventInField);
	Route(Route *route);
	virtual ~Route(); 

	void	setEventOutNode(Node *node);
	void	setEventInNode(Node *node);
	Node	*getEventOutNode() const;
	Node	*getEventInNode() const;
	void	setEventOutField(Field *field);
	Field	*getEventOutField() const;
	void	setEventInField(Field *field);
	Field	*getEventInField() const;

	////////////////////////////////////////////////
	//	Active
	////////////////////////////////////////////////

	void setIsActive(bool active);
	bool	isActive() const;

	////////////////////////////////////////////////
	//	update
	////////////////////////////////////////////////

	void initialize();
	void update();

	////////////////////////////////////////////////
	//	update
	////////////////////////////////////////////////

	void setValue(void *value); 
	void *getValue() const;

	////////////////////////////////////////////////
	//	output
	////////////////////////////////////////////////

	void output(std::ostream& printStream) const;
	void outputXML(std::ostream& printStream) const;

	void print() const{
		output(std::cout);
	}

	void printXML() const{
		outputXML(std::cout);
	}
};

}

#endif
