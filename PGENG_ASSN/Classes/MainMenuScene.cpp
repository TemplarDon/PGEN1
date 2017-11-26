#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Input\InputHandler.h"
#include "SceneManagement\SceneManager.h"

USING_NS_CC;

using namespace ui;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainMenuScene::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Menu
    MenuItemFont* menu_play = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuScene::Play, this));
    MenuItemFont* menu_quit = MenuItemFont::create("Quit", CC_CALLBACK_1(MainMenuScene::Play, this));

    auto *menu = Menu::create(menu_play, menu_quit, nullptr);
    menu->setPosition(Point(0, 0));

    menu_play->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menu_quit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));

    this->addChild(menu);
    this->scheduleUpdate();

    return true;
}

void MainMenuScene::update(float _dt)
{

}

void MainMenuScene::menuCloseCallback(Ref* pSender)
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

void MainMenuScene::OnMouseEvent(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;

    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        auto target = static_cast<Sprite*>(_event->getCurrentTarget());
        string name = target->getName();

        if (name == "play_btn")
        {
            SceneManager::GetInstance().TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE);
        }
        else if (name == "quit_btn")
        {
            SceneManager::GetInstance().Shutdown();
        }
    }
}

void MainMenuScene::Play(Ref *pSender)
{
    SceneManager::GetInstance().TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE);
}
