/*RoleSuitManager.h
 *
 * Date :2019.07.09
 *
 * Author: next
 *
 * */
#ifndef _ROLE_SUIT_MANAGER_H_
#define _ROLE_SUIT_MANAGER_H_

#include "BattleBaseInc.h"

class RoleSuitManager :public CSingleton<RoleSuitManager> {
private:
	friend class CSingleton<RoleSuitManager>;
	RoleSuitManager();
	~RoleSuitManager();
public:
	bool FormatSkills(uint32_t uid, uint32_t roleId, const CfgSuit::Suit& suit, vector<dbs::TPlayerSkill> &msg);
	bool AddRoleSuit(uint32_t uid, uint32_t roleId, uint32_t suitId);
	bool GetactiveSuit(const map<uint32_t, DataRoleSuit> &source, map<int32_t, map<int32_t, int32_t> > &target);
	bool GetUnlockSuit(const map<uint32_t, DataRoleSuit> &source, map<int32_t, int32_t> &target);
	bool IsSuitUnlock(const DataRoleSuit& data);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	uint32_t GetStarFromEquip(const DataEquip& equip);
	uint32_t& GetSloteByPart(DataRoleSuit& data, uint32_t index);
	const uint32_t& GetSloteByPart(const DataRoleSuit& data, uint32_t index);
	uint16_t GetShowId(uint32_t type);
public:
	int Process(uint32_t uid, logins::SActiveSuitReq *req);
	int Process(uint32_t uid, logins::SUnlockSuitReq *req);
	int Process(uint32_t uid, logins::SDressSuitReq *req);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerSuitCollects *resp);

};

#endif /*_ROLE_SUIT_MANAGER_H_*/
