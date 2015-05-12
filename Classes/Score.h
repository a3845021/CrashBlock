//
//  Score.h
//  CrashBlock
//
//  Created by tianshuai on 5/1/15.
//
//

#ifndef __CrashBlock__Score__
#define __CrashBlock__Score__

#include "cocos2d.h"

class Score
{
public:
    static Score* getInstance();
    
    int getTopScore();
    void setTopScore(int socre);
private:
    static Score *_instance;
    
    class CGarbo // 它的唯一工作就是在析构函数中删除CSingleton的实例
    {
    public:
        ~CGarbo()
        {
            if (Score::_instance)
                delete Score::_instance;
        }
    };
    static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
};

#endif /* defined(__CrashBlock__Score__) */
