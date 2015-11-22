#include "newMap.h"
#include <cassert>
#include <iostream>


int main()
{
	Map map;
	assert(map.empty());
	assert(map.insert("Hello", 0));
	assert(map.insert("Goodbye", 1));
	assert(map.size() == 2);
	assert(!map.insert("Hello", 2)); // should be false
	assert(!map.empty());
	assert(map.update("Goodbye", 3));
	assert(map.insertOrUpdate("Never", 4));
	assert(map.insertOrUpdate("Hello", 5));
	assert(map.erase("Goodbye"));
	assert(!map.contains("Goodbye"));
	assert(map.contains("Hello"));
	assert(map.insert("Say", 6));
	assert(map.size() == 3);

	std::string s;
	double d = 0;

	assert(map.get("Hello", d));
	std::cout << d << std::endl;
	assert(!map.get("Leaving", d));

	for (int i = 0; i < map.size(); i++)
	{
		map.get(i, s, d);
		std::cout << s << " " << d << std:: endl;
	}

	Map map2;
	map2.insert("Life", 7);
	map2.insert("Death", 8);

	map.swap(map2);

	assert(map.size() == 2 && map.contains("Life") && map.contains("Death"));
	assert(map2.size() == 3 && map2.contains("Hello") && map2.contains("Never") && map2.contains("Say"));
}
	