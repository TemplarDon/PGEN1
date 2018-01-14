#include "PuzzleElement.h"

PuzzleElement::PuzzleElement() : Interactable()
{} 

PuzzleElement::~PuzzleElement()
{}

bool PuzzleElement::Init(Node * scene)
{
    Interactable::Init(scene);
    this->setName("generic puzzle piece");

    m_IsCompleted = false;
    m_puzzleID = -1;
    return true;
}

void PuzzleElement::OnInteract()
{
}

void PuzzleElement::OnInteractLeave()
{
}