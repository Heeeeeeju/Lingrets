#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;


	srand(time(NULL));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	loadingImg = Sprite::create("GameUI/loading1.png");
	loadingImg->setPosition(visibleSize / 2);
	this->addChild(loadingImg);

	this->scheduleOnce(schedule_selector(LoadingScene::playAnime), 0);
	this->scheduleOnce(schedule_selector(LoadingScene::load), 0);


	return true;

}

void LoadingScene::load(float dt)
{
	CCTextureCache* cache = CCTextureCache::sharedTextureCache();

	cache->addImage("GameUI/pausebtn.png");
	cache->addImage("GameUI/bar1.png");
	cache->addImage("GameUI/bar2.png");
	cache->addImage("GameUI/bar3.png");
	cache->addImage("GameUI/clock.png");
	cache->addImage("GameUI/board.png");
	cache->addImage("GameUI/coinholder.png");
	cache->addImage("GameUI/now.png");
	cache->addImage("GameUI/puzzle.png");
	cache->addImage("GameUI/puzzle_.png");
	cache->addImage("GameUI/scoreholder.png");
	cache->addImage("GameUI/targetgage.png");
	cache->addImage("GameUI/shutter.png");


	cache->addImage("Background/back.png");
	cache->addImage("Background/back2.png");
	cache->addImage("Background/back3.png");
	cache->addImage("Background/back4.png");
	cache->addImage("Background/flash.png");
	cache->addImage("Background/floorblock.png");
	cache->addImage("Background/moon.png");
	cache->addImage("Background/sun.png");
	cache->addImage("Background/bgaddc.png");

	cache->addImage("Background/Bonus/back.png");
	cache->addImage("Background/Bonus/back2.png");
	cache->addImage("Background/Bonus/back3.png");
	cache->addImage("Background/Bonus/back4.png");

	cache->addImage("Character/blocked.png");
	cache->addImage("Character/fire1.png");
	cache->addImage("Character/fire2.png");
	cache->addImage("Character/jump.png");
	cache->addImage("Character/jump2.png");
	cache->addImage("Character/run1.png");
	cache->addImage("Character/run2.png");
	cache->addImage("Character/player.png");


	cache->addImage("Character/box_1.png");
	cache->addImage("Character/box_2.png");
	cache->addImage("Character/box_b.png");
	cache->addImage("Character/box_j.png");
	cache->addImage("Character/box_j2.png");
	cache->addImage("Character/da_1.png");
	cache->addImage("Character/da_2.png");
	cache->addImage("Character/da_b.png");
	cache->addImage("Character/da_j.png");
	cache->addImage("Character/da_j2.png");
	cache->addImage("Character/mandarin_1.png");
	cache->addImage("Character/mandarin_2.png");
	cache->addImage("Character/mandarin_b.png");
	cache->addImage("Character/mandarin_j.png");
	cache->addImage("Character/mandarin_j2.png");
	cache->addImage("Character/mu_1.png");
	cache->addImage("Character/mu_2.png");
	cache->addImage("Character/mu_b.png");
	cache->addImage("Character/mu_j.png");
	cache->addImage("Character/mu_j2.png");


	auto pScene = GameScene::createScene();
	Director::sharedDirector()->replaceScene(pScene);
}

void LoadingScene::playAnime(float dt)
{
	auto loadingAnimation = Animation::create();
	loadingAnimation->setDelayPerUnit(0.5);

	loadingAnimation->addSpriteFrameWithFile("GameUI/loading1.png");
	loadingAnimation->addSpriteFrameWithFile("GameUI/loading2.png");
	loadingAnimation->addSpriteFrameWithFile("GameUI/loading3.png");
	loadingAnimation->addSpriteFrameWithFile("GameUI/loading4.png");

	auto loadingAnimate = Animate::create(loadingAnimation);

	auto rep = RepeatForever::create(loadingAnimate);
	loadingImg->runAction(rep);
}