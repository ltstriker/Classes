#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

void SoundManager::playEfreetiLaugh()
{
}

void SoundManager::playEfreetiClap()
{
}

void SoundManager::playEfreetiDeath()
{
}

bool SoundManager::cheakEffectState() {
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1 == 1)) {
		return true;
	}
	else {
		return false;
	}
}

void SoundManager::playClickEffect()
{
}

void SoundManager::playIncomingWave()
{
}

void SoundManager::playNextWaveReady()
{
}
