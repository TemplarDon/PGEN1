#ifndef __PATROLLING_FSM_H__
#define __PATROLLING_FSM_H__

#include "BaseFSM.h"

class PatrollingFSM : public BaseFSM
{
public:
    PatrollingFSM(TMXTiledMap* map, string sprite);
    ~PatrollingFSM();
    virtual bool init();

private:
    virtual void Sense();  // get/receive updates from the world
    virtual int Think();   // process the updates
    virtual void Act(int value);     // act upon any change in behaviour

    virtual bool OnCollisionEnter(const PhysicsContact &contact);

public:

    enum PATROLLING_STATES
    {
        IDLE,
        PATROLLING,
        DEAD,

        NUM_STATES,
    };

    PATROLLING_STATES m_currentState;
    Vec2 m_patrolTarget;

    //map<int, Vec2> m_waypoints;
    //int m_idx;

};

#endif