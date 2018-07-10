#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld *p)
		:GraphObject(imageID, startX, startY, startDirection, size, depth)
	{
		isDead = false;
		world = p;
		id = imageID;
	}

	virtual void doSomething() = 0;
	virtual bool isEnemy() = 0;
	virtual bool isProjectile() = 0;
	virtual bool isDamageableObject() = 0;
	virtual bool isNachenBlaster() = 0;
	virtual bool isGoodie() = 0;
	bool getIsDead() const;
	void setIsDead(bool in);
	StudentWorld *getWorld();
	int getID();
	
	virtual void changeHealth(int x)
	{
	}
private:
	int id;
	bool isDead;
	StudentWorld *world;
};

class Star : public Actor
{
public:
	Star(int startX, int startY, double size, StudentWorld* p)
		:Actor(IID_STAR, startX, startY, 0, size, 3, p)
	{

	}

	virtual void doSomething();
	virtual bool isEnemy()
	{
		return false;
	}
	virtual bool isProjectile()
	{
		return false;
	}
	virtual bool isDamageableObject()
	{
		return false;
	}
	virtual bool isNachenBlaster()
	{
		return false;
	}
	virtual bool isGoodie()
	{
		return false;
	}
};

class Explosion: public Actor
{
public:
	Explosion(int startX, int startY, StudentWorld* p)
		:Actor(IID_EXPLOSION, startX, startY, 0, 1, 0, p)
	{
		
	}
	virtual void doSomething();
	virtual bool isEnemy()
	{
		return false;
	}
	virtual bool isProjectile()
	{
		return false;
	}
	virtual bool isDamageableObject()
	{
		return false;
	}
	virtual bool isNachenBlaster()
	{
		return false;
	}
	virtual bool isGoodie()
	{
		return false;
	}
};

class Goodies :public Actor
{
public:
	Goodies(int id, int startX, int startY, StudentWorld* p)
		:Actor(id, startX, startY, 0, 0.5, 1, p)
	{

	}
	virtual void doSomething();
	virtual bool isEnemy()
	{
		return false;
	}
	virtual bool isProjectile()
	{
		return false;
	}
	virtual bool isDamageableObject()
	{
		return false;
	}
	virtual bool isNachenBlaster()
	{
		return false;
	}
	virtual bool isGoodie()
	{
		return true;
	}
};

class ExtraLifeGoodie :public Goodies
{
public:
	ExtraLifeGoodie(int startX, int startY, StudentWorld* p)
		:Goodies(IID_LIFE_GOODIE, startX, startY, p)
	{
	}
};

class RepairGoodie :public Goodies
{
public:
	RepairGoodie(int startX, int startY, StudentWorld* p)
		:Goodies(IID_REPAIR_GOODIE, startX, startY, p)
	{
	}
};

class TorpedoGoodie :public Goodies
{
public:
	TorpedoGoodie(int startX, int startY, StudentWorld* p)
		:Goodies(IID_TORPEDO_GOODIE, startX, startY, p)
	{
	}
};

class Projectile : public Actor
{
public:
	Projectile(int id, int startX, int startY, StudentWorld* p)
		:Actor(id, startX, startY, 0, 0.5, 1, p)
	{

	}
	virtual void doSomething() = 0;
	virtual bool isEnemy() = 0;
	virtual void move() = 0;
	virtual bool isProjectile()
	{
		return true;
	}
	virtual bool isDamageableObject()
	{
		return false;
	}
	virtual bool isNachenBlaster()
	{
		return false;
	}
	virtual bool isGoodie()
	{
		return false;
	}
};

class Cabbage :public Projectile
{
public:
	Cabbage(int startX, int startY, StudentWorld* p)
		:Projectile (IID_CABBAGE, startX, startY, p)		//id, x, y, dir, size, depth, world
	{

	}
	virtual void doSomething();
	virtual void move();
	virtual bool isEnemy()
	{
		return false;
	}
};

class Turnip :public Projectile
{
public:
	Turnip(int startX, int startY, StudentWorld* p)
		:Projectile(IID_TURNIP, startX, startY, p)
	{

	}
	virtual void doSomething();
	virtual void move();
	virtual bool isEnemy()
	{
		return true;
	}
};

