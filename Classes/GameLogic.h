//
//  GameLogic.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef __CrashBlock__GameLogic__
#define __CrashBlock__GameLogic__

#include "cocos2d.h"

#include "CrossWeb.h"

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();
    
    //初始化游戏开始的层数
    void initBeginingStatus();
    
    //点击方块后进行整理并三消
    bool treeToGo();
    
    //设置地图大小
    void setMapSize(int row, int col);
    
    //把_crossWeb的状态更新到Layer
    void updateToLayer(cocos2d::Layer *layer);
    
    //插入一列方块
    void insertAtBottom();
    
    void shiftUpOnce();
    
    void fillTheHole();
    
    void clickBlockDown(cocos2d::Node *block);
    
    int getBlockNum();
    bool isGameOver();
    
    int getFallBlockNum();
    
    void cleanUp();
private:
    Block *getBlock(cocos2d::Node* block);
    void removeNodeFromCrossWeb(cocos2d::Node* block);
    
    void fillDown(Block* block);
    
    int _mapRow;
    int _mapCol;
    CrossWeb _crossWeb;
    
    bool _needUpdate;
    
    void insertSameColorBlock(Block* block);
    std::set<Block*> _sameColorBlock;
    Color _clickColor;
    
    int _fallBlcokNum;
};

#endif /* defined(__CrashBlock__GameLogic__) */
