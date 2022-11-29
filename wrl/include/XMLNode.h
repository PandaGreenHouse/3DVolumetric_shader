/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	XMLNode.h
*
******************************************************************/

#ifndef _MYVRML_XMLNODE_H_
#define _MYVRML_XMLNODE_H_

#include <Node.h>
#include <XMLElement.h>

namespace MyVrml {

class XMLNode : public Node {

public:

	XMLNode();
	virtual ~XMLNode();

	////////////////////////////////////////////////
	//	Element Field
	////////////////////////////////////////////////

	XMLElement *getElement(const char *eleName) const;
	int getNElements() const;
	void addElement(XMLElement *ele);
	void addElement(const char *name, XMLElement *ele);
	void addElement(const char *name, const char *value);
	XMLElement *getElement(int index) const;
/*
	bool removeElement(XMLElement *ele);
	bool removeElement(const char *eleName);
	int getElementNumber(XMLElement ele);
*/

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	XMLNode *next() const;
	XMLNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	virtual functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();
	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif
