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


