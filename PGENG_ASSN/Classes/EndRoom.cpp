#include "EndRoom.h"
#include "Input\InputHandler.h"
#include "SceneManagement\SceneManager.h"
#include "SimpleAudioEngine.h"
#include "Animation\SpriteBuilder.h"
#include "Interactables\HeartDrops.h"

#include "FSM\PatrollingFSM.h"
#include "Puzzle\Puzzle.h"
#include "Puzzle\Button.h"
#include "Puzzle\ChainedPressurePlate.h"
#include "Interactables\Exit.h"
#include "Player\PlayerInfo.h"

#define COCOS2D_DEBUG 1
#define FSM_TAG 5

using namespace CocosDenshion;

USING_NS_CC;

Scene* EndRoom::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("PhysicsBase");

    auto layer = EndRoom::create();

    layer->setName("Scene");
    layer->retain();

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PathfinderEndRoom.cpp\n");
}

// on "init" you need to initialize your instance
bool EndRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    // Reset all binded actions 
    InputHandler::GetInstance().ClearActionMaps();

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
    //auto spriteNode = Node::create();
    //spriteNode->setName("SpriteNode");

    //auto characterSprite = Sprite::create("Blue_Front1.png");
    //characterSprite->setName("MainCharacter");
    //characterSprite->setAnchorPoint(Vec2::ZERO);
    //characterSprite->setPosition(250, 250);
    //characterSprite->setScale(0.2);

    //// PhysicsBody
    //auto physicsBody = PhysicsBody::createBox(
    //    characterSprite->getContentSize(),
    //    PhysicsMaterial(0.1f, 0, 0.0f)
    //    );

    //physicsBody->setDynamic(true);
    //physicsBody->setGravityEnable(false);
    //physicsBody->setRotationEnable(false);

    //physicsBody->setCategoryBitmask(PLAYER_BITMASK);
    //physicsBody->setCollisionBitmask(ENEMY_BITMASK | WALLS_BITMASK);
    //physicsBody->setContactTestBitmask(ENEMY_BITMASK | WALLS_BITMASK);

    //characterSprite->addComponent(physicsBody);

    //spriteNode->addChild(characterSprite, 1);


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
    //animController = new AnimationController();
    //animController->Init(characterSprite);

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
    //this->addChild(spriteNode, 1);

    // Use this function to assign functions to specific key press
    InputHandler::GetInstance().AssignMouseAction(EventMouse::MouseButton::BUTTON_LEFT, bind(&EndRoom::InputMouseTestFunction, this), true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&EndRoom::InputKeyboardTestFunction, this), true);

    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_TAB, bind(&EndRoom::Pause, this), true);

    //InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_L, bind(&EndRoom::SpawnNPC, this), true);

    //Init Player
    player = new Player();
    player->init();
    player->setName("player");
    player->getPhysicsBody()->setTag(PHYSICS_TAG_PLAYER);
    addChild(player, 99);

    SetListeners();
    InitAnimationActions();
    InitShader();
    InitTilemap();
    InitFSM();
    InitEnvironment();
    scheduleUpdate();

    SpawnNPC();

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio/BGM.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);

    cameraOrthoScale.set(234, 160);
    runAction(DelayTime::create(2.0f));

    PlayerInfo::GetInstance().SetHighScore(PlayerInfo::GetInstance().GetScore());

    return true;
}

void EndRoom::update(float _dt)
{
    auto charSprite = this->getChildByName("player");

    Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
    mainCam->initOrthographic(cameraOrthoScale.x, cameraOrthoScale.y, 1, 800);
    mainCam->setPosition(player->getPosition() - Vec2(cameraOrthoScale.x * 0.5, cameraOrthoScale.y * 0.5));

    //rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //this->visit();
    //rendtex->end();
    //rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setGLProgram(proPostProcess);
}

void EndRoom::InitShader()
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

void EndRoom::InitAnimationActions()
{
    //AnimateBuilder::GetInstance().LoadSpriteSheet("sprite sheet", "spritesheet_test.png", 6, 3);
    //AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("Special1", "sprite sheet", 6, 12);	//Only half of the sprite sheet

    //AnimateBuilder::GetInstance().LoadAnimateFromWholeSpriteSheet("Special2", "spritesheet_test.png", 6, 3);	//Whole sprite sheet

    //AnimateBuilder::GetInstance().LoadAnimateSpriteBySprite("Front", { "Blue_Front2.png", "Blue_Front1.png", "Blue_Front3.png", "Blue_Front1.png" });
    //AnimateBuilder::GetInstance().LoadAnimateSpriteBySprite("Back", { "Blue_Back2.png", "Blue_Back1.png", "Blue_Back3.png", "Blue_Back1.png" });
    //AnimateBuilder::GetInstance().LoadAnimateSpriteBySprite("Left", { "Blue_Left2.png", "Blue_Left1.png", "Blue_Left3.png", "Blue_Left1.png" });
    //AnimateBuilder::GetInstance().LoadAnimateSpriteBySprite("Right", { "Blue_Right2.png", "Blue_Right1.png", "Blue_Right3.png", "Blue_Right1.png" });

    //animController->AddAnimate("Special1", AnimateBuilder::GetInstance().GetAnimate("Special1"));
    //animController->AddAnimate("Special2", AnimateBuilder::GetInstance().GetAnimate("Special2"));
    //animController->AddAnimate("Front", AnimateBuilder::GetInstance().GetAnimate("Front"));
    //animController->AddAnimate("Back", AnimateBuilder::GetInstance().GetAnimate("Back"));
    //animController->AddAnimate("Left", AnimateBuilder::GetInstance().GetAnimate("Left"));
    //animController->AddAnimate("Right", AnimateBuilder::GetInstance().GetAnimate("Right"));
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
    AnimateBuilder::GetInstance().LoadSpriteSheet("patrol", "spritesheet_patrol.png", 4, 9);
}

