#ifndef NEWMAP_H
#define NEWMAP_H

#include <string>
typedef std::string KeyType;
typedef double ValueType;
const int DEFAULT_MAX_ITEMS = 200;

class Map
{
public:
	Map(int size = DEFAULT_MAX_ITEMS);  // Constructor. Default parameter 200
	Map(const Map& old);				// Copy constructor
	~Map();								// Destructor
	Map& operator= (const Map &old);	// Assignment operator

	bool empty() const;												// Return true if the map is empty
	int size() const;												// Return the number of pairs in the map
	bool insert(const KeyType& key, const ValueType& value);		// Insert key and value pair into map
	bool update(const KeyType& key, const ValueType& value);		// Update key with value in map
	bool insertOrUpdate(const KeyType& key, const ValueType& value);// Insert if pair doesn't exist, update if does
	bool erase(const KeyType& key);									// Make key and value pair no longer accessable
	bool contains(const KeyType& key) const;						// Boolean check for key in map
	bool get(const KeyType& key, ValueType& value) const;			// Set pair value to value of key
	bool get(int i, KeyType& key, ValueType& value) const;			// Set key and value to any pairing in map
	void swap(Map& other);											// Exchange the contents of 2 maps.

private:
	struct Pairs
	{
		Pairs()
		{m_used = false;}
		KeyType m_key;
		ValueType m_value;
		bool m_used; // boolean to see if the current pair is in use. See erase function for more info
	};				 // and this is not overkill.

	Pairs *m_pairs; 
	int m_elements;
	int m_size;
};

#endif NEWMAP_H