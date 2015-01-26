#include "GameScene.h"



Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	srand(time(NULL));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	wordImgVector.clear();
	blockVector.clear();
	itemList.clear();
	
	bg4 = Background::create("Background/back4.png");
	bg4->setTag(2);
	this->addChild(bg4);

	bg3 = Background::create("Background/back3.png");
	bg3->setTag(1);
	this->addChild(bg3);

	bg2 = Background::create("Background/back2.png");
	this->addChild(bg2);
	bg2->setTag(2);

	background = Background::create("Background/back.png");
	background->setTag(3);
	this->addChild(background);

	bgForAddC = Background::create("Background/bgaddc.png");
	bgForAddC->setTag(0);
	this->addChild(bgForAddC, 3);
	
	scoreLabel = LabelTTF::create("0","SourceHanSansKR.ttf",24);
	scoreLabel->setColor(Color3B(0, 0, 0));
	scoreLabel->setPosition(visibleSize.width - 100, visibleSize.height - 55);
	scoreLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(scoreLabel, 12);
	moneyLabel = LabelTTF::create("0", "SourceHanSansKR.ttf", 24);
	moneyLabel->setColor(Color3B(0, 0, 0));
	moneyLabel->setPosition(visibleSize.width - 295, visibleSize.height - 55);
	moneyLabel->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(moneyLabel, 12);


	//UI init
	flash = Sprite::create("Background/flash.png");
	flash->setOpacity(0);
	flash->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(flash, 9);
	Sprite *backHpGage = Sprite::create("GameUI/bar2.png");
	backHpGage->setAnchorPoint(Vec2(0, 0.5));
	backHpGage->setPosition(30, visibleSize.height - 100);
	this->addChild(backHpGage, 10);
	hpGage = ProgressTimer::create(Sprite::create("GameUI/bar1.png"));
	hpGage->setType(kCCProgressTimerTypeBar);
	hpGage->setAnchorPoint(Vec2(0, 0.5));
	hpGage->setMidpoint(Vec2(0, 0));
	hpGage->setBarChangeRate(Vec2(1,0));
	hpGage->setPosition(30, visibleSize.height - 100);
	hpGage->setPercentage(100.0f);
	this->addChild(hpGage, 11);
	Sprite *clock = Sprite::create("GameUI/clock.png");
	clock->setPosition(30, visibleSize.height - 100);
	this->addChild(clock, 12);

	board = Sprite::create("GameUI/board.png");
	board->setAnchorPoint(Vec2(0.5, 1));
	board->setPosition(visibleSize.width / 2, visibleSize.height);
	this->addChild(board, 10);

	collectWordHoldNode = Node::create();
	collectWordHoldNode->setPosition(board->getPositionX(), board->getPositionY() - 90);
	this->addChild(collectWordHoldNode, 12);

	auto coinHolder = Sprite::create("GameUI/coinholder.png");
	coinHolder->setPosition(visibleSize.width - 370, visibleSize.height - 50);
	this->addChild(coinHolder, 10);

	auto scoreHolder = Sprite::create("GameUI/scoreholder.png");
	scoreHolder->setPosition(visibleSize.width - 175, visibleSize.height - 50);
	this->addChild(scoreHolder, 10);

	auto targetGage = Sprite::create("GameUI/targetgage.png");
	targetGage->setAnchorPoint(Vec2(0, 0.5));
	targetGage->setPosition(30, visibleSize.height - 160);
	this->addChild(targetGage, 10);

	now = Sprite::create("GameUI/now.png");
	now->setPosition(50, 15);
	targetGage->addChild(now, 11);

	menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu, 11);

	MenuItemImage *pause = MenuItemImage::create("GameUI/pausebtn.png", "GameUI/pausebtn.png", CC_CALLBACK_1(GameScene::pause, this));
	pause->setPosition(visibleSize.width - 30, visibleSize.height - 30);
	menu->addChild(pause);

	//

	floor = Sprite::create("Background/floor.png");
	floor->setPosition(visibleSize.width/2, 400);
