#ifndef __EXIT_H__
#define __EXIT_H__

#include "Interactables\Interactable.h"
#include <string>
using std::string;

class Exit : public Interactable
{
public:

    bool Init(Node* scene, Vec2 pos);
    virtual void OnInteract();
    virtual void OnInteractLeave();

    Exit();
    ~Exit();

    string m_nextLevel;
};

#endif