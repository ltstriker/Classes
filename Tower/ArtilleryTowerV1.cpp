#include "ArtilleryTowerV1.h"
#include "../UI/UpdatePanleLayer.h"
#include "../UI/GameManager.h"
#include "../UI/map/BaseMap.h"

bool ArtilleryTowerV1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARTILLERY_1);
	setLevel(1);
	addTerrain();
	buildingAnimation();

	setScope(160.0f);
	setUpdateMoney(150);
	setBuildMoney(120);
	isUpdateMenuShown = false;
	return true;
}

void ArtilleryTowerV1::buildingAnimation()
{
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("tower_constructing_0001.png");
	auto hpBgSprite = Sprite::createWithSpriteFrameName("buildbar_bg.png");
	hpBgSprite->setPosition(Point(constructing->getContentSize().width / 2, constructing->getContentSize().height / 2 + 10));
	auto hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(0);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
	constructing->addChild(hpBgSprite);
	building->addChild(constructing);
	addChild(building);

	hpBar->runAction(Sequence::create(ProgressTo::create(0.5f, 100)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, building))
		, NULL));
	scheduleOnce(schedule_selector(ArtilleryTowerV1::buildingSmokeAnimation), 0.5f);
}

void ArtilleryTowerV1::buildingSmokeAnimation(float dt)
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	addChild(smoke, 99);
	smoke->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("build_smoke")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)), NULL));
	//SoundManager::playArtilleryReady();
	initTower(1);
	setListener();

	schedule(schedule_selector(ArtilleryTowerV1::shoot), 3.0f);
}

void ArtilleryTowerV1::updateTower()
{
	//cannot

	/*auto simpleArtilleryTowerlvl2 = SimpleArtilleryTowerlvl2::create();
	simpleArtilleryTowerlvl2->setMyTerrain(myTerrain);
	simpleArtilleryTowerlvl2->setTag(myTerrain->getTag());
	simpleArtilleryTowerlvl2->setPosition(Point(0, 20));
	myTerrain->addChild(simpleArtilleryTowerlvl2);
	this->removeTower();*/
}

void ArtilleryTowerV1::showUpdateMenu()
{
	if (TowerAIManager::getInstance()->getAble())
	{
		return;
	}

	auto updatePanleLayer = UpdatePanleLayer::create();
	CCLOG(std::to_string(myTerrain->getTag()).c_str());
	updatePanleLayer->setTag(myTerrain->getTag() + 100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	if (GameManager::getInstance()->LEVEL == 0) {
		updatePanleLayer->couldUpdate = false;
	}
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}