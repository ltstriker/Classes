#pragma once

#include "cocos2d.h"
#include "BaseArtilleryTower.h"

USING_NS_CC;

class ArtilleryTowerV1 : public BaseArtilleryTower
{
public:

	virtual bool init();
	CREATE_FUNC(ArtilleryTowerV1);
	void updateTower();
	void showUpdateMenu();

private:
	void buildingAnimation();
	void buildingSmokeAnimation(float dt);
};

