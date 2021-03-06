#include "PathfinderTest.h"
#include "Input/InputHandler.h"
#include "SceneManagement/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "Animation/SpriteBuilder.h"

#include "FSM/PatrollingFSM.h"

#define COCOS2D_DEBUG 1
#define FSM_TAG 5

using namespace CocosDenshion;

USING_NS_CC;

Scene* PathfinderTest::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("PhysicsBase");

    auto layer = PathfinderTest::create();

    layer->setName("Scene");
    layer->retain();

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PathfinderPathfinderTest.cpp/n");
}

// on "init" you need to initialize your instance
bool PathfinderTest::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    // Reset all binded actions 
    InputHandler::GetInstance()->ClearActionMaps();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    // World
    //auto nodeItems = Node::create();
    //nodeItems->setName("nodeItems");

    //auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

    //float groundSpriteWidth = sprite->getContentSize().width;
    //float  groundSpriteHeight = sprite->getContentSize().height;
    //int numToRender = ceil(playingSize.width / groundSpriteWidth);

    //float groundPosition = playingSize.height * 0.5f;

    //for (int i = 0; i < numToRender; ++i)
    //{
    //    auto tempSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
    //    tempSprite->setAnchorPoint(Vec2::ZERO);
    //    tempSprite->setPosition(groundSpriteWidth * i, groundPosition);

    //    nodeItems->addChild(tempSprite, 0);
    //}

    // Character	
    auto spriteNode = Node::create();
    spriteNode->setName("SpriteNode");

    auto characterSprite = Sprite::create("Blue_Front1.png");
    characterSprite->setName("MainCharacter");
    characterSprite->setAnchorPoint(Vec2::ZERO);
    characterSprite->setPosition(250, 250);
    characterSprite->setScale(0.2);

    // PhysicsBody
    auto physicsBody = PhysicsBody::createBox(
        characterSprite->getContentSize(),
        PhysicsMaterial(0.1f, 0, 0.0f)
        );

    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);
    
    physicsBody->setCategoryBitmask(PLAYER_BITMASK);
    physicsBody->setCollisionBitmask(ENEMY_BITMASK | WALLS_BITMASK); 
    physicsBody->setContactTestBitmask(ENEMY_BITMASK | WALLS_BITMASK);

    characterSprite->addComponent(physicsBody);

    spriteNode->addChild(characterSprite, 1);


    //auto characterSprite2 = Sprite::create("Blue_Front1.png");
    //characterSprite2->setName("MainCharacter2");
    //characterSprite2->setAnchorPoint(Vec2::ZERO);
    //characterSprite2->setPosition(250, 100);
    //characterSprite2->setScale(0.4);

    //// PhysicsBody2
    //auto physicsBody2 = PhysicsBody::createBox(
    //    characterSprite2->getContentSize(),
    //    PhysicsMaterial(0.1f, 1.0f, 0.0f)
    //    );

    //physicsBody2->setDynamic(true);
    //physicsBody2->setGravityEnable(false);
    //physicsBody2->setRotationEnable(false);
    //
    //physicsBody2->setCategoryBitmask(NEUTRAL_BITMASK);
    //physicsBody2->setCollisionBitmask(ENEMY_BITMASK);
    //physicsBody2->setContactTestBitmask(ENEMY_BITMASK);

    //characterSprite2->addComponent(physicsBody2);

    //spriteNode->addChild(characterSprite2, 1);

    //Animation Controller
    animController = new AnimationController();
    animController->Init(characterSprite);

    // Character Movement
    //auto moveEvent = MoveBy::create(5.0f, Vec2(5.0f, 0));
    //characterSprite->runAction(moveEvent->clone());

    // Delayed Action
    //DelayTime* delay = DelayTime::create(5.0f);
    //Sequence* delaySequence = Sequence::create(delay, delay->clone(), nullptr);
    //Sequence* sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);

    //characterSprite->runAction(sequence);

    // Add to this node tree
    //this->addChild(nodeItems, 1);
    this->addChild(spriteNode, 1);

    // Use this function to assign functions to specific key press
    InputHandler::GetInstance()->AssignMouseAction(EventMouse::MouseButton::BUTTON_LEFT, bind(&PathfinderTest::InputMouseTestFunction, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&PathfinderTest::InputKeyboardTestFunction, this), true);

    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_Z, bind(&PathfinderTest::SwitchSceneTestFunction, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_X, bind(&PathfinderTest::AddSceneTestFunction, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_C, bind(&PathfinderTest::PopSceneTestFunction, this), true);

    //Stops animation when movement buttons are released
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&PathfinderTest::StopAnimation, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&PathfinderTest::StopAnimation, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&PathfinderTest::StopAnimation, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&PathfinderTest::StopAnimation, this), false, false, true);

    //Add Moveplayer when button is press and held
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&PathfinderTest::MovePlayerUp, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&PathfinderTest::MovePlayerDown, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&PathfinderTest::MovePlayerLeft, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&PathfinderTest::MovePlayerRight, this), true);

    //Add Moveplayer when button is released
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&PathfinderTest::StopPlayerUp, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&PathfinderTest::StopPlayerDown, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&PathfinderTest::StopPlayerLeft, this), false, false, true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&PathfinderTest::StopPlayerRight, this), false, false, true);

    //Play walking sound effect when movement buttons are pressed
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&PathfinderTest::PlayWalkingSoundEffect, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&PathfinderTest::PlayWalkingSoundEffect, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&PathfinderTest::PlayWalkingSoundEffect, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&PathfinderTest::PlayWalkingSoundEffect, this), true);

    SetListeners();
    InitAnimationActions();
    InitShader();
    InitTilemap();
    InitFSM();
    scheduleUpdate();

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio/BGM.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    return true;
}

