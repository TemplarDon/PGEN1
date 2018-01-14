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
    PlayerInfo(){};
    ~PlayerInfo(){};

    virtual bool init()
    {
        maxHealth = 5;
        currentHealth = 5;
        score = 0;
        return true;
    };

    inline int GetCurrHealth(){ return this->currentHealth; }
    inline void SetCurrHealth(unsigned int _newHealth){ this->currentHealth = _newHealth; }

    inline int GetMaxHealth(){ return this->currentHealth; }
    inline void SetMaxHealth(unsigned int _newHealth){ this->currentHealth = _newHealth; }

    inline void TakeDamage(int amount){ this->maxHealth -= amount; if (maxHealth < 0){ maxHealth = 0; } }

	inline unsigned int GetScore(){ return this->score; }
	inline void SetScore(unsigned int _score){ this->score = _score; }

	inline unsigned int GetHighScore(){ return this->highscore; }
	inline void SetHighScore(unsigned int _score){ this->highscore = _score; }

protected:
    float maxHealth = 5;
    float currentHealth = 5;
    
	unsigned int score;
	unsigned int highscore = 0;
};

#endif