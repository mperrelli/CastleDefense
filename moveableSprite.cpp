#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"
#include "moveableSprite.h"

MoveableSprite::MoveableSprite() : Sprite()
{
   distance = 0;
}

// This constructor accepts arguments for the sprite
// index, image file name, and distance to move.
MoveableSprite::MoveableSprite(int index, string filename,
               int dist) : Sprite(index, filename)
{
   distance = dist;
}

// The setDistance member function sets
// the moving distance.
void MoveableSprite::setDistance(int dist)
{
   distance = dist;
}

// The getDistance member function returns the
// sprite's moving distance.
int MoveableSprite::getDistance() const
{
   return distance;
}

// The moveUp member function moves the sprite up.
void MoveableSprite::moveUp()
{
   // Get the sprite's current coordinates.
   int x = getX();
   int y = getY();

   // Decrease y.
   y -= distance;

   // Move the sprite to its new location.
   setY(y);
}

// The moveDown member function moves the sprite down.
void MoveableSprite::moveDown()
{
   // Get the sprite's current coordinates.
   int x = getX();
   int y = getY();

   // Increase y.
   y += distance;

   // Move the sprite to its new location.
   setY(y);
}

// The moveLeft member function moves the sprite left.
void MoveableSprite::moveLeft()
{
   // Get the sprite's current coordinates.
   int x = getX();
   int y = getY();

   // Decrease x.
   x -= distance;

   // Move the sprite to its new location.
   setX(x);
}

// The moveRight member function moves the sprite right.
void MoveableSprite::moveRight()
{
   // Get the sprite's current coordinates.
   int x = getX();
   int y = getY();

   // Increase x.
   x += distance;

   // Move the sprite to its new location.
   setX(x);
}