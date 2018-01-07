#ifndef __BASE_FSM_H__
#define __BASE_FSM_H__

#include "cocos2d.h"
#include "Pathfinder.h"
#include "BitmasksHeader.h"
#include "Animation\AnimationController.h"
#include "Animation\SpriteBuilder.h"

using namespace cocos2d;
using namespace std;

// Should be child to some interactable/moveable parent class
class BaseFSM : public Node
{

protected:
    BaseFSM(TMXTiledMap* map, string sprite);
    
    enum ANIMLIST
    {
        FRONT = 0,
        LEFT,
        RIGHT,
        BACK,
        NUM_ANIM,
    };

    Animate* animArr[NUM_ANIM];
    AnimationController* animController;

    Pathfinder* m_pathFinder;
    TMXTiledMap* m_map;
    Sprite* m_sprite;

public:
    bool init();

    virtual ~BaseFSM();
    void RunFSM();

    int m_health;
    float m_moveSpeed;
    bool m_isActive;
private:

    virtual void Sense() = 0;  // get/receive updates from the world
    virtual int Think() = 0;   // process the updates
    virtual void Act(int value) = 0;     // act upon any change in behaviour

    string m_spriteStr;
};

#endif