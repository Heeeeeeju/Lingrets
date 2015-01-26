#include "CharShop.h"


CharShop::CharShop()
{
}


CharShop::~CharShop()
{
}

bool CharShop::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	auto menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);

	auto black = MenuItemImage::create("Main/black.png", "Main/black.png");
	menu->addChild(black);
	black->setOpacity(160);
	black->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	back = Sprite::create("Main/CharShop/back.png");
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(back);

	shopMenu = Menu::create();
	shopMenu->setPosition(0, 0);
	back->addChild(shopMenu,1);

	character = MenuItemImage::create("Main/CharShop/char.png", "Main/CharShop/char.png",CC_CALLBACK_1(CharShop::toChar, this));
	shopMenu->addChild(character);
	character->setPosition(142, 455);

	pet = MenuItemImage::create("Main/CharShop/pet_.png", "Main/CharShop/pet_.png", CC_CALLBACK_1(CharShop::toPet, this));
	shopMenu->addChild(pet);
	pet->setPosition(345, 455);

	auto exit = MenuItemImage::create("Main/CharShop/exit.png", "Main/CharShop/exit.png",CC_CALLBACK_1(CharShop::exit,this));
	shopMenu->addChild(exit);
	exit->setPosition(1045, 470);

	slide = Sprite::create("Main/CharShop/slide.png");
	slide->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2-25);
	back->addChild(slide, 2);

/*	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			Goods goods = { i + 1, i % 3, 10000, 1, 30, 6, true, true};
			goodsVector.push_back(goods);
		}
		else
		{
			Goods goods = { i + 1, i % 3, 0, 1, 30, 1, false, false };
			goodsVector.push_back(goods);
		}
	}
	saveShopData();*/
	loadShopData();

	show();
	

	return true;
}

void CharShop::exit(Object* pSender)
{
	this->removeFromParent();
}

