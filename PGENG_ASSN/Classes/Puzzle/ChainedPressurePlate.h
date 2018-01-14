#ifndef __CHAINED_PRESSURE_PLATE_H__
#define __CHAINED_PRESSURE_PLATE_H__

#include "PuzzleElement.h"

class ChainedPressurePlate : public PuzzleElement
{
public:
    bool Init(Node* scene, Vec2 pos);
    virtual void OnInteract();
    virtual void OnInteractLeave();

    int m_chainNum;

    ChainedPressurePlate* m_prevPlate;

    ChainedPressurePlate();
    ~ChainedPressurePlate();
};

#endif