void PathfinderTest::update(float _dt)
{
    auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");

    UpdatePlayer();

    // NOT THE BEST WAY PROBABLY, BETTER TO HAVE ENTITY CLASS WITH UPDATE
    Vector<Node*> myVector = getChildren();
    Vector<Node*>::iterator myIterator;

    for (myIterator = myVector.begin(); myIterator != myVector.end(); ++myIterator)
    {
        auto mySprite = *myIterator;

        if (mySprite->getTag() == FSM_TAG)
        {
            dynamic_cast<BaseFSM*>(mySprite)->RunFSM();
        }
    }

    //UpdateFSM();

    Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
    mainCam->setPosition(charSprite->getPosition());

    //rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //this->visit();
    //rendtex->end();
    //rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setGLProgram(proPostProcess);
}

void PathfinderTest::InitShader()
{
    //Vec2 mLoc(0.5f, 0.5f);
    //
    //// Specific order according to shaders
    //auto shaderCharEffect = new GLProgram();
    //shaderCharEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
    //shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    //shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    //shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

    //shaderCharEffect->link();
    //shaderCharEffect->updateUniforms();

    //GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
    //
    //auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //charSprite->setGLProgram(shaderCharEffect);
    //charSprite->setGLProgramState(state);
    //state->setUniformVec2("loc", mLoc);

    //proPostProcess = GLProgram::createWithFilenames("Shaders/Basic.vsh", "Shaders/GreyScale.fsh");
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    //proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

    //proPostProcess->link();
    //proPostProcess->updateUniforms();

    //rendtex = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
    //rendtex->retain();

    //rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
    //rendtexSprite->setAnchorPoint(Point::ZERO);
    //rendtexSprite->setPosition(Point::ZERO);
    //rendtexSprite->setFlippedY(true);
    //rendtexSprite->setGLProgram(proPostProcess);
    //this->addChild(rendtexSprite, 2);
}

