#ifndef __MAINEMENU_SCENE_H__
#define __MAINEMENU_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d;

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

    virtual void update(float _dt);

    void OnMouseEvent(Event* _event);
    void Play(Ref *pSender);
};

#endif // __MAINEMENU_SCENE_H__
