#ifndef _GIFTBAG_CONFIG_H_
#define _GIFTBAG_CONFIG_H_

#include "Kernel.h"
#include "CommData.h"
#include "Award.h"
#include "CommonConfig.h"

struct GiftBagItemConfig {
	uint32_t id;
	vector<uint32_t> rate;
	Award award;
	GiftBagItemConfig(): id(0) {
		rate.clear();
		award.clear();
	}
};

struct ChargeRewardConfig {
	uint32_t require;
	Award award;
	ChargeRewardConfig(): require(0) {
		award.clear();
	}
};

struct NewServerRankConfig {
	uint8_t from;
	uint8_t to;
	uint32_t require;
	Award reward;

	NewServerRankConfig() {
		from = 0;
		to = 0;
		require = 0;
	}
};

struct LuckyLotteryConfig {
	uint32_t one;
	uint32_t ten;
	uint32_t lucky_count;
	uint32_t lucky_id;
	vector<ChargeRewardConfig> pools;

	LuckyLotteryConfig() {
		one = 0;
		ten = 0;
		lucky_count = 0;
		lucky_id = 0;
		pools.clear();
	}
};

class GiftBagConfig {
public:
	~GiftBagConfig();
	static GiftBagConfig * getInstance() {
		static GiftBagConfig gc;
		return &gc;
	}
	bool init(const string & path);
	bool initFirstCharge(const string & path);
	bool initDailyCharge(const Json::Value &value);
	bool initTotalCharge(const Json::Value &value);
	bool initNewServerRank(const Json::Value &value, uint32_t type, uint32_t day);
	bool initActRank(const Json::Value &value, uint32_t type);
	bool initDailyBuyBag(const Json::Value &value, map<uint32_t, ChargeRewardConfig> &data);
	bool initDailyChargeEquip(const Json::Value &value, map<uint32_t, map<uint32_t, ChargeRewardConfig> > &data);
	bool initDailyChargeCash(const Json::Value &value, map<uint32_t, map<uint32_t, ChargeRewardConfig> > &data);
	bool initContinueCharge(const Json::Value &value, map<uint32_t, ChargeRewardConfig> &data);
	bool initWanbaVipSpecialBag(const Json::Value &value);
	bool initWanbaVipDailyBag(const Json::Value &value);
	bool initLuckyLottery(const string &path);
	bool initfunctionUnlock(const string &path);
	bool initLuckyBox(const Json::Value &value);
	const GiftBagItemConfig* getConfig(uint32_t id);
	const Award* getDailyChargeReward(uint32_t cash);
	const Award* getTotalChargeReward(uint32_t id, uint32_t cash);
	uint32_t getTotalChargeRewardLen() const;
	bool openLuckyBox(uint32_t id, uint32_t count, Award &award);
	bool isBox(uint32_t id);
	bool openAllLuckyBox(uint32_t id, uint32_t count, Award &award);
	bool openAll(const vector<AwardInfo> &in, Award &award);
	const NewServerRankConfig* getNewSrvTar(uint32_t type, uint32_t id, uint32_t day) const;
	const NewServerRankConfig* getNewSrvRank(uint32_t type, uint32_t id, uint32_t day) const;
	const NewServerRankConfig* getActRank(uint32_t type, uint32_t id) const;
	uint32_t getActRankRequire(uint32_t type) const;
	uint32_t getFirstChargeSize() const;
	const Award* getFirstChargeReward(uint32_t id) const;
	const ChargeRewardConfig* getDailyBuyBag(uint32_t day, bool is_new) const;
	uint32_t getDailyChargeEquipSize(uint32_t day, bool is_new) const;
	const ChargeRewardConfig* getDailyChargeEquip(uint32_t day, uint32_t id, bool is_new) const;
	uint32_t getDailyChargeCashSize(uint32_t day, bool is_new) const;
	const ChargeRewardConfig* getDailyChargeCash(uint32_t day, uint32_t id, bool is_new) const;
	uint32_t getContinueChargeSize(bool is_new) const;
	const ChargeRewardConfig* getContinueCharge(uint32_t id, bool is_new) const;
	uint32_t getLuckyLotteryCost(bool ten) const;
	uint32_t getLuckyLotteryLuckyCount() const;
	uint32_t getLuckyLotteryLuckyId() const;
	int32_t randomLuckyLottery() const;
	const Award* getLuckyLotteryReward(uint32_t id) const;
	const ChargeRewardConfig* getWanbaVipSpecialBag(uint32_t id) const;
	const ChargeRewardConfig* getWanbaVipDailyBag(uint32_t id) const;
	const Award* getShare() const;
	const Award* getAddShortcut() const;
	const ChargeRewardConfig* getFunctionUnlock(byte type, uint32_t id) const;
protected:
	GiftBagConfig();
private:
	map<uint32_t, GiftBagItemConfig> m_giftBag;
	map<uint32_t, ChargeRewardConfig> m_totalCharge;
	map<uint32_t, Award> m_firstCharge;
	map<uint32_t, map<uint32_t, vector<NewServerRankConfig> > > m_new_srv_rank;
	map<uint32_t, vector<NewServerRankConfig> > m_act_rank;
	map<uint32_t, ChargeRewardConfig> m_dailyBuyBag;
	map<uint32_t, map<uint32_t, ChargeRewardConfig> > m_dailyChargeEquip;
	map<uint32_t, map<uint32_t, ChargeRewardConfig> > m_dailyChargeCash;
	map<uint32_t, ChargeRewardConfig> m_continueCharge;
	map<uint32_t, ChargeRewardConfig> m_dailyBuyBagNew;
	map<uint32_t, map<uint32_t, ChargeRewardConfig> > m_dailyChargeEquipNew;
	map<uint32_t, map<uint32_t, ChargeRewardConfig> > m_dailyChargeCashNew;
	map<uint32_t, ChargeRewardConfig> m_continueChargeNew;
	map<uint32_t, ChargeRewardConfig> m_wanbaVipSpecialBag;
	map<uint32_t, ChargeRewardConfig> m_wanbaVipDailyBag;
	map<uint32_t, ChargeRewardConfig> m_functionUnlock_a;
	map<uint32_t, ChargeRewardConfig> m_functionUnlock_b;
	ChargeRewardConfig m_dailyCharge;
	Award m_share;
	Award m_addShortcut;
	LuckyLotteryConfig m_luckyLottery;
};

#endif /* _GIFTBAG_CONFIG_H_ */
