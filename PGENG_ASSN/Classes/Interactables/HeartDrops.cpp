#include "HeartDrops.h"
#include "Player//PlayerInfo.h"
#include "BitmasksHeader.h"

bool HeartDrop::Init(Node *scene, Vec2 pos)
{
	//this->init();
	this->setName("heartdrop");

	remove_when_done = false;

	this->ignoreAnchorPointForPosition(false);
	this->setIgnoreAnchorPointForPosition(false);

	//Adding a Sprite 
	sprite = Sprite::create("hearticon.png");
	sprite->setName("heart");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->ignoreAnchorPointForPosition(false);
	sprite->setIgnoreAnchorPointForPosition(false);
	sprite->setPosition(150,150);
	sprite->setScale(0.05f);
	this->addChild(sprite, 1000);

	//Addding a physics body - (this is a child of the sprite)
	body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
	body->setDynamic(false);

	body->setTag(PHYSICS_TAG_INTERACTABLE);
    body->setCollisionBitmask(PHYSICS_TAG_INTERACTABLE);
	body->setContactTestBitmask(PLAYER_BITMASK);

	sprite->addComponent(body);

	return true;
}

void HeartDrop::OnInteract()
{
	//if (PlayerInfo::GetInstance()->GetCurrHealth() < PlayerInfo::GetInstance()->GetMaxHealth())
	{
		PlayerInfo::GetInstance()->SetCurrHealth(PlayerInfo::GetInstance()->GetCurrHealth() + 1);
		this->removeFromParentAndCleanup(true);
	}
}

HeartDrop::HeartDrop() : Interactable()
{
}

HeartDrop::~HeartDrop()
{
}
