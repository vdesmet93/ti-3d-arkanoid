#include "platform.h"
#include "stdio.h"

Platform::Platform(){}

Platform::Platform(float x, float y): Sprite(x, y)
{
	this->w = 0.5f;
	this->h = 0.2f;
	this->z = 0.0f;
	this->d = 0.2f;
	lastX = x;
}

void Platform:: applyBoost(BouncingBall& ball)
{
	ball.applyBoost(speedX);
}

void Platform:: moveLeft()
{
	x-=0.1f;
	if(x < -1.0f){x = -1.0f;}
}

void Platform:: moveRight()
{
	x+=0.1f;
	if(x+w > 1.0f){x = 1.0f-w;}
}

void Platform:: update()
{
	if(timesUpdated%100==0)
	{
		speedX = (x-lastX)/1000;
		lastX = x;
		//printf("\nSpeed: %f", speedX);
	}
	timesUpdated++;
}

void Platform:: draw()
{
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	//back
	glVertex3f(x, y, z);
	glVertex3f(x, y+h, z);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x+w, y, z);
	//front
	glVertex3f(x, y, z+d);
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y, z+d);

	glColor3f(0.0f, 1.0f, 0.0f);
	//down
	glVertex3f(x, y, z+d);
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x, y, z);
	//up
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x, y+h, z);

	glColor3f(1.0f, 0.0f, 0.0f);
	//left
	glVertex3f(x, y, z+d);
	glVertex3f(x, y, z);
	glVertex3f(x, y+h, z);
	glVertex3f(x, y+h, z+d);
	//right
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x+w, y+h, z+d);

	glEnd();
}
