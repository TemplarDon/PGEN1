#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d;

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

    // Callback functions
    void SetListeners();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);

	MenuItemFont* menu_play;

    virtual void update(float _dt);

    void Resume(cocos2d::Ref* pSender);
    void Quit(cocos2d::Ref* pSender);

};

#endif // __MAINEMENU_SCENE_H__
