#ifndef _PLAYER_PROJECTILE_ENTITY_H
#define _PLAYER_PROJECTILE_ENTITY_H

#include "cocos2d.h"
#include "Animation/AnimationController.h"
#include "Projectile/ProjectileBase.h"

using namespace cocos2d;

class PlayerProjectileEntity : public ProjectileBase
{
public:
    PlayerProjectileEntity();
    virtual ~PlayerProjectileEntity();

    virtual bool init();
    virtual void update(double dt);
    virtual void InitPhysicBody();
    bool OnCollisionEnter(const PhysicsContact &contact);

protected:

};

namespace Create
{
    PlayerProjectileEntity* playerProjectileEntity(
        const Vec2& _position = Vec2(0, 0),
        const Vec2& _veloctiy = Vec2(0, 0),
        const float& _damage = 0,
        const float& _lifespan = 3
        );
}

#endif // _PLAYER_PROJECTILE_ENTITY_H