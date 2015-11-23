#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

Actor* Actor::getActorAtPoint(int x, int y) const    //function is time consuming and uses many resources, causing lag
{													//will find another way if possible to reimplement
	list<Actor*>::iterator it;
	it = m_world->showBegin();
	while(it != m_world->showEnd())
	{
		if ((*it)->getX() == x && (*it)->getY() == y)
			return *it;
		it++;
	}

	return nullptr;
}

void Player::doSomething()
{
	if (isDead())
		return;
	int key = 0;

	if (m_simulOn)
	{
		if (m_sprayDuration == 0)
		{
			m_sprayMax = 2;
			m_simulOn = false;
		}
		m_sprayDuration--;
	}

	if (m_walkOn)
	{
		if (m_walkDuration == 0)
			m_walkOn = false;
		m_walkDuration--;
	}
	
	if (!m_walkOn)
	{
	Actor* aTarget = getActorAtPoint(getX(),getY());

		if (aTarget != nullptr)						//kills player if in brick after walk through buff fades
		{
			BreakBrick* target = dynamic_cast<BreakBrick*>(aTarget);
			if (target != nullptr)
				setDead();
		}
	}

	if (getWorld()->getKey(key))
	{
		//Move the player
		switch(key) 
		{
		case KEY_PRESS_LEFT: moveKey(getX()-1,getY()); break;
		case KEY_PRESS_UP: moveKey(getX(),getY()+1); break;
		case KEY_PRESS_RIGHT: moveKey(getX()+1,getY()); break;
		case KEY_PRESS_DOWN: moveKey(getX(),getY()-1); break;
		//Place a bug spray
		case KEY_PRESS_SPACE:
			{
				if (getWorld()->showPlayer()->usedSpray() == getWorld()->showPlayer()->maxSpray())
					return;

				Actor* aTarget = getActorAtPoint(getX(),getY());

				if (aTarget != nullptr)
				{
					Brick* bTarget = dynamic_cast<Brick*>(aTarget);
						if (bTarget != nullptr)
							break;
					BugSprayer* target = dynamic_cast<BugSprayer*>(aTarget);
						if (target == nullptr)
						{
							getWorld()->createBugSprayer(getX(), getY());
							getWorld()->showPlayer()->useSpray();
						}

				}
				else
				{
					getWorld()->createBugSprayer(getX(), getY());
					getWorld()->showPlayer()->useSpray();
				}
			}
			break;
		}
	}
}

//Checks if move is valid
bool Actor::moveKey(int x, int y)
{
	Actor* aTarget = getActorAtPoint(x, y);
	if (aTarget != nullptr)
	{
		Brick* bTarget = dynamic_cast<Brick*>(aTarget);
			if (bTarget == nullptr)
			{
				moveTo(x, y);
				return true;
			}
	}
	else
	{
		moveTo(x, y);
		return true;
	}
	return false;
}

bool Player::moveKey(int x, int y)
{
	if (!m_walkOn)
		Actor::moveKey(x, y);
	else
	{
		Actor* aTarget = getActorAtPoint(x, y);
		if (aTarget != nullptr)
		{
			PermaBrick* bTarget = dynamic_cast<PermaBrick*>(aTarget);
				if (bTarget == nullptr)
				{
					moveTo(x, y);
					return true;
				}
		}
		else
		{
			moveTo(x, y);
			return true;
		}
	}
	return false;
}

void BugSprayer::doSomething()
{
	if (isDead())
		return;
	decLifetime();
	if (isLife())
	{
		getWorld()->showPlayer()->dieSpray();
		getWorld()->createBugSpray(getX(), getY());
		sprayRange(getX(), getY());
		getWorld()->playSound(SOUND_SPRAY);
		setDead();
	}

}

