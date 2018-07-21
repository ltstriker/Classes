#include "Thug.h"
#include "../../UI/GameManager.h"
USING_NS_CC;


Thug* Thug::createMonster(std::vector<Point> points) {
	auto monster = new Thug();
	if (monster && monster->init()) {
		monster->setPointsVector(points);
		monster->setMaxHp(35);
		monster->setCurrHp(35);
		monster->setMoney(10);

		if (GameManager::getInstance()->mode == true) {
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - 10;
		}

		monster->setForce(4); // ¹¥»÷4
		monster->setArmor(0); // ·ÀÓù0
		// monster->setForce(8);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(40);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Thug::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(THUG);
	setName("Thug_");
	baseSprite = Sprite::createWithSpriteFrameName("desertThug_0001.png");
	addChild(baseSprite);
	createAndSetHpBar(); // ÏÔÊ¾ÑªÌõ
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	addListener();
	return true;
}