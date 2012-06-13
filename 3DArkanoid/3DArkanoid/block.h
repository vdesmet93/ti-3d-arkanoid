#ifndef BLOCK_H
#define BLOCK_H
#include "sprite.h"

class Block: public Sprite
{
	private:
	float red, green, blue;
	Sprite* power_up;
	bool enabled;


	public:
	Block::Block(void);
	Block::Block(float x, float y, float z, float w, float h, float d);

	void Block:: setColor(float red, float green, float blue);
	void Block:: update();
	void Block:: draw(float x, float y, float z, float w, float h, float d);
	bool Block:: isEnabled();
	void Block:: enable();
	void Block:: disable();
};

#endif