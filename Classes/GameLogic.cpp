//
//  GameLogic.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#include "GameLogic.h"

#include "CrashBlock.h"

#include "ColorBlockFactory.h"

#include "GameLayer.h"

USING_NS_CC;

GameLogic::GameLogic()
{
    _mapRow = 0;
    _mapCol = 0;
    _fallBlcokNum = 0;
    _needUpdate = false;
}
GameLogic::~GameLogic()
{}

void GameLogic::initBeginingStatus()
{
    for(int i = 0; i < 3;i++)
    {
        shiftUpOnce();
        insertAtBottom();
    }
}

bool GameLogic::treeToGo()
{
    for(int j = _crossWeb.getCol()-1; j >= 0; j--)
    {
        for(int i = 0; i < _crossWeb.getRow(); i++)
        {
            if( !_crossWeb.getCrossWeb(i, j)->isEmpty() )
            {
                Block* block = _crossWeb.getCrossWeb(i, j);
                if( (block->getLeftBlock() != NULL && !block->getLeftBlock()->isEmpty() && block->getLeftBlock()->getColor() == block->getColor() &&
                   block->getRightBlock() != NULL && !block->getRightBlock()->isEmpty() && block->getRightBlock()->getColor() == block->getColor()) ||
                    (block->getUpBlock() != NULL && !block->getUpBlock()->isEmpty() && block->getUpBlock()->getColor() == block->getColor() &&
                    block->getDownBlock() != NULL && !block->getDownBlock()->isEmpty() && block->getDownBlock()->getColor() == block->getColor()) )
                {
                    
                    _sameColorBlock.clear();
                    
                    Block *clickBlock = getBlock( ((Node*)block->getData()) );
                    _clickColor = clickBlock->getColor();
                    insertSameColorBlock(clickBlock);
                    
                    for(std::set<Block*>::iterator it = _sameColorBlock.begin(); it != _sameColorBlock.end(); it++)
                    {
                        //printf("%p  ", *it);
                        ((Node*)(*it)->getData())->setLocalZOrder(100);
                        ((Node*)(*it)->getData())->runAction( ColorBlockFactory::GenFallingDownAction((Node*)(*it)->getData()) );
                        ((Node*)(*it)->getData())->getParent()->getEventDispatcher()->removeEventListenersForTarget((Node*)(*it)->getData());
                        removeNodeFromCrossWeb(((Node*)(*it)->getData()));
                    }
                    
                    fillTheHole();
                    
                    return true;
                }
                
                
            }
        }
    }
    return false;
}
                
void GameLogic::setMapSize(int row, int col)
{
    _mapRow = row;
    _mapCol = col;
    _crossWeb.initWithSize(row, col);
}

void GameLogic::insertAtBottom()
{
    for(int i = 0; i < _mapRow; i++)
    {
        BlockColorNodeInfo block = ColorBlockFactory::GenColorBlock();
        _crossWeb.setCrossWeb(i, 0, (void*)block.block);
        _crossWeb.getCrossWeb(i, 0)->setColor(block.color);
        Action *action = ColorBlockFactory::GenInsertAction(i);
        block.block->runAction(action);
    }
    _needUpdate = true;
}

void GameLogic::shiftUpOnce()
{
    for(int j = _crossWeb.getCol()-1; j >= 1; j--)
    {
        for(int i = 0; i < _crossWeb.getRow(); i++)
        {
            if( !_crossWeb.getCrossWeb(i, j)->getDownBlock()->isEmpty() )
            {
                _crossWeb.getCrossWeb(i, j)->setData( _crossWeb.getCrossWeb(i, j)->getDownBlock()->getData() );
                _crossWeb.getCrossWeb(i, j)->setColor( _crossWeb.getCrossWeb(i, j)->getDownBlock()->getColor() );
                _crossWeb.getCrossWeb(i, j)->getDownBlock()->clearData();
                _crossWeb.getCrossWeb(i, j)->getDownBlock()->setColor(NONE);
                void *data = _crossWeb.getCrossWeb(i, j)->getData();
                Action *action = ColorBlockFactory::GenUpOnceAction();
                ((Node*)data)->runAction(action);
            }
        }
    }
}

void GameLogic::updateToLayer(Layer *layer)
{
    if(_needUpdate == true)
    {
        for(int i = 0; i < _crossWeb.getRow(); i++)
        {
            for(int j = 0; j < _crossWeb.getCol(); j++)
            {
                void *data = _crossWeb.getCrossWeb(i, j)->getData();
                if(data != NULL )
                {
                    if(((Node*)data)->getParent() == NULL)
                    {
                        layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority( ((GameLayer*)layer)->listener->clone(), (Node*)data ) ;
                        layer->addChild( (Node*)data );
                    }
                }
            }
        }
    }
    _needUpdate =false;
}