//	this->addChild(floor,3);

	wordStorage = new WordStorage();
	for (int i = 0; i < wordStorage->getCount(); ++i)
	{
		if (wordStorage->getWord(i)->getType() == stage)
		{
			staWord.push_back(wordStorage->getWord(i));
		}
	}

	for (int st = 0; st < 10; st++)
	{
		for (unsigned int i = 0; i < staWord.size(); ++i)
		{
			char cat[35];
			for (int j = 1; j <= 2; ++j)
			{
				for (int k = 0; k < staWord.at(i)->getPartsNum(); ++k)
				{
					auto pStr = String::create(staWord.at(i)->getParts(k));
					sprintf(cat, "GameSound/level%d/%s_%d.mp3", st, pStr->getCString(), j);
					CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(cat);
				}
			}
		}
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("GameSound/Eff/pong.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("GameSound/Eff/coin.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("GameSound/Eff/kick.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("GameSound/Bgm/bgm.mp3",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);

	player = Player::create();
	player->setPosition(350, 150);
	pet = Pet::create();
	pet->setPosition(250, 210);
	bgForAddC->addChild(player,4,"player");
	bgForAddC->addChild(pet, 5, "pet");
	target = Target::create("002");
	this->addChild(target, 4);

	for (int i = 0; i < 25; i++)
	{
		if (floorList.size() == 0)
		{
			FloorBlock* block = FloorBlock::create();
			block->setPosition(i*60, 140);
			floorList.push_back(block);
			bgForAddC->addChild(block, 4);
		}
		else
		{
			FloorBlock* block = FloorBlock::create();
			block->setPosition((*--floorList.end())->getPositionX() + 60 , 140);
			floorList.push_back(block);
			bgForAddC->addChild(block, 4);
		}
	}

	//touch
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//
	gsta = Play;

	this->scheduleUpdate();


	return true;
}

void GameScene::update(float dt)
{
	if (gsta != Play)
		return;
	dt = 0.017;
	playTime += dt;
	player->update(dt);
	pet->update(dt);
	if (player->getPositionY() <= -250)
	{
		gameFinish();
	}
	if (player->getBoost())
		target->setSpeed(4.5);
	else
		target->setSpeed(9);
	target->update(dt);
	if (target->getBoundingBox().intersectsRect(player->boundingBox()) )
	{
		target->catched();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameSound/Eff/kick.mp3");
		hpChange(15);
	}

	background->update(dt);
	bg2->update(dt);
	bg3->update(dt);
	bg4->update(dt);
	bgForAddC->update(dt);
	boostUpdate(dt);
	genFloorBlock(dt);

	if (!feverTime&&!bonusTime)
	{
		genObjectCheck(dt);
		starGenerate(dt);
		timerUpdate(dt);
		ItemGenerate(dt);
	}
	else
	{
		bonusUpdate(dt);
	}

	floorCollisionUpdate(dt);
	
	objectUpdate(dt);

	now->setPositionX(50 + (target->getEscapePoint() - target->getPositionX()) * 185 / target->getEscapePoint());

}

void GameScene::floorCollisionUpdate(float dt)
{
	for (auto iter = floorList.begin(); iter != floorList.end();)
	{
		(*iter)->setSpeed(player->getSpeed());
		(*iter)->update(dt);

		if ((*iter)->getPositionX() + (*iter)->getParent()->getPositionX()<-(*iter)->getContentSize().width)
		{
			(*iter)->removeFromParent();
			floorList.erase(iter++);
			continue;
		}

		if ((*iter)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			if (player->getPositionY() + player->getGravity() + 1 > (*iter)->getPositionY())
			{
				player->setPositionY((*iter)->getPositionY() + 1);
				if (player->getGravity()>4)
					player->land();
				else
				{
					player->setGravity(1);
				}
			}
		}

		iter++;
	}

	if (player->getPositionY() <= 141 && (player->getBoost() || player->getInvinsible()))
	{
		player->setPositionY(141);
		if (player->getGravity()>4)
			player->land();
	}
}

void GameScene::objectUpdate(float dt)
{
	for (auto iter = coinList.begin(); iter != coinList.end(); )
	{
		(*iter)->setSpeed(player->getSpeed());
		(*iter)->update(dt);

		if ((*iter)->getPositionX() + (*iter)->getParent()->getPositionX()<-(*iter)->getContentSize().width / 2)
		{
			(*iter)->removeFromParent();
			coinList.erase(iter++);
			continue;
		}

		if ((*iter)->getBoundingBox().intersectsRect(player->getBoundingBox()) && abs((*iter)->getPositionX() - player->getPositionX())<25)
		{
			money += (*iter)->getMoney();
			char moneyString[10];
			sprintf(moneyString, "%d", money);
			moneyLabel->setString(moneyString);
			(*iter)->removeFromParentWithEffect();
			coinList.erase(iter++);
			continue;
		}


		iter++;
	}
	for (auto i = wordImgVector.begin(); i != wordImgVector.end();)
	{
		(*i)->setSpeed(player->getSpeed());
		(*i)->update(dt);
		if ((*i)->getPositionX() + (*i)->getParent()->getPositionX()<-(*i)->getContentSize().width/2)
		{
			collectPuzzle(WordImg::create(" ? ", true));
			(*i)->removeFromParent();
			wordImgVector.erase(i++);
			if (i == wordImgVector.end())
				break;
			continue;
		}
		if ((*i)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{//collect
			collectPuzzle((*i));
			(*i)->removeFromParentWithEffect();
			wordImgVector.erase(i++);
			if (i == wordImgVector.end())
				break;
			continue;
		}
		i++;
	}
	for (auto iter = blockVector.begin(); iter != blockVector.end();)
	{
		(*iter)->setSpeed(player->getSpeed());
		(*iter)->update(dt);
		if ((*iter)->getPositionX() + (*iter)->getParent()->getPositionX()<-(*iter)->getContentSize().width / 2)
		{
			(*iter)->removeFromParent();
			blockVector.erase(iter++);
			continue;
		}
		if (!player->getInvinsible())
		{
			if ((*iter)->getBoundingBox().intersectsRect(player->getBoundingBox()))
			{//collect
				if (player->getCrashable())
				{
					(*iter)->removeFromParentWithEffect();
					blockVector.erase(iter++);
					continue;
				}
				else
				{
					player->blocked();
					hpChange(-12);
				}
			}
		}
		if (pet->getMean())
		{
			if ((*iter)->getBoundingBox().intersectsRect(pet->getKartBoundingBox()))
			{//collect
				(*iter)->removeFromParentWithEffect();
				blockVector.erase(iter++);
				continue;
				
			}

		}

		iter++;
	}

	for (auto iter = starVector.begin(); iter != starVector.end();)
	{
		(*iter)->setSpeed(player->getSpeed());
		auto b = sqrt(((*iter)->getPositionX()*(*iter)->getPositionX()) + (player->getCenter().x*player->getCenter().x));
		if (player->getMagnet() && b<700)
		{
			auto ipos = (*iter)->getPosition();
			auto ppos = player->getCenter();
			
			if (abs(ipos.y - ppos.y) <= 10)
			{
				ipos.y = ppos.y;
			}
			else
			{

				if (ipos.y > ppos.y)
					ipos.y -= 10;
				else
					ipos.y += 10;
			}

			if (abs(ipos.x - ppos.x) <= 25)
			{
				ipos.x = ppos.x;
			}
			else
			{

				if (ipos.x > ppos.x)
					ipos.x -= 25;
				else
					ipos.x += 25;
			}

			(*iter)->setPosition(ipos);
		}
		else
			(*iter)->update(dt);

		if ((*iter)->getPositionX() + (*iter)->getParent()->getPositionX()<-(*iter)->getContentSize().width / 2)
		{
			(*iter)->removeFromParent();
			starVector.erase(iter++);
			continue;
		}

		if ((*iter)->getBoundingBox().intersectsRect(player->getBoundingBox()) && abs((*iter)->getPositionX()  -player->getPositionX())<25 )
		{//collect
			score += (*iter)->getScore();
			char scoreString[10];
			sprintf(scoreString, "%d", score);
			scoreLabel->setString(scoreString);
			(*iter)->removeFromParentWithEffect();
			starVector.erase(iter++);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameSound/Eff/pong.mp3");
			continue;
		}
		

		iter++;
	}

	for (auto iter = itemList.begin(); iter != itemList.end();)
	{
		(*iter)->setSpeed(player->getSpeed());
		auto b = sqrt(((*iter)->getPositionX()*(*iter)->getPositionX()) + (player->getCenter().x*player->getCenter().x));
		if (player->getMagnet() && b<700)
		{
			auto ipos = (*iter)->getPosition();
			auto ppos = player->getCenter();

			if (abs(ipos.y - ppos.y) <= 10)
			{
				ipos.y = ppos.y;
			}
			else
			{

				if (ipos.y > ppos.y)
					ipos.y -= 10;
				else
					ipos.y += 10;
			}

			if (abs(ipos.x - ppos.x) <= 25)
			{
				ipos.x = ppos.x;
			}
			else
			{

				if (ipos.x > ppos.x)
					ipos.x -= 25;
				else
					ipos.x += 25;
			}

			(*iter)->setPosition(ipos);
		}
		else
			(*iter)->update(dt);

		if ((*iter)->getPositionX() < -(*iter)->getContentSize().width / 2)
		{
			(*iter)->removeFromParent();
			itemList.erase(iter++);
			continue;
		}
		if ((*iter)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			itemGet((*iter)->getType());
			(*iter)->removeFromParent();
			itemList.erase(iter++);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameSound/Eff/pong.mp3");
			continue;
		}
		iter++;
	}
}

void GameScene::timerUpdate(float dt)
{
	hpChange(-0.017);
	hpGage->setPercentage((float)((float)hpTime / (float)maxHp)*100);
}

void GameScene::genPuzzle(const std::string parts,bool high)
{
	auto worditem = WordImg::create(parts,high);
	wordImgVector.push_back(worditem);

	bgForAddC->addChild(worditem, 3);	

	worditem->setPosition(1400-worditem->getParent()->getPositionX(), 150);
}

void GameScene::genBlockObject(int type)
{
	auto blockObj = BreakBlock::create(type);
	blockVector.push_back(blockObj);

	bgForAddC->addChild(blockObj, 2);
	

	blockObj->setPositionX(1400 - blockObj->getParent()->getPositionX());
}

void GameScene::boostUpdate(float dt)
{
	if (!boosted)
		return;
	if (boostGage <= 0)
	{
		resetB();
	}
	boostGage -= dt;
	
}

void GameScene::bonusUpdate(float dt)
{
	bonusGenDelay -= dt;
	bonusTimeGage -= dt;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	if (!player->getBoost())
		player->boost();
	if (bonusTimeGage <= 0)
		bonusEnd(dt);
	if (bonusGenDelay <= 0)
	{
		bonusGenDelay = 1;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (j <= 4)
				{
					if (i < 5)
					{
						if (j + i >= 4)
						{
							auto star = Coin::create(1);

							
							coinList.push_back(star);
							bgForAddC->addChild(star, 2);
							star->setPosition((9-j) * 50 +1400 -star->getParent()->getPositionX(), (9-i) * 50+100);
						}
					}
					else
					{
						if (i-j <= 4)
						{
							auto star = Coin::create(1);

							coinList.push_back(star);
							bgForAddC->addChild(star, 2);
							star->setPosition((9-j) * 50 +1400 -star->getParent()->getPositionX(), (9-i) * 50+100);
						}
					}
					
				}
				//우
				else
				{
					if (i < 5)
					{
						if (j - i <= 4)
						{
							auto star = Coin::create(1);

							coinList.push_back(star);
							bgForAddC->addChild(star, 2);
							star->setPosition((9-j) * 50 +1400 -star->getParent()->getPositionX(), (9-i) * 50+100);
						}
					}
					else
					{
						if (i + j <= 12)
						{
							auto star = Coin::create(1);

							coinList.push_back(star);
							bgForAddC->addChild(star, 2);
							star->setPosition((9-j) * 50 +1400 -star->getParent()->getPositionX(), (9-i) * 50+100);
						}
					}
				}
				

			}
		}

	}
	

}

void GameScene::blocked()
{
	player->blocked();
}

void GameScene::boost()
{//2,6,8,10
	player->boost();
	boosted = true;
}

void GameScene::resetB()
{
	player->reset(1);
	boostGage = 2;
	boosted = false;
}

void GameScene::collectPuzzle(WordImg *puzzle)
{
	collectedWord.append(puzzle->getPartString());
	Sprite *collectedParts;
	if (puzzle->getHigh())
	{
		collectedParts = Sprite::create("WordBlock/block2.png");

		char cat[30];
		sprintf(cat, "GameSound/level%d/%s_%d.mp3", stage, puzzle->getPartString().c_str(), 2);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(cat);
	}
	else
	{
		collectedParts = Sprite::create("WordBlock/block1.png");

		char cat[30];
		sprintf(cat, "GameSound/level%d/%s_%d.mp3", stage, puzzle->getPartString().c_str(), 1);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(cat);
	}

	collectedParts->setPosition(player->getPosition());
	auto label = LabelTTF::create(puzzle->getPartString().c_str(), "Fonts/SourceHanSansKR.ttf", 48);
	label->setPosition(collectedParts->getContentSize().width / 2, collectedParts->getContentSize().height / 2);
	label->setColor(Color3B(0, 0, 0));
	collectedParts->addChild(label);
	this->addChild(collectedParts,12);
	collectedParts->setScale(0.0f);

	auto boardOriginX = board->getPositionX() - ((float)(collectWord->getPartsNum()+1)*collectedParts->getContentSize().width)/2;
	auto boardOriginY = board->getPositionY() - 90;
		
	auto moveAction = MoveTo::create(0.3, Vec2(boardOriginX +  collectCounter * collectedParts->getContentSize().width + collectedParts->getContentSize().width / 2, boardOriginY));
	auto scaleAction = EaseIn::create(ScaleTo::create(0.3, 1.0f),5.0f);
	auto rotateAction = RotateBy::create(0.3, 360 * 2);
	collectCounter++;
	if (collectCounter >= collectWord->getPartsNum() + 1)
	{
		auto firstAction = Spawn::create(moveAction, scaleAction, rotateAction, NULL);
		auto action = Sequence::create(firstAction,DelayTime::create(1.0f), CCCallFunc::create(CC_CALLBACK_0(GameScene::addToHoldNodeAction, this, collectedParts)),
			CCCallFunc::create(CC_CALLBACK_0(GameScene::deleteNodeAction, this)), NULL);
		collectedParts->runAction(action);
		collectCounter = 0;
	}
	else
	{
		auto spawnAction = Spawn::create(moveAction, scaleAction, rotateAction, NULL);
		auto action = Sequence::create(spawnAction, CCCallFunc::create(CC_CALLBACK_0(GameScene::addToHoldNodeAction, this, collectedParts)),NULL);

		collectedParts->runAction(action);

	}
}

void GameScene::addToHoldNodeAction(Sprite* img)
{
	img->retain();
	this->removeChild(img);
	collectWordHoldNode->addChild(img);
	img->setPosition(img->getPositionX() - collectWordHoldNode->getPositionX(), 0);
}

void GameScene::deleteNodeAction()
{
	auto scaleAction = ScaleTo::create(0.3, 0.0f);
	auto action = Sequence::create(scaleAction,CCCallFunc::create(CC_CALLBACK_0(GameScene::nodeInit,this)),NULL);
	collectWordHoldNode->runAction(action);

}

void GameScene::nodeInit()
{
	collectWordHoldNode->removeFromParent();
	collectWordHoldNode = Node::create();
	collectWordHoldNode->setPosition(board->getPositionX(), board->getPositionY() - 90);
	this->addChild(collectWordHoldNode, 12);


	if (collectedWord.c_str() != collectWord->getEng())
	{
		staWord.push_back(collectWord);
		return;
	}
	pet->showMean(collectWord->getKor());

	auto puzzleDeck = Sprite::create("GameUI/puzzle.png");
	puzzleDeck->setPosition(55+60*collectedDeck.size(),800- 45);

	auto label = LabelTTF::create(collectedWord.c_str(), "Fonts/SourceHanSansKR.ttf", 96 / collectWord->getEng().length());
	label->setPosition(puzzleDeck->getContentSize().width / 2, puzzleDeck->getContentSize().height / 2);
	label->setColor(Color3B(0, 0, 0));
	puzzleDeck->addChild(label);
	this->addChild(puzzleDeck,12);

	collectedDeck.push_back(puzzleDeck);


	if (staWord.size() <= 0)
	{//피버 스타트 조건
		bonusStart();

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		auto particle = ParticleRain::createWithTotalParticles(400);
		particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("Particle/18.png"));
		particle->setPosition(visibleSize.width+200, visibleSize.height/ 2);
		particle->setRotation(90);
		particle->setStartSize(100);
		particle->setStartColor(Color4F(255, 255, 0, 255));
		particle->setEndColor(Color4F(255, 255, 100, 255));
		particle->setSpeed(1500);
		particle->setDuration(CCUserDefault::getInstance()->getIntegerForKey("BonusLv", 0)*0.3 + 3);
		particle->setLife(1.5);
		bgForAddC->addChild(particle);
	}
}