void CharShop::loadShopData()
{
	std::string data;
	int size;
	if (!isPet)
	{
		data = CCUserDefault::sharedUserDefault()->getStringForKey("CharaterData");
		size = CCUserDefault::sharedUserDefault()->getIntegerForKey("CharaterSize");
	}
	else
	{
		data = CCUserDefault::sharedUserDefault()->getStringForKey("PetData");
		size = CCUserDefault::sharedUserDefault()->getIntegerForKey("PetSize");
	}
	goodsVector.clear();

	for (int i = 0; i < size; i++)
	{
		char getdata[26];

		int no;//3
		int rank;//1
		int prize;//5
		int type;//1
		int time;//3
		int level;//1
		int soldout;//1
		int equiped;//1

		strcpy(getdata, data.substr(i * 25, 25).c_str());
		sscanf(getdata, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", &no, &rank, &prize, &type,&time,&level,&soldout,&equiped);
		Goods goods;
		if (equiped == 1)
		{
			goods = { no, rank, prize, type, time, level, true, true };
		}
		else if (soldout == 1)
		{
			goods = { no, rank, prize, type, time, level, true, false};
		}
		else
		{
			goods = { no, rank, prize, type, time, level, false, false };
		}
		goodsVector.push_back(goods);
		
	}


}

void CharShop::saveShopData()
{
	std::string str;
	str.clear();
	for (int i = 0; i < goodsVector.size(); i++)
	{

		char apnd[26];
		auto bg = goodsVector.at(i);
		if (bg.equiped)
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t1\t1\t\n", bg.no,bg.rank,bg.prize,bg.type,bg.time,bg.level);
		else if (bg.soldout)
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t1\t0\t\n", bg.no, bg.rank, bg.prize, bg.type, bg.time, bg.level);
		else
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t0\t0\t\n", bg.no, bg.rank, bg.prize, bg.type, bg.time, bg.level);

		str.append(apnd);
	}

	if (!isPet)
	{
		CCUserDefault::sharedUserDefault()->setStringForKey("CharaterData", str);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("CharaterSize", goodsVector.size());
	}
	else
	{
		CCUserDefault::sharedUserDefault()->setStringForKey("PetData", str);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("PetSize", goodsVector.size());
	}
}

void CharShop::buy(Object *pSender)
{
	int num = ((MenuItemImage*)pSender)->getParent()->getParent()->getTag();
	auto holderMenu = ((MenuItemImage*)pSender)->getParent();
	auto holder = holderMenu->getParent();
	if (goodsVector.at(num).soldout)
		return;
	else
	{
		if (goodsVector.at(num).prize <= money)
		{
			money -= goodsVector.at(num).prize;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			((MainScene*)this->getParent())->setMoney(money);
			goodsVector.at(num).soldout = true;
			holderMenu->removeFromParent();

			auto menu = Menu::create();
			menu->setPosition(0, 0);
			menu->setName("menu");
			holder->addChild(menu);

			auto equip = MenuItemImage::create("Main/CharShop/select.png", "Main/CharShop/select.png", CC_CALLBACK_1(CharShop::select, this));
			equip->setPosition(holder->getContentSize().width / 2, 45);
			equip->setName("button");
			menu->addChild(equip);
		}
	}
	saveShopData();
}

void CharShop::select(Object *pSender)
{
	int num = ((MenuItemImage*)pSender)->getParent()->getParent()->getTag();
	auto holderMenu = ((MenuItemImage*)pSender)->getParent();
	auto holder = holderMenu->getParent();
	if (goodsVector.at(num).soldout && !goodsVector.at(num).equiped)
	{
		int i = 0;
		for (auto iter = goodsVector.begin(); iter != goodsVector.end(); iter++,i++)
		{
			if (iter->equiped)
			{
				iter->equiped = false;
				auto holder = slide->getChildByTag(i);
				holder->removeChildByName("menu");

				auto holdermenu = Menu::create();
				holdermenu->setPosition(0, 0);
				holdermenu->setName("menu");
				holder->addChild(holdermenu);

				auto equip = MenuItemImage::create("Main/CharShop/select.png", "Main/CharShop/select.png",CC_CALLBACK_1(CharShop::select,this));
				equip->setPosition(holder->getContentSize().width / 2, 45);
				equip->setName("button");
				holdermenu->addChild(equip);
			}

		}
		goodsVector.at(num).equiped = true;

		if (!isPet)
			CCUserDefault::getInstance()->setIntegerForKey("EquipedChar", num+1);
		else
			CCUserDefault::getInstance()->setIntegerForKey("EquipedPet", num+1);

		auto menu = Menu::create();
		menu->setPosition(0, 0);
		menu->setName("menu");
		holder->addChild(menu);

		auto equip = MenuItemImage::create("Main/CharShop/equiped.png", "Main/CharShop/equiped.png");
		equip->setPosition(holder->getContentSize().width / 2, 45);
		equip->setName("button");
		menu->addChild(equip);

		saveShopData();
	}

}

void CharShop::show()
{
	slide->removeAllChildren();

	int i = 0;
	for (auto iter = goodsVector.begin(); iter != goodsVector.end(); iter++, i++)
	{
		auto holder = Sprite::create("Main/CharShop/holder.png");
		holder->setPosition(holder->getContentSize().width *(i + 0.5), slide->getContentSize().height / 2);
		slide->addChild(holder);
		holder->setTag(i);

		Sprite* rank;
		switch (iter->rank)
		{
		case 0:
			rank = Sprite::create("Main/CharShop/c.png"); break;
		case 1:
			rank = Sprite::create("Main/CharShop/b.png"); break;
		case 2:
			rank = Sprite::create("Main/CharShop/a.png"); break;
		}
		rank->setPosition(35, 370);
		holder->addChild(rank);

		char filename[32];
		if (!isPet)
			sprintf(filename, "Main/CharShop/Character/%.3d.png", iter->no);
		else
			sprintf(filename, "Main/CharShop/Pet/%.3d.png", iter->no);
		auto charImg = Sprite::create(filename);
		charImg->setPosition(holder->getContentSize().width / 2, 265);
		holder->addChild(charImg);

		auto levelGage = Sprite::create("Main/CharShop/level.png");
		levelGage->setPosition(holder->getContentSize().width / 2, 155);
		holder->addChild(levelGage);

		for (int i = 2; i < iter->level; i++)
		{
			//28
			char file[20];
			sprintf(file, "Main/CharShop/%d.png", i);
			auto levelImg = Sprite::create(file);
			levelImg->setAnchorPoint(Vec2(1, 0.5));
			levelImg->setPosition(i * 28 + 1, 15);
			levelGage->addChild(levelImg);
		}

		auto time = Sprite::create("Main/CharShop/time.png");
		time->setPosition(holder->getContentSize().width / 2, 125);
		holder->addChild(time);

		auto type = Sprite::create("Main/CharShop/type.png");
		type->setPosition(holder->getContentSize().width / 2, 85);
		holder->addChild(type);

		auto holderMenu = Menu::create();
		holderMenu->setPosition(0, 0);
		holderMenu->setName("menu");
		holder->addChild(holderMenu);

		if (iter->equiped)
		{
			auto equip = MenuItemImage::create("Main/CharShop/equiped.png", "Main/CharShop/equiped.png");
			equip->setPosition(holder->getContentSize().width / 2, 45);
			equip->setName("button");
			holderMenu->addChild(equip);
		}
		else  if (iter->soldout)
		{
			auto equip = MenuItemImage::create("Main/CharShop/select.png", "Main/CharShop/select.png", CC_CALLBACK_1(CharShop::select, this));
			equip->setPosition(holder->getContentSize().width / 2, 45);
			equip->setName("button");
			holderMenu->addChild(equip);
		}
		else
		{
			auto equip = MenuItemImage::create("Main/CharShop/buy.png", "Main/CharShop/buy.png", CC_CALLBACK_1(CharShop::buy, this));
			equip->setPosition(holder->getContentSize().width / 2, 45);
			equip->setName("button");
			holderMenu->addChild(equip);
		}

	}

}


void CharShop::toPet(Object *pSender)
{ 
	saveShopData();
	isPet = true;

	shopMenu->removeFromParent();
	
	shopMenu = Menu::create();
	shopMenu->setPosition(0, 0);
	back->addChild(shopMenu, 1);

	character = MenuItemImage::create("Main/CharShop/char_.png", "Main/CharShop/char_.png", CC_CALLBACK_1(CharShop::toChar, this));
	shopMenu->addChild(character);
	character->setPosition(142, 455);

	pet = MenuItemImage::create("Main/CharShop/pet.png", "Main/CharShop/pet.png", CC_CALLBACK_1(CharShop::toPet, this));
	shopMenu->addChild(pet);
	pet->setPosition(345, 455);

	auto exit = MenuItemImage::create("Main/CharShop/exit.png", "Main/CharShop/exit.png", CC_CALLBACK_1(CharShop::exit, this));
	shopMenu->addChild(exit);
	exit->setPosition(1045, 470);

	loadShopData();
	show(); 
}

void CharShop::toChar(Object *pSender)
{
	saveShopData();
	isPet = false;

	shopMenu->removeFromParent();
	
	shopMenu = Menu::create();
	shopMenu->setPosition(0, 0);
	back->addChild(shopMenu, 1);

	character = MenuItemImage::create("Main/CharShop/char.png", "Main/CharShop/char.png", CC_CALLBACK_1(CharShop::toChar, this));
	shopMenu->addChild(character);
	character->setPosition(142, 455);

	pet = MenuItemImage::create("Main/CharShop/pet_.png", "Main/CharShop/pet_.png", CC_CALLBACK_1(CharShop::toPet, this));
	shopMenu->addChild(pet);
	pet->setPosition(345, 455);

	auto exit = MenuItemImage::create("Main/CharShop/exit.png", "Main/CharShop/exit.png", CC_CALLBACK_1(CharShop::exit, this));
	shopMenu->addChild(exit);
	exit->setPosition(1045, 470);

	loadShopData();
	show();
}