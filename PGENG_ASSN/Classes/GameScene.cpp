#include "GameScene.h"
#include "Player/PlayerInfo.h"
#include "Input/InputHandler.h"
#include "SceneManagement/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "Animation/SpriteBuilder.h"
#include "Interactables/HeartDrops.h"

#include "FSM/PatrollingFSM.h"
#include "Puzzle/Puzzle.h"
#include "Puzzle/Button.h"
#include "Puzzle/ChainedPressurePlate.h"
#include "Interactables/Exit.h"

// Facebook
#include "proj.ios_mac/PluginFacebook.framework/Versions/A/Headers/PluginFacebook.h"
#define SDKBOX_ENABLED

#define COCOS2D_DEBUG 1
#define FSM_TAG 5

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("PhysicsBase");

    auto layer = GameScene::create();

    layer->setName("Scene");
    layer->retain();

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PathfinderGameScene.cpp/n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    // Reset all binded actions 
    InputHandler::GetInstance()->ClearActionMaps();

    cameraOrthoScale.set(234, 160);
	//cameraOrthoScale.set(1024, 800);
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
    InputHandler::GetInstance()->AssignMouseAction(EventMouse::MouseButton::BUTTON_LEFT, bind(&GameScene::InputMouseTestFunction, this), true);
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&GameScene::InputKeyboardTestFunction, this), true);

    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_TAB, bind(&GameScene::Pause, this), true);

	//InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_L, bind(&GameScene::SpawnNPC, this), true);

    //Init Player
    player = new Player();
    player->init();
    player->setName("player");
	player->getPhysicsBody()->setTag(PHYSICS_TAG_PLAYER);
	addChild(player, 99);
 
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	//Spawn some hearts
	SpawnHeart(Vec2(100, 100));
	SpawnHeart(Vec2(250, 120));
	SpawnHeart(Vec2(240, 350));
	SpawnHeart(Vec2(290, 320));
	SpawnHeart(Vec2(260, 360));

	PlayerInfo::GetInstance()->OnLevelStart();
    PlayerInfo::GetInstance()->SetScore(10000);

    SetListeners();
    InitAnimationActions();
    InitShader();
    InitTilemap();
    InitFSM();
    InitEnvironment();
    InitPuzzle();
    InitUI();
    scheduleUpdate();

	m_over = false;

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio/BGM.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);

    // Particles
    auto particleSystem = ParticleSystemQuad::create("particle_enemydeath.plist");
    particleSystem->setName("particle_enemydeath");
    particleSystem->setScale(0.15);
    addChild(particleSystem, 99);

    return true;
}

void GameScene::update(float _dt)
{
    auto charSprite = this->getChildByName("player");

    // NOT THE BEST WAY PROBABLY, BETTER TO HAVE ENTITY CLASS WITH UPDATE
    Vector<Node*> myVector = getChildren();
    Vector<Node*>::iterator myIterator;

	bool enemyalive = false;
    for (myIterator = myVector.begin(); myIterator != myVector.end(); ++myIterator)
    {
        auto mySprite = *myIterator;

        if (mySprite->getTag() == FSM_TAG)
        {
            dynamic_cast<BaseFSM*>(mySprite)->RunFSM();
			enemyalive = true;
        }
    }

	if (!enemyalive)
	{
		SpawnNPC();
	}

    //UpdateFSM();
    Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
	mainCam->initOrthographic(cameraOrthoScale.x, cameraOrthoScale.y, 1, 800);
	auto lerpedPosition = ccpLerp(mainCam->getPosition(), player->getPosition() - Vec2(cameraOrthoScale.x * 0.5, cameraOrthoScale.y * 0.5), 0.1);
    mainCam->setPosition(lerpedPosition);
	mainCam->setViewport(cocos2d::experimental::Viewport(cameraOrthoScale.x * 0.2f, cameraOrthoScale.y * 0.2f, cameraOrthoScale.x * 0.2f, cameraOrthoScale.y * 0.2f));
	//gameUINode->ignoreAnchorPointForPosition(false);
    gameUINode->setPosition(mainCam->getPosition() + Vec2(cameraOrthoScale.x * 0.5, cameraOrthoScale.y * 0.5));
	
    UpdateUI(_dt);

    PlayerInfo::GetInstance()->AddScore(-_dt * 100);
    //rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //this->visit();
    //rendtex->end();
    //rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setGLProgram(proPostProcess);
}

void GameScene::InitShader()
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

