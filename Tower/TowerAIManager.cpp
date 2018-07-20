#include "TowerAIManager.h"

#include "ArrowTowerV1.h"
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
	/*this->terrainVector = vec;
	for each (KRTerrain* t in terrainVector)
	{
		//make menu unable
	}*/
	isAble = true;
}

void TowerAIManager::update()
{

}


