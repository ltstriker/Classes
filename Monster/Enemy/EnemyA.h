#ifndef _ENEMYA_H_
#define _ENEMYA_H_

#include "../BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class EnemyA : public BaseMonster
{
public:
	virtual bool init() override;
	static EnemyA* createMonster(std::vector<Point> points, int pointCounter);
	void getHurt();
	void death();
	void explosion();
};

#endif