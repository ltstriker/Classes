#pragma once

#include "cocos2d.h"
#include "BaseArrowTower.h"

USING_NS_CC;

class ArrowTowerV1 : public BaseArrowTower
{
public:

	bool init();
	CREATE_FUNC(ArrowTowerV1);
	void updateTower();
	void showUpdateMenu();
	Bullet* ArrowTowerBullet();
private:
	void buildingAnimation();
	void buildingSmokeAnimation(float dt);
};
