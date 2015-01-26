#include "Word.h"


Word::Word(std::string eng, std::string kor,int type)
{
	this->eng = eng;
	this->kor = kor;
	this->type = type;

	parts.clear();
	int count = 0;
	for (int i = 0; true;i++)
	{
		if (eng[i]=='*' || eng[i] == '\0')
		{	//ba*na*na

			cocos2d::String a = eng.substr(i - 1, 1);
			
			Parts part = { eng.substr(count, i - count - 1), atoi(a.getCString()) };
			count = i+1;
			partsNum++;
			parts.push_back(part);
			if (eng[i] == '\0')
			{
				break;
			}
		}
	}
	this->eng.clear();

	for (auto iter = parts.begin(); iter != parts.end(); ++iter)
	{
		this->eng.append((*iter).part);
	}
	partsNum = parts.size()-1;

	char filename[30];
	sprintf(filename, "wordImg/%s.png", this->eng.c_str());

	imgStr = filename;

}


Word::~Word()
{
}


std::string Word::getParts(int num)
{
	if (num > partsNum)
		num = partsNum; 

	return parts.at(num).part;
}

int Word::getPartsEmphasis(int num)
{
	if (num > partsNum)
		num = partsNum;

	return parts.at(num).emphasis;
}

int Word::getPartsNum()
{
	int rtn = parts.size() - 1;
	return rtn;
}