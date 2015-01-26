#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Background : public Layer
{
private:
	std::string file;
	int speed=5;
	Sprite* img1;
	Sprite* img2;
	bool backImgIs1 = false;
public:
	static Background* create(const std::string &filename);
	virtual bool init();

	inline bool getBackImgIs1(void){ return backImgIs1; }
	inline void setSpeed(int spd){ speed = spd; }
	inline Sprite* getImg1(){ return img1; }
	inline Sprite* getImg2(){ return img2; }

	void update(float dt);
	void bonus(const std::string &filename);

	void reset();
private:

	void setImg(const std::string &filename);
	void removeAllChildrenAndEraseFromVector(Sprite* img);

	
};

