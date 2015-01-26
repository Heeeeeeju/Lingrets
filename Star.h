#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Star : public Sprite
{
private:

	int additionalScore;
	float speed = 10;
	int type;
public:
	static Star* create(int type);
	virtual bool init();
	Star(int type);
	~Star();
	void update(float dt);

	inline void setSpeed(float speed){ this->speed = speed; }
	int getScore(){ return additionalScore; }

	void removeFromParentWithEffect();
private:
};

