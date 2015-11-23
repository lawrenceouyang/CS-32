#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <queue>

class StudentWorld;

//Base Class
class Actor: public GraphObject
{
public:
	Actor(StudentWorld* world, int ID, int x, int y) :GraphObject(ID, x, y),
		m_dead(false), m_world(world), m_lifetime(0)
	{
		setVisible(true);
		std::srand((unsigned)time(0));
	}
	virtual ~Actor() {}
	virtual void doSomething() = 0;
	
	StudentWorld* getWorld() const 
	{return m_world;}

	bool isDead() const
	{return m_dead;}

	bool isLife() const
	{
		if (m_lifetime == 0)
			return true;
		return false;
	}

	Actor* getActorAtPoint(int x, int y) const;

	void setLifetime(int time) {m_lifetime = time;}
	void decLifetime() {m_lifetime--;}
	void setDead() {m_dead = true;}
	virtual bool moveKey(int x, int y);

	int randInt(int min, int max)
	{
		return (rand() % max + min);
	}

private:
	StudentWorld* m_world;
	bool m_dead;
	int m_lifetime;
};

//Player Class
class Player: public Actor
{
public:
	Player(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y),
		m_sprayMax(2), m_sprayUsed(0), m_simulOn(false), m_walkOn(false) {}
	void doSomething();

	int maxSpray() const {return m_sprayMax;}
	int usedSpray() const {return m_sprayUsed;}
	void useSpray() {m_sprayUsed++;}
	void dieSpray() {m_sprayUsed--;}
	void setSprayDuration(int duration) {m_sprayDuration = duration;}
	void setWalkDuration(int duration) {m_walkDuration = duration;}
	void boostSpray(int max) {m_sprayMax = max;}
	void activateSimul() {m_simulOn = true;}
	void activateWalk() {m_walkOn = true;}
	virtual bool moveKey(int x, int y);
private:
	int m_sprayMax;
	int m_sprayUsed;
	int m_sprayDuration;
	int m_walkDuration;
	bool m_simulOn;
	bool m_walkOn;
};

//Brick Class
class Brick: public Actor
{
public:
	Brick(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y) {}
	virtual ~Brick() {}
	virtual void doSomething()
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
	Zumi(StudentWorld* world, int ID, int x, int y, int ticksPerMove):Actor(world, ID, x, y),
		m_ticksMove(ticksPerMove), m_currentTick(0), m_currentDirection(randInt(0,4)), m_killed(false) {}
	virtual ~Zumi() {}
	virtual void doSomething();
	virtual bool moveKey(int x, int y); //overload function that stops zumis from landing on bugsprayers

	void changeDir() {m_currentDirection = randInt(0,4);}
	void kill() {m_killed = true;}
	virtual void move();
	void dropGoodie();

private:
	int m_currentDirection;
	int m_ticksMove;
	int m_currentTick;
	bool m_killed;
};

//Complex Zumi Class
class ComplexZumi: public Zumi
{
public:
	ComplexZumi(StudentWorld* world, int ID, int x, int y, int ticksPerMove, int searchRange)
		:Zumi(world, ID, x, y, ticksPerMove), m_smellDistance(searchRange), m_detectPlayer(false) {}
	virtual void doSomething();
	virtual void move();
	bool detectPlayer();
	bool checkPath();

private:
	int m_smellDistance;
	bool m_detectPlayer;
};

//Exit Class
class Exit: public Actor
{
public:
	Exit(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y), m_complete(false)
	{
		setVisible(false);
	}
	void doSomething();
private:
	bool m_complete;
};

//Bug Sprayer Class
class BugSprayer: public Actor
{
public:
	BugSprayer(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y)
	{
		setLifetime(40);
	}
	void doSomething();
private:
	void sprayRange(int x, int y);
};

//BugSpray Class
class BugSpray: public Actor
{
public:
	BugSpray(StudentWorld* world, int ID, int x, int y):Actor(world, ID, x, y) 
	{
		setLifetime(3);
	}
	void doSomething();
private:
	void examineSpot(int x, int y);
};

//Goodie Class
class Goodie: public Actor
{
public:
	Goodie(StudentWorld* world, int ID, int x, int y, int duration):Actor(world, ID, x, y) 
	{
		setLifetime(duration);
	}
	virtual void doSomething();
};

//Extra Life Goodie Class
class ExtraLifeGoodie: public Goodie
{
public:
	ExtraLifeGoodie(StudentWorld* world, int ID, int x, int y, int duration): Goodie(world, ID, x, y, duration) {}
	virtual void doSomething();
};

//Simul Sprayer Goodie Class
class SimulSprayerGoodie: public Goodie
{
public:
	SimulSprayerGoodie(StudentWorld* world, int ID, int x, int y, int duration): Goodie(world, ID, x, y, duration) {}
	virtual void doSomething();
};

//Walk Walls Goodie Class
class WalkWallsGoodie: public Goodie
{
public:
	WalkWallsGoodie(StudentWorld* world, int ID, int x, int y, int duration): Goodie(world, ID, x, y, duration) {}
	virtual void doSomething();
};
#endif // ACTOR_H_
