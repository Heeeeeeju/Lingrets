#include "NoteEnchant.h"


NoteEnchant::NoteEnchant()
{
}


NoteEnchant::~NoteEnchant()
{
}

bool NoteEnchant::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto backMenu = Menu::create();
	backMenu->setPosition(0, 0);
	this->addChild(backMenu);

	auto black = MenuItemImage::create("Pause/black.png", "Pause/black.png");
	black->setPosition(visibleSize / 2);
	backMenu->addChild(black);


	return true;
}