#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

// 声效管理
class SoundManager {
public:
	static void playClickEffect();
	static void playIncomingWave();
	static void playNextWaveReady();

	//音效
	static void playTowerMenu();
	static void playShipOpen();
	static void playWinStars();
	//防御塔
	static void playTowerBuilding();
	static void playTowerUpdate();
	static void playTowerSell();
	//野人塔
	static void playTotemReady();
	static void playTotemShot();
	static void playTotemSpirits();
	static void playTotemWeakness();
	//箭塔
	static void playArrowShoot1();
	static void playArrowShoot2();
	static void playArrowRelease();
	static void playArcherReady();
	static void playArcher2Ready();
	static void playArcher3Ready();
	//弩塔
	static void playCrossbowReady();
	static void playCrossbowMultishot();
	static void playCrossbowEagle();
	//地震塔
	static void playEarthquakeReady();
	static void playEarthquakeHit();
	static void playEarthquakeDrillin();
	static void playEarthquakeDrillOut();
	static void playEarthquakeLava();
	//机器人
	static void playMechReady();
	static void playMechWalk();
	static void playMechShit();
	static void playMechLoading();
	//炮塔
	static void playArtilleryReady();
	static void playArtillery2Ready();
	static void playArtillery3Ready();
	static void playBomb();
	//兵营塔
	static void playRallyPointPlaced();
	static void playBarrackReady();
	static void playBarrack2Ready();
	static void playBarrack3Ready();
	static void playBarrackOpendoor();
	static void playBarrackMove();
	static void playAssassinMove();
	//龙卷风塔
	static void playArchmageReady();
	static void playArchmageShot();
	static void playArchmageTwister();
	static void playArchmagePrecharge();
	//基础魔法塔
	static void playMageTowerReady();
	static void playMageTower2Ready();
	static void playMageTower3Ready();
	static void playMageTowerShot();
	//NEC
	static void playNecTowerReady();
	static void playDKReady();
	static void playNecShot();
	static void playDKTaunt();
	//陨石
	static void playFireballHit();
	static void playFireballUnleash();
	//关卡结束
	static void playQuestCompleted();
	static void playQuestFailed();
	//技能
	static void playReinforcement();
	static void playCash();
	static void playFreeze();
	static void playHearts();
	//猩猩BOSS
	static void playChestdrum();
	static void playChimps_1();
	static void playChimps_2();
	static void playChimps_3();
	static void playMonoDeath();
public:
	static void playWelcomeBackMusic();
	static void playJungleBattle();
	static void playDesertBattle();
	static void playGameTheme1();
public:
	//BOSS 100
	static void playEfreetiLaugh();
	static void playEfreetiClap();
	static void playEfreetiDeath();
private:
	static bool cheakEffectState();
};

#endif