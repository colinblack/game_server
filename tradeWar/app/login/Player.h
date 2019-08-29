/*
 * player.h
 *
 *
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Kernel.h"
#include "DataInc.h"
#include "SoldierManager.h"
#include "BuildingManager.h"
#include "EquipmentManager.h"
#include "PlayerManager.h"
#include "PropertyManager.h"
#include "ResourceManager.h"
#include "TaskManager.h"
#include "EmailManager.h"
#include "UserStateManager.h"
#include "ActivenessManager.h"
#include "Award.h"
#include "SkillManager.h"
#include "InviteManager.h"
#include "DefendManager.h"
#include "TroopsManager.h"
#include "BoatManager.h"
#include "SoldierRecoverTrain.h"
#include "DailyLoginManager.h"
#include "VipManager.h"
#include "DailyBuyManager.h"
#include "BattleGateManager.h"
#include "SocialManager.h"
#include "RandomQuestManager.h"
#include "ActivityManager.h"
#include "WorldShopManager.h"
#include "MonthGiftManager.h"
#include "ChargeHistoryManager.h"
#include "GemManager.h"
#include "BossManager.h"
#include "ArenaManager.h"
#include "DailyWatchADManager.h"
#include "InteractManager.h"
#include "StarBoxManager.h"

class Player {
public:
	Player();
	~Player();
public:
	bool doPacket(CNetPacket * packet);
public:
	bool onLogin();
	bool onOffline(uint32_t uid);
	bool doReward(const Award * const pReward, const string & reason, bool notice = true, Award * result = NULL);
	bool doUser(CNetPacket * packet);
	bool doMiscPacket(CNetPacket *packet);
	bool doSocialPacket(CNetPacket *packet);
	bool doUserQuery(CNetPacket * packet);
	bool doQueryMenubar(CNetPacket * packet);
	bool doSetMenubar(CNetPacket * packet);
	bool doHeroRecruit(CNetPacket * packet);
	bool doQueryHeroRefreshItem(CNetPacket * packet);
	bool doChooseHeroRefreshItem(CNetPacket * packet);
	bool doHeroSetChief(CNetPacket * packet);
	bool doHeroSetStation(CNetPacket * packet);
	bool doHeroRecallStation(CNetPacket * packet);
	bool doHeroTrainListQuery(CNetPacket* packet);
	bool doHeroTrainSlotOpen(CNetPacket* packet);
	bool doHeroTrainFinishNow(CNetPacket* packet);
	bool doUpgradeBuildingOver(Building* pBuilding);
	bool doUpgradeSoldierOver(Soldier* pSoldier);
	bool doAccUpgradeBuilding(CNetPacket* packet);
	bool onAccUpgradeBuildingResp(byte ret, uint32_t ud, uint32_t ts);
	bool doAccUpgradeBuildingQuery(CNetPacket* packet);
	bool doSetUserKingdom(CNetPacket* packet);
	bool doBuyBuildingAccUpgrade(CNetPacket* packet);
	bool doSetTutorialStage(CNetPacket* packet);
	bool doSetTrailerStage(CNetPacket* packet);
	bool doSetBloodBankThreshold(CNetPacket* packet);
	bool doUserGetBlueValidTime(CNetPacket* packet);
	bool doUserGetPayToken(CNetPacket* packet);
	bool doAdvertChat(CNetPacket *packet);
	bool doSocialFriendAddTL(CNetPacket *packet);
	bool doAddictionRate(CNetPacket *packet);
	bool doAddictionRateQuery(CNetPacket *packet);
	bool doResetProtectTime(CNetPacket *packet);
	bool doAddShortcutReward(CNetPacket *packet);
	bool doSetClientState(CNetPacket *packet);
	bool doLevelReward(CNetPacket *packet);
	bool doAutoRewardInfo(CNetPacket *packet);
	bool doAutoRewardBag(CNetPacket *packet);
	bool doDailyChargeReward(CNetPacket *packet);
	bool doTotalChargeReward(CNetPacket *packet);
	bool doSetName(CNetPacket *packet);
	bool doFirstChargeReward(CNetPacket *packet);
	bool doBuyVipGift(CNetPacket *packet);
	bool doChargeReport(CNetPacket *packet);
	bool doInteract(CNetPacket *packet);
	bool doInteractBox(CNetPacket *packet);
	bool doAddRank();
public:
	bool onTrailerStageReward(uint32_t stage);
	void onPlayerCombatUpdate();
	void onPlayerNameUpdate();
	void onPlayerFigureUrlUpdate();
	bool onTimer();
	bool onBuildingTimer();
	bool onSoldierTimer();
	bool onOfflineInfo();
	bool onPlatfromGift(uint32_t giftid);
	bool onAutoReward(bool offline);
	bool loadAddiction();
	bool saveAddiction();
	bool onFirstChargeReward(byte ret);
	bool onTotalChargeReward(byte ret);
	bool onBuyVipGift(byte ret);
	bool onCombatChange(int chg);
	bool onInteract(uint32_t uid, uint32_t lv, uint32_t type, const string &name, const string &pic, int16_t &cnt);
	bool onInteractNotic(byte type);
	bool onInteractRecover();
	bool onInteractResp(byte ret, int16_t cnt);
	bool onInteractBoxResp(byte ret);
public:
	DataUser & getUserInfo() {
		return m_dataUser;
	}
	TencentBasicInfo & getTencentInfo() {
		return m_tencent_info;
	}
	void setTutorialStage(uint32_t stage) {
		m_dataUser.tutorial_stage = stage;
	}
	void setUserOfflineTime(uint32_t ts) {
		m_dataUser.offline_time = ts;
	}
	void setLevel(uint32_t level) {
		m_dataUser.level = level;
	}
	void setSpeedUpFlag(byte flag) {
		m_dataUser.speed_up = flag;
	}
	void addExp(int32_t exp) {
		if (exp < 0 && static_cast<uint32_t>(-1 * exp) > m_dataUser.exp) {
			m_dataUser.exp = 0;
		} else {
			m_dataUser.exp += exp;
		}
	}
	uint32_t getExp() {
		return m_dataUser.exp;
	}
	uint32_t getUserCombat() {
		return m_dataUser.combat + m_gemManager.getPower();
	}
	uint32_t getBuildingCombat() {
		return 0;
	}
	uint32_t getHeroCombat() {
		return 0;
	}
	uint32_t getUid() {
		return m_dataUser.uid;
	}
	uint32_t getLevel() {
		return m_dataUser.level;
	}
	byte getSpeedUp() {
		return m_dataUser.speed_up;
	}
	uint32_t getVipLevel() {
		return m_dataUser.viplevel;
	}
	uint32_t getLoginTime() {
		return m_dataUser.login_time;
	}
	uint32_t getOfflineTime() {
		return m_dataUser.offline_time;
	}
	uint32_t getAllianceId() {
		return 0;
	}
	byte getKingdom() {
		return 0;
	}
	const string& getName() {
		return m_dataUser.name;
	}
	const string& getFig() {
		return m_dataUser.figure_url;
	}
	const string &getOpenId() {
		return m_openId;
	}
	float getExpRate() {
		return m_expRate;
	}
	bool getIsNewUser() {
		return m_isNewUser;
	}
	void setIsNewUser(bool flag) {
		m_isNewUser = flag;
	}
	void setExpRate(float expRate);
	bool addTransPort(uint32_t res);
public:
	ResourceManager* getRm() {
		return &m_resourceManager;
	}
	PropertyManager* getPm() {
		return &m_propertyManager;
	}
	BuildingManager* getBm() {
		return &m_buildingManager;
	}
	DefendManager* getDefendManager() {
		return &m_defendManager;
	}
	BattleGateManager* getBattleGateMgr() {
		return &m_battleGateMgr;
	}
	SoldierManager* getSoldierManager() {
		return &m_soldierManager;
	}
	UserStateManager* getSm() {
		return &m_stateManager;
	}
	TaskManager* getTaskManager() {
		return &m_taskManager;
	}
	EmailManager* getEmailManager() {
		return &m_emailManager;
	}
	ActivenessManager* getActivenessManager() {
		return &m_activenessManager;
	}
	CSkillManager *getSkillManager() {
		return &m_skillManager;
	}
	InviteManager* getIm() {
		return &m_inviteManager;
	}
	EquipmentManager *getEm() {
		return &m_equipmentManager;
	}
	TroopsManager* getTroopsManager() {
		return &m_troopsManager;
	}
	BoatManager* getBoatManager() {
		return &m_boatManager;
	}
	SoldierRecoverTrain* getSoldierRecoverTrain() {
		return &m_soldierRecoverTrain;
	}
	VipManager* getVipManager() {
		return &m_vipManager;
	}
	SocialManager* getSocialManager() {
		return &m_socialManager;
	}
	ActivityManager* getActManager() {
		return &m_activityManager;
	}
	WorldShopManager* getWorldShopManager() {
		return &m_worldShopManager;
	}
	MonthGiftManager* getMonthGiftManager() {
		return &m_monthGiftManager;
	}
	ChargeHistoryManager* getChargeHistoryManager() {
		return &m_chargeHistoryManager;
	}
	GemManager* getGemManager() {
		return &m_gemManager;
	}
	ArenaManager* getArenaManager() {
		return &m_arenaManager;
	}
	InteractManager* getInteractManager() {
		return &m_interactManager;
	}
	StarBoxManager* getStarBoxManager() {
		return &m_starBoxmanager;
	}

	uint32_t getRegServerId() {
		return m_reg_server_id;
	}
	uint32_t getCurServerId() {
		return m_cur_server_id;
	}
	Building* getBuildingTimer(uint32_t bud);
	bool getResource(ResourceInfo & sInfo);
	void getRobResource(uint32_t aLv, ResourceInfo & sInfo);
public:
	void setTencentInfo(TencentBasicInfo & info) {
		m_tencent_info = info;
	}
	void setUserName(string & name) {
		m_dataUser.name.assign(name);
	}
	void setUserUrl(string & url) {
		m_dataUser.figure_url.assign(url);
	}
	void setBattleId(uint64_t battleId) {
		m_battleId = battleId;
	}
	uint64_t getBattleId() {
		return m_battleId;
	}
	bool isInBattle() {
		return m_battleId > 0;
	}
	bool getPay(byte payType, uint32_t pay, MoneyCost& cost);
	bool addTotalCharge(uint32_t money);
	bool addDailyCharge(uint32_t money);
	bool firstCharge(uint32_t cash);
	bool isFirstCharge();
	bool buySpecialDiscount(uint32_t id);
public:
	void load(uint32_t uid);
	bool LoadPlayerData(uint32_t uid);
	bool LoadNewPlayerData(uint32_t uid);
	int AddUser(const string& openId, uint32_t platform, uint32_t uid);
	int GetInitArchive(const Json::Value *&pArchive);
	int InitailizeResource(uint32_t uid, DataUserResource& res);
	int InitailizePay(uint32_t uid, DataPay& pay);
	int InitializeBuilding(uint32_t uid, vector<DataBuilding>& db);
	int InitializeHero(uint32_t uid, const string& name, vector<DataHero>& dh);
	int InitializeSoldier(uint32_t uid, const string& name, vector<DataSoldier>& ds);
	int InitializeEquipment(uint32_t uid, vector<DataEquipment>& de);
	int InitializeWorker(uint32_t uid, vector<DataWorker>& dw);
	int InitializeSkill(uint32_t uid, vector<DataSkill>& datas);
	int InitializeTroops(uint32_t uid);
	bool initTimerList();
	bool getAutoTransportRes();
public:
	void setOpenId(string openId) {
		m_openId = openId;
	}
	void setOpenKey(string openKey) {
		m_openKey = openKey;
	}
	void setUid(uint32_t uid) {
		m_uid = uid;
	}
	void setSpanId(uint32_t spanId) {
		m_spanId = spanId;
	}
	void setLoginPlatform(uint32_t platform) {
		m_login_platform = platform;
	}
	bool setProtectedTime(uint32_t protectedTime);
	uint32_t getProtectedTime();
	void setPropChange() {
		m_isPropChange = true;
	}
	void setOnline() {
		m_isOnline = true;
	}
	void setOffline() {
		m_isOnline = false;
	}
	void setFrontReady(bool flag) {
		m_isFrontReady = flag;
	}
	void setRegServerId(uint32_t serverId) {
		m_reg_server_id = serverId;
	}
	void setCurServerId(uint32_t serverId) {
		m_cur_server_id = serverId;
	}
	void setInviteBy(uint32_t uid) {
		m_dataUser.invite_by = uid;
	}
	bool isBlock() {
		return m_dataUser.block_time > Time::GetGlobalTime();
	}
public:
	bool addBuildingTimer(Building * pBuilding);
	bool removeBuildingTimer(Building * pBuilding);
	bool addSoldierTimer(Soldier * pSoldier);
	bool removeSoldierTimer(Soldier * pSoldier);
	bool clearAllTimer();
public:
	bool upPlayerExp(int32_t exp, const string& code);
	bool upDiamond(uint32_t diamondv, const string& code);
	bool upCoin(uint32_t coin, const string& code);
	bool upR1(uint32_t count, const string& code);
	bool upR2(uint32_t count, const string& code);
	bool upR3(uint32_t count, const string& code);
	bool upR1Rate(uint32_t rate, const string& code);
	bool upR2Rate(uint32_t rate, const string& code);
	bool upEnergy(uint32_t power, const string& code);
	bool upContribute(int32_t contribute, const string& code);
	bool updateResourceData(ResourceInfo& oi, const string& code);
	bool setVipLevel();
public:
	uint32_t getRegisterDay();
	uint32_t calcCombat();
	uint32_t calcGemCombat(bool save);
	uint32_t addCombat(uint32_t cnt);
	uint32_t calcHeroCombat();
	uint32_t calcBuildingCombat();
	uint32_t calcSoldierCombat();
	uint32_t calcAutoRewardRes();
	bool calcHeroProps(uint32_t hud);
	void calcDefenseBuildingProps();
	void calcSoldierProps();
public:
	bool savePlayerUserInfo(bool offline = false);
	bool isFrontReady() {
		return m_isFrontReady;
	}
	bool isLoadComplete() {
		return m_isOnline;
	}
	bool inProtected() {
		return m_dataUser.protected_time > Time::GetGlobalTime();
	}
	bool isQzone() {
		return m_spanId == 2;
	}
	bool makeHeroPos(int x, int y, int& hx, int& hy) {
		hx = x + 5;
		hy = y + 5;
		return true;
	}
	bool loadUser(DataUser& du);
	bool IsNewUser(uint32_t uid, bool& isNew);
	bool setPropertyManager();
	byte onHeroRecruit(byte ret, uint32_t heroId);
	bool save(uint32_t uid);
public:
	bool sendTencentUserInfo();
	bool sendHomeInfo();
	bool sendBaseInfo();
	bool sendPlayerInfo();
	bool sendPlayerCombat();
	bool sendServerTime();
	bool sendUnderAttack(uint32_t uid, uint64_t & battleId);
	bool sendHeroInfo(uint32_t hud);
	bool sendBuildingInfo(uint32_t bud);
	bool sendSoldierInfo(uint32_t sud);
	bool sendSoldierListInfo();
	bool sendHeroTrainList(uint32_t uid);
	bool sendJoinKingdomToAlliance(uint32_t uid, uint32_t kingdom);
	bool sendBagSize();
	bool sendActionOver(byte cmd, byte subCmd, MapObject* pMo);
	bool sendBuildingActionOver(byte cmd, byte subCmd, MapObject* pMo, uint32_t level);
	bool sendHeroRefreshItem(uint32_t uid, byte ret);
	bool sendHeroRefreshList(uint32_t uid, byte ret);
	bool sendDoubleExpTime();
	bool sendLockTimes();
	bool sendRestTimes();
	bool sendAutoRewardTs();
	bool sendChargeReward();
	bool sendBoxScore();
	bool sendIsNewUser();
public:
	void checkNextDay();
	void resetUserDaily();
private:
	bool m_isPropChange;		// 属性是否改变
	bool m_isFrontReady;		// 前端是否准备好
	bool m_isOnline;			// 是否在线
	bool m_isNewUser;
	bool m_isAddRank;
	int32_t m_onlineDay;
	float m_expRate;
	string m_openId;
	string m_openKey;
	uint32_t m_spanId;
	uint32_t m_login_platform;
	uint32_t m_uid;
	uint32_t m_reg_server_id;
	uint32_t m_cur_server_id;
	uint64_t m_battleId;
	uint32_t m_auto_reward_res;
	TencentBasicInfo m_tencent_info;
	DataUser m_dataUser;
	vector<Building*> m_bTimer;
	vector<Soldier*> m_sTimer;
private:
	SoldierManager m_soldierManager;
	BuildingManager m_buildingManager;
	EquipmentManager m_equipmentManager;
	PropertyManager m_propertyManager;
	ResourceManager m_resourceManager;
	UserStateManager m_stateManager;
	TaskManager m_taskManager;
	EmailManager m_emailManager;
	ActivenessManager m_activenessManager;
	InviteManager m_inviteManager;
	CSkillManager m_skillManager;
	DefendManager m_defendManager;
	BattleGateManager m_battleGateMgr;
	TroopsManager m_troopsManager;
	BoatManager m_boatManager;
	SoldierRecoverTrain m_soldierRecoverTrain;
	DailyLoginManager m_dailyLoginManager;
	VipManager m_vipManager;
	DailyBuyManager m_dailyBuyManager;
	SocialManager m_socialManager;
	RandomQuestManager m_randomQuestManager;
	ActivityManager m_activityManager;
	WorldShopManager m_worldShopManager;
	MonthGiftManager m_monthGiftManager;
	ChargeHistoryManager m_chargeHistoryManager;
	GemManager m_gemManager;
	BossManager m_bossManager;
	ArenaManager m_arenaManager;
	DailyWatchADManager m_watchADManager;
	InteractManager m_interactManager;
	StarBoxManager m_starBoxmanager;
};

#endif /* PLAYER_H_ */
