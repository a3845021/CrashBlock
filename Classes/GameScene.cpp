//
//  GameScene.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#include "GameScene.h"


#include "GameLayer.h"
#include "ScoreLayer.h"
#include "EndLayer.h"

USING_NS_CC;

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::init()
{
    if( !Scene::init() )
    {
        return false;
    }
    
    GameLayer* gameLayer = GameLayer::create();
    this->addChild(gameLayer);
    
    ScoreLayer* scorelayer = ScoreLayer::create();
    this->addChild(scorelayer);
    
    EndLayer* layer = EndLayer::create();
    layer->setVisible(false);
    layer->setTag(1000);
    layer->setLocalZOrder(-1);
    this->addChild(layer);
    
    return true;
}

