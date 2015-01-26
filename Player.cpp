#pragma once
#include "Player.h"
#include "GameScene.h"



bool Player::init()
{
	if (!Sprite::initWithFile("Character/player.png"))
		return false;

	//auto apearAction = MoveBy::create(3,Vec2(300,0));
	//this->runAction(apearAction);

	sprintf(spriteName, "%.3d", CCUserDefault::getInstance()->getIntegerForKey("EquipedChar",1));

	cloud = Sprite::create("Character/cloud.png");
	cloud->setPosition(this->getPositionX() - this->getContentSize().width / 2, this->getPositionY() - this->getContentSize().height / 2);
	cloud->setOpacity(0);

	boostImg = Sprite::create("Character/fire1.png");

	boostAnimation = Animation::create();
	boostAnimation->setDelayPerUnit(delayPerUnit);

	boostAnimation->addSpriteFrameWithFile("Character/fire1.png");
	boostAnimation->addSpriteFrameWithFile("Character/fire2.png");

	boostAnimate = Animate::create(boostAnimation);

	auto rep = RepeatForever::create(boostAnimate);
	boostImg->runAction(rep);
	boostImg->setPosition(-60, this->getContentSize().height / 2);
	boostImg->setVisible(false);
	this->addChild(boostImg, -1);

	//scheduleUpdate();
	this->setAnchorPoint(ccp(0.5, 0));

	return true;
}

void Player::update(float dt)
{
	//	Item
	if (invinsible)
	{
		blinkTimer--;
		if (blinkTimer <= 0)
		{
			blinkTimer = 10;
			if (getOpacity() == 255)
				this->setOpacity(255 * 0.6);
			else
				this->setOpacity(255);
		}

	}
	else
		this->setOpacity(255);

	if (gianted && this->getScale() < 3.0f)
	{
		this->setScale(this->getScale() + dt * 6);
		if (this->getScale() > 3.0f)
			this->setScale(3.0f);
	}
	else if (!gianted && this->getScale() > 1.0f)
	{
		this->setScale(this->getScale() - dt * 6);
		if (this->getScale() < 1.0f)
			this->setScale(1.0f);
	}

	//
	gravity += G;
	if (gravity > 4)
		jump = true;
	this->setPositionY(this->getPositionY() - gravity);


	itemUpdate(dt);



}

void Player::itemUpdate(float dt)
{
	if (block)
	{
		blockTime -= dt;
		if (blockTime <= 0)
		{
			invinsibleFunc(0);
		}
	}
	if (gianted)
	{
		giantTime -= dt;
		if (giantTime <= 0)
		{
			invinsibleFunc(2);
			if (boosted)
			{
				invinsible = false;
			}
		}
	}
	if (boosted)
	{
		boostTime -= dt;
		
		if (boostTime <= 0)
		{
			invinsibleFunc(1);
			if (gianted)
			{
				invinsible = false;
			}
		}
	}
	if (magneting)
	{
		magnetTime -= dt;
		if (magnetTime <= 0)
		{
			magneting = false;
		}
	}


}

void Player::jumpFunc()
{
	if (secJump == false)
	{
		gravity = JUMPPOWER;
		if (jump)
		{
			secJump = true;
			jumpRotation = true;
			this->stopAllActions();
			char filename[64];
			sprintf(filename, "Character/%s_j2.png", spriteName);
			this->setTexture(filename);

			//			cloud->setPosition(this->getPositionX() - this->getContentSize().width / 2, this->getPositionY() - this->getContentSize().height / 2);
			//			cloud->setOpacity(255);
			//			cloud->runAction(Spawn::create(FadeOut::create(0.7), MoveBy::create(0.7, Vec2(-70, 0)), NULL));
		}
		else
		{
			auto pos = this->getPosition();
			this->stopAllActions();
			char filename[64];
			sprintf(filename, "Character/%s_j.png", spriteName);
			this->setTexture(filename);
		}
		jump = true;
	}

	if (block)
	{
		char filename[64];
		sprintf(filename, "Character/%s_b.png", spriteName);
		this->setTexture(filename);
	}
}

void Player::blocked()
{
	if (boosted || gianted || crashable)
		return;

	this->stopAllActions();
	char filename[64];
	sprintf(filename, "Character/%s_b.png", spriteName);
	this->setTexture(filename);
	block = true;
	blockTime = 0.3;
	invinsible = true;
	((GameScene*)this->getParent())->viberate();

}

void Player::reset(int type)
{

	if (!boosted && !gianted)
	{
		crashable = false;
		invinsible = false;
	}

	this->setVisible(true);
	this->setOpacity(255);
	playAnimation();

}

