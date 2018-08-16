#ifndef _BASE_TOWER_
#define _BASE_TOWER_

#include "cocos2d.h"
#include "Circle.h"
#include "KRTerrain.h"
#include "../Monster/BaseMonster.h"

 

USING_NS_CC;

typedef enum {
	ARCHER_1 = 0, //1������
	ARCHER_2, //2������
	ARCHER_3, //3������
	ARTILLERY_1,//1������
	ARTILLERY_2,//2������
	ARTILLERY_3,//3������
	MAGE_1,//1����ʦ��
	MAGE_2,//2����ʦ��
	MAGE_3,//3����ʦ��
	ASSASSIN,
	BARAACKS_1,//��Ӫ
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
	CC_SYNTHESIZE(TowerType, towerType, TowerType); //����
	CC_SYNTHESIZE(KRTerrain*, myTerrain, MyTerrain);  //�����
	CC_SYNTHESIZE(std::string, towerName, TowerName); //����
	CC_SYNTHESIZE(int, level, Level);//�ȼ�
	CC_SYNTHESIZE(float, scope, Scope);//��Χ
	CC_SYNTHESIZE(float, nextScope, NextScope);//������Χ
	CC_SYNTHESIZE(float, rate, Rate);//�����ٶ�
	CC_SYNTHESIZE(int, force, Force);//������
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, buildMoney, BuildMoney);//�۳�ʱ������Ǯ
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
