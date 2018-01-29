//#ifndef SINGLETON_NODE_H
//#define SINGLETON_NODE_H
//
//#include "cocos2d.h"
//using namespace cocos2d;
//
//template <typename T>
//class SingletonNode : public Node
//{
//public:
//    static T& GetInstance()
//    {
//        static T instance;
//        return instance;
//    }
//
//    virtual bool init() = 0;
//
//protected:
//    SingletonNode() { retain(); };
//    virtual ~SingletonNode() { }
//
//    
//};
//
//#endif

#ifndef SINGLETON_NODE_H
#define SINGLETON_NODE_H

#include "cocos2d.h"
using namespace cocos2d;

template <typename T>
class SingletonNode : public Node
{
private:
	static T* instance;

public:
	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
			instance->init();
		}

		return instance;
	}

	virtual bool init() = 0;

protected:
	SingletonNode() { };
	virtual ~SingletonNode() { }

};

template <class T>
T* SingletonNode<T>::instance = nullptr;

#endif
