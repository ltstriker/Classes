#include "Level1.h"
#include "../../Tower/TowerAIManager.h"
#include "../GameManager.h"
USING_NS_CC;

Level1::Level1()
{
};

Level1::~Level1(){};

bool Level1::initWithDifficulty(int difficulty)
{
	 
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level1_2-hd.plist");
	setLevel(1);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	//road 0提示
	points.push_back(Point(980,40));
	//road 1 提示
	points.push_back(Point(40,270));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();

	return true;
}

Level1* Level1::createGame(int difficulty)
{  
	 
   auto layer = new Level1();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level1::addOrnament()
{

}

/*void Level1::onExit()
{
	 
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level1_2-hd.plist");
}*/

/*void Level1::addTerrains()
{
	auto terrain1 = KRTerrain::createTerrain(1);
	terrain1->setPosition(Point(455,535));//终点左一
	terrain1->setTag(1);
	addChild(terrain1,2);

	auto terrain13 = KRTerrain::createTerrain(1);
	terrain13->setPosition(Point(340,520));//终点左二
	terrain13->setTag(13);
	addChild(terrain13,3);

	auto terrain12 = KRTerrain::createTerrain(1);
	terrain12->setPosition(Point(655, 470));//水桶右上
	terrain12->setTag(12);
	addChild(terrain12,4);

	auto terrain3 = KRTerrain::createTerrain(1);
	terrain3->setPosition(Point(430,395));//水桶左上
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain10 = KRTerrain::createTerrain(1);
	terrain10->setPosition(Point(440,310));//水桶左下
	terrain10->setTag(10);
	addChild(terrain10,5);

	auto terrain7 = KRTerrain::createTerrain(1);
	terrain7->setPosition(Point(445,180));//三角交汇处右下
	terrain7->setTag(7);
	addChild(terrain7,6);

	auto terrain9 = KRTerrain::createTerrain(1);
	terrain9->setPosition(Point(200,320));//假山下
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain6 = KRTerrain::createTerrain(1);
	terrain6->setPosition(Point(740,290));//与牛角旁拐角相对
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain2 = KRTerrain::createTerrain(1);
	terrain2->setPosition(Point(160,120));//假山旁第一拐角
	terrain2->setTag(2);
	addChild(terrain2,7);

	auto terrain8 = KRTerrain::createTerrain(1);
	terrain8->setPosition(Point(140,240));//与假山旁1
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain4 = KRTerrain::createTerrain(1);
	terrain4->setPosition(Point(280,200));//圆环旁拐角
	terrain4->setTag(4);
	addChild(terrain4,7);

	auto terrain5 = KRTerrain::createTerrain(1);
	terrain5->setPosition(Point(810,140));//牛角旁拐角
	terrain5->setTag(5);
	addChild(terrain5,8);

	auto terrain11 = KRTerrain::createTerrain(1);
	terrain11->setPosition(Point(420,100));//圆环旁拐角下
	terrain11->setTag(11);
	addChild(terrain11,8);


}*/

void Level1::addTerrains()
{
	GameManager::getInstance()->terrain_vector.clear();
	auto terrain1 = KRTerrain::createTerrain(1);
	terrain1->setPosition(Point(610, 820));
	terrain1->setTag(1);
	addChild(terrain1, 2);
	GameManager::getInstance()->terrain_vector.pushBack(terrain1);

	auto terrain13 = KRTerrain::createTerrain(1);
	terrain13->setPosition(Point(340, 750));
	terrain13->setTag(13);
	addChild(terrain13, 3);
	GameManager::getInstance()->terrain_vector.pushBack(terrain13);

	auto terrain12 = KRTerrain::createTerrain(1);
	terrain12->setPosition(Point(650, 650));
	terrain12->setTag(12);
	addChild(terrain12, 4);
	GameManager::getInstance()->terrain_vector.pushBack(terrain12);

	auto terrain3 = KRTerrain::createTerrain(1);
	terrain3->setPosition(Point(535, 620));
	terrain3->setTag(3);
	addChild(terrain3, 4);
	GameManager::getInstance()->terrain_vector.pushBack(terrain3);

	auto terrain10 = KRTerrain::createTerrain(1);
	terrain10->setPosition(Point(540, 560));
	terrain10->setTag(10);
	addChild(terrain10, 5);
	GameManager::getInstance()->terrain_vector.pushBack(terrain10);

	auto terrain7 = KRTerrain::createTerrain(1);
	terrain7->setPosition(Point(590, 460));
	terrain7->setTag(7);
	addChild(terrain7, 6);
	GameManager::getInstance()->terrain_vector.pushBack(terrain7);

	auto terrain9 = KRTerrain::createTerrain(1);
	terrain9->setPosition(Point(310, 440));
	terrain9->setTag(9);
	addChild(terrain9, 6);
	GameManager::getInstance()->terrain_vector.pushBack(terrain9);


	auto terrain6 = KRTerrain::createTerrain(1);
	terrain6->setPosition(Point(900, 440));
	terrain6->setTag(6);
	addChild(terrain6, 6);
	GameManager::getInstance()->terrain_vector.pushBack(terrain6);

	auto terrain2 = KRTerrain::createTerrain(1);
	terrain2->setPosition(Point(380, 360));
	terrain2->setTag(2);
	addChild(terrain2, 7);
	GameManager::getInstance()->terrain_vector.pushBack(terrain2);


	auto terrain8 = KRTerrain::createTerrain(1);
	terrain8->setPosition(Point(250, 360));
	terrain8->setTag(8);
	addChild(terrain8, 7);
	GameManager::getInstance()->terrain_vector.pushBack(terrain8);

	auto terrain4 = KRTerrain::createTerrain(1);
	terrain4->setPosition(Point(590, 300));
	terrain4->setTag(4);
	addChild(terrain4, 7);
	GameManager::getInstance()->terrain_vector.pushBack(terrain4);

	auto terrain5 = KRTerrain::createTerrain(1);
	terrain5->setPosition(Point(920, 260));
	terrain5->setTag(5);
	addChild(terrain5, 8);
	GameManager::getInstance()->terrain_vector.pushBack(terrain5);

	auto terrain11 = KRTerrain::createTerrain(1);
	terrain11->setPosition(Point(530, 220));
	terrain11->setTag(11);
	addChild(terrain11, 8);
	GameManager::getInstance()->terrain_vector.pushBack(terrain11);


	if (GameManager::getInstance()->mode == true)
	{
		TowerAIManager::getInstance()->initAI();
		schedule(schedule_selector(Level1::Update), 1.0f);
	}
	else
	{
		unschedule(schedule_selector(Level1::Update));
	}
}

void Level1::Update(float dt)
{
	TowerAIManager::getInstance()->update();
}