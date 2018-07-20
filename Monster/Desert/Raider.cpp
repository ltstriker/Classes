#include "Raider.h"

USING_NS_CC;

Raider* Raider::createMonster(std::vector<Point> points) {
	auto monster = new Raider();
	if (monster && monster->init()) {
		monster->setPointsVector(points);
		monster->setMaxHp(160);
		monster->setCurrHp(160);
		monster->setMoney(30);
		monster->setRunSpeed(40); // 速度40
		monster->setArmor(10); // 防御10
		monster->setForce(8); // 攻击8
		monster->setAttackBySoldier(true);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Raider::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(RADIER);
	setName("Raider_");
	baseSprite = Sprite::createWithSpriteFrameName("desertRaider_0001.png");
	addChild(baseSprite);
	createAndSetHpBar(); // 显示血量
	setState(stateNone);
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	addListener();
	return true;
}