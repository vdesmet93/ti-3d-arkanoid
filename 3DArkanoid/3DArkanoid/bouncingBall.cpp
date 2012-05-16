#include "bouncingBall.h"
#include <stdio.h>

BouncingBall::BouncingBall(){}

BouncingBall::BouncingBall(float x, float y): Sprite(x, y)
{
	this->speedX = 0.0005f;
	this->speedY = 0.0008f;
	this->radius = 0.1f;
	this->w = 0.2f;
	this->h = 0.2f;
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

void BouncingBall:: bounceBack()
{
	speedY = -speedY;
	move();
}

void BouncingBall::collide(const Sprite& anotherSprite)
{
	//Check left side
	if(x+w >= anotherSprite.getX() && x+w <= anotherSprite.getX()+anotherSprite.getW())
	{
		speedX = -speedX;
		printf("\nLEFT");
	}
	//Check right side
	if(x <= anotherSprite.getX()+anotherSprite.getW() && x >= anotherSprite.getX())
	{
		speedX = -speedX;
		printf("\nRIGHT");
	}
	//Check lower side
	if(y+h >= anotherSprite.getY() && y+h <= anotherSprite.getY()+anotherSprite.getH())
	{
		speedY = -speedY;
		printf("\nDOWN");
	}
	//Check upper side
	if(y <= anotherSprite.getY()+anotherSprite.getH() && y >= anotherSprite.getY())
	{
		speedY = -speedY;
		printf("\nUP");
	}
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
	float increment = 2*M_PI/50;
	float cx = getCenterX();
	float cy = getCenterY();
	float radius = 0.1f;
	for(float angle = 0; angle < 2*M_PI; angle+=increment)
	{
		glBegin(GL_POLYGON);
		glVertex2d(cx, cy);	
		glVertex2d(cx + cos(angle)* radius, cy + sin(angle)*radius);
		glVertex2d(cx + cos(angle + increment)*radius, cy + sin(angle + increment)*radius);
		glEnd();
	}
}
