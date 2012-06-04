#include "bouncingBall.h"
#include <stdio.h>


BouncingBall::BouncingBall(){}

BouncingBall::BouncingBall(float x, float y): Sprite(x, y)
{
	this->speedX = 0.0005f;
	this->speedY = 0.0008f;
	this->radius = 0.05f;
	this->w = 0.1f;
	this->h = 0.1f;
	this->z = 0.0f;
	this->d = 0.1f;
}

void BouncingBall:: move()
{
	x+=speedX;
	y+=speedY;
	if(x+w > 1.0f){x = 1.0f-w; speedX=-speedX;}
	else if(x < -1.0f){x = -1.0f; speedX=-speedX;}
	if(y+h > 1.0f){y = 1.0f-h; speedY=-speedY;}
	else if(y < -1.0f){y = -1.0f; speedY=-speedY;}
}

void BouncingBall:: applyBoost(float amount)
{
	this->speedX += amount;
	move();
}

void BouncingBall:: bounceBack()
{
	speedY = -speedY;
	move();
}

bool BouncingBall::collide(const Sprite& anotherSprite)
{
	bool boost = false;
	bool left = false, right = false, down = false, up = false;
	//Check left side
	if(x+w >= anotherSprite.getX() && x+w <= anotherSprite.getX()+anotherSprite.getW())
	{
		left = true;
	}
	//Check right side
	if(x <= anotherSprite.getX()+anotherSprite.getW() && x >= anotherSprite.getX())
	{
		right = true;
	}
	//Check lower side
	if(y+h >= anotherSprite.getY() && y+h <= anotherSprite.getY()+anotherSprite.getH())
	{
		down = true;
	}
	//Check upper side
	if(y <= anotherSprite.getY()+anotherSprite.getH() && y >= anotherSprite.getY())
	{
		up = true;
	}
	//Bounce Left
	if(left && !right && speedX > 0)
	{
		speedX = -speedX;
		boost = true;
	}
	//Bounce Right
	if(right && !left && speedX < 0)
	{
		speedX = -speedX;
		boost = true;
	}
	//Bounce Down
	if(down && !up && speedY > 0)
	{
		speedY = -speedY;
		boost = true;
	}
	//Bounce Up
	if(up && !down && speedY < 0)
	{
		speedY = -speedY;
		boost = true;
	}
	return boost;
}

float BouncingBall:: getCenterX(){return x + radius;}
float BouncingBall:: getCenterY(){return y + radius;}

void BouncingBall:: update()
{
	move();
}

void BouncingBall:: draw()
{
	glColor3f(0.7f, 0.7f, 0.7f);
	
	GLUquadricObj* sphere = gluNewQuadric();
	glPushMatrix();
	glTranslatef(x+(w/2), y+(h/2), z+(d/2));
	gluSphere(sphere, w/2, 25, 25);
	glPopMatrix();

}
