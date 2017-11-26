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

    //// Menu
    //MenuItemFont* menu_play = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuScene::Play, this));
    //MenuItemFont* menu_quit = MenuItemFont::create("Quit", CC_CALLBACK_1(MainMenuScene::Play, this));

    //menu_play->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    //menu_quit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));

    //auto *menu = Menu::create(menu_play, menu_quit, NULL);
    //menu->setPosition(Point(0, 0));
    //this->addChild(menu);

    //// Button
    //auto play_btn = Button::create("Button.png", "ButtonPressed.png");
    //play_btn->setTitleText("Spawn Girl");
    //play_btn->setTitleFontName("MarkerFelt.ttf");
    //play_btn->setTitleFontSize(12.0f);
    //play_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    //play_btn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
    //{
    //    switch (type)
    //    {
    //    case cocos2d::ui::Widget::TouchEventType::BEGAN:
    //        break;
    //    case cocos2d::ui::Widget::TouchEventType::MOVED:
    //        break;
    //    case cocos2d::ui::Widget::TouchEventType::ENDED:
    //        Play(this);
    //        break;
    //    case cocos2d::ui::Widget::TouchEventType::CANCELED:
    //        break;
    //    default:
    //        break;
    //    }
    //});
    //this->addChild(play_btn);
    
    auto spriteNode = Node::create();
    spriteNode->setName("ButtonsNode");

    play_btn = Sprite::create("Button.png");
    play_btn->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    play_btn->setName("play_btn");
    spriteNode->addChild(play_btn);

    quit_btn = Sprite::create("Button.png");
    quit_btn->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    quit_btn->setName("quit_btn");
    spriteNode->addChild(quit_btn);

    this->addChild(spriteNode);

 //   // Listener
	//auto touchListener = EventListenerTouchOneByOne::create();
 //   touchListener->setSwallowTouches(true);

 //   touchListener->onTouchBegan = [](Touch* touch, Event* event){

 //       auto target = static_cast<Sprite*>(event->getCurrentTarget());

 //       //Get the position of the current point relative to the button
 //       Point locationInNode = target->convertToNodeSpace(touch->getLocation());
 //       Size s = target->getContentSize();
 //       Rect rect = Rect(0, 0, s.width, s.height);

 //       //Check the click area
 //       if (rect.containsPoint(locationInNode))
 //       {
 //           target->setOpacity(180);
 //           return true;
 //       }
 //       return false;
 //   };

 //   touchListener->onTouchMoved = [](Touch* touch, Event* event){
 //   };

 //   touchListener->onTouchEnded = [](Touch* touch, Event* event){

 //       auto target = static_cast<Sprite*>(event->getCurrentTarget());

 //       if (target->getName() == "play_btn")
 //       {
 //           SceneManager::GetInstance().TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE);
 //       }
 //       else if (target->getName() == "quit_btn")
 //       {
 //           SceneManager::GetInstance().Shutdown();
 //       }

 //   };

 //   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
 //   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainMenuScene::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), play_btn);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), quit_btn);

    //InputHandler::GetInstance().AssignMouseAction(EventMouse::MouseButton::BUTTON_LEFT, bind(&MainMenuScene::OnLeftMouse, this), true);

    return true;
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

void MainMenuScene::OnLeftMouse()
{
    // Get mouse pos
 
}

void MainMenuScene::Play(Ref *pSender)
{
    SceneManager::GetInstance().TransitionLevel("test scene", SceneManager::TRANSITION_TYPES::FADE);
}
