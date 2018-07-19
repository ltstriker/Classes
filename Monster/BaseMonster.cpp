#include "BaseMonster.h"
#include "../UI/GameManager.h"
#include "../UI/BaseMap.h"

USING_NS_CC;

BaseMonster::BaseMonster()
  :baseSprite(NULL),
  pointCounter(0),
  runSpeed(0),
  maxHp(0),
  currHp(0),
  armor(0),
  hpPercentage(100),
  hpBar(NULL),
  lastState(stateNone),
  attackBySoldier(true),
  attackByTower(true),
  isAttacking(false),
  isSlowed(false),
  money(0)
{}

BaseMonster::~BaseMonster() {}

bool BaseMonster::init() {
  if (!Sprite::init()) {
    return false;
  }
  return true;
}

// 添加事件监听
void BaseMonster::addListener() {
  auto listener = EventListenerTouchOneByOne::create();
  listener->onTouchBegan = CC_CALLBACK_2(BaseMonster::onTouchBegan, this);
  listener->onTouchEnded = CC_CALLBACK_2(BaseMonster::onTouchEnded, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, baseSprite);
}

// 创建血条
void BaseMonster::createAndSetHpBar() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("towers-hd.plist");
  hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");

  hpBgSprite->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height));
  baseSprite->addChild(hpBgSprite);

  hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
  hpBar->setType(ProgressTimer::Type::BAR);
  hpBar->setMidpoint(Point(0, 0.5f));
  hpBar->setBarChangeRate(Point(1, 0));
  hpBar->setPercentage(hpPercentage);
  hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
  hpBgSprite->addChild(hpBar);
}

// 受伤，播放流血动画
void BaseMonster::getHurt() {
  blood->setVisible(true);
  blood->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("blood_red")),
    CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible, blood, false))
    , NULL));
}

// 获取现在的位置
Point BaseMonster::currPoint() {
  return pointsVector.at(pointCounter);
}

// 获取下一个移动的位置
Point BaseMonster::getNextPoint() {
  auto temp = pointCounter + 5;
  auto maxCount = int(pointsVector.size());
  if (temp < maxCount) {
    auto node = this->pointsVector.at(temp);
    return node;
  }
  return currPoint();
}

// 获取下一个位置
Point BaseMonster::nextPoint() {
  auto maxCount = int(pointsVector.size());
  pointCounter++;
  if (pointCounter < maxCount) {
    auto node = this->pointsVector.at(pointCounter);
    return node;
  }
  else {
    pointCounter = maxCount - 1;
  }
  return currPoint();
}

// 设置Monster的z轴位置
void BaseMonster::setMonsterZorder(int yOrder) {
  int hunder = (yOrder / 100);
  switch (hunder) {
  case(0):
    this->setLocalZOrder(10);
    break;
  case(1):
    this->setLocalZOrder(9);
    break;
  case(2):
    this->setLocalZOrder(8);
    break;
  case(3):
    this->setLocalZOrder(7);
    break;
  case(4):
    this->setLocalZOrder(6);
    break;
  case(5):
    this->setLocalZOrder(5);
    break;
  case(6):
    this->setLocalZOrder(4);
    break;
  case(7):
    this->setLocalZOrder(3);
    break;
  case(8):
    this->setLocalZOrder(2);
    break;
  case(9):
    this->setLocalZOrder(1);
    break;
  case(10):
    this->setLocalZOrder(0);
    break;
  default:
    break;
  }
}

// 移动到下一个点
void BaseMonster::runNextPoint() {
  auto tempCurrPoint = currPoint();
  baseSprite->setPosition(tempCurrPoint);
  tempNextPoint = nextPoint();
  setMonsterZorder(tempNextPoint.y); // 根据y轴坐标设置z轴坐标

  if (fabs(tempNextPoint.y - tempCurrPoint.y)>5 && tempNextPoint.y > tempCurrPoint.y)// 往上走
  {
    setState(stateWalkUp);
  }
  else if (fabs(tempNextPoint.y - tempCurrPoint.y)>5 && tempNextPoint.y <= tempCurrPoint.y) // 往下走
  {
    setState(stateWalkDown);
  }
  else if (tempNextPoint.x >= tempCurrPoint.x)//正在向右走
  {
    setState(stateWalkRight);
  }
  else if (tempNextPoint.x < tempCurrPoint.x)//正在向左走
  {
    setState(stateWalkLeft);
  }
  if (tempNextPoint != tempCurrPoint) {
    auto duration = tempCurrPoint.getDistance(tempNextPoint) / getRunSpeed(); // 时间=路程/速度
    // 播放移动动画
    baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
      , CallFuncN::create(CC_CALLBACK_0(BaseMonster::runNextPoint, this))
      , NULL));
  }
  else {
    //走到终点
    GameManager::getInstance()->LIFE--;
    GameManager::getInstance()->monsterVector.eraseObject(this);
    unscheduleAllCallbacks();
    setCurrHp(0);
  }
}

