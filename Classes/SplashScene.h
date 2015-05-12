//
//  SplashScene.h
//  AreUBlind
//
//  Created by tianshuai on 4/22/15.
//
//

#ifndef __AreUBlind__SplashScene__
#define __AreUBlind__SplashScene__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:

    SplashScene();
    
    ~SplashScene();
    
    virtual bool init();
    
    CREATE_FUNC(SplashScene);

    void onEnter();
};

#endif /* defined(__AreUBlind__SplashScene__) */