void GameScene::bonusStart()
{
	bonusTime = true;
	flash->setOpacity(255 * 0.5);
	flash->runAction(Sequence::create(FadeTo::create(0.5f,255), FadeOut::create(0.5f),NULL));
	player->boost();
	
	for (int i = 0; i < wordStorage->getCount(); ++i)
	{
		if (wordStorage->getWord(i)->getType() == stage)
		{
			staWord.push_back(wordStorage->getWord(i));
		}
	}
	for (auto iter = starVector.begin(); iter != starVector.end(); iter++)
	{
		(*iter)->removeFromParent();
	}
	starVector.clear();

	for (auto bter = blockVector.begin(); bter != blockVector.end(); bter++)
	{
		(*bter)->removeFromParent();
	}
	blockVector.clear();

	bonusGenDelay += 1;

	background->bonus("Background/Bonus/back.png");
	bg2->bonus("Background/Bonus/back2.png");
	bg3->bonus("Background/Bonus/back3.png");
	bg4->bonus("Background/Bonus/back4.png");
}

void GameScene::bonusEnd(float dt)
{
	flash->setOpacity(255 * 0.5);
	flash->runAction(Sequence::create(FadeTo::create(0.5f, 255), FadeOut::create(0.5f), NULL));

	for (auto iter = collectedDeck.begin(); iter != collectedDeck.end(); iter++)
	{
		(*iter)->removeFromParent();
	}
	collectedDeck.clear();

	bonusTime = false;

	background->bonus("Background/back.png");
	bg2->bonus("Background/back2.png");
	bg3->bonus("Background/back3.png");
	bg4->bonus("Background/back4.png");

	bonusTimeGage = CCUserDefault::getInstance()->getIntegerForKey("BonusLv", 0)*0.3+3;
	objectGenDelay = 3;
	genDelay = 4;
	starCoinDelay = 2;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	stage++;

	staWord.clear();

	for (int i = 0; i < wordStorage->getCount(); ++i)
	{
		if (wordStorage->getWord(i)->getType() == stage)
		{
			staWord.push_back(wordStorage->getWord(i));
		}
	}
}
//

