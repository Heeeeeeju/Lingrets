#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Pet: public Sprite
{
private:
	float sum = 0;
	bool mean = false;
	Sprite *kart;

	float timer = 0;

public:
	CREATE_FUNC(Pet);
	virtual bool init();
	
	Pet();
	~Pet();

	inline Sprite* getKart(){ return kart; }
	inline bool getMean(){ return mean; }

	void update(float dt);

	void showMean(std::string mean);
	Rect getKartBoundingBox();

private:


};