void BugSprayer::sprayRange(int x, int y)
{
	for (int i = 1; i <= 2; i++)				//checks for bricks to right
	{
		Actor* aTarget = getActorAtPoint(x+i, y);
		if (aTarget != nullptr)
		{
			PermaBrick* target = dynamic_cast<PermaBrick*>(aTarget);
				if (target == nullptr)
					getWorld()->createBugSpray(x+i, y);
				else 
					break;
		}
		else
			getWorld()->createBugSpray(x+i, y);

		if (aTarget != nullptr)
		{
			Brick* target = dynamic_cast<Brick*>(aTarget);
				if (target != nullptr)
					break;
		}
	}

	for (int i = 1; i <= 2; i++)				//checks for bricks to left
	{
		Actor* aTarget = getActorAtPoint(x-i, y);
		if (aTarget != nullptr)
		{
			PermaBrick* target = dynamic_cast<PermaBrick*>(aTarget);
				if (target == nullptr)
					getWorld()->createBugSpray(x-i, y);
				else 
					break;
		}
		else
			getWorld()->createBugSpray(x-i, y);

		if (aTarget != nullptr)
		{
			Brick* target = dynamic_cast<Brick*>(aTarget);
				if (target != nullptr)
					break;
		}
	}

	for (int i = 1; i <= 2; i++)				//checks for bricks up
	{
		Actor* aTarget = getActorAtPoint(x, y+i);
		if (aTarget != nullptr)
		{
			PermaBrick* target = dynamic_cast<PermaBrick*>(aTarget);
				if (target == nullptr)
					getWorld()->createBugSpray(x, y+i);
				else 
					break;
		}
		else
			getWorld()->createBugSpray(x, y+i);

		if (aTarget != nullptr)
		{
			Brick* target = dynamic_cast<Brick*>(aTarget);
				if (target != nullptr)
					break;
		}
	}

	for (int i = 1; i <= 2; i++)				//checks for bricks down
	{
		Actor* aTarget = getActorAtPoint(x, y-i);
		if (aTarget != nullptr)
		{
			PermaBrick* target = dynamic_cast<PermaBrick*>(aTarget);
				if (target == nullptr)
					getWorld()->createBugSpray(x, y-i);
				else 
					break;
		}
		else
			getWorld()->createBugSpray(x, y-i);

		if (aTarget != nullptr)
		{
			Brick* target = dynamic_cast<Brick*>(aTarget);
				if (target != nullptr)
					break;
		}
	}
}

void BugSpray::doSomething()
{
	if (isDead())
		return;
	decLifetime();

	examineSpot(getX(), getY());

	if (isLife())
		setDead();
}

void BugSpray::examineSpot(int x, int y)
{
	if (getWorld()->showPlayer()->getX() == x && getWorld()->showPlayer()->getY() == y)
		getWorld()->showPlayer()->setDead();

	Actor* aTarget = getActorAtPoint(getX(),getY()); //calling this function causes lag due to multiple for loop runs
													 //will see if can improve
	if (aTarget != nullptr)
	{
		BreakBrick* bTarget = dynamic_cast<BreakBrick*>(aTarget); //Cast to see if destructable brick
			if (bTarget != nullptr)
			{
				bTarget->setDead();
			}

		Zumi* zTarget = dynamic_cast<Zumi*>(aTarget); //Cast to see if Zumi
			if (zTarget != nullptr)
			{
				zTarget->kill();
			}

		BugSprayer* bugTarget = dynamic_cast<BugSprayer*>(aTarget); //Cast to see if bugsprayer
			if (bugTarget != nullptr)
			{
				bugTarget->setLifetime(1);
			}
	}

}

void Zumi::doSomething()
{
	if (isDead())
		return;
	if (getX() == getWorld()->showPlayer()->getX() && getY() == getWorld()->showPlayer()->getY())
		 getWorld()->showPlayer()->setDead();
	move();
	if (m_killed == true)
	{
		setDead();
		getWorld()->decZCount();
		getWorld()->playSound(SOUND_ENEMY_DIE);
		getWorld()->increaseScore(100);
		dropGoodie();

	}

}

void Zumi::move()
{
	if (m_currentTick < m_ticksMove-1)
		m_currentTick++;
	else
	{
		switch (m_currentDirection)
		{
		case 0: 
			if(!moveKey(getX()-1, getY()))			//move left
				changeDir(); 
			break; 
		case 1: 
			if (!moveKey(getX(), getY()+1))			//move up
				changeDir();
			break; 
		case 2:
			if (!moveKey(getX()+1, getY()))			//move right
				changeDir(); 
			break; 
		case 3: 
			if(!moveKey(getX(), getY()-1))			//move down
				changeDir(); 
			break;
		}
		m_currentTick = 0;
	}
}

void ComplexZumi::move()
{
	if(!m_detectPlayer)
		Zumi::move();
	else
		if(!checkPath())
			{
				Zumi::move();
			}
		else
			Zumi::move();
}

void ComplexZumi::doSomething()
{
	m_detectPlayer = detectPlayer();
	Zumi::doSomething();
	if(isDead())
		getWorld()->increaseScore(400);		//does same thing as zumi do something except more points if dead
}

bool ComplexZumi::detectPlayer()
{
	if (getWorld()->showPlayer()->getX() - getX() <= m_smellDistance &&
		getWorld()->showPlayer()->getY() - getY() <= m_smellDistance)
		return true;
	else
		return false;
}

