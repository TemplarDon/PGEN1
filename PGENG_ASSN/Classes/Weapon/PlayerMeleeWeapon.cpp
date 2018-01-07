//#include "PlayerMeleeWeapon.h"
//
//
//PlayerMeleeWeapon::PlayerMeleeWeapon() :
//attackDuration(0),
//meleeHitbox(nullptr)
//{
//}
//
//PlayerMeleeWeapon::~PlayerMeleeWeapon()
//{
//}
//
//void PlayerMeleeWeapon::Update(double dt)
//{
//    WeaponBase::Update(dt);
//
//    if (meleeHitbox)
//    {
//        meleeHitbox->SetPosition(position + (front * 3.5f));
//
//        if (meleeHitbox->GetIsDead() || meleeHitbox->GetIsDone())
//            this->meleeHitbox = NULL;
//    }
//}
//
//void PlayerMeleeWeapon::Discharge(Vector3 Direction)
//{
//	if (!b_canFire)
//		return;
//	else
//		b_canFire = false;
//
//	if (Direction.LengthSquared() >  Math::EPSILON)
//	{
//		Direction.Normalize();
//	}
//	else
//	{
//		return;
//	}
//
//	SoundManager::GetInstance()->PlaySound2D("player_melee_attack");
//
//    this->meleeHitbox = Create::playerMeleeHitboxEntity(EntityManager::GetInstance(),
//		"player_shield_melee",
//		this->position + (Direction * 4.f),
//		Direction, 
//		Vector3(13, 10, 1),  
//        attackDuration,
//		weaponDamage);
//
//    front = Direction;
//}
//
//PlayerMeleeWeapon* Create::playerMeleeWeapon(
//	const float& _fireRate,
//	const float& _damage,
//	const float& _attackDuration 
//    )
//{
//    PlayerMeleeWeapon* weapon = new PlayerMeleeWeapon();
//    weapon->SetDamage(_damage);
//    weapon->SetFireRate(_fireRate);
//	weapon->SetAttackDuration(_attackDuration);
//	
//    return weapon;
//}
