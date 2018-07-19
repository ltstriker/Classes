#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public BaseMap
{
public:
	GameScene();
	~GameScene();
	static GameScene* createGame(int difficulty);
	virtual bool initWithDifficulty(int difficulty);
private:
	void onExit();
	//void addMonsters(float dt);
	void addTerrains();
};
