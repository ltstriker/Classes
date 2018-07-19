#include "cocos2d.h"
#include "terrain.h"


USING_NS_CC;

class BaseMap : public Layer
{
public:
	CREATE_FUNC(BaseMap);
	//当前关卡
	CC_SYNTHESIZE(int, level, Level);
	//地图精灵
	Sprite* mapSprite;
protected:
	void initTouchLayer();
	//屏幕尺寸
	Size winSize;
	//设置初始地图位置
	void setMapPosition();
	//初始化地图
	void initMap();
	//添加建塔点
	virtual void addTerrains() {};
	virtual void onExit() {};
};