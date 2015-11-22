//Lawrence Ouyang
//504128219
//CS32 Project 2 Double Trouble
#include "Map.h"

Map::Map()
{
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;
}
Map::~Map()
{
	Pair* temp = m_head;
	while (temp != nullptr)
	{
		Pair* die = temp;
		temp = temp->next;
		delete die;
	}
}

Map::Map(const Map& other)
{
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;
	Pair* temp = other.m_tail;
	while (temp != nullptr)                      // Uses the values in other.m_tail and inserts them into its own map
	{
		insert(temp->m_key,temp->m_value);
		temp = temp->previous;
	}
}

Map&::Map::operator=(Map& other)
{
	if (&other == this)                          // Checks if the operands are the same
	{
		return *this;
	}
	Pair* temp1 = m_head;
	while (temp1 != nullptr)                     // Clears all data from the current map
	{
		Pair* die = temp1;
		temp1 = temp1->next;
		delete die;
	}
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;
	Pair* temp2 = other.m_tail;
	while (temp2 != nullptr)                     // Uses the values in other.m_tail and inserts them into its own map
	{
		insert(temp2->m_key,temp2->m_value);
		temp2 = temp2->previous;
	}
	return *this;
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
	if (m_head == nullptr || !contains(key))            // Checks if there are no pairs or if the key is already in the map
	{
		Pair* latest = new Pair;
		latest->m_key = key;
		latest->m_value = value;
		latest->next = m_head;                      // Sets the head as the one after itself
		m_head = latest;                            // Sets head to itself
		latest->previous = nullptr;
		if (m_tail == nullptr)                      // Sets tail if first element to be entered into array
			m_tail = latest;
		else
			latest->next->previous = latest;    // Otherwise links itself to next element
		m_size++;
		return true;
	}

	return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	Pair* temp = pairCheck(key);
	if (temp != nullptr)
	{
		temp->m_value = value;
		return true;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (!update(key, value))                                // If update fails, means no key is present, so add it
		return insert(key, value);

	return false;
}

bool Map::erase(const KeyType& key)
{
	Pair* temp = pairCheck(key);
	if (temp != nullptr)
	{
		if (temp == m_head && temp == m_tail) {}        // Case 1: 1 element in array, do nothing else
		else if (temp == m_head)                        // Case 2: deleting first element, adjust next element link
		{
			m_head = temp->next;
			m_head->previous = nullptr;
		}
		else if (temp == m_tail)                        //Case 3: deleting last element, adjust second to last element link
		{
			m_tail = temp->previous;
			m_tail->next = nullptr;
		}
		else                                            //Case 4: deleting anything else, adjust 2 adjacent element links
		{
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
		}
		m_size--;
		delete temp;
		return true;
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	if (m_head != nullptr)
	{
		Pair* temp = m_head;
		while (temp != nullptr)
		{
			if (temp->m_key == key)
				return true;
			temp = temp->next;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	Pair* temp = pairCheck(key);
	if (temp != nullptr)
	{
		value = temp->m_value;
		return true;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i >= 0 && i < m_size)
	{
		Pair* temp = m_head;
		for (int j = 0; j < i; j++) // For value i, traverse i times on list
			temp = temp->next;

		key = temp->m_key;
		value = temp->m_value;
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
		 
//Private Auxillary Function

Map::Pair* Map::pairCheck(const KeyType& key) const
{
	if (m_head != nullptr)
	{
		Pair* temp = m_head;
		while (temp != nullptr)
		{
			if (temp->m_key == key)
				return temp;
			temp = temp->next;
		}
	}
	return nullptr;
}
