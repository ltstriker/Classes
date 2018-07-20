#pragma once
#include "cocos2d.h"
#include "BaseMagicTower.h"

USING_NS_CC;

class MagicTowerV1: public BaseMagicTower
{
public:

	bool init();
    CREATE_FUNC(MagicTowerV1);
	void updateTower();
	void showUpdateMenu();
	Bullet* MageTowerBullet();
private:
	void buildingAnimation();
	void buildingSmokeAnimation(float dt);
};