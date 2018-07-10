#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <vector>
#include <string>
using namespace std;

class NachenBlaster;
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();

	virtual ~StudentWorld();
	void addCabbage(int x, int y);
	void addTorpedo(int x, int y, bool b);
	void addAlien(int r, int max);
	void addLifeGoodie(int x, int y);
	void addRepairGoodie(int x, int y);
	void addTorpedoGoodie(int x, int y);
	int getNumShips();
	void setNumShips(int x);
	void fireTurnip(int x, int y);
	int getNachenX();
	int getNachenY();
	void updateStatusText();
	void collided(Actor* a1, Actor* a2);
	void incNumDestroyed();
	int getTorpedos();
	void setTorpedos(int x);
	void incTorpedos();
	void fireTorpedo();
	void addExplosion(int x, int y);
private:
	vector<Actor *> actors;
	vector<NachenBlaster *> nb;
	int numDestroyed;
	int numShips;
	int numTorpedos;
};

#endif // STUDENTWORLD_H_
