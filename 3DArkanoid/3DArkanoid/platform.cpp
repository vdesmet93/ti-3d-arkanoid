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

void Platform:: moveTo(float x2, float y2)
{
	this->x = x2-(w/2);
	this->y = y2-(h/2);
	if(x < -1.0f){x = -1.0f;}
	else if(x+w > 1.0f){x = 1.0f-w;}
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
	glNormal3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.5f);
	//back
	glTexCoord2f(0,0); glVertex3f(x, y, z);
	glTexCoord2f(0,1); glVertex3f(x, y+h, z);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x+w, y, z);
	//front
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x, y+h, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z+d);
	glTexCoord2f(1,0); glVertex3f(x+w, y, z+d);

	glColor3f(0.0f, 0.5f, 0.0f);
	//down
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y, z);
	glTexCoord2f(1,0); glVertex3f(x, y, z);
	//up
	glTexCoord2f(0,0); glVertex3f(x, y+h, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y+h, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x, y+h, z);

	glColor3f(0.5f, 0.0f, 0.0f);
	//left
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x, y, z);
	glTexCoord2f(1,1); glVertex3f(x, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x, y+h, z+d);
	//right
	glTexCoord2f(0,0); glVertex3f(x+w, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y, z);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x+w, y+h, z+d);

	glEnd();
}
