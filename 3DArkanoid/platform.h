#ifndef PLATFORM_H
#define PLATFORM_H
#include "sprite.h"

class Platform: public Sprite
{
	private:
	float speedX, speedY, radius;

	public:
	Platform::Platform();
	Platform::Platform(float x, float y);

	void Platform:: moveLeft();
	void Platform:: moveRight();
	void Platform:: update();
	void Platform:: draw();
};

#endif