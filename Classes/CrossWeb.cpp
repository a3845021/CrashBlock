//
//  CrossWeb.cpp
//  CrashBlock
//
//  Created by tianshuai on 4/27/15.
//
//

#include "CrossWeb.h"

void CrossWeb::initWithSize(int row, int col)
{
    _row = row; _col = col;
    //分配二维数组
    _crossWeb = new Block*[row];
    for(int i = 0; i < row; i++)
    {
        _crossWeb[i] = new Block[col];
    }
    
    //连接block指针,形成网络 左下角为坐标原点
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(i < row - 1)
                _crossWeb[i][j].setRightBlock( &_crossWeb[i+1][j] );
            if(j < col - 1)
                _crossWeb[i][j].setUpBlock( &_crossWeb[i][j+1] );
            if(j > 0)
                _crossWeb[i][j].setDownBlock( &_crossWeb[i][j-1] );
            if(i > 0)
                _crossWeb[i][j].setLeftBlock( &_crossWeb[i-1][j] );
        }
    }
}

CrossWeb::~CrossWeb()
{
    if(_crossWeb != NULL)
    {
        for(int i = 0; i < _row; i++)
        {
            delete[] _crossWeb[i];
        }
        delete[] _crossWeb;
    }
}

bool CrossWeb::isTopHaveBlock()
{
    for(int i = 0; i < _row; i++)
    {
        if( !_crossWeb[i][_col - 1].isEmpty() )
        {
            return true;
        }
    }
    return false;
}

void CrossWeb::setCrossWeb(int row, int col, void* data)
{
    assert(row < _row);
    assert(col < _col);
    _crossWeb[row][col].setData(data);
}

Block* CrossWeb::getCrossWeb(int row, int col)
{
    assert(row < _row);
    assert(col < _col);
    return &_crossWeb[row][col];
}

void CrossWeb::clearCrossWeb(int row, int col)
{
    assert(row < _row);
    assert(col < _col);
    _crossWeb[row][col].clearData();
}

void CrossWeb::print()
{
    for(int i = 0; i < _row; i++)
    {
        for(int j = 0; j < _col; j++)
        {
            printf("i=%d,j=%d,node=%p up=%p donw=%p left=%p right=%p        ",i,j,&_crossWeb[i][j], _crossWeb[i][j].getUpBlock(), _crossWeb[i][j].getDownBlock(), _crossWeb[i][j].getLeftBlock(), _crossWeb[i][j].getRightBlock());
        }
        printf("\n");
    }
}
