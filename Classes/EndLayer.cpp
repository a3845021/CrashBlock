//
//  EndLayer.cpp
//  CrashBlock
//
//  Created by tianshuai on 5/1/15.
//
//

#include "EndLayer.h"
#include "GameScene.h"
#include "CrashBlock.h"
#include "Score.h"

#include "AdmobWrapper.h"

USING_NS_CC;

EndLayer::EndLayer()
{
    
}

EndLayer::~EndLayer()
{
    
}

bool EndLayer::init()
{
    if( !LayerColor::initWithColor( Color4B( 255,255,255,180 ) ))
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto rateLable = Label::createWithTTF("LOL Rate!", "fonts/arial.ttf", visibleSize.width/18);
    rateLable->setColor(Color3B(255,0,0));
    auto menuItemrate = MenuItemLabel::create(rateLable, CC_CALLBACK_1(EndLayer::startRate, this));
    menuItemrate->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/5*1 ));
    
    auto labelContinue = Label::createWithTTF("TAP TO CONTINUE", "fonts/arial.ttf", visibleSize.width/15);
    labelContinue->setColor(Color3B(10,10,10) );
    auto fadeOut = FadeOut::create(1);
    auto fadeIn = FadeIn::create(1);
    Sequence *seq = Sequence::create(fadeOut, fadeIn, NULL);
    labelContinue->runAction(RepeatForever::create(seq));
    auto menuItem = MenuItemLabel::create(labelContinue, CC_CALLBACK_1(EndLayer::menuStartCallback, this));
    menuItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3*1 ));
    auto menu = Menu::create(menuItem, menuItemrate,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    char buff[32];
    sprintf(buff,"%d", 0);
    score = Label::createWithTTF(buff, "fonts/arial.ttf", visibleSize.width/8);
    score->setPosition( Vec2(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2)) );
    this->addChild(score);
    
    sprintf(buff,"Top Score : %d", Score::getInstance()->getTopScore() );
    Label *topscore = Label::createWithTTF(buff, "fonts/arial.ttf", visibleSize.width/16);
    topscore->setPosition(Vec2(Vec2(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3*2))  ) );
    this->addChild(topscore);
    
    if(random(0, 2) == 0)
        AdmobWrapper::getInstance()->showInterstitial();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(EndLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void EndLayer::setScoreText(int s)
{
    char buff[32];
    sprintf(buff,"%d", s);
    score->setString(buff);
}

void EndLayer::menuStartCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene( GameScene::create() );
}

bool EndLayer::onTouchBegan(Touch *touch, Event *event)
{
    
    return true;
}

void EndLayer::startRate(Ref* pSender)
{
    if( Application::getInstance()->openURL("market://details?id=com.topspeedsnail.crashblock") == false )
    {
        
        Application::getInstance()->openURL("https://play.google.com/store/apps/details?com.topspeedsnail.crashblock");
    }
}