#pragma once
#include "cocos2d.h"
#include "KRTerrain.h"
#include "./ui/map/Level1.h"
#include "TowerAIManager.h"

USING_NS_CC;

class TowerAIManager
{
public:
	bool getAble();
	static TowerAIManager* getInstance();
	void initAI();
	void update(KRTerrain*);
private:
	bool isAble;
	static TowerAIManager* _instance;
	TowerAIManager() {};
};
