#include "Actor.h"
#include "StudentWorld.h"

Actor* Actor::getActorAtPoint(int x, int y)
{
	std::vector<Actor*> temp = m_world->showObjects();
	for (unsigned int i = 0; i < temp.size();i++)
		if (temp[i]->getX() == x && temp[i]->getY() == y)
			return temp[i];

	return nullptr;
}

void Player::doSomething()
{
	if (isDead())
		return;
	int key = 0;
	if (getWorld()->getKey(key))

		if (key == KEY_PRESS_LEFT)
		{
			Actor* aTarget = getActorAtPoint(getX()-1,getY());
			if (aTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(aTarget);
					if (target == nullptr)
						moveTo(getX()-1,getY());
			}
			else
				moveTo(getX()-1,getY());
		}

		if (key == KEY_PRESS_UP)
		{
			Actor* aTarget = getActorAtPoint(getX(),getY()+1);
			if (aTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(aTarget);
					if (target == nullptr)
						moveTo(getX(),getY()+1);
			}
			else
				moveTo(getX(),getY()+1);
		}

		if (key == KEY_PRESS_RIGHT)
		{
			Actor* aTarget = getActorAtPoint(getX()+1,getY());
			if (aTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(aTarget);
					if (target == nullptr)
						moveTo(getX()-1,getY());
			}
			else
				moveTo(getX()+1,getY());
		}

		if (key == KEY_PRESS_DOWN)
		{
			Actor* aTarget = getActorAtPoint(getX(),getY()-1);
			if (aTarget != nullptr)
			{
				Brick* target = dynamic_cast<Brick*>(aTarget);
					if (target == nullptr)
						moveTo(getX(),getY()-1);
			}
			else
				moveTo(getX(),getY()-1);
		}
}