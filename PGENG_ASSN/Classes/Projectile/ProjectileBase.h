#ifndef _PROJECTILE_BASE_H
#define _PROJECTILE_BASE_H

#include "cocos2d.h"
#include "Animation\AnimationController.h"

using namespace cocos2d;

class ProjectileBase : public Node
{

public:
    ProjectileBase();
    virtual ~ProjectileBase();

    virtual bool init();
    virtual void InitPhysicBody();
    virtual void update(double dt);

    inline void SetProjectileDamage(const float& _damage){ this->projectile_Damage = _damage; };
    inline float GetProjectileDamage(void){ return this->projectile_Damage; };

	inline void SetLifespan(const float& _lifespan){ this->lifespan = _lifespan; };
	inline float GetLifespan(void){ return this->lifespan; }

    virtual void CollisionResponse(Node* _other)
    {
    };

	virtual void TimeOut();

protected:
    float projectile_Damage;

	float lifespan;
	float currentLifetime;
};


#endif // _PROJECTILE_BASE_H