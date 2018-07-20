#pragma once
#include "cocos2d.h"
#include "BaseTower.h"
#include "./bullet/Bullet.h"
USING_NS_CC;

class BaseMagicTower:public BaseTower
{
public:

protected:
	Sprite* shooter;
	Sprite* towerBase;
	Bullet* currBullet;
	void initTower(int level);
	void addTerrain();

	virtual Bullet* MageTowerBullet();
	void shoot(float dt);
};