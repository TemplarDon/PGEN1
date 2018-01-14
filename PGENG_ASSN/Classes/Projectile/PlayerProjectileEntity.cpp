#include "PlayerProjectileEntity.h"
#include "BitmasksHeader.h"
#include "FSM\BaseFSM.h"


PlayerProjectileEntity::PlayerProjectileEntity()
{
}

PlayerProjectileEntity::~PlayerProjectileEntity()
{
}

bool PlayerProjectileEntity::init()
{
    this->runAction(
        Sequence::create(
        CCDelayTime::create(lifespan),
        CallFunc::create([&]()
    {
        TimeOut();
    }
        ),
        NULL
        ));

    InitPhysicBody();

    auto collisionListener = EventListenerPhysicsContact::create();
    collisionListener->onContactBegin = CC_CALLBACK_1(PlayerProjectileEntity::OnCollisionEnter, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener, this);

    return true;
}

void PlayerProjectileEntity::update(double dt)
{
}

bool PlayerProjectileEntity::OnCollisionEnter(const PhysicsContact &contact)
{
    //Ran collision stuff
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    if (bodyA->getTag() == PHYSICS_TAG_ENEMY && bodyB->getNode() == this)
    {
        dynamic_cast<BaseFSM*>(bodyA->getNode())->m_isActive = false;
        bodyA->getNode()->removeFromParentAndCleanup(true);

    }
    else if (bodyB->getTag() == PHYSICS_TAG_ENEMY && bodyA->getNode() == this)
    {
        dynamic_cast<BaseFSM*>(bodyB->getNode())->m_isActive = false;
        bodyB->getNode()->removeFromParentAndCleanup(true);
    }

    removeFromParentAndCleanup(true);
    return true;
}

void PlayerProjectileEntity::InitPhysicBody()
{
    auto characterSprite = Sprite::create("Player/Rock.png");
    characterSprite->setName("bullet");
    characterSprite->setAnchorPoint(Vec2::ZERO);
    characterSprite->setPosition(0, 0);
    characterSprite->setScale(0.05f);

    auto physicsBody = PhysicsBody::createCircle((characterSprite->getContentSize() * 0.05f).width,
        PhysicsMaterial(0.1f, 1.0f, 0.0f));

    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);

    this->setPhysicsBody(physicsBody);

    physicsBody->setTag(PHYSICS_TAG_PLAYER_PROJECTILE);
    physicsBody->setCategoryBitmask(PLAYER_PROJECTILE_BITMASK);
    physicsBody->setCollisionBitmask(ENEMY_BITMASK | WALLS_BITMASK);
    physicsBody->setContactTestBitmask(ENEMY_BITMASK | WALLS_BITMASK);

    this->addChild(characterSprite);
}

PlayerProjectileEntity* Create::playerProjectileEntity(
    const Vec2& _position,
    const Vec2& _veloctiy,
    const float& _damage,
    const float& _lifespan
    )
{
    PlayerProjectileEntity* newProjectile = new PlayerProjectileEntity();

    newProjectile->setPosition(_position);
    newProjectile->SetLifespan(_lifespan);
    newProjectile->SetProjectileDamage(_damage);
    newProjectile->init();

    newProjectile->getPhysicsBody()->setVelocity(_veloctiy);
    
    return newProjectile;
}