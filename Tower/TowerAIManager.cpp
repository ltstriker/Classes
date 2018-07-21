#include "TowerAIManager.h"

#include "./ui/map/Level1.h"
#include "TowerAIManager.h"

TowerAIManager* TowerAIManager::_instance;

bool TowerAIManager::getAble()
{
	return isAble;
}

TowerAIManager * TowerAIManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TowerAIManager();
		_instance->isAble = false;
	}
	return _instance;
}

void TowerAIManager::initAI()
{

	isAble = true;
}

void TowerAIManager::update()
{
	static int count = 0;
	auto vec = GameManager::getInstance()->terrain_vector;
	if (count != 0)
		return;

	if (vec.size() == 0)
	{
		return;
	}
	auto p= vec.at(0);
	p->AIAddTower(2);

	count++;
}


