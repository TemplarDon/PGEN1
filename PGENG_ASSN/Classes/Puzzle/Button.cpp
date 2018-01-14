#include "Button.h"

Button::Button() : PuzzleElement()
{}

Button::~Button()
{}

bool Button::Init(Node* scene, Vec2 pos)
{
    PuzzleElement::Init(scene);
    this->setName("button");

    //// Remove generic sprite and body
    if (sprite)
        sprite->removeFromParent();

    //Adding a Sprite 
    sprite = Sprite::create("Puzzle/puzzle_button.png");
    //sprite = Sprite::create("Blue_Back1.png");
    sprite->setName("button image");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(pos);
    sprite->setScale(1);

    //Addding a physics body - (this is a child of the sprite)
    body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
        PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
    body->setDynamic(false);

    body->setTag(PHYSICS_TAG_INTERACTABLE);
    body->setCategoryBitmask(WALLS_BITMASK);
    //body->setCollisionBitmask(PLAYER_BITMASK);
    body->setContactTestBitmask(PLAYER_BITMASK);

    sprite->addComponent(body);

    // Text label
    textLabel = Label::createWithSystemFont("generic", "Arial", 36);
    textLabel->setVisible(false);
    textLabel->setPosition(textLabel->getPosition() + Vec2(sprite->getContentSize().width * 1.5, sprite->getContentSize().height * 1.5));
    textLabel->setScale(0.25);
    sprite->addChild(textLabel, 999);

    this->addChild(sprite, 98);
    scene->addChild(this);
    return true;
}

void Button::OnInteract()
{
    if (!m_IsCompleted)
    {
        m_IsCompleted = true;

        CCLOG("<BUTTON> status change");

        EventCustom event("puzzle_status_change");
        _eventDispatcher->dispatchEvent(&event);

        textLabel->setString("*click*");
        textLabel->setVisible(true);
    }
}

void Button::OnInteractLeave()
{
    textLabel->setVisible(false);
}