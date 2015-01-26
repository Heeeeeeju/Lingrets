#include "WordNote.h"


WordNote::WordNote()
{
}


WordNote::~WordNote()
{
}

bool WordNote::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto backMenu = Menu::create();
	backMenu->setPosition(0, 0);
	this->addChild(backMenu);

	auto black = MenuItemImage::create("Main/black.png", "Main/black.png");
	black->setPosition(visibleSize / 2);
	black->setOpacity(160);
	backMenu->addChild(black);

	auto back = Sprite::create("Main/WordNote/back.png");
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(back);
	
	detail = Sprite::create("Main/WordNote/detail.png");
	detail->setPosition(818, 263);
	back->addChild(detail);
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			auto holder = Sprite::create("Main/WordNote/holder.png");
			holder->setPosition(140 * j +115, 140 * i + 115);
			back->addChild(holder);
		}
	}


	WordN *word = new WordN{ "Main/WordNote/a.png", "えんぴつ", "体力減少 5 % 遅い\n", 0, 1, false };
	WordN *word2 = new WordN{ "Main/WordNote/b.png", "原子", "体力 100で 復活", 0, 2, false };
	WordN *word3 = new WordN{ "Main/WordNote/c.png", "カキ", "体力減少 1 % 遅い", 0, 3, false };
	wordNVector.push_back(word);
	wordNVector.push_back(word2);
	wordNVector.push_back(word3);

	menu = Menu::create();
	menu->setPosition(0, 0);
	back->addChild(menu);

	int i = 0;
	for (auto iter = wordNVector.begin(); iter != wordNVector.end(); iter++,i++)
	{
		auto btn = MenuItemImage::create((*iter)->img, (*iter)->img, CC_CALLBACK_1(WordNote::select, this));
		btn->setPosition(140 * i + 115, 395 );
		btn->setTag(i);
		menu->addChild(btn);
		char str[3];
		sprintf(str, "+%d", (*iter)->enchant);
		auto lbl = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 24);
		lbl->setPosition(100, 100);
		lbl->setAnchorPoint(Vec2(1, 1));
		lbl->setColor(Color3B(0, 0, 0));
		btn->addChild(lbl,1, "label");
		if ((*iter)->enchant <= 0)
			lbl->setVisible(false);

	}

	auto exitMenu = Menu::create();
	exitMenu->setPosition(0, 0);
	back->addChild(exitMenu);
	auto exit = MenuItemImage::create("Main/WordNote/exit.png", "Main / WordNote / exit.png",CC_CALLBACK_1(WordNote::exit,this));
	exitMenu->addChild(exit);
	exit->setPosition(back->getContentSize().width - 60, back->getContentSize().height - 50);

	selector = Sprite::create("Main/WordNote/selected.png");
	selector->setPosition(-200, -200);
	back->addChild(selector, 1);


	return true;
}

void WordNote::select(Object *pSender)
{
	int tag = ((MenuItemImage*)pSender)->getTag();
	auto note =	wordNVector.at(tag);
	detail->removeAllChildren();
	Sprite *detailSprite = Sprite::create(note->img);
	detailSprite->setPosition(detail->getContentSize().width / 2, 330);
	detailSprite->setScale(1.2);
	detail->addChild(detailSprite);

	auto detailName = LabelTTF::create(note->name, "Fonts/SourceHanSansJP.ttf", 60);
	detailName->setColor(Color3B(255, 0, 0));
	detailName->setPosition(detail->getContentSize().width / 2, 225);
	detail->addChild(detailName);

	auto detailInfo = LabelTTF::create(note->info, "Fonts/SourceHanSansJP.ttf", 24);
	detailInfo->setColor(Color3B(0, 0, 0));
	detailInfo->setPosition(detail->getContentSize().width / 2, 125);
	detail->addChild(detailInfo);

	auto detailMenu = Menu::create();
	detailMenu->setPosition(0, 0);
	detail->addChild(detailMenu);

	auto equipBtn = MenuItemImage::create("Main/WordNote/equipbtn.png", "Main/WordNote/equipbtn.png",CC_CALLBACK_1(WordNote::equip,this));
	equipBtn->setPosition(detail->getContentSize().width / 4 + 10, 55);
	equipBtn->setTag(tag);
	detailMenu->addChild(equipBtn);

	auto enchantBtn = MenuItemImage::create("Main/WordNote/enchantbtn.png", "Main/WordNote/enchantbtn.png", CC_CALLBACK_1(WordNote::enchant, this));
	enchantBtn->setPosition(detail->getContentSize().width / 4 * 3 - 10, 55);
	enchantBtn->setTag(tag);
	detailMenu->addChild(enchantBtn);

}