void GameLogic::fillDown(Block* block)
{
    if( block->getDownBlock() != NULL && block->getDownBlock()->isEmpty() )
    {
        block->getDownBlock()->setData( block->getData() );
        block->getDownBlock()->setColor( block->getColor() );
        Action *action = ColorBlockFactory::GenDownAction();
        ((Node*)block->getData())->runAction(action);
        block->clearData();
        block->setColor(NONE);
        
        fillDown( block->getDownBlock());
    }
}

void GameLogic::fillTheHole()
{
    for(int j = 1; j < _crossWeb.getCol(); j++)
    {
        for(int i = 0; i < _crossWeb.getRow(); i++)
        {
            if( !_crossWeb.getCrossWeb(i, j)->isEmpty() )
            {
                fillDown(_crossWeb.getCrossWeb(i, j));
            }
        }
    }
}

Block *GameLogic::getBlock(Node* block)
{
    for(int i = 0; i < _crossWeb.getRow(); i++)
    {
        for(int j = 0; j < _crossWeb.getCol(); j++)
        {
            if( _crossWeb.getCrossWeb(i, j)->getData()== block  )
            {
                return _crossWeb.getCrossWeb(i, j);
            }
        }
    }
    return NULL;
}

void GameLogic::removeNodeFromCrossWeb(cocos2d::Node* block)
{
    Block* b = getBlock(block);
    if(b != NULL)
    {
        b->clearData();
        b->setColor(NONE);
        
        _fallBlcokNum++;
    }
}

//递归真好用
void GameLogic::insertSameColorBlock(Block* block)
{
    _sameColorBlock.insert(block);
    
    if( block->getUpBlock() != NULL &&
       (block->getUpBlock()->getColor() == _clickColor) &&
       _sameColorBlock.find(block->getUpBlock())==_sameColorBlock.end()  )
    {
        insertSameColorBlock(block->getUpBlock());
    }
    if( block->getDownBlock() != NULL &&
       (block->getDownBlock()->getColor() == _clickColor) &&
       _sameColorBlock.find(block->getDownBlock())==_sameColorBlock.end()  )
    {
        insertSameColorBlock(block->getDownBlock());
    }
    if( block->getLeftBlock() != NULL &&
       (block->getLeftBlock()->getColor() == _clickColor) &&
       _sameColorBlock.find(block->getLeftBlock())==_sameColorBlock.end()  )
    {
        insertSameColorBlock(block->getLeftBlock());
    }
    if( block->getRightBlock() != NULL &&
       (block->getRightBlock()->getColor() == _clickColor) &&
       _sameColorBlock.find(block->getRightBlock())==_sameColorBlock.end()  )
    {
        insertSameColorBlock(block->getRightBlock());
    }
}

void GameLogic::clickBlockDown(Node *block)
{
    _sameColorBlock.clear();
    
    Block *clickBlock = getBlock(block);
    _clickColor = clickBlock->getColor();
    insertSameColorBlock(clickBlock);
    
    
    for(std::set<Block*>::iterator it = _sameColorBlock.begin(); it != _sameColorBlock.end(); it++)
    {
        //printf("%p  ", *it);
        ((Node*)(*it)->getData())->setLocalZOrder(100);
        ((Node*)(*it)->getData())->runAction( ColorBlockFactory::GenFallingDownAction((Node*)(*it)->getData()) );
        ((Node*)(*it)->getData())->getParent()->getEventDispatcher()->removeEventListenersForTarget((Node*)(*it)->getData());
        removeNodeFromCrossWeb(((Node*)(*it)->getData()));
    }
}

int GameLogic::getBlockNum()
{
    int num = 0;
    for(int i = 0; i < _crossWeb.getRow(); i++)
    {
        for(int j = 0; j < _crossWeb.getCol(); j++)
        {
            if( !_crossWeb.getCrossWeb(i, j)->isEmpty() )
            {
                num++;
            }
        }
    }
    return num;
}

bool GameLogic::isGameOver()
{
    for(int i = 0; i < _crossWeb.getRow(); i++)
    {
        if( !_crossWeb.getCrossWeb(i, _crossWeb.getCol()-1)->isEmpty() )
        {
            return true;
        }
    }
    return false;
}

int GameLogic::getFallBlockNum()
{
    return _fallBlcokNum;
}

void GameLogic::cleanUp()
{
    for(int i = 0; i < _crossWeb.getRow(); i++)
    {
        for(int j = 0; j < _crossWeb.getCol(); j++)
        {
            if( !_crossWeb.getCrossWeb(i, j)->isEmpty() )
            {
                void *block = _crossWeb.getCrossWeb(i, j)->getData();
                ((Node*)block)->release();
            }
        }
    }
}