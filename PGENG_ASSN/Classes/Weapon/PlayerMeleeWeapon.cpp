#include "PlayerMeleeWeapon.h"
#include "Projectile/PlayerProjectileEntity.h"

PlayerMeleeWeapon::PlayerMeleeWeapon(Player* _player)
{
    this->player = _player;
}

PlayerMeleeWeapon::~PlayerMeleeWeapon()
{
}

void PlayerMeleeWeapon::Update(double dt)
{
}

void PlayerMeleeWeapon::Discharge(Vec2 Direction)
{
	if (!b_canFire)
		return;
	else
		b_canFire = false;

    WeaponBase::Discharge(Direction);

    Vec2 offSet = AnimateBuilder::GetInstance().GetSpriteSize("player_bow", 1, 1) * 0.25f * 0.5f;
    player->getParent()->addChild(Create::playerProjectileEntity(player->getPosition() + offSet, 900 * Direction, 1, 3), 99);
}
