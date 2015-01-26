#include "ResultScene.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

Scene* ResultScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ResultScene::create();
	scene->addChild(layer);
	return scene;
}

bool ResultScene::init()
{
	if (!Layer::init())
		return false;

	srand(time(NULL));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	auto shutter = Sprite::create("GameUI/shutter.png");
	shutter->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(shutter,5);

	shutter->runAction(MoveBy::create(1, Vec2(0, shutter->getContentSize().height)));

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);

	for (int i = 1; i <= 4; i++)
	{
		auto card = MenuItemImage::create("Finish/Result/cardback.png", "Finish/Result/cardback.png",CC_CALLBACK_1(ResultScene::selectCard,this));
		card->setPosition(visibleSize.width / 5 * i, visibleSize.height / 2);
		menu->addChild(card);

	}
	//resultCard = Sprite::create("Finish/Result/card/result.png");
	resultCard = Sprite::create("Finish/Result/cardback.png");
	resultCard->setPosition(visibleSize / 2);
	this->addChild(resultCard);
	resultCard->setVisible(false);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void ResultScene::selectCard(Object *pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < ((MenuItemImage*)pSender)->getParent()->getChildren().size(); i++)
	{
		if (((MenuItemImage*)pSender)->getParent()->getChildren().at(i) != ((MenuItemImage*)pSender))
		{
			((MenuItemImage*)pSender)->getParent()->getChildren().at(i)->runAction(
				FadeOut::create(0.3)
				);
		}
	}
	((MenuItemImage*)pSender)->runAction(Sequence::create(MoveTo::create(0.7, visibleSize / 2),
		CCCallFunc::create(CC_CALLBACK_0(ResultScene::cardOpen, this, pSender)), NULL));


}
void ResultScene::cardOpen(Object *pSender)
{
	if (start)
		return;
	start = true;
	((MenuItemImage*)pSender)->setVisible(false);
	resultCard->setVisible(true);
	resultCard->setScaleX(-1);
	scheduleUpdate();
}

void ResultScene::update(float dt)
{

	if (resultCard->getScaleX() >= 1)
	{
		end = true;
		return;
	}
	resultCard->setScaleX(resultCard->getScaleX() + 0.05);
	if (resultCard->getScaleX() >= 0 &&!once)
	{
		resultCard->setTexture("Finish/Result/card/result.png");
		int rnd = rand() % 5 + 1;
		int money=CCUserDefault::getInstance()->getIntegerForKey("Money",0);
		CCUserDefault::getInstance()->setIntegerForKey("Money", money + rnd * 500);
		char str[5];
		sprintf(str, "%d", rnd * 500);
		auto lbl = LabelTTF::create(str, "Fonts/SourceHanSansJP.ttf", 48);
		lbl->setColor(Color3B(0, 0, 0));
		lbl->setPosition(resultCard->getContentSize() / 2);
		resultCard->addChild(lbl);
		once = true;
	}


}


bool ResultScene::onTouchBegan(Touch* touch, Event* event)
{
	if (end)
	{
		auto pScene = MainScene::createScene();
		Director::sharedDirector()->replaceScene(pScene);
	}
	return true;
}