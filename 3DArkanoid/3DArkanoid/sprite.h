#ifndef SPRITE_H
#define SPRITE_H

#ifdef __GNUC__
#include <GL/glut.h>
#else
#include <glut.h>
#endif

#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Sprite
{
	protected:
	float x, y, z, w, h, d;

	public:
	Sprite();
	Sprite(float x, float y);
	Sprite(float x, float y, float w, float h);

	float getX()const{return x;}
	float getY()const{return y;}
	float getZ()const{return z;}
	float getW()const{return w;}
	float getH()const{return h;}
	float getD()const{return d;}
	bool intersects(const Sprite& anotherSprite);
	virtual void update()=0;
	virtual void draw()=0;

	private:
	float max(float value1, float value2);
	float min(float value1, float value2);
};

#endif
