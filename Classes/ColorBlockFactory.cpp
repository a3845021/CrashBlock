//
//  ColorBlockFactory.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/28/15.
//
//

#include "ColorBlockFactory.h"
#include "CrashBlock.h"

USING_NS_CC;

Color3B getRandomColor()
{
    int n = random(1,global.blockColor);
    switch (n)
    {
        case 1:
            return Color3B::WHITE;
        case 2:
            return Color3B::BLACK;
        case 3:
            return Color3B::BLUE;
        case 4:
            return Color3B::RED;
        case 5:
            return Color3B::ORANGE;
        case 6:
            return Color3B::GREEN;
    }
}

BlockColorNodeInfo ColorBlockFactory::GenColorBlock()
{
    BlockColorNodeInfo info;
    Node* _block = Node::create();
    DrawNode *block = DrawNode::create();
    block->drawSolidRect(Vec2::ZERO, Vec2(BLOCK_SIZE, BLOCK_SIZE), Color4F::GRAY);
    Color3B color = getRandomColor();
    if(color == Color3B::WHITE)
    {
        info.color = WHITE;
    }
    else if(color == Color3B::BLACK)
    {
        info.color = BLACK;
    }
    else if(color == Color3B::BLUE)
    {
        info.color = BLUE;
    }
    else if(color == Color3B::RED)
    {
        info.color = RED;
    }
    else if(color == Color3B::ORANGE)
    {
        info.color = ORANGE;
    }
    else if(color == Color3B::GREEN)
    {
        info.color = GREEN;
    }
    block->drawSolidRect(Vec2::ZERO, Vec2(BLOCK_SIZE-1, BLOCK_SIZE-1), Color4F(color));
    _block->setContentSize( Size(BLOCK_SIZE, BLOCK_SIZE) );
    _block->addChild(block);
    _block->retain();
    info.block = _block;
    return info;
}

Action* ColorBlockFactory::GenInsertAction(int i)
{
    MoveTo *moveTo = MoveTo::create(0.2, Vec2(BLOCK_SIZE*i, 0) );
    return moveTo;
}

Action* ColorBlockFactory::GenUpOnceAction()
{
    MoveBy *moveBy = MoveBy::create(0.2, Vec2(0, BLOCK_SIZE ));
    return moveBy;
}

Action* ColorBlockFactory::GenFallingDownAction(Node* block)
{
    RotateBy *rotateBy = RotateBy::create(0.2, -20);
    MoveTo *moveTo = MoveTo::create(0.5, Vec2(block->getPositionX(), -block->getContentSize().height*2));
    EaseIn* easeIn = EaseIn::create(moveTo, 4);
    Spawn *spawn = Spawn::create(rotateBy,easeIn, NULL);
    return Sequence::create(spawn,NULL);
}

Action* ColorBlockFactory::GenDownAction()
{
    MoveBy *moveTo = MoveBy::create(0.2, Vec2(0, -BLOCK_SIZE)) ;
    ActionEase *easeIn = EaseExponentialIn::create(moveTo);
    return easeIn;
}
