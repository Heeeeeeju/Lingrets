#pragma once

#include "cocos2d.h"
#include "WordNote.h"

USING_NS_CC;

class NoteEnchant : public Layer
{
private:

	int targetNote = 1;

public:
	NoteEnchant();
	~NoteEnchant();
	CREATE_FUNC(NoteEnchant);
	bool init();

private:

};

