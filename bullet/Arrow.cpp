#include "Arrow.h"

bool Arrow::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::create("/bullet/arrow.png");
	sprite->setScale(0.1, 0.1);
	addChild(sprite);
	return true;
}

void Arrow::shoot()
{
	//SoundManager::playArrowRelease();
	/*auto bombPostion = this->getPosition() + this->getParent()->getPosition();
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
	auto rtt = RotateWithAction::create(10.0);

	bulletAction = Spawn::create(mt, rtt, NULL);
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));*/

	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));
}

void Arrow::removeBullet()
{
	bool isMissed = true;
	auto instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect) && monster->getAttackBySoldier())
		{
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getMaxForce() + monster->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPercentage((currHp / monster->getMaxHp()) * 100);
			monster->getHurt();
			isMissed = false;
			if (currHp == 0) {
				monster->death();
			}
			break;
		}
	}
	if (isMissed) {

		sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("/bullet/arrow_broken.png"));

		sprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}

