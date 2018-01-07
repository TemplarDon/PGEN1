#include "PatrollingFSM.h"

PatrollingFSM::PatrollingFSM(TMXTiledMap* map, string sprite) 
: BaseFSM(map, sprite)
, m_currentState(PATROLLING_STATES::IDLE)
, m_idx(1)
{
    m_waypoints = std::map<int, Vec2>();

    auto pathfinderPointsGroup = m_map->getObjectGroup("PathfinderPoints");
    auto pathfinderPoints = pathfinderPointsGroup->getObjects();

    for (auto &itr : pathfinderPoints)
    {
        auto point = itr.asValueMap();

        int pointIdx = point["Point"].asInt();
        Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

        pair<int, Vec2> aPair = pair<int, Vec2>(pointIdx, pos);

        m_waypoints.insert(aPair);
    }

    setPosition(m_waypoints[0]);

    /*
    for (auto&coinD : coinData)
    {
        auto prop = coinD.asValueMap();
        int xC = prop["x"].asInt();
        int yC = prop["y"].asInt();

        coin = Sprite::create("Coin.png");
        coin->setPosition(Vec2(xC, yC));
        this->addChild(coin, 1);
    }
    */
}

PatrollingFSM::~PatrollingFSM()
{
    
}

void PatrollingFSM::Sense()
{

}

int PatrollingFSM::Think()
{
    switch (m_currentState)
    {
    case PATROLLING_STATES::IDLE:
        return (int)PATROLLING_STATES::PATROLLING;

    case PATROLLING_STATES::PATROLLING:
    {
        if (m_pathFinder->m_pathFound)
        {
            ++m_idx;
            if (m_idx >= m_waypoints.size())
            {
                m_idx = 0;
            }
        }

        break;
    }
    case PATROLLING_STATES::DEAD:
        break;
    }

    return (int)m_currentState;
}

void PatrollingFSM::Act(int value)
{
    m_currentState = (PATROLLING_STATES)value;

    switch (m_currentState)
    {
    case PATROLLING_STATES::IDLE:
        break;

    case PATROLLING_STATES::PATROLLING:
    {
        Vec2 moveby = Vec2();

        if (!m_pathFinder->m_pathFound)
            m_pathFinder->FindPath(m_waypoints[m_idx]);
        else
            moveby = m_pathFinder->FollowPath();

        auto moveEvent = MoveBy::create(0, moveby);
        this->runAction(moveEvent);
        
        //PhysicsBody* curPhysics = getChildByName("sprite")->getPhysicsBody();
        //curPhysics->applyForce(moveby * m_moveForce);

        break;
    }
    case PATROLLING_STATES::DEAD:
        break;
    }
}