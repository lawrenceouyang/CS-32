#include "Map.h"

Map::Map()
{
	m_size = 0;
	m_elements = DEFAULT_MAX_ITEMS;
}
bool Map::empty() const
{
	if (m_size == 0)
		return true;
	return false;
}

int Map::size() const
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)	//checks entire array for any key that matches
			return false;	

	for (int i = 0; i < m_elements; i++)
		if (!m_pairs[i].m_used)								//if none found, checks array for any empty pairs
		{
			m_pairs[i].m_key = key;
			m_pairs[i].m_value = value;
			m_pairs[i].m_used = true;
			m_size++;
			return true;
		}
	return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)
		{
			m_pairs[i].m_value = value;
			return true;
		}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)	//checks entire array for any key that matches
		{
			m_pairs[i].m_value = value;
			return true;
		}	

	for (int i = 0; i < m_elements; i++)
		if (!m_pairs[i].m_used)	//if none found, checks array for any empty pairs
		{
			m_pairs[i].m_key = key;
			m_pairs[i].m_value = value;
			m_pairs[i].m_used = true;
			m_size++;
			return true;
		}
	return false;
}

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)
		{
			m_pairs[i].m_used = false;	//actual key & value not changed, just the in use bool
			m_size--;					//using a bool in the Pairs struct compresses the erase function
			return true;				//as well as prevents any problems from undefined behavior, as the
		}								//values of the array are undefined and cannot be initialized because
	return false;						//of typeset.
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)
			return true;

	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < m_elements; i++)
		if (m_pairs[i].m_used && m_pairs[i].m_key == key)
		{
			value = m_pairs[i].m_value;
			return true;
		}
		
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if ( i >= 0 && i < m_size)
		for (int j = i; j < m_elements; j++)
			if (m_pairs[j].m_used)
				if (key != m_pairs[j].m_key)
					{
						key = m_pairs[j].m_key;
						value = m_pairs[j].m_value;
						return true;
					}

	return false;
}

void Map::swap(Map& other)
{
	Map* temp = new Map;
	*temp = *this;
	*this = other;
	other = *temp;
	delete temp;
}