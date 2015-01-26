#include "Target.h"

Target::Target()
{
}

Target::~Target()
{
	
}

Target* Target::create(const std::string &spriteName)
{
	Target* pRet = new Target();

	pRet->spriteName = spriteName;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool Target::init()
{
	char tfilename[64];
	sprintf(tfilename, "Character/%s_1.png", spriteName.c_str());

	if (!Sprite::initWithFile(tfilename))
		return false;

	animation = Animation::create();
	animation->setDelayPerUnit(0.11f);

	for (int i = 1; i <= 2; i++)
	{
		char filename[64];
		sprintf(filename, "Character/%s_%d.png", spriteName.c_str(), i);
		animation->addSpriteFrameWithFile(filename);
	}
	animate = Animate::create(animation);

	auto rep = RepeatForever::create(animate);
	this->runAction(rep);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	this->setPosition(escapePoint, 140 + this->getContentSize().height / 2);

	//scheduleUpdate();

	return true;
}

void Target::update(float dt)
{
	if (this->getPositionX()>300)
		this->setPositionX(this->getPositionX() - (10 - speed));
	
}

void Target::catched()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	char tfilename[64];
	sprintf(tfilename, "Character/%s_b.png", spriteName.c_str());
	auto dead = Sprite::create(tfilename);
	dead->setPosition(this->getPosition());
	this->getParent()->addChild(dead, 3);
	dead->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3, Vec2(rand()%3*200+350, rand()%2*100+500)), ScaleTo::create(0.3, 2.5f),RotateBy::create(0.3,rand()%8*40+540), NULL)
		, DelayTime::create(1.0)
		 ,Spawn::create(MoveBy::create(0.5,Vec2(0,-500)),FadeOut::create(0.5),NULL),
		CCCallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, dead))
		, NULL));

	this->setPosition(escapePoint, 190);

	changeToNext();
}

void Target::changeToNext()
{
	this->stopAllActions();
	targetNum++;
	speed = targetNum+9;
	escapePoint += 500;
	if (targetNum % 5 == 0)
		escapePoint += 500;
	if (this->spriteName == "002")
	{
		this->spriteName = "003";
	}
	else if (this->spriteName == "003")
	{
		this->spriteName = "004";
	}
	else if (this->spriteName == "004")
	{
		this->spriteName = "005";
	}
	else
	{
		this->spriteName = "002";
	}
	init();

	if (speed > 9)
	{
		//escapePoint = (speed - 9) * 10;
		speed = 9;
	}

}