#ifndef __SHARE_BUTTON_H__
#define __SHARE_BUTTON_H__

#include "Interactables/Interactable.h"

class ShareButton : public Interactable
{
public:

	bool Init(Node* scene, Vec2 pos);
	virtual void OnInteract();
	virtual void OnInteractLeave();

	bool isSharing;

	ShareButton();
	~ShareButton();
};

#endif
