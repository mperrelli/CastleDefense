#pragma once
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;

class MoveableSprite : public Sprite
{
private:
   int distance;
public:
   // Constructors
   MoveableSprite();
   MoveableSprite(int, string, int);

   // Mutators and accessors
   void setDistance(int);
   int getDistance() const;

   // Functions to move the sprite
   void moveUp();
   void moveDown();
   void moveLeft();
   void moveRight();
};