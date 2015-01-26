#include "Coin.h"


Coin::Coin()
{
}


Coin::~Coin()
{
}

Coin* Coin::create(int type)
{
	Coin *pRet = new Coin();
	pRet->type = type;
	if (pRet&&pRet->init())
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

bool Coin::init()
{
	switch (type)
	{
	case SILVER:if (!Sprite::initWithFile("Object/Coin/silver1.png"))return false; break;
	case GOLD:if (!Sprite::initWithFile("Object/Coin/gold1.png"))return false; break;
	case FEVER:if (!Sprite::initWithFile("Object/Coin/fevercoin1.png"))return false; break;
		return false;
		break;
	}

	money = pow(10, type);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.25);

	switch (type)
	{
	case SILVER:
		animation->addSpriteFrameWithFile("Object/Coin/silver1.png");
		animation->addSpriteFrameWithFile("Object/Coin/silver2.png");
		animation->addSpriteFrameWithFile("Object/Coin/silver3.png");
		animation->addSpriteFrameWithFile("Object/Coin/silver4.png");
		break;
	case GOLD:
		animation->addSpriteFrameWithFile("Object/Coin/gold1.png");
		animation->addSpriteFrameWithFile("Object/Coin/gold2.png");
		animation->addSpriteFrameWithFile("Object/Coin/gold3.png");
		animation->addSpriteFrameWithFile("Object/Coin/gold4.png");
		break;
	case FEVER:
		animation->addSpriteFrameWithFile("Object/Coin/fevercoin1.png");
		animation->addSpriteFrameWithFile("Object/Coin/fevercoin2.png");
		animation->addSpriteFrameWithFile("Object/Coin/fevercoin3.png");
		animation->addSpriteFrameWithFile("Object/Coin/fevercoin4.png");
		break;
	}
	

	auto animate = Animate::create(animation);

	auto rep = RepeatForever::create(animate);
	this->runAction(rep);
	return true;
}

void Coin::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}

void Coin::removeFromParentWithEffect()
{
	auto particle = Sprite::create("Particle/img.png");
	particle->setPosition(this->getPosition());
	this->getParent()->addChild(particle);
	particle->setColor(Color3B(35, 35, 255));

	auto action = FadeOut::create(0.7f);
	auto spawn = Spawn::create(action, MoveBy::create(2, Vec2(-120 * speed, 0)), NULL);
	particle->runAction(spawn);

	this->removeFromParent();

}