void WordNote::enchant(Object* pSender)
{
	int tag = ((MenuItemImage*)pSender)->getTag();
	if (money >= 3000 * (wordNVector.at(tag)->enchant + 1))
	{
		wordNVector.at(tag)->enchant += 1;

		char str[3];
		sprintf(str, "+%d", wordNVector.at(tag)->enchant);
		((LabelTTF*)menu->getChildByTag(tag)->getChildByName("label"))->setString(str);
		((LabelTTF*)menu->getChildByTag(tag)->getChildByName("label"))->setVisible(true);

	}

	

	//auto layer = NoteEnchant::create();
	//layer->setPosition(0, 0);
	//this->addChild(layer, 1);

}

void WordNote::equip(Object* pSender)
{
	int tag = ((MenuItemImage*)pSender)->getTag();
	auto note = wordNVector.at(tag);

	for (int i = 0; i < wordNVector.size(); i++)
	{
		if (wordNVector.at(i)->equiped)
		{
			wordNVector.at(i)->equiped = false;
			menu->getChildByTag(i)->removeChildByName("equiped");
		}

	}

	wordNVector.at(tag)->equiped = true;

	auto equipedImg = Sprite::create("Main/WordNote/equip.png");
	equipedImg->setName("equiped");
	equipedImg->setPosition(equipedImg->getContentSize().width/2, equipedImg->getContentSize().height/2);
	auto btn = menu->getChildByTag(tag);
	btn->addChild(equipedImg);
	
}

void WordNote::exit(Object *pSender)
{
	((MainScene*)this->getParent())->unReady();
	removeFromParent();
}

/*
void WordNote::loadNoteData()
{

	auto data = CCUserDefault::sharedUserDefault()->getStringForKey("NoteData");
	auto size = CCUserDefault::sharedUserDefault()->getIntegerForKey("NoteSize");
	wordNVector.clear();

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
		sscanf(getdata, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", &no, &rank, &prize, &type, &time, &level, &soldout, &equiped);
		Goods goods;
		if (equiped == 1)
		{
			goods = { no, rank, prize, type, time, level, true, true };
		}
		else if (soldout == 1)
		{
			goods = { no, rank, prize, type, time, level, true, false };
		}
		else
		{
			goods = { no, rank, prize, type, time, level, false, false };
		}
		goodsVector.push_back(goods);

	}


}

void WordNote::saveNoteData()
{
	std::string str;
	str.clear();
	for (int i = 0; i < goodsVector.size(); i++)
	{

		char apnd[26];
		auto bg = goodsVector.at(i);
		if (bg.equiped)
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t1\t1\t\n", bg.no, bg.rank, bg.prize, bg.type, bg.time, bg.level);
		else if (bg.soldout)
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t1\t0\t\n", bg.no, bg.rank, bg.prize, bg.type, bg.time, bg.level);
		else
			sprintf(apnd, "%.3d\t%.1d\t%.5d\t%.1d\t%.3d\t%.1d\t0\t0\t\n", bg.no, bg.rank, bg.prize, bg.type, bg.time, bg.level);

		str.append(apnd);
	}

	CCUserDefault::sharedUserDefault()->setStringForKey("GoodsData", str);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("GoodsSize", goodsVector.size());
}*/