void GameScene::InitAnimationActions()
{
    //AnimateBuilder::GetInstance()->LoadSpriteSheet("sprite sheet", "spritesheet_test.png", 6, 3);
    //AnimateBuilder::GetInstance()->LoadAnimateFromLoadedSpriteSheet("Special1", "sprite sheet", 6, 12);	//Only half of the sprite sheet

    //AnimateBuilder::GetInstance()->LoadAnimateFromWholeSpriteSheet("Special2", "spritesheet_test.png", 6, 3);	//Whole sprite sheet

    //AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Front", { "Blue_Front2.png", "Blue_Front1.png", "Blue_Front3.png", "Blue_Front1.png" });
    //AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Back", { "Blue_Back2.png", "Blue_Back1.png", "Blue_Back3.png", "Blue_Back1.png" });
    //AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Left", { "Blue_Left2.png", "Blue_Left1.png", "Blue_Left3.png", "Blue_Left1.png" });
    //AnimateBuilder::GetInstance()->LoadAnimateSpriteBySprite("Right", { "Blue_Right2.png", "Blue_Right1.png", "Blue_Right3.png", "Blue_Right1.png" });

    //animController->AddAnimate("Special1", AnimateBuilder::GetInstance()->GetAnimate("Special1"));
    //animController->AddAnimate("Special2", AnimateBuilder::GetInstance()->GetAnimate("Special2"));
    //animController->AddAnimate("Front", AnimateBuilder::GetInstance()->GetAnimate("Front"));
    //animController->AddAnimate("Back", AnimateBuilder::GetInstance()->GetAnimate("Back"));
    //animController->AddAnimate("Left", AnimateBuilder::GetInstance()->GetAnimate("Left"));
    //animController->AddAnimate("Right", AnimateBuilder::GetInstance()->GetAnimate("Right"));
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

void GameScene::InitTilemap()
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

void GameScene::InitFSM()
{
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(99);

    auto enemySpawnGroup = map->getObjectGroup("Spawns");

    if (enemySpawnGroup != nullptr)
    {
        auto enemySpawns = enemySpawnGroup->getObjects();

        int count = 0;

		


        for (ValueVector::iterator itr = enemySpawns.begin(); itr != enemySpawns.end(); ++itr)
        {
            auto point = itr->asValueMap();
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

void GameScene::InitEnvironment()
{
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(99);

    auto environmentSpawnGroup = map->getObjectGroup("Environment");
    if (environmentSpawnGroup != nullptr)
    {
        auto environmentSpawns = environmentSpawnGroup->getObjects();
		for (ValueVector::iterator itr = environmentSpawns.begin(); itr != environmentSpawns.end(); ++itr)
		{
            auto point = itr->asValueMap();
            Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

            if (point["name"].asString() == "Exit")
            {
                Exit* anExit = new Exit();
                anExit->Init(this, pos);
                anExit->m_nextLevel = "end room";
            }
        }
    }
}

void GameScene::InitPuzzle()
{
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(99);

    std::vector<PuzzleElement*> tempPuzzleElements;
    std::map<int, Puzzle*> tempPuzzle;

    auto puzzleSpawnGroup = map->getObjectGroup("Puzzle");
    if (puzzleSpawnGroup != nullptr)
    {
        auto puzzleSpawns = puzzleSpawnGroup->getObjects();

		for (ValueVector::iterator itr = puzzleSpawns.begin(); itr != puzzleSpawns.end(); ++itr)
		{
            auto point = itr->asValueMap();
            Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

            if (point["name"].asString() == "Door")
            {
                Puzzle* aPuzzle = new Puzzle();
                aPuzzle->init();
                aPuzzle->setPosition(pos);

                tempPuzzle.insert(std::pair<int, Puzzle*>(point["PuzzleID"].asInt(), aPuzzle));
            }
            else
            {
                string temp = point["name"].asString();
               
                if (temp == "Button")
                {
                    Button* aButton = new Button();
                    aButton->Init(this, pos);
                    aButton->m_puzzleID = point["PuzzleID"].asInt();

                    tempPuzzleElements.push_back(aButton);
                }
                else if (temp == "PressurePlate")
                {

                }
                else if (temp == "ChainedPressurePlate")
                {
                    ChainedPressurePlate* aPlate = new ChainedPressurePlate();
                    aPlate->Init(this, pos);
                    aPlate->m_puzzleID = point["PuzzleID"].asInt();
                    aPlate->m_chainNum = point["ChainNum"].asInt();

                    tempPuzzleElements.push_back(aPlate);
                }
            }
        }

        // Link puzzles and puzzle elements
		for (std::map<int, Puzzle*>::iterator itr = tempPuzzle.begin(); itr != tempPuzzle.end(); ++itr)
		{
            for (int i = 0; i < tempPuzzleElements.size(); ++i)
            {
                // Check index
                if (tempPuzzleElements[i]->m_puzzleID == itr->first)
                {
                    itr->second->m_elementList.push_back(tempPuzzleElements[i]);
                }
            }
            addChild(itr->second);
        }

        // Link any puzzle elements that need linking
        for (int i = 0; i < tempPuzzleElements.size(); ++i)
        {
            if (tempPuzzleElements[i]->getName() == "ChainedPressurePlate")
            {
                for (int j = 0; j < tempPuzzleElements.size(); ++j)
                {
                    if (tempPuzzleElements[j]->getName() == "ChainedPressurePlate" && i != j && tempPuzzleElements[i]->m_puzzleID == tempPuzzleElements[j]->m_puzzleID)
                    {
                        if (dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[i])->m_chainNum ==
                            dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[j])->m_chainNum - 1)
                        {
                            dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[j])->m_prevPlate = dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[i]);

                            break;
                        }
                        else if (dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[j])->m_chainNum ==
                                 dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[i])->m_chainNum - 1)
                        {
                            dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[i])->m_prevPlate = dynamic_cast<ChainedPressurePlate*>(tempPuzzleElements[j]);

                            break;
                        }
                    }
                }
            }
        }
    }
}

void GameScene::InitUI()
{
	gameUINode = Node::create();
	
    UILayout = ui::Layout::create();
    UILayout->setLayoutType(cocos2d::ui::Layout::Type::HORIZONTAL);
    UILayout->setPosition(Vec2(-cameraOrthoScale.x * 0.35f, cameraOrthoScale.y * -0.375f));
	gameUINode->addChild(UILayout, INT_MAX);

    ui::ImageView* heartImage = ui::ImageView::create("hearticon.png");
    heartImage->setName("heart");
    heartImage->setScale(0.1f);
    UILayout->addChild(heartImage, INT_MAX);

    heartImage = ui::ImageView::create("hearticon.png");
    heartImage->setName("heart");
    heartImage->setScale(0.1f);
    UILayout->addChild(heartImage, INT_MAX);

    heartImage = ui::ImageView::create("hearticon.png");
    heartImage->setName("heart");
    heartImage->setScale(0.1f);
    UILayout->addChild(heartImage, INT_MAX);

    heartImage = ui::ImageView::create("hearticon.png");
    heartImage->setName("heart");
    heartImage->setScale(0.1f);
    UILayout->addChild(heartImage, INT_MAX);

	auto ControlsLayout = ui::Layout::create();
	ControlsLayout->setLayoutType(cocos2d::ui::Layout::Type::ABSOLUTE);
	ControlsLayout->setPosition(Vec2(cameraOrthoScale.x * 0.3f, -cameraOrthoScale.y * 0.25f));
	gameUINode->addChild(ControlsLayout, INT_MAX);

	addChild(gameUINode, INT_MAX);

	auto moveButton = ui::Button::create("button_up_normal.png", "button_up_pressed.png");
	moveButton->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN)
        {
            player->MovePlayerUp();
        }
        
        if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
		{
            player->StopPlayerMovementUp();
		}
	});

	moveButton->setName("button_up");
	moveButton->setPosition(Vec2(0, 10.f));
	moveButton->setScale(0.05f);
	ControlsLayout->addChild(moveButton, INT_MAX);

	moveButton = ui::Button::create("button_down_normal.png", "button_down_pressed.png");
    moveButton->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN)
        {
            player->MovePlayerDown();
        }

        if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
        {
            player->StopPlayerMovementDown();
        }
    });

	moveButton->setName("button_down");
	moveButton->setPosition(Vec2(0, -10.f));
	moveButton->setScale(0.05f);
	ControlsLayout->addChild(moveButton, INT_MAX);

	moveButton = ui::Button::create("button_left_normal.png", "button_left_pressed.png");
    moveButton->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN)
        {
            player->MovePlayerLeft();
        }

        if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
        {
            player->StopPlayerMovementLeft();
        }
    });

	moveButton->setName("button_left");
	moveButton->setPosition(Vec2(-10.f, 0));
	moveButton->setScale(0.05f);
	ControlsLayout->addChild(moveButton, INT_MAX);

	moveButton = ui::Button::create("button_right_normal.png", "button_right_pressed.png");
    moveButton->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN)
        {
            player->MovePlayerRight();
        }

        if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
        {
            player->StopPlayerMovementRight();
        }
    });

	moveButton->setName("button_right");
	moveButton->setPosition(Vec2(10.f, 0));
	moveButton->setScale(0.05f);
	ControlsLayout->addChild(moveButton, INT_MAX);

    moveButton = ui::Button::create("button_attack_normal.png", "button_attack_pressed.png");
    moveButton->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN)
        {
            player->Attack();
        }
    });

    moveButton->setName("button_attack");
    moveButton->setPosition(Vec2(-cameraOrthoScale.x * 0.6f, 0));
    moveButton->setScale(0.1f);
    ControlsLayout->addChild(moveButton, INT_MAX);


    string currScore = "Score : " +  std::to_string(PlayerInfo::GetInstance()->GetScore());
 
    MenuItemFont* score = MenuItemFont::create("score");
    score->setName("score");
    score->setString(currScore);
    score->setFontSize(100);
    score->setFontSizeObj(9);
    score->setPosition(Vec2(cameraOrthoScale.x * 0.2f, cameraOrthoScale.y * 0.4f));

    player->addChild(score, INT_MAX);
}

void GameScene::UpdateUI(float _dt)
{
    if (PlayerInfo::GetInstance()->GetCurrHealth() > UILayout->getChildrenCount())
    {
        while (PlayerInfo::GetInstance()->GetCurrHealth() > UILayout->getChildrenCount())
        {
            ui::ImageView* heartImage = ui::ImageView::create("hearticon.png");
            heartImage->setName("heart");
            heartImage->setScale(0.1f);
            UILayout->addChild(heartImage, INT_MAX);
        }
    }
    else if (PlayerInfo::GetInstance()->GetCurrHealth() < UILayout->getChildrenCount())
    {
        while (PlayerInfo::GetInstance()->GetCurrHealth() < UILayout->getChildrenCount())
        {
            if (!UILayout->getChildren().empty())
                UILayout->removeChild(UILayout->getChildByName("heart"), true);
        }
    }

    Node* score = player->getChildByName("score");
	String currScore = "Score : " + std::to_string(PlayerInfo::GetInstance()->GetScore());
    dynamic_cast<MenuItemFont*>(score)->setString(currScore.getCString());
}

void GameScene::SetListeners()
{
    // Keyboard Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::OnKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::OnMouseEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Contact Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto contactListener_sep = EventListenerPhysicsContact::create();
	contactListener_sep->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener_sep, this);

    // Adds enemydeath listener
    auto enemyDeathListener = EventListenerCustom::create("enemy_death", [=](EventCustom* event)
    {
        CCLOG("enemy death received");
        Vec2* pos = static_cast<Vec2*>(event->getUserData());
        SpawnHeart(*pos);
        PlayerInfo::GetInstance()->AddScore(1000);

		//player->setPosition(*pos);

        getChildByName("particle_enemydeath")->setPosition(*pos);
        (static_cast<ParticleSystemQuad*>(getChildByName("particle_enemydeath")))->start();
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(enemyDeathListener, this);
}

void GameScene::menuCloseCallback(Ref* pSender)
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

void GameScene::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
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
    //			TransitionFlipAngular::create(1.5, GameScene::createScene())
    //		);
    //	}
    //	break;
    //}
}

void GameScene::OnMouseEvent(Event* _event)
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

bool GameScene::onContactBegin(PhysicsContact& contact)
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

			//(static_cast<Interactable*>(bodyB->getNode()))->OnInteract();
			if(m_over)
				menu_play->setVisible(true);

			break;
		}
		}
        break;
	}
    case PHYSICS_TAG_INTERACTABLE:
    {
        switch (bodyB->getTag())
        {
            //...Interactable
        case PHYSICS_TAG_PLAYER:
        {
            Node* aNode = bodyA->getNode();
            static_cast<Interactable*>(aNode->getParent())->OnInteract();

            //(static_cast<Interactable*>(bodyB->getNode()))->OnInteract();
            if (m_over)
                menu_play->setVisible(true);

            break;
        }
        }
        break;
    }
	default:
		break;
	}
    return true;
}

void GameScene::InputMouseTestFunction()
{
    //CCLOG("Mouse Function");
}

void GameScene::InputKeyboardTestFunction()
{
    //CCLOG("Keyboard Function");
}

void GameScene::Pause()
{
    SceneManager::GetInstance()->AddSceneToStack("pause", true);
}

void GameScene::onContactSeperate(PhysicsContact & contact)
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

			//(static_cast<Interactable*>(bodyB->getNode()))->OnInteractLeave();
			if (m_over)
				menu_play->setVisible(false);
			break;
		}
		}
	}
	break;
	default:
		break;
	}

}

void GameScene::SpawnNPC()
{
	if (m_over)
		return;

	//Some quick and dirty menu stuff
	menu_play = MenuItemFont::create("thingy");
	menu_play->setString("YOU WIN GOOD JOB.");
	menu_play->setFontSize(10000);
	menu_play->setFontSizeObj(12);

	auto *menu = Menu::create(menu_play, nullptr);
	menu->setPosition(15, 720);
	menu->setName("menu");
	menu_play->setPosition(40, -20);
	menu_play->setVisible(false);

	this->addChild(menu, 100);

	//Interactables
	auto asdasd = new Interactable();
	asdasd->Init(this);
	asdasd->setName("npc");
	addChild(asdasd, 98);

	m_over = true;
}

void GameScene::SpawnHeart(Vec2 pos)
{
    //Test heart object
	auto hrt = new HeartDrop();
	hrt->Init(this, pos);
	hrt->setPosition(pos);
	hrt->sprite->setPosition(pos);
	this->addChild(hrt, 98);

}
