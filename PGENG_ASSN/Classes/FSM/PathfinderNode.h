#ifndef __PATHFINDER_NODE_H__
#define __PATHFINDER_NODE_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class PathfinderNode
{
public:
    PathfinderNode(){}
    ~PathfinderNode(){}

    int m_tileCost;
    int m_accumulateCost;

    Vec2 m_pos;
    Vec2 m_gridPos;

    PathfinderNode* m_parentNode;
    bool m_inClosedList;
    bool m_inOpenList;

    void Init(int cost, Vec2 pos, float x, float y)
    {
        m_parentNode = nullptr;
        m_tileCost = cost;
        m_pos = pos;
        m_inClosedList = false;
        m_inOpenList = false;

        m_gridPos.x = x;
        m_gridPos.y = y;
    }

    int CalculateAccumulateCost()
    {
        if (m_parentNode != nullptr)
        {
            m_accumulateCost = m_tileCost + m_parentNode->CalculateAccumulateCost();
            return m_accumulateCost;
        }
        else
        {
            m_accumulateCost = m_tileCost;
            return m_accumulateCost;
        }
    }

    void Reset()
    {
        m_accumulateCost = 0;
        m_parentNode = nullptr;
        m_inClosedList = m_inOpenList = false;
    }
};

#endif