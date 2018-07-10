#ifndef GAME_H

#define GAME_H
class City;

int decodeDirection(char dir);

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

private:
	City* m_city;

};

#endif