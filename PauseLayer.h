#pragma once

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class PauseLayer: public Layer
{
public:
	CREATE_FUNC(PauseLayer);
	bool init();
	PauseLayer();
	~PauseLayer();

private:

	void resume(Object *pSender);
	void retry(Object *pSender);
	void main(Object *pSender);

};

