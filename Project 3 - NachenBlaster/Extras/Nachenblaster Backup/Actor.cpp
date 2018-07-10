#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <iostream>
using namespace std;

bool collided(Actor *a1, Actor *a2)
{
	int d = sqrt(((a1->getX() - a2->getX()) * (a1->getX() - a2->getX())) + ((a1->getY() - a2->getY())*(a1->getY() - a2->getY())));
	if (d < 0.75 * (a1->getRadius() + a2->getRadius()))
	{
		return true;
	}
	return false;
}

bool Actor::getIsDead() const
{
	return isDead;
}

void Actor::setIsDead(bool in)
{
	isDead = in;
}

int Actor::getID()
{
	return id;
}

void Star::doSomething()
{
	double curx = getX();
	double cury = getY();
	moveTo(curx - 1, cury);
	if (getX() <= -1)
	{
		setIsDead(true);
	}
}

void Explosion::doSomething()
{
	setSize(getSize() * 1.5);
	if (getSize() > 5)
		setIsDead(true);
}

int DamageableObject::getHealth()
{
	return hp;
}

void NachenBlaster::doSomething()
{
	if (getHealth() <= 0)
	{
		setIsDead(true);
		return;
	}

	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case 's':
		case KEY_PRESS_DOWN:
			if(getY() - 6 >= 0)
				moveTo(getX(), getY() - 6);
			break;
		case 'a':
		case KEY_PRESS_LEFT:
			if(getX() - 6 >= 0)
				moveTo(getX() - 6, getY());
			break;
		case 'd':
		case KEY_PRESS_RIGHT:
			if(getX() + 6 <= VIEW_WIDTH)
				moveTo(getX() + 6, getY());
			break;
		case 'w':
		case KEY_PRESS_UP:
			if(getY() + 6 <= VIEW_HEIGHT)
				moveTo(getX(), getY() + 6);
			break;
		case KEY_PRESS_SPACE:
			if (cp >= 5)
			{
				getWorld()->addCabbage(getX() + 6, getY());
				getWorld()->playSound(SOUND_PLAYER_SHOOT);
				cp -= 5;
			}
			break;
		case KEY_PRESS_TAB:
			if (getWorld()->getTorpedos() > 0)
			{
				getWorld()->addTorpedo(getX() + 14, getY(), false);
				getWorld()->fireTorpedo();
				getWorld()->playSound(SOUND_TORPEDO);
			}
			break;
		default:
			break;
		}
	}

	if (cp < 30)
	{
		cp++;
	}

	if (getHealth() <= 0)
	{
		setIsDead(true);
	}
}

int NachenBlaster::getCabbagePower()
{
	return cp;
}

void DamageableObject::changeHealth(int x)
{
	hp -= x;
	if (hp > 50)
		hp = 50;
}

void Goodies::doSomething()
{
	//check if goodie is dead, check if goodie has gone past screen. if not, move it
	if (getIsDead())
	{
		return;
	}

	if (getX() >= VIEW_WIDTH)
	{
		setIsDead(true);
		return;
	}

	moveTo(static_cast<double>(getX()) - 0.75, static_cast<double>(getY()) - 0.75);
}

void Cabbage::doSomething()
{
	if (getIsDead() == false)
	{
		if (getX() >= VIEW_WIDTH)
		{
			setIsDead(true);
			return;
		}
		
		move();
	}
	else 
	{
		return;
	}
}

void Cabbage::move()
{
	moveTo(getX() + 8, getY());
	setDirection(getDirection() + 20);
}

void Turnip::doSomething()
{
	//check if turnip is dead
	if (getIsDead() == true)
	{
		return;
	}
	//check if it has gone past the screen
	if (getX() < 0)
	{
		setIsDead(true);
		return;
	}

	//move
	move();
}

void Turnip::move()
{
	moveTo(getX() - 6, getY());
	setDirection(getDirection() + 20);
}

void Torpedo::doSomething()
{
	//check if smallgon is dead
	if (getIsDead() == true)
	{
		return;
	}
	//check if it has gone past the screen
	if (getX() < 0 || getX() > VIEW_WIDTH)
	{
		setIsDead(true);
		return;
	}

	//move
	move();
}

void Torpedo::move()
{
	if (isEnemy())
	{
		moveTo(getX() - 8, getY());
	}
	else
	{
		moveTo(getX() + 8, getY());
	}
}

