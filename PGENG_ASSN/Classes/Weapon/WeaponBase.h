#ifndef _WEAPON_BASE_H
#define _WEAPON_BASE_H

#include "cocos2d.h"
#include "Animation/SpriteBuilder.h"
#include "Animation/AnimationController.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class WeaponBase : public Node
{
public:
    virtual ~WeaponBase();

    inline void SetDamage(const float& _damage){ this->weaponDamage = _damage; };
    inline float GetDamage(void){ return this->weaponDamage; };

    inline void SetFireRate(const float& _firerate){ this->fireRate = _firerate; };
    inline float GetFireRate(void){ return this->fireRate; };

    virtual void Update(double dt);
    virtual void Discharge(Vec2 Direction);

	bool GetCanFire(){ return this->b_canFire; };

protected:
    WeaponBase();

    bool b_canFire;

    float weaponDamage;
    double fireRate;
    double bulletDelay;
};


#endif // _WEAPON_BASE_H