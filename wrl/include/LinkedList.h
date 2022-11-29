/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	LinkedList.h
*
*	03/23/04
*	- Thanks for Joerg Scheurich aka MUFTI <rusmufti@helpdesk.rus.uni-stuttgart.de>
*	- Added to include MyVrmlConfig.h for IRIX platform
*
******************************************************************/

#ifndef _MYVRML_LINKEDLIST_H_
#define _MYVRML_LINKEDLIST_H_

#include <MyVrmlConfig.h>
#include <LinkedListNode.h>

#ifndef NO_USE_STL
#include <list>
#endif

namespace MyVrml {

#ifndef NO_USE_STL

#include <list>

template <class T>
class LinkedList {

	LinkedListNode<T>	*mHeaderNode;

	 // caching
	int m_nSize;
	int m_nCurrentNode;
	LinkedListNode <T> *m_pCurrentNode;

	void clearCacheData ()
	{
		m_nSize = -1;
		m_nCurrentNode = -1;
		m_pCurrentNode = NULL;
	}

public:

	LinkedList () {
		mHeaderNode = new LinkedListNode<T>(true);
		m_nSize = -1;
		m_nCurrentNode = -1;
		m_pCurrentNode = NULL;
	}

	virtual ~LinkedList () {
		clearCacheData ();
		deleteNodes();
		delete mHeaderNode;
	}

	void setRootNode(LinkedListNode<T> *obj) {
		clearCacheData ();
		if (mHeaderNode) delete mHeaderNode;
		mHeaderNode = obj;
	}

	T *getRootNode () const {
		return (T *)mHeaderNode;
	}

	T *getNodes () const {
		if (mHeaderNode == NULL)
			return NULL;
		return (T *)mHeaderNode->next();
	}


	T *getNode (int number) {
		if (number < 0)
			return (T *)NULL;

		if (m_nCurrentNode < 0 || number < m_nCurrentNode)
		{
			m_nCurrentNode = 0;
			m_pCurrentNode = NULL;
		}

		LinkedListNode<T> *node = m_pCurrentNode ? m_pCurrentNode : (LinkedListNode<T> *)getNodes();
		for (int n=m_nCurrentNode; n<number && node; n++)
			node = (LinkedListNode<T> *)node->next();

		if (node)
		{
			m_nCurrentNode = number;
			m_pCurrentNode = node;
		}
		else
		{
			m_nCurrentNode = -1;
		}

		return (T *)node;
	}

	T *getLastNode () const {
		LinkedListNode<T> *lastNode = (LinkedListNode<T> *)mHeaderNode->prev();
		if (lastNode == NULL)
			return NULL;
		if (lastNode->isHeaderNode())
			return NULL;
		else
			return (T *)lastNode;
	}

	int getNNodes() {
		if (m_nSize > 0)
		{
			return m_nSize;
		}
		else
		{
			register int n = 0;
			for (LinkedListNode<T> *listNode = (LinkedListNode<T> *)getNodes(); listNode; listNode = (LinkedListNode<T> *)listNode->next())
				n++;
			return m_nSize = n;
		}
	}

	void addNode(LinkedListNode<T> *node) {
		clearCacheData ();
		node->remove ();
		node->insert((LinkedListNode<T> *)mHeaderNode->prev());
	}
	void addNodeAtFirst(LinkedListNode<T> *node) {
		clearCacheData ();
		node->remove();
		node->insert(mHeaderNode);
	}

	void deleteNode(LinkedListNode<T> *node) {
		LinkedListNode<T> *rootNode = (LinkedListNode<T> *)getRootNode();
		if (!rootNode || !node)
			return;
		LinkedListNode<T> * temp;
		while (rootNode->next())
		{
			temp = rootNode->mNextNode;
			if (temp == node)
			{
				rootNode->mNextNode = temp->next();
				delete temp;
				return;
			}
		}

		while (rootNode->prev())
		{
			temp = rootNode->mPrevNode;
			if (temp == node)
			{
				rootNode->mPrevNode = temp->prev();
				delete temp;
			}
		}
	}

	void deleteNodes() {
		clearCacheData ();
		LinkedListNode<T> *rootNode = (LinkedListNode<T> *)getRootNode();
		if (!rootNode)
			return;
		LinkedListNode<T> * temp;
		while (rootNode->next())
		{
			temp = rootNode->mNextNode;
			rootNode->mNextNode = temp->next();
			delete temp;
		}
	}
};
#else

template <class T>class LinkedList {

	LinkedListNode<T>	*mHeaderNode;

	// caching
	int m_nSize;
	int m_nCurrentNode;
	LinkedListNode <T> *m_pCurrentNode;

	void clearCacheData ()
	{
		m_nSize = -1;
		m_nCurrentNode = -1;
		m_pCurrentNode = NULL;
	}

public:

	LinkedList () {
		mHeaderNode = new LinkedListNode<T>(true);
		m_nSize = -1;
		m_nCurrentNode = -1;
		m_pCurrentNode = NULL;
	}

	virtual ~LinkedList () {
		clearCacheData ();
		deleteNodes();
		delete mHeaderNode;
		mHeaderNode = NULL;
	}

	void setRootNode(LinkedListNode<T> *obj) {
		clearCacheData ();
		mHeaderNode = obj;
	}

	T *getRootNode () const {
		return (T *)mHeaderNode;
	}

	T *getNodes () const {
		return (T *)mHeaderNode->next();
	}

	T *getNode (int number) const {
		if (number < 0)
			return (T *)NULL;
		LinkedListNode<T> *node = (LinkedListNode<T> *)getNodes();
		
		if (m_nCurrentNode < 0 || number < m_nCurrentNode)
		{
			m_nCurrentNode = 0;
			m_pCurrentNode = NULL;
		}
		LinkedListNode<T> *node = m_pCurrentNode ? m_pCurrentNode : (LinkedListNode<T> *)getNodes();
		for (int n=m_nCurrentNode; n<number && node; n++)
			node = (LinkedListNode<T> *)node->next();

		if (node)
		{
			m_nCurrentNode = number;
			m_pCurrentNode = node;
		}
		else
		{			
			m_nCurrentNode = -1;
		}

		return (T *)node;
	}

	T *getLastNode () const {
		LinkedListNode<T> *lastNode = (LinkedListNode<T> *)mHeaderNode->prev();
		if (lastNode->isHeaderNode())
			return NULL;
		else
			return (T *)lastNode;
	}

	int getNNodes() const	{
		if (m_nSize > 0)
			return m_nSize;
		else
		{
			register int n = 0;
			for (LinkedListNode<T> *listNode = (LinkedListNode<T> *)getNodes(); listNode; listNode = (LinkedListNode<T> *)listNode->next())
				n++;
			return m_nSize = n;
		}
	}

	void addNode(LinkedListNode<T> *node) {
		clearCacheData ();
		node->remove();
		node->insert((LinkedListNode<T> *)mHeaderNode->prev());
	}

	void addNodeAtFirst(LinkedListNode<T> *node) {
		clearCacheData ();
		node->remove();
		node->insert(mHeaderNode);
	}

	void deleteNodes() {
		clearCacheData ();
		LinkedListNode<T> *rootNode = (LinkedListNode<T> *)getRootNode();
		if (!rootNode)
			return;
		LinkedListNode<T> * temp;
		while (rootNode->next())
		{
			temp = rootNode->mNextNode;
			rootNode->mNextNode = temp->next();
			delete temp;
		}
	}
};

#endif

}

#endif

