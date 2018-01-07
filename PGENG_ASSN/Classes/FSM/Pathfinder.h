#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include "PathfinderNode.h"

class Pathfinder
{
public:
    Pathfinder();
    ~Pathfinder();

    void Init(TMXTiledMap* map);
    void UpdateCurrentPosition(Vec2 pos);
    void FindPath(Vec2 dest);
    Vec2 FollowPath();
    Vec2 RandomPosition(int range);

    bool m_pathFound;
    bool m_pathComplete;

private:
    PathfinderNode* m_currentNode;
    PathfinderNode* m_destinationNode;

    PathfinderNode*** m_nodeList;
    vector<PathfinderNode*> m_openList;
    vector<PathfinderNode*> m_closedList;
    vector<PathfinderNode*> m_path;

    bool m_followPathCreated;
    bool m_continueNextFrame;

    Vec2 m_currentPos;
    Vec2 m_mapSize;
    int m_currentIdx;
    float m_reachedDist;

    // Debug
    int maxLoops;

    float GetManhattenDist(PathfinderNode* aNode);
    PathfinderNode* GetNode(Vec2 pos);
    bool ValidateNode(PathfinderNode* checkNode, bool checkOpenList = false);
    PathfinderNode* GetLowestF(vector<PathfinderNode*> checkList);
    void RefreshNodeList();
};

#endif