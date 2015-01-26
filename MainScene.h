#pragma once

#include "cocos2d.h"
#include "LoadingScene.h"
#include "RankLayer.h"
#include "CharShop.h"
#include "ReadyShop.h"
#include "WordNote.h"

class MainScene : Layer
{
private:
	Menu *menu;

	int money = CCUserDefault::getInstance()->getIntegerForKey("Money",0);

	LabelTTF *moneyLabel;
	Layer *changeAbleLayer;
	RankLayer *rankLayer;

	MenuItemImage* gameStart;

	friend class ReadyShop;
	friend class WordNote;

public:
	
	static Scene* createScene();
	
	virtual bool init();
	
	CREATE_FUNC(MainScene);

	void setMoney(int money);

	MainScene();
	~MainScene();

private:

	void wordNote(Object *pSender);

	void charShop(Object *pSender);
	void ReadyShop(Object *pSender);
	void unReady();

	void startGame(Object *pSender);


};

