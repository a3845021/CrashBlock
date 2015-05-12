//
//  GameLayer.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef __CrashBlock__GameLayer__
#define __CrashBlock__GameLayer__

#include "cocos2d.h"
#include "GameLogic.h"

class GameLayer : public cocos2d::LayerGradient
{
public:
    GameLayer(void);
    ~GameLayer(void);
    
    bool init();
    
    CREATE_FUNC(GameLayer);
    
    cocos2d::EventListenerTouchOneByOne* listener;
private:
    void update(float dt);
    void updateSceneClear(float dt);
    void organization(float dt);
    bool canTouch;
    
    GameLogic _game;
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    long curTime;
    int timeInter;
};

#endif /* defined(__CrashBlock__GameLayer__) */
