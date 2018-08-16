#include "TowerAIManager.h"

#include "./ui/map/Level1.h"
#include "TowerAIManager.h"

TowerAIManager* TowerAIManager::_instance;

int TowerAIManager::count = 0;

bool TowerAIManager::getAble()
{
	return isAble;
}

TowerAIManager * TowerAIManager::getInstance()
{
	if (_instance == nullptr)
	{
		count = 0;
		_instance = new TowerAIManager();
		_instance->isAble = false;
	}
	return _instance;
}

void TowerAIManager::initAI()
{
	count = 0;
	isAble = true;
}

void TowerAIManager::TowerAi_delete()
{
	count = 0;
	isAble = false;

}

void TowerAIManager::update()
{
	auto vec = GameManager::getInstance()->terrain_vector;
	if (count == 0)
	{
		vec.at(8)->AIAddTower(3);
		vec.at(9)->AIAddTower(1);
		vec.at(7)->AIAddTower(4);
	}
	else if (count == 5)
	{
		for (auto i = 0; i < vec.size(); i++)
		{
			if (!vec.at(i)->isBuilt)
			{
				vec.at(i)->AIAddTower(i / 3 + 1);
				break;
			}
		}
	}

	count = count%5 +1;
}