void GameScene::genObjectCheck(float dt)
{
	if (feverTime)
		return;

	genDelay -= dt;
	objectGenDelay -= dt;

	if (genDelay <= 0 && !boosted)
	{
		genDelay = GENTIME;
		if (targetWord == nullptr && staWord.size() > 0)
		{
			targetWord = staWord.at(rand() % staWord.size());
			collectWord = targetWord;
			collectCounter = 0;
			collectedWord.clear();
			genDelay = GENTIME;
			//deleteNodeAction();
		}
		else if (targetWord!=nullptr)
		{
			if (targetWord->getPartsEmphasis(genCounter) == 2)
			{
				genPuzzle(targetWord->getParts(genCounter), true);
				objectGenDelay = BLOCKOBJECT_GENTIME;
				genBlockObject(1);
			}
			else
			{
				genPuzzle(targetWord->getParts(genCounter), false);
				objectGenDelay = BLOCKOBJECT_GENTIME;
				genBlockObject(0);
			}

			if (genCounter >= targetWord->getPartsNum())
			{
				for (auto iter = staWord.begin(); iter != staWord.end(); iter++)
				{
					if ((*iter) == targetWord)
					{
						staWord.erase(iter);
						break;
					}
				}
				targetWord = nullptr;
				genCounter = 0;
				genDelay = GENTIME * 15;
			}
			else
				genCounter++;
		}
		
	}
	else if (objectGenDelay <= 0)
	{
		int rnd=rand()%2;
		objectGenDelay = BLOCKOBJECT_GENTIME*(rand() % (rnd + 2) + 1);
		floorTerm += 60 * (rand() % (rnd + 2) + 1);
		genBlockObject(rnd);
	}
	

}

