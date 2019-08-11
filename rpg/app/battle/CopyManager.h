/*
 * CopyManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */
#ifndef COPY_MANAGER_H_
#define COPY_MANAGER_H_
#include "BattleBaseInc.h"
#include "MapManager.h"

#define DEFAULT_COPY_X 588
#define DEFAULT_COPY_Y 876

#define MAGIC_TOWER_BASE 200001000
#define MAGIC_TOWER_COPY 220


struct CopySaveInfo{
	uint32_t copyType;
	uint32_t copyCode;
	uint32_t fromMapId;
	uint32_t mapId;
	uint32_t bossId;
	uint32_t count;
	uint32_t wave;
	uint32_t index;
	uint32_t refreshTime;
	uint32_t singExp;
	uint32_t rateCount;
	uint32_t startTime;
	CopySaveInfo(){
		memset(this,0,sizeof(*this));
	}
};


class CopyManager: public CSingleton<CopyManager> {
private:
	friend class CSingleton<CopyManager>;
	CopyManager();
	~CopyManager();


public:
	bool Init();
	void onHour(uint32_t hour);
	void onSecondTimer();
	bool OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos);
	bool OnHumanDie(uint32_t uid);
	bool OnCopyHumanDie(uint32_t uid);
	void OnHurt(uint32_t copyId,uint32_t mapIndex,uint32_t monsterId,uint32_t lastAttacker,map<uint64_t, HurtInfo>& hurtList,uint64_t hp);
public:
	//离开副本
	int Process(uint32_t uid, copy::CSLeaveCopy *req);

	//转生BOSS
	int Process(uint32_t uid, copy::CSEnterReincarnCopy *req);
	int Process(uint32_t uid, copy::CSQuickFinish *req);
	int Process(uint32_t uid, copy::CSGotReward *req);

	//符文塔
	int Process(uint32_t uid, copy::CSEnterMagicTowerCopy *req);
	int Process(uint32_t uid, copy::CSLotteryMagicTower *req,copy::SCLotteryMagicTowerResp * resp);

	//世界BOSS
	int Process(uint32_t uid, copy::CSEnterWorldBoss *req);
	int Process(uint32_t uid, copy::CSGetWorldBossList *req);
	//世界BOSS引导
	int Process(uint32_t uid, copy::CSEnterTaskCopy *req);

	//材料副本
	int Process(uint32_t uid, copy::CSEnterMaterialCopy *req);
	int Process(uint32_t uid, copy::CSQuickFinishMaterial *req);
	int Process(uint32_t uid, copy::CSMopMaterial *req);



	//经验副本
	//CMD_RPC_COPY_ENCOURAGEEXPCOPY
	//CMD_RPC_COPY_BUYEXTRAEXPCOPY
	int Process(uint32_t uid, copy::CSEnterExpCopy *req);


	//秘境BOSS
	int Process(uint32_t uid, copy::CSGetGodPlaneList *req);
	int Process(uint32_t uid, copy::CSEnterGodPlane *req);
	int Process(uint32_t uid, copy::CSFightRevive *req);


	//组队副本
	int Process(uint32_t uid, copy::CSEnterImmortalroadCopy *req);


	//伙伴岛
	int Process(uint32_t uid, copy::CSEnterPartnerIslandCopy *req);
	//quick




public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerCopyDataList *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SLotteryMagicTower *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SBossList *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SEntityUpdate *resp);

private:
	bool onMatrialMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterid,const Point &diePos);

	bool onImmortalRoadMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterid,const Point &diePos);
	bool onImmortalRoadFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);

	bool onExpMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterid,const Point &diePos);
	bool onExpFinish(uint32_t uid,CopySaveInfo& saveInfo);

	bool onReinCarnFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);

	bool onMagicTowerFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);

	bool onMaterialFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);


	void onTaskBossDie(uint32_t bossId);
	void OnTaskBossHurt(uint32_t mapIndex,uint32_t monsterId,map<uint64_t, HurtInfo>& hurtList,uint64_t hp);
	bool onTaskCopyFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);

	void onWorldBossDie(uint32_t bossId);
	void OnWorldBossHurt(uint32_t mapIndex,uint32_t monsterId,map<uint64_t, HurtInfo>& hurtList,uint64_t hp);
	bool onWorldBossFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);


	bool onGoldPlaneHumanDie(uint32_t uid);
	void OnGodPlaneHurt(uint32_t monsterId,uint32_t lastAttacker);
	bool onGodPlaneFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);

	bool onPartnerIslandFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos);




	bool MonsterDrop(uint32_t uid,uint32_t monster_id,Award& reward, const Point &diePos);
	bool checkReset(CopyInfo& copyInfo);
	void resetGodPlaneBoss(uint32_t bossId);


	bool sendUpdate(const UserCache &cache, uint32_t copyId);
	bool sendBossUpdate(uint32_t uid,uint32_t type,uint32_t bossId);


	bool sendGodPlaneList(uint32_t uid);
	bool sendWorldBossList(uint32_t uid);

	bool sendPlayerDeath(uint32_t uid,uint32_t bossId,uint32_t reviveTime);
	bool sendEntityUpdate(uint32_t uid,uint32_t mapIndex,uint64_t ownerId);
	bool sendImmortalRoadCopyInfo(uint32_t uid,uint32_t wave,map<uint32_t,uint32_t>& monsters);
	bool sendExpCopyInfo(uint32_t uid);
	bool sendPartnerIslandInfo(uint32_t uid);



private:
	CDataCopy * m_data;
	map<uint32_t,CopySaveInfo> m_saveInfo;
	map<uint32_t,CopyBoss> m_worldboss;

};

#endif /* COPY_MANAGER_H_ */
