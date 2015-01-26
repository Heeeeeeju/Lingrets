#pragma once

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class ResultScene : public Layer
{
private :
	Sprite *resultCard;
	bool end = false;
	bool start = false;
	bool once = false;
public:
	static Scene* createScene();
	CREATE_FUNC(ResultScene);
	bool init();
	ResultScene();
	~ResultScene();

private :
	void selectCard(Object *pSender);
	void cardOpen(Object *pSender);
	void update(float dt);

	bool onTouchBegan(Touch* touch, Event* event);
};

