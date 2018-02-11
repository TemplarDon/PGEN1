#include "ShopScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputHandler.h"
#include "SceneManagement/SceneManager.h"
#include "Player\PlayerInfo.h"

USING_NS_CC;

using namespace ui;

Scene* ShopScene::createScene()
{
    return ShopScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp/n");
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    // World
    auto nodeItems = Node::create();
    nodeItems->setName("nodeItems");
    this->addChild(nodeItems, 1);

    SetListeners();
    this->scheduleUpdate();

    // Title
    auto text = Label::createWithSystemFont("Cash Shop", "Arial", 32);
    text->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3.5));
    addChild(text, 5);

	// Amount of cash
	std::stringstream ss;
	ss << "Cash: " << PlayerInfo::GetInstance()->cash;

	cash_amount = Label::createWithSystemFont(ss.str().c_str(), "Arial", 32);
	cash_amount->setPosition(Point((visibleSize.width / 4) * 3.5, (visibleSize.height / 4) * 3.5));
	addChild(cash_amount, 5);

	successful_buy = Label::createWithSystemFont("Bought", "Arial", 32);
	successful_buy->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 6)));
	successful_buy->setVisible(false);
	successful_buy->setTextColor(cocos2d::Color4B::GREEN);
	addChild(successful_buy, 5);

	// When there isn't enough cash
	not_enough_cash = Label::createWithSystemFont("You do not have enough cash", "Arial", 32);
	not_enough_cash->setPosition(Point((visibleSize.width / 2) , (visibleSize.height / 6)));
	not_enough_cash->setVisible(false);
	not_enough_cash->setTextColor(cocos2d::Color4B::RED);
	addChild(not_enough_cash, 5);

	// When you already purchased the item
	cannot_buy_more = Label::createWithSystemFont("You can not buy any more", "Arial", 32);
	cannot_buy_more->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 6)));
	cannot_buy_more->setVisible(false);
	cannot_buy_more->setTextColor(cocos2d::Color4B::RED);
	addChild(cannot_buy_more, 5);

    // Buttons in Menu
    MenuItemFont* back_to_main_menu = MenuItemFont::create("  Back to \nMain Menu", CC_CALLBACK_1(ShopScene::BackToMainMenu, this));
    //MenuItemFont* menu_quit = MenuItemFont::create("Quit", CC_CALLBACK_1(ShopScene::menuCloseCallback, this));

	MenuItemFont* buy_heart = MenuItemFont::create("Buy Heart", CC_CALLBACK_1(ShopScene::BuyHeart, this));
	MenuItemFont* buy_potion = MenuItemFont::create("Buy Potion", CC_CALLBACK_1(ShopScene::BuyPotion, this));
	MenuItemFont* buy_skin = MenuItemFont::create("Buy Skin", CC_CALLBACK_1(ShopScene::BuySkin, this));

    auto* menu = Menu::create(back_to_main_menu, buy_heart, buy_potion, buy_skin, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setName("menu");
    menu->retain();

	back_to_main_menu->setPosition(Point(visibleSize.width / 6, (visibleSize.height / 4) * 3.5));
	back_to_main_menu->setFontSize(10000);
	back_to_main_menu->setFontSizeObj(32);

	buy_heart->setPosition(Point((visibleSize.width / 6), (visibleSize.height / 4) * 1.5));
	buy_heart->setFontSize(10000);
	buy_heart->setFontSizeObj(32);

	buy_potion->setPosition(Point((visibleSize.width / 6) * 3, (visibleSize.height / 4) * 1.5));
	buy_potion->setFontSize(10000);
	buy_potion->setFontSizeObj(32);

	buy_skin->setPosition(Point((visibleSize.width / 6) * 5, (visibleSize.height / 4) * 1.5));
	buy_skin->setFontSize(10000);
	buy_skin->setFontSizeObj(32);

    /*menu_quit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
	menu_quit->setFontSize(10000);
	menu_quit->setFontSizeObj(64);*/

	menu->setVisible(true);
    this->addChild(menu, 5);

	//Icons
	auto heart_icon = Sprite::create("hearticon.png");
	heart_icon->setPosition(Point((visibleSize.width / 6), (visibleSize.height / 4) * 2));
	nodeItems->addChild(heart_icon, 0);

	auto potion_icon = Sprite::create("potion_icon.png");
	potion_icon->setScale(0.5, 0.5);
	potion_icon->setPosition(Point((visibleSize.width / 6) * 3, (visibleSize.height / 4) * 2));
	nodeItems->addChild(potion_icon, 0);

	auto skin_icon = Sprite::create("skin_icon.png");
	skin_icon->setScale(1.5, 1.5);
	skin_icon->setPosition(Point((visibleSize.width / 6) * 5, (visibleSize.height / 4) * 2));
	nodeItems->addChild(skin_icon, 0);

    return true;
}

