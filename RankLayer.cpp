#include "RankLayer.h"


RankLayer::RankLayer()
{
}


RankLayer::~RankLayer()
{
}

bool RankLayer::init()
{
	if (!Layer::init())
		return false;

	auto rankImg = Sprite::create("Main/rank.png");
	this->addChild(rankImg);

	return true;
}