#include "Player.h"
#include "Input\InputHandler.h"
#include "BitmasksHeader.h"
#include "PlayerInfo.h"
#include "Weapon\PlayerRangeWeapon.h"

Player::Player():
moveSpeed(1),
invulTime(0.0f),
spriteNode(nullptr),
animController(nullptr),
currentMoveDirection(PlayerMoveDir::MOVEDIR_LEFT)
{
}

Player::~Player()
{
}

bool Player::init()
{
    InitActions();
    InitAnimation();
    InitPhysicBody();
    scheduleUpdate();
    setName("Player");
    weapon = new PlayerRangeWeapon(this);
    weapon->SetDamage(1);
    weapon->SetFireRate(1);
    this->addChild(weapon);
    return true;
}

void Player::update(float _dt)
{
}

void Player::InitAnimation()
{
    spriteNode = Node::create();

    // Init base sprite
    Sprite* characterBaseSprite = Sprite::create("Player/PlayerBowTilesheet.png");

    characterBaseSprite->setName("MainCharacter");
    characterBaseSprite->setAnchorPoint(Vec2::ZERO);
    characterBaseSprite->setScale(0.3);

    animController = new AnimationController();
    animController->Init(characterBaseSprite);
    spriteNode->addChild(characterBaseSprite);
    this->addChild(spriteNode, 1);

    AnimateBuilder::GetInstance().LoadSpriteSheet("player_bow", "Player/PlayerBowTilesheet.png", 21, 13);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_walk_up", "player_bow", 105, 112);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_walk_left", "player_bow", 117, 124);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_walk_down", "player_bow", 130, 137);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_walk_right", "player_bow", 143, 150);

    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_attack_up", "player_bow", 208, 220);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_attack_left", "player_bow", 221, 233);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_attack_down", "player_bow", 234, 247);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_bow_attack_right", "player_bow", 248, 261);

    AnimateBuilder::GetInstance().LoadSpriteSheet("player_spear", "Player/PlayerSpearTilesheet.png", 21, 13);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_walk_up", "player_spear", 103, 111);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_walk_left", "player_spear", 116, 124);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_walk_down", "player_spear", 129, 137);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_walk_right", "player_spear", 142, 150);

    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_attack_up", "player_spear", 208, 220);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_attack_left", "player_spear", 221, 233);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_attack_down", "player_spear", 234, 247);
    AnimateBuilder::GetInstance().LoadAnimateFromLoadedSpriteSheet("player_spear_attack_right", "player_spear", 248, 261);

    animController->AddAnimate("player_bow_walk_up", AnimateBuilder::GetInstance().GetAnimate("player_bow_walk_up"));
    animController->AddAnimate("player_bow_walk_down", AnimateBuilder::GetInstance().GetAnimate("player_bow_walk_down"));
    animController->AddAnimate("player_bow_walk_left", AnimateBuilder::GetInstance().GetAnimate("player_bow_walk_left"));
    animController->AddAnimate("player_bow_walk_right", AnimateBuilder::GetInstance().GetAnimate("player_bow_walk_right"));
    animController->AddAnimate("player_bow_attack_up", AnimateBuilder::GetInstance().GetAnimate("player_bow_attack_up"));
    animController->AddAnimate("player_bow_attack_down", AnimateBuilder::GetInstance().GetAnimate("player_bow_attack_down"));
    animController->AddAnimate("player_bow_attack_left", AnimateBuilder::GetInstance().GetAnimate("player_bow_attack_left"));
    animController->AddAnimate("player_bow_attack_right", AnimateBuilder::GetInstance().GetAnimate("player_bow_attack_right"));

    animController->AddAnimate("player_spear_walk_up", AnimateBuilder::GetInstance().GetAnimate("player_spear_walk_up"));
    animController->AddAnimate("player_spear_walk_down", AnimateBuilder::GetInstance().GetAnimate("player_spear_walk_down"));
    animController->AddAnimate("player_spear_walk_left", AnimateBuilder::GetInstance().GetAnimate("player_spear_walk_left"));
    animController->AddAnimate("player_spear_walk_right", AnimateBuilder::GetInstance().GetAnimate("player_spear_walk_right"));
    animController->AddAnimate("player_spear_attack_up", AnimateBuilder::GetInstance().GetAnimate("player_spear_attack_up"));
    animController->AddAnimate("player_spear_attack_down", AnimateBuilder::GetInstance().GetAnimate("player_spear_attack_down"));
    animController->AddAnimate("player_spear_attack_left", AnimateBuilder::GetInstance().GetAnimate("player_spear_attack_left"));
    animController->AddAnimate("player_spear_attack_right", AnimateBuilder::GetInstance().GetAnimate("player_spear_attack_right"));
}

