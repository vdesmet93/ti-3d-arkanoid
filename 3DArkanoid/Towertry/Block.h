#ifndef BLOCK_H
#define BLOCK_H
#include <glut.h>

class Block
{
	private:
	float red, green, blue;


	public:
	Block::Block();
	Block::Block(const Block& b);
	Block::Block(float x, float y, float z, float w, float h, float d);

	void Block:: setColor(float red, float green, float blue);
	void Block:: update();
	void Block:: draw(float x, float y, float z, float w, float h, float d);
};

#endif