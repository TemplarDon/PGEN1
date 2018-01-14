#ifndef __PUZZLE_ELEMENT_H__
#define __PUZZLE_ELEMENT_H__

#include "Interactables\Interactable.h"
#include <string>
using std::string;

class PuzzleElement : public Interactable
{
public:

    bool Init(Node* scene);
    virtual void OnInteract();
    virtual void OnInteractLeave();

    int m_puzzleID;
    bool m_IsCompleted;

    PuzzleElement();
    ~PuzzleElement();
};

#endif