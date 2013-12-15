#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"
#include "moveableSprite.h"
#include "opfor.h"

Opfor::Opfor()
{
	health = 1;
	fireOffset = setFireOffset();
}
Opfor::Opfor(int sIndex, string sImage, int dist, 
			 int initHealth) : MoveableSprite(sIndex, sImage, dist)
{
	health = initHealth;
	active = true;
	fireOffset = setFireOffset();
}

int Opfor::getHealth()
{
	return health;
}

void Opfor::setHealth(int change)
{
	health = change;
}

void Opfor::decrementHealth()
{
	health--;
}

bool Opfor::getActive()
{
	return active;
}

void Opfor::setActive(bool change)
{
	active = change;
}

void Opfor::deactivate(int posX, int posY)
{
	active = false;
	setPosition(posX, posY);
}

int Opfor::setFireOffset()
{
	return agk::Random(0, FIRE_OFFSET_MAX);
}

int Opfor::getFireOffset()
{
	return fireOffset;
}