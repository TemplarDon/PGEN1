#include "WeaponBase.h"

WeaponBase::WeaponBase() : 
b_canFire(true),
weaponDamage(0),
fireRate(0),
bulletDelay(0)
{
}

WeaponBase::~WeaponBase()
{
}

void WeaponBase::Update(double dt)
{
}

void WeaponBase::Discharge(Vec2 Direction)
{
    this->runAction(Sequence::create(
        CCDelayTime::create(fireRate),
        CallFunc::create([&]()
    {
        b_canFire = true;
    }
        ),
        NULL
        ));
};