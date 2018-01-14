#include "PressurePlate.h"

PressurePlate::PressurePlate() : PuzzleElement()
{}

PressurePlate::~PressurePlate()
{}

bool PressurePlate::Init(Node* scene, Vec2 pos)
{
    PuzzleElement::Init(scene);
    this->setName("pressure plate");

    // Remove generic sprite and body
    if (sprite)
        delete sprite;

    //Adding a Sprite 
    sprite = Sprite::create("Puzzle/puzzle_pressureplate.png");
    sprite->setName("pressure plate image");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(pos);
    sprite->setScale(0.15);
    this->addChild(sprite, 98);

    //Addding a physics body - (this is a child of the sprite)
    body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
        PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
    body->setDynamic(false);

    body->setTag(PHYSICS_TAG_INTERACTABLE);
    body->setCategoryBitmask(PRESSURE_PLATE_BITMASK);
    body->setContactTestBitmask(PLAYER_BITMASK);

    sprite->addComponent(body);

    return true;
}

void PressurePlate::OnInteract()
{
    m_IsCompleted = true;

    EventCustom event("puzzle_status_change");
    _eventDispatcher->dispatchEvent(&event);
}

void PressurePlate::OnInteractLeave()
{
    m_IsCompleted = false;

    EventCustom event("puzzle_status_change");
    _eventDispatcher->dispatchEvent(&event);
}