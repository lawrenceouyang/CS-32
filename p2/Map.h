#ifndef MAP_H
#define MAP_H

#include <string>
typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
	Map();                              // Constructor
	~Map();                             // Destructor
	Map(const Map& other);              // Copy Constructor
	Map& operator= (Map& other);        // Assignment Operator

	bool empty() const;                                             // Return true if the map is empty
	int size() const;                                               // Return the number of pairs in the map
	bool insert(const KeyType& key, const ValueType& value);        // Insert key and value pair into map
	bool update(const KeyType& key, const ValueType& value);        // Update key with value in map
	bool insertOrUpdate(const KeyType& key, const ValueType& value);// Insert if pair doesn't exist, update if does
	bool erase(const KeyType& key);                                 // Make key and value pair no longer accessable
	bool contains(const KeyType& key) const;                        // Boolean check for key in map
	bool get(const KeyType& key, ValueType& value) const;           // Set pair value to value of key
	bool get(int i, KeyType& key, ValueType& value) const;          // Set key and value to any pairing in map
	void swap(Map& other);                                          // Exchange the contents of 2 maps.

private:
	struct Pair
	{
		Pair* previous;
		Pair* next;
		KeyType m_key;
		ValueType m_value;
	};

	Pair* m_head;                               // Pointer to first pair
	Pair* m_tail;                               // Pointer to end pair
	int m_size;                                 // Number of pairs							
	Pair* pairCheck(const KeyType& key) const;  // Traverses the list search for key & return mem
};

inline bool combine(const Map& m1, const Map& m2, Map& result)
{
	Map temp;                               // Uses an empty map. Prevents aliasing issues.
	bool done = true;
	for (int i = 0; i < m1.size(); i++)     // Inserts all pairs in map 1
	{
		KeyType k;
		ValueType v;
		m1.get(i, k, v);
		temp.insert(k, v);
	}
	for (int i = 0; i < m2.size(); i++)     // Inserts all pairs in map 2
	{
		KeyType k;
		ValueType v;
		m2.get(i, k, v);
		temp.insert(k, v);
	}
	for (int i = 0; i < temp.size(); i++)   // Checks every pair in result to see if their key matches both maps
	{
		KeyType k;
		ValueType v;
		temp.get(i, k, v);
		if (m1.contains(k) && m2.contains(k))
		{
			ValueType v1, v2;       // If match found, compares their values. If no match, deletes pair.
			m1.get(k, v1);
			m2.get(k, v2);
			if (v1 != v2)
			{
				temp.erase(k);
				done = false;
			}
		}
	}
	result = temp;
	return done;
}

inline void subtract(const Map& m1, const Map& m2, Map& result)
{
	Map temp(m1);                           // Creates duplicate of m1
	for (int i = 0; i < m1.size(); i++)     // Check all keys of temp and compare with m2
	{
		KeyType k;
		ValueType v;
		m1.get(i, k, v);
		if (m2.contains(k))             // If pair is in m2, erases the value from temp
			temp.erase(k);
	}
	result = temp;
}
#endif MAP_H