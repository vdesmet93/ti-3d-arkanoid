#include "block.h"
#include <stdio.h>

using namespace std;

Block::Block(void): Sprite()
{

}

Block::Block(float x, float y, float z, float w, float h, float d): Sprite(x, y, z, w, h, d)
{
	
}

void Block:: setColor(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void Block:: update()
{

}

void Block:: draw(float x, float y, float z, float w, float h, float d)
{
	glBegin(GL_QUADS);

	glColor3f(this->red, this->green, this->blue);
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

	glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP);
	//front
	glVertex3f(x, y, z+d);
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y, z+d);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//down
	glVertex3f(x, y, z+d);
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//up
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x, y+h, z);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//left
	glVertex3f(x, y, z+d);
	glVertex3f(x, y, z);
	glVertex3f(x, y+h, z);
	glVertex3f(x, y+h, z+d);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//right
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x+w, y+h, z+d);
	glEnd();
}

void Block:: draw()
{
	glBegin(GL_QUADS);

	glColor3f(red, green, blue);
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

	glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP);
	//front
	glVertex3f(x, y, z+d);
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y, z+d);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//down
	glVertex3f(x, y, z+d);
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//up
	glVertex3f(x, y+h, z+d);
	glVertex3f(x+w, y+h, z+d);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x, y+h, z);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//left
	glVertex3f(x, y, z+d);
	glVertex3f(x, y, z);
	glVertex3f(x, y+h, z);
	glVertex3f(x, y+h, z+d);
	glEnd();

	glBegin(GL_LINE_STRIP);

	//right
	glVertex3f(x+w, y, z+d);
	glVertex3f(x+w, y, z);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x+w, y+h, z+d);
	glEnd();
}
bool Block:: isEnabled()
{
	return this -> enabled;
}

void Block:: enable()
{
	this->enabled = true;
}

void Block:: disable()
{
	this->enabled = false;
}

void Block:: setCoordinates(float x, float y, float z)
{
	this -> x = x;
	this -> y = y;
	this -> z = z;
}

void Block:: setDimensions(float d, float w, float h)
{
	this -> d = d;
	this -> w = w;
	this -> h = h;
}
