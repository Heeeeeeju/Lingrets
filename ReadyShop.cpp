#include "ReadyShop.h"


ReadyShop::ReadyShop()
{
}


ReadyShop::~ReadyShop()
{
}

bool ReadyShop::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto backMenu = Menu::create();
	backMenu->setPosition(0, 0);
	this->addChild(backMenu);

	auto black = MenuItemImage::create("Main/black.png", "Main/black.png");
	black->setOpacity(160);
	black->setPosition(visibleSize / 2);
	backMenu->addChild(black);

	auto itemHolder = Sprite::create("Main/ReadyShop/itemholder.png");
	itemHolder->setPosition(400, 350);
	this->addChild(itemHolder);

	auto upgradeHolder = Sprite::create("Main/ReadyShop/upgrade.png");

	auto termB = (visibleSize.width - 1078) / 4;
	upgradeHolder->setPosition( visibleSize.width-termB - 26.5,430);
	upgradeHolder->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(upgradeHolder);

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	itemHolder->addChild(menu);

	auto exit = MenuItemImage::create("Main/ReadyShop/exit.png", "Main/ReadyShop/exit.png", CC_CALLBACK_1(ReadyShop::exit, this));
	exit->setPosition(itemHolder->getContentSize().width - 50, itemHolder->getContentSize().height - 45);
	menu->addChild(exit);

	hpUpg = MenuItemImage::create("Main/ReadyShop/hp_.png", "Main/ReadyShop/hp_.png",CC_CALLBACK_1(ReadyShop::hpF,this));
	hpUpg->setPosition(135, 325);
	menu->addChild(hpUpg);
	char str[6];
	sprintf(str, "Lv.%d", hpLv);
	hpL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	hpL->setPosition(65, 65);
	hpL->setColor(Color3B(0, 0, 0));
	hpUpg->addChild(hpL);

	scoreUpg = MenuItemImage::create("Main/ReadyShop/score_.png", "Main/ReadyShop/score_.png", CC_CALLBACK_1(ReadyShop::scoreF, this));
	scoreUpg->setPosition(290, 325);
	menu->addChild(scoreUpg);
	sprintf(str, "Lv.%d", scoreLv);
	scoreL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	scoreL->setPosition(65, 65);
	scoreL->setColor(Color3B(0, 0, 0));
	scoreUpg->addChild(scoreL);

	bonusUpg = MenuItemImage::create("Main/ReadyShop/time_.png", "Main/ReadyShop/time_.png", CC_CALLBACK_1(ReadyShop::bonusF, this));
	bonusUpg->setPosition(445, 325);
	menu->addChild(bonusUpg);
	sprintf(str, "Lv.%d", bonusLv);
	bonusL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	bonusL->setPosition(65, 65);
	bonusL->setColor(Color3B(0, 0, 0));
	bonusUpg->addChild(bonusL);

	giantBtn = MenuItemImage::create("Main/ReadyShop/giant_.png", "Main/ReadyShop/giant_.png", CC_CALLBACK_1(ReadyShop::giantF, this));
	giantBtn->setPosition(135, 130);
	menu->addChild(giantBtn);
	sprintf(str, "%d", giantCnt);
	giantL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	giantL->setAnchorPoint(Vec2(1, 1));
	giantL->setPosition(125, 120);
	giantL->setColor(Color3B(0, 0, 0));
	giantBtn->addChild(giantL);

	boostBtn = MenuItemImage::create("Main/ReadyShop/boost_.png", "Main/ReadyShop/boost_.png", CC_CALLBACK_1(ReadyShop::boostF, this));
	boostBtn->setPosition(290, 130);
	menu->addChild(boostBtn);
	sprintf(str, "%d", boostCnt);
	boostL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	boostL->setAnchorPoint(Vec2(1, 1));
	boostL->setPosition(125, 120);
	boostL->setColor(Color3B(0, 0, 0));
	boostBtn->addChild(boostL);

	magnetBtn = MenuItemImage::create("Main/ReadyShop/magnet_.png", "Main/ReadyShop/magnet_.png", CC_CALLBACK_1(ReadyShop::magnetF, this));
	magnetBtn->setPosition(445, 130);
	menu->addChild(magnetBtn);
	sprintf(str, "%d", magnetCnt);
	magnetL = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 36);
	magnetL->setAnchorPoint(Vec2(1, 1));
	magnetL->setPosition(125, 120);
	magnetL->setColor(Color3B(0, 0, 0));
	magnetBtn->addChild(magnetL);

	selector = Sprite::create("Main/ReadyShop/select.png");
	selector->setPosition(hpUpg->getPosition());
	itemHolder->addChild(selector, 1);

	upgradeTarget = Sprite::create("Main/ReadyShop/hp.png");
	upgradeTarget->setPosition(upgradeHolder->getContentSize().width / 2, upgradeHolder->getContentSize().height / 2);
	upgradeHolder->addChild(upgradeTarget);

	upgradeMenu = Menu::create();
	upgradeMenu->setPosition(0, 0);
	upgradeHolder->addChild(upgradeMenu);

	auto upgrade = MenuItemImage::create("Main/ReadyShop/levelup.png", "Main/ReadyShop/levelup.png",CC_CALLBACK_1(ReadyShop::upgrade,this));
	upgrade->setPosition(295, 165);
	upgradeMenu->addChild(upgrade);

	return true;
}

