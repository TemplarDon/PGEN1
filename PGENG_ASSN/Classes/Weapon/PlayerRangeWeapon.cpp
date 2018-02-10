#include "PlayerRangeWeapon.h"
#include "../Projectile/PlayerProjectileEntity.h"

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

    Vec2 offSet = AnimateBuilder::GetInstance()->GetSpriteSize("player_bow", 1, 1) * 0.25f * 0.5f;
    player->getParent()->addChild(Create::playerProjectileEntity(player->getPosition() + offSet, 750.0f * Direction, 1, 3), 99);
}
