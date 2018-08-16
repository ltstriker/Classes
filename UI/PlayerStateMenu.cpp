#include "PlayerStateMenu.h"
#include "GameOption.h"
#include "GameManager.h"
#include "map/BaseMap.h"
#include "../Monster/Desert/Thug.h"
#include "../Monster/Desert/Fallen.h"
#include "../Monster/Desert/Wolf.h"
#include "../Monster/Desert/Immortal.h"
#include "../Monster/Desert/Raider.h"
#include "../Monster/Boss/Boss_Efreeti.h"
 
//#include "TowerInfoLayer.h"
//#include "MonsterInfoLayer.h"

bool PlayerStateMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

//	std::vector<std::vector<std::vector<Point>>> path1;
	auto plistDic = Dictionary::createWithContentsOfFile(String::createWithFormat("level1_paths.plist")->getCString());

	auto path_array = dynamic_cast<__Array*>(plistDic->objectForKey("paths"));

	for (int i = 0; i < path_array->count(); i++)
	{
		std::vector<std::vector<Point>> tempPathVector;
		auto path_array2 = dynamic_cast<__Array*>(path_array->getObjectAtIndex(i));
		for (int j = 0; j < path_array2->count(); j++)
		{
			std::vector<Point> tempRandomPathVector;
			auto path_array3 = dynamic_cast<__Array*>(path_array2->getObjectAtIndex(j));
			for (int k = 0; k < path_array3->count(); k++)
			{
				auto tempDic = dynamic_cast<__Dictionary*>(path_array3->getObjectAtIndex(k));
				Point tempPath = Point();
				tempPath.x = dynamic_cast<__String*>(tempDic->objectForKey("x"))->floatValue()*1.15;
				tempPath.y = dynamic_cast<__String*>(tempDic->objectForKey("y"))->floatValue()*1.20 + 50;
				tempRandomPathVector.push_back(tempPath);
			}
			tempPathVector.push_back(tempRandomPathVector);
		}
		path1.push_back(tempPathVector);
	}

	isFrozen = false;
	instance = GameManager::getInstance();
	stateSprite = Sprite::createWithSpriteFrameName("hud_background.png");
	stateSprite->setAnchorPoint(Point(0,1));
	stateSprite->setPosition(Point(20,Director::getInstance()->getWinSize().height - 20 + 100));
	addChild(stateSprite);
	
	lifeLabel = Label::createWithTTF("0","arial.ttf",20);
	lifeLabel->setPosition(Point(stateSprite->getContentSize().width/4,stateSprite->getContentSize().height/4*3));
	stateSprite->addChild(lifeLabel);

	goldLabel = Label::createWithTTF("0","arial.ttf",20);
	goldLabel->setPosition(Point(stateSprite->getContentSize().width/4*3,stateSprite->getContentSize().height/4*3));
	stateSprite->addChild(goldLabel);

	waveLabel = Label::createWithTTF("","arial.ttf",20);
	waveLabel->setPosition(Point(stateSprite->getContentSize().width/2,stateSprite->getContentSize().height/4));
	stateSprite->addChild(waveLabel);

	pause = Sprite::createWithSpriteFrameName("hud_buttons_0001.png");
	pause->setAnchorPoint(Point(1,1));
	pause->setPosition(Point(Director::getInstance()->getWinSize().width - 20,Director::getInstance()->getWinSize().height - 20 + 100));
	addChild(pause);

	//zhanglei-��չ�Ĺ������ܣ���ʯ��ɡ�������� 
	thunderStoneSprite = Sprite::createWithSpriteFrameName("power_portrait_fireball_0001.png");
	thunderStoneSprite->setAnchorPoint(Point(0,0));
	thunderStoneSprite->setPosition(Point(10,-20));
	thunderStoneSprite->setName("inactive");
	completeThunder = false;
	addChild(thunderStoneSprite,1);

	paratrooperSprite = Sprite::createWithSpriteFrameName("power_portrait_reinforcement_0001.png");
	paratrooperSprite->setAnchorPoint(Point(0,0));
	paratrooperSprite->setPosition(Point(120,-20));
	paratrooperSprite->setName("inactive");
	completeParatrooper = false;
	addChild(paratrooperSprite,1);

	packSprite = Sprite::createWithSpriteFrameName("power_portrait_backpack_0001.png");
	packSprite->setAnchorPoint(Point(1,0));
	packSprite->setPosition(Point(Director::getInstance()->getWinSize().width - 10,-20));
	packSprite->setName("inactive");
	addChild(packSprite,1);
	//���ұ���
	backPackSprite = Sprite::createWithSpriteFrameName("backPack_hover.png");
	backPackSprite->setAnchorPoint(Point(1,0));
	backPackSprite->setPosition(Point(Director::getInstance()->getWinSize().width - 60,30));
	backPackSprite->setVisible(false);
	addChild(backPackSprite,-1);
	auto backPackSpritelistener = EventListenerTouchOneByOne::create();
	backPackSpritelistener->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode) && backPackSprite->isVisible() )
		{  
			
			return true;  
		}  
		return false;  
	};
	backPackSpritelistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backPackSpritelistener,backPackSprite);
	//��������

	for(int i = 0; i <  6; i ++){
		int num = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(instance->SLOTX_SHOP,i)->getCString());
		switch (i)
		{
			case(0): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("desertThug_0001.png"); }break;
			case(1): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("desertRaider_0001.png"); }break;
			case(2): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("desertWolf_0001.png"); }break;
			case(3): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("desertImmortal_0001.png"); }break;
			case(4): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("fallen_0001.png"); }break;
			case(5): {backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName("fallen_0001.png"); }break;
		}
		
		backPack_icons_Sprite[i]->setAnchorPoint(Point(1,0));
		backPack_icons_Sprite[i]->setPosition(Point(540 - 85 * i,0));

		backPack_icons_Sprite[i]->setTag(i);
		backPack_icons_Sprite[i]->setName(String::createWithFormat(instance->SLOTX_SHOP,i)->getCString());
		backPackSprite->addChild(backPack_icons_Sprite[i],0);

		auto numLeft = Label::createWithTTF(String::createWithFormat("%d",num)->getCString(),"arial.ttf",20);
		numLeft->setPosition(Point(backPack_icons_Sprite[i]->getContentSize().width/4*3,backPack_icons_Sprite[i]->getContentSize().height/4));
		numLeft->setTag(101);
		backPack_icons_Sprite[i]->addChild(numLeft);
	}

	//����ʱͼ��
	stoneTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	stoneTimer->setAnchorPoint(Point(0,0));
	stoneTimer->setReverseDirection(true);
	stoneTimer->setPosition(Point(10,-20));
	stoneTimer->setPercentage(100);//��ʾԭ�εİٷֱ�
	this->addChild(stoneTimer,1,100);
	

	paratrooperTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	paratrooperTimer->setReverseDirection(true);
	paratrooperTimer->setAnchorPoint(Point(0,0));
	paratrooperTimer->setPosition(Point(120,-20));
	paratrooperTimer->setPercentage(100);//��ʾԭ�εİٷֱ�
	this->addChild(paratrooperTimer,1,200);

	//zhanglei-end

	auto pause_listener = EventListenerTouchOneByOne::create();
	pause_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  
			 
			return true;  
		}  
		return false;  
	};
	pause_listener->onTouchEnded = [&](Touch* touch, Event* event){
		if(packSprite->getName() == "active"){
			packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
			packSprite->setName("inactive");
			backPackSprite->setVisible(false);
		}
		removeTowerInfo();
		removeMonsterInfo();
		addGameOption();
	};
	pause_listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pause_listener,pause);

	//zhanglei-begin
	//������ʯ
	auto stoneListener = EventListenerTouchOneByOne::create();
	stoneListener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		//�����
		if(rect.containsPoint(locationInNode)){
			//����ȴ����
			if(completeThunder == true){
//				mTouchLayer->removeAllListener();
				if(thunderStoneSprite->getName() == "inactive"){
					//����Ϊ���״̬
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0002.png"));
					//�ı�״̬TAG
					thunderStoneSprite->setName("active");
					//�ı�����2������״̬
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
					paratrooperSprite->setName("inactive");
					packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
					packSprite->setName("inactive");
					backPackSprite->setVisible(false);
//					mTouchLayer->setFireBallTouchShield();
				//�ڶ��ε��
				}else{
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
					thunderStoneSprite->setName("inactive");
				}
			}
			return true;
		}
		return false;  
	};

	stoneListener->onTouchEnded = [&](Touch* touch, Event* event){
	};
	stoneListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(stoneListener,thunderStoneSprite);
	//����ɡ��
	auto paratrooperListener = EventListenerTouchOneByOne::create();
	paratrooperListener->onTouchBegan = [&](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		
		if(rect.containsPoint(locationInNode)){
			if(completeParatrooper == true){
//				mTouchLayer->removeAllListener();
				if(paratrooperSprite->getName() == "inactive"){
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0002.png"));
					paratrooperSprite->setName("active");
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
					thunderStoneSprite->setName("inactive");
					packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
					packSprite->setName("inactive");
					backPackSprite->setVisible(false);
//					mTouchLayer->setSoldierTouchShield();
				}else{
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
					paratrooperSprite->setName("inactive");
				}
			}
			return true;
		}
		return false;
	};
	paratrooperListener->onTouchEnded = [&](Touch* touch, Event* event){

	};
	paratrooperListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(paratrooperListener,paratrooperSprite);
	//��������
	if (GameManager::getInstance()->mode == true)
	{ 
		auto packListener = EventListenerTouchOneByOne::create();
		packListener->onTouchBegan = [&](Touch* touch, Event* event){

			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertTouchToNodeSpace(touch);
			Size size = target->getContentSize();
			Rect rect = Rect(0, 0, size.width, size.height);
			if (rect.containsPoint(locationInNode) && packSprite->getName() == "inactive"){  
				removeTowerInfo();
				removeMonsterInfo();
	//			mTouchLayer->removeAllListener();
				packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0002.png"));
				packSprite->setName("active");
				backPackSprite->setVisible(true);
				if(thunderStoneSprite->getName() == "active" || paratrooperSprite->getName() == "active"){
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
					thunderStoneSprite->setName("inactive");
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
					paratrooperSprite->setName("inactive");
				}
				return true;  
			}
			if(rect.containsPoint(locationInNode) && packSprite->getName() == "active"){
				packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
				packSprite->setName("inactive");
				backPackSprite->setVisible(false);
			}
			return false;  
		};
		packListener->setSwallowTouches(true);
		paratrooperListener->onTouchEnded = [&](Touch* touch, Event* event){
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(packListener,packSprite);

	//�������������

	
		auto skillListener = EventListenerTouchOneByOne::create();
		skillListener->onTouchBegan = [&](Touch* touch, Event* event) {

			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertTouchToNodeSpace(touch);
			Size size = target->getContentSize();
			Rect rect = Rect(0, 0, size.width, size.height);
			if (rect.containsPoint(locationInNode) && backPackSprite->isVisible()) {
				/*
					int num = UserDefault::getInstance()->getIntegerForKey(target->getName().c_str());
					if(num <= 0){
						UserDefault::getInstance()->setIntegerForKey(target->getName().c_str(),0);
						target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Boss_Efreeti_0001.png"));
						static_cast<Label*>(target->getChildByTag(101))->setString("0");
						packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
						packSprite->setName("inactive");
						backPackSprite->setVisible(false);
					}else{
						num--;
						static_cast<Label*>(target->getChildByTag(101))->setString(String::createWithFormat("%d",num)->getCString());
						UserDefault::getInstance()->setIntegerForKey(target->getName().c_str(),num);
						*/
				shopSkill(target->getTag());
				/*
								if(num<=0){
									target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Boss_Efreeti_0001.png"));
									target->setAnchorPoint(Point(1,0));
									static_cast<Label*>(target->getChildByTag(101))->setString("0");
								}
								packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
								packSprite->setName("inactive");
								backPackSprite->setVisible(false);*/
								//}
				return true;
			}
			return false;
		};
		skillListener->onTouchEnded = [&](Touch* touch, Event* event) {
		};
		skillListener->setSwallowTouches(true);
		for (int i = 0; i < 6; i++) {
			_eventDispatcher->addEventListenerWithSceneGraphPriority(skillListener->clone(), backPack_icons_Sprite[i]);
		}
	}
	return true;
}

