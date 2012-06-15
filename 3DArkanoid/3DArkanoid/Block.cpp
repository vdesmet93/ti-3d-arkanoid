#include "block.h"
#include <stdio.h>

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

void Block:: draw()
{

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);
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

	glDisable(GL_TEXTURE_2D);
	glLineWidth(4.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
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

	glEnable(GL_TEXTURE_2D);
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

void Block:: drop()
{
	this -> z -= h;
}
