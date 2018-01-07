#include "BaseFSM.h"

BaseFSM::BaseFSM(TMXTiledMap* map, string sprite) 
: m_map(map)
, m_spriteStr(sprite)
, m_health(3)
, m_moveSpeed(1.1)
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
    sprite->setName("sprite");
    sprite->setScale(0.5);
    //sprite->setAnchorPoint(Vec2(0.5, 0.5));

    addChild(sprite);
    m_sprite = sprite;

    // PhysicsBody
    auto physicsBody = PhysicsBody::createBox(
        m_map->getTileSize(), // assumes that all enemy will be same size as tile
        PhysicsMaterial(5.f, 0, 0.0f)
        );

    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);

    physicsBody->setCategoryBitmask(ENEMY_BITMASK);
    physicsBody->setCollisionBitmask(PLAYER_BITMASK | WALLS_BITMASK | PLAYER_PROJECTILE_BITMASK);
    physicsBody->setContactTestBitmask(PLAYER_BITMASK | WALLS_BITMASK | PLAYER_PROJECTILE_BITMASK);

    sprite->addComponent(physicsBody);
}

void BaseFSM::RunFSM()
{
    m_pathFinder->UpdateCurrentPosition(getPosition());

    Sense();

    int actValue = Think();
    if (actValue != -1)
    {
        Act(actValue);
    }

}