void PlayerStateMenu::initGameOption()
{
	gameOption = GameOption::create();
	gameOption->level = getLevel();
	gameOption->difficult = getDifficult();
	gameOption->setPosition(Point(0,
		Director::getInstance() -> getVisibleSize().height));
	addChild(gameOption,99);
}

void PlayerStateMenu::addGameOption()
{
	auto color = LayerColor::create(Color4B(0, 0, 0, 60), Director::getInstance() -> getVisibleSize().width, Director::getInstance() -> getVisibleSize().height);
	color->setTag(501);
	addChild(color);
	auto gameOptionListener = EventListenerTouchOneByOne::create();
	gameOptionListener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	gameOptionListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(gameOptionListener,color);
	gameOption->runAction(
		Sequence::create(MoveBy::create(0.2f,Point(0,-Director::getInstance() -> getVisibleSize().height)),
		CallFuncN::create(CC_CALLBACK_0(PlayerStateMenu::pauseGame, this)),NULL));
}

void PlayerStateMenu::removeGameOption()
{
	Director::getInstance()->resume();
	gameOption->runAction(MoveBy::create(0.2f,Point(0,Director::getInstance() -> getVisibleSize().height)));
	removeChildByTag(501);
}

void PlayerStateMenu::pauseGame()
{
	Director::getInstance()->pause();
}

