#ifndef SALARYMAP_H
#define SALARYMAP_H

#include "Map.h" //although "class Map;" would compile as well
#include <iostream>

class SalaryMap
{
public:
	SalaryMap();       // Create an empty salary map.

	bool add(std::string name, double salary); // Add employee and salary to map
	bool raise(std::string name, double pct); // Increase/decrease the employee's salary
	double salary(std::string name) const; // returns employee's salary
	int size() const;  // Return the number of employees in the SalaryMap.
	void print() const; // Prints all employees and their respective salaries
private:
	Map m_smap;
};

#endif SALARYMAP_H