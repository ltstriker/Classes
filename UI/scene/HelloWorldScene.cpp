#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "TransitionGame.h"
#include "../GameManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

HelloWorld* HelloWorld::instance;

HelloWorld* HelloWorld::getinstance()
{
	if (instance == NULL)
		instance = new HelloWorld();
	return instance;
}

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
	initAction();

	GameManager::getInstance()->mode = false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("/pictures/image 3245.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	Size mywinsize = Director::getInstance()->getWinSize();
	float winh = mywinsize.height;
	float spy = background->getTextureRect().getMaxY();
	float winx = mywinsize.width;
	float spx = background->getTextureRect().getMaxX();
	background->setScaleY(winh / spy); 
	background->setScaleX(winx / spx); 
	this->addChild(background, 0);

	auto game_label = Sprite::create("/pictures/image 3289.png");
	game_label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 150));
	game_label->setScaleY(1.5);
	game_label->setScaleX(1.5);
	this->addChild(game_label, 0);

	auto startItem = MenuItemImage::create(
		"/pictures/image 3262.png",
		"/pictures/image 3266.png",
		CC_CALLBACK_1(HelloWorld::startMenuCallback, this));
	startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	startItem->setScaleY(2);
	startItem->setScaleX(2);
/*	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/
 
	 mode1 = MenuItemImage::create(
		"/pictures/image 1077.png",
		"/pictures/image 1103.png",
		CC_CALLBACK_1(HelloWorld::ChangetoBasicMode, this));
	 mode1->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 - 250));
	 mode1->setScaleY(3);
	 mode1->setScaleX(3);

	 mode2 = MenuItemImage::create(
		"/pictures/image 1077.png",
		"/pictures/image 1127.png",
		CC_CALLBACK_1(HelloWorld::ChangetoAdvMode, this));
	 mode2->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 250));
	 mode2->setScaleY(3);
	 mode2->setScaleX(3);

	auto menu = Menu::create(startItem, mode1, mode2, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void HelloWorld::ChangetoBasicMode(Ref* pSender)
{
	mode1->selected();
	mode2->unselected();
	GameManager::getInstance()->mode = false;
}

void HelloWorld::ChangetoAdvMode(Ref* pSender)
{
	mode1->unselected();
	mode2->selected();
	GameManager::getInstance()->mode = true;
}

void HelloWorld::startMenuCallback(cocos2d::Ref* pSender)
{
	auto scene = GameScene::playGame(1, 0);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/sounds/GameStart.mp3");
	Director::getInstance()->replaceScene(TransitionGame::create(3.0f, scene));
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level10 - hd.plist");
}

void HelloWorld::initAction()
{
	init_ArcherTower();
	init_MageTower();
	init_ArtilleryTower();
	init_BossEfreeti();
	init_BossCanibal();
	init_Thug();
	init_Raider();
	init_Immortal();
	init_Fallen();
	init_Wolf();
	AnimationCache::getInstance()->addAnimation(createAnimation("effect_sellSmoke_00%02d.png", 1, 11, 0.04f), "sell_smoke");
	AnimationCache::getInstance()->addAnimation(createAnimation("effect_buildSmoke_00%02d.png", 1, 10, 0.04f), "build_smoke");
	AnimationCache::getInstance()->addAnimation(createAnimation("fx_blood_splat_red_00%02d.png", 1, 9, 0.04f), "blood_red");
}

void HelloWorld::init_ArtilleryTower()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer1_00%02d.png", 1, 35, 0.04f), "level1_Artillery_towerBase");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer1_00%02d.png", 1, 35, 0.04f), "level2_Artillery_towerBase");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer1_00%02d.png", 1, 35, 0.04f), "level3_Artillery_towerBase");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer2_00%02d.png", 1, 17, 0.04f), "level1_Artillery_leftShooter_hold");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer2_00%02d.png", 1, 17, 0.04f), "level2_Artillery_leftShooter_hold");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer2_00%02d.png", 1, 17, 0.04f), "level3_Artillery_leftShooter_hold");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer3_00%02d.png", 1, 35, 0.04f, "tower_artillery_lvl1_layer3_0001.png"), "level1_Artillery_rightShooter");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer3_00%02d.png", 1, 35, 0.04f, "tower_artillery_lvl2_layer3_0001.png"), "level2_Artillery_rightShooter");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer3_00%02d.png", 1, 35, 0.04f, "tower_artillery_lvl3_layer3_0001.png"), "level3_Artillery_rightShooter");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer4_00%02d.png", 1, 35, 0.04f), "level1_Artillery_barrel");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer4_00%02d.png", 1, 35, 0.04f), "level2_Artillery_barrel");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer4_00%02d.png", 1, 35, 0.04f), "level3_Artillery_barrel");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer5_00%02d.png", 1, 35, 0.04f), "level1_Artillery_smoke");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer5_00%02d.png", 1, 35, 0.04f), "level2_Artillery_smoke");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer5_00%02d.png", 1, 35, 0.04f), "level3_Artillery_smoke");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer6_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl1_layer6_0001.png"), "level1_Artillery_c4");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer6_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl2_layer6_0001.png"), "level2_Artillery_c4");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer6_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl3_layer6_0001.png"), "level3_Artillery_c4");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl1_layer2_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl1_layer2_0001.png"), "level1_Artillery_leftShooter_throw");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl2_layer2_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl2_layer2_0001.png"), "level2_Artillery_leftShooter_throw");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_artillery_lvl3_layer2_00%02d.png", 18, 35, 0.04f, "tower_artillery_lvl3_layer2_0001.png"), "level3_Artillery_leftShooter_throw");

	AnimationCache::getInstance()->addAnimation(createAnimation("explosion_air_00%02d.png", 1, 17, 0.04f), "bomb");
	AnimationCache::getInstance()->addAnimation(createAnimation("states_small_00%02d.png", 22, 32, 0.04f), "explosion_Artillery");
}

void HelloWorld::init_MageTower()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("mage_lvl1_00%02d.png", 1, 12, 0.04f), "level1_mage_shine");
	AnimationCache::getInstance()->addAnimation(createAnimation("mage_lvl2_00%02d.png", 1, 12, 0.04f), "level2_mage_shine");
	AnimationCache::getInstance()->addAnimation(createAnimation("mage_lvl3_00%02d.png", 1, 12, 0.04f), "level3_mage_shine");

	AnimationCache::getInstance()->addAnimation(createAnimation("mage_shooter_00%02d.png", 17, 29, 0.04f, "mage_shooter_0001.png"), "mage_shoot_up");
	AnimationCache::getInstance()->addAnimation(createAnimation("mage_shooter_00%02d.png", 3, 16, 0.04f, "mage_shooter_0001.png"), "mage_shoot_down");
}

void HelloWorld::init_ArcherTower()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl1_shooter_00%02d.png", 3, 10, 0.04f, "tower_archer_lvl1_shooter_0001.png"), "level1_shoot_down");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl2_shooter_00%02d.png", 3, 10, 0.04f, "tower_archer_lvl2_shooter_0001.png"), "level2_shoot_down");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl3_shooter_00%02d.png", 3, 10, 0.04f, "tower_archer_lvl3_shooter_0001.png"), "level3_shoot_down");

	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl3_shooter_00%02d.png", 11, 18, 0.04f, "tower_archer_lvl3_shooter_0002.png"), "level1_shoot_top");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl3_shooter_00%02d.png", 11, 18, 0.04f, "tower_archer_lvl3_shooter_0002.png"), "level2_shoot_top");
	AnimationCache::getInstance()->addAnimation(createAnimation("tower_archer_lvl3_shooter_00%02d.png", 11, 18, 0.04f, "tower_archer_lvl3_shooter_0002.png"), "level3_shoot_top");

}

void HelloWorld::init_BossEfreeti()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 1, 25, 0.04f), "Boss_Efreeti_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 1, 25, 0.04f), "Boss_Efreeti_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 1, 25, 0.04f), "Boss_Efreeti_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 26, 50, 0.04f), "Boss_Efreeti_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 53, 89, 0.04f), "Boss_Efreeti_attack");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 91, 127, 0.1f), "Boss_Efreeti_skill");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_0%03d.png", 130, 211, 0.04f), "Boss_Efreeti_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("Boss_Efreeti_Cloud_0%03d.png", 1, 11, 0.04f), "Boss_Efreeti_cloud");

	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 1, 11, 0.04f), "Efreeti_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 13, 23, 0.04f), "Efreeti_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 1, 11, 0.04f), "Efreeti_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 1, 11, 0.04f), "Efreeti_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 47, 61, 0.04f), "Efreeti_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertEfreeti_0%03d.png", 25, 46, 0.04f), "Efreeti_attack");
}

void HelloWorld::release_BossEfreeti()
{
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_runleft");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_runright");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_runup");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_rundown");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_attack");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_skill");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_death");
	AnimationCache::getInstance()->removeAnimation("Boss_Efreeti_cloud");

	AnimationCache::getInstance()->removeAnimation("Efreeti_runleft");
	AnimationCache::getInstance()->removeAnimation("Efreeti_rundown");
	AnimationCache::getInstance()->removeAnimation("Efreeti_runup");
	AnimationCache::getInstance()->removeAnimation("Efreeti_runright");
	AnimationCache::getInstance()->removeAnimation("Efreeti_death");
	AnimationCache::getInstance()->removeAnimation("Efreeti_attack");
}

void HelloWorld::release_BossCanibal()
{
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_runleft");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_runright");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_runup");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_rundown");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_attack");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_skill_before");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_skill");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_skill_after");
	AnimationCache::getInstance()->removeAnimation("Boss_Canibal_death");

	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_runleft");
	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_rundown");
	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_runup");
	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_runright");
	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_attack");
	AnimationCache::getInstance()->removeAnimation("CanibalBoos_Offspring_death");
}

void HelloWorld::init_BossCanibal()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 1, 31, 0.04f), "Boss_Canibal_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 1, 31, 0.04f), "Boss_Canibal_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 1, 31, 0.04f), "Boss_Canibal_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 33, 62, 0.04f), "Boss_Canibal_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 65, 91, 0.04f), "Boss_Canibal_attack");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 92, 143, 0.1f), "Boss_Canibal_skill_before");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 197, 242, 0.04f), "Boss_Canibal_skill");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 244, 252, 0.04f), "Boss_Canibal_skill_after");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 251, 292, 0.04f), "Boss_Canibal_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_0%03d.png", 184, 197, 0.04f), "Boss_Canibal_jump");

	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 1, 13, 0.04f), "CanibalBoos_Offspring_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 15, 27, 0.04f), "CanibalBoos_Offspring_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 1, 13, 0.04f), "CanibalBoos_Offspring_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 1, 13, 0.04f), "CanibalBoos_Offspring_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 29, 53, 0.04f), "CanibalBoos_Offspring_attack");
	AnimationCache::getInstance()->addAnimation(createAnimation("CanibalBoos_Offspring_0%03d.png", 56, 70, 0.04f), "CanibalBoos_Offspring_death");
}

void HelloWorld::init_Thug()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 89, 106, 0.04f), "Thug_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 23, 44, 0.04f), "Thug_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 45, 66, 0.04f), "Thug_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 1, 22, 0.04f), "Thug_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 1, 22, 0.04f), "Thug_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 67, 88, 0.04f), "Thug_attack");
}

void HelloWorld::init_Raider()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 89, 106, 0.04f), "Raider_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 23, 44, 0.04f), "Raider_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 45, 66, 0.04f), "Raider_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 1, 22, 0.04f), "Raider_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 1, 22, 0.04f), "Raider_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertRaider_0%03d.png", 67, 88, 0.04f), "Raider_attack");
}

void HelloWorld::init_Wolf()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 69, 86, 0.04f), "Wolf_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 11, 30, 0.04f), "Wolf_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 1, 10, 0.04f), "Wolf_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 1, 10, 0.04f), "Wolf_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 1, 10, 0.04f), "Wolf_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertWolf_0%03d.png", 31, 43, 0.04f), "Wolf_attack");
}

void HelloWorld::init_Fallen()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 48, 69, 0.04f), "Fallen_attack");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 70, 110, 0.04f), "Fallen_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 17, 32, 0.04f), "Fallen_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 32, 47, 0.04f), "Fallen_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 1, 16, 0.04f), "Fallen_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 1, 16, 0.04f), "Fallen_runright");
	AnimationCache::getInstance()->addAnimation(createAnimation("fallen_0%03d.png", 114, 146, 0.04f), "Fallen_birth");
}

void HelloWorld::init_Immortal()
{
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 67, 88, 0.04f), "Immortal_attack");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 89, 124, 0.04f), "Immortal_death");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 23, 44, 0.04f), "Immortal_runup");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 45, 66, 0.04f), "Immortal_rundown");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 1, 22, 0.04f), "Immortal_runleft");
	AnimationCache::getInstance()->addAnimation(createAnimation("desertImmortal_0%03d.png", 1, 22, 0.04f), "Immortal_runright");
}

Animation* HelloWorld::createAnimation(const char* prefixName, int start, int end, float delay)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = start; i <= end; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());
		if (frame != nullptr)
			animFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animFrames, delay);
}

Animation* HelloWorld::createAnimation(const char* prefixName, int start, int end, float delay, std::string lastFrame)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = start; i <= end; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());
		if (frame != nullptr)
			animFrames.pushBack(frame);
	}
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(lastFrame));
	return Animation::createWithSpriteFrames(animFrames, delay);
}