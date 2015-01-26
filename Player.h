#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define DELAY_PER_UNIT 0.05f
#define G 1.2f
#define JUMPPOWER -22.8f
#define SPEED 10

class Player : public Sprite
{
private:

	float gravity = 0;

	char spriteName[5];

	bool jump = true;
	bool secJump = true;
	bool jumpRotation = false;
	bool crashable = false;
	bool block = false;
	bool boosted = false;
	bool gianted = false;
	bool magneting = true;

	float speed = SPEED;

	Animation *animation;
	Animation *boostAnimation;

	Animate *boostAnimate;
	Animate *animate;

	Sprite* cloud;
	Sprite* boostImg;

	float delayPerUnit = DELAY_PER_UNIT;

	float giantTime = CCUserDefault::getInstance()->getFloatForKey("GiantTime",3);
	float boostTime = CCUserDefault::getInstance()->getFloatForKey("BoostTime", 3);
	float magnetTime = CCUserDefault::getInstance()->getFloatForKey("MagnetTime", 3);
	float blockTime = 0.3;

	int blinkTimer = 10;
	bool invinsible = false;
public:

	CREATE_FUNC(Player);
	virtual bool init();

	inline void setSpeed(float spd){ speed = spd; }
	inline float getSpeed(){ return speed; }
	inline float getGravity(){ return gravity; }

	void blocked();
	void dead();
	
	void giant();
	void magnet();
	void boost();

	void feverF();
	void feverEnd();
	void reset(int type);

	void update(float dt);
	void itemUpdate(float dt);
	void playAnimation();

	void jumpFunc();
	void land();

	bool catchable();

	inline bool getJump(){ return jump; }
	inline bool getCrashable(){ return crashable; }
	inline bool getInvinsible(){ return invinsible; }
	inline bool getMagnet(){ return magneting; }
	inline bool getGiant(){ return gianted; }
	inline bool getBoost(){ return boosted; }
	inline void setGravity(float g){ gravity = g; }
	virtual Rect getBoundingBox();
	Point getCenter();

private:

	void invinsibleFunc(float type);

};

