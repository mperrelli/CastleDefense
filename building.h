#pragma once
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;

class Building : public Sprite
{
private:
	static const int FIRE_OFFSET_MAX = 100;
	int mapIndex, angle, deltaX, deltaY, bType, fireOffset;
	void updateTrajectory();
	int setFireOffset();

public:
	// Constructors
	Building();
	Building(int, string, int, int);

	// Mutators and accessors
	int getMapIndex();
	int getType();
	int setType(int type);
	void setMapIndex(int pos);
	int getDeltaX();
	int getDeltaY();
	int getFireOffset();

	// Rotations
	void rotateCCW();
	void rotateCW();
};
