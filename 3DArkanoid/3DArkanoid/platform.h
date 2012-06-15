#ifndef PLATFORM_H
#define PLATFORM_H
#include "sprite.h"
#include "bouncingBall.h"

class Platform: public Sprite
{
	private:
	float speedX, lastX;
	int timesUpdated;

	public:
	Platform::Platform();
	Platform::Platform(float x, float y);

	void Platform:: applyBoost(BouncingBall& ball);
	void Platform:: moveLeft();
	void Platform:: moveRight();
	void Platform:: moveTo(float x2);
	void Platform:: update();
	void Platform:: draw();
};

#endif