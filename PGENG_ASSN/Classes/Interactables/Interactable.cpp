#include "Interactable.h"

bool Interactable::Init(Node *scene)
{
	//this->init();
	this->setName("generic interactable object");

	remove_when_done = false;

	//Adding a Sprite 
	sprite = Sprite::create("Blue_Front1.png");
	sprite->setName("generic interactable object image");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(1000, 900);
	sprite->setScale(0.4);
	this->addChild(sprite, 1);

	//Addding a physics body - (this is a child of the sprite)
	body = PhysicsBody::createBox( Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.1, 1.0f, 0.0f));
	body->setDynamic(false);

	body->setTag(PHYSICS_TAG_INTERACTABLE);
	body->setContactTestBitmask(ENEMY_BITMASK);

	sprite->addComponent(body);

	scene->addChild(this, 4);

	/*text = MenuItemFont::create("NPC text");
	text->setString("Hello.");

	menu = Menu::create(text, nullptr);
	menu->setPosition(Point(525, 450));
	menu->setName("menuuu");
	menu->retain();
	text->setPosition(Point(500, 500));

	scene->addChild(menu, 5);*/
	
	return true;
}

Interactable::Interactable() : Node()
{
}

Interactable::~Interactable()
{
}

void Interactable::OnInteract()
{
	//text->setString("Hello.");
	CCLOG("Interacted with generic interactable object");
}

void Interactable::OnInteractLeave()
{
	//text->setString("");
	CCLOG("Interact with generic interactable leave");
	if (remove_when_done)
		this->removeFromParentAndCleanup(true);
}