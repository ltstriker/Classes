#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	static HelloWorld* getinstance();
    virtual bool init();

	void initAction();
	void init_ArtilleryTower();
	void init_MageTower();
	void init_ArcherTower();
	void init_BossEfreeti();
	void init_BossCanibal();
	void release_BossCanibal();
	void release_BossEfreeti();
	void init_Thug();
	void init_Raider();
	void init_Immortal();
	void init_Fallen();
	void init_Wolf();

	MenuItemImage* mode1;
	void ChangetoBasicMode(Ref* pSender);
	MenuItemImage* mode2;
	void ChangetoAdvMode(Ref* pSender);
	bool mode;

	void startMenuCallback(cocos2d::Ref* pSender);
	void preLoad();
	Animation* createAnimation(const char* prefixName, int start, int end, float delay);
	Animation* createAnimation(const char* prefixName, int start, int end, float delay, std::string lastFrame);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
private:
	static HelloWorld * instance;

};

#endif // __HELLOWORLD_SCENE_H__
