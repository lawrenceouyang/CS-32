#include "StudentWorld.h"
using namespace std;

GameWorld* createStudentWorld()
{
	return new StudentWorld();
}

int StudentWorld::init()	
{
	m_levelFin = false;
	m_onExit = false;

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
				m_worldObjects.push_front(new PermaBrick(this,IID_PERMA_BRICK,i,j)); break;
			case Level::destroyable_brick:
				m_worldObjects.push_back(new BreakBrick(this,IID_DESTROYABLE_BRICK,i,j)); break;
			case Level::simple_zumi:
				m_worldObjects.push_back(new Zumi(this,IID_SIMPLE_ZUMI,i,j, 
					lev.getOptionValue(optionTicksPerSimpleZumiMove))); m_zumiCount++; break;
			case Level::complex_zumi:
				m_worldObjects.push_back(new ComplexZumi(this,IID_COMPLEX_ZUMI,i,j, 
					lev.getOptionValue(optionTicksPerComplexZumiMove), 
					lev.getOptionValue(optionComplexZumiSearchDistance))); m_zumiCount++; break;
			case Level::exit:
				m_worldObjects.push_back(new Exit(this,IID_EXIT,i,j)); break;
			}

	setBonus(lev.getOptionValue(optionLevelBonus));
	m_chanceOfGoodie = lev.getOptionValue(optionProbOfGoodieOverall);
	m_probOfLifeGoodie = lev.getOptionValue(optionProbOfExtraLifeGoodie);
	m_probOfSimulGoodie = lev.getOptionValue(optionProbOfMoreSprayersGoodie);
	m_probOfWalkGoodie = lev.getOptionValue(optionProbOfWalkThruGoodie);
	m_durationOfGoodie = lev.getOptionValue(optionGoodieLifetimeInTicks);
	m_durOfSimulGoodie = lev.getOptionValue(optionBoostedSprayerLifetimeTicks);
	m_durOfWalkGoodie = lev.getOptionValue(optionWalkThruLifetimeTicks);
	m_maxSimulGoodie = lev.getOptionValue(optionMaxBoostedSprayers);
	m_CZumiSearchRange = lev.getOptionValue(optionComplexZumiSearchDistance);

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setGameStatText(getStats());
	if (getBonus() > 0)
		setBonus(getBonus()-1);

	list<Actor*>::iterator it;
	it = m_worldObjects.begin();
	while(it != m_worldObjects.end())
	{
		if (!(*it)->isDead())
			(*it)->doSomething();
		it++;
	}

	it = m_worldObjects.begin();
	while(it != m_worldObjects.end())
	{
		if ((*it)->isDead())
		{
			delete *it;
			it = m_worldObjects.erase(it);
		}
		else
			it++;
	}

	if (!m_player->isDead())
		m_player->doSomething();
	else
	{
		decLives();
		playSound(SOUND_PLAYER_DIE);
		return GWSTATUS_PLAYER_DIED;
	}

	if (m_zumiCount <= 0 && !m_levelFin)
	{
		m_levelFin = true;
	}

	if (m_onExit)
	{
		increaseScore(m_bonus);
		return GWSTATUS_FINISHED_LEVEL;
	}

	return GWSTATUS_CONTINUE_GAME;
}

string StudentWorld::getStats()
{
	std::ostringstream ossScore;
	std::ostringstream ossLevel;
	std::ostringstream ossLives;
	std::ostringstream ossBonus;
	std::string s;

	int score = getScore();
	int level = getLevel();
	int lives = getLives();
	int bonus = getBonus();

	ossScore.fill('0');
	ossScore << setw(8) << score;

	ossLevel.fill('0');
	ossLevel << setw(2) << level;

	ossLives.fill('0');
	ossLives << setw(3) << lives;

	ossBonus << setw(5) << bonus;


	return ("Score: " + ossScore.str() + "  " + "Level: " + ossLevel.str() + "  " + 
		"Lives: " + ossLives.str() + "  " + "Bonus: " + ossBonus.str());
}

