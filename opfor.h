#pragma once
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;

class Opfor : public MoveableSprite
{
private:
	static const int FIRE_OFFSET_MAX = 100;
	int health, fireOffset;
	bool active;
	int setFireOffset();

public:
	// Constructors
	Opfor();
	Opfor(int sIndex, string sImage, int dist, int initHealth);

	// Mutators and accessors
	int getHealth();
	bool getActive();
	void setHealth(int change);
	void decrementHealth();
	void setActive(bool);
	void deactivate(int posX, int posY);
	int getFireOffset();
};