void Player::InitActions()
{
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&Player::StopPlayerMovementUp, this), false, false, true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&Player::StopPlayerMovementDown, this), false, false, true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&Player::StopPlayerMovementLeft, this), false, false, true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&Player::StopPlayerMovementRight, this), false, false, true);

    //Add Moveplayer when button is press and held
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_UP_ARROW, bind(&Player::MovePlayerUp, this), true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_DOWN_ARROW, bind(&Player::MovePlayerDown, this), true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_LEFT_ARROW, bind(&Player::MovePlayerLeft, this), true);
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, bind(&Player::MovePlayerRight, this), true);

    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&Player::Attack, this), true);
}

void Player::InitPhysicBody()
{
    auto physicsBody = PhysicsBody::createBox(Size(8.f, 8.f),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));

    physicsBody->setGravityEnable(false);
    physicsBody->setTag(PLAYER_BITMASK);
    physicsBody->setRotationEnable(false);

    physicsBody->setCategoryBitmask(PLAYER_BITMASK);
    physicsBody->setCollisionBitmask(ENEMY_BITMASK | WALLS_BITMASK);
    physicsBody->setContactTestBitmask(ENEMY_BITMASK | WALLS_BITMASK);

    this->setPhysicsBody(physicsBody);

    
}

void Player::TakeDamage(int _amount)
{
    if (invulTime <= 0.0f)
	{
        invulTime = 1.0f;
        cocos2d::Blink* blinkAction = CCBlink::create(1.0f, 10);
        this->runAction(blinkAction);
        //PlayerInfo::GetInstance().TakeDamage(_amount);
	}
}

void Player::StopPlayerMovementUp()
{
    if (currentMoveDirection == PlayerMoveDir::MOVEDIR_UP)
        StopAnimation();
}

void Player::StopPlayerMovementDown()
{
    if (currentMoveDirection == PlayerMoveDir::MOVEDIR_DOWN)
        StopAnimation();
}

void Player::StopPlayerMovementLeft()
{
    if (currentMoveDirection == PlayerMoveDir::MOVEDIR_LEFT)
        StopAnimation();
}

void Player::StopPlayerMovementRight()
{
    if (currentMoveDirection == PlayerMoveDir::MOVEDIR_RIGHT)
        StopAnimation();
}

void Player::MovePlayerUp()
{
    animController->PlayAnimation("player_bow_walk_up");
    currentMoveDirection = PlayerMoveDir::MOVEDIR_UP;
    MovePlayer();
}

void Player::MovePlayerDown()
{
    animController->PlayAnimation("player_bow_walk_down");
    currentMoveDirection = PlayerMoveDir::MOVEDIR_DOWN;
    MovePlayer();
}

void Player::MovePlayerLeft()
{
    animController->PlayAnimation("player_bow_walk_left");
    currentMoveDirection = PlayerMoveDir::MOVEDIR_LEFT;
    MovePlayer();
}

void Player::MovePlayerRight()
{
    animController->PlayAnimation("player_bow_walk_right");
    currentMoveDirection = PlayerMoveDir::MOVEDIR_RIGHT;
    MovePlayer();
}

void Player::MoveIdle()
{
}

void Player::MovePlayer()
{
    switch (currentMoveDirection)
    {
        case MOVEDIR_LEFT:
        {
            getPhysicsBody()->setVelocity(Vec2(-80.f, 0.0f));
            break;
        }
        case MOVEDIR_RIGHT:
        {
            getPhysicsBody()->setVelocity(Vec2(80.f, 0.0f));
        }
            break;
        case MOVEDIR_UP:
        {
            getPhysicsBody()->setVelocity(Vec2(0.0f, 80.f));
            break;
        }
        case MOVEDIR_DOWN:
        {
            getPhysicsBody()->setVelocity(Vec2(0.0f, -80.f));
            break;
        }
        case MOVEDIR_IDLE:
        {
            MoveIdle();
            break;
        }
        default:
        break;
    }
}

void Player::StopAnimation()
{
    animController->StopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    getPhysicsBody()->setVelocity(Vec2(0.0f, 0.0f));
}

void Player::Attack()
{
    switch (currentMoveDirection)
    {
    case MOVEDIR_LEFT:
        weapon->Discharge(Vec2(-1.0f, 0.0f));
        break;
    case MOVEDIR_RIGHT:
        weapon->Discharge(Vec2(1.0f, 0.0f));
        break;
    case MOVEDIR_UP:
        weapon->Discharge(Vec2(0.0f, 1.0f));
        break;
    case MOVEDIR_DOWN:
        weapon->Discharge(Vec2(0.0f, -1.0f));
        break;
    default:
        break;
    }
}