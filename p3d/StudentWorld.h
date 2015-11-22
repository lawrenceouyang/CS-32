#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "GraphObject.h"
#include "Actor.h"
#include <vector>

class StudentWorld : public GameWorld
{
public:
	StudentWorld() {}
	virtual ~StudentWorld()
	{
		for (unsigned int i = 0; i < m_worldObjects.size(); i++)
			delete m_worldObjects[i];
		delete m_player;
	}
	virtual int init();
	virtual int move();

	virtual void cleanUp()
    {
		for (unsigned int i = 0; i < m_worldObjects.size(); i++)
			delete m_worldObjects[i];
		delete m_player;
    }

	std::vector<Actor*> showObjects() const {return m_worldObjects;}

private:
	std::vector<Actor*> m_worldObjects;
	Player* m_player;
};

#endif // STUDENTWORLD_H_
