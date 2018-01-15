#ifndef _PLAYER_MELEE_HITBOX_ENTITY_H
#define _PLAYER_MELEE_HITBOX_ENTITY_H

#include "cocos2d.h"
#include "Animation/AnimationController.h"
#include "Projectile/ProjectileBase.h"

using namespace cocos2d;

class PlayerMeleeHitboxEntity : public ProjectileBase
{
public:
    PlayerMeleeHitboxEntity();
    virtual ~PlayerMeleeHitboxEntity();

    virtual bool init();
    virtual void update(double dt);
    virtual void InitPhysicBody();
    bool OnCollisionEnter(const PhysicsContact &contact);

protected:

};

namespace Create
{
    PlayerMeleeHitboxEntity* playerMeleeHitboxEntity(
        const Vec2& _position = Vec2(0, 0),
        const Vec2& _veloctiy = Vec2(0, 0),
        const float& _damage = 0,
        const float& _lifespan = 3
        );
}

#endif // _PLAYER_MeleeHitbox_ENTITY_H