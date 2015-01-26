#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define HP_BIG 0
#define HP_SMALL 1
#define GIANT 2
#define BOOST 3
#define MAGNET 4
#define BOOM 5

class Item :public Sprite
{
private:

	int type;
	float speed;

public:
	static Item* create(int type);
	virtual bool init();
	Item();
	~Item();

	inline void setSpeed(float spd){ speed = spd; }
	inline int getType(){ return type; }
	void update(float dt);
private:


};

