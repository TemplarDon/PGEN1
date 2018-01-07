#include "Interactable.h"

bool Interactable::Init(Node *scene)
{
	node = Node::create();
	node->setName("generic interactable object");

	//Adding a Sprite 
	sprite = Sprite::create("Blue_Front1.png");
	sprite->setName("generic interactable object image");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(1000, 1000);
	sprite->setScale(0.4);
	node->addChild(sprite, 1);

	//Addding a physics body - (this is a child of the sprite)
	/*body = PhysicsBody::createBox( Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.1, 1.0f, 0.0f));
	body->setDynamic(false);
	sprite->addComponent(body);*/

	scene->addChild(node);
	
	return true;
}

Interactable::Interactable()  
{
}

Interactable::~Interactable()
{
}

void Interactable::OnInteract()
{
	CCLOG("Interacted with interactable object");
}
