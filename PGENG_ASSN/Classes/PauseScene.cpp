#include "PauseScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputHandler.h"
#include "SceneManagement/SceneManager.h"

USING_NS_CC;

using namespace ui;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp/n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
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

    auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

    float groundSpriteWidth = sprite->getContentSize().width;
    float  groundSpriteHeight = sprite->getContentSize().height;
    int numToRender = ceil(playingSize.width / groundSpriteWidth);

    float groundPosition = playingSize.height * 0.15f;

    for (int i = 0; i < numToRender; ++i)
    {
        auto tempSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        tempSprite->setAnchorPoint(Vec2::ZERO);
        tempSprite->setPosition(groundSpriteWidth * i, groundPosition);

        nodeItems->addChild(tempSprite, 0);
    }

    this->addChild(nodeItems, 1);

    SetListeners();
    this->scheduleUpdate();

    // Text
    auto text = Label::createWithSystemFont("PAUSE", "Arial", 32);
    text->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3.5));
    addChild(text, 5);

    // Menu
    MenuItemFont* menu_play = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseScene::Resume, this));
    MenuItemFont* menu_quit = MenuItemFont::create("Quit", CC_CALLBACK_1(PauseScene::Quit, this));

    auto *menu = Menu::create(menu_play, menu_quit, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setName("menu");
	menu_play->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
	menu_play->setFontSize(10000);
	menu_play->setFontSizeObj(64);

	menu_quit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
	menu_quit->setFontSize(10000);
	menu_quit->setFontSizeObj(64);

    this->addChild(menu, 5);

    return true;
}

void PauseScene::update(float _dt)
{
    Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mainCam->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2)));
}

void PauseScene::SetListeners()
{
    // Keyboard Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(PauseScene::OnKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PauseScene::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void PauseScene::menuCloseCallback(Ref* pSender)
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

void PauseScene::OnMouseEvent(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;

    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        auto target = static_cast<Sprite*>(_event->getCurrentTarget());
        string name = target->getName();

        if (name == "play_btn")
        {
            SceneManager::GetInstance().TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE, true);
        }
        else if (name == "quit_btn")
        {
            SceneManager::GetInstance().Shutdown();
        }
    }
}

void PauseScene::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
{

}

void PauseScene::Resume(Ref *pSender)
{
    SceneManager::GetInstance().PopSceneFromStack();
}

void PauseScene::Quit(Ref *pSender)
{
	SceneManager::GetInstance().PopSceneFromStack();
    SceneManager::GetInstance().TransitionLevel("menu", SceneManager::TRANSITION_TYPES::FADE);
}