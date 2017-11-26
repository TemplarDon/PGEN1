#include "SceneManager.h"

SceneManager::SceneManager()
{
    if (Node::init())
        init();
}

SceneManager::~SceneManager()
{
}

bool SceneManager::init()
{
    if (!Node::init())
    {
        return false;
    }

    theDirector = Director::getInstance();
    //theDirector->init();
}

void SceneManager::Start(Scene* initialScene)
{
    theDirector->runWithScene(initialScene);
}

void SceneManager::AddLevel(string name, Scene* toAdd)
{
    m_LevelMap[name] = toAdd;
    m_LevelMap[name]->retain();
}

void SceneManager::AddSharedScene(string name, Scene* toAdd)
{
    m_SharedScenesMap[name] = toAdd;
    m_SharedScenesMap[name]->retain();
}

void SceneManager::AddSceneToStack(string name)
{
    Scene* toAdd = GetSharedScene(name);

    if (toAdd)
        theDirector->pushScene(GetSharedScene(name));
}

void SceneManager::PopSceneFromStack(int popToLevel)
{
    if (popToLevel > 0)
    {
        theDirector->popToSceneStackLevel(popToLevel);
    }
    else
    {
        theDirector->popScene();
    }
}

void SceneManager::TransitionLevel(string newScene, TRANSITION_TYPES transition)
{
    Scene* toTransition = GetLevel(newScene);
    if (toTransition != nullptr)
    {
        if (transition == TRANSITION_TYPES::NIL)
        {
            theDirector->replaceScene(toTransition);
        }
        else
        {
            TransitionSceneWithAnimations(toTransition, transition);
        }
    }
}

void SceneManager::TransitionSceneWithAnimations(Scene* newScene, TRANSITION_TYPES transition)
{
    switch (transition)
    {
        case TRANSITION_TYPES::FADE:
        {
            theDirector->replaceScene(TransitionFade::create(1, newScene));
            break;
        }
    }
}

Scene* SceneManager::GetSharedScene(string sceneName)
{
    std::map<string, Scene*>::iterator it = m_SharedScenesMap.find(sceneName);
    if (it != m_SharedScenesMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Scene* SceneManager::GetLevel(string sceneName)
{
    std::map<string, Scene*>::iterator it = m_LevelMap.find(sceneName);
    if (it != m_LevelMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void SceneManager::Shutdown()
{
    theDirector->popToSceneStackLevel(0);
}