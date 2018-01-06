#include "BaseFSM.h"

BaseFSM::BaseFSM(TMXTiledMap* map) 
: m_map(map)
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

    m_pathFinder = new Pathfinder();
    m_pathFinder->Init(m_map);
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