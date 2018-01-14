#include "PlayerMeleeHitboxEntity.h"
#include "BitmasksHeader.h"
#include "FSM\BaseFSM.h"


PlayerMeleeHitboxEntity::PlayerMeleeHitboxEntity()
{
}

PlayerMeleeHitboxEntity::~PlayerMeleeHitboxEntity()
{
}

bool PlayerMeleeHitboxEntity::init()
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
    collisionListener->onContactBegin = CC_CALLBACK_1(PlayerMeleeHitboxEntity::OnCollisionEnter, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener, this);

    return true;
}

void PlayerMeleeHitboxEntity::update(double dt)
{
}

bool PlayerMeleeHitboxEntity::OnCollisionEnter(const PhysicsContact &contact)
{
    //Ran collision stuff
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    if (bodyA->getTag() == PHYSICS_TAG_ENEMY && bodyB->getNode() == this)
    {
        dynamic_cast<BaseFSM*>(bodyA->getNode())->m_isActive = false;
        bodyA->getNode()->removeFromParentAndCleanup(true);

        // dispatch enemy dead event
        EventCustom event("enemy_death");
        event.setUserData(new Vec2(bodyA->getPosition()));
        _eventDispatcher->dispatchEvent(&event);

    }
    else if (bodyB->getTag() == PHYSICS_TAG_ENEMY && bodyA->getNode() == this)
    {
        dynamic_cast<BaseFSM*>(bodyB->getNode())->m_isActive = false;
        bodyB->getNode()->removeFromParentAndCleanup(true);

        // dispatch enemy dead event
        EventCustom event("enemy_death");
        event.setUserData(new Vec2(bodyB->getPosition()));
        _eventDispatcher->dispatchEvent(&event);
    }

    removeFromParentAndCleanup(true);
    return true;
}

void PlayerMeleeHitboxEntity::InitPhysicBody()
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

    physicsBody->setTag(PHYSICS_TAG_PLAYER_MELEE_HITBOX);
    physicsBody->setCategoryBitmask(PHYSICS_TAG_PLAYER_MELEE_HITBOX);
    physicsBody->setCollisionBitmask(ENEMY_BITMASK | WALLS_BITMASK);
    physicsBody->setContactTestBitmask(ENEMY_BITMASK | WALLS_BITMASK);

    this->addChild(characterSprite);
}

PlayerMeleeHitboxEntity* Create::playerMeleeHitboxEntity(
    const Vec2& _position,
    const Vec2& _veloctiy,
    const float& _damage,
    const float& _lifespan
    )
{
    PlayerMeleeHitboxEntity* newMeleeHitbox = new PlayerMeleeHitboxEntity();

    newMeleeHitbox->setPosition(_position);
    newMeleeHitbox->SetLifespan(_lifespan);
    newMeleeHitbox->SetProjectileDamage(_damage);
    newMeleeHitbox->init();

    newMeleeHitbox->getPhysicsBody()->setVelocity(_veloctiy);
    
    return newMeleeHitbox;
}