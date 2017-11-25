#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;

class SceneManager
{
    static SceneManager* m_instance;
    SceneManager();

    Director* theDirector;

public:
    static SceneManager* GetInstance()
    {
        if (!m_instance)
            m_instance = new SceneManager;
        return m_instance;
    }

    void Init();
    void AddSceneToStack(Scene* toAdd);
    void PopSceneFromStack();


};

#endif // __SCENE_MANAGER_H__
