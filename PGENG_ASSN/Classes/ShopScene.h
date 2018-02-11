#ifndef __SHOPSCENE_SCENE_H__
#define __SHOPSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class ShopScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);

    // Callback functions
    void SetListeners();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);

    virtual void update(float _dt);

    void BackToMainMenu(cocos2d::Ref* pSender);

	void BuyHeart(cocos2d::Ref* pSender);
	void BuyPotion(cocos2d::Ref* pSender);
	void BuySkin(cocos2d::Ref* pSender);

	void UpdateCashAmount();

	Label* cash_amount;
	Label* not_enough_cash;
	Label* cannot_buy_more;
	Label* successful_buy;
};

#endif // __MAINEMENU_SCENE_H__
