#include "MageBolt.h"
#include "UI/GameManager.h"
#include "RotateWithAction.h"
bool MageBolt::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::create("/bullet/image 4946.png");
	addChild(sprite);
	return true;
}

void MageBolt::shoot()
{
	Node* target = nullptr;
	auto instance = GameManager::getInstance();
	auto tower = this->getParent();
	auto monsterVector = instance->monsterVector;
	double  min_dis = 1000000.0f;
	for (int i = 0; i < monsterVector.size(); i++) {
		auto monster = monsterVector.at(i);
		auto sprite = monster->baseSprite;

		auto towerPos = tower->getPosition();
		double temp_dis = towerPos.distance(sprite->getPosition());

		if (temp_dis < min_dis) {
			target = monster;
			min_dis = temp_dis;
			//auto spritepos = monster->getPosition();

		}
	}
	auto dist = ((BaseMonster*)target)->baseSprite->getPosition();
	//auto mt = ParabolaTo::create(0.5f, (CCPoint)getPosition(), (CCPoint)(dist - getParent()->getPosition()));
	auto mt = MoveTo::create(0.5f, dist-getParent()->getPosition());
	auto rtt = RotateWithAction::create(0.5);

	auto bulletAction0 = Spawn::create(mt, rtt, NULL);
	runAction(Sequence::create(bulletAction0,
		CallFuncN::create(CC_CALLBACK_0(MageBolt::removeBullet, this)),
		NULL));
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
	bulletAction = Spawn::create(mt);
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(MageBolt::removeBullet, this)),
		NULL));*/

	/*runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(MageBolt::removeBullet, this)),
		NULL));
		*/
}

void MageBolt::shoot(Vec2 dist)
{
	auto bombPostion = this->getPosition();
	/*Sprite* target = nullptr;
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
	}*/
	//auto dist = target->getPosition();
	auto mt = ParabolaTo::create(1.0f, (CCPoint)bombPostion, (CCPoint)dist);
	//auto rtt = RotateWithAction::create(10.0);

	bulletAction = Spawn::create(mt, NULL);
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(MageBolt::removeBullet, this)),
		NULL));


	/*runAction(Sequence::create(bulletAction,
	CallFuncN::create(CC_CALLBACK_0(Bomb::removeBullet, this)),
	NULL));
	*/
}

void MageBolt::shoot(BaseMonster * target)
{
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



