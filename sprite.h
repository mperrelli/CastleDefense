#pragma once
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;

class Sprite
{
private:
   int spriteIndex;  // The sprite index
   string imageFile; // The name of the image file
public:
   // Constructors
   Sprite();
   Sprite(int, string);

   // Mutators
   void createSprite();
   void createSprite(int, string);
   void setImage(int);
   void setPosition(float, float);
   void setX(float);
   void setY(float);

   // Accessors
   int getSpriteIndex() const;
   string getImageFile() const;
   float getX() const;
   float getY() const;
   float getWidth() const;
   float getHeight()const;
   float getCenterX() const;
   float getCenterY() const;

   // Destructor
   ~Sprite();
};