#pragma once
#include "Word.h"
#include <vector>

class WordStorage
{
private:

	std::vector<Word*> wordlist;

public:
	WordStorage();
	~WordStorage();

	Word* getRandWord(int stage); 
	int getCount(){ return wordlist.size(); }
	Word* getWord(int at){ return wordlist.at(at); }

private:

	void init();

};