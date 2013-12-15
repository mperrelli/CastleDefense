#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"
#include "building.h"

Building::Building() : Sprite()
{
	mapIndex = 0;
	angle = 0;
	bType = 1;
	fireOffset = setFireOffset();
	updateTrajectory();
}

Building::Building(int index, string filename,
               int mIndex, int type) : Sprite(index, filename)
{
	mapIndex = mIndex;
	bType = type;
	fireOffset = setFireOffset();
	updateTrajectory();
}

int Building::getMapIndex()
{
	return mapIndex;
}

int Building::getType()
{
	return bType;
}

int Building::setType(int type)
{
	return bType = type;
}

void Building::setMapIndex(int mIndex)
{
	mapIndex = mIndex;
}

void Building::rotateCCW()
{
	angle += 45;

	if(angle >= 360)
	{
		angle = 0;
	}

	agk::SetSpriteAngle(getSpriteIndex(), angle);
	updateTrajectory();
}

void Building::rotateCW()
{
	angle -= 45;

	if(angle <= 0)
	{
		angle = 360;
	}

	agk::SetSpriteAngle(getSpriteIndex(), angle);
	updateTrajectory();
}

void Building::updateTrajectory()
{
	switch(angle)
	{
	case 0:
		deltaX = 0;
		deltaY = 1;
		break;
	case 45:
		deltaX = -1;
		deltaY = 1;
		break;
	case 90:
		deltaX = -1;
		deltaY = 0;
		break;
	case 135:
		deltaX = -1;
		deltaY = -1;
		break;
	case 180:
		deltaX = 0;
		deltaY = -1;
		break;
	case 225:
		deltaX = 1;
		deltaY = -1;
		break;
	case 270:
		deltaX = 1;
		deltaY = 0;
		break;
	case 315:
		deltaX = 1;
		deltaY = 1;
		break;
	case 360:
		deltaX = 0;
		deltaY = 1;
		break;
	}
}

int Building::getDeltaX()
{
	return deltaX;
}

int Building::getDeltaY()
{
	return deltaY;
}

int Building::setFireOffset()
{
	return agk::Random(0, FIRE_OFFSET_MAX);
}

int Building::getFireOffset()
{
	return fireOffset;
}