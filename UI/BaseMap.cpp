#include "BaseMap.h"


USING_NS_CC;


void BaseMap::setMapPosition()
{
	Point location = Point();
	auto mapSize = mapSprite->getBoundingBox().size;
	location.x = winSize.width / 2 - mapSize.width / 2;
	location.y = winSize.height / 2 - mapSize.height / 2;
	location.x = MIN(location.x, 0);
	location.x = MAX(location.x, -mapSize.width + winSize.width);
	location.y = MIN(location.y, 0);
	location.y = MAX(location.y, -mapSize.height + winSize.height);
	this->setPosition(location);
}

void BaseMap::initTouchLayer()
{
	//ÉèÖÃ·ÀÓùËþÉý¼¶²Ëµ¥²ã
	mTouchLayer = TouchLayer::create();
	mTouchLayer->setContentSize(mapSprite->getContentSize());
	mTouchLayer->setAnchorPoint(Point(0, 0));
	mTouchLayer->setPosition(Point(0, 0));
	addChild(mTouchLayer, 99);
}

void BaseMap::initMap()
{
	mapSprite = Sprite::createWithSpriteFrameName(String::createWithFormat("Stage_%d.png", level + 1)->getCString());
	mapSprite->setAnchorPoint(Point(0, 0));
	mapSprite->setPosition(Point(0, 0));
	addChild(mapSprite);
	addTerrains();
	initTouchLayer();
	setMapPosition();
}
