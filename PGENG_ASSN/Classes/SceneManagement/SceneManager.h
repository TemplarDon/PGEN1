#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "Classes\Common\SingletonNode.h"

using namespace cocos2d;
using namespace std;

class SceneManager : public SingletonNode<SceneManager>
{
    friend SingletonNode <SceneManager>;

public:
    SceneManager();
    ~SceneManager();

    enum TRANSITION_TYPES
    {
        NIL,
        FADE,
        NUM_TYPES,
    };

    bool init();
    void Start(Scene* initialScene);
    void AddLevel(string name, Scene* toAdd);
    void AddSharedScene(string name, Scene* toAdd);

    void AddSceneToStack(string name, bool leaveOldScene = false);
    void PopSceneFromStack(int popToLevel = -1);

    Scene* GetSharedScene(string sceneName);
    Scene* GetLevel(string levelName);

    void TransitionLevel(string newScene, TRANSITION_TYPES transition = TRANSITION_TYPES::NIL);

    void Shutdown();

private:
    static SceneManager* m_instance;

    Director* theDirector;
    string currentScene;

    map<string, Scene*> m_LevelMap;
    map<string, Scene*> m_SharedScenesMap;

    GLProgram* greyscaleShader;

    void TransitionSceneWithAnimations(Scene* newScene, TRANSITION_TYPES transition);
    Layer* CreateLayerFromScene(Scene* scene);
    void AddLayerToScene(string sceneToAddTo, string layer);

};

#endif // __SCENE_MANAGER_H__
