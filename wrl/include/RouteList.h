/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	RouteList.h
*
******************************************************************/

#ifndef _MYVRML_ROUTELIST_H_
#define _MYVRML_ROUTELIST_H_

#include <LinkedList.h>
#include <Route.h>

namespace MyVrml {

class RouteList : public LinkedList<Route> {

public:

	RouteList();
	virtual ~RouteList();

	void addRoute(Route *route);
	Route *getRoutes() const;
	Route *getRoute(int n);
	int getNRoutes();
};

}

#endif
