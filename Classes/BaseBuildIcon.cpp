#include "BaseBuildIcon.h"
#include "GameManager.h"

bool BaseBuildIcon::initIcon(int type, int money)
{
	if (!Sprite::init())
	{
		return false;
	}

	this->isSelected = false;
	auto name = String::createWithFormat("main_icons_00%02d.png", type)->getCString();
	this->baseIcon = Sprite::createWithSpriteFrameName(name);
	this->addChild(baseIcon);
	
	this->priceIcon = Sprite::createWithSpriteFrameName("price_tag.png");
	this->priceIcon->setPosition(Point(0, -this->baseIcon->getContentSize().height / 2));
	this->addChild(priceIcon);

	this->priceLabel = Label::createWithTTF(String::createWithFormat("%d", money)->getCString(), "arial.ttf", 20);
	this->priceLabel->setColor(Color3B(255, 153, 0));
	this->priceLabel->setPosition(Point(this->priceIcon->getContentSize().width / 2, this->priceIcon->getContentSize().height / 2 - 2));
	this->priceIcon->addChild(priceLabel);

	this->okIcon = Sprite::createWithSpriteFrameName("main_icons_0019.png");
	this->okIcon->setPosition(Point(this->baseIcon->getContentSize().width / 2, this->baseIcon->getContentSize().height / 2));
	this->baseIcon->addChild(this->okIcon);
	this->okIcon->setVisible(false);

	this->setMoney(money);
	this->setType(type);
	this->scheduleUpdate();

	return true;
}

BaseBuildIcon * BaseBuildIcon::createIcon(int type, int money)
{
	auto baseBuildIcon = new BaseBuildIcon();

	if (baseBuildIcon && baseBuildIcon->initIcon(type, money))
	{
		baseBuildIcon->autorelease();
		return baseBuildIcon;
	}

	CC_SAFE_DELETE(baseBuildIcon);
	return nullptr;
}

void BaseBuildIcon::setSelected()
{
	this->isSelected = true;
	this->okIcon->setVisible(true);
}

void BaseBuildIcon::setNotSelected()
{
	this->isSelected = false;
	this->okIcon->setVisible(false);
}

void BaseBuildIcon::setNotEnoughMoney()
{
	this->isAble = false;
	this->priceLabel->setColor(Color3B(102, 102, 102));
	this->baseIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("main_icons_disabled_00%02d.png", type)->getCString()));
	this->priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag_disabled.png"));
	this->okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_disabled_0019.png"));
}

void BaseBuildIcon::setEnoughMoney()
{
	this->isAble = true;
	this->priceLabel->setColor(Color3B(255, 153, 0));
	this->okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_0019.png"));
	this->baseIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("main_icons_00%02d.png", type)->getCString()));
	this->priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag.png"));
}

void BaseBuildIcon::setUpdateMoney(int money)
{
	this->setMoney(money);
	this->priceLabel->setString(String::createWithFormat("%d", money)->getCString());
}

void BaseBuildIcon::update(float dt)
{
	if (this->getMoney() <= GameManager::getInstance()->MONEY) {
		this->setEnoughMoney();
	}
	else {
		this->setNotEnoughMoney();
	}
}
