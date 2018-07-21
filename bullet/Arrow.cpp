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
	//auto sf = SpriteFrame::create("/bullet/arrow_broken.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 500, 500)));
	//sprite->setSpriteFrame(sf);
	//SoundManager::playArrowRelease();
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();
	Node* target = nullptr;
	auto instance = GameManager::getInstance();
	auto tower = this->getParent();
	auto monsterVector = instance->monsterVector;
	double  min_dis = 1000000.0f;
	for (int i = 0; i < monsterVector.size(); i++) {
		auto monster = monsterVector.at(i);
		CCLOG("%d\tmonsters x=%f,y=%f", i,monster->getPosition().x, monster->getPosition().y);
		auto towerPos = tower->getPosition();
		double temp_dis = towerPos.distance(monster->getPosition());
		CCLOG("distance:%f", temp_dis);
		if (temp_dis < min_dis) {
			target = monster;
			min_dis = temp_dis;
			auto spritepos = monster->getPosition();
			CCLOG("hit by min distance = %f",min_dis);
			//CCLOG("target x= %f,y=%f", target->getPosition().x, target->getPosition().y);
		}
	}
	if (target == nullptr) {
		CCLOG("nullptr");
		return;
	}
	if (target == tower) {
		CCLOG("tower == target");
		return;
	}
	target = monsterVector.at(0);
	CCLOG("target x= %f,y=%f", target->getPosition().x, target->getPosition().y);
	//target = tower;
	/*CCLOG("arrow x=%f,y=%f", getPosition().x, getPosition().y);
	//CCLOG("arr")
	CCLOG("target x= %f,y=%f", target->getPosition().x,target->getPosition().y);
	CCLOG("tower x = %f ,y=%f", tower->getPosition().x, tower->getPosition().y);*/
	//auto ccvisi
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto rightup = Vec2(origin.x + visibleSize.width, origin.y +0* visibleSize.height);
	auto dist = tower->convertToNodeSpace(rightup);
	auto mt = ParabolaTo::create(1.0f, (CCPoint)getPosition(), (CCPoint)dist);
	auto rtt = RotateWithAction::create(10.0);

	auto bulletAction0 = Spawn::create(mt, rtt, NULL);
	runAction(Sequence::create(bulletAction0,
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));

	/*runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));*/
}

void Arrow::shoot(Vec2 dist)
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
	auto rtt = RotateWithAction::create(10.0);

	bulletAction = Spawn::create(mt, rtt, NULL);
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));


	/*runAction(Sequence::create(bulletAction,
	CallFuncN::create(CC_CALLBACK_0(Bomb::removeBullet, this)),
	NULL));
	*/
}

void Arrow::shoot(BaseMonster * target)
{
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
		CCLOG("isMissed1");
		auto sfcc = SpriteFrameCache::getInstance();
		//auto sf = sfcc->getSpriteFrameByName("/bullet/arrow_broken.png");
		auto sf = SpriteFrame::create("/bullet/arrow_broken.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 500, 500)));
		auto test = sf == nullptr ? 0 : 1;
		sprite->setSpriteFrame(sf);
		CCLOG("test == %d", test);
		CCLOG("isMissed2");
		sprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}

