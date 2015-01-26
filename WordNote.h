#pragma once

#include "cocos2d.h"
#include "MainScene.h"
#include "NoteEnchant.h"

USING_NS_CC;

struct WordN
{
	std::string img;
	std::string name;
	std::string info;
	int enchant;
	int stage;
	bool equiped;
};

class WordNote : public Layer
{
private:

	std::vector<WordN*> wordNVector;


	Menu *menu;
	Sprite *selector;
	Sprite *detail;

	int money = CCUserDefault::getInstance()->getIntegerForKey("Money", 0);

	friend class NoteEnchant;

public:
	CREATE_FUNC(WordNote);
	bool init();
	WordNote();
	~WordNote();

private:

	//void loadNoteData();
	//void saveNoteData();

	void select(Object* pSender);

	void equip(Object *pSender);
	void enchant(Object *pSender);

	void exit(Object *pSender);

};

