#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>

#define HITBOX_CIRCLE 0x1
#define HITBOX_SQUARE 0x2

class Block {
private:
	double old_vect[3];
	double new_vect[3];
	double targ_vect[3];
	double velocity[3];
	uint32_t colour;
	uint8_t Interacts; // 0 if not interacting
	Block* power_up;
	int hitbox;
protected:
public:
	Block();
	~Block();
	void move(double vect[3]);
	void update(); // Move to ...
	void use(); // Break, catch or use
	void draw();
};

#endif

