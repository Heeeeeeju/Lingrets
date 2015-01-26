#include "MainScene.h"


MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CCUserDefault::getInstance()->setIntegerForKey("HPLv",0);
	CCUserDefault::getInstance()->setIntegerForKey("ScoreLv", 0);
	CCUserDefault::getInstance()->setIntegerForKey("BonusLv", 0);
	CCUserDefault::getInstance()->setIntegerForKey("Money", 1000000);
	money = 1000000;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto term = (visibleSize.width - 1080) / 5;
	auto endpos = 0.0f;

	auto back = Sprite::create("Main/back.png");
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(back);

	auto level = Sprite::create("Main/level.png");
	level->setAnchorPoint(Point(0, 0.5));
	level->setPosition(term, visibleSize.height - 50);
	this->addChild(level,2);
	endpos += term + level->getContentSize().width;

	auto fish = Sprite::create("Main/fish.png");
	fish->setAnchorPoint(Point(0, 0.5f));
	fish->setPosition(term + endpos, visibleSize.height - 50);
	this->addChild(fish, 2);
	endpos += term + fish->getContentSize().width;

	auto moneyHolder = Sprite::create("Main/money.png");
	moneyHolder->setAnchorPoint(Point(0, 0.5f));
	moneyHolder->setPosition(term + endpos, visibleSize.height - 50);
	this->addChild(moneyHolder, 2);
	endpos += term + moneyHolder->getContentSize().width;

	char moneystr[10];
	sprintf(moneystr, "%d", money);
	moneyLabel = LabelTTF::create(moneystr, "Fonts/SourceHanSansKR.ttf", 36);
	moneyLabel->setPosition(endpos - 70, visibleSize.height - 50);
	moneyLabel->setAnchorPoint(Vec2(1, 0.5));
	moneyLabel->setColor(Color3B(0, 0, 0));
	this->addChild(moneyLabel, 2);
	
	auto life = Sprite::create("Main/life.png");
	life->setAnchorPoint(Point(0, 0.5));
	life->setPosition(term + endpos, visibleSize.height - 50);
	this->addChild(life, 2);


	menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu,1);

	auto termB = (visibleSize.width - 1078) / 4;
	auto endposB = 0.0f;
	
	auto settingBtn = MenuItemImage::create("Main/setting.png", "Main/setting.png");
	settingBtn->setAnchorPoint(Point(0, 0.5f));
	settingBtn->setPosition(termB, 75);
	menu->addChild(settingBtn);
	endposB += termB + settingBtn->getContentSize().width;
	
	auto friendBtn = MenuItemImage::create("Main/friend.png", "Main/friend.png");
	friendBtn->setAnchorPoint(Point(0, 0.5f));
	friendBtn->setPosition(endposB, 75);
	menu->addChild(friendBtn);
	endposB += friendBtn->getContentSize().width;

	auto messageBtn = MenuItemImage::create("Main/message.png", "Main/message.png");
	messageBtn->setAnchorPoint(Point(0, 0.5f));
	messageBtn->setPosition(endposB, 75);
	menu->addChild(messageBtn);
	endposB += messageBtn->getContentSize().width;

	auto wordBtn = MenuItemImage::create("Main/word.png", "Main/word.png", CC_CALLBACK_1(MainScene::wordNote, this));
	wordBtn->setAnchorPoint(Point(0, 0.5f));
	wordBtn->setPosition(endposB, 75);
	menu->addChild(wordBtn);
	endposB += wordBtn->getContentSize().width;

	auto startBtn = MenuItemImage::create("Main/start.png", "Main/start.png",CC_CALLBACK_1(MainScene::ReadyShop,this));
	startBtn->setAnchorPoint(Point(0, 0.5f));
	startBtn->setPosition(termB + termB + endposB, 75);
	menu->addChild(startBtn);

	auto stageBtn = MenuItemImage::create("Main/stage.png", "Main/stage.png");
	stageBtn->setAnchorPoint(Point(0, 0.5f));
	stageBtn->setPosition(termB + termB + endposB, 605);
	menu->addChild(stageBtn);

	auto charShopBtn = MenuItemImage::create("Main/charshop.png", "Main/charshop.png", CC_CALLBACK_1(MainScene::charShop, this));
	charShopBtn->setAnchorPoint(Point(0, 0.5f));
	charShopBtn->setPosition(termB *2.7 + endposB, 360);
	menu->addChild(charShopBtn);



	gameStart = MenuItemImage::create("Main/ReadyShop/start.png", "Main/ReadyShop/start.png", CC_CALLBACK_1(MainScene::startGame, this));
	gameStart->setPosition(startBtn->getPosition().x, startBtn->getPosition().y + 70);
	gameStart->setAnchorPoint(Vec2(0, 0.5));
	menu->addChild(gameStart,2);
	gameStart->setVisible(false);

	//
	changeAbleLayer = Layer::create();
	rankLayer= RankLayer::create();
	changeAbleLayer->setPosition(400, visibleSize.height / 2);
	this->addChild(changeAbleLayer);
	changeAbleLayer->addChild(rankLayer);


	return true;
}

void MainScene::startGame(Object *pSender)
{
	auto pScene = LoadingScene::createScene();
	Director::sharedDirector()->replaceScene(pScene);
}

void MainScene::charShop(Object *pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	menu->setZOrder(0);

	CharShop *layer = CharShop::create();
	layer->setPosition(0,0);
	this->addChild(layer, 1);
}

void MainScene::ReadyShop(Object *pSender)
{
	auto menuChild = menu->getChildren();
	for (auto iter = menuChild.begin(); iter != menuChild.end(); iter++)
	{
			(*iter)->setVisible(false);
	}

	changeAbleLayer->setVisible(false);

	gameStart->setVisible(true);

	menu->setZOrder(2);


	auto layer = ReadyShop::create();
	layer->setPosition(0, 0);
	this->addChild(layer, 1);

}

void MainScene::unReady()
{
	auto menuChild = menu->getChildren();
	for (auto iter = menuChild.begin(); iter != menuChild.end(); iter++)
	{
		(*iter)->setVisible(true);
	}
	gameStart->setVisible(false);

	menu->setZOrder(1);

	changeAbleLayer->setVisible(true);
}

void MainScene::wordNote(Object *pSender)
{
	auto menuChild = menu->getChildren();
	for (auto iter = menuChild.begin(); iter != menuChild.end(); iter++)
	{
		(*iter)->setVisible(false);
	}

	changeAbleLayer->setVisible(false);

	auto layer = WordNote::create();
	layer->setPosition(0, 0);
	this->addChild(layer, 1);
}

void MainScene::setMoney(int money)
{
	this->money = money;
	char str[10];
	sprintf(str, "%d", money);
	moneyLabel->setString(str);
}