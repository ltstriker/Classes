#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	static void playClickEffect();
	static void playIncomingWave();
	static void playNextWaveReady();
	static void playEfreetiLaugh();
	static void playEfreetiClap();
	static void playEfreetiDeath();
private:
	static bool cheakEffectState();
};

#endif