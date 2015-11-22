#include "MultiMap.h"
using namespace std;

//MultiMap::Iterator Implementations

bool MultiMap::Iterator::next()
{
	if (!valid())
		return false;
	if (m_node->m_right != nullptr)						//first moves onto the right
	{
		m_node = m_node->m_right;
		if (m_node->m_key == m_node->m_parent->m_key)	//check if duplicate key
			return true;

		while (m_node->m_left != nullptr)				//if there are left nodes, travel to the furthest left node
			m_node = m_node->m_left;

		return true;
	}
	while (m_node->m_parent != nullptr)					//if at this statement, no pertinent child nodes
	{                                                   //check if not root node					
		if (m_node->m_key >= m_node->m_parent->m_key)	//checks if parent key is greater than node key
			m_node = m_node->m_parent;
		else
		{
			m_node = m_node->m_parent;
			return true;
		}
	}
	m_node = nullptr;
	return false;
}

bool MultiMap::Iterator::prev()				//inverse instructions to next()
{
	if (!valid())
		return false;
	if (m_node->m_left != nullptr)
	{
		m_node = m_node->m_left;
		if (m_node->m_key == m_node->m_parent->m_key)
			return true;

		while (m_node->m_right != nullptr)
			m_node = m_node->m_right;

		return true;
	}
	while (m_node->m_parent != nullptr)
	{
		if (m_node->m_key < m_node->m_parent->m_key)
			m_node = m_node->m_parent;
		else
		{
			m_node = m_node->m_parent;
			return true;
		}
	}
	m_node = nullptr;
	return false;
}

//MultiMap Implementations

void MultiMap::insert(string key, unsigned int value)
{
	if (m_root == nullptr)
	{
		m_root = new Node(key, value);
		return;
	}
	Node* temp = m_root;
	
	for (;;)
	{
		if (key < temp->m_key) 
			if (temp->m_left != nullptr)
				temp = temp->m_left;
			else
				break;
			
		if (key >= temp->m_key)
			if (temp->m_right != nullptr)
				temp = temp->m_right;
			else
				break;

	}
	if (key < temp->m_key)
	{
		temp->m_left = new Node(key, value);
		temp->m_left->m_parent = temp;
	}

	if (key >= temp->m_key)
	{
		temp->m_right = new Node(key, value);
		temp->m_right->m_parent = temp;
	}
}

MultiMap::Iterator MultiMap::findEqual(string key) const
{
	Iterator it(m_root);
	while (it.valid())
	{
		if (key == it.getKey())
			return it;
		else if (key > it.getKey())
			it.next();
		else if (key < it.getKey())
			it.prev();
	}
	return it;
}

MultiMap::Iterator MultiMap::findEqualOrSuccessor(string key) const
{
	Iterator it(m_root);
	Iterator p;
	for (; it.valid(); it.prev())
		p = it;
	while (p.valid())
	{
		if (p.getKey() >= key)
			return p;
		p.next();
	}
	return p;
}

MultiMap::Iterator MultiMap::findEqualOrPredecessor(string key) const
{
	Iterator it(m_root);
	Iterator p;
	for (; it.valid(); it.next())
		p = it;
	while (p.valid())
	{
		if (p.getKey() <= key)
			return p;
		p.prev();
	}
	return p;
}

void MultiMap::postOrderDelete(Node* current)
{
	if (current == nullptr)
		return;

	postOrderDelete(current->m_left);
	postOrderDelete(current->m_right);

	delete current;
}
