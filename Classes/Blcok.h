//
//  Blcok.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef __CrashBlock__Blcok__
#define __CrashBlock__Blcok__

#include "assert.h"
#include "stdio.h"

enum Color
{
    NONE = 0,
    WHITE,
    BLACK,
    BLUE,
    RED,
    ORANGE,
    GREEN
};

class Block
{
public:
    Block();
    ~Block();
    
    void setUpBlock(Block *block);
    void setDownBlock(Block *block);
    void setLeftBlock(Block *block);
    void setRightBlock(Block *block);
    
    Block* getUpBlock();
    Block* getDownBlock();
    Block* getLeftBlock();
    Block* getRightBlock();
    
    void *getData();
    void setData(void* data);
    void clearData();
    bool isEmpty();
    
    void setColor(Color color);
    Color getColor();
    
private:
    Block* _up;
    Block* _down;
    Block* _left;
    Block* _right;

    Color _color;
    void* _data;
};


#endif /* defined(__CrashBlock__Blcok__) */