void Player::boost()
{
	boosted = true;
	block = false;
	invinsible = false;
	crashable = true;
	this->speed = SPEED * 2;
	delayPerUnit = DELAY_PER_UNIT / 2;
	if (CCUserDefault::getInstance()->getIntegerForKey("BoostCnt", 0) > 0)
		boostTime = 5;
	else
		boostTime = 3;
	boostImg->setVisible(true);
	playAnimation();

}

void Player::giant()
{
	crashable = true;
	block = false;
	invinsible = false;
	if (CCUserDefault::getInstance()->getIntegerForKey("GiantCnt", 0) > 0)
		giantTime = 5;
	else
		giantTime = 3;
	gianted = true;
	playAnimation();

}

void Player::magnet()
{
	magneting = true;
	if (CCUserDefault::getInstance()->getIntegerForKey("MagnetCnt", 0) > 0)
		magnetTime = 5;
	else
		magnetTime = 3;
}

void Player::playAnimation()
{
	if (block)
	{
		this->stopAllActions();
		char filename[64];
		sprintf(filename, "Character/%s_b.png", spriteName);
		this->setTexture(filename);
	}

	if (boosted)
	{
		boostAnimation = Animation::create();
		boostAnimation->setDelayPerUnit(delayPerUnit);

		boostAnimation->addSpriteFrameWithFile("Character/fire1.png");
		boostAnimation->addSpriteFrameWithFile("Character/fire2.png");


		boostAnimate = Animate::create(boostAnimation);

		auto rep = RepeatForever::create(boostAnimate);
		boostImg->runAction(rep);
		boostImg->setVisible(true);
	}

	if (!jump)
	{
		animation = Animation::create();
		animation->setDelayPerUnit(delayPerUnit);
		for (int i = 1; i <= 2; i++)
		{
			char filename[64];
			sprintf(filename, "Character/%s_%d.png", spriteName, i);
			animation->addSpriteFrameWithFile(filename);
		}


		animate = Animate::create(animation);

		auto rep = RepeatForever::create(animate);
		this->runAction(rep);
	}
	else if (secJump)
	{
		this->stopAllActions();
		char filename[64];
		sprintf(filename, "Character/%s_j2.png", spriteName);
		this->setTexture(filename);
	}
	else
	{
		this->stopAllActions();
		char filename[64];
		sprintf(filename, "Character/%s_j.png", spriteName);
		this->setTexture(filename);
	}
}

bool Player::catchable()
{
	if (jump&&gravity > 0)
		return true;

	return false;
}

Rect Player::getBoundingBox()
{

	auto anchor = this->getAnchorPoint();
	auto wScaleRatio = 0.8 * this->getScaleX();
	auto hScaleRatio = 1.0* this->getScaleY();

	auto width = this->getContentSize().width*wScaleRatio;
	auto height = this->getContentSize().height*hScaleRatio;

	Rect boundingBox = Rect(this->getPositionX() - width*anchor.x,
		this->getPositionY() - height*anchor.y,
		width,
		height);

	return boundingBox;
}

Point Player::getCenter()
{
	auto anchor = this->getAnchorPoint();
	auto x = this->getPositionX() + (0.5f - anchor.x) * this->getContentSize().width;
	auto y = this->getPositionY() + (0.5f - anchor.y) * this->getContentSize().height;

	auto point = Point(x, y);
	return point;
}

void Player::invinsibleFunc(float type)
{
	type = (int)type;
	block = false;
	switch ((int)type)
	{
	case 0: break;
	case 1:boosted = false;
		delayPerUnit = DELAY_PER_UNIT;
		this->speed = SPEED;
		boostImg->setVisible(false);
		break;
	case 2:gianted = false; break;
	case 3:magneting = false; break;
	}

	if (!boosted && !gianted)
	{
		crashable = false;
	}

	playAnimation();
	invinsible = true;
	this->setOpacity(255 * 0.8);

	auto seq = Sequence::create(DelayTime::create(2.3),
		CCCallFunc::create(CC_CALLBACK_0(Player::reset, this, type)), NULL);
	this->getParent()->runAction(seq);

}

void Player::land()
{
	if (gianted)
		((GameScene*)this->getParent())->viberate();
	jump = false;
	secJump = false;
	gravity = 0;
	this->setRotation(0);
	playAnimation();
}

void Player::dead()
{
	boostImg->setVisible(false);
	this->setSpeed(0);
	this->stopAllActions();
	this->getParent()->stopAllActions(); 
	char filename[64];
	sprintf(filename, "Character/%s_b.png", spriteName);
	this->setTexture(filename);
}