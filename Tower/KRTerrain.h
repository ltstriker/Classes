#pragma once

#include "cocos2d.h"

USING_NS_CC;

class KRTerrain: public Sprite
{
public:
	virtual bool init(int type);
	static KRTerrain* createTerrain(int type);
	void showUpdateMenu();
	void hideUpdateMenu();
	Sprite* terrain;
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	bool isUpdateMenuShown;
	void smokeEffect();
};

