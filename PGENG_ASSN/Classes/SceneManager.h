#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__


class SceneManager
{
    static SceneManager* m_instance;
    SceneManager();

public:
    static SceneManager* GetInstance()
    {
        if (!m_instance)
            m_instance = new SceneManager;
        return m_instance;
    }

};

#endif // __SCENE_MANAGER_H__
