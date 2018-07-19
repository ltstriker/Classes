#pragma once

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Bomb : public Bullet
{
private:
	static void initBombAnimation();
	
public:
	static Bomb* createBombWithType(int type);
	virtual bool initWithType(int type);
	int type;
	CREATE_FUNC(Bomb);
	void shoot();
	void removeBullet();
};

