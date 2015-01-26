#pragma once

#include "cocos2d.h"

#include "GameScene.h"

USING_NS_CC;

class LoadingScene : public Layer
{
private:
	Sprite* loadingImg;
public:
	static Scene* createScene();
	CREATE_FUNC(LoadingScene);
	bool init();
	LoadingScene();
	~LoadingScene();

private:
	void load(float dt);
	void playAnime(float dt);
};

