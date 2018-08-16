#pragma once
#include "cocos2d.h"
#include "KRTerrain.h"

USING_NS_CC;

class TowerAIManager : public Sprite
{
public:
	bool getAble();
	static TowerAIManager* getInstance();
	void initAI();
	void update();
	void TowerAi_delete();
private:

	static int count;
	bool isAble;
	static TowerAIManager* _instance;
	TowerAIManager() {};
};