void ReadyShop::exit(Object *pSender)
{
	((MainScene*)this->getParent())->unReady();
	removeFromParent();
}

void ReadyShop::hpF(Object *pSender)
{
	selected = hp;
	selector->setPosition(hpUpg->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/hp.png");
}

void ReadyShop::scoreF(Object *pSender)
{
	selected = score;
	selector->setPosition(scoreUpg->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/score.png");
}

void ReadyShop::bonusF(Object *pSender)
{
	selected = bonus;
	selector->setPosition(bonusUpg->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/time.png");

}

void ReadyShop::giantF(Object *pSender)
{
	selected = giant;
	selector->setPosition(giantBtn->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/giant.png");
}

void ReadyShop::boostF(Object *pSender)
{
	selected = boost;
	selector->setPosition(boostBtn->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/boost.png");

}

void ReadyShop::magnetF(Object *pSender)
{
	selected = magnet;
	selector->setPosition(magnetBtn->getPosition());
	upgradeTarget->setTexture("Main/ReadyShop/magnet.png");

}

void ReadyShop::upgrade(Object *pSender)
{
	switch (selected)
	{
	case hp:
		if (hpLv * 500 <= money)
		{
			money -= hpLv++ * 500;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			CCUserDefault::getInstance()->setIntegerForKey("HPLv", hpLv);

			char str[6];
			sprintf(str, "Lv.%d", hpLv);
			hpL->setString(str);
			
		}
		break;
	case score:
		if (scoreLv * 500 <= money)
	{
			money -= scoreLv++ * 500;
		CCUserDefault::getInstance()->setIntegerForKey("Money", money);
		CCUserDefault::getInstance()->setIntegerForKey("ScoreLv", scoreLv);
		char str[6];
		sprintf(str, "Lv.%d", scoreLv);
		scoreL->setString(str);
	}
			   break;
	case bonus:
		if (bonusLv * 500 <= money)
		{
			money -= bonusLv++ * 500;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			CCUserDefault::getInstance()->setIntegerForKey("BonusLv", bonusLv);
			char str[6];
			sprintf(str, "Lv.%d", bonusLv);
			bonusL->setString(str);
		}
		break;
	case giant:
		if (500 <= money)
		{
			money -= 500;
			giantCnt++;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			CCUserDefault::getInstance()->setIntegerForKey("GiantCnt", giantCnt);
			char str[6];
			sprintf(str, "%d", giantCnt);
			giantL->setString(str);
		}
		break;
	case boost:
		if (500 <= money)
		{
			money -= 500;
			boostCnt++;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			CCUserDefault::getInstance()->setIntegerForKey("BoostCnt", boostCnt);
			char str[6];
			sprintf(str, "%d", boostCnt);
			boostL->setString(str);
		}
		break;
	case magnet:
		if ( 500 <= money)
		{
			money -= 500;
			magnetCnt++;
			CCUserDefault::getInstance()->setIntegerForKey("Money", money);
			CCUserDefault::getInstance()->setIntegerForKey("MagnetCnt", magnetCnt);
			char str[6];
			sprintf(str, "%d", magnetCnt);
			magnetL->setString(str);
		}
		break;
	}
	((MainScene*)this->getParent())->setMoney(money);

}