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

void TowerAIManager::update(KRTerrain* t)
{
	if (!isAble)
	{
		return;
	}
	static int count = 0;
	if (count == 0)
	{
		/*auto vec = l->terrain_vector;
		if (vec.size()==0)
		{
			return;
		}
		auto t = vec.at(0);*/
		t->AIAddTower(1);
		count++;
	}
}


