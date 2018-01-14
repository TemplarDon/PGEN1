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
		healthPotions = 0;
        return true;
    };

    inline int GetCurrHealth(){ return this->currentHealth; }
    inline void SetCurrHealth(unsigned int _newHealth){ this->currentHealth = clampf(_newHealth, 0, maxHealth); }

    inline int GetMaxHealth(){ return this->maxHealth; }
    inline void SetMaxHealth(unsigned int _newHealth){ this->maxHealth = _newHealth; }

    inline void ResetHealth(){ this->currentHealth = this->maxHealth; }

    inline void TakeDamage(int amount){ this->currentHealth -= amount; if (maxHealth < 0){ maxHealth = 0; } }

	inline unsigned int GetScore(){ return this->score; }
	inline void SetScore(unsigned int _score){ this->score = _score; }

	inline unsigned int GetHighScore(){ return this->highscore; }
	inline void SetHighScore(unsigned int _score){ this->highscore = _score; }

	inline unsigned int GetNumberOfHealthPotions(){ return this->healthPotions; }
	inline void AddHealthPotions(unsigned int amount) { this->healthPotions += amount; }

	inline void SetNumberOfHealthPotions(unsigned int amount) { this->healthPotions = amount; }
	inline bool UseHealthPotion() 
	{ 
		if (!healthPotions || this->currentHealth >= this->maxHealth)
			return false; 

		this->currentHealth++;
		return true;
	}

protected:
    float maxHealth = 5;
    float currentHealth = 5;
    
	unsigned int score;
	unsigned int highscore = 0;
	unsigned int healthPotions = 0;
};

#endif