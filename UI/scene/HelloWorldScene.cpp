#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "TransitionGame.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	
	preLoad();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("/pictures/image 3245.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	Size mywinsize = Director::getInstance()->getWinSize();
	float winh = mywinsize.height;//获取屏幕高度
	float spy = background->getTextureRect().getMaxY();
	background->setScaleY(winh / spy); //设置精灵高度缩放比例
	this->addChild(background, 0);

	auto game_label = Sprite::create("/pictures/image 3289.png");
	game_label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 150));
	this->addChild(game_label, 0);

	auto startItem = MenuItemImage::create(
		"/pictures/image 3262.png",
		"/pictures/image 3266.png",
		CC_CALLBACK_1(HelloWorld::startMenuCallback, this));
	startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	startItem->setScaleY(1.5);
	startItem->setScaleX(1.5);
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
 
    return true;
}


void HelloWorld::startMenuCallback(cocos2d::Ref* pSender)
{
	auto scene = GameScene::playGame(0, 0);
	Director::getInstance()->replaceScene(TransitionGame::create(1.0f, scene));
}

void HelloWorld::preLoad()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_a_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a_3-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("towers-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na_2_IPAD2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_campaign_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_iron_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_heroic_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cinematics_comic1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert_3-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level6-hd.plist");
}