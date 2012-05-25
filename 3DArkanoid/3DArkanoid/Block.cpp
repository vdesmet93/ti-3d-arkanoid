#include <iostream>
#include "Block.hpp"
#include <string.h>

Block::Block()
{
        memset(this, 0, sizeof(*this));
}

Block::~Block()
{
        memset(this, 0, sizeof(*this));
}

void Block::update()
{
}

void Block::move(double vect[3])
{
}

void Block::use()
{
}

void Block::draw()
{
}
