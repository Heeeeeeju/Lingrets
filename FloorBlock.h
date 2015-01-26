#pragma once

#include "cocos2d.h"

USING_NS_CC;

class FloorBlock : public Sprite
{
private:
	float speed=10;

public:
	FloorBlock();
	~FloorBlock();

	CREATE_FUNC(FloorBlock);
	virtual bool init();

	void update(float dt);

	inline void setSpeed(float spd){ speed = spd; }

private:

};

