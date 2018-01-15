#ifndef __MAINEMENU_SCENE_H__
#define __MAINEMENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

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

    // Callback functions
    void SetListeners();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);

    virtual void update(float _dt);

    void Play(cocos2d::Ref* pSender);

};

#endif // __MAINEMENU_SCENE_H__
