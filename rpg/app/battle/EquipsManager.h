/*
 * EquipsManager.h
 *
 *  Created on: 2019年6月12日
 *      Author: Administrator
 */

#ifndef EQUIPS_MANAGER_H_
#define EQUIPS_MANAGER_H_

#include "BattleBaseInc.h"

#define BAG_ALL					(1)
#define BAG_ZHANLING_EQUIP		(12)
#define BAG_TREASURE_EQUIP		(14)
#define BAG_CARD				(15)
#define BAG_TREASURE_DIANFENG	(16)
#define BAG_TREASURE_SANJIE		(21)
#define BAG_ROLE				(1000)
#define BAG_ROLE_GEM			(1010)
#define BAG_ROLE_RUNE			(1020)
#define BAG_ADVANCE_HORSE		(2000)
#define BAG_ADVANCE_WING		(2010)

#define IS_BAG_ROLE(bag) (bag>BAG_ROLE&&bag<=BAG_ROLE+MAX_ROLE_COUNT)
#define IS_BAG_ROLE_RUNE(bag) (bag>BAG_ROLE_RUNE&&bag<=BAG_ROLE_RUNE+MAX_ROLE_COUNT)
#define IS_TRUMP(id) (id >= 310010001 && id <= 310010009)

class EquipsManager: public CSingleton<EquipsManager> {
private:
	friend class CSingleton<EquipsManager>;
	EquipsManager();

public:
	bool ActorLogin(uint32_t uid);
	bool ActorCreate(uint32_t uid, uint32_t career);
	bool InitRoleBag(UserCache &cache, DataEquip &item);
	bool GetBagList(const UserCache &cache, int16_t type, bool multiRole, vector<msgs::SPlayerBag> &msg);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	bool RandomAttr(DataEquip &equip);
	bool RandomStar(const CfgItem::Equip &cfg, uint32_t &star);
	bool RandomSkill(const CfgItem::Equip &cfg, uint32_t &skill);
	bool RandomSub(const CfgItem::Equip &cfg, uint32_t star, set<uint32_t> &ids);
	bool OpenGift(const UserCache &cache, uint32_t id, uint32_t num, uint32_t select, Award &data);
	bool RandomGift(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t num, Award &data);
	bool RandomExtend(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t num, Award &data);
	bool IsWear(const UserCache &cache, byte rid, byte type);
	bool GetGiftReward(const UserCache& cache, const CfgItem::Gift& cfg, ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v);

public:
	//熔炼
	int Process(uint32_t uid, logins::SBagDecompose *req);
	int Process(uint32_t uid, logins::SEquipEquip *req);
	int Process(uint32_t uid, logins::SBagOpenGrid *req);
	int Process(uint32_t uid, logins::SBagUse *req);
	int Process(uint32_t uid, logins::SBagMoveItem *req);
	int Process(uint32_t uid, logins::SBagMoveItemAll *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerBagList *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerBagItemList *resp);
	int Sync(const UserCache & cache, uint32_t cmd, msgs::SDevilAngelDate *resp);
};

#endif /* EQUIPS_MANAGER_H_ */
