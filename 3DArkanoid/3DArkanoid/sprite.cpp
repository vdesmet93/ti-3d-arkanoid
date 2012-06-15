#include "sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(float x, float y)
{
	this->x = x;
	this->y = y;
}

Sprite::Sprite(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Sprite::Sprite(float x, float y, float z, float w, float h, float d)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
}

bool Sprite::intersects(const Sprite& anotherSprite)
{
	float aX = x;
	float aY = y;
	float aX2 = x+w;
	float aY2 = y+h;
	float bX = anotherSprite.x;
	float bY = anotherSprite.y;
	float bX2 = anotherSprite.x+anotherSprite.w;
	float bY2 = anotherSprite.y+anotherSprite.h;

	if(min(aX2, bX2) > max(aX, bX) && min(aY2, bY2) > max(aY, bY))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Sprite::max(float value1, float value2)
{
	if(value1 >= value2){return value1;}
	else{return value2;}
}
float Sprite::min(float value1, float value2)
{
	if(value1 <= value2){return value1;}
	else{return value2;}
}


