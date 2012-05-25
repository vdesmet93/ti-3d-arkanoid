#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H
#include "sprite.h"

class BouncingBall: public Sprite
{
private:
	float speedX, speedY, radius;
public:
	BouncingBall();
	BouncingBall(float x, float y);
        ~BouncingBall();

	void applyBoost(float amount);
	void move();
	void bounceBack();
	bool collide(const Sprite& anotherSprite);
	float getCenterX();
	float getCenterY();
	void update();
	void draw();
        void incSpd();
        void decSpd();
};

#endif
