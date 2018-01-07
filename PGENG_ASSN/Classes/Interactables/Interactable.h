#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "cocos2d.h"
#include "BitmasksHeader.h"

using namespace cocos2d;

class Interactable : public Node
{
private:
	MenuItemFont *text;
	Menu *menu;
public:
	Sprite *sprite;
	PhysicsBody *body;
	bool remove_when_done;

	bool Init(Node *scene);
	void OnInteract();
	void OnInteractLeave();

	Interactable();
	~Interactable();
};

#endif