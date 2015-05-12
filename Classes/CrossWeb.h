//
//  CrossWeb.h
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#ifndef __CrashBlock__CrossWeb__
#define __CrashBlock__CrossWeb__

#include "cocos2d.h"

#include "Blcok.h"

class CrossWeb
{
public:
    void initWithSize(int row, int col);
    
    ~CrossWeb();
    
    int getRow() { return _row; }
    int getCol() { return _col; }
    
    //顶部有没有block
    bool isTopHaveBlock();
    
    void setCrossWeb(int row, int col, void* data);
    void clearCrossWeb(int row, int col);
    Block* getCrossWeb(int row, int col);
    
    void print();

    int _row,_col;
    Block** _crossWeb;
};

#endif /* defined(__CrashBlock__CrossWeb__) */
