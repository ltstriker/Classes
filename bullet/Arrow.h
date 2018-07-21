#pragma once
#include "cocos2d.h"
#include "bullet/Bullet.h"
#include "RotateWithAction.h"

USING_NS_CC;

class Arrow : public Bullet
{
public:
	virtual bool init();
	CREATE_FUNC(Arrow);
	void shoot();
	void shoot(Vec2 dist);
	void shoot(BaseMonster* target);
	void removeBullet();
};

