#include "PatrollingFSM.h"

PatrollingFSM::PatrollingFSM(TMXTiledMap* map, string sprite) 
: BaseFSM(map, sprite)
, m_currentState(PATROLLING_STATES::IDLE)
, m_patrolTarget(Vec2(-1, -1))
{
    //m_waypoints = std::map<int, Vec2>();

    //auto pathfinderPointsGroup = m_map->getObjectGroup("PathfinderPoints");

    //if (pathfinderPointsGroup != nullptr)
    //{
    //    auto pathfinderPoints = pathfinderPointsGroup->getObjects();

    //    for (auto &itr : pathfinderPoints)
    //    {
    //        auto point = itr.asValueMap();

    //        int pointIdx = point["Point"].asInt();
    //        Vec2 pos = Vec2(point["x"].asInt(), point["y"].asInt());

    //        pair<int, Vec2> aPair = pair<int, Vec2>(pointIdx, pos);

    //        m_waypoints.insert(aPair);
    //    }

    //    setPosition(m_waypoints[0]);
    //}
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
        if (m_patrolTarget != Vec2(-1, -1))
            return (int)PATROLLING_STATES::PATROLLING;

    case PATROLLING_STATES::PATROLLING:
    {
        if (m_pathFinder->m_pathComplete)
        {
            //++m_idx;
            //if (m_idx >= m_waypoints.size())
            //{
            //    m_idx = 0;
            //}
            return (int)PATROLLING_STATES::IDLE;
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
        m_patrolTarget = m_pathFinder->RandomPosition(8);
        break;

    case PATROLLING_STATES::PATROLLING:
    {
        Vec2 moveby = Vec2();

        if (!m_pathFinder->m_pathFound)
            m_pathFinder->FindPath(m_patrolTarget);
        else
            moveby = m_pathFinder->FollowPath();

        auto moveEvent = MoveBy::create(0, moveby * m_moveSpeed);
        this->runAction(moveEvent);
        
        //PhysicsBody* curPhysics = getChildByName("sprite")->getPhysicsBody();
        //curPhysics->applyForce(moveby * m_moveForce);

        break;
    }
    case PATROLLING_STATES::DEAD:
        break;
    }
}