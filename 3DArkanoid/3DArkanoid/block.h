#ifndef BLOCK_H
#define BLOCK_H
#include "sprite.h"

class Block: public Sprite
{
	private:
	float red, green, blue;
	Sprite* power_up;


	public:
	Block::Block();
	Block::Block(float x, float y, float z, float w, float h, float d);

	void Block:: setColor(float red, float green, float blue);
	void Block:: update();
	void Block:: draw();
};

#endif