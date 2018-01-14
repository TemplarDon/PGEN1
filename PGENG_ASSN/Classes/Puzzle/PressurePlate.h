#ifndef __PRESSURE_PLATE_H__
#define __PRESSURE_PLATE_H__

#include "PuzzleElement.h"

class PressurePlate : public PuzzleElement
{
public:
    bool Init(Node* scene, Vec2 pos);
    virtual void OnInteract();
    virtual void OnInteractLeave();

    PressurePlate();
    ~PressurePlate();
};

#endif
