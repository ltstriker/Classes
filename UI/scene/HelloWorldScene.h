#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void initAction();
	void init_ArtilleryTower();
	void init_MageTower();
	void init_ArcherTower();
	void init_BossEfreeti();
	void init_BossCanibal();
//	void init_ArcherTower();
//	void init_MageTower();
	void release_BossCanibal();
	void release_BossEfreeti();
	void init_Thug();
	void init_Raider();

	void startMenuCallback(cocos2d::Ref* pSender);
	void preLoad();
	Animation* createAnimation(const char* prefixName, int start, int end, float delay);
	Animation* createAnimation(const char* prefixName, int start, int end, float delay, std::string lastFrame);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