void GameScene::starGenerate(float dt)
{
	if (feverTime)
		return;

	if (boosted)
	{
		starCoinDelay -= dt;
	}
	starCoinDelay -= dt;
	if (starCoinDelay <= 0)
	{
		auto star = Star::create((int)(playTime / 20));
		starVector.push_back(star);
		bgForAddC->addChild(star, 2);

		star->setPosition(1450 - star->getParent()->getPositionX(), 200);



		for (auto bter = blockVector.begin(); bter != blockVector.end(); bter++)
		{
			if (star->getBoundingBox().intersectsRect(Rect((*bter)->getBoundingBox().getMinX(), (*bter)->getBoundingBox().getMinY(), (*bter)->getBoundingBox().size.width * 100 / 65, (*bter)->getBoundingBox().size.height)))
			{//
				star->setPositionY((*bter)->getPositionY() + (*bter)->getContentSize().height / 2 + 100);
			}
		}

		if (boosted)
		{
			auto star2 = Star::create((int)(playTime / 20));
			starVector.push_back(star2);
			bgForAddC->addChild(star2, 2);

			star2->setPosition(1400 - star2->getParent()->getPositionX(), 300);
			for (auto bter = blockVector.begin(); bter != blockVector.end(); bter++)
			{
				if (star2->getBoundingBox().intersectsRect(Rect((*bter)->getBoundingBox().getMinX(), (*bter)->getBoundingBox().getMinY(), (*bter)->getBoundingBox().size.width * 100 / 65, (*bter)->getBoundingBox().size.height)))
				{//
					star2->setPositionY((*bter)->getPositionY() + (*bter)->getContentSize().height / 2 + 100);
				}
			}
		}
		starCoinDelay = STAR_COIN_GENTIME;
		
	}
}

