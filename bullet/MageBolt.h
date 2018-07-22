#pragma once

#include "cocos2d.h"
#include "bullet/Bullet.h"
#include "Monster/BaseMonster.h"
USING_NS_CC;
using namespace cocos2d;
class MageBolt : public Bullet
{
public:
	virtual bool init();
	CREATE_FUNC(MageBolt);
	void shoot();
	 void shoot(Vec2 dist) ;
	 void shoot(BaseMonster* target) ;
	void removeBullet();
};
