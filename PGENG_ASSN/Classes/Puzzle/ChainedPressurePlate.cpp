#include "ChainedPressurePlate.h"

ChainedPressurePlate::ChainedPressurePlate() : PuzzleElement()
{}

ChainedPressurePlate::~ChainedPressurePlate()
{}

bool ChainedPressurePlate::Init(Node* scene, Vec2 pos)
{
    PuzzleElement::Init(scene);
    this->setName("ChainedPressurePlate");
    m_prevPlate = nullptr;

    //// Remove generic sprite and body
    if (sprite)
        sprite->removeFromParent();

    //Adding a Sprite 
    sprite = Sprite::create("Puzzle/puzzle_pressureplate.png");
    //sprite = Sprite::create("Blue_Back1.png");
    sprite->setName("ChainedPressurePlate image");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(pos);
    sprite->setScale(0.075);

    //Addding a physics body - (this is a child of the sprite)
    body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
        PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
    body->setDynamic(false);

    body->setTag(PHYSICS_TAG_INTERACTABLE);
    body->setCategoryBitmask(PRESSURE_PLATE);
    body->setCollisionBitmask(PLAYER_BITMASK);
    body->setContactTestBitmask(PLAYER_BITMASK);

    sprite->addComponent(body);

    this->addChild(sprite, 98);
    scene->addChild(this);
    return true;
}

void ChainedPressurePlate::OnInteract()
{
    //this->getChildByName("ChainedPressurePlate image")->getPhysicsBody()->setContactTestBitmask(0x00000000);
    CCLOG("<CHAIN PRESSURE PLATE> interact");

    if (!m_IsCompleted)
    {
        if (m_prevPlate != nullptr)
        {
            if (m_prevPlate->m_IsCompleted)
            {
                CCLOG("<CHAIN PRESSURE PLATE> status change");

                m_IsCompleted = true;
                EventCustom event("puzzle_status_change");
                _eventDispatcher->dispatchEvent(&event);
            }
            else
            {
                EventCustom event("puzzle_failed");
                _eventDispatcher->dispatchEvent(&event);
            }
        }
        else if (m_chainNum == 1)
        {
            CCLOG("<CHAIN PRESSURE PLATE> status change");

            m_IsCompleted = true;
            EventCustom event("puzzle_status_change");
            _eventDispatcher->dispatchEvent(&event);
            
        }
    }
}

void ChainedPressurePlate::OnInteractLeave()
{
    CCLOG("<CHAIN PRESSURE PLATE> interact leave");
    //this->getChildByName("ChainedPressurePlate image")->getPhysicsBody()->setContactTestBitmask(PLAYER_BITMASK);
}