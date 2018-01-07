#ifndef _PLAYER_RANGE_WEAPON_H
#define _PLAYER_RANGE_WEAPON_H
#include "Player\Player.h"
#include "WeaponBase.h"

class PlayerRangeWeapon : public WeaponBase
{
public:
    PlayerRangeWeapon(Player* _player);
    virtual ~PlayerRangeWeapon();

    virtual void Update(double dt);
    virtual void Discharge(Vec2 Direction);

    Player* player;
protected:

};


#endif // _PLAYER_RANGE_WEAPON_H