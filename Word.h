#pragma once

#include <iostream>
#include "cocos2d.h"



struct Parts
{
	std::string part;
	int emphasis;
};

class Word
{
private:


	std::string eng;
	std::string kor;	

	std::vector<Parts> parts;

	std::string imgStr;

	int partsNum;
	int type;
public:
	Word(std::string eng, std::string kor, int type);
	~Word();
public:
	std::string getEng(){ return eng; }
	std::string getKor(){ return kor; }
	int getType(){ return type; }
	std::string getParts(int num);
	int getPartsEmphasis(int num);
	int getPartsNum();
	std::string getImg(){ return imgStr; }

};

