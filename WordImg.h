#pragma once
#include "cocos2d.h"

USING_NS_CC;

class WordImg : public Sprite
{
private:
	LabelTTF *partLabel;
	std::string partString;
	float speed = 10;
	bool high;
public:
	~WordImg();

	static WordImg* create(const std::string &parts,bool high);
	virtual bool init();

	inline std::string getPartString(){ return partString; }
	inline bool getHigh(){ return high; }
	inline void setSpeed(float speed){ this->speed = speed; }

	void update(float dt);

	void removeFromParentWithEffect();

private:
	WordImg();



};

