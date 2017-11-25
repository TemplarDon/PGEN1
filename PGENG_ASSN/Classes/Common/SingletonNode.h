#ifndef SINGLETON_NODE_H
#define SINGLETON_NODE_H

#include "cocos2d.h"
using namespace cocos2d;

template <typename T>
class SingletonNode : public Node
{
public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

    virtual bool init() = 0;

protected:
    SingletonNode() { };
    virtual ~SingletonNode() { }

    
};

#endif