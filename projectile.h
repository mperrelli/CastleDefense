#pragma once
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;

class Projectile : public MoveableSprite
{
private:
	int strength, deltaY, deltaX, type;
	bool active;

public:
	// Constructors
	Projectile();
	Projectile(int sIndex, string sImage, int dist, int str, int dx, int dy);

	// Mutators and accessors
	int getStrength();
	int getDeltaX();
	int getDeltaY();
	bool getActive();
	void setStrength(int change);
	void setTrajectory(int dx, int dy);
	void deactivate(int posX, int posY);
	void setActive();
	void setType(int);
	int getType();
	
	// Move projectile
	void advanceProjectile();
};
