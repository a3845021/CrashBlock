//
//  ColorBlockFactory.h
//  CrashBlock
//
//  Created by tianshuai on 4/28/15.
//
//

#ifndef __CrashBlock__ColorBlockFactory__
#define __CrashBlock__ColorBlockFactory__

#include "cocos2d.h"
#include "Blcok.h"

struct BlockColorNodeInfo
{
    cocos2d::Node* block;
    Color color;
};

class ColorBlockFactory
{
public:
    static BlockColorNodeInfo GenColorBlock();
    
    static cocos2d::Action* GenInsertAction(int i);
    static cocos2d::Action* GenUpOnceAction();
    static cocos2d::Action* GenFallingDownAction(cocos2d::Node* block);
    static cocos2d::Action* GenDownAction();
};

#endif /* defined(__CrashBlock__ColorBlockFactory__) */
