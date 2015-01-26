#include "WordImg.h"

WordImg::WordImg()
{
}


WordImg::~WordImg()
{
	
}


WordImg* WordImg::create(const std::string &parts,bool high)
{
	WordImg* pRet = new WordImg();
	pRet->high = high;
	pRet->partString = std::string(parts);
	pRet->partLabel = LabelTTF::create(parts,"Fonts/SourceHanSansKR.ttf",48);
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

bool WordImg::init()
{
	if(!Sprite::initWithFile("Object/puzzle1.png"))
		return false;

	ccBezierConfig bezier;

	if (high)
	{
		bezier.controlPoint_1 = Point(00, 800);
		bezier.controlPoint_2 = Point(00, 600);
		bezier.endPosition = Point(00, 370);
	}
	else
	{
		bezier.controlPoint_1 = Point(00, 500);
		bezier.controlPoint_2 = Point(00, 300);
		bezier.endPosition = Point(00, 220);
	}

	auto genAction = BezierBy::create(0.5, bezier);
	this->runAction(genAction);

	this->addChild(partLabel);
	partLabel->setPosition(this->getContentSize()/2);
	partLabel->setColor(Color3B(0, 0, 0));

	return true;
}

void WordImg::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}

void WordImg::removeFromParentWithEffect()
{
	auto particle = ParticleSun::createWithTotalParticles(300);
	particle->setPosition(this->getPosition());
	particle->setTexture(TextureCache::getInstance()->addImage("Particle/1.png"));
	particle->setSpeed(300);
	particle->setStartColor(Color4F(150, 150, 100, 60));
	particle->setStartColorVar(Color4F(110, 60, 0, 60));
	particle->setEndColor(Color4F(0, 0, 0, 0));
	particle->setEndColorVar(Color4F(100, 60, 0, 1));
	particle->setLife(0.5f);
	particle->setDuration(0.1f);
	particle->setAutoRemoveOnFinish(true);
	this->getParent()->addChild(particle);

	this->removeFromParent();
}