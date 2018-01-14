#pragma once
#include "Interactable.h"

class HeartDrop : public Interactable
{
public:
	bool Init(Node* scene);
	virtual void OnInteract();
};