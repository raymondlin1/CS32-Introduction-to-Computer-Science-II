#include "StudentWorld.h"
#include <string>
#include "Actor.h"
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
	numDestroyed = 0;
	numShips = 0;
	numTorpedos = 0;
}

int StudentWorld::init()
{
	//create a NachenBlaster
	nb.push_back(new NachenBlaster(this));
	numDestroyed = 0;
	//create stars
	for (int i = 0; i < 30; i++)
	{
		double size = randInt(5, 50);
		actors.push_back(new Star(randInt(0, VIEW_WIDTH - 1), randInt(0, VIEW_HEIGHT - 1), size * 0.01, this));
	}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	//make nachenblaster do something
	vector<NachenBlaster*>::iterator nachenPointer = nb.begin();
	if ((*nachenPointer) != nullptr)
	{
		(*nachenPointer)->doSomething();
	}

	//determine if player has finished the level, add aliens accordingly
	int t = 6 + (4 * getLevel());
	int r = t - numDestroyed;
	if (r == 0)
	{
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}
	int max = 4 + (0.5 * getLevel());
	addAlien(r, max);

	//make all actors do something
	vector<Actor *>::iterator it = actors.begin();
	while (it != actors.end())
	{
		(*it)->doSomething();

		//loop through to check for collisions
		vector<Actor*>::iterator it2 = actors.begin();
		while (it2 != actors.end())
		{
			collided((*it), (*it2));
			it2++;
		}

		collided((*nachenPointer), (*it));
		//if anything is dead, delete it and erase it from the vector
		if ((*it)->getIsDead() == true)
		{
			delete (*it);
			it = actors.erase(it);
			
		}
		else {
			it++;
		}
	}

	//chance of spawning new star
	int temp = randInt(1, 15);
	if (temp == 5)
	{
		double size = randInt(5, 50);
		actors.push_back(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), size * 0.01, this));
	}

	//determine if nachenblaster is dead
	if ((*nachenPointer)->getHealth() <= 0)
	{
		decLives();
		setTorpedos(0);
		return GWSTATUS_PLAYER_DIED;
	}
	updateStatusText();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	//delete everything in actors vector and the NachenBlaster
	vector<Actor *>::iterator it = actors.begin();
	while (it != actors.end())
	{
		delete (*it);
		it = actors.erase(it);
	}

	vector<NachenBlaster *>::iterator np = nb.begin();
	delete (*np);
	np = nb.erase(np);
}

void StudentWorld::addCabbage(int x, int y)
{
	actors.push_back(new Cabbage(x, y, this));
}

void StudentWorld::addTorpedo(int x, int y, bool b)
{
	actors.push_back(new Torpedo(x, y, this, b));
}

StudentWorld::~StudentWorld()
{
	//if there are items in actors vector, delete all of them
	if (actors.size() > 0)
	{
		vector<Actor *>::iterator it = actors.begin();
		while (it != actors.end())
		{
			delete (*it);
			it = actors.erase(it);
		}
	}

	//delete the NachenBlaster
	if (nb.size() != 0)
	{
		vector<NachenBlaster *>::iterator ni = nb.begin();
		delete (*ni);
		ni = nb.erase(ni);
	}
}

void StudentWorld::addAlien(int r, int max)
{
	
	if (numShips < min(max, r))
	{
		int smallgon = 60;
		int smoregon = smallgon + (20 + 5 * getLevel());
		int snagglegon = smoregon + (5 + 10 * getLevel());

		int probability = randInt(1, snagglegon);

		if (probability <= smallgon)
		{
			int y = randInt(0, VIEW_HEIGHT - 1);
			actors.push_back(new Smallgon(VIEW_WIDTH - 1, y, this));
			numShips++;
		}
		else if (probability > smallgon && probability <= smoregon)
		{
			int y = randInt(0, VIEW_HEIGHT - 1);
			actors.push_back(new Smoregon(VIEW_WIDTH - 1, y, this));
			numShips++;
		} 
		else
		{
			int y = randInt(0, VIEW_HEIGHT - 1);
			actors.push_back(new Snagglegon(VIEW_WIDTH - 1, y, this));
			numShips++;
		}
		
	}
}

void StudentWorld::fireTurnip(int x, int y)
{
	actors.push_back(new Turnip(x, y, this));
}

int StudentWorld::getNumShips()
{
	return numShips;
}

void StudentWorld::setNumShips(int x)
{
	numShips = x;
}

