#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    //return HelloWorld::create();

    auto scene = Scene::createWithPhysics();

    auto layer = HelloWorld::create();
	layer->setName("Scene");
	layer->retain();

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.


	/* Comment out the entire scene
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	*/

    // Character	
    auto spriteNode = Node::create();
    spriteNode->setName("SpriteNode");

    auto characterSprite = Sprite::create("Blue_Front1.png");
    characterSprite->setName("MainCharacter");
    characterSprite->setAnchorPoint(Vec2::ZERO);
    characterSprite->setPosition(0, playingSize.height * 0.5);

    auto physics = PhysicsBody::createBox(characterSprite->getContentSize(), PhysicsMaterial(0.1f, 0.1f, 0.0f));
    physics->setDynamic(true);
    characterSprite->addComponent(physics);

    spriteNode->addChild(characterSprite, 1);

    //// Character Movement
    //auto moveEvent = MoveBy::create(5.0f, Vec2(5.0f, 0));
    //characterSprite->runAction(moveEvent->clone());

    // Add to this node tree
    this->addChild(spriteNode, 1);

    // World: floor
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

        auto physics = PhysicsBody::createBox(tempSprite->getContentSize(), PhysicsMaterial(0.1f, 0.1f, 0.0f));
        physics->setDynamic(false);
        tempSprite->addComponent(physics);

        nodeItems->addChild(tempSprite, 0);
    }

    this->addChild(nodeItems, 1);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
