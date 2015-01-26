#pragma once

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class ReadyShop: public Layer
{
private:

	enum SelectedItem{hp,score,bonus,giant,boost,magnet} selected=hp;
	Sprite *selector;
	MenuItemImage *hpUpg;
	MenuItemImage *scoreUpg;
	MenuItemImage *bonusUpg;
	MenuItemImage *giantBtn;
	MenuItemImage *boostBtn;
	MenuItemImage *magnetBtn;

	int hpLv = CCUserDefault::getInstance()->getIntegerForKey("HPLv", 1);
	int scoreLv = CCUserDefault::getInstance()->getIntegerForKey("ScoreLv", 1);
	int bonusLv = CCUserDefault::getInstance()->getIntegerForKey("BonusLv", 1);
	int giantCnt = CCUserDefault::getInstance()->getIntegerForKey("GiantCnt", 1);
	int boostCnt = CCUserDefault::getInstance()->getIntegerForKey("BoostCnt", 1);
	int magnetCnt = CCUserDefault::getInstance()->getIntegerForKey("MagnetCnt", 1);

	LabelTTF *hpL;
	LabelTTF *scoreL;
	LabelTTF *bonusL;
	LabelTTF *giantL;
	LabelTTF *boostL;
	LabelTTF *magnetL;

	int money = CCUserDefault::getInstance()->getIntegerForKey("Money", 0);

	Menu* upgradeMenu;
	Sprite* upgradeTarget;

public:
	ReadyShop();
	~ReadyShop();
	CREATE_FUNC(ReadyShop);
	bool init();
private:

	void hpF(Object *pSender);
	void scoreF(Object *pSender);
	void bonusF(Object *pSender);
	void giantF(Object *pSender);
	void magnetF(Object *pSender);
	void boostF(Object *pSender);

	void upgrade(Object *pSender);

	void exit(Object *pSender);
};

