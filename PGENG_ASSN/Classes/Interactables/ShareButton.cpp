#include "ShareButton.h"
#include "../SceneManagement/SceneManager.h"

ShareButton::ShareButton() : Interactable(), isSharing(false)
{

}

ShareButton::~ShareButton()
{

}

bool ShareButton::Init(Node * scene, Vec2 pos)
{
	Interactable::Init(scene);
	this->setName("ShareButton");

	//// Remove generic sprite and body
	if (sprite)
		sprite->removeFromParent();

	//Adding a Sprite 
	auto sprite = Sprite::create("Puzzle/puzzle_button.png");
	sprite->setName("facebook share button image");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(pos);
	sprite->setScale(1);

	//Addding a physics body - (this is a child of the sprite)
	auto body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
	body->setDynamic(false);
	body->setTag(PHYSICS_TAG_INTERACTABLE);
	body->setCategoryBitmask(BUTTON_BITMASK);
	body->setCollisionBitmask(PLAYER_BITMASK);
	body->setContactTestBitmask(PLAYER_BITMASK);

	sprite->addComponent(body);
	this->addChild(sprite, 98);
	scene->addChild(this);
	return true;
}

void ShareButton::OnInteract()
{
	if (!isSharing)
	{
		EventCustom event("facebook_share");
		_eventDispatcher->dispatchEvent(&event);

		isSharing = true;
	}
}

void ShareButton::OnInteractLeave()
{
	isSharing = false;
}