#include "SpriteBuilder.h"

AnimateBuilder::AnimateBuilder()
{

}

AnimateBuilder::~AnimateBuilder()
{

}

void AnimateBuilder::LoadSpriteSheet(string sprite_sheet_name, string file_name, unsigned rows, unsigned coloumn)
{
	Sprite* resc = Sprite::create(file_name);
	Vector<SpriteFrame*> sprite_frames;
	Texture2D* texture = resc->getTexture();
	float width = resc->getContentSize().width / coloumn;
	float height = resc->getContentSize().height / rows;

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < coloumn; ++j)
		{
			SpriteFrame* sprite = SpriteFrame::createWithTexture(texture, Rect(j * width, i * height, width, height));
			sprite->retain();
			sprite_frames.pushBack(sprite);
		}

	spriteSheetDatabase[sprite_sheet_name] = sprite_frames;

}

void AnimateBuilder::LoadAnimateFromLoadedSpriteSheet(string animate_name, string sprite_sheet_name, unsigned start_frame, unsigned end_frame, float time_between_frames, bool loop)
{
	Vector<SpriteFrame*> new_animate(end_frame - start_frame);
	for (int i = start_frame; i <= end_frame; ++i)
	{
		SpriteFrame* sprite = spriteSheetDatabase[sprite_sheet_name].at(i);
		new_animate.pushBack(sprite);
	}

	Animation* anim = Animation::createWithSpriteFrames(new_animate, time_between_frames);
	Animate* animate = Animate::create(anim);

	animateDatabase[animate_name] = animate;
}

void AnimateBuilder::LoadAnimateFromWholeSpriteSheet(string animate_name, string file_name, unsigned rows, unsigned coloumn, float time_between_frames, bool loop)
{
	Sprite* resc = Sprite::create(file_name);
	Vector<SpriteFrame*> sprite_frames;
	Texture2D* texture = resc->getTexture();
	float width = resc->getContentSize().width / coloumn;
	float height = resc->getContentSize().height / rows;

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < coloumn; ++j)
		{
			SpriteFrame* sprite = SpriteFrame::createWithTexture(texture, Rect(j * width, i * height, width, height));
			sprite->retain();
			sprite_frames.pushBack(sprite);
		}

	Animation* anim = Animation::createWithSpriteFrames(sprite_frames, time_between_frames);
	Animate* animate = Animate::create(anim);

	animateDatabase[animate_name] = animate;
}

void AnimateBuilder::LoadAnimateSpriteBySprite(string animate_name, initializer_list<string> frame_names, float time_between_frames, bool loop)
{
	Vector<SpriteFrame*> sprite_frames;
	sprite_frames.reserve(frame_names.size());

	for (initializer_list<string>::iterator itr = frame_names.begin(); itr != frame_names.end(); ++itr)
	{
		Sprite* resc = Sprite::create(*itr);
		sprite_frames.pushBack(SpriteFrame::create(*itr, Rect(0, 0, resc->getContentSize().width, resc->getContentSize().height)));
	}

	Animation* anim = Animation::createWithSpriteFrames(sprite_frames, time_between_frames);
	Animate* animate = Animate::create(anim);

	animateDatabase[animate_name] = animate;
	animateDatabase[animate_name]->retain();
}

Animate* AnimateBuilder::GetAnimate(string animate_name)
{
	return animateDatabase[animate_name];
}

Size AnimateBuilder::GetSpriteSize(string sprite_sheet_name, unsigned row_position, unsigned coloumn_position)
{
    Vector<SpriteFrame*> v_spriteFrame = spriteSheetDatabase[sprite_sheet_name];

    return v_spriteFrame.at((row_position * coloumn_position) - 1)->getOriginalSize();
}

Sprite* AnimateBuilder::GetSpriteFromSpriteSheet(string sprite_sheet_name, unsigned row_position, unsigned coloumn_position)
{
   
    return nullptr;
}

bool AnimateBuilder::init()
{
	if (!Node::init())
		return false;

	return true;
}
