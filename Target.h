#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Target : public Sprite
{
private:

	int targetNum = 1;
	float speed=9;
	float escapePoint = 2000;

	Animation *animation;
	Animate *animate;

	std::string spriteName;

public:
	~Target();

	static Target* create(const std::string &spriteName);

	void setSpeed(float spd){ speed = spd; }

	void reset(float dt);
	void catched();

	CREATE_FUNC(Target);
	virtual bool init();

	void update(float dt);
	inline float getEscapePoint(){ return escapePoint; }
private:
	Target();

	void changeToNext();
};

