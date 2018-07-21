#ifndef _BASE_TOWER_
#define _BASE_TOWER_

#include "cocos2d.h"
#include "Circle.h"
#include "KRTerrain.h"
#include "../Monster/BaseMonster.h"

 

USING_NS_CC;

typedef enum {
	ARCHER_1 = 0, //1级箭塔
	ARCHER_2, //2级箭塔
	ARCHER_3, //3级箭塔
	ARTILLERY_1,//1级炮塔
	ARTILLERY_2,//2级炮塔
	ARTILLERY_3,//3级炮塔
	MAGE_1,//1级法师塔
	MAGE_2,//2级法师塔
	MAGE_3,//3级法师塔
	ASSASSIN,
	BARAACKS_1,//兵营
	BARAACKS_2,
	BARAACKS_3,
	TEMPLAR
}TowerType;


class BaseTower : public Sprite
{
public:
	BaseTower();
	~BaseTower();
	virtual void updateTower() {};
	virtual void sellTower();
	virtual void removeTower();
	virtual bool init();
	CC_SYNTHESIZE(TowerType, towerType, TowerType); //类型
	CC_SYNTHESIZE(KRTerrain*, myTerrain, MyTerrain);  //建造点
	CC_SYNTHESIZE(std::string, towerName, TowerName); //名称
	CC_SYNTHESIZE(int, level, Level);//等级
	CC_SYNTHESIZE(float, scope, Scope);//范围
	CC_SYNTHESIZE(float, nextScope, NextScope);//升级后范围
	CC_SYNTHESIZE(float, rate, Rate);//攻击速度
	CC_SYNTHESIZE(int, force, Force);//攻击力
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, buildMoney, BuildMoney);//售出时返还金钱
	virtual void showTowerInfo();
	bool isUpdateMenuShown;
	virtual void update1() {};
	virtual void update2() {};
	virtual void setRallyPoint(Point point) {};
protected:
	virtual void checkNearestMonster();
	BaseMonster* nearestMonster;
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	virtual void showUpdateMenu() {};
	virtual void hideUpdateMenu();
	Sprite* terrain;
	void setListener();
};

#endif