void PathfinderTest::InitAnimationActions()
{
    AnimateBuilder::GetInstance()->LoadSpriteSheet("sprite sheet", "spritesheet_test.png", 6, 3);
    AnimateBuilder::GetInstance()->LoadAnimateFromLoadedSpriteSheet("Special1", "sprite sheet", 6, 12);	//Only half of the sprite sheet

    AnimateBuilder::GetInstance()->LoadAnimateFromWholeSpriteSheet("Special2", "spritesheet_test.png", 6, 3);	//Whole sprite sheet

    AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Front", { "Blue_Front2.png", "Blue_Front1.png", "Blue_Front3.png", "Blue_Front1.png" });
    AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Back", { "Blue_Back2.png", "Blue_Back1.png", "Blue_Back3.png", "Blue_Back1.png" });
    AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Left", { "Blue_Left2.png", "Blue_Left1.png", "Blue_Left3.png", "Blue_Left1.png" });
    AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Right", { "Blue_Right2.png", "Blue_Right1.png", "Blue_Right3.png", "Blue_Right1.png" });

    animController->AddAnimate("Special1", AnimateBuilder::GetInstance()->GetAnimate("Special1"));
    animController->AddAnimate("Special2", AnimateBuilder::GetInstance()->GetAnimate("Special2"));
    animController->AddAnimate("Front", AnimateBuilder::GetInstance()->GetAnimate("Front"));
    animController->AddAnimate("Back", AnimateBuilder::GetInstance()->GetAnimate("Back"));
    animController->AddAnimate("Left", AnimateBuilder::GetInstance()->GetAnimate("Left"));
    animController->AddAnimate("Right", AnimateBuilder::GetInstance()->GetAnimate("Right"));
    /*Vector<SpriteFrame*> frontFrames;
    frontFrames.reserve(4);

    frontFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
    frontFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
    frontFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
    frontFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

    Animation* frontAnimation = Animation::createWithSpriteFrames(frontFrames, 0.5f);
    Animate* animateFront = Animate::create(frontAnimation);

    v_mainCharAnimation[FRONT] = animateFront;

    Vector<SpriteFrame*> backFrames;
    backFrames.reserve(4);

    backFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
    backFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
    backFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
    backFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));

    Animation* backAnimation = Animation::createWithSpriteFrames(backFrames, 0.5f);
    Animate* animateBack = Animate::create(backAnimation);

    v_mainCharAnimation[BACK] = animateBack;

    Vector<SpriteFrame*> leftFrames;
    leftFrames.reserve(4);

    leftFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
    leftFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
    leftFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
    leftFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));

    Animation* leftAnimation = Animation::createWithSpriteFrames(leftFrames, 0.5f);
    Animate* animateLeft = Animate::create(leftAnimation);

    v_mainCharAnimation[LEFT] = animateLeft;

    Vector<SpriteFrame*> rightFrames;
    rightFrames.reserve(4);

    rightFrames.pushBack(SpriteFrame::create("Blue_right2.png", Rect(0, 0, 65, 81)));
    rightFrames.pushBack(SpriteFrame::create("Blue_right1.png", Rect(0, 0, 65, 81)));
    rightFrames.pushBack(SpriteFrame::create("Blue_right3.png", Rect(0, 0, 65, 81)));
    rightFrames.pushBack(SpriteFrame::create("Blue_right1.png", Rect(0, 0, 65, 81)));

    Animation* rightAnimation = Animation::createWithSpriteFrames(rightFrames, 0.5f);
    Animate* animateRight = Animate::create(rightAnimation);

    v_mainCharAnimation[RIGHT] = animateRight;

    for (int i = 0; i < NUM_ANIM; ++i)
    {
    v_mainCharAnimation[i]->retain();
    }*/


    // FSM animations
    AnimateBuilder::GetInstance()->LoadSpriteSheet("patrol", "spritesheet_patrol.png", 4, 9);
}

