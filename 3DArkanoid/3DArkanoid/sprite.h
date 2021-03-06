#ifndef SPRITE_H
#define SPRITE_H
#ifndef __GNUC__
#include <glut.h>
#include <gl/GL.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>

class Sprite
{
	protected:
	float x, y, z, w, h, d;

	public:
	Sprite::Sprite();
	Sprite::Sprite(float x, float y);
	Sprite::Sprite(float x, float y, float w, float h);
	Sprite::Sprite(float x, float y, float z, float w, float h, float d);

	float Sprite:: getX()const{return x;}
	float Sprite:: getY()const{return y;}
	float Sprite:: getZ()const{return z;}
	float Sprite:: getW()const{return w;}
	float Sprite:: getH()const{return h;}
	float Sprite:: getD()const{return d;}
	bool Sprite::intersects(const Sprite& anotherSprite);
	virtual void Sprite::update()=0;
	virtual void Sprite::draw()=0;

	private:
	float Sprite::max(float value1, float value2);
	float Sprite::min(float value1, float value2);
};

#endif