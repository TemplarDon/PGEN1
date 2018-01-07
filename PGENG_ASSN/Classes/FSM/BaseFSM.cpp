#include "BaseFSM.h"

BaseFSM::BaseFSM(TMXTiledMap* map, string sprite) 
: m_map(map)
, m_spriteStr(sprite)
, m_health(3)
, m_moveSpeed(1000)
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

    addChild(sprite);
    getChildByName("sprite")->setScale(0.2);
    getChildByName("sprite")->setAnchorPoint(Vec2::ZERO);

    // PhysicsBody
    auto physicsBody = PhysicsBody::createBox(
        sprite->getContentSize(),
        PhysicsMaterial(5.f, 1.0f, 0.0f)
        );

    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(ENEMY_BITMASK);
    physicsBody->setCollisionBitmask(PLAYER_BITMASK | NEUTRAL_BITMASK);
    physicsBody->setContactTestBitmask(PLAYER_BITMASK | NEUTRAL_BITMASK);

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