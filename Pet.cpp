#include "Pet.h"
#include <math.h>

bool Pet::init()
{
	if (!Sprite::initWithFile("Pet/001_1.png"))
		return false;

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	animation->addSpriteFrameWithFile("Pet/001_1.png");
	animation->addSpriteFrameWithFile("Pet/001_2.png");
	
	auto animate = Animate::create(animation);
	auto repAction = RepeatForever::create(animate);

	this->runAction(repAction);//S4BJT
	
	kart = Sprite::create("Pet/kart_1.png");
	kart->setPosition(kart->getContentSize().width / 2, -kart->getContentSize().height / 2);
	this->addChild(kart);
	kart->setVisible(false);

	auto pAnimation = Animation::create();
	pAnimation->setDelayPerUnit(0.2f);

	pAnimation->addSpriteFrameWithFile("Pet/kart_1.png");
	pAnimation->addSpriteFrameWithFile("Pet/kart_2.png");

	auto panimate = Animate::create(pAnimation);
	auto prepAction = RepeatForever::create(panimate);

	kart->runAction(prepAction);

	return true;
}

Pet::Pet()
{
}


Pet::~Pet()
{
}

void Pet::update(float dt)
{
	if (mean)
	{
		timer += dt;
		if (timer >= 2.5)
		{
			kart->setVisible(false);
			this->runAction(Sequence::create(
				MoveBy::create(0.4, Vec2(-850, 0)),
				MoveBy::create(0.5, Vec2(400, 0)),
				NULL
				));
			mean = false;
			timer = 0;
		}
	}

}

void Pet::showMean(std::string mean)
{
	this->mean = true;
	kart->setVisible(true);
	this->runAction(Sequence::create(
		MoveBy::create(0.2,Vec2(-500,0)),
		MoveTo::create(0.3, Vec2(600, 350)),
		NULL
		));

	kart->removeAllChildren();

	auto label = LabelTTF::create(mean.c_str(), "Fonts/SourceHanSansKR.ttf", 48);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(kart->getContentSize().width / 2,kart->getContentSize().height* 3 / 5);
	kart->addChild(label,2);

}

Rect Pet::getKartBoundingBox()
{
	Rect kartRect = Rect(
		kart->getPositionX() + kart->getParent()->getPositionX(),
		kart->getPositionY() + kart->getParent()->getPositionY(),
		kart->getContentSize().width,
		kart->getContentSize().height
		);

	return kartRect;

}