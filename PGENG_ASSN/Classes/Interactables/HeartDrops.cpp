#include "HeartDrops.h"
#include "Player\/PlayerInfo.h"

bool HeartDrop::Init(Node *scene)
{
	//this->init();
	this->setName("generic interactable object");

	remove_when_done = false;

	//Adding a Sprite 
	sprite = Sprite::create("hearticon.png");
	sprite->setName("heart");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(0, 0);
	sprite->setScale(0.05f);
	this->addChild(sprite, 98);

	//Addding a physics body - (this is a child of the sprite)
	body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
	body->setDynamic(false);

	body->setTag(PHYSICS_TAG_INTERACTABLE);
	body->setContactTestBitmask(PLAYER_BITMASK);

	sprite->addComponent(body);
	return true;
}

void HeartDrop::OnInteract()
{
	//if (PlayerInfo::GetInstance().GetCurrHealth() < PlayerInfo::GetInstance().GetMaxHealth())
	{
		PlayerInfo::GetInstance().SetCurrHealth(PlayerInfo::GetInstance().GetCurrHealth() + 1);
		//this->removeFromParentAndCleanup(true);
	}
}
