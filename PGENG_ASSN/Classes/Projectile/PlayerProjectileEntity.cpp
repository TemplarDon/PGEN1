#include "PlayerProjectileEntity.h"
#include "BitmasksHeader.h"


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

    return true;
}

void PlayerProjectileEntity::update(double dt)
{
}

void PlayerProjectileEntity::CollisionResponse(Node* _other)
{
	
}

void PlayerProjectileEntity::InitPhysicBody()
{
    auto characterSprite = Sprite::create("Blue_Front1.png");
    characterSprite->setName("bullet");
    characterSprite->setAnchorPoint(Vec2::ZERO);
    characterSprite->setPosition(0, 0);
    characterSprite->setScale(0.4);

    auto physicsBody = PhysicsBody::createBox(characterSprite->getContentSize(),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));

    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);

    this->setPhysicsBody(physicsBody);

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