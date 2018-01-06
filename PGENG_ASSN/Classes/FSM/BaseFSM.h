#ifndef __BASE_FSM_H__
#define __BASE_FSM_H__

#include "cocos2d.h"
#include "Pathfinder.h"

using namespace cocos2d;
using namespace std;

// Should be child to some interactable/moveable parent class
class BaseFSM : public Node
{

protected:
    BaseFSM(TMXTiledMap* map);
    
    Pathfinder* m_pathFinder;
    TMXTiledMap* m_map;

public:
    bool init();

    virtual ~BaseFSM();
    void RunFSM();

    float m_moveSpeed;

private:

    virtual void Sense() = 0;  // get/receive updates from the world
    virtual int Think() = 0;   // process the updates
    virtual void Act(int value) = 0;     // act upon any change in behaviour
};

#endif