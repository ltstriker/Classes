#include "GameScene.h"
//#include "Level0.h"
#include "Level1.h"
/*#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "Level10.h"
#include "Level11.h"
#include "Level12.h"*/
#include "PlayerStateMenu.h"
#include "GameManager.h"

Scene* GameScene::playGame(int Level,int Difficulty)
{            
	auto scene = new GameScene();
	if(scene && scene->initGame(Level,Difficulty)){
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool GameScene::initGame(int Level,int difficulty)
{
	auto playerStateMenu = PlayerStateMenu::create();
	BaseMap* game;
	GameManager::getInstance()->LEVEL = Level;
	game = Level1::createGame(difficulty);
	game->bindPlayerStateMenu(playerStateMenu);
	playerStateMenu->setLevel(Level);
	playerStateMenu->setDifficult(difficulty);
	playerStateMenu->initGameOption();
	addChild(game);	
	addChild(playerStateMenu);
	return true;
}