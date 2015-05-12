//
//  ScoreLayer.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/30/15.
//
//

#include "ScoreLayer.h"

#include "Score.h"
#include "CrashBlock.h"

#include "GameScene.h"

#include "EndLayer.h"

USING_NS_CC;

ScoreLayer::ScoreLayer()
{}

ScoreLayer::~ScoreLayer()
{

}

bool ScoreLayer::init()
{
    if( !LayerColor::initWithColor( Color4B(251,0,144, 230) ))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->setContentSize( Size(visibleSize.width*1/3, Director::getInstance()->getVisibleSize().height) );
    this->setPosition( Vec2(visibleSize.width*2/3,0) );
    
    visibleSize = this->getContentSize();
    
    _topScore = Score::getInstance()->getTopScore();
    sprintf(buff, "Top Score : %d",_topScore);
    topScore = Label::createWithTTF(buff, "fonts/arial.ttf", visibleSize.width/10);
    topScore->setPosition(Vec2(visibleSize.width/2,visibleSize.height - topScore->getContentSize().height ) );
    topScore->setTextColor(Color4B(255,255,255,234));
    this->addChild(topScore,1);
    
    sprintf(buff, "%d",0);
    scoreLabel = Label::createWithTTF(buff, "fonts/arial.ttf", visibleSize.width);
    scoreLabel->setAnchorPoint(Vec2(0,0.5) );
    scoreLabel->setPosition(Vec2( visibleSize.width/2, visibleSize.height - topScore->getContentSize().height*3) );
    scoreLabel->setTextColor(Color4B(255,255,255,234));
    scoreLabel->setRotation(90);
    this->addChild(scoreLabel,1);
    
    replay = Sprite::create("replay.png");
    replay->setPosition(Vec2(visibleSize.width/2, visibleSize.height/8) );
    this->addChild(replay);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ScoreLayer::onTouchBegan, this);
    listener->onTouchEnded= CC_CALLBACK_2(ScoreLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, replay);
    
    scheduleUpdate();
    
    return true;
}

void ScoreLayer::update(float dt)
{
    sprintf(buff, "%d", global.score);
    scoreLabel->setString(buff);
    
    if(global.gameover == true)
    {
        if(_topScore < global.score)
        {
            _topScore = global.score;
            Score::getInstance()->setTopScore(_topScore);
        }
        Node* endlayer = this->getParent()->getChildByTag(1000);
        endlayer->setVisible(true);
        endlayer->setLocalZOrder(1000);
        ((EndLayer*)endlayer)->setScoreText(global.score);
        unscheduleUpdate();
    }
}

bool ScoreLayer::onTouchBegan(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    // 获取当前触控点相对与按钮的位置
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    // 检测点击区域
    if (rect.containsPoint(locationInNode))
    {
        target->setOpacity(180);
        return true;
    }
    return false;
}

void ScoreLayer::onTouchEnded(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    target->setOpacity(255);
    //重开按钮
    if (target == replay)
    {
        //如果点击结束时在sprtie外 不响应消息
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            Director::getInstance()->replaceScene( GameScene::create() );
        }
    }
}
