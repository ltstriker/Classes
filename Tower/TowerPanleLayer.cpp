#include "TowerPanleLayer.h"

#include "ArrowTowerV1.h"
#include "ArtilleryTowerV1.h"
#include "MagicTowerV1.h"
#include "KRTerrain.h"
#include "../UI/GameManager.h"
#include "../UI/map/BaseMap.h"


bool TowerPanleLayer::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->circle = Circle::create();
	this->addChild(circle);
	this->circle->setVisible(false);

	this->planesprite = Sprite::createWithSpriteFrameName("gui_ring.png");
	this->planesprite->setPosition(Point(0, 0));
	this->planesprite->setScale(0.5f);
	this->addChild(planesprite);

	this->isBuilt = false;
	return true;
}

bool TowerPanleLayer::onTouchBegan(Touch * touch, Event * event)
{
	auto target = static_cast<BaseBuildIcon*>(event->getCurrentTarget());
	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->baseIcon->getContentSize();
	Rect rect = Rect(0 - size.width / 2, 0 - size.height / 2, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (target->getIsSelected())//如果已经选中（第二次按下）
		{
			if (target->getIsAble())//如果钱够用
			{
				int i = target->getType();
				addTower(target->getType());
			}
		}
		else {//第一次按下
			archerIcon->setNotSelected();
			artilleryIcon->setNotSelected();
			barracksIcon->setNotSelected();
			magicIcon->setNotSelected();

			target->setSelected();//设置为选中状态
			addTempTower(target->getType());
		}
		return true;
	}
	return false;
}

void TowerPanleLayer::onTouchEnded(Touch * touch, Event * event)
{
	if (isBuilt)
	{
		removeFromParent();
	}
}

void TowerPanleLayer::inAnimation()
{
	 
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f, 1.0f, 1.0f),
		CallFuncN::create(CC_CALLBACK_0(TowerPanleLayer::addIcons, this)),
		NULL));
}

void TowerPanleLayer::addIcons()
{
	archerIcon = BaseBuildIcon::createIcon(1, 70);
	archerIcon->setMoney(70);
	archerIcon->setPosition(Point(-(planesprite->getContentSize().width / 4 + 20), planesprite->getContentSize().height / 4 + 30));
	addChild(archerIcon);

	artilleryIcon = BaseBuildIcon::createIcon(4, 120);
	artilleryIcon->setPosition(Point(planesprite->getContentSize().width / 4 + 20, -(planesprite->getContentSize().height / 4 + 30)));
	addChild(artilleryIcon);

	barracksIcon = BaseBuildIcon::createIcon(2, 100);
	barracksIcon->setPosition(Point(planesprite->getContentSize().width / 4 + 20, planesprite->getContentSize().height / 4 + 30));
	addChild(barracksIcon);

	magicIcon = BaseBuildIcon::createIcon(3, 100);
	magicIcon->setPosition(Point(-(planesprite->getContentSize().width / 4 + 20), -(planesprite->getContentSize().height / 4 + 30)));
	addChild(magicIcon);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, archerIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), artilleryIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), barracksIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), magicIcon);
}

void TowerPanleLayer::addTempTower(int type)
{
	//建塔时的幻影
	if (tempTower != NULL) {
		removeChild(tempTower, true);
	}
	circle->setVisible(true);

	switch (type)
	{
	case(1): {
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
		tempTower->setPosition(Point(0, 25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_1);}
			 break;
	case(3): {
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_mage.png");
		tempTower->setPosition(Point(0, 10));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MAGE_1);}
			 break;
	case(4): {
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_artillery.png");
		tempTower->setPosition(Point(0, 25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARTILLERY_1);}
			 break;
	default:
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
		tempTower->setPosition(Point(0, 25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_1);
		break;
	}
	addChild(tempTower);
}

void TowerPanleLayer::addTower(int type)
{
	static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();

	switch (type)
	{
	case(2): {
		auto arrowTower = ArrowTowerV1::create();
		arrowTower->setPosition(Point(0, 20));
		arrowTower->setTag(terrain->getTag());
		arrowTower->setMyTerrain(terrain);
		terrain->addChild(arrowTower);
		if (GameManager::getInstance()->mode == false)
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - arrowTower->getBuildMoney();
	}
			 break;
	case(1): {
		auto arrowTower = ArrowTowerV1::create();
		arrowTower->setPosition(Point(0, 20));
		arrowTower->setTag(terrain->getTag());
		arrowTower->setMyTerrain(terrain);
		terrain->addChild(arrowTower);
		if (GameManager::getInstance()->mode == false)
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - arrowTower->getBuildMoney();
	}
			 break;
	case(4): {
		auto artilleryTower = ArtilleryTowerV1::create();
		artilleryTower->setPosition(Point(0, 20));
		artilleryTower->setTag(terrain->getTag());
		artilleryTower->setMyTerrain(terrain);
		terrain->addChild(artilleryTower);
		if (GameManager::getInstance()->mode == false)
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - artilleryTower->getBuildMoney();
	}
			 break;
	case(3): 		
		auto mageTower = MagicTowerV1::create();
		mageTower->setPosition(Point(0, 20));
		mageTower->setTag(terrain->getTag());
		mageTower->setMyTerrain(terrain);
		terrain->addChild(mageTower);
		if(GameManager::getInstance()->mode == false)
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - mageTower->getBuildMoney();
		break;
	}
	
	 
	isBuilt = true;
	terrain->isBuilt = true;
	terrain->terrain->setVisible(false);
	this->setVisible(false);
}
