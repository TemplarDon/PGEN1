#include "AnimationController.h"
#include "SpriteBuilder.h"


bool AnimationController::PlayAnimation(string animation_name, bool loop)
{
	if (currentAnim == animMap[animation_name])
	{
		if (controlledNode->numberOfRunningActions() == 0)	//Check if animation is done
		{
			controlledNode->runAction(animMap[animation_name]);
			return true;
		}
		else
			return false;
	}

	controlledNode->stopAllActions();

	if(loop)
		controlledNode->runAction(RepeatForever::create(animMap[animation_name]));
	else
		controlledNode->runAction(animMap[animation_name]);

	currentAnim = animMap[animation_name];

	return true;
}

Animate* AnimationController::GetCurrentAnimation()
{
	return currentAnim;
}

void AnimationController::AddAnimate(string anim_name, Animate* animate)
{
	animMap[anim_name] = animate;
	animMap[anim_name]->retain();
}

void AnimationController::StopAnimation()
{
	controlledNode->stopAllActions();
	currentAnim = NULL;
}


bool AnimationController::Init(Node * node)
{
	if(node == NULL)
		return false;
	
	controlledNode = node;

	return true;
}

AnimationController::AnimationController()
{
}


AnimationController::~AnimationController()
{
}
