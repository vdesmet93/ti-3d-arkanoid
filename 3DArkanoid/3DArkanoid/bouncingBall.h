#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H
#include "sprite.h"

class BouncingBall: public Sprite
{
	private:
	float speedX, speedY, radius;

	public:
	BouncingBall::BouncingBall();
	BouncingBall::BouncingBall(float x, float y);

	void BouncingBall:: move();
	void BouncingBall::bounceBack();
	void BouncingBall::collide(const Sprite& anotherSprite);
	float BouncingBall:: getCenterX();
	float BouncingBall:: getCenterY();
	void BouncingBall:: update();
	void BouncingBall:: draw();
};

#endif