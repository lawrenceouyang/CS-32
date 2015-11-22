#include <iostream>
#include <string>
using namespace std;

class Sport
{
public:
	Sport(string name)
	{
		m_name = name;
		if (m_name == "Pair skating free")
			m_place = false;
		else
			m_place = true;
	}

	virtual ~Sport() {}
	virtual bool isOutdoor() const
	{ return m_place; }
	virtual string icon() const = 0;

	virtual string name() const
	{ return m_name; }

private:
	string m_name; 
	bool m_place;
};

class Snowboarding: public Sport
{
public:
	Snowboarding(string name)
		:Sport(name) {}
	virtual ~Snowboarding()
	{ cout << "Destroying the Snowboarding object named " << name() << "." << endl; }

	virtual string icon() const
	{ return "a descending snowboarder"; }
};

class Biathlon: public Sport
{
public:
	Biathlon(string name, double distance)
		:Sport(name)
	{ m_distance = distance; }

	virtual ~Biathlon()
	{ cout << "Destroying the Biathalon object named " << name() << ", distance " << m_distance << " km." << endl; }

	virtual string icon() const
	{ return "a skier with a rifle"; }

private:
	double m_distance;
};

class FigureSkating: public Sport
{
public:
	FigureSkating(string name)
		:Sport(name) {}
	
	virtual ~FigureSkating()
	{ cout << "Destroying the FigureSkating object named " << name() << "." << endl; }

	virtual string icon() const
	{ return "a skater in the Biellmann position"; }
};
