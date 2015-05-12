//
//  GameScene.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef __CrashBlock__GameScene__
#define __CrashBlock__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();
    bool init();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__CrashBlock__GameScene__) */
