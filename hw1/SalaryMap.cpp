#include "Map.h"
#include "SalaryMap.h"

SalaryMap::SalaryMap()
{
}

bool SalaryMap::add(std::string name, double salary)
{
	if (salary > 0 && m_smap.insert(name, salary))
		return true;
	return false;
}

bool SalaryMap::raise(std::string name, double pct)
{
	if (pct < -100 || !m_smap.contains(name))
		return false;
	double salary = 0;
	m_smap.get(name, salary);
	m_smap.update(name, salary * (1 + pct/100));
	return true;
}

double SalaryMap::salary(std::string name) const
{
	if (m_smap.contains(name))
	{
		double s;
		m_smap.get(name, s);
		return s;
	}
	return -1;
}

int SalaryMap::size() const
{
	return m_smap.size();
}

void SalaryMap::print() const
{
	std::string s;
	double d;

	for (int i = 0; i < m_smap.size(); i++)
	{
		m_smap.get(i,s,d);
			std::cout << s << " " << d << std::endl;
	}
}