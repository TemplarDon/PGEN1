#include "Pathfinder.h"
#include <math.h>

Pathfinder::Pathfinder()
{}

Pathfinder::~Pathfinder()
{}

void Pathfinder::Init(TMXTiledMap* map)
{
    m_pathFound = false;
    m_pathComplete = false;
    m_followPathCreated = false;
    m_continueNextFrame = false;

    m_currentNode = nullptr;
    m_destinationNode = nullptr;

    m_currentIdx = 0;
    maxLoops = 500;

    m_reachedDist = 0.001f;

    m_openList = vector<PathfinderNode*>();
    m_closedList = vector<PathfinderNode*>();
    m_path = vector<PathfinderNode*>();

    auto collideMap = map->layerNamed("CollideMap");
    auto groundMap = map->layerNamed("Ground");

    m_mapSize = Vec2(map->getMapSize());

    int width = m_mapSize.x;
    int height = m_mapSize.y;

    m_nodeList = new PathfinderNode**[width];

    for (int x = 0; x < m_mapSize.x; ++x)
    {
        m_nodeList[x] = new PathfinderNode*[height];
        for (int y = 0; y < m_mapSize.y; ++y)
        {
            PathfinderNode* node = new PathfinderNode();

            // Check if tile is in collidemap
            auto sprite = collideMap->tileAt(Vec2(x, y));
            Vec2 pos = groundMap->tileAt(Vec2(x, y))->getPosition();
            if (sprite)
            {
                // if in, tile is collidable
                node->Init(-1, pos, x, y);
            }
            else
            {
                // if not, tile is noncollidable
                node->Init(1, pos, x, y);
            }

            m_nodeList[x][y] = node;
        }
    }

}

void Pathfinder::UpdateCurrentPosition(Vec2 pos)
{
    m_currentPos = pos;
}

void Pathfinder::FindPath(Vec2 dest)
{
    if (!m_continueNextFrame)
    {
        // Reset variables
        m_pathComplete = false;
        m_pathFound = false;

        RefreshNodeList();

        m_destinationNode = GetNode(dest);
        m_destinationNode->m_inClosedList = false;
        m_destinationNode->m_inOpenList = false;

        m_currentNode = GetNode(m_currentPos);
    }

    vector<PathfinderNode*> neighbours;
    int loopCount = 0;

    while (!m_pathFound && loopCount <= maxLoops)
    {
        // Add Current Node to closed list
        if (ValidateNode(m_currentNode))
        {
            m_currentNode->m_inOpenList = false;
            m_currentNode->m_inClosedList = true;
            m_closedList.push_back(m_currentNode);
        }

        // Check if reached target
        if (m_destinationNode->m_inClosedList)
        {
            m_pathFound = true;
            m_continueNextFrame = false;
        }

        // Get Neighbours of curr node, compute F-values and add to openlist
        int checkX = m_currentNode->m_gridPos.x;
        int checkY = m_currentNode->m_gridPos.y;

        // Up
        if (checkY + 1 < m_mapSize.y)
        {
            if (ValidateNode(m_nodeList[checkX][checkY + 1], true))
            {
                m_nodeList[checkX][checkY + 1]->m_inOpenList = true;

                m_openList.push_back(m_nodeList[checkX][checkY + 1]);
                neighbours.push_back(m_nodeList[checkX][checkY + 1]);
            }
        }

        // Down
        if (checkY - 1 >= 0)
        {
            if (ValidateNode(m_nodeList[checkX][checkY - 1], true))
            {
                m_nodeList[checkX][checkY - 1]->m_inOpenList = true;

                m_openList.push_back(m_nodeList[checkX][checkY - 1]);
                neighbours.push_back(m_nodeList[checkX][checkY - 1]);
            }
        }

        // Left
        if (checkX - 1 >= 0)
        {
            if (ValidateNode(m_nodeList[checkX - 1][checkY], true))
            {
                m_nodeList[checkX - 1][checkY]->m_inOpenList = true;

                m_openList.push_back(m_nodeList[checkX - 1][checkY]);
                neighbours.push_back(m_nodeList[checkX - 1][checkY]);
            }
        }

        // Right
        if (checkX + 1 < m_mapSize.x)
        {
            if (ValidateNode(m_nodeList[checkX + 1][checkY], true))
            {
                m_nodeList[checkX + 1][checkY]->m_inOpenList = true;

                m_openList.push_back(m_nodeList[checkX + 1][checkY]);
                neighbours.push_back(m_nodeList[checkX + 1][checkY]);
            }
        }

        // Set all neghbours parent to current node
        for each (PathfinderNode* var in neighbours)
        {
            if (var->m_parentNode == nullptr)
                var->m_parentNode = m_currentNode;
        }

        // Get neighbour with lowest F value ()
        PathfinderNode* lowest = GetLowestF(m_openList);
        
        for (auto it = m_openList.begin(); it != m_openList.end();) 
        {
            if (*it == lowest)
            {
                it = m_openList.erase(it);
            }
            else 
            {
                ++it;
            }
        }
        m_currentNode = lowest;
        neighbours.clear();

        // Increase the loop and check if over loop limit
        ++loopCount;
        if (loopCount <= maxLoops)
            m_continueNextFrame = true;
    }
}

