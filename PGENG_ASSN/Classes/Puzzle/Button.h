#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "PuzzleElement.h"

class Button : public PuzzleElement
{
public:
    bool Init(Node* scene, Vec2 pos);
    virtual void OnInteract();
    virtual void OnInteractLeave();

    Button();
    ~Button();
};

#endif