void PlayerStateMenu::startProgressTimers()
{
	this->schedule(schedule_selector(PlayerStateMenu::updateStoneProgress));//����ʵ����������½���.
	this->schedule(schedule_selector(PlayerStateMenu::updateParatrooperProgress));//����ʵ����������½���.
}

void PlayerStateMenu::startStone()
{
	completeThunder = false;
	thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
	thunderStoneSprite->setName("inactive");
	stoneTimer->setPercentage(100.0f);
	this->unschedule(schedule_selector(PlayerStateMenu::updateStoneProgress));
	this->schedule(schedule_selector(PlayerStateMenu::updateStoneProgress));
}

void PlayerStateMenu::showTowerInfo(TowerType towerType)
{
/*	removeChildByTag(MONSTER_INFO);
	removeChildByTag(TOWER_INFO);
	packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
	packSprite->setName("inactive");
	backPackSprite->setVisible(false);
	auto towerInfoLayer = TowerInfoLayer::createTowerInfoLayer(towerType);
	towerInfoLayer->setTag(TOWER_INFO);
	addChild(towerInfoLayer);
	towerInfoLayer->setAnchorPoint(Point(0,0));
	towerInfoLayer->setPosition(Point(620,-50));
	towerInfoLayer->runAction(MoveBy::create(0.2f,Point(0,100)));*/
}

