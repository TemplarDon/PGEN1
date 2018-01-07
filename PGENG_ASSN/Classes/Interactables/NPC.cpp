#include "NPC.h"

void NPC::SetString(string text)
{
	this->text->setString(text);
}

string NPC::GetString()
{
	return text->getString();
}

bool NPC::Init(Node * scene)
{
	Interactable::Init(scene);
	this->setName("NPC");

	text = MenuItemFont::create("NPC text");
	text->setString("Hello.");

	auto *menu = Menu::create(text, nullptr);
	menu->setPosition(getPosition() + Vec2(0.f, 10.0f));
	menu->setName("menu");
	menu->retain();
	text->setPosition(getPosition() + Vec2(0.f, 10.0f));

	scene->addChild(menu);

	return true;
}

void NPC::OnInteract()
{
	CCLOG("Interacted with NPC");

	text->setVisible(true);
}

void NPC::OnInteractLeave()
{
	CCLOG("Interacted with NPC leave");

	text->setVisible(false);
}

NPC::NPC() : Interactable()
{
	
}

NPC::~NPC()
{

}
