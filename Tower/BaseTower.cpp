#include "BaseTower.h"
//#include "Terrain.h"
//#include "TowerPanleLayer.h"
//#include "BaseMap.h"
//#include "GameManager.h"


BaseTower::BaseTower() :isUpdateMenuShown(false)
{

}


BaseTower::~BaseTower()
{
}

void BaseTower::sellTower()
{
	static_cast<KRTerrain*>(this->getParent())->terrain->setVisible(true);
	this->removeTower();
}

void BaseTower::removeTower()
{
	static_cast<BaseMap*>(this->getParent())->playerState->removeTowerInfo();
	static_cast<KRTerrain*>(this->getParent())->smokeEffect();
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	this->removeFromParent();
}

bool BaseTower::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BaseTower::showTowerInfo()
{
}

void BaseTower::checkNearestMonster()
{
	//��ȡ����Ĺ�����й���
	auto instance = GameManager::getInstance();
	auto monsterVector = instance->monsterVector;

	auto min = this->scope;//��ʼ��Ϊ��������

	BaseMonster *monsterTemp = NULL;//��ʼ����ǰ�������

	for (size_t i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		auto distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < min && monster->getAttackByTower())
		{
			min = distance;
			monsterTemp = monster;
		}
	}

	this->checkNearestMonster = monsterTemp;
}

bool BaseTower::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void BaseTower::onTouchEnded(Touch * touch, Event * event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	auto size = target->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		//�ڷ�Χ������෴
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(getTowerType());
		if (isUpdateMenuShown)
		{
			hideUpdateMenu();
		}
		else
		{
			showUpdateMenu();
		}
	}
	else
	{
		//���ڷ�Χ����ֱ�����ؾ�����
		hideUpdateMenu();
	}

}

void BaseTower::hideUpdateMenu()
{
	static_cast<BaseMap*>(this->getParent())->mTouchLayer->removeChildByTag() + 100);
	this->isUpdateMenuShown = false;
}

void BaseTower::setListener()
{
	//���Ӽ�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseTower::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseTower::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
}