void PlayerStateMenu::removeTowerInfo()
{
	//removeChildByTag(TOWER_INFO);
}

void PlayerStateMenu::showMonsterInfo(BaseMonster* monster)
{
/*	removeChildByTag(TOWER_INFO);
	removeChildByTag(MONSTER_INFO);
	packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
	packSprite->setName("inactive");
	backPackSprite->setVisible(false);
	auto monsterInfoLayer = MonsterInfoLayer::createMonsterInfoLayer(monster);
	monsterInfoLayer->setTag(MONSTER_INFO);
	addChild(monsterInfoLayer);
	monsterInfoLayer->setAnchorPoint(Point(0,0));
	monsterInfoLayer->setPosition(Point(620,-50));
	monsterInfoLayer->runAction(MoveBy::create(0.2f,Point(0,100)));*/
}

void PlayerStateMenu::removeMonsterInfo()
{
	//removeChildByTag(MONSTER_INFO);
}

void PlayerStateMenu::startParatrooper()
{
	completeParatrooper = false;
	paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
	paratrooperSprite->setName("inactive");
	paratrooperTimer->setPercentage(100.0f);
	this->unschedule(schedule_selector(PlayerStateMenu::updateParatrooperProgress));
	this->schedule(schedule_selector(PlayerStateMenu::updateParatrooperProgress));
}

void PlayerStateMenu::setLife(int life)
{
	lifeLabel->setString(String::createWithFormat("%d",life)->getCString());
}

void PlayerStateMenu::setGold(int gold)
{
	goldLabel->setString(String::createWithFormat("%d",gold)->getCString());
}

void PlayerStateMenu::setWave(int thisWave,int totalWave)
{
	waveLabel->setString(String::createWithFormat("WAVE %d/%d",thisWave,totalWave)->getCString());
}

void PlayerStateMenu::onEnterTransitionDidFinish()
{
	stateSprite->runAction(MoveBy::create(0.2f,Point(0,-100)));
	pause->runAction(MoveBy::create(0.2f,Point(0,-100)));

}

