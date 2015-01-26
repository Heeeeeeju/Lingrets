#include "Star.h"


Star::Star(int type)
{
	this->type = type;
	
}


Star::~Star()
{
}

Star* Star::create(int type)
{
	Star* pRet = new Star(type);
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

bool Star::init()
{
	switch (CCUserDefault::getInstance()->getIntegerForKey("ScoreLv", 0)%4)
	{
	case 0:
		if (!Sprite::initWithFile("Object/Star/star.png"))
			return false;
		break;
	case 1:
		if (!Sprite::initWithFile("Object/Star/star2.png"))
			return false;
		break;
	case 2:
		if (!Sprite::initWithFile("Object/Star/star3.png"))
			return false;
		break;
	case 3:
		if (!Sprite::initWithFile("Object/Star/star4.png"))
			return false;
		break;
	default:
		if (!Sprite::initWithFile("Object/Star/star4.png"))
			return false;
		break;
	}
	additionalScore = (type + 1) +CCUserDefault::getInstance()->getIntegerForKey("ScoreLv",0)*(2.5)+50;

	this->setContentSize(this->getContentSize()*1.5); 
	this->setScale(1.0f);

	auto genAction = ScaleTo::create(0.4, 1.0f);

	//this->runAction(genAction);


	return true;
}

void Star::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}

void Star::removeFromParentWithEffect()
{
	auto particle = Sprite::create("Particle/img.png");
	particle->setPosition(this->getPosition());
	this->getParent()->addChild(particle);

	auto action = FadeOut::create(0.7f);
	auto spawn = Spawn::create(action, MoveBy::create(2, Vec2(-120 * speed, 0)),NULL);
	particle->runAction(spawn);

	this->removeFromParent();

}
