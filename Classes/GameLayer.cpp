//
//  GameLayer.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#include "GameLayer.h"

#include "CrashBlock.h"

#include "ColorBlockFactory.h"

USING_NS_CC;

GameLayer::GameLayer()
{
    canTouch = true;
}

GameLayer::~GameLayer()
{
    listener->release();
    
    //妈蛋找一小时内存泄漏 一retain一release
    _game.cleanUp();
}


bool GameLayer::init()
{
    if( !LayerGradient::init()  )
    {
        return false;
    }
    
    this->setStartColor(Color3B(255, 0, 0));
    this->setStartOpacity(120);
    this->setEndColor(Color3B(0,255,0));
    this->setEndOpacity(80);
    this->setVector(Vec2(0, -1));
    
    //初始化全局变量
    global.score = 0;
    global.blockColor = 3;
    global.gameover = false;
    
    //设置Layer大小
    this->setContentSize( Size(Director::getInstance()->getVisibleSize().width*2/3, Director::getInstance()->getVisibleSize().height) );
    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->retain();
    
    //----    ------    -----    ------
    DrawNode *deadLine = DrawNode::create();
    for(int i = -this->getContentSize().width/2; i <= this->getContentSize().width/2; i = i + 20)
    {
        deadLine->drawLine( Vec2(i, 0 ) , Vec2( i + 10, 0 ), Color4F(Color4B( 251,0,144, 230)));
    }
    deadLine->setLocalZOrder(100);
    deadLine->setPosition( Vec2(this->getContentSize().width/2, BLOCK_SIZE*GAME_COL) );
    this->addChild(deadLine);

    //设置地图大小
    _game.setMapSize(GAME_ROW, GAME_COL+1);
    
    //初始化地图
    _game.initBeginingStatus();
    
    schedule(schedule_selector(GameLayer::updateSceneClear), 1.0f, kRepeatForever, 0);
    scheduleUpdate();
    
    return true;
}

void GameLayer::update(float dt)
{
    _game.updateToLayer(this);
    
    global.score = _game.getFallBlockNum();
}

void GameLayer::updateSceneClear(float dt)
{
    //clear outside block
    Vector<Node*> child = this->getChildren();
    for(auto c : child)
    {
        if(c->getPositionY() <= -BLOCK_SIZE)
        {
            this->removeChild(c);
            c->release();
        }
    }
    
    if(global.score > 50)
        global.blockColor = 4;
    
    if(global.score > 300)
        global.blockColor = 5;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    if(canTouch == false)
        return false;
    Node* target = static_cast<Node*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint( locationInNode ) )
    {
//        struct timeval tv;
//        gettimeofday(&tv,NULL);
//        static long preTime = tv.tv_sec * 1000 + tv.tv_usec / 1000 -1000;
//        curTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
//        timeInter = curTime - preTime + timeInter;
//        preTime = curTime;
//        if(timeInter > 250)
//        {
            _game.clickBlockDown(target);
            _game.shiftUpOnce();
            _game.insertAtBottom();
            _game.fillTheHole();
        
            schedule(schedule_selector(GameLayer::organization) ,0.45f, kRepeatForever, 0.26);
            
//            timeInter = 0;
            canTouch = false;
//        }
        
    }
    return false;
}

void GameLayer::organization(float dt)
{
    bool isHave = _game.treeToGo();
    if(isHave == false)
    {
        canTouch = true;
        unschedule(schedule_selector(GameLayer::organization));
        
        if(_game.isGameOver() == true)
        {
            canTouch = false;
            global.gameover = true;
        }
        
        //如果全部消除添加一行
        int n = _game.getBlockNum();
        if(n == 0)
        {
            _game.insertAtBottom();
        }
    }
}

