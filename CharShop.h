#pragma once

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

struct Goods
{
	int no;
	int rank;
	int prize;
	int type;
	int time;
	int level;
	bool soldout;
	bool equiped;
};

class CharShop : public Layer
{
private:

	bool isPet=false;
	MenuItemImage *character, *pet;
	Sprite *slide;
	Sprite *back;

	Menu *shopMenu;

	int money = CCUserDefault::getInstance()->getIntegerForKey("Money",0);

	std::vector<Goods> goodsVector;

public:
	CREATE_FUNC(CharShop);
	bool init();
	CharShop();
	~CharShop();
private:

	void loadShopData();
	void saveShopData();
	
	void buy(Object *pSender);
	void select(Object *pSender);
	void exit(Object *pSender);
	void show();

	void toPet(Object *pSender);
	void toChar(Object *pSender);

};

