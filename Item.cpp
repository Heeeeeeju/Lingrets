#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

Item* Item::create(int type)
{
	Item *pRet = new Item();
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

bool Item::init()
{
	switch (type)
	{
	case HP_BIG:if (!Sprite::initWithFile("Object/Item/hp_big.png"))return false; break;
	case HP_SMALL:if (!Sprite::initWithFile("Object/Item/hp_small.png"))return false; break;
	case GIANT:if (!Sprite::initWithFile("Object/Item/giant.png"))return false; break;
	case BOOST:if (!Sprite::initWithFile("Object/Item/boost.png"))return false; break;
	case MAGNET:if (!Sprite::initWithFile("Object/Item/magnet.png"))return false; break;
	case BOOM:if (!Sprite::initWithFile("Object/Item/boom.png"))return false; break;
	default:
		return false;
		break;
	}

	return true;
}

void Item::update(float dt)
{
	this->setPositionX(this->getPositionX() - speed);
}