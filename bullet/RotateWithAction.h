#pragma once

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class RotateWithAction :public cocos2d::CCActionInterval
{
public:
	//CCObject * copyWithZone(CCZone* pZone);
	RotateWithAction(void);
	~RotateWithAction(void);
	static RotateWithAction* create(double duration);

	void RotateWithAction::update(float t);
	void RotateWithAction::startWithTarget(Node *target);
private:
	Vec2 lastPosition;
	Vec2 thisPosition;

};