// 调度器更新，检查Monster状态
void BaseMonster::update(float dt) {
  //若状态更新
  if (lastState != getState()) {
    //根据状态判断
    switch (getState()) {
    case(stateWalkRight): {
      lastState = stateWalkRight;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(false); // 图像向右
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "runright")));
      action->setTag(stateWalkRight);
      baseSprite->runAction(action);
    }
      break;
    case(stateWalkLeft): {
      lastState = stateWalkLeft;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(true); // 图像向左
      auto aa = getName();
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "runleft")));
      action->setTag(stateWalkLeft);
      baseSprite->runAction(action);
    }
      break;
    case(stateWalkUp): {
      lastState = stateWalkUp;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(false); // 图像向右
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "runup")));
      action->setTag(stateWalkUp);
      baseSprite->runAction(action);
    }
      break;
    case(stateWalkDown): {
      lastState = stateWalkDown;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(false); // 图像向右
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "rundown")));
      action->setTag(stateWalkDown);
      baseSprite->runAction(action);
    }
      break;
    case(stateAttackRight): {
      lastState = stateAttackRight;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(false); // 图像向右
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "attack")));
      action->setTag(stateAttackRight);
      baseSprite->runAction(action);
    }
      break;
    case(stateAttackLeft): {
      lastState = stateAttackLeft;
      // 停止所有动画
      stopMonsterAnimation();
      baseSprite->setFlippedX(true); // 图像向左
      auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "attack")));
      action->setTag(stateAttackLeft);
      baseSprite->runAction(action);
    }
      break;
    case(stateNone): {
      lastState = stateNone;
    }
      break;
    case(stateFrozen): {
      lastState = stateFrozen;
    }
      break;
    case(stateDeath): {
      lastState = stateDeath;
    }
      break;
    }
  }
}

// 停止Monster所有动画
void BaseMonster::stopMonsterAnimation() {
  for (int i = 1; i <= 6; i++) {
    baseSprite->stopActionByTag(i);
  }
}

// Monster死亡
void BaseMonster::death() {
  if (GameManager::getInstance()->monsterVector.contains(this)) {
    GameManager::getInstance()->monsterVector.eraseObject(this);
  }
    
  if (getState() != stateDeath) {
    setCurrHp(0);
    setState(stateDeath);
    hpBgSprite->setVisible(false);
    baseSprite->stopAllActions();
    unscheduleUpdate();
    auto decal_blood = Sprite::createWithSpriteFrameName("decal_blood_0001.png");
    decal_blood->setPosition(Point(baseSprite->getContentSize().width / 2, -baseSprite->getContentSize().height / 4));
    baseSprite->addChild(decal_blood);
    GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
    baseSprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName() + "death")));
    decal_blood->runAction(Sequence::create(FadeOut::create(1.0f)
      , CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this, false))
      , NULL));
  }
}

void BaseMonster::explosion()
{
  if (GameManager::getInstance()->monsterVector.contains(this)) {
    GameManager::getInstance()->monsterVector.eraseObject(this);
  }
    
  if (getState() != stateDeath) {
    setCurrHp(0);
    setState(stateDeath);
    hpBgSprite->setVisible(false);
    baseSprite->stopAllActions();
    unscheduleUpdate();
    auto decal_blood = Sprite::createWithSpriteFrameName("decal_blood_0001.png");
    decal_blood->setPosition(Point(baseSprite->getContentSize().width / 2, -baseSprite->getContentSize().height / 4));
    baseSprite->addChild(decal_blood);
    GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
    baseSprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("explosion_Artillery")));
    decal_blood->runAction(Sequence::create(FadeOut::create(1.0f)
      , CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this, false))
      , NULL));
  }
}

void BaseMonster::frozen()
{
  if (getState() != stateFrozen) {
    tempState = lastState;
    setState(stateFrozen);
    baseSprite->stopAllActions();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
    ice = Sprite::createWithSpriteFrameName("freeze_creep_0007.png");
    ice->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 4));
    baseSprite->addChild(ice);
    ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creep")));
    scheduleOnce(schedule_selector(BaseMonster::refrozen), 8.0f);
  }
  else {
    unschedule(schedule_selector(BaseMonster::refrozen));
    scheduleOnce(schedule_selector(BaseMonster::refrozen), 8.0f);
    ice->stopAllActions();
    ice->removeFromParent();
    ice = Sprite::createWithSpriteFrameName("freeze_creep_0007.png");
    ice->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 4));
    baseSprite->addChild(ice);
    ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creep")));
  }
}

void BaseMonster::refrozen(float dt)
{
  ice->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("refreeze_creep"))
    , CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, ice))
    , CallFuncN::create(CC_CALLBACK_0(BaseMonster::restartWalking, this))
    , NULL));
}

void BaseMonster::stopWalking()
{
  tempState = lastState;
  baseSprite->stopAllActions();
}

void BaseMonster::restartWalking()
{
  lastState = stateNone; // 重置为默认值
  baseSprite->stopAllActions();
  setState(tempState);

  auto tempCurrPoint = baseSprite->getPosition();
  auto duration = tempCurrPoint.getDistance(tempNextPoint) / getRunSpeed();
  baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
    , CallFuncN::create(CC_CALLBACK_0(BaseMonster::runNextPoint, this))
    , NULL));
}

// 减速
void BaseMonster::slowRunSpeed(float dt, float dis) {
  if (!isSlowed) {
    isSlowed = true;
    auto temp = this->getRunSpeed();
    this->setRunSpeed(temp - dis);
    runAction(Sequence::create(
      DelayTime::create(dt),
      CallFuncN::create(CC_CALLBACK_0(BaseMonster::setRunSpeed, this, temp)),
      CallFuncN::create(CC_CALLBACK_0(BaseMonster::setIsSlowed, this, false)),
      NULL));
  }
}

bool BaseMonster::onTouchBegan(Touch* touch, Event* event) {
  auto target = static_cast<Sprite*>(event->getCurrentTarget());

  Point locationInNode = target->convertTouchToNodeSpace(touch);

  Size size = target->getContentSize();
  Rect rect = Rect(0, 0, size.width, size.height);
  if (rect.containsPoint(locationInNode) && this->isVisible()) {

    return true;
  }
  return false;
}

void BaseMonster::onTouchEnded(Touch* touch, Event* event) {
  static_cast<BaseMap*>(this->getParent())->playerState->showMonsterInfo(this);
}
