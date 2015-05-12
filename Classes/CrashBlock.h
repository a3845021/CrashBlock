//
//  CrashBall.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef CrashBlock_CrashBall_h
#define CrashBlock_CrashBall_h

#include "cocos2d.h"

#define GAME_ROW (6)

#define BLOCK_SIZE (Director::getInstance()->getVisibleSize().width*2/3/GAME_ROW)

#define GAME_COL (int)(Director::getInstance()->getVisibleSize().height / (BLOCK_SIZE) )

struct GLOBAL
{
    int score;
    
    int blockColor;
    
    bool gameover;
};

extern GLOBAL global;

#endif
