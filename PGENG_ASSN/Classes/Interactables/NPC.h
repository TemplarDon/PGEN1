#pragma once

#include "Interactable.h"
#include <string>
using std::string;

class NPC : public Interactable
{
private:
	MenuItemFont *text;

public:
	void SetString(string text);
	string GetString();

	bool Init(Node* scene);
	void OnInteract();
	void OnInteractLeave();

	NPC();
	~NPC();
};