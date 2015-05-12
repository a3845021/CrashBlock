//
//  Blcok.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#include "Blcok.h"


Block::Block()
{
    _up = NULL;
    _down = NULL;
    _left = NULL;
    _right = NULL;
    _data = NULL;
    _color = NONE;
}

Block::~Block()
{
    
}

void Block::setUpBlock(Block *block)
{
    _up = block;
}

void Block::setDownBlock(Block *block)
{
    _down = block;
}

void Block::setLeftBlock(Block *block)
{
    _left = block;
}

void Block::setRightBlock(Block *block)
{
    _right = block;
}

Block* Block::getUpBlock()
{
    return _up;
}

Block* Block::getDownBlock()
{
    return _down;
}

Block* Block::getLeftBlock()
{
    return _left;
}

Block* Block::getRightBlock()
{
    return _right;
}

void* Block::getData()
{
    return _data;
}

void Block::setData(void* data)
{
    assert(data != NULL);
    _data = data;
}

void Block::clearData()
{
    _data = NULL;
}

bool Block::isEmpty()
{
    if(_data == NULL)
        return true;
    else
        return false;
}

void Block::setColor(Color color)
{
    _color = color;
}

Color Block::getColor()
{
    return _color;
}