void PathfinderTest::InitTilemap()
{
    auto map = TMXTiledMap::create("Map/Dungeon.tmx");
    addChild(map, 0, 99);
    //auto layer = map->getLayer("Layer0");

    // Disable collidemap layer
    map->getLayer("CollideMap")->setVisible(false);
    map->getLayer("InaccessibleMap")->setVisible(false);
 
    // Create collision boxes
    auto collisionNode = Node::create();
    collisionNode->setName("collisionNode");

    auto collideMap = map->layerNamed("CollideMap");

    int width = map->getMapSize().width;
    int height = map->getMapSize().height;

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            // Check if tile is in collidemap
            auto colllide_sprite = collideMap->tileAt(Vec2(x, y));

            if (colllide_sprite)
            {
                Vec2 pos = collideMap->tileAt(Vec2(x, y))->getPosition();
                auto aNode = Node::create();
                aNode->setPosition(pos);

                Size sz = map->getTileSize();
                auto physicsBody = PhysicsBody::createBox(
                    sz,
                    PhysicsMaterial(0.1f, 0, 0.0f)
                    );

                physicsBody->setDynamic(false);

                physicsBody->setCategoryBitmask(WALLS_BITMASK);
                physicsBody->setCollisionBitmask(PLAYER_BITMASK | ENEMY_BITMASK);
                physicsBody->setContactTestBitmask(PLAYER_BITMASK | ENEMY_BITMASK);
                aNode->addComponent(physicsBody);

                collisionNode->addChild(aNode);
            }
        }
    }

    addChild(collisionNode);

}

void PathfinderTest::InitFSM()
{
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(99);

    auto enemySpawnGroup = map->getObjectGroup("Spawns");

    if (enemySpawnGroup != nullptr)
    {
        auto enemySpawns = enemySpawnGroup->getObjects();

        int count = 0;
        for (auto &itr : enemySpawns)
        {
            auto point = itr.asValueMap();
            Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

            if (!point["isPlayerSpawn"].asBool())
            {
                stringstream ss;
                ss << count;
                string str = ss.str();

                PatrollingFSM* testFSM = new PatrollingFSM(map, "White_Front1.png");
                testFSM->setName("patrollingFSM" + str);
                testFSM->setTag(FSM_TAG);
                testFSM->setPosition(pos);
                addChild(testFSM);

                ++count;
            }
            else
            {
                // set player pos
                auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
                charSprite->setPosition(pos);

                spawnPos = pos;
            }
        }
    }
}

