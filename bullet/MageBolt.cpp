#include "MageBolt.h"
#include "UI/GameManager.h"

bool MageBolt::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("/bullet/image 4946.png.png");
	addChild(sprite);
	return true;
}

void MageBolt::shoot()
{
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();
	Sprite* target = nullptr;
	auto instance = GameManager::getInstance();
	auto tower = this->getParent();
	auto monsterVector = instance->monsterVector;
	double  min_dis = 1000000.0f;
	for (int i = 0; i < monsterVector.size(); i++) {
		auto monster = monsterVector.at(i);
		auto towerPos = tower->getPosition();
		double temp_dis = towerPos.distance(monster->getPosition());
		if (temp_dis < min_dis) {
			target = monster;
			min_dis = temp_dis;
		}
	}
	auto dist = target->getPosition();
	auto mt = ParabolaTo::create(1.0f, (CCPoint)bombPostion, (CCPoint)dist);
	bulletAction = Spawn::create(mt);
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(MageBolt::removeBullet, this)),
		NULL));
}

void MageBolt::removeBullet()
{
	GameManager *instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();

		if (monster != NULL && monsterRect.intersectsRect(bulletRect) && monster->getAttackByTower())
		{
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getMaxForce();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPercentage((currHp / monster->getMaxHp()) * 100);
			monster->getHurt();

			if (currHp == 0) {
				monster->death();
				//instance->monsterVector.eraseObject(monster);
			}
			break;
		}
	}
	this->removeFromParent();
}