void StudentWorld::incNumDestroyed()
{
	numDestroyed++;
}

int StudentWorld::getNachenX()
{
	vector<NachenBlaster*>::iterator it = nb.begin();
	return (*it)->getX();
}

int StudentWorld::getNachenY()
{
	vector<NachenBlaster*>::iterator it = nb.begin();
	return (*it)->getY();
}

void StudentWorld::updateStatusText()
{
	vector<NachenBlaster*>::iterator it = nb.begin();
	double temp = ((*it)->getHealth() / 50.0) * 100;
	int healthPercentage = temp;

	double temp2 = ((*it)->getCabbagePower() / 30.0) * 100;
	int cabbagePercentage = temp2;
	string status = string("Lives:") + to_string(getLives()) + "  Health:" + to_string(healthPercentage) + "%  Score:" + to_string(getScore()) + "  Level:" + to_string(getLevel()) + "  Cabbages:" + to_string(cabbagePercentage) + "%  Torpedos:" + to_string(getTorpedos());
	setGameStatText(status);
}

bool StudentWorld::collided(Actor* a1, Actor* a2)
{
	double x1 = a1->getX();
	double x2 = a2->getX();
	double y1 = a1->getY();
	double y2 = a2->getY();

	double dist = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	double temp = 0.75 * (a1->getRadius() + a2->getRadius());

	if (dist < temp)
	{
		if (a1->isProjectile() && a2->isDamageableObject())
		{
			if (a1->isEnemy() != a2->isEnemy())
			{
				playSound(SOUND_BLAST);
				a1->setIsDead(true);
				if (a1->getID() == IID_TORPEDO)
				{
					a2->changeHealth(8);
				}
				else if (a1->getID() == IID_TURNIP)
				{
					a2->changeHealth(2);
				}
				else if (a1->getID() == IID_CABBAGE)
				{
					a2->changeHealth(2);
				}
				return true;
			}
		}
		else if(a1->isNachenBlaster())
		{
			if (a1->isEnemy() != a2->isEnemy())
			{
				//a2 must be an enemy's projectile or an enemy
				
				if (a2->getID() == IID_TURNIP)
				{
					a2->setIsDead(true);
					a1->changeHealth(2);
					playSound(SOUND_BLAST);
				}
				else if (a2->getID() == IID_TORPEDO)
				{
					a2->setIsDead(true);
					a1->changeHealth(8);
					playSound(SOUND_BLAST);
				}
				else if (a2->getID() == IID_SMALLGON)
				{
					a1->changeHealth(5);
					a2->changeHealth(100);
					playSound(SOUND_DEATH);
				}
				else if (a2->getID() == IID_SMOREGON)
				{
					a1->changeHealth(5);
					a2->changeHealth(100);
					playSound(SOUND_DEATH);
				}
				else if (a2->getID() == IID_SNAGGLEGON)
				{
					a1->changeHealth(15);
					a2->changeHealth(100);
					playSound(SOUND_DEATH);
				}
				return true;
			}
			else if(a2->isGoodie())
			{
				a2->setIsDead(true);
				playSound(SOUND_GOODIE);
				if (a2->getID() == IID_REPAIR_GOODIE)
				{
					increaseScore(100);
					a1->changeHealth(-10);
				}
				else if (a2->getID() == IID_LIFE_GOODIE)
				{
					increaseScore(100);
					incLives();
				}
				else if (a2->getID() == IID_TORPEDO_GOODIE)
				{
					increaseScore(100);
					numTorpedos += 5;
				}
				return true;
			}
		}
	}
	else
	{
		return  false;
	}
}

void StudentWorld::addLifeGoodie(int x, int y)
{
	actors.push_back(new ExtraLifeGoodie(x, y, this));
}

void StudentWorld::addRepairGoodie(int x, int y)
{
	actors.push_back(new RepairGoodie(x, y, this));
}

void StudentWorld::addTorpedoGoodie(int x, int y)
{
	actors.push_back(new TorpedoGoodie(x, y, this));
}

int StudentWorld::getTorpedos()
{
	return numTorpedos;
}

void StudentWorld::fireTorpedo()
{
	numTorpedos--;
}

void StudentWorld::incTorpedos()
{
	numTorpedos += 5;
}

void StudentWorld::setTorpedos(int x)
{
	numTorpedos = x;
}

void StudentWorld::addExplosion(int x, int y)
{
	actors.push_back(new Explosion(x, y, this));
}