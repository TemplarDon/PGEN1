#include "SceneManager.h"
#include "Input/InputHandler.h"

SceneManager::SceneManager()
{
    if (Node::init())
        init();
}

SceneManager::~SceneManager()
{
    //Shutdown();
}

bool SceneManager::init()
{
    if (!Node::init())
    {
        return false;
    }

    theDirector = Director::getInstance();
    //theDirector->init();

    greyscaleShader = GLProgram::createWithFilenames("Shaders/Basic.vsh", "Shaders/GreyScale.fsh");
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    greyscaleShader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

    greyscaleShader->link();
    greyscaleShader->updateUniforms();

    greyscaleShader->retain();
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

void SceneManager::ReloadScene()
{
    Scene* currScene = theDirector->getRunningScene();
    Node* actualScene = currScene->getChildByName("Scene");

    actualScene->removeAllChildren();
    currScene->removeAllChildren();
    actualScene->init();
    currScene->init();

    currScene->addChild(actualScene);

    /*
            Node* scene = nullptr;
        if (hasPhysicsParentLayer)
        {
            scene = toTransition->getChildByName("Scene");
            scene->removeAllChildren(); 
        }
        toTransition->removeAllChildren();

        if (hasPhysicsParentLayer)
        {
            scene->init();
            toTransition->addChild(scene);
        }
        else
        {
            toTransition->init();
        }

        if (transition == TRANSITION_TYPES::NIL)
        {
            theDirector->replaceScene(toTransition);
        }
        else
        {
            TransitionSceneWithAnimations(toTransition, transition);
        }
    */
}

void SceneManager::FinishSetup()
{
    InputHandler::GetInstance().ClearActionMaps();
}

void SceneManager::AddSceneToStack(string name, bool leaveOldScene)
{
    Scene* toAdd = GetSharedScene(name);

    if (toAdd == theDirector->getRunningScene())
        return;

    if (toAdd)
    {
        Scene* oldScene = theDirector->getRunningScene();

        toAdd->removeAllChildren();
        toAdd->init();

        if (leaveOldScene)
        {
            toAdd->removeChildByName("pause_bg");
            Layer* newLayer = CreateLayerFromScene(oldScene);
            newLayer->setName("pause_bg");
            toAdd->addChild(newLayer, -1);
        }

        theDirector->pushScene(toAdd); 
    }
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

Layer* SceneManager::CreateLayerFromScene(Scene* sourceScene)
{
    if (sourceScene)
    {
        RenderTexture* rendtex = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
        Sprite* rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());

        rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
        //sourceScene->visit();
        /*Director::getInstance()->getRenderer(), Camera::getDefaultCamera()->getPosition(), Camera::getDefaultCamera()->getCameraFlag()*/

        //sourceScene->getDefaultCamera()->visit(Director::getInstance()->getRenderer(), sourceScene->getDefaultCamera()->getProjectionMatrix(), true);

        rendtex->end();
        rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
        rendtexSprite->setName("prevscene_bg");
        rendtexSprite->setPosition(theDirector->getVisibleSize().width * 0.5, theDirector->getVisibleSize().height * 0.5);
        rendtexSprite->setFlipY(true);
        rendtexSprite->setGLProgram(greyscaleShader);

        Layer* returnLayer = Layer::create();
        returnLayer->addChild(rendtexSprite, -1);
        returnLayer->retain();
        return returnLayer;
    }
}

void SceneManager::AddLayerToScene(string sceneToAddTo, string layer)
{
    RenderTexture* rendtex;
    Sprite* rendtexSprite;

    rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    GetLevel(layer)->visit();
    rendtex->end();
    rendtexSprite->setTexture(rendtex->getSprite()->getTexture());

    GetLevel(sceneToAddTo)->addChild(rendtexSprite);
}

void SceneManager::TransitionLevel(string newScene, TRANSITION_TYPES transition, bool hasPhysicsParentLayer)
{
    Scene* toTransition = GetLevel(newScene);

    if (toTransition == theDirector->getRunningScene())
        return;

    if (toTransition != nullptr)
    {
        Node* scene = nullptr;
        if (hasPhysicsParentLayer)
        {
            scene = toTransition->getChildByName("Scene");
            scene->removeAllChildren(); 
        }
        toTransition->removeAllChildren();

        if (hasPhysicsParentLayer)
        {
            scene->init();
            toTransition->addChild(scene);
        }
        else
        {
            toTransition->init();
        }

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
            theDirector->replaceScene(TransitionFade::create(1.5, newScene));
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
    // release
    for (auto it : m_LevelMap)
    {
        it.second->release();
    }

    for (auto it : m_SharedScenesMap)
    {
        it.second->release();
    }

    // pop all scenes away
    theDirector->popToSceneStackLevel(0);

    theDirector->end();
}