#include "Puzzle.h"

Puzzle::Puzzle()
{
    if (Node::init())
        init();
}

Puzzle::~Puzzle()
{}

bool Puzzle::init()
{
    if (!Node::init())
    {
        return false;
    }

    //Adding a Sprite 
    auto sprite = Sprite::create("Puzzle/puzzle_door.png");
    sprite->setName("puzzle door image");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setScale(1);

    //Addding a physics body - (this is a child of the sprite)
    auto body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
        PhysicsMaterial(0.000001, 0.000001f, 0.00001f));
    body->setDynamic(false);
    body->setCategoryBitmask(WALLS_BITMASK);
    body->setCollisionBitmask(PLAYER_BITMASK);
    body->setContactTestBitmask(PLAYER_BITMASK);

    sprite->addComponent(body);
    this->addChild(sprite, 98);

    // Adds puzzle listener
    auto puzzleStatusListener = EventListenerCustom::create("puzzle_status_change", [=](EventCustom* event){

        CCLOG("puzzle_status_change received");

        if (CheckPuzzleComplete())
        {
            this->removeFromParent();
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(puzzleStatusListener, 1);

    auto puzzleFailedListener = EventListenerCustom::create("puzzle_failed", [=](EventCustom* event){

        CCLOG("puzzle_failed received");
        //for each (PuzzleElement* var in m_elementList)
        //{
        //    var->m_IsCompleted = false;
        //}

        for (int i = 0; i < m_elementList.size(); ++i)
        {
            m_elementList[i]->m_IsCompleted = false;
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(puzzleFailedListener, 1);
}

bool Puzzle::CheckPuzzleComplete()
{
    //for each (PuzzleElement* var in m_elementList)
    //{
    //    if (!var->m_IsCompleted)
    //        return false;
    //}

    for (int i = 0; i < m_elementList.size(); ++i)
    {
        if (!m_elementList[i]->m_IsCompleted)
            return false;
    }
    
    return true;
}

//void Puzzle::SetPuzzleElementStatus(PuzzleElement* element, bool status)
//{
//    for each (PuzzleElement* var in m_elementList)
//    {
//        if (var == element)
//        {
//            var->m_IsCompleted = status;
//        }
//    }
//}
//
//void Puzzle::SetPuzzleElementStatus(int elementIdx, bool status)
//{
//    m_elementList[elementIdx]->m_IsCompleted = status;
//}