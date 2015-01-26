#include "FloorBlock.h"


FloorBlock::FloorBlock()
{
}


FloorBlock::~FloorBlock()
{
}

bool FloorBlock::init()
{
	if (!Sprite::initWithFile("Background/floorblock.png"))
		return false;

	this->setAnchorPoint(ccp(0, 1));
	this->setPositionY(this->getContentSize().height);

	return true;
}
void FloorBlock::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}