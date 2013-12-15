#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"

// This is the default constructor for the Sprite
// class. It sets index to 1 and imageFile to
// an empty string.
Sprite::Sprite()
{
   spriteIndex = 1;
   imageFile = "";
}

// This Sprite class constructor accepts as arguments
// the sprite index and the name of the image file,
// and initializes the member variables.
Sprite::Sprite(int index, string filename)
{
   spriteIndex = index;
   imageFile = filename;
}

// The Sprite::createSprite member function 
void Sprite::createSprite()
{
   // If the sprite does not already exist,
   // then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
   }
}

// The Sprite::createSprite member function 
void Sprite::createSprite(int index, string filename)
{
   // Set the member variables.
   spriteIndex = index;
   imageFile = filename;

   // If the sprite does not already exist,
   // then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
   }
}

// The Sprite::setPosition member function sets the
// sprite's position.
void Sprite::setPosition(float x, float y)
{
   agk::SetSpritePosition(spriteIndex, x, y);
}

// The Sprite::setX member function sets the
// sprite's X coordinate.
void Sprite::setX(float x)
{
   agk::SetSpriteX(spriteIndex, x);
}

// The Sprite::setY member function sets the
// sprite's Y coordinate.
void Sprite::setY(float y)
{
   agk::SetSpriteY(spriteIndex, y);
}

// The Sprite::setImage member function
// sprite's image
void Sprite::setImage(int imgIndex)
{
	agk::SetSpriteImage(spriteIndex, imgIndex);
}

// The Sprite::getSpriteIndex member function
// returns the sprite's index.
int Sprite::getSpriteIndex() const
{
   return spriteIndex;
}

// The Sprite::getImageFile member function
// returns the name of the image file used to 
// create this sprite.
string Sprite::getImageFile() const
{
   return imageFile;
}

// The Sprite::getX member function returns the
// sprite's X coordinate.
float Sprite::getX() const
{
   return agk::GetSpriteX(spriteIndex);
}

// The Sprite::getY member function returns the
// sprite's Y coordinate.
float Sprite::getY() const
{
   return agk::GetSpriteY(spriteIndex);
}

float Sprite::getWidth() const
{
	return agk::GetSpriteWidth(spriteIndex);
}

float Sprite::getHeight() const
{
	return agk::GetSpriteHeight(spriteIndex);
}

float Sprite::getCenterX() const
{
	return getX() + (getWidth() / 2);
}

float Sprite::getCenterY() const
{
	return getY() + (getHeight() / 2);
}

// The Sprite class destructor deletes the
// sprite from memory.
Sprite::~Sprite()
{
   agk::DeleteSprite(spriteIndex);
}
