//
//  EndLayer.h
//  CrashBlock
//
//  Created by tianshuai on 5/1/15.
//
//

#ifndef __CrashBlock__EndLayer__
#define __CrashBlock__EndLayer__

#include "cocos2d.h"
class EndLayer : public cocos2d::LayerColor
{
public:
    EndLayer(void);
    ~EndLayer(void);
    
    bool init();
    
    CREATE_FUNC(EndLayer);
    
    void setScoreText(int s);
    
private:
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    
    cocos2d::Label *score;
    
    void menuStartCallback(cocos2d::Ref* pSender);
    void startRate(cocos2d::Ref* pSender);
};


#endif /* defined(__CrashBlock__EndLayer__) */
