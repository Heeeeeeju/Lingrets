#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define SILVER 0
#define GOLD 1
#define FEVER 2


class Coin:public Sprite
{
private:
	int type;
	int money;
	float speed;
public:

	Coin();
	~Coin();
	static Coin* create(int type);
	virtual bool init();

	inline void setSpeed(float speed){ this->speed = speed; }
	inline int getMoney(){ return money; }

	void update(float dt);
	void removeFromParentWithEffect();
};