void PathfinderTest::SetListeners()
{
    // Keyboard Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(PathfinderTest::OnKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PathfinderTest::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Contact Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PathfinderTest::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void PathfinderTest::menuCloseCallback(Ref* pSender)
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

void PathfinderTest::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
{
    //switch (_keycode)
    //{
    //	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    //	{
    //		auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //		auto moveEvent = MoveBy::create(0.0f, Vec2(10.0f, 0));
    //		//charSprite->stopActionByTag(1);
    //		charSprite->runAction(moveEvent);
    //	}
    //	break;

    //	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
    //	{
    //		auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //		auto moveEvent = MoveBy::create(0.0f, Vec2(-10.0f, 0));
    //           //charSprite->stopAllActions();
    //		charSprite->runAction(moveEvent);
    //	}
    //	break;

    //	case EventKeyboard::KeyCode::KEY_K:
    //	{
    //		CCDirector::getInstance()->replaceScene(
    //			TransitionFlipAngular::create(1.5, PathfinderTest::createScene())
    //		);
    //	}
    //	break;
    //}
}

void PathfinderTest::OnMouseEvent(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;

    //if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    //{
    //	Vec2 mousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

    //	auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //	charSprite->stopAllActions();

    //	auto moveEvent = MoveTo::create(1.0f, mousePos);
    //	charSprite->runAction(moveEvent);

    //	float mouseXChange = mousePos.x - charSprite->getPosition().x;
    //	float mouseYChange = mousePos.y - charSprite->getPosition().y;

    //	if (fabs(mouseXChange) > fabs(mouseYChange))
    //	{
    //		if (mouseXChange > 0)
    //			charSprite->runAction(RepeatForever::create(v_mainCharAnimation[RIGHT]));
    //		else
    //			charSprite->runAction(RepeatForever::create(v_mainCharAnimation[LEFT]));
    //	}
    //	else
    //	{
    //		if (mouseYChange > 0)
    //			charSprite->runAction(RepeatForever::create(v_mainCharAnimation[BACK]));
    //		else
    //			charSprite->runAction(RepeatForever::create(v_mainCharAnimation[FRONT]));
    //	}
    //}
}

bool PathfinderTest::onContactBegin(PhysicsContact& contact)
{
    auto shapeA = contact.getShapeA()->getBody();
    auto shapeB = contact.getShapeB()->getBody();

    if ((shapeA->getCategoryBitmask() & shapeB->getCollisionBitmask()) == 0
        || (shapeB->getCategoryBitmask() & shapeA->getCollisionBitmask()) == 0)
    {
        // shapes can't collide
        return false;
    }

    // PLAYER & ENEMY
    //if ((shapeA->getCategoryBitmask() == PLAYER_BITMASK & shapeB->getCollisionBitmask() == ENEMY_BITMASK) == 0
    //    || (shapeB->getCategoryBitmask() == ENEMY_BITMASK & shapeA->getCollisionBitmask() == PLAYER_BITMASK) == 0)
    if ((shapeA->getCategoryBitmask() == PLAYER_BITMASK && shapeB->getCategoryBitmask() == ENEMY_BITMASK)
        || (shapeB->getCategoryBitmask() == ENEMY_BITMASK && shapeA->getCategoryBitmask() == PLAYER_BITMASK))
    {
        CCLOG("Player reset pos");

        if (shapeA->getCategoryBitmask() == PLAYER_BITMASK)
        {
            shapeA->getNode()->setPosition(spawnPos);
            shapeA->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }
        else
        {
            shapeB->getNode()->setPosition(spawnPos);
            shapeB->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }

        return false;
    }

    // PLAYER & WALL
    if ((shapeA->getCategoryBitmask() == PLAYER_BITMASK && shapeB->getCategoryBitmask() == WALLS_BITMASK)
        || (shapeB->getCategoryBitmask() == WALLS_BITMASK && shapeA->getCategoryBitmask() == PLAYER_BITMASK))
    {
        if (shapeA->getCategoryBitmask() == PLAYER_BITMASK)
        {
            shapeA->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }
        else
        {
            shapeB->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }
        return false;
    }

    // ENEMY & WALL
    if ((shapeA->getCategoryBitmask() == ENEMY_BITMASK && shapeB->getCategoryBitmask() == WALLS_BITMASK)
        || (shapeB->getCategoryBitmask() == WALLS_BITMASK && shapeA->getCategoryBitmask() == ENEMY_BITMASK))
    {
        if (shapeA->getCategoryBitmask() == ENEMY_BITMASK)
        {
            shapeA->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }
        else
        {
            shapeB->getNode()->getPhysicsBody()->setVelocity(Vec2(0, 0));
        }
        return false;
    }

    return true;
}

void PathfinderTest::InputMouseTestFunction()
{
    CCLOG("Mouse Function");
}

void PathfinderTest::InputKeyboardTestFunction()
{
    CCLOG("Keyboard Function");
}

void PathfinderTest::SwitchSceneTestFunction()
{
    SceneManager::GetInstance()->TransitionLevel("menu", SceneManager::TRANSITION_TYPES::FADE);
}

void PathfinderTest::AddSceneTestFunction()
{
    SceneManager::GetInstance()->AddSceneToStack("ello scene", true);
}

void PathfinderTest::PopSceneTestFunction()
{
    SceneManager::GetInstance()->PopSceneFromStack();
}

void PathfinderTest::SwitchSceneTest(cocos2d::Ref* pSender)
{
    SceneManager::GetInstance()->TransitionLevel("menu", SceneManager::TRANSITION_TYPES::FADE);
}

void PathfinderTest::MovePlayerUp()
{
    //auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //charSprite->stopAllActions();

    animController->PlayAnimation("Back");

    shouldMoveUp = true;

    //auto moveEvent = MoveBy::create(0, Vec2(0, 10));
    //charSprite->runAction(moveEvent);

    //CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Walking.wav");
}

void PathfinderTest::MovePlayerDown()
{
    //auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //charSprite->stopAllActions();

    animController->PlayAnimation("Front");

    shouldMoveDown = true;

    //auto moveEvent = MoveBy::create(0, Vec2(0, -10));
    //charSprite->runAction(moveEvent);

    // CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Walking.wav");
}

void PathfinderTest::MovePlayerLeft()
{
    //auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //charSprite->stopAllActions();

    animController->PlayAnimation("Left");

    shouldMoveLeft = true;

    // auto moveEvent = MoveBy::create(0, Vec2(-10, 0));
    //charSprite->runAction(moveEvent);

    //CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Walking.wav");
}

void PathfinderTest::MovePlayerRight()
{
    //auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
    //charSprite->stopAllActions();

    animController->PlayAnimation("Right");

    shouldMoveRight = true;

    //auto moveEvent = MoveBy::create(0,  Vec2(10, 0));
    //charSprite->runAction(moveEvent);

    //CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Walking.wav");

}

void PathfinderTest::StopPlayerUp()
{
    shouldMoveUp = false;
}

void PathfinderTest::StopPlayerDown()
{
    shouldMoveDown = false;
}

void PathfinderTest::StopPlayerLeft()
{
    shouldMoveLeft = false;
}

void PathfinderTest::StopPlayerRight()
{
    shouldMoveRight = false;
}

void PathfinderTest::MovePlayer()
{
    auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");

    if (shouldMoveLeft)
    {
        //auto moveEvent = MoveBy::create(0, Vec2(-5, 0));
        //charSprite->runAction(moveEvent);

        charSprite->getPhysicsBody()->setVelocity(Vec2(-100, 0));
    }

    if (shouldMoveRight)
    {
        //auto moveEvent = MoveBy::create(0, Vec2(5, 0));
        //charSprite->runAction(moveEvent);

        charSprite->getPhysicsBody()->setVelocity(Vec2(100, 0));
    }

    if (shouldMoveUp)
    {
        //auto moveEvent = MoveBy::create(0, Vec2(0, 5));
        //charSprite->runAction(moveEvent);

        charSprite->getPhysicsBody()->setVelocity(Vec2(0, 100));

    }

    if (shouldMoveDown)
    {
        //auto moveEvent = MoveBy::create(0, Vec2(0, -5));
        //charSprite->runAction(moveEvent);

        charSprite->getPhysicsBody()->setVelocity(Vec2(0, -100));

    }
}

void PathfinderTest::UpdatePlayer()
{
    if (shouldMoveLeft)
        MovePlayerLeft();

    if (shouldMoveRight)
        MovePlayerRight();

    if (shouldMoveUp)
        MovePlayerUp();

    if (shouldMoveDown)
        MovePlayerDown();


    MovePlayer();


    if (InputHandler::GetInstance()->GetKeyDown(EventKeyboard::KeyCode::KEY_1))
        animController->PlayAnimation("Special1", false);

    if (InputHandler::GetInstance()->GetKeyDown(EventKeyboard::KeyCode::KEY_2))
        animController->PlayAnimation("Special2", false);

}

void PathfinderTest::UpdateFSM()
{

}

void PathfinderTest::StopAnimation()
{
    animController->StopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void PathfinderTest::PlayWalkingSoundEffect()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Walking.wav");
}