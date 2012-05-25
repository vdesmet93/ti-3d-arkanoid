#ifndef PLATFORM_H
#define PLATFORM_H
#include "sprite.h"
#include "bouncingBall.h"

class Platform: public Sprite
{
	private:
	float speedX, lastX, radius;
	int timesUpdated;

	public:
	Platform();
	Platform(float x, float y);
        ~Platform();

	void applyBoost(BouncingBall& ball);
	void moveLeft();
	void moveRight();
	void update();
	void draw();
};

#endif
