#include "StudentWorld.h"
using namespace std;

GameWorld* createStudentWorld()
{
	return new StudentWorld();
}

int StudentWorld::init()	
{
	char currentLevel = getLevel() + 48;
	string loadLevel;
	Level lev;

	//Set Level String
	if (getLevel() < 10)
	{
		loadLevel = "level0";
		loadLevel += currentLevel;
		loadLevel += ".dat";
	}
	else
	{
		loadLevel = "level";
		loadLevel += currentLevel;
		loadLevel += ".dat";
	}

	Level::LoadResult result = lev.loadLevel(loadLevel);

	//Load first level
	if (getLevel() == 0)
	{
		if (result == Level::load_fail_file_not_found)
			return GWSTATUS_NO_FIRST_LEVEL;
	}
	else
	{
		if (result == Level::load_fail_file_not_found)
			return GWSTATUS_PLAYER_WON;
		if (result == Level::load_fail_bad_format)
			return GWSTATUS_LEVEL_ERROR;	
	}
	for (int i = 0; i < VIEW_HEIGHT; i++)
		for (int j = 0; j < VIEW_WIDTH; j++)
			switch (lev.getContentsOf(i,j))
			{
			case Level::empty: break;
			case Level::player:
				m_player = new Player(this,IID_PLAYER,i,j); break;
			case Level::perma_brick:
				m_worldObjects.push_back(new PermaBrick(this,IID_PERMA_BRICK,i,j)); break;
			case Level::destroyable_brick:
				m_worldObjects.push_back(new BreakBrick(this,IID_DESTROYABLE_BRICK,i,j)); break;
			case Level::simple_zumi:
				m_worldObjects.push_back(new Zumi(this,IID_SIMPLE_ZUMI,i,j)); break;
			case Level::complex_zumi:
				m_worldObjects.push_back(new ComplexZumi(this,IID_COMPLEX_ZUMI,i,j)); break;
			case Level::exit:
				m_worldObjects.push_back(new Exit(this,IID_EXIT,i,j)); break;
			}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

	for (unsigned int i = 0; i < m_worldObjects.size(); i++)
		if (!m_worldObjects[i]->isDead())
			m_worldObjects[i]->doSomething();
	if (!m_player->isDead())
		m_player->doSomething();
	return GWSTATUS_CONTINUE_GAME;
}
