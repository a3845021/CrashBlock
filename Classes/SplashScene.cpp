//
//  SplashScene.cpp
//  AreUBlind
//
//  Created by tianshuai on 4/22/15.
//
//

#include "SplashScene.h"

#include "GameScene.h"
#include "Score.h"

USING_NS_CC;

SplashScene::SplashScene()
{}

SplashScene::~SplashScene()
{}

bool SplashScene::init()
{
    if(Scene::init())
    {
        return true;
    } else
    {
        return false;
    }
}

void SplashScene::onEnter()
{
    Sprite *background = Sprite::create("splash2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    this->addChild(background);
    
    
    auto scene = GameScene::create();
    TransitionFade *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}
