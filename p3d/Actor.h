#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <vector>

class StudentWorld;

//Base Class
class Actor: public GraphObject
{
public:
	Actor(StudentWorld* world, int ID, int x, int y) :GraphObject(ID, x, y), m_dead(false), m_world(world)
	{
		setVisible(true);
	}
	virtual ~Actor() {}
	virtual void doSomething() = 0;
	
	StudentWorld* getWorld() const 
	{return m_world;}

	bool isDead() const
	{return m_dead;}

	Actor* getActorAtPoint(int x, int y);
private:
	StudentWorld* m_world;
	bool m_dead;
};

//Player Class
class Player: public Actor
{
public:
	Player(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y) {}
	void doSomething();
};

//Brick Class
class Brick: public Actor
{
public:
	Brick(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y) {}
	virtual ~Brick() {}
	void doSomething()
	{
		//do nothing...
	}
};

//Perma Brick Class
class PermaBrick: public Brick
{
public:
	PermaBrick(StudentWorld* world, int ID, int x, int y):Brick(world, ID, x, y) {}
};

//Breakable Brick Class
class BreakBrick: public Brick
{
public:
	BreakBrick(StudentWorld* world, int ID, int x, int y):Brick(world, ID, x, y) {}
};

//Zumi Class
class Zumi: public Actor
{
public:
	Zumi(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y)  {}
	void doSomething() {}
};

//Complex Zumi Class
class ComplexZumi: public Zumi
{
public:
	ComplexZumi(StudentWorld* world, int ID, int x, int y):Zumi(world, ID, x, y) {}
	void doSomething() {}
};

//Exit Class
class Exit: public Actor
{
public:
	Exit(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y) 
	{
		setVisible(false);
	}
	void doSomething() {}
};
#endif // ACTOR_H_