void ShopScene::update(float _dt)
{
    Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mainCam->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2)));
}

void ShopScene::SetListeners()
{
    // Keyboard Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ShopScene::OnKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(ShopScene::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void ShopScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void ShopScene::OnMouseEvent(Event* _event)
{
    /*EventMouse* mouseEvent = (EventMouse*)_event;

    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        auto target = static_cast<Sprite*>(_event->getCurrentTarget());
        string name = target->getName();

        if (name == "play_btn")
        {
            SceneManager::GetInstance()->TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE, true);
        }
        else if (name == "quit_btn")
        {
            SceneManager::GetInstance()->Shutdown();
        }
    }*/
}

void ShopScene::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
{

}

void ShopScene::BackToMainMenu(Ref *pSender)
{
    SceneManager::GetInstance()->TransitionLevel("menu", SceneManager::TRANSITION_TYPES::FADE);
}

void ShopScene::BuyHeart(cocos2d::Ref* pSender)
{
	successful_buy->setVisible(false);
	not_enough_cash->setVisible(false);
	cannot_buy_more->setVisible(false);

	//Cannot buy anymore -> Maxed Out hearts
	if (PlayerInfo::GetInstance()->GetMaxHealth() == 10)
	{
		cannot_buy_more->setVisible(true);
		cannot_buy_more->setString("You have maximum hearts");
		return; 
	}

	//Cannot buy -> Not enough cash
	if (PlayerInfo::GetInstance()->cash <= 200)
	{
		not_enough_cash->setVisible(true);
		return; 
	}

	PlayerInfo::GetInstance()->cash -= 200;
	UpdateCashAmount();

	PlayerInfo::GetInstance()->SetMaxHealth(PlayerInfo::GetInstance()->GetMaxHealth() + 1);

	std::stringstream ss;
	ss << "You bought a heart container!\nYou now have " << PlayerInfo::GetInstance()->GetMaxHealth() << " hearts";
	successful_buy->setVisible(true);
	successful_buy->setString(ss.str().c_str());
}

void ShopScene::BuyPotion(cocos2d::Ref* pSender)
{
	successful_buy->setVisible(false);
	not_enough_cash->setVisible(false);
	cannot_buy_more->setVisible(false);

	//Cannot buy -> Not enough cash
	if (PlayerInfo::GetInstance()->cash <= 100)
	{
		not_enough_cash->setVisible(true);
		return;
	}

	PlayerInfo::GetInstance()->cash -= 100;
	UpdateCashAmount();

	PlayerInfo::GetInstance()->AddHealthPotions(1);

	std::stringstream ss;
	ss << "You bought a potion!\nYou now have " << PlayerInfo::GetInstance()->GetNumberOfHealthPotions() << " potions";
	successful_buy->setVisible(true);
	successful_buy->setString(ss.str().c_str());
}

void ShopScene::BuySkin(cocos2d::Ref* pSender)
{
	successful_buy->setVisible(false);
	not_enough_cash->setVisible(false);
	cannot_buy_more->setVisible(false);

	//Cannot buy anymore -> Already bought
	if (PlayerInfo::GetInstance()->usingSkin)
	{
		cannot_buy_more->setVisible(true);
		cannot_buy_more->setString("You already have this skin");
		return;
	}

	//Cannot buy -> Not enough cash
	if (PlayerInfo::GetInstance()->cash <= 500)
	{
		not_enough_cash->setVisible(true);
		return;
	}

	PlayerInfo::GetInstance()->cash -= 500;
	UpdateCashAmount();

	PlayerInfo::GetInstance()->usingSkin = true;

	successful_buy->setVisible(true);
	successful_buy->setString("You bought a new skin!");
}


void ShopScene::UpdateCashAmount()
{
	std::stringstream ss;
	ss << "Cash: " << PlayerInfo::GetInstance()->cash;
	cash_amount->setString(ss.str().c_str());
}