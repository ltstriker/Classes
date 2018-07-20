#include "Boss_Efreeti.h"
#include "../../UI/GameManager.h"
#include "../../UI/map/BaseMap.h"
#include "Efreeti.h"
// #include "../../UI/"

// ����
Boss_Efreeti* Boss_Efreeti::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath) {
	auto monster = new Boss_Efreeti();
	if (monster && monster->init()) {
		monster->setPointsVector(points);
		monster->setMaxHp(5550);
		monster->setCurrHp(5550);
		monster->setMoney(1500);
		monster->sonPath = sonpath;
		monster->setForce(50); // ����50
		monster->setArmor(10); // ����10
		monster->setAttackByTower(true);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(20); // �ٶ�20
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

void Boss_Efreeti::frozen() {}

bool Boss_Efreeti::init() {
	if (!BaseMonster::init()) {
		return false;
	}
	setMonsterType(BOSS_EFREETI);
	setName("Boss_Efreeti_");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5-hd.plist");
	baseSprite = Sprite::createWithSpriteFrameName("Boss_Efreeti_0001.png");
	addChild(baseSprite);

	cloud = Sprite::createWithSpriteFrameName("Boss_Efreeti_Cloud_0001.png"); 

	cloud->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(cloud, -1);
	// �ƶ���
	cloud->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "cloud"))));
	createAndSetHpBar(); // ���Ѫ��
	lastState = stateNone;
	scheduleUpdate();
	schedule(schedule_selector(Boss_Efreeti::skill), 20.0f, 2, 5.0f); // ���似�ܵ�����
	addListener();
	return true;
}

void Boss_Efreeti::getHurt() {}

// ����
void Boss_Efreeti::death() {
	if (GameManager::getInstance()->monsterVector.contains(this)) {
		GameManager::getInstance()->monsterVector.eraseObject(this);
	}
	if (getState() != stateDeath) {
		//SoundManager::playEfreetiDeath();
		unschedule(schedule_selector(Boss_Efreeti::skill)); // �Ƴ�������
		setState(stateDeath);
		hpBgSprite->setVisible(false); // �Ƴ�Ѫ��
		baseSprite->stopAllActions();
		unscheduleUpdate();

		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		// ������������
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "death")),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this, false))
			, NULL));
	}
}

void Boss_Efreeti::skill(float dt)
{
	setIsAttacking(true); // ���빥��ģʽ
	stopWalking(); // ֹͣ�ƶ�
	//SoundManager::playEfreetiClap();
	// ���ż��ܶ���
	baseSprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "skill")),
		CallFuncN::create(CC_CALLBACK_0(Boss_Efreeti::addSons, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Efreeti::laugh, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Efreeti::restartWalking, this)),
		CallFuncN::create(CC_CALLBACK_0(Boss_Efreeti::setIsAttacking, this, false)),
		NULL));
}

// �ɳ�С��
void Boss_Efreeti::addSons() {
	for (unsigned int i = 0; i<sonPath.size(); i++) {
		for (unsigned int j = 1; j<sonPath.at(i).size(); j++) {
			std::vector<Point> points = sonPath.at(i).at(j);
			auto Efreeti = Efreeti::createMonster(points, pointCounter);
			this->getParent()->addChild(Efreeti);
			GameManager::getInstance()->monsterVector.pushBack(Efreeti);
		}
	}
}

// Ц��
void Boss_Efreeti::laugh() {
	//SoundManager::playEfreetiLaugh();
}

// ��ը����
void Boss_Efreeti::explosion() {
	death();
}