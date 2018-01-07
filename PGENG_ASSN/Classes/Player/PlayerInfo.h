#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "cocos2d.h"

#include "Classes\Common\SingletonNode.h"

using namespace cocos2d;
using namespace std;

class PlayerInfo : public SingletonNode<PlayerInfo>
{
    friend SingletonNode<PlayerInfo>;

public:
    PlayerInfo();
    ~PlayerInfo();

    virtual bool init()
    {
        health = 3;
        score = 0;
        return true;
    };

	inline int GetHealth(){ return this->health; }
	inline void SetHealth(unsigned int hp){ this->health = hp; }
	inline void TakeDamage(int amount){ this->health -= amount; if (health < 0){ health = 0; } }

	inline unsigned int GetScore(){ return this->score; }
	inline void SetScore(unsigned int _score){ this->score = _score; }

	inline unsigned int GetHighScore(){ return this->highscore; }
	inline void SetHighScore(unsigned int _score){ this->highscore = _score; }

protected:
	int health = 1;
	unsigned int score;
	unsigned int highscore = 0;
};

#endif