Vec2 Pathfinder::FollowPath()
{
    if (!m_followPathCreated)
    {
        PathfinderNode* endNode = (m_closedList.back());

        m_path.push_back(endNode);

        while (endNode->m_parentNode != nullptr)
        {
            endNode = endNode->m_parentNode;
            m_path.push_back(endNode);
        }

        std::reverse(m_path.begin(), m_path.end());
        m_followPathCreated = true;
    }

    if (!m_pathComplete)
    {
        if (m_currentPos.distance(m_path[m_currentIdx]->m_pos) <= m_reachedDist)
        {
            ++m_currentIdx;
        }

        if (m_currentIdx >= m_path.size())
        {
            m_pathComplete = true;
            m_pathFound = false;
            m_followPathCreated = false;
            m_path.clear();

            m_currentIdx = 0;

            return Vec2();
        }

        return (m_path[m_currentIdx]->m_pos - m_currentPos).getNormalized();
    }



    return Vec2();
}

float Pathfinder::GetManhattenDist(PathfinderNode* aNode)
{
    return (abs(m_destinationNode->m_pos.x - aNode->m_pos.x) + abs(m_destinationNode->m_pos.y - aNode->m_pos.y));
}

PathfinderNode* Pathfinder::GetNode(Vec2 pos)
{
    float closest = 999999;
    int closestX = 0;
    int closestY = 0;

    for (int x = 0; x < m_mapSize.x; ++x)
    {
        for (int y = 0; y < m_mapSize.y; ++y)
        {
            float tempDist = m_nodeList[x][y]->m_pos.distance(pos);
            if (tempDist < closest)
            {
                closest = tempDist;
                closestX = x;
                closestY = y;
            }
        }
    }

    return m_nodeList[closestX][closestY];
}

bool Pathfinder::ValidateNode(PathfinderNode* checkNode, bool checkOpenList)
{
    if (checkNode == nullptr)
    {
        return false;
    }

    if (checkNode->m_tileCost <= -1)
    {
        return false;
    }

    if (checkNode->m_inClosedList)
    {
        return false;
    }

    if (checkOpenList)
    {
        if (checkNode->m_inOpenList) {
            return false;
        }
    }

    return true;
}

PathfinderNode* Pathfinder::GetLowestF(vector<PathfinderNode*> checkList)
{
    if (checkList.size() <= 0)
        return nullptr;

    float LowestF_Value = 99999;
    int LowestF_Idx = 0;
    for (int i = 0; i < checkList.size(); ++i)
    {
        if (checkList[i]->CalculateAccumulateCost() + GetManhattenDist(checkList[i]) < LowestF_Value)
        {
            LowestF_Value = checkList[i]->m_accumulateCost + GetManhattenDist(checkList[i]);
            LowestF_Idx = i;
        }
    }
    return checkList[LowestF_Idx];
}

void Pathfinder::RefreshNodeList()
{
    for (int x = 0; x < m_mapSize.x; ++x)
    {
        for (int y = 0; y < m_mapSize.y; ++y)
        {
            m_nodeList[x][y]->Reset();
        }
    }
}