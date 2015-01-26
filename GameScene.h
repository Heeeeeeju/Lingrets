#pragma once

#include "cocos2d.h"
#include "Target.h"
#include "Player.h"
#include "Background.h"
#include "WordImg.h"
#include "WordStorage.h"
#include "BreakBlock.h"
#include "PauseLayer.h"
#include "Item.h"
#include "Coin.h"
#include "Star.h"
#include "ResultScene.h"
#include "FloorBlock.h"
#include "Pet.h"

USING_NS_CC;

#define BLOCKOBJECT_GENTIME 1.0f
#define STAR_COIN_GENTIME 0.1f
#define GENTIME 1.0f
#define ITEM_GEN_TIME 15.0f;

class GameScene : public Layer
{
private:
	int stage = 1;

	Background *background;
	Background *bg2, *bg3,*bg4;
	Background *bgForAddC;
	Player *player;
	Target *target;
	Pet *pet;

	Sprite *flash;
	Sprite *now;

	enum GSta{Ready,Play,End,Pause} gsta=Ready;

	float hpTime = CCUserDefault::getInstance()->getIntegerForKey("HPLv", 0) * 2 + 43;
	float maxHp = CCUserDefault::getInstance()->getIntegerForKey("HPLv", 0) * 2 + 43;

	bool feverTime = false;
	bool bonusTime = false;

	ProgressTimer *hpGage;

	float playTime = 0;

	float genDelay = GENTIME;
	float objectGenDelay = BLOCKOBJECT_GENTIME*2;
	float starCoinDelay = 5;
	int genCounter = 0;
	float ItemGenDelay = ITEM_GEN_TIME;
	float bonusTimeGage = CCUserDefault::getInstance()->getIntegerForKey("BonusLv", 0)*0.3 + 3;;
	float bonusGenDelay = 0;

	int score = 0;
	int money = 0;

	int floorTerm = 0;

	std::list<WordImg*> wordImgVector;
	std::string collectedWord;
	
	std::list<BreakBlock*> blockVector;
	std::list<Star*> starVector;
	std::list<Item*> itemList;
	std::list<Coin*> coinList;
	std::list<FloorBlock*> floorList;
	
	std::vector<Word*> staWord;

	std::vector<Node*> collectedDeck;

	WordStorage *wordStorage;

	Word* targetWord=nullptr;
	Word* collectWord;
	int collectCounter = 0;

	Sprite *board;
	Sprite *floor;
	Node* collectWordHoldNode;

	LabelTTF *scoreLabel;
	LabelTTF *moneyLabel;

	bool boosted = false;

	float boostGage = 2;

	Menu *menu;

	friend class Background;
	friend class PauseLayer;
public:
	CREATE_FUNC(GameScene);
	static Scene *createScene();
	virtual bool init();

	void itemGet(int type);
	void viberate();

private:

	void addToHoldNodeAction(Sprite* img);
	void deleteNodeAction();
	void nodeInit();

	void update(float dt);
	void boostUpdate(float dt);
	void bonusUpdate(float dt);
	void objectUpdate(float dt);
	void timerUpdate(float dt);
	void floorCollisionUpdate(float dt);

	void genObjectCheck(float dt);

	void genPuzzle(const std::string parts,bool high);
	void genBlockObject(int type);
	void starGenerate(float dt);
	void ItemGenerate(float dt);
	void genFloorBlock(float dt);

	void gameFinish();

	void bonusStart();
	void bonusEnd(float dt);

	void hpChange(float index);

	void blocked();
	void boost();
	void resetB();

	void pause(Object *pSender);
	void resume();
	void goToMain(Object *pSender);

	void collectPuzzle(WordImg *puzzle);
	std::string confuseWord(std::string str);
	
	bool onTouchBegan(Touch* touch, Event* event);
	inline bool isVowel(char c){ if (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o') return true; return false; }

};

