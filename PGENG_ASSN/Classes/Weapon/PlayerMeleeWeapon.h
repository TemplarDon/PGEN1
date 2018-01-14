#ifndef _PLAYER_MELEE_WEAPON_H
#define _PLAYER_MELEE_WEAPON_H
#include "Player\Player.h"
#include "WeaponBase.h"

class PlayerMeleeWeapon : public WeaponBase
{
public:
    PlayerMeleeWeapon(Player* _player);
    virtual ~PlayerMeleeWeapon();

    virtual void Update(double dt);
    virtual void Discharge(Vec2 Direction);

    Player* player;
protected:

};


#endif // _PLAYER_Melee_WEAPON_H