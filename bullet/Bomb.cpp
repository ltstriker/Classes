#include "Bomb.h"
void Bomb::initBombAnimation()
{
	if (AnimationCache::getInstance()->getAnimation("bomb") != nullptr) {
		return;
	}
	// not be initialized
	int start = 5061;
	int end = 5081;
	int num = (end - num) / 2 + 1;
	Animation* bomb = Animation::create();
	for (int i = 0; i < num; i++) {
		int index = start + i * 2;
		char *bf = new char[50];
		sprintf(bf,"/bullet/image %d.png", index);
		const std::string filename = bf;
		auto sf = SpriteFrame::create(filename, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 100, 100)));
		bomb->addSpriteFrame(sf);
	}
	bomb->setDelayPerUnit(2.0f / num);
	bomb->setRestoreOriginalFrame(false);
	AnimationCache::getInstance()->addAnimation(bomb, "bomb");
}
Bomb* Bomb::createBombWithType(int level)
{
	auto bomb = new Bomb();
	initBombAnimation();
	if (bomb && bomb->initWithType(level))
	{
		bomb->autorelease();
		return bomb;
	}
	CC_SAFE_DELETE(bomb);
	return NULL;
}

bool Bomb::initWithType(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (type)
	{
	case(1): {
		sprite = Sprite::create("/bullet/image 5092.png");
		setMaxForce(20);
	}
			 break;
	case(2): {
		sprite = Sprite::create("/bullet/bomb_level2.png");
		setMaxForce(30);
	}
			 break;
	case(3): {
		sprite = Sprite::create("/bullet/bomb_level3.png");
		setMaxForce(40);
	}
			 break;
	case(4): {
		sprite = Sprite::createWithSpriteFrameName("/bullet/bomb_level2.png");
		setMaxForce(30);
	}
			 break;
	}
	addChild(sprite);
	return true;
}

void Bomb::shoot()
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
	auto mt = ParabolaTo::create(0.5f, (CCPoint)getPosition(), (CCPoint)(dist - getParent()->getPosition()));
	auto rtt = RotateWithAction::create(0.5);

	auto bulletAction0 = Spawn::create(mt, rtt, NULL);
	runAction(Sequence::create(bulletAction0,
		CallFuncN::create(CC_CALLBACK_0(Bomb::removeBullet, this)),
		NULL));

}




void Bomb::removeBullet()
{
	auto instance = GameManager::getInstance();

	auto bombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if (monster != NULL && bombPostion.distance(monsterPosition) <= 50 && monster->getAttackBySoldier())
		{
			 
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getMaxForce() + monster->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPercentage((currHp / monster->getMaxHp()) * 100);

			if (currHp == 0) {
				monster->explosion();
			}
		}
	}
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("bomb")),
		CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
		, NULL));
}

