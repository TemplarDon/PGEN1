#include "BaseFSM.h"

BaseFSM::BaseFSM(TMXTiledMap* map, string sprite) 
: m_map(map)
, m_spriteStr(sprite)
, m_health(3)
, m_moveSpeed(1.1)
, m_isActive(true)
{
    if (Node::init())
        init();
}

BaseFSM::~BaseFSM()
{

}

bool BaseFSM::init()
{
    if (!Node::init())
    {
        return false;
    }

    // Pathfinder
    m_pathFinder = new Pathfinder();
    m_pathFinder->Init(m_map);

    // Can be moved to parent class
    // Sprite
    auto sprite = Sprite::create(m_spriteStr);
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setAnchorPoint(Vec2(0.25, 0.25));

    sprite->setName("sprite");
    sprite->setScale(0.5);

    addChild(sprite);
    m_sprite = sprite;

    // PhysicsBody
    auto physicsBody = PhysicsBody::createBox(
        Size(15.f, 15.f), // assumes that all enemy will be same size as tile
        PhysicsMaterial(5.f, 0, 0.0f)
        );

    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);

    physicsBody->setCategoryBitmask(ENEMY_BITMASK);
    physicsBody->setCollisionBitmask(PLAYER_BITMASK | WALLS_BITMASK | PLAYER_PROJECTILE_BITMASK);
    physicsBody->setContactTestBitmask(PLAYER_BITMASK | WALLS_BITMASK | PLAYER_PROJECTILE_BITMASK);

    //sprite->addComponent(physicsBody);
    this->setPhysicsBody(physicsBody);
}

void BaseFSM::RunFSM()
{
    if (!_parent || !m_isActive)
        return;

    m_pathFinder->UpdateCurrentPosition(getPosition());

    Sense();

    int actValue = Think();
    if (actValue != -1)
    {
        Act(actValue);
    }

}