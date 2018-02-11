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
    body->setCategoryBitmask(PRESSURE_PLATE_BITMASK);
    //body->setCollisionBitmask(PLAYER_BITMASK);
    body->setContactTestBitmask(PLAYER_BITMASK);

    sprite->addComponent(body);

    // Text label
    textLabel = Label::createWithSystemFont("generic", "Arial", 36);
    textLabel->setVisible(false);
    textLabel->setPosition(textLabel->getPosition() + Vec2(-sprite->getContentSize().width * 0.5, sprite->getContentSize().height * 1.25));
    textLabel->setScale(3);
    sprite->addChild(textLabel, 999);

    this->addChild(sprite, 98);
    scene->addChild(this);

    auto particleSystem = ParticleSystemQuad::create("particle_puzzleclick.plist");
    particleSystem->setName("particle_puzzleclick");
    sprite->setAnchorPoint(Vec2::ZERO);
    particleSystem->setPosition(pos);
    particleSystem->setScale(0.1);
    particleSystem->stop();
    addChild(particleSystem, 99);

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

                textLabel->setString("*click*");
                textLabel->setVisible(true);

                (static_cast<ParticleSystemQuad*>(getChildByName("particle_puzzleclick")))->start();
            }
            else
            {
                textLabel->setString("*silence*");
                textLabel->setVisible(true);

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

            textLabel->setString("*click*");
            textLabel->setVisible(true);
            
        }
    }
}

void ChainedPressurePlate::OnInteractLeave()
{
    CCLOG("<CHAIN PRESSURE PLATE> interact leave");
    //this->getChildByName("ChainedPressurePlate image")->getPhysicsBody()->setContactTestBitmask(PLAYER_BITMASK);

    textLabel->setVisible(false);
}