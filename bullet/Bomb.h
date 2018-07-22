#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "RotateWithAction.h"
#include "Monster/BaseMonster.h"
USING_NS_CC;
using namespace cocos2d;
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

