#include "Efreeti.h"
#include "../../UI/GameManager.h"
USING_NS_CC;

// ¥¥Ω®
Efreeti* Efreeti::createMonster(std::vector<Point> points, int pointCounter) {
	auto monster = new Efreeti();
	if (monster && monster->init()) {
		monster->setPointsVector(points);
		monster->setMaxHp(100);
		monster->setCurrHp(100);
		monster->setMoney(20);
		monster->setForce(15); // π•ª˜15
		monster->setArmor(0); // ∑¿”˘0
		monster->setAttackBySoldier(true);
		monster->setAttackByTower(true);
		monster->setRunSpeed(50); // ÀŸ∂»50
		monster->pointCounter = pointCounter + 10;
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Efreeti::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(EFREETI);
	setName("Efreeti_");
	// SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5-hd.plist");
	baseSprite = Sprite::createWithSpriteFrameName("desertEfreeti_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = stateNone;
	scheduleUpdate();
	addListener();
	return true;
}

void Efreeti::getHurt() {}

// À¿Õˆ
void Efreeti::death() {
	if (GameManager::getInstance()->monsterVector.contains(this)) {
		GameManager::getInstance()->monsterVector.eraseObject(this);
	}
	if (getState() != stateDeath) {
		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleUpdate();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "death")),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this, false))
			, NULL));
	}
}

// ±¨’®À¿Õˆ
void Efreeti::explosion() {
	death();
}