void GameScene::ItemGenerate(float dt)
{
	ItemGenDelay -= dt;
	if (feverTime)
		return;

	if (ItemGenDelay <= 0)
	{
		ItemGenDelay = ITEM_GEN_TIME;

		auto item = Item::create(rand() % 5);
		item->setPosition(1450, 300);
		bgForAddC->addChild(item,4);

		itemList.push_back(item);
	}
	

}

void GameScene::genFloorBlock(float dt)
{
	if (floorList.size() == 0)
	{
		FloorBlock* block = FloorBlock::create();
		block->setPosition(1450,140);
		floorList.push_back(block);
		bgForAddC->addChild(block, 4);
	}
	else
	{
		if (60+floorTerm + (*--floorList.end())->getPositionX() < 1450)
		{

			if (!feverTime)
			{
				FloorBlock* block = FloorBlock::create();
				block->setPosition((*--floorList.end())->getPositionX()+60+floorTerm, 140);
				floorList.push_back(block);
				bgForAddC->addChild(block, 4);
				floorTerm = 0;
			}
		}
		else if (feverTime&&60 + (*--floorList.end())->getPositionX() < 1450)
		{
			FloorBlock* block = FloorBlock::create();
			block->setPosition((*--floorList.end())->getPositionX() + 60 + floorTerm, 140);
			floorList.push_back(block);
			bgForAddC->addChild(block, 4);
			floorTerm = 0;
		}

	}
}