class Torpedo :public Projectile
{
public:
	Torpedo(int startX, int startY, StudentWorld* p, bool e)
		:Projectile(IID_TORPEDO, startX, startY, p)		//id, x, y, dir, size, depth, world
	{
		enemy = e;
	}
	virtual void doSomething();
	virtual void move();
	virtual bool isEnemy();
private:
	bool enemy;
};

class DamageableObject : public Actor
{
public:
	DamageableObject(int id, int startX, int startY, StudentWorld *p, int health, int depth, double size)		//ID, X, Y, WORLD, HP, DEPTH, SIZE
		:Actor(id, startX, startY, 0, size, depth, p)		//ID, XCOORD, YCOORD, DIR, SIZE, DEPTH, WORLD
	{
		hp = health;
	}
	int getHealth();
	virtual void changeHealth(int x);
	virtual void doSomething() = 0;
	virtual bool isNachenBlaster() = 0;
	virtual bool isProjectile()
	{
		return false;
	}
	virtual bool isDamageableObject()
	{
		return true;
	}
	virtual bool isGoodie()
	{
		return false;
	}
private:
	int hp;
};

class NachenBlaster : public DamageableObject
{
public:
	NachenBlaster(StudentWorld* p)
		:DamageableObject(IID_NACHENBLASTER, 0, 128, p, 50, 0, 1.0)
	{
		cp = 30;
	}

	virtual void doSomething();
	int getCabbagePower();

	virtual bool isEnemy()
	{
		return false;
	}
	virtual bool isNachenBlaster()
	{
		return true;
	}
	
private:
	int cp;
};

class Alien : public DamageableObject
{
public:
	Alien(int id, int startX, int startY, StudentWorld *p, int health, double ts, int fpl, int td)		//ID, X, Y, WORLD, HP, SPEED, FPL, TRAVDIR
		:DamageableObject(id, startX, startY, p, health, 1, 1.5)		//ID, XCOORD, YCOORD, WORLD, DEPTH
	{
		travelSpeed = ts;
		flightPlanLength = fpl;
		travDir = td;
	}

	virtual bool isEnemy() 
	{
		return true;
	}
	virtual bool isNachenBlaster()
	{
		return false;
	}
	virtual void doSomething();
	virtual void shoot() = 0;
	virtual int getScore() = 0;
	virtual void dropSomething()
	{
	}
	int getFPL();
	void setFPL(int x);
	double getTravelSpeed();
	void setTravelSpeed(int x);
	int getTravDir();
	void setTravDir(int x);
	virtual ~Alien();
private:
	double travelSpeed;
	int flightPlanLength;
	int travDir;			//1 = down and left, 2 = up and left, 3 = straight left
};

class Smallgon : public Alien
{
public:
	Smallgon(int x, int y, StudentWorld *p)
		:Alien(IID_SMALLGON, x, y, p, (5*(1+(p->getLevel() - 1) * 0.1)), 2.0, 0, 3)
		//ID, X, Y, WORLD, HP, SPEED, FPL
	{

	}
	virtual void shoot();
	virtual int getScore()
	{
		return 250;
	}
};

class Smoregon : public Alien
{
public:
	Smoregon(int x, int y, StudentWorld *p)
		:Alien(IID_SMOREGON, x, y, p, (5 * (1 + (p->getLevel() - 1) * 0.1)), 2.0, 0, 3)
		//ID, X, Y, WORLD, HP, SPEED, FPL
	{

	};
	virtual void shoot();
	virtual void dropSomething();
	virtual int getScore() 
	{
		return 250;
	}
};

class Snagglegon : public Alien
{
public:
	Snagglegon(int x, int y, StudentWorld *p)
		:Alien(IID_SNAGGLEGON, x, y, p, (10 * (1 + (p->getLevel() - 1) * 0.1)), 1.75, 0, 1)
		//ID, X, Y, WORLD, HP, SPEED, FPL
	{

	}
	virtual void shoot();
	virtual void dropSomething();
	virtual int getScore()
	{
		return 1000;
	}
};
#endif // ACTOR_H_
