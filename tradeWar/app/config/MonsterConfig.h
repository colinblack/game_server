/*
 * MonsterConfig.h
 *
 *  Created on: 2016年1月26日
 *      Author: asdf
 */

#ifndef SERVERS_APP_CONFIG_MONSTERCONFIG_H_
#define SERVERS_APP_CONFIG_MONSTERCONFIG_H_

#include "Kernel.h"
#include "CommData.h"

struct MonsterItemConfig
{
	uint32_t id;
	uint32_t type;
	uint32_t prof;
	uint32_t sp;
//	uint32_t rejectHurtRate; // 免伤系数
//	uint32_t critRate; // 暴击系数
//	uint32_t dodgeRate; // 闪避系数
	uint32_t range;
	uint32_t hurtBuildingRatio; // 建筑伤害比
	uint32_t hurtAirRatio; // 建筑伤害比
	uint32_t hurtArmyRatio; // 建筑伤害比
	uint32_t hurtNavyRatio; // 建筑伤害比

	vector<uint32_t> hp;
	vector<uint32_t> ha;
	vector<uint32_t> hd;
	vector<uint32_t> ip;
	vector<uint32_t> bp;
	vector<uint32_t> bv;
	vector<uint32_t> rp;
};

class MonsterConfig
{
private:
	MonsterConfig();
public:
	~MonsterConfig();
	static MonsterConfig* getInstance()
	{
		static MonsterConfig mc;
		return &mc;
	};
	bool init(const string & path);
	bool initJson(const string & path);
	MonsterItemConfig* getItemConfig(uint32_t id);
	bool getMonsterConfig(uint32_t id, uint32_t level, PropertySets& props);
	uint32_t getSp(MonsterItemConfig* mic);
	uint32_t getRange(MonsterItemConfig* mic);
	uint32_t getProf(MonsterItemConfig* mic);
	uint32_t getHp(MonsterItemConfig* mic, uint32_t level);
	uint32_t getHa(MonsterItemConfig* mic, uint32_t level);
	uint32_t getHd(MonsterItemConfig* mic, uint32_t level);
	uint32_t getIp(MonsterItemConfig* mic, uint32_t level);
	uint32_t getBp(MonsterItemConfig* mic, uint32_t level);
	uint32_t getBv(MonsterItemConfig* mic, uint32_t level);
	uint32_t getRp(MonsterItemConfig* mic, uint32_t level);
	bool parseArr(const Json::Value &item, const string &key, vector<uint32_t> &arr);
private:
	map<uint32_t,MonsterItemConfig> m_mapItemConfig;

}; // end of MonsterConfig


#endif /* SERVERS_APP_CONFIG_MONSTERCONFIG_H_ */
