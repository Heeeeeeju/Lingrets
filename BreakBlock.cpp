#include "BreakBlock.h"


BreakBlock::BreakBlock()
{
}


BreakBlock::~BreakBlock()
{
}

BreakBlock* BreakBlock::create(int type)
{
	BreakBlock* pRet = new BreakBlock();

	switch (type)
	{
	case 0:
		pRet->blockType = SmallBlock; break;
	case 1:
		pRet->blockType = BigBlock; break;
	default:
		pRet->blockType = SmallBlock; break;
	}

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

bool BreakBlock::init()
{
	switch (blockType)
	{
	case SmallBlock:
		if (!Sprite::initWithFile("Object/Block/smallblock.png"))
			return false;
		break;
	case BigBlock:
		if (!Sprite::initWithFile("Object/Block/bigblock.png"))
			return false;
		break;
	}

	this->setContentSize(Size(this->getContentSize().width*0.7, this->getContentSize().height));
	this->setPositionY(140+this->getContentSize().height/2);

	//auto genAction = MoveBy::create(0.8, Vec2(0, img->getContentSize().height/2));

	//his->runAction(genAction);


	
	return true;
}

void BreakBlock::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}

void BreakBlock::removeFromParentWithEffect()
{
	this->setPosition(this->getPositionX() + this->getParent()->getPositionX(), this->getPositionY());
	auto gScene = this->getParent()->getParent()->getParent();
	this->retain();
	this->getParent()->removeChild(this);
	gScene->addChild(this, 4);
	auto rot = RotateBy::create(1.0, 540);
	auto move = MoveBy::create(1.0, Vec2(1600, 300));
	auto spawn = Spawn::create(rot, move, NULL);
	auto seq = Sequence::create(spawn, CCCallFunc::create(CC_CALLBACK_0(BreakBlock::removeFromParent, this)), NULL);
	this->runAction(seq);

}

Rect BreakBlock::getBoundingBox()
{

	auto anchor = this->getAnchorPoint();
	auto wScaleRatio = 0.4;
	auto hScaleRatio = 1.0;

	auto width = this->getContentSize().width*wScaleRatio;
	auto height = this->getContentSize().height*hScaleRatio;

	Rect boundingBox = Rect(this->getPositionX() - width*anchor.x,
		this->getPositionY() - height*anchor.y,
		width,
		height);


	return boundingBox;
}