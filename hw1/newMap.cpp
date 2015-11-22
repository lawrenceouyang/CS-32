#include "newMap.h"

Map::Map(int size)
{
	m_size = 0;
	m_elements = size;
	m_pairs = new Pairs[m_elements];
}

Map::Map(const Map& old)
{
	m_size = old.m_size;
	m_elements = old.m_elements;
	m_pairs = new Pairs[m_elements];
	for (int i = 0; i < m_elements; i++)
		m_pairs[i] = old.m_pairs[i];
}

Map& Map::operator= (const Map &old)
	{
		if (&old == this)
			return (*this);
		delete [] m_pairs;
		m_elements = old.m_elements;
		m_size = old.m_size;
		m_pairs = new Pairs[m_elements];
		for (int i = 0; i < m_elements; i++)
			m_pairs[i] = old.m_pairs[i];
		return (*this);
	}

Map::~Map()
{
	delete [] m_pairs;
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
			m_size--;
			return true;
		}

	return false;
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