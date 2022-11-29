/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	NodeList.h
*
******************************************************************/

#ifndef _MYVRML_NODELIST_H_
#define _MYVRML_NODELIST_H_

#include <LinkedList.h>
#include <RootNode.h>

namespace MyVrml {

class NodeList : public LinkedList<Node> {

public:

	NodeList();
	virtual ~NodeList();
};

}

#endif
