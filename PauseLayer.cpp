#include "PauseLayer.h"


PauseLayer::PauseLayer()
{
}


PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
	if (!Layer::init())
		return false;

	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto backMenu = Menu::create();
	backMenu->setPosition(0, 0);
	this->addChild(backMenu);

	auto black = MenuItemImage::create("Pause/black.png", "Pause/black.png");
	black->setPosition(visibleSize / 2);
	backMenu->addChild(black);

	auto back = Sprite::create("Pause/back.png");
	back->setPosition(visibleSize / 2);
	this->addChild(back);

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	back->addChild(menu);

	auto resume = MenuItemImage::create("Pause/resume.png", "Pause/resume.png", CC_CALLBACK_1(PauseLayer::resume, this));
	resume->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 4 * 3);
	menu->addChild(resume);

	auto retry = MenuItemImage::create("Pause/retry.png", "Pause/retry.png", CC_CALLBACK_1(PauseLayer::retry, this));
	retry->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	menu->addChild(retry);

	auto main = MenuItemImage::create("Pause/main.png", "Pause/main.png", CC_CALLBACK_1(PauseLayer::main, this));
	main->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 4);
	menu->addChild(main);
	
	return true;
}

void PauseLayer::resume(Object *pSender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	((GameScene*)this->getParent())->resume();
	this->removeFromParent();
}

void PauseLayer::retry(Object *pSender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	auto pScene = GameScene::createScene();
	Director::sharedDirector()->replaceScene(pScene);
}

void PauseLayer::main(Object *pSender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	auto pScene = MainScene::createScene();
	Director::sharedDirector()->replaceScene(pScene);
}