//zhanglei-Բ�ε���ʱ������-��ʯ
void PlayerStateMenu::updateStoneProgress(float Dt){  
	stoneTimer->setPercentage(stoneTimer->getPercentage() - Dt*2);//���½���2
	if (stoneTimer->getPercentage()==0) {
		this->unschedule(schedule_selector(PlayerStateMenu::updateStoneProgress));//ȡ����ʱ��
		completeThunder = true;
	}
	return;
}
//zhanglei-Բ�ε���ʱ������-ɡ��
void PlayerStateMenu::updateParatrooperProgress(float Dt){ 
	paratrooperTimer->setPercentage(paratrooperTimer->getPercentage() - Dt*5);//���½���5
	if (paratrooperTimer->getPercentage()==0) {
		this->unschedule(schedule_selector(PlayerStateMenu::updateParatrooperProgress));//ȡ����ʱ��
		completeParatrooper = true;
	}
	return;
}

void PlayerStateMenu::clearMonsters()
{
	auto monstersVector = GameManager::getInstance()->monsterVector;

	for(int i = 0;i<monstersVector.size();i++){
		auto monster = monstersVector.at(i);
		if(monster!=NULL){
			monster->explosion();
			//instance->monsterVector.eraseObject(monster);
		}
	}
}

void PlayerStateMenu::shopSkill(int type)
{
//	float dt = 1;
//	BaseMap::getinstance()->addMonstersPlus(dt, type);
/*	std::vector<std::vector<std::vector<Point>>> path1;
	auto plistDic = Dictionary::createWithContentsOfFile(String::createWithFormat("level1_paths.plist")->getCString());

	auto path_array = dynamic_cast<__Array*>(plistDic->objectForKey("paths"));

	for (int i = 0; i < path_array->count(); i++)
	{
		std::vector<std::vector<Point>> tempPathVector;
		auto path_array2 = dynamic_cast<__Array*>(path_array->getObjectAtIndex(i));
		for (int j = 0; j < path_array2->count(); j++)
		{
			std::vector<Point> tempRandomPathVector;
			auto path_array3 = dynamic_cast<__Array*>(path_array2->getObjectAtIndex(j));
			for (int k = 0; k < path_array3->count(); k++)
			{
				auto tempDic = dynamic_cast<__Dictionary*>(path_array3->getObjectAtIndex(k));
				Point tempPath = Point();
				tempPath.x = dynamic_cast<__String*>(tempDic->objectForKey("x"))->floatValue()*1.15;
				tempPath.y = dynamic_cast<__String*>(tempDic->objectForKey("y"))->floatValue()*1.20 + 50;
				tempRandomPathVector.push_back(tempPath);
			}
			tempPathVector.push_back(tempRandomPathVector);
		}
		path1.push_back(tempPathVector);
	}

	BaseMap::getinstance()->loadPathFromPlist();
	BaseMap::getinstance()->loadAndSetLevelData();
	int wave = BaseMap::getinstance()->wave;
	int time = BaseMap::getinstance()->time;
*/
//	auto monsterData = BaseMap::getinstance()->waveVector.at(0).at(0).at(1);
	
	switch (type)
	{
		case (0):
		{
			auto thug = Thug::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(thug);
				GameManager::getInstance()->monsterVector.pushBack(thug);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
		case (1):
		{
			auto raider = Raider::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(raider);
				GameManager::getInstance()->monsterVector.pushBack(raider);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
		case (2):
		{			
			auto wolf = Wolf::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(wolf);
				GameManager::getInstance()->monsterVector.pushBack(wolf);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
		case (3):
		{
			auto immortal = Immortal::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(immortal);
				GameManager::getInstance()->monsterVector.pushBack(immortal);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
		case (4):
		{
			auto fallen = Fallen::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(fallen);
				GameManager::getInstance()->monsterVector.pushBack(fallen);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
		case (5):
		{
			auto fallen = Fallen::createMonster(path1.at(1).at(2));
			if (GameManager::getInstance()->MONEY > 0)
			{
				addChild(fallen);
				GameManager::getInstance()->monsterVector.pushBack(fallen);
			}
			else
			{
				GameManager::getInstance()->MONEY = 0;
			}
		}
		break;
	}

//	auto monsterData = BaseMap::getinstance()->waveVector.at(wave).at(time).at(1);

/*	for (int i = 0; i < path1.size(); i++)
	{
		for (int j = 0; j < path1[i].size(); j++)
		{
			for (int k = 0; k < path1[i][j].size(); k++)
			{
				 
			}
		}
	}*/
/*	if (time < BaseMap::getinstance()->waveVector.at(wave).size()) {
		for (int i = 0; i < BaseMap::getinstance()->waveVector.at(wave).at(time).size(); i++) {

			//auto monsterData = BaseMap::getinstance()->waveVector.at(wave).at(time).at(i);
			auto thug = Thug::createMonster(BaseMap::getinstance()->path.at(monsterData->getRoad()).at(monsterData->getPath()));
			addChild(thug);
		}
	}*/
	
/*	switch(type){
	case(0):{
		auto atomicBomb_plane = Sprite::createWithSpriteFrameName("atomicBomb_plane.png");
		atomicBomb_plane->setPosition(Point(0,Director::getInstance()->getWinSize().height/3*2));
		addChild(atomicBomb_plane);
		atomicBomb_plane->runAction(Sequence::create(
			MoveBy::create(2.0f,Point(Director::getInstance()->getWinSize().width,0)),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, atomicBomb_plane))
			,NULL));
		auto atomicBomb_bomb = Sprite::createWithSpriteFrameName("atomicBomb_bomb.png");
		atomicBomb_bomb->setPosition(Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/3*2-30));
		addChild(atomicBomb_bomb);
		atomicBomb_bomb->setVisible(false);
		atomicBomb_bomb->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible, atomicBomb_bomb,true)),
			MoveBy::create(0.5f,Point(0,-300)),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, atomicBomb_bomb)),
			CallFuncN::create(CC_CALLBACK_0(PlayerStateMenu::clearMonsters, this)),NULL));
		}
		break;
	case(1)://��Χ����
		frozenMonsters();	
		break;
	case(2)://С��Χը��
//		mTouchLayer->removeAllListener();
//		mTouchLayer->setDynamiteTouchShield();
		break;
	case(3)://С��Χ����
//		mTouchLayer->removeAllListener();
//		mTouchLayer->setFreezeTouchShield();
		break;
	case(4)://��������
//		SoundManager::playCash();
		GameManager::getInstance()->LIFE = GameManager::getInstance()->LIFE + 5;
		break;
	case(5)://���ӽ�Ǯ
//		SoundManager::playHearts();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + 500;
		break;
	}*/
}

void PlayerStateMenu::reFrozenMonsters(float dt)
{
	removeChildByTag(301);
	removeChildByTag(302);
	removeChildByTag(303);
	removeChildByTag(304);
	isFrozen = false;
}

void PlayerStateMenu::frozenMonsters()
{
	if(!isFrozen){
		//���Ͻ�
		auto winSize = Director::getInstance()->getWinSize();
		auto ice_corner_1 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_1->setAnchorPoint(Point(1,1));
		ice_corner_1->setPosition(Point(winSize.width,winSize.height));
		//���½�
		auto ice_corner_2 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_2->setFlippedY(true);
		ice_corner_2->setAnchorPoint(Point(1,0));
		ice_corner_2->setPosition(Point(winSize.width,0));
		//���½�
		auto ice_corner_3 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_3->setFlippedX(true);
		ice_corner_3->setFlippedY(true);
		ice_corner_3->setAnchorPoint(Point(0,0));
		ice_corner_3->setPosition(Point(0,0));
		auto ice_corner_4 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_4->setFlippedX(true);
		ice_corner_4->setAnchorPoint(Point(0,1));
		ice_corner_4->setPosition(Point(0,winSize.height));

		ice_corner_1->setTag(301);
		ice_corner_2->setTag(302);
		ice_corner_3->setTag(303);
		ice_corner_4->setTag(304);
		addChild(ice_corner_1);
		addChild(ice_corner_2);
		addChild(ice_corner_3);
		addChild(ice_corner_4);
		isFrozen = true;
		auto monstersVector = GameManager::getInstance()->monsterVector;

		for(int i = 0;i<monstersVector.size();i++){
			auto monster = monstersVector.at(i);
			if(monster!=NULL)
				monster->frozen();
		}
		scheduleOnce(schedule_selector(PlayerStateMenu::reFrozenMonsters),8.0f);
	}else{
		unschedule(schedule_selector(PlayerStateMenu::reFrozenMonsters));
		removeChildByTag(301);
		removeChildByTag(302);
		removeChildByTag(303);
		removeChildByTag(304);
		isFrozen = false;
		frozenMonsters();
	}
}