#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"
#include "moveableSprite.h"
#include "projectile.h"

Projectile::Projectile()
{
	strength = 1;
	deltaX = 1;
	deltaY = 1;
	active = true;
	type = 1;
}
Projectile::Projectile(int sIndex, string sImage, int dist, 
			int str, int dx, int dy) : MoveableSprite(sIndex, 
									   sImage, dist)
{
	strength = str;
	deltaY = dy;
	deltaX = dx;
	active = true;
	type = 1;
}

int Projectile::getStrength()
{
	return strength;
}

void Projectile::setStrength(int change)
{
	strength = change;
}

void Projectile::setTrajectory(int dx, int dy)
{
	deltaX = dx;
	deltaY = dy;
}

int Projectile::getDeltaX()
{
	return deltaX;
}

int Projectile::getDeltaY()
{
	return deltaY;
}

void Projectile::advanceProjectile()
{
	int distance = getDistance();

	float currX = getX();
	float currY = getY();
	
	float posX = currX + (deltaX * distance);
	float posY = currY + (deltaY * distance);

	setX(posX);
	setY(posY);
}

void Projectile::deactivate(int posX, int posY)
{
	active = false;
	setPosition(posX, posY);
}
void Projectile::setActive()
{
	active = true;
}

bool Projectile::getActive()
{
	return active;
}

void Projectile::setType(int pType)
{
	type = pType;
}

int Projectile::getType()
{
	return type;
}