//#ifndef _PLAYER_MELEE_WEAPON_H
//#define _PLAYER_MELEE_WEAPON_H
//
//#include "WeaponBase.h"
//
//class PlayerMeleeWeapon : public WeaponBase
//{
//public:
//    PlayerMeleeWeapon();
//    virtual ~PlayerMeleeWeapon();
//
//    virtual void Update(double dt);
//	virtual void Discharge(Vec3 Direction);
//
//	inline void SetAttackDuration(const float& _attackDuration){ this->attackDuration = _attackDuration; };
//	inline float GetAttackDuration(void){ return this->attackDuration; };
//
//protected:
//	float attackDuration;
//};
//
//namespace Create
//{
//	PlayerMeleeWeapon* playerMeleeWeapon(
//		const float& _fireRate = 0,
//		const float& _damage = 0,
//        );
//};
//
//
//#endif // _PLAYER_MELEE_WEAPON_H