void GameScene::hpChange(float index)
{
	hpTime += index;
	if (hpTime > maxHp)
		hpTime = maxHp;
	if (hpTime <= 0)
	{
		gameFinish();		
	}
}

void GameScene::gameFinish()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	hpGage->setPercentage(0);
	gsta = End;
	player->dead();
	player->setOpacity(255);
	ccBezierConfig bezier;

	bezier.controlPoint_1 = Point(00, 1500);
	bezier.controlPoint_2 = Point(00, 800);
	bezier.endPosition = Point(00, -500);


	auto genAction = BezierBy::create(1, bezier);
	player->runAction(genAction);
	//target->runAction(MoveBy::create(0.4, Vec2(400, 0)));

	Sprite* shutter = Sprite::create("GameUI/shutter.png");
	shutter->setAnchorPoint(Vec2(0.5, 0));
	shutter->setPosition(visibleSize.width / 2, visibleSize.height);
	shutter->runAction( Sequence::create(DelayTime::create(1) , MoveBy::create(0.2, Vec2(0, -800)) ,NULL) );
	this->addChild(shutter, 30);

	auto bMoney = CCUserDefault::getInstance()->getIntegerForKey("Money",0);
	CCUserDefault::getInstance()->setIntegerForKey("Money", bMoney+money);

	auto fMenu = Menu::create();
	shutter->addChild(fMenu);
	fMenu->setPosition(0, 0);

	auto end = MenuItemImage::create("GameUI/alert.png", "GameUI/alert.png", CC_CALLBACK_1(GameScene::goToMain,this));
	end->setPosition(visibleSize.width / 2, 150);
	fMenu->addChild(end);


}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (gsta == Play)
	{
		player->jumpFunc();
	}
	return true;
}

