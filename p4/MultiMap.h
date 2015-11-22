#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <string>

class MultiMap
{
private:
	struct Node
	{
		Node(std::string key, unsigned int value):m_key(key), m_value(value),
			m_left(nullptr), m_right(nullptr), m_parent(nullptr) {}
		std::string m_key;
		unsigned int m_value;
		Node* m_left;
		Node* m_right;
		Node* m_parent;
	};

public:
	// You must implement this public nested MultiMap::Iterator class
	class Iterator
	{
	public:
		Iterator() {}		// You must have a default constructor
		Iterator(Node* start):m_node(start) {}
		Iterator operator= (const Iterator& other) {m_node = other.m_node; return m_node;}
		bool valid() const {return (m_node != nullptr);}
		std::string getKey() const {return m_node->m_key;}
		unsigned int getValue() const {return m_node->m_value;}
		bool next();	
		bool prev();
	private:
		Node* m_node;
	};

	MultiMap():m_root(nullptr) {}
	~MultiMap() {clear();}
	void clear() {postOrderDelete(m_root); m_root = nullptr;}
	void insert(std::string key, unsigned int value);
	Iterator findEqual(std::string key) const;
	Iterator findEqualOrSuccessor(std::string key) const;
	Iterator findEqualOrPredecessor(std::string key) const;

	Node* root() const {return m_root;}
private:
	// To prevent MultiMaps from being coped or assigned, declare these members
	// private and do not implement them.
	MultiMap(const MultiMap& other);
	MultiMap& operator=(const MultiMap& rhs);
	void postOrderDelete(Node* current);		//recursion to delete post order tree

	Node* m_root;
};

#endif MULTIMAP_H