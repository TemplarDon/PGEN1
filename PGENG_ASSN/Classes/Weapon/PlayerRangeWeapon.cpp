#include "PlayerRangeWeapon.h"
#include "Projectile\PlayerProjectileEntity.h"

PlayerRangeWeapon::PlayerRangeWeapon(Player* _player)
{
    this->player = _player;
}

PlayerRangeWeapon::~PlayerRangeWeapon()
{
}

void PlayerRangeWeapon::Update(double dt)
{
}

void PlayerRangeWeapon::Discharge(Vec2 Direction)
{
	if (!b_canFire)
		return;
	else
		b_canFire = false;

    WeaponBase::Discharge(Direction);
    player->getParent()->addChild(Create::playerProjectileEntity(player->getPosition(), 1500 * Direction, 1, 3), 99);
}
