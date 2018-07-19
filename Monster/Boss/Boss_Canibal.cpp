#include "Boss_Canibal.h"
#include "../../UI/GameManager.h"
#include "../../UI/BaseMap.h"
#include "CanibalOffspring.h"
// #include "SoundManager.h"

// ����Monster
Boss_Canibal* Boss_Canibal::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath) {
	auto monster = new Boss_Canibal();
	if (monster && monster->init()) {
		monster->setPointsVector(points);
		monster->setMaxHp(9999);
		monster->setCurrHp(9999);
		monster->setMoney(1500);
		monster->sonPath = sonpath;
		monster->setForce(80); // ����80
		monster->setArmor(10); // ����10
		monster->setAttackByTower(true);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(20); // ��ʼ�ٶ�20
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

// �ݲ�ʵ��
void Boss_Canibal::frozen() {

}

bool Boss_Canibal::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(BOSS_CANIBAL);
	setName("Boss_Canibal_");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level10 - hd.plist"); 
	baseSprite = Sprite::createWithSpriteFrameName("CanibalBoos_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = stateNone;
	scheduleUpdate();
	schedule(schedule_selector(Boss_Canibal::beforeSkill), 50.0f, 2, 20.0f);
	addListener(); // ����¼�����
	skillTag = 0;
	return true;
}

void Boss_Canibal::getHurt() {}

// Boss����
void Boss_Canibal::death() {
	if (GameManager::getInstance()->monsterVector.contains(this)) {
		GameManager::getInstance()->monsterVector.eraseObject(this);
	}
	if (getState() != stateDeath) {
		// ������Ч
		SoundManager::playMonoDeath();
		SoundManager::playEfreetiDeath();

		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleAllCallbacks();
		unscheduleUpdate();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		// ���Ŷ���
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "death")),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this, false))
			, NULL));
	}
}

// ���似��ǰ״̬
void Boss_Canibal::beforeSkill(float dt) {
	SoundManager::playChestdrum();
	if (skillTag == 0) {
		pointCounter = pointCounter + 60;
		location = this->getPointsVector().at(pointCounter);
	}
	if (skillTag == 1) {
		setPointsVector(sonPath.at(0).at(1));
		pointCounter = 100;
		location = this->getPointsVector().at(pointCounter);
	}
	// ���ڹ���״̬
	setIsAttacking(true);
	setAttackBySoldier(false);
	setAttackByTower(false);
	stopWalking();
	// ���Ŷ���
	baseSprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "skill_before")),
		Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "jump")),
		MoveTo::create(0.5f, Point(590, 510)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::skill, this)),
		NULL));
	skillTag++;
}

// ����
void Boss_Canibal::changePositionLeft() {
	SoundManager::playChimps_1();
	baseSprite->setPosition(Point(590, 510));
}

// ����
void Boss_Canibal::changePositionRight() {
	SoundManager::playChimps_2();
	baseSprite->setPosition(Point(680, 510));
}

// ʹ�ü���
void Boss_Canibal::skill() {
	setAttackByTower(false);
	setAttackBySoldier(false);
	// ����ʹ�ö���
	baseSprite->runAction(Sequence::create(
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setFlippedX, this->baseSprite, false)),
		Animate::create((AnimationCache::getInstance()->getAnimation(getName() + "skill"))),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::addSons, this)),

		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::changePositionRight, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setFlippedX, this->baseSprite, true)),

		Animate::create((AnimationCache::getInstance()->getAnimation(getName() + "skill"))),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::addSons, this)),

		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setFlippedX, this->baseSprite, false)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::changePositionLeft, this)),

		Animate::create((AnimationCache::getInstance()->getAnimation(getName() + "skill"))),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::addSons, this)),

		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::changePositionRight, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setFlippedX, this->baseSprite, true)),

		Animate::create((AnimationCache::getInstance()->getAnimation(getName() + "skill"))),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::addSons, this)),

		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::changePositionLeft, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setFlippedX, this->baseSprite, false)),

		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::afterSkill, this)),
		NULL));
}

// ʹ�ü��ܺ󶯻�
void Boss_Canibal::afterSkill() {
	tempNextPoint = this->getPointsVector().at(pointCounter + 1);
	baseSprite->runAction(Sequence::create(
		Animate::create((AnimationCache::getInstance()->getAnimation(getName() + "skill_after"))),
		MoveTo::create(0.5f, location),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::restartWalking, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setAttackBySoldier, this, true)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setAttackByTower, this, true)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Canibal::setIsAttacking, this, false)),
		NULL));
}

// �ɳ�С��
void Boss_Canibal::addSons() {
	for (unsigned int i = 0; i<sonPath.size(); i++) {
		for (unsigned int j = 1; j<sonPath.at(i).size(); j++) {
			std::vector<Point> points = sonPath.at(i).at(j);
			auto canibalOffspring = CanibalOffspring::createMonster(points, pointCounter);
			this->getParent()->addChild(canibalOffspring);
			GameManager::getInstance()->monsterVector.pushBack(canibalOffspring);
		}
	}
}

// ��ը����
void Boss_Canibal::explosion() {
	death();
}