void EndRoom::InitTilemap()
{
    auto map = TMXTiledMap::create("Map/EndRoom.tmx");
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
                auto aNode = Node::create();
                Size sz = map->getTileSize();
                Vec2 pos = collideMap->tileAt(Vec2(x, y))->getPosition() + (sz * 0.5f);

                aNode->setPosition(pos);

                sz.width *= 0.85;
                sz.height *= 0.85;

                auto physicsBody = PhysicsBody::createBox(
                    sz,
                    PhysicsMaterial(0.1f, 0, 0.0f)
                    );

                physicsBody->setDynamic(false);
                physicsBody->setTag(PHYSICS_TAG_WALL);
                physicsBody->setCategoryBitmask(WALLS_BITMASK);
                physicsBody->setCollisionBitmask(PLAYER_BITMASK | ENEMY_BITMASK | PLAYER_PROJECTILE_BITMASK);
                physicsBody->setContactTestBitmask(PLAYER_BITMASK | ENEMY_BITMASK | PLAYER_PROJECTILE_BITMASK);
                aNode->addComponent(physicsBody);

                collisionNode->addChild(aNode);
            }
        }
    }

    addChild(collisionNode);

}

void EndRoom::InitFSM()
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
                testFSM->init();
                addChild(testFSM);

                ++count;
            }
            else
            {
                // set player pos
                auto charSprite = this->getChildByName("player");
                charSprite->setPosition(pos);

                spawnPos = pos;
            }
        }
    }
}

void EndRoom::InitEnvironment()
{
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(99);

    auto environmentSpawnGroup = map->getObjectGroup("Environment");
    if (environmentSpawnGroup != nullptr)
    {
        auto environmentSpawns = environmentSpawnGroup->getObjects();

        for (auto &itr : environmentSpawns)
        {
            auto point = itr.asValueMap();
            Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

            if (point["name"].asString() == "Exit")
            {
                Exit* anExit = new Exit();
                anExit->Init(this, pos);
                anExit->m_nextLevel = "dungeon scene";
            }
        }
    }
}

void EndRoom::SetListeners()
{
    // Keyboard Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(EndRoom::OnKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(EndRoom::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Contact Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(EndRoom::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto contactListener_sep = EventListenerPhysicsContact::create();
    contactListener_sep->onContactSeparate = CC_CALLBACK_1(EndRoom::onContactSeperate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener_sep, this);
}

void EndRoom::menuCloseCallback(Ref* pSender)
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

void EndRoom::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
{

}

void EndRoom::OnMouseEvent(Event* _event)
{

}

bool EndRoom::onContactBegin(PhysicsContact& contact)
{
    //Ran collision stuff
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    switch (bodyA->getTag())
    {
        //When player collides with...
    case PHYSICS_TAG_PLAYER:
    {
        switch (bodyB->getTag())
        {
            //...Interactable
        case PHYSICS_TAG_INTERACTABLE:
        {
            Node* bNode = bodyB->getNode();
            static_cast<Interactable*>(bNode->getParent())->OnInteract();

            break;
        }
        }
    }
        break;
    default:
        break;
    }
    return true;
}

void EndRoom::InputMouseTestFunction()
{
    //CCLOG("Mouse Function");
}

void EndRoom::InputKeyboardTestFunction()
{
    //CCLOG("Keyboard Function");
}

void EndRoom::Pause()
{
    SceneManager::GetInstance().AddSceneToStack("pause", true);
}

void EndRoom::SpawnNPC()
{
    //Some quick and dirty menu stuff
    MenuItemFont* winText = MenuItemFont::create("winText");
    winText->setString("YOU WIN GOOD JOB.");
    winText->setFontSize(INT_MAX);
    winText->setFontSizeObj(9);
    winText->setPosition(70, 120);

    MenuItemFont* lastRunScore = MenuItemFont::create("lastRunScore");
    string currScore = "This run's score : " + std::to_string(PlayerInfo::GetInstance().GetScore());
    lastRunScore->setString(currScore);
    lastRunScore->setFontSize(INT_MAX);
    lastRunScore->setFontSizeObj(9);
    lastRunScore->setPosition(70, 100);

    MenuItemFont* highScore = MenuItemFont::create("highScore");
    string highScoreText = "Highscore : " + std::to_string(PlayerInfo::GetInstance().GetHighScore());
    highScore->setString(highScoreText);
    highScore->setFontSize(INT_MAX);
    highScore->setFontSizeObj(9);
    highScore->setPosition(70, 80);

    auto *menu = Menu::create(winText, lastRunScore, highScore, nullptr);
    menu->setPosition(45, 50);
    menu->setName("menu");

    this->addChild(menu, 100);

    //Interactables
    auto newNPC = new Interactable();
    newNPC->Init(this);
    //newNPC->setPosition(40, 80);
    newNPC->setName("npc");
    addChild(newNPC, 98);
}

void EndRoom::onContactSeperate(PhysicsContact & contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    switch (bodyA->getTag())
    {
        //When player seperates with...
    case PHYSICS_TAG_PLAYER:
    {
        switch (bodyB->getTag())
        {
            //...Interactable
        case PHYSICS_TAG_INTERACTABLE:
        {
            Node* bNode = bodyB->getNode();
            static_cast<Interactable*>(bNode->getParent())->OnInteractLeave();
            break;
        }
        }
    }
        break;
    default:
        break;
    }

}