bool ComplexZumi::checkPath()
{
	char maze[VIEW_HEIGHT][VIEW_WIDTH];
	for (int i = 0; i < VIEW_HEIGHT; i++)
		for (int j = 0; j < VIEW_WIDTH; j++)
			maze[i][j] = '.';

	int playerX = getWorld()->showPlayer()->getX();
	int playerY = getWorld()->showPlayer()->getY();

	class Coord
	{
	public:
		Coord(int xx, int yy) : m_x(xx), m_y(yy) {}
		int x() const { return m_x; }
		int y() const { return m_y; }
	private:
		int m_x;
		int m_y;
	};

	queue<Coord> coordQueue;
	coordQueue.push(Coord(getX(), getY()));
	maze[getX()][getY()] = '#';
	
	while (!coordQueue.empty())
	{
		Coord current = coordQueue.front();
		if (current.x() == playerX && current.y() == playerY)				//return true if player found
			return true;
		coordQueue.pop();

		//East Check
		if (maze[current.x()+1][current.y()] == '.')						//if not marked, check if brick
		{
			Actor* eTarget = getActorAtPoint(current.x()+1, current.y());
			if (eTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(eTarget);				//if not a brick, push onto queue
				BugSprayer* btarget = dynamic_cast<BugSprayer*>(eTarget);
				if (target == nullptr && btarget == nullptr)
				{
					coordQueue.push(Coord(current.x()+1, current.y()));
					maze[current.x()+1][current.y()] = 'X';
				}
					else 
						maze[current.x()+1][current.y()] = '#';						//else mark on map as inaccessable
			}
			else
			{
				coordQueue.push(Coord(current.x()+1, current.y()));
				maze[current.x()+1][current.y()] = 'X';
			}
		}

		//South Check
		if (maze[current.x()][current.y()-1] == '.')						//if not marked, check if brick
		{
			Actor* sTarget = getActorAtPoint(current.x(), current.y()-1);
			if (sTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(sTarget);				//if not a brick, push onto queue
				BugSprayer* btarget = dynamic_cast<BugSprayer*>(sTarget);
				if (target == nullptr && btarget == nullptr)
				{
						coordQueue.push(Coord(current.x(), current.y()-1));
						maze[current.x()][current.y()-1] = 'X';
				}
					else 
						maze[current.x()][current.y()-1] = '#';						//else mark on map as inaccessable
			}
			else
			{
				coordQueue.push(Coord(current.x(), current.y()-1));
				maze[current.x()][current.y()-1] = 'X';
			}
		}

		//West Check
		if (maze[current.x()-1][current.y()] == '.')						//if not marked, check if brick
		{
			Actor* wTarget = getActorAtPoint(current.x()-1, current.y());
			if (wTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(wTarget);				//if not a brick, push onto queue
				BugSprayer* btarget = dynamic_cast<BugSprayer*>(wTarget);
				if (target == nullptr && btarget == nullptr)
				{
						coordQueue.push(Coord(getX()-1, current.y()));
						maze[current.x()-1][current.y()] = 'X';
				}
					else 
						maze[current.x()-1][current.y()] = '#';						//else mark on map as inaccessable
			}
			else
			{
				coordQueue.push(Coord(current.x()-1, current.y()));
				maze[current.x()-1][current.y()] = 'X';
			}
		}

		//North Check
		if (maze[current.x()][current.y()+1] == '.')						//if not marked, check if brick
		{
			Actor* nTarget = getActorAtPoint(current.x(), current.y()+1);
			if (nTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(nTarget);				//if not a brick, push onto queue
				BugSprayer* btarget = dynamic_cast<BugSprayer*>(nTarget);
				if (target == nullptr && btarget == nullptr)
				{
						coordQueue.push(Coord(current.x(), current.y()+1));
						maze[current.x()][current.y()+1] = 'X';
				}
					else 
						maze[current.x()][current.y()+1] = '#';						//else mark on map as inaccessable
			}
			else
			{
				coordQueue.push(Coord(current.x(), current.y()+1));
				maze[current.x()][current.y()+1] = 'X';
			}
		}
	}
	return false;
}