bool Torpedo::isEnemy()
{
	return enemy;
}

StudentWorld *Actor::getWorld()
{
	return world;
}

void Alien::doSomething()
{
	//check if smallgon is dead
	if (getHealth() <= 0)
	{
		getWorld()->addExplosion(getX(), getY());
		dropSomething();
		getWorld()->incNumDestroyed();
		getWorld()->increaseScore(getScore());
		getWorld()->playSound(SOUND_DEATH);
		setIsDead(true);
		return;
	}

	//check if it has gone past the screen
	if (getX() < 0)
	{
		setIsDead(true);
		return;
	}

	//check collided

	//check if needs a new flight path
	if (getFPL() <= 0 || getY() >= VIEW_HEIGHT - 1 || getY() <= 0)
	{

		if (getY() >= VIEW_HEIGHT - 1)
		{
			setTravDir(1);
		}
		else if (getY() <= 0)
		{
			setTravDir(2);
		}
		else
		{
			int temp = randInt(0, 2);
			switch (temp)
			{
			case 0:
				setTravDir(3);
				break;
			case 1:
				setTravDir(2);
				break;
			case 2:
				setTravDir(1);
				break;
			default:
				break;
			}

			int x = randInt(1, 32);
			setFPL(x);
		}
	}

	//check to shoot at nachenblaster
	shoot();

	//move the object
	if (getTravDir() == 3)
	{
		moveTo(getX() - getTravelSpeed(), getY());
		setFPL(getFPL() - 1);
	}
	else if (getTravDir() == 2)
	{
		moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
		setFPL(getFPL() - 1);
	}
	else if (getTravDir() == 1)
	{
		moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
		setFPL(getFPL() - 1);
	}
}

int Alien::getFPL()
{
	return flightPlanLength;
}

void Alien::setFPL(int x)
{
	flightPlanLength = x;
}

double Alien::getTravelSpeed()
{
	return travelSpeed;
}

void Alien::setTravelSpeed(int x)
{
	travelSpeed = x;
}

int Alien::getTravDir()
{
	return travDir;
}

void Alien::setTravDir(int x)
{
	travDir = x;
}

Alien::~Alien()
{
	getWorld()->setNumShips(getWorld()->getNumShips() - 1);
}

void Smoregon::shoot()
{
	if (getWorld()->getNachenX() < getX() && abs((getWorld()->getNachenY()) - getY()) <= 4)
	{
		int chance = (20 / getWorld()->getLevel()) + 5;
		int random = randInt(0, chance);

		if (random == 1)
		{
			//fire a turnip
			getWorld()->fireTurnip(getX() - 14, getY());
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}

		//ramming mode
		if (random == 0)
		{
			setTravDir(3);
			setFPL(VIEW_WIDTH);
			setTravelSpeed(5);
		}
	}
}

void Smoregon::dropSomething()
{
	int chance = randInt(0, 2);
	int chance2 = randInt(1, 2);
	switch (chance)
	{
	case 1:
		if (chance2 == 1)
			getWorld()->addTorpedoGoodie(getX(), getY());
		else
			getWorld()->addRepairGoodie(getX(), getY());
		break;
	default:
		break;
	}
}

void Smallgon::shoot()
{
	if (getWorld()->getNachenX() < getX() && abs((getWorld()->getNachenY()) - getY()) <= 4)
	{
		int chance = (20 / getWorld()->getLevel()) + 5;
		int random = randInt(0, chance);

		if (random == 1)
		{
			//fire a turnip
			getWorld()->fireTurnip(getX() - 14, getY());
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
	}
}

void Snagglegon::shoot()
{
	if (getWorld()->getNachenX() < getX() && abs((getWorld()->getNachenY()) - getY()) <= 4)
	{
		int chance = (15 / getWorld()->getLevel()) + 5;
		int random = randInt(0, chance);

		if (random == 1)
		{
			getWorld()->addTorpedo(getX() - 14, getY(), true);
			getWorld()->playSound(SOUND_TORPEDO);
			return;
		}
	}
}

void Snagglegon::dropSomething()
{
	int chance = randInt(0, 5);

	switch (chance)
	{
	case 1:
		getWorld()->addLifeGoodie(getX(), getY());
		break;
	default:
		break;
	}
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
