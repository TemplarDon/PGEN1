#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "cocos2d.h"
using namespace cocos2d;

class Interactable
{
private:

public:
	Sprite *sprite;
	PhysicsBody *body;
	Node *node;

	bool Init(Node *scene);
	virtual void OnInteract();

	Interactable();
	~Interactable();
};

#endif