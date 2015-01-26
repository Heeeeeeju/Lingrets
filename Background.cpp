#include "Background.h"
#include "GameScene.h"


Background* Background::create(const std::string &filename)
{
	Background *pRet = new Background();

	pRet->setImg(filename);
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

bool Background::init()
{
	if (!Layer::init())
		return false;

	img1->setPosition(0, 400);
	img1->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(img1);
	img2->setPosition(img1->getContentSize().width, 400);
	img2->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(img2);

	return true;
}

void Background::setImg(const std::string &filename)
{
	file = filename;
	img1 = Sprite::create(filename);
	img2 = Sprite::create(filename);
}

void Background::update(float dt)
{	

	this->setSpeed(((GameScene*)getParent())->player->getSpeed() *getTag()/4);
	img1->setPositionX(img1->getPositionX() - speed);
	img2->setPositionX(img2->getPositionX() - speed);
	
	if (img1->getPositionX() < 0)
	{
		img1->setPositionX(img1->getPositionX() + img1->getContentSize().width * 2);
		removeAllChildrenAndEraseFromVector(img1);
		backImgIs1 = true;
	}
	if (img2->getPositionX() < 0)
	{
		img2->setPositionX(img2->getPositionX() + img1->getContentSize().width * 2);
		removeAllChildrenAndEraseFromVector(img2);
		backImgIs1 = false;
	}	

}

void Background::removeAllChildrenAndEraseFromVector(Sprite* img)
{
	auto children = img->getChildren();
	auto gameScene = (GameScene*)this->getParent();
	

	for (auto iter = children.begin(); iter != children.end(); ++iter)
	{
		bool erased = false;

		for (auto i = gameScene->starVector.begin(); i != gameScene->starVector.end(); ++i)
		{
			if ((*i) == (*iter))
			{
				(*i)->removeFromParent();
				if ((*i) != NULL)
				{
					delete((*i));
					(*i) = NULL;
				}
				gameScene->starVector.erase(i);
				erased = true;
				break;
			}
		}

		if (!erased)
		{
			for (auto i = gameScene->blockVector.begin(); i != gameScene->blockVector.end(); ++i)
			{
				if ((*i) == (*iter))
				{
					(*i)->removeFromParent();
					if ((*i) != NULL)
					{
						delete((*i));
						(*i) = NULL;
					}
					gameScene->blockVector.erase(i);
					erased = true;
					break;
				}
			}
		}
			
		if (!erased)
		{
			for (auto i = gameScene->wordImgVector.begin(); i != gameScene->wordImgVector.end(); ++i)
			{
				if ((*i) == (*iter))
				{
					(*i)->removeFromParent();
					if ((*i) != NULL)
					{
						delete((*i));
						(*i) = NULL;
					}
					auto puzzle = WordImg::create(" ? ", true);
					gameScene->collectPuzzle(puzzle);
					gameScene->wordImgVector.erase(i);
					erased = true;
					break;
				}
			}
		}
	}

	img->removeAllChildren();

}
void Background::bonus(const std::string &filename)
{
	img1->setTexture(filename);
	img2->setTexture(filename);
}

void Background::reset()
{
	auto pos1 = img1->getPosition();
	auto pos2 = img2->getPosition();
	img1->removeFromParent();
	img2->removeFromParent();
	img1 = Sprite::create(file);
	img2 = Sprite::create(file);
	img1->setPosition(pos1);
	img2->setPosition(pos2);
	this->addChild(img1);
	this->addChild(img2);
}
