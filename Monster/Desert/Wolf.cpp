#include "Wolf.h"
#include "../../UI/GameManager.h"
USING_NS_CC;

Wolf* Wolf::createMonster(std::vector<Point> points) {
	auto monster = new Wolf();
	if (monster && monster->init())
	{
		monster->setPointsVector(points);
		monster->setMaxHp(35);
		monster->setCurrHp(35);
		monster->setRunSpeed(100); // 速度100
		monster->runNextPoint();
		monster->setMoney(20);

		if (GameManager::getInstance()->mode == true) {
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - 20;
		}

		monster->setForce(2); // 攻击2
		monster->setArmor(0); // 防御0
		monster->setAttackBySoldier(true);
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Wolf::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(WOLF);
	setName("Wolf_");
	baseSprite = Sprite::createWithSpriteFrameName("desertWolf_0001.png");
	addChild(baseSprite);
	createAndSetHpBar(); // 显示血条
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	addListener();
	return true;
}