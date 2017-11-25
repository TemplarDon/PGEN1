#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "Input\InputHandler.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

Scene* TestScene::createScene()
{
    return TestScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TestSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TestScene::init()
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

    float groundPosition = playingSize.height * 0.5f;

    for (int i = 0; i < numToRender; ++i)
    {
        auto tempSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        tempSprite->setAnchorPoint(Vec2::ZERO);
        tempSprite->setPosition(groundSpriteWidth * i, groundPosition);

        nodeItems->addChild(tempSprite, 0);
    }

    // Character	
    auto spriteNode = Node::create();
    spriteNode->setName("SpriteNode");

    auto characterSprite = Sprite::create("Blue_Front1.png");
    characterSprite->setName("MainCharacter");
    characterSprite->setAnchorPoint(Vec2::ZERO);
    characterSprite->setPosition(0, groundPosition + groundSpriteHeight);

    spriteNode->addChild(characterSprite, 1);

    // Character Movement
    //auto moveEvent = MoveBy::create(5.0f, Vec2(5.0f, 0));
    //characterSprite->runAction(moveEvent->clone());

    // Delayed Action
    //DelayTime* delay = DelayTime::create(5.0f);
    //Sequence* delaySequence = Sequence::create(delay, delay->clone(), nullptr);
    //Sequence* sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);

    //characterSprite->runAction(sequence);

    // Add to this node tree
    this->addChild(nodeItems, 1);
    this->addChild(spriteNode, 1);

    // Use this function to assign functions to specific key press
    InputHandler::GetInstance().AssignMouseAction(EventMouse::MouseButton::BUTTON_LEFT, bind(&TestScene::InputMouseTestFunction, this), true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&TestScene::InputKeyboardTestFunction, this), true);

    SetListeners();
    InitAnimationActions();
    InitShader();
    this->scheduleUpdate();

    return true;
}

void TestScene::update(float _dt)
{
	auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");

	Camera* mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
	mainCam->setPosition(charSprite->getPosition());

	rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setGLProgram(proPostProcess);

    static int doOnce = 1;
}

void TestScene::InitShader()
{
	Vec2 mLoc(0.5f, 0.5f);
	
	// Specific order according to shaders
	auto shaderCharEffect = new GLProgram();
	shaderCharEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

	shaderCharEffect->link();
	shaderCharEffect->updateUniforms();

	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
	
	auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
	charSprite->setGLProgram(shaderCharEffect);
	charSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);

	proPostProcess = GLProgram::createWithFilenames("Shaders/Basic.vsh", "Shaders/GreyScale.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

	proPostProcess->link();
	proPostProcess->updateUniforms();

	rendtex = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);
}

void TestScene::InitAnimationActions()
{
	Vector<SpriteFrame*> frontFrames;
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
	}
}

void TestScene::SetListeners()
{
	// Keyboard Listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(TestScene::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Mouse Listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(TestScene::OnMouseEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void TestScene::menuCloseCallback(Ref* pSender)
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

void TestScene::OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event)
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
	//			TransitionFlipAngular::create(1.5, TestScene::createScene())
	//		);
	//	}
	//	break;
	//}
}

void TestScene::OnMouseEvent(Event* _event)
{
	EventMouse* mouseEvent = (EventMouse*)_event;

	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		Vec2 mousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

		auto charSprite = this->getChildByName("SpriteNode")->getChildByName("MainCharacter");
		charSprite->stopAllActions();

		auto moveEvent = MoveTo::create(1.0f, mousePos);
		charSprite->runAction(moveEvent);

		float mouseXChange = mousePos.x - charSprite->getPosition().x;
		float mouseYChange = mousePos.y - charSprite->getPosition().y;

		if (fabs(mouseXChange) > fabs(mouseYChange))
		{
			if (mouseXChange > 0)
				charSprite->runAction(RepeatForever::create(v_mainCharAnimation[RIGHT]));
			else
				charSprite->runAction(RepeatForever::create(v_mainCharAnimation[LEFT]));
		}
		else
		{
			if (mouseYChange > 0)
				charSprite->runAction(RepeatForever::create(v_mainCharAnimation[BACK]));
			else
				charSprite->runAction(RepeatForever::create(v_mainCharAnimation[FRONT]));
		}
	}
}

void TestScene::InputMouseTestFunction()
{
    CCLOG("Mouse Function");
}


void TestScene::InputKeyboardTestFunction()
{
    CCLOG("Keyboard Function");
}

