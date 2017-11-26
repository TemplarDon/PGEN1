#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "cocos2d.h"
#include <initializer_list>
#include <map>

using namespace cocos2d;

using std::map;
using std::string;
using std::initializer_list;

class AnimationController 
{
private:
	Animate* currentAnim;
	Node* controlledNode;
	map<string, Animate*> animMap;

public:

	Animate* GetCurrentAnimation();
	bool PlayAnimation(string animation_name, bool loop = true);
	void AddAnimate(string anim_name, Animate* animate);
	void StopAnimation();

	bool Init(Node* node);

	AnimationController();
	~AnimationController();
};

#endif 

