#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BreakBlock:public Sprite
{
private:

	enum BlockType {SmallBlock,BigBlock} blockType;

	float speed = 10;

public:
	static BreakBlock* create(int type);
	virtual bool init();

	BreakBlock();
	~BreakBlock();

	void update(float dt);
	inline void setSpeed(float speed){ this->speed = speed; }
	void removeFromParentWithEffect();

	virtual Rect getBoundingBox();

private:

};

