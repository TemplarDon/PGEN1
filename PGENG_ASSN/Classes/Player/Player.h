#ifndef _PLAYER_H
#define _PLAYER_H

#include "cocos2d.h"
#include "Animation\SpriteBuilder.h"
#include "Animation\AnimationController.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class WeaponBase;

enum PlayerMoveDir
{
    MOVEDIR_LEFT = 0,
    MOVEDIR_RIGHT,
    MOVEDIR_UP,
    MOVEDIR_DOWN,
    MOVEDIR_IDLE,
    NUM_DIR,
};

class Player : public Node
{
public:
    Player();
    virtual ~Player();

    bool init();
    void update(float _dt);

	virtual void TakeDamage(int amount);

	inline void SetMoveSpeed(const float& _value){ this->moveSpeed = _value; };
	inline float GetMoveSpeed(void){ return this->moveSpeed; };

	inline void SetWeapon(WeaponBase* _weapon){ this->weapon = _weapon; };
	inline WeaponBase* GetWeapon(void){ return this->weapon; };

    inline Node* GetPlayerSpriteNode(){ return this->spriteNode; }

protected:
    void InitActions();
    void InitAnimation();
    void InitPhysicBody();

	float moveSpeed;
    float invulTime;
    bool canBeHit = true;
    WeaponBase* weapon;

    Node* spriteNode;
    AnimationController* animController;

    // Player Movement Variables
    PlayerMoveDir currentMoveDirection;

    //Player Movement Functions
    void MovePlayer();
    void MoveIdle();
    void MovePlayerUp();
    void MovePlayerDown();
    void MovePlayerLeft();
    void MovePlayerRight();

    void StopAnimation();

    void StopPlayerMovementUp();
    void StopPlayerMovementDown();
    void StopPlayerMovementLeft();
    void StopPlayerMovementRight();

    void Attack();

};

#endif // _PLAYER_ENTITY_BASE_H