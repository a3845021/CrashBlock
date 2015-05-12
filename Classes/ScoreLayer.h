//
//  ScoreLayer.h
//  CrashBlock
//
//  Created by tianshuai on 4/30/15.
//
//

#ifndef __CrashBlock__ScoreLayer__
#define __CrashBlock__ScoreLayer__

#include "cocos2d.h"

class ScoreLayer : public cocos2d::LayerColor
{
public:
    ScoreLayer(void);
    ~ScoreLayer(void);
    
    bool init();
    
    CREATE_FUNC(ScoreLayer);
    
private:
    char buff[32];
    
    cocos2d::Label *topScore;
    int _topScore;
    
    void update(float dt);
    cocos2d::Label *scoreLabel;
    
    cocos2d::Sprite *replay;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif /* defined(__CrashBlock__ScoreLayer__) */
