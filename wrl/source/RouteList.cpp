/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	RouteList.cpp
*
******************************************************************/

#include <RouteList.h>

using namespace MyVrml;

RouteList::RouteList()
{
}

RouteList::~RouteList()
{
}

void RouteList::addRoute(Route *route) 
{
	addNode(route);
}

Route *RouteList::getRoutes() const
{
	return (Route *)getNodes();
}

Route *RouteList::getRoute(int n)
{
	return (Route *)getNode(n);
}

int RouteList::getNRoutes()
{
	return getNNodes();
}