std::string GameScene::confuseWord(std::string str)
{
	bool swaped = false;
	while (swaped == false)
		for (int i = 0; str[i] != '\0'; ++i)
		{
		if (rand() % 2 == 1)
		{
			switch (str[i])
			{
			case 'k':
				if (str[i + 1] == 'n' && i == 0)//kn->n
				{
					str[i] = 'n';
					for (int j = i + 1; str[j] != '\0'; ++j)
					{
						str[j] = str[j + 1];
					}
					swaped = true;
				}
				else if (str[i + 1] == '\0' && str[i - 1] != 'c')//끝에 k->ck
				{
					str[i] = 'c';
					str[i + 1] = 'k';
					str[i + 2] = NULL;
					i++;
					swaped = true;
				}
				else if (i != 0)
				{
					if (str[i - 1] != 'c')
					{
						str[i] = 'c';
						swaped = true;
					}
				}
				break;
			case 'c':
				if (str[i + 1] == 'k')//ck->k
				{
					str[i] = 'k';
					str[i + 1] = NULL;
					swaped = true;
				}
				break;
			case 'a': str[i] = 'e'; swaped = true; break;
			case 'e': str[i] = 'a'; swaped = true; break;
			case 'i': str[i] = 'y'; swaped = true; break;
			case 'o':
				if (str[i + 1] == 'u')//ou->o
				{
					str[i] = 'o';
					for (int j = i + 1; str[j] != '\0'; ++j)
					{
						str[j] = str[j + 1];
					}
					swaped = true;
				}
				else if (str[i + 1] == 'o')//oo->u
				{
					str[i] = 'u';
					for (int j = i + 1; str[j] != '\0'; ++j)
					{
						str[j] = str[j + 1];
					}
					swaped = true;
				}
				else
				{
					str[i] = 'a'; swaped = true;
				}
				break;
			case 'u': str[i] = 'o'; swaped = true; break;
			case 'f':
				if (isVowel(str[i + 1]))
					str[i] = 'p';
				else
				{
					str[i] = 'h';
					char tmp = str[i + 1];
					char tmp2;
					str.resize(str.size() + 1);
					for (int j = i + 1; str[j] != '\0'; ++j)
					{
						tmp2 = str[j + 1];
						str[j + 1] = tmp;
						tmp = tmp2;
					}
					str[i + 1] = 'u';
				}
				swaped = true; break;
			case 'p': str[i] = 'f'; swaped = true; break;
				//case 'k': str[i] = 'c'; swaped = true; break;
			case 'g': str[i] = 'k'; swaped = true; break;
			case 'r': str[i] = 'l'; swaped = true; break;
			case 'l': str[i] = 'r'; swaped = true; break;
			case 'y': str[i] = 'i'; swaped = true; break;
			case 'm':
				if (str[i + 1] == '\0')
				{
					str[i] = 'n';
					swaped = true;
				}
				break;
			case 'n':
				if (str[i + 1] == '\0')
				{
					str[i] = 'm';
					swaped = true;
				}
				break;
			default:
				break;
			}
		}
		if (swaped)
			break;
		}

	int i = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
	}
	str.resize(i);

	return str;
}

void GameScene::itemGet(int type)
{
	switch (type)
	{
	case 0:
		hpTime += 10;
		if (hpTime >= maxHp)
			hpTime = maxHp;
		hpGage->setPercentage((float)((float)hpTime / (float)maxHp) * 100);		
		break;
	case 1:
		hpTime += 3;
		if (hpTime >= maxHp)
			hpTime = maxHp;
		hpGage->setPercentage((float)((float)hpTime / (float)maxHp) * 100);
		break;
	case 2:
		player->giant();
		break;
	case 3:
		player->boost();
		break;
	case 4:
		player->magnet();
		break;
	case 5:
		break;
	}
}

void GameScene::viberate()
{
	auto action = Sequence::create(
		//Repeat::create(MoveTo::create(0.1, Vec2((rand() % 3 - 1) * 15, (rand() % 3 - 1) * 15)), 10),
		MoveTo::create(1,Vec2(10,10)),
		Place::create(Vec2(0, 0)),
		NULL);

	//bg4->runAction(MoveTo::create(1,Vec2(10,10)));
	//bg3->runAction(action);
	//bg2->runAction(action);
	//background->runAction(action);
	//bgForAddC->runAction(action);
}

void GameScene::pause(Object *pSender)
{
	gsta = Pause;


	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto layer = PauseLayer::create();
	layer->setPosition(0, 0);
	this->addChild(layer, 30);
}

void GameScene::resume()
{
	gsta = Play;
}

void GameScene::goToMain(Object *pSender)
{
	auto GC = CCUserDefault::getInstance()->getIntegerForKey("GiantCnt", 0);
	auto BC = CCUserDefault::getInstance()->getIntegerForKey("BoostCnt", 0);
	auto MC = CCUserDefault::getInstance()->getIntegerForKey("MagnetCnt", 0);
	if (MC > 0)
		MC--;
	if (BC > 0)
		BC--;
	if (GC > 0)
		GC--;

	CCUserDefault::getInstance()->setIntegerForKey("GiantCnt", GC);
	CCUserDefault::getInstance()->setIntegerForKey("BoostCnt", BC);
	CCUserDefault::getInstance()->setIntegerForKey("MagnetCnt", MC);


	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	auto pScene = ResultScene::createScene();
	Director::sharedDirector()->replaceScene(pScene);
}