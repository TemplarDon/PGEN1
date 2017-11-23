#include "SceneManager.h"
SceneManager *SceneManager::m_instance = 0;

SceneManager* SceneManager::GetInstance()
{
    if (m_instance == 0)
    {
        m_instance = new SceneManager();
    }

    return m_instance;
}

SceneManager::SceneManager()
{}
