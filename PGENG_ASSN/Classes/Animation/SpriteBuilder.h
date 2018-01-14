#ifndef SPRITEBUILDER_H
#define SPRITEBUILDER_H

#include "../Common/SingletonNode.h"
#include "cocos2d.h"
#include <vector>
#include <map>

using namespace cocos2d;

using std::map;
using std::string;
using std::initializer_list;

class AnimateBuilder : public SingletonNode<AnimateBuilder>
{
private:
	static AnimateBuilder* instance;
	map<string, Vector<SpriteFrame*>> spriteSheetDatabase;
	map<string, Animate*> animateDatabase;
 
public:
	AnimateBuilder();
	~AnimateBuilder();

	void LoadSpriteSheet(string sprite_sheet_name, string file_name, unsigned rows, unsigned coloumn);

	void LoadAnimateFromLoadedSpriteSheet(string animate_name, string sprite_sheet_name, unsigned start_frame, unsigned end_frame, float time_between_frames = 0.1f, bool loop = true);
	void LoadAnimateFromWholeSpriteSheet(string animate_name, string file_name, unsigned rows, unsigned coloumn, float time_between_frames = 0.1f, bool loop = true);
	void LoadAnimateSpriteBySprite(string animate_name, initializer_list<string> frame_names, float time_between_frames = 0.1f, bool loop = true);

	Animate* GetAnimate(string animate_name);

    Size GetSpriteSize(string sprite_sheet_name, unsigned row_position, unsigned coloumn_position);

	Sprite* GetSpriteFromSpriteSheet(string sprite_sheet_name, unsigned row_position, unsigned coloumn_position);

	bool init();

friend 
	SingletonNode <Animate>;

};

#endif SPRITEBUILDER_H

