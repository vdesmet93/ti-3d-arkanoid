#include "platform.h"

Platform::Platform(){}

Platform::Platform(float x, float y): Sprite(x, y)
{
	this->w = 0.5f;
	this->h = 0.2f;
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
	
}

void Platform:: draw()
{
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(x, y);
	glVertex2f(x, y+h);
	glVertex2f(x+w, y+h);
	glVertex2f(x+w, y);
	glEnd();
}