void Zumi::dropGoodie()
{
	if (randInt(0,100) < getWorld()->getChanceOfGoodie())
		{
			int rand = randInt(0,100); //Checks for the lowest/highest probabilities and checks rand to it.
			int life = getWorld()->getChanceOfLife();
			int simul = getWorld()->getChanceOfSimul();
			int walk = getWorld()->getChanceOfWalk();

			if (life <= simul && simul <= walk)
			{
				if (rand <= life)
					getWorld()->createExtraLifeGoodie(getX(), getY());
				else if (rand > life && rand <= life + simul)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
				else if (rand > simul)
					getWorld()->createWalkWallsGoodie(getX(), getY());
			}

			else if (life <= walk && walk <= simul)
			{
				if (rand <= life)
					getWorld()->createExtraLifeGoodie(getX(), getY());
				else if (rand > life && rand <= life + walk)
					getWorld()->createWalkWallsGoodie(getX(), getY());
				else if (rand > walk)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
			}

			else if (simul <= life && life <= walk)
			{
				if (rand <= simul)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
				else if (rand > simul && rand <= simul + life)
					getWorld()->createExtraLifeGoodie(getX(), getY());
				else if (rand > life)
					getWorld()->createWalkWallsGoodie(getX(), getY());
			}

			else if (walk <= life && life <= simul)
			{
				if (rand <= walk)
					getWorld()->createWalkWallsGoodie(getX(), getY());
				else if (rand > walk && rand <= walk + life)
					getWorld()->createExtraLifeGoodie(getX(), getY());
				else if (rand > life)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
			}

			else if (simul <= walk && walk <= life)
			{
				if (rand <= simul)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
				else if (rand > simul && rand <= simul + walk)
					getWorld()->createWalkWallsGoodie(getX(), getY());
				else if (rand > walk)
					getWorld()->createExtraLifeGoodie(getX(), getY());
			}

			else if (walk <= simul && simul <= life)
			{
				if (rand <= walk)
					getWorld()->createWalkWallsGoodie(getX(), getY());
				else if (rand > walk && rand <= walk + simul)
					getWorld()->createSimulSprayerGoodie(getX(), getY());
				else if (rand > simul)
					getWorld()->createExtraLifeGoodie(getX(), getY());
			}
		}
}

void Exit::doSomething()
{
	if (getWorld()->getWin() && !m_complete)  //reveals exit when all zumi dead
	{
		setVisible(true);
		getWorld()->playSound(SOUND_REVEAL_EXIT);
		m_complete = true;
	}

	if (getX() == getWorld()->showPlayer()->getX() && getY() == getWorld()->showPlayer()->getY() && m_complete)
	{
		getWorld()->playSound(SOUND_FINISHED_LEVEL);
		getWorld()->getOnExit();
	}

}

bool Zumi::moveKey(int x, int y)  //same as player except cannot walk through bugsprayers
{
	Actor* aTarget = getActorAtPoint(x, y);
	if (aTarget != nullptr)
	{
		Brick* bTarget = dynamic_cast<Brick*>(aTarget);
			if (bTarget != nullptr)
				return false;
		BugSprayer* bugTarget = dynamic_cast<BugSprayer*>(aTarget);
			if (bugTarget != nullptr)
				return false;
		moveTo(x, y);
		return true;
	}
	else
	{
		moveTo(x, y);
		return true;
	}
	return false;
}

void Goodie::doSomething()
{
		getWorld()->increaseScore(1000);
		getWorld()->playSound(SOUND_GOT_GOODIE);
		setDead();
}

void ExtraLifeGoodie::doSomething()
{
	if(isDead())
		return;

	decLifetime();

	if (getX() == getWorld()->showPlayer()->getX() && getY() == getWorld()->showPlayer()->getY())
	{
		getWorld()->incLives();
		Goodie::doSomething();
	}

	if (isLife())
		setDead();
}	

void SimulSprayerGoodie::doSomething()
{
	if(isDead())
		return;

	decLifetime();

	if (getX() == getWorld()->showPlayer()->getX() && getY() == getWorld()->showPlayer()->getY())
	{
		getWorld()->showPlayer()->setSprayDuration(getWorld()->getDurOfSimul());
		getWorld()->showPlayer()->boostSpray(getWorld()->getMaxSimul());
		getWorld()->showPlayer()->activateSimul();
		Goodie::doSomething();
	}

	if (isLife())
		setDead();
}

void WalkWallsGoodie::doSomething()
{
	if(isDead())
		return;

	decLifetime();

	if (getX() == getWorld()->showPlayer()->getX() && getY() == getWorld()->showPlayer()->getY())
	{
		getWorld()->showPlayer()->setWalkDuration(getWorld()->getDurOfWalk());
		getWorld()->showPlayer()->activateWalk();
		Goodie::doSomething();
	}

	if (isLife())
		setDead();
}