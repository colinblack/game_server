#ifndef __LOGIC_EQUIPMENT_H__
#define __LOGIC_EQUIPMENT_H__

#include "LogicInc.h"

//fashion
#define IS_TEMP_FASHION_EQID(eqid) ((eqid >= 72001 && eqid <= 72050)||(eqid >= 71001 && eqid <= 71050))
#define IS_FOREVER_FASHION_EQID(eqid) ((eqid >= 72101 && eqid <= 72150)||(eqid >= 71101 && eqid <= 71150))
#define IS_FASHION_EQID(eqid) (IS_TEMP_FASHION_EQID(eqid) || IS_FOREVER_FASHION_EQID(eqid))
//horse
#define IS_HORSE_EQID(eqid)  (eqid >= 14001 && eqid <= 14999)
//token
#define IS_TOKEN_EQID(eqid) (eqid >= 18001 && eqid <= 18999)
//eq
#define IS_GENERAL_EQ_EQID(eqid)  ((eqid >= 100001 && eqid <= 128011))
//set
#define IS_SET_EQID(eqid) (eqid >= 151001 && eqid <= 158249)
//信物
#define IS_KEEPSAKE_EQID(eqid) (eqid >= 8001 && eqid <= 8099)
//争霸技能
#define IS_NEW_WORLD_SKILL_EQID(eqid) (eqid >= 13101 && eqid <= 13104)
//星石
#define IS_STAR_STONE_EQID(eqid) (eqid >= 6901 && eqid <= 6999)
//士兵宝物
#define IS_SOILDER_SkILL_EQID(eqid) (eqid >= 25101 && eqid <= 25399)
//英灵
#define IS_YINGLING_EQ_EQID(eqid) (eqid >= 1006000 && eqid <= 1009999 )
//争霸宝石
#define IS_NEWWORLD_STONE_EQID(eqid) ((eqid >= 7101 && eqid <= 7110) || (eqid >= 7201 && eqid <= 7210) || (eqid >= 7301 && eqid <= 7310))

//all eq
#define IS_EQ_EQID(eqid)  (IS_FASHION_EQID(eqid) || IS_HORSE_EQID(eqid) || IS_TOKEN_EQID(eqid)\
		|| IS_GENERAL_EQ_EQID(eqid) || IS_SET_EQID(eqid) || IS_KEEPSAKE_EQID(eqid)\
		|| IS_NEW_WORLD_SKILL_EQID(eqid) || IS_STAR_STONE_EQID(eqid) || IS_SOILDER_SkILL_EQID(eqid) \
		|| IS_YINGLING_EQ_EQID(eqid) || IS_NEWWORLD_STONE_EQID(eqid))

//gem
#define IS_SOULSTONE_EQID(eqid)  (eqid >= 4401 && eqid <= 4490)
#define IS_BUILDSTONE_EQID(eqid)  (eqid >= 4301 && eqid <= 4360)
#define IS_GEM_EQID(eqid) (IS_SOULSTONE_EQID(eqid) || IS_BUILDSTONE_EQID(eqid))
#define IS_NEW_SOULSTONE_EQID(eqid)  (eqid >= 44011 && eqid <= 44140)
//temp gem
#define IS_TEMP_SOULSTONE_EQID(eqid)  (eqid >= 4904 && eqid <= 4909)
#define IS_TEMP_BUILDSTONE_EQID(eqid)  (eqid >= 4804 && eqid <= 4809)
#define IS_TEMP_GEM_EQID(eqid) (IS_TEMP_SOULSTONE_EQID(eqid) || IS_TEMP_BUILDSTONE_EQID(eqid))
//sp gem
#define IS_SPECIALSTONE_EQID(eqid)  (eqid >= 4491 && eqid <= 4500)
//ssp gem
#define IS_SS_SS_EQID(eqid)  (eqid == 9108 || eqid == 9118 || eqid == 9128 || eqid == 9138 || eqid == 9148)
#define IS_SS_BS_EQID(eqid)  (eqid == 9207 || eqid == 9217 || eqid == 9227 || eqid == 9237 || eqid == 9247)
//gem of gem
#define IS_GEM_GEM_EQID(eqid) (eqid >= 9248 && eqid <= 9250)
//建筑双属性宝石
#define IS_DOUBLE_GEM(eqid) (eqid >=4361 && eqid <= 4390)
//five
#define IS_FIVE_ATTACK_STONE_EQID(eqid)  ((eqid >= 75101 && eqid <= 75110) || (eqid >= 75201 && eqid <= 75210) || (eqid >= 75301 && eqid <= 75310) || (eqid >= 75401 && eqid <= 75410) || (eqid >= 75501 && eqid <= 75510))
//限时万能灵珠
#define IS_UNLIMIT_PEARL(eqid) (eqid >= 75002 && eqid <= 75008)
//天降神力
#define IS_TECH_GEM_EQID(eqid) (eqid >= 6601 && eqid <= 6610)

//unoverlay
#define IS_UN_OVERLAY_ID(eqid) (IS_EQ_EQID(eqid) || IS_GEM_EQID(eqid) || IS_TEMP_GEM_EQID(eqid) \
		|| IS_SPECIALSTONE_EQID(eqid) || IS_FIVE_ATTACK_STONE_EQID(eqid) || IS_SS_SS_EQID(eqid) \
		|| IS_SS_BS_EQID(eqid) || IS_UNLIMIT_PEARL(eqid) || IS_GEM_GEM_EQID(eqid) \
		|| IS_DOUBLE_GEM(eqid) || IS_TECH_GEM_EQID(eqid) || IS_NEW_SOULSTONE_EQID(eqid))
//other
#define IS_CAN_SYN_SPECIALSTONE_EQID(eqid)  (eqid >= 4496 && eqid <= 4500)
#define IS_ADVANCED_SET_EQID(eqid) (eqid >= 157001 && eqid <= 157249)
#define IS_INTENSIFY_EQID(eqid)  (eqid >= 4201 && eqid <= 4210)
#define IS_SUCCINCT_EQID(eqid)  (eqid >= 4011 && eqid <= 4014)

#define ACT_BIRD_BRIDGE_LEFT 40991
#define ACT_BIRD_BRIDGE_RIGHT 40992

struct ItemAdd
{
	unsigned eqid, count, ch, q, ats, xwexp, sexp, lexp, hexp;
	string reason;
	Json::Value xwsub;
	ItemAdd()
	{
		eqid = count = ch = q = ats = xwexp = sexp = lexp = hexp = 0;
	}
	ItemAdd(unsigned eqid1, unsigned count1, string reason1, unsigned ch1 = 0, unsigned q1 = 0, unsigned a = 0)
	{
		eqid = eqid1;
		count = count1;
		reason = reason1;
		ch = ch1;
		q = q1;
		ats = a;
		xwexp = 0;
		sexp = 0;
		lexp = 0;
		hexp = 0;
	}
};

class CLogicEquipment
{
public:
	int InitializeEquipment(unsigned uid);
	int GetEquipment(unsigned uid, unsigned uidBy, Json::Value &data);
	int UpdateEquipment(unsigned uid, unsigned uidBy, Json::Value &data, Json::Value &result, bool merge=false);
	int ImportEquipment(unsigned uid, Json::Value &data);
	int GetEquipmentUsed(unsigned uid, Json::Value &data);

	int UseEquipment(unsigned uid, unsigned eqid, unsigned ud, unsigned count, string reason);
	int UseEquipmentEx(unsigned uid, unsigned eqid, unsigned ud, unsigned count, string reason, int &newcount);
	int AddOneItem(unsigned uid, unsigned eqid, unsigned count, string reason,Json::Value &result, bool merge=false, unsigned ch=0, unsigned q=0, unsigned a = 0);
	int AddItems(unsigned uid, vector<ItemAdd> &items, Json::Value &result, bool merge=false);

	int Get(unsigned uid, unsigned id, Json::Value &data);
	int Del(unsigned uid, unsigned id);
	int Chg(unsigned uid, unsigned id, Json::Value &data);

	int Try(unsigned uid, unsigned eqid, unsigned ud, unsigned count);

	int genEquipSet(ItemAdd &item, Json::Value &data, Json::Value &sub, unsigned gemlocks);	//套装
	int genEquip(ItemAdd &item, Json::Value &data);

	int genFashion(ItemAdd &item, bool can_die, unsigned ts, Json::Value &data);	//时装
};

#endif
