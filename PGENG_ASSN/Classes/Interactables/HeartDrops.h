#pragma once
#include "Interactable.h"

class HeartDrop : public Interactable
{
public:
	bool Init(Node* scene, Vec2 pos);
	virtual void OnInteract();

	HeartDrop();
	~HeartDrop();
};