#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "GraphObject.h"
#include "Actor.h"
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>

class StudentWorld : public GameWorld
{
public:
	StudentWorld() 
	{
		m_bonus = 0;
		m_zumiCount = 0;
		m_levelFin = false;
		m_onExit = false;
	}
	virtual ~StudentWorld()
	{
		std::list<Actor*>::iterator it;
		for (it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
			delete *it;

		m_worldObjects.clear();
		delete m_player;
	}
	virtual int init();
	virtual int move();

	virtual void cleanUp()
    {
		std::list<Actor*>::iterator it;
		for (it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
			delete *it;

		m_worldObjects.clear();
		delete m_player;
    }

	//actor creators
	void createBugSprayer(int x, int y)
	{m_worldObjects.push_back(new BugSprayer(this, IID_BUGSPRAYER, x, y));}

	void createBugSpray(int x, int y)
	{m_worldObjects.push_back(new BugSpray(this, IID_BUGSPRAY, x, y));}
	
	void createExtraLifeGoodie(int x, int y)
	{m_worldObjects.push_back(new ExtraLifeGoodie(this, IID_EXTRA_LIFE_GOODIE, x, y, m_durationOfGoodie));}

	void createSimulSprayerGoodie(int x, int y)
	{m_worldObjects.push_back(new SimulSprayerGoodie(this, IID_INCREASE_SIMULTANEOUS_SPRAYER_GOODIE, x, y, m_durationOfGoodie));}

	void createWalkWallsGoodie(int x, int y)
	{m_worldObjects.push_back(new WalkWallsGoodie(this, IID_WALK_THRU_GOODIE, x, y, m_durationOfGoodie));}

	std::string getStats();

	int getBonus() const {return m_bonus;}
	void setBonus(int val) {m_bonus = val;}

	void decZCount() {m_zumiCount--;}

	bool getWin() {return m_levelFin;}
	void getOnExit() {m_onExit = true;}

	//accessors for level data for use by actors
	int getChanceOfGoodie() const {return m_chanceOfGoodie;}
	int getChanceOfLife() const {return m_probOfLifeGoodie;}
	int getChanceOfSimul() const {return m_probOfSimulGoodie;}
	int getChanceOfWalk() const {return m_probOfWalkGoodie;}
	int getDurOfSimul() const {return m_durOfSimulGoodie;}
	int getDurOfWalk() const {return m_durOfWalkGoodie;}
	int getMaxSimul() const {return m_maxSimulGoodie;}
	int getCZumiSearchRange() const {return m_CZumiSearchRange;}

	std::list<Actor*> showObjects() const {return m_worldObjects;}
	std::list<Actor*>::iterator showBegin() {return m_worldObjects.begin();}
	std::list<Actor*>::iterator showEnd() {return m_worldObjects.end();}
	Player* showPlayer() const {return m_player;}


private:
	std::list<Actor*> m_worldObjects;
	Player* m_player;
	int m_bonus;
	int m_zumiCount;

	//Storing level data for easy access
	int m_chanceOfGoodie;
	int m_durationOfGoodie;
	int m_probOfLifeGoodie;
	int m_probOfSimulGoodie;
	int m_probOfWalkGoodie;
	int m_durOfWalkGoodie;
	int m_durOfSimulGoodie;
	int m_maxSimulGoodie;
	int m_CZumiSearchRange;
	bool m_levelFin;
	bool m_onExit;
};

#endif // STUDENTWORLD_H_
