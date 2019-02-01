/*
 * DataXML.h
 *
 *  Created on: 2014-4-24
 *      Author: ralf
 */

#ifndef DATAXML_H_
#define DATAXML_H_

#include "Kernel.h"
#include <stdexcept>
#include "DataJsonConfig.h"

/****************Base*********************/
struct GiftEquipment
{
    int id;  //装备ID => id
    int cnt; //数量 => c
    int quality; //品质 => q
    int ch; //ch

    GiftEquipment() : id(0),cnt(0),quality(0), ch(0)
    {

    }

    bool CopyFromJson(const Json::Value& json);
};

///////////////////////////////////////
//保存物品或英雄  映射到共享内存
struct GiftEquipItem
{
public:
	unsigned m_nId; //装备ID => id 或英雄Id
	unsigned m_nCnt; //
	unsigned m_nQuality;
	unsigned m_nCh;

	bool m_bIsHero;

public:
	GiftEquipItem();
	GiftEquipItem(const Json::Value& json, bool ishero);

	bool IsHero() const;
	bool IsEquip() const;
	bool IsSame(GiftEquipItem & othitem); //判断两种选项是否属于同一物品

	void Double();
};


/****************Hero*********************/
#define XML_HERO_STAR 10
#define XML_HERO_RATE 4
#define XML_HERO_NUM 1000
struct XMLHero
{
	unsigned id;
	unsigned type;
	unsigned mix;
	unsigned prof;
	unsigned country;
	unsigned rate[XML_HERO_STAR][XML_HERO_RATE];
	unsigned point;
	unsigned hirecost;
	XMLHero()
	{
		id=type=mix=prof=country=point=hirecost=0;
		memset(rate,0,sizeof(rate));
	}
};
struct DataXMLHero
{
	XMLHero xmlhero[XML_HERO_NUM];
};
/*************************************/

/****************MixHero*********************/
#define XML_HERO_SOURCE 3
#define XML_HERO_SELF -1
struct XMLSourceHero
{
	unsigned heroId;
	unsigned type;
	unsigned star;
	XMLSourceHero()
	{
		heroId = type = star = 0;
	}
};
struct DataXMLMixHero
{
	XMLSourceHero xmlmixhero[XML_HERO_NUM][XML_HERO_STAR-1][XML_HERO_SOURCE];
};
/*************************************/

/*****************boats***************/
#define XML_BOATS_COUNT 5
struct XMLBoat{
	uint32_t id;
	uint32_t time;
	uint32_t reward[3];
	uint32_t rate;
	XMLBoat(){
		id = time = rate = 0;
		memset(reward,0,sizeof(reward));
	}
};
struct DataXMLBoats{
	XMLBoat boats[XML_BOATS_COUNT];
};
/*************************************/

/****************hammer***************/
#define HAMMER_ITEM_NUM 100
struct HammerItem{
	uint32_t id;
	int rate;
	HammerItem(){
		id = 0;
		rate = 0;
	}
	HammerItem(uint32_t id, int rate) {
		this->id = id;
		this->rate = rate;
	}
};
struct XMLHammer {
	int type;
	HammerItem items[HAMMER_ITEM_NUM];
};
struct Hammer{
	int type;
	int total_rate;
	vector<HammerItem> items;
	Hammer(){
		type = total_rate = 0;
	}
};

#define XML_HAMMER_COUNT 4
struct DataXMLHammer{
	XMLHammer hammers[XML_HAMMER_COUNT];
	XMLHammer hammersAllServer[XML_HAMMER_COUNT];
};
/**************************************/

/*************VIP************************/
#define XML_VIP_GRADE 10
#define XML_VIP_PRL 18
struct XMLVIP
{
	unsigned id;
	unsigned type;
	unsigned index;
	unsigned privile[XML_VIP_GRADE];
	unsigned privileS[XML_VIP_GRADE];
	XMLVIP()
	{
		id=type=index=0;
		memset(privile,0,sizeof(privile));
		memset(privileS,0,sizeof(privileS));
	}
};
struct DataXMLVIP
{
	XMLVIP xmlvip[XML_VIP_PRL];
	unsigned vipcharge[XML_VIP_GRADE];
	DataXMLVIP()
	{
		memset(vipcharge,0,sizeof(vipcharge));
	}
};
/*************************************/

/***************EquipSub**********************/
#define XML_EQUIP_SUB_LEVEL 20
#define XML_EQUIP_SUB_ITEM_S 30
#define XML_EQUIP_SUB_GOLD 4
#define XML_EQUIP_SUB_ITEM 10
#define XML_EQUIP_SUB_ID 5

struct XMLEquipSubItem
{
	unsigned star, value, rate;
	XMLEquipSubItem()
	{
		star = value = rate = 0;
	}
};

struct XMLEquipOneSub
{
	char id[XML_EQUIP_SUB_ID];
	unsigned rate;
	XMLEquipSubItem items[XML_EQUIP_SUB_ITEM];
	XMLEquipOneSub()
	{
		memset(id,0,sizeof(id));
		rate = 0;
	}
};

struct XMLEquipSubLevel
{
	unsigned id, start, end, stone, gold[XML_EQUIP_SUB_GOLD];
	XMLEquipOneSub subs[XML_EQUIP_SUB_ITEM_S];
	XMLEquipSubLevel()
	{
		id = start = end = stone = 0;
		memset(gold,0,sizeof(gold));
	}
};

struct DataXMLEquipSub
{
	XMLEquipSubLevel sub[XML_EQUIP_SUB_LEVEL];
};

struct EquipSub
{
	unsigned star, value;
	string id;
	EquipSub()
	{
		star = value = 0;
	}
	EquipSub(unsigned star1, unsigned value1, string id1)
	{
		star = star1;
		value = value1;
		id = id1;
	}
};

struct EquipSubLevel
{
	unsigned id, start, end, stone, gold[XML_EQUIP_SUB_GOLD];
	EquipSubLevel()
	{
		id = start = end = stone = 0;
		memset(gold,0,sizeof(gold));
	}
	EquipSubLevel(unsigned id1,unsigned start1,unsigned end1,unsigned stone1,unsigned gold1[XML_EQUIP_SUB_GOLD])
	{
		id = id1;
		start = start1;
		end = end1;
		stone = stone1;
		memcpy(gold,gold1,sizeof(gold));
	}
	bool operator <(const EquipSubLevel& other) const
	{
		if(start != other.start)
			return start < other.start;
		else if(end != other.end)
			return end < other.end;
		else
			return id < other.id;
	}
};

struct EquipSubItem
{
	unsigned start, end;
	string id;
	EquipSubItem()
	{
		start = end = 0;
	}
	EquipSubItem(unsigned start1, unsigned end1, string id1)
	{
		start = start1;
		end = end1;
		id = id1;
	}
	bool operator <(const EquipSubItem& other) const
	{
		if(start != other.start)
			return start < other.start;
		else if(end != other.end)
			return end < other.end;
		else
			return id < other.id;
	}
};
/*************************************/

/*****************sginvitegiftconfig.xml***************************/
#define XML_INVITE_REWARD_ITEM_MAX (5)
#define XML_INVITE_LEVEL_ITEMS_MAX (30)
struct XMLInviteDayGiftItem
{
	unsigned equipsCnt;
	GiftEquipment equips[XML_INVITE_REWARD_ITEM_MAX];

	XMLInviteDayGiftItem() : equipsCnt(0)
	{

	}
};

struct XMLInviteLevelGiftItem
{
	unsigned id;
	unsigned level;
	unsigned number;
	unsigned equipsCnt;
	GiftEquipment equips[XML_INVITE_REWARD_ITEM_MAX];

	XMLInviteLevelGiftItem() : id(0),level(0),number(0),equipsCnt(0)
	{

	}
};


struct DataXMLsginvitegiftconfig
{
	XMLInviteDayGiftItem dayItem;
	XMLInviteLevelGiftItem levelItems[XML_INVITE_LEVEL_ITEMS_MAX];
};

/*****************sgsigninnewconfig.xml***************************/
#define SIGNIN_REWARDS_NUM (5) 
#define SIGNIN_EQUIP_ITEMS (5)
struct XMLSignInReward
{
	int gold; //金币
	int prosper; //威望
	int equipCnt; //记录装备的数

	GiftEquipment equips[SIGNIN_EQUIP_ITEMS]; //装备列表

	XMLSignInReward() : gold(0), prosper(0), equipCnt(0)
	{

	}
};

struct DataXMLsgsigninnewconfig
{
	XMLSignInReward rewards[SIGNIN_REWARDS_NUM];
};

/********************************************/

//--------------------------------------------
//武魂消耗
#define XML_WEAPON_SOUL_ITEMS_MAX (120)
struct XMLWeaponSoulCostItem
{
	unsigned id;
	unsigned cost;
	float    discount;

	XMLWeaponSoulCostItem()
		: id(0), cost(0), discount(0)
	{

	}
};

struct DataXMLpartpowerconfig
{
	XMLWeaponSoulCostItem items[XML_WEAPON_SOUL_ITEMS_MAX];
};
//end

/**************GiftBag***********************/
#define XML_GIFT_MAX 128
#define DATA_GIFT_MAX 1000
#define GIFT_BAG_LEVEL_COUNT 10
#define XML_GIFT_TYPE 32
#define XML_GIFT_DATA 128
struct XMLGiftBag
{
	char type[XML_GIFT_TYPE];
	char data[XML_GIFT_DATA];
	unsigned flag;
	unsigned rate;
	XMLGiftBag()
	{
		flag=rate=0;
		memset(type,0,sizeof(type)-1);
		memset(data,0,sizeof(data)-1);
	}

};
struct XMLGiftBagAll
{
	unsigned id;
	XMLGiftBag gift[XML_GIFT_MAX];
	XMLGiftBagAll()
	{
		id = 0;
	}

};
struct XMLGifgBagLvl
{
	unsigned id;
	unsigned level;
	char data[XML_GIFT_DATA];
	XMLGifgBagLvl()
	{
		id = 0;
		level = 0;
		memset(data,0,sizeof(data));
	}
};
struct DataXMLsggiftbagconfig
{
	XMLGiftBagAll GiftBag[DATA_GIFT_MAX];
	XMLGifgBagLvl GiftBagLevel[GIFT_BAG_LEVEL_COUNT];
};
/*************************************/

/***************************************/
//struct XMLInviteLevelGift
//{
//   unsigned id;
//   unsigned level;
//   unsigned number;
//   std::vector<GiftEquipment> equipments;
//
//   XMLInviteLevelGift() : id(0), level(0), number()
//   {}
//}
//
//struct DataXMLsginvitegiftconfig
//{
//    GiftEquipment dayGift;
//    std::map<XMLInviteLevelGift>
//}


/**************Test***********************/
struct DataXML3
{
	unsigned xml;
};
struct DataXML4
{
	unsigned xml;
};
/*************************************/

/**************TreasureHunt***********************/
#define XML_TREASURE_HUNT 500
#define XML_TREASURE_COIN 5
#define XML_TREASURE_CASH 10
#define XML_TREASURE_RAND 6
#define XML_TREASURE_RATE 1000
enum TreasureHuntItemType
{
	TreasureHuntItemType_Point 	= 1,
	TreasureHuntItemType_Jade 	= 2,
	TreasureHuntItemType_Equip 	= 3,
	TreasureHuntItemType_Double = 4,

	TreasureHuntItemType_Max
};
struct TreasureHuntItem
{
	unsigned id,type,point,jade,equip,count,rate;
	TreasureHuntItem()
	{
		id = type = point = jade = equip = count = rate = 0;
	}
};
struct DataXMLTreasureHunt
{
	TreasureHuntItem item[XML_TREASURE_HUNT];
};
/*************************************/

/**************EquipIntensifys  装备强化***********************/
#define XML_EQUIPINTENSIFYS_COUNT 20

struct EquipIntensifys
{
	unsigned id;
	unsigned rate[10];
	unsigned addrate[10];
	unsigned yijian[10];			//拆解所有等级一键搞定对应的幸运石数量 *0.3
	EquipIntensifys()
	{
		id = 0;
		memset(rate,0,sizeof(rate));
		memset(addrate,0,sizeof(addrate));
		memset(yijian,0,sizeof(yijian));
	}
};
struct DataXMLequipintensifys
{
	EquipIntensifys IntensifysItem[XML_EQUIPINTENSIFYS_COUNT];
};
/*************************************/

/**************Equipolequipset***********************/
#define XML_EQUIPQIANGHUA_COUNT 10
#define XML_EQUIPSET_COUNT 128

struct EquipQiangHua
{
	unsigned q_level;
	unsigned q_id;
	unsigned q_number;

	EquipQiangHua()
	{
		q_level = q_id = q_number = 0;
	}
};

//套装拆解
struct EquipSetDismantling
{
	unsigned level;
	unsigned part;
	unsigned MaterialsNum;
	EquipSetDismantling()
	{
		level = part = MaterialsNum = 0;
	}
};

//套装打造或升级
struct EquipSetBulidOrUp
{
	unsigned level;
	unsigned part;
	char data[256];
	EquipSetBulidOrUp()
	{
		level = part = 0;
		memset(data,0,sizeof(data));
	}
};

//110级套装精炼
struct EquipSetJinglian
{
	char data[256];
	EquipSetJinglian()
	{
		memset(data,0,sizeof(data));
	}
};

//套装五行洗练
#define XML_EQUIPSET_WUXING 7
#define WUXING_RATE_MAX 10000
struct EquipSetWuxing
{
	unsigned level;
	float rate;
	unsigned count;
	unsigned bs;
	EquipSetWuxing()
	{
		level = count = bs = 0;
		rate = 0;
	}
};

//套装祝福
#define XML_EQUIPSET_BLESS 10
struct EquipSetBless
{
	unsigned level;
	unsigned exp;
	unsigned eqid;
	unsigned needeqcount;
	unsigned bs;
	unsigned minrate;
	unsigned maxrate;
	EquipSetBless()
	{
		level = exp = eqid = needeqcount = bs = minrate = maxrate = 0;
	}
};

struct EquipSetShenGe
{
	unsigned level;
	unsigned exp;
	unsigned eqid[3];
	unsigned needeqcount[3];
	unsigned bs;
	unsigned minrate;
	unsigned maxrate;
	EquipSetShenGe()
	{
		level = exp = bs = minrate = maxrate = 0;
		memset(eqid, 0, sizeof(eqid));
		memset(needeqcount, 0, sizeof(needeqcount));
	}
};

struct DataXMLolequipset
{
	EquipQiangHua StoneItem[XML_EQUIPQIANGHUA_COUNT];
	EquipSetDismantling Setitem[XML_EQUIPSET_COUNT];
	EquipSetBulidOrUp BulidOrUp[XML_EQUIPSET_COUNT];
	EquipSetJinglian Jinglian;
	EquipSetJinglian ShenZhu;
	EquipSetJinglian ShenQi;
	EquipSetWuxing Wuxing[XML_EQUIPSET_WUXING];
	EquipSetBless Bless[XML_EQUIPSET_BLESS];
	EquipSetBless ShenWen[XML_EQUIPSET_BLESS];
	EquipSetShenGe ShenGe[XML_EQUIPSET_BLESS];
};
/*************************************/

/**************Payrank 物品为代码中直接写死***********************/
#define PAYRANK_COUNT 7
#define PAYRANK_LEVEL 3
struct Payrank
{
	unsigned id;
	unsigned count;
	unsigned rate;
	Payrank()
	{
		id = count = rate = 0;
	}

	Payrank(unsigned id1, unsigned count1, unsigned rate1)
	{
		id = id1;
		count = count1;
		rate = rate1;
	}
};

//100积分对应奖品
#define PAYRANK_LEVEL_1_1 Payrank(4201,2,1600)
#define PAYRANK_LEVEL_1_2 Payrank(42015,1,1600)
#define PAYRANK_LEVEL_1_3 Payrank(50011,2,1600)
#define PAYRANK_LEVEL_1_4 Payrank(4022,1,1500)
#define PAYRANK_LEVEL_1_5 Payrank(4004,6,1400)
#define PAYRANK_LEVEL_1_6 Payrank(50040,1,1300)
#define PAYRANK_LEVEL_1_7 Payrank(11112,1,1000)

//300积分对应奖品
#define PAYRANK_LEVEL_2_1 Payrank(4011,7,1500)
#define PAYRANK_LEVEL_2_2 Payrank(4205,1,1600)
#define PAYRANK_LEVEL_2_3 Payrank(50033,2,1600)
#define PAYRANK_LEVEL_2_4 Payrank(50013,3,1500)
#define PAYRANK_LEVEL_2_5 Payrank(50041,2,1400)
#define PAYRANK_LEVEL_2_6 Payrank(11111,2,1200)
#define PAYRANK_LEVEL_2_7 Payrank(11112,2,1200)

//1000积分对应奖品
#define PAYRANK_LEVEL_3_1 Payrank(50042,4,1900)
#define PAYRANK_LEVEL_3_2 Payrank(50014,3,2000)
#define PAYRANK_LEVEL_3_3 Payrank(4031,40,1700)
#define PAYRANK_LEVEL_3_4 Payrank(50034,8,1700)
#define PAYRANK_LEVEL_3_5 Payrank(11112,9,1600)
#define PAYRANK_LEVEL_3_6 Payrank(4208,1,800)
#define PAYRANK_LEVEL_3_7 Payrank(3207,1,300)

//4399改版
//50积分对应奖品
#define PAYRANK_LEVEL_4_1_1 Payrank(40121,2,1600)
#define PAYRANK_LEVEL_4_1_2 Payrank(4201,1,1600)
#define PAYRANK_LEVEL_4_1_3 Payrank(50011,2,1600)
#define PAYRANK_LEVEL_4_1_4 Payrank(4022,1,1500)
#define PAYRANK_LEVEL_4_1_5 Payrank(4203,6,1400)
#define PAYRANK_LEVEL_4_1_6 Payrank(11111,1,1300)
#define PAYRANK_LEVEL_4_1_7 Payrank(11112,1,1000)

//250积分对应奖品
#define PAYRANK_LEVEL_4_2_1 Payrank(4011,7,1500)
#define PAYRANK_LEVEL_4_2_2 Payrank(4205,1,1600)
#define PAYRANK_LEVEL_4_2_3 Payrank(40123,2,1600)
#define PAYRANK_LEVEL_4_2_4 Payrank(50041,3,1500)
#define PAYRANK_LEVEL_4_2_5 Payrank(11111,2,1400)
#define PAYRANK_LEVEL_4_2_6 Payrank(6001,2,1200)
#define PAYRANK_LEVEL_4_2_7 Payrank(50013,2,1200)

//800积分对应奖品
#define PAYRANK_LEVEL_4_3_1 Payrank(50042,4,1900)
#define PAYRANK_LEVEL_4_3_2 Payrank(50014,3,2000)
#define PAYRANK_LEVEL_4_3_3 Payrank(4031,40,1700)
#define PAYRANK_LEVEL_4_3_4 Payrank(50034,8,1700)
#define PAYRANK_LEVEL_4_3_5 Payrank(11112,9,1600)
#define PAYRANK_LEVEL_4_3_6 Payrank(4208,1,800)
#define PAYRANK_LEVEL_4_3_7 Payrank(3207,1,300)
/*************************************/

/*************shop************************/
#define XML_SHOP_ALL_ITEM 1000
struct XMLShop
{
	unsigned id, price, type, ch, vip;
	XMLShop()
	{
		id = price = type = ch = vip = 0;
	}
};
struct DataXMLShop
{
	XMLShop shop[XML_SHOP_ALL_ITEM];
};
/*************************************/

/*************worldBattleShop************************/
#define XML_WORLD_BATTLE_SHOP_ALL_ITEM 200
#define XML_WORLD_BATTLE_KILL_ITEM_NUM 12
struct XMLWorldBattleShopItem
{
	unsigned id, getItem, getCount, type, costItem, costCount, times;
	XMLWorldBattleShopItem()
	{
		id = getItem = getCount = type = costCount = costItem = times = 0;
	}
};
struct XMLWorldBattleKillRewardsItem
{
	unsigned kill;
	char data[256];
	XMLWorldBattleKillRewardsItem()
	{
		kill = 0;
		memset(data,0,sizeof(data));
	}
};

struct DataXMLWorldBattleShop
{
	XMLWorldBattleShopItem shop[XML_WORLD_BATTLE_SHOP_ALL_ITEM];
	XMLWorldBattleKillRewardsItem kill[XML_WORLD_BATTLE_KILL_ITEM_NUM];
};
/*************************************/

/*************rankBattleShop************************/
#define XML_RANK_BATTLE_SHOP_ALL_ITEM 200
struct XMLRankBattleShopItem
{
	unsigned id, getItem, getCount, type, costItem, costCount, times;
	XMLRankBattleShopItem()
	{
		id = getItem = getCount = type = costCount = costItem = times = 0;
	}
};
struct DataXMLRankBattleShop
{
	XMLRankBattleShopItem shop[XML_RANK_BATTLE_SHOP_ALL_ITEM];
};
/*************************************/

//暑假前奏 @start
#define XML_DATA_PRESUMMER_ITEMS (3)
struct XMLPreSummerItem
{
	unsigned id;
	GiftEquipment equip;

	XMLPreSummerItem() : id(0)
	{

	}
};

struct DataXMLPreSummer
{
	unsigned cost[XML_DATA_PRESUMMER_ITEMS], cost2[XML_DATA_PRESUMMER_ITEMS], cost3[XML_DATA_PRESUMMER_ITEMS];
	XMLPreSummerItem items[XML_DATA_PRESUMMER_ITEMS], items2[XML_DATA_PRESUMMER_ITEMS], items3[XML_DATA_PRESUMMER_ITEMS];
};
//@end

//@ 天坛
#define XML_DATA_TEMPLE_ITEMS (7)
#define XML_DATA_GOODS_CNT (10)
struct XMLTempleItem
{
	unsigned id;
	unsigned cost;
	unsigned level;
	unsigned rate[XML_DATA_GOODS_CNT];
	GiftEquipment equips[XML_DATA_GOODS_CNT];

	XMLTempleItem()
		: id(0),cost(0),level(0)
	{
		memset(rate, 0, sizeof(rate) / sizeof(rate[0]));
	}

	//随机获取一个物品
	int GetRandomEquipIndex();
};

struct DataXMLTemple
{
	XMLTempleItem items[XML_DATA_TEMPLE_ITEMS];
};
//@end

//开区充值大礼包
#define XML_DATA_NEW_RECHARGE_REWARD_ITEMS (5)
#define XML_DATA_NEW_RECHARGE_ITEMS (8)
struct XMLNewRechargeRewardItem
{
	unsigned id;
	unsigned needRecharge;
	GiftEquipItem items[XML_DATA_NEW_RECHARGE_REWARD_ITEMS];

	std::vector<std::string > GetHeros() const;
};

struct DataXMLNewRecharge
{
	XMLNewRechargeRewardItem items[XML_DATA_NEW_RECHARGE_ITEMS];
};
//end


//月度礼包
struct DataXMLMonthGiftBagZone
{
	enum {
		EQUIP_ITEMS = 3,
	};

	unsigned zoneStart;
	unsigned zoneEnd;
	unsigned equips[EQUIP_ITEMS];

	DataXMLMonthGiftBagZone() :zoneStart(0),zoneEnd(0)
	{
		memset(equips, 0, sizeof(equips));
	}

	unsigned GetEquipId(unsigned index);
	bool InZone(unsigned zoneId) const;
};

struct DataXMLMonthGiftBag
{
	enum {
		ZONE_CNT = 2,
	};

	DataXMLMonthGiftBagZone zones[ZONE_CNT];
	DataXMLMonthGiftBagZone zones4399[ZONE_CNT];
};
//@end

//////////////////////////////////////////////////////////////////
//组合商店
struct DataXMLCombinedShopItem
{
	enum {
		EQUIP_CNT = 8,
	};

	unsigned cost; //
	unsigned limit;

	unsigned equipsId[EQUIP_CNT];
	unsigned equipsCnt[EQUIP_CNT];

	DataXMLCombinedShopItem() : cost(0), limit(0)
	{
		memset(equipsId, 0, sizeof(equipsId));
		memset(equipsCnt, 0, sizeof(equipsCnt));
	}

	unsigned GetEquipCnt(unsigned eqid);
};

struct DataXMLCombinedShop
{
	enum {
		ITEMS_CNT = 3,
	};

	DataXMLCombinedShopItem items[ITEMS_CNT];
};
//@end

//////////////////////////////////////////////////////////////////
//预告功能
struct DataXMLNewerAdvanceItem
{
	unsigned id;
	unsigned level; //等级
	unsigned exp; //奖励经验
	unsigned gold; //奖励金币

	DataXMLNewerAdvanceItem() : id(0),level(0),exp(0), gold(0)
	{}
};

struct DataXMLNewerAdvance
{
	enum {
		ITEMS_CNT = 32,
	};

	DataXMLNewerAdvanceItem items[ITEMS_CNT];
};
//@end

//////////////////////////////////////////////////////////////////
//步步为营  兑换
struct DataXMLTreasureHuntExchangeItem
{
	unsigned id;
	unsigned count;
	unsigned cost;

	DataXMLTreasureHuntExchangeItem() : id(0),count(0),cost(0)
	{}
};

struct DataXMLTreasureHuntExchange
{
	enum {
		ITEMS_CNT = 10,
	};

	DataXMLTreasureHuntExchangeItem point[ITEMS_CNT];
	DataXMLTreasureHuntExchangeItem jade[ITEMS_CNT];
};

//@end

//////////////////////////////////////////////////////////////////
//圣诞活动
struct DataXMLChristmasExtraItem
{
	unsigned id;
	unsigned point;
	unsigned limit;
	GiftEquipItem item;

	DataXMLChristmasExtraItem() : id(0), point(0), limit(0)
	{

	}
};

struct DataXMLChristmasEggItem
{
	unsigned id;
	unsigned rate;
	unsigned show;
	GiftEquipItem item;

	DataXMLChristmasEggItem() : id(0), rate(0),show(0)
	{

	}
};

struct DataXMLChristmasEgg
{
	enum {
		ITEMS_CNT = 15,
	};
	unsigned id;
	unsigned point;
	unsigned cold;
	DataXMLChristmasEggItem items[ITEMS_CNT];

	DataXMLChristmasEgg() : id(0), point(0), cold(0)
	{

	}
};

struct DataXMLChristmas
{
	enum {
		EGG_ITEMS = 3,
		EXTRA_ITEMS = 12,
	};

	DataXMLChristmasExtraItem 	extra[EXTRA_ITEMS];
	DataXMLChristmasEgg			egg[EGG_ITEMS];
};
//@end


//积分换礼
struct DataXMLPointExchageRewardItem
{
	enum {
		ITEM_CNT = 5,
	};
	unsigned 		require;
	GiftEquipItem 	items[ITEM_CNT];
};

struct DataXMLPointCutPriceItem
{
	unsigned id;
	unsigned item_id;
	unsigned price;
	unsigned needLv;

	DataXMLPointCutPriceItem()
		: id(0),item_id(0),price(0),needLv(0)
	{

	}
};

struct DataXMLPointCutPrice
{
	enum{
		LEVLE_CNT = 2,
		ITEM_CNT  = 4,
	};

	unsigned 					lvlInt[LEVLE_CNT];
	DataXMLPointCutPriceItem 	items[ITEM_CNT];

	unsigned LevelByPoint(unsigned point) const;

	DataXMLPointCutPrice()
	{
		memset(lvlInt, 0, sizeof(unsigned)*LEVLE_CNT);
	}
};

struct DataXMLPointExchange
{
	enum {
		ITEM_CNT = 6,
	};
	DataXMLPointExchageRewardItem items[ITEM_CNT];
	DataXMLPointCutPrice		  cut_price;
};
//@end

//每日团购
struct DataXMLGroupBuyDailyBuyItem
{
	enum {
		EQUIP_ITEMS = 2,
		RS_ITEMS = 4,
	};

	////////////////////////////////////
	unsigned price;
	unsigned rs[RS_ITEMS];
	GiftEquipItem items[EQUIP_ITEMS];

	DataXMLGroupBuyDailyBuyItem() : price(0)
	{
		memset(rs, 0, sizeof(rs) / sizeof(rs[0]));
	}
};

struct DataXMLGroupBuyDailyReward
{
	enum {
		EQUIP_ITEMS = 2,
	};
	unsigned id;
	unsigned point;
	GiftEquipItem items[EQUIP_ITEMS];
};

struct DataXMLGroupBuyDaily
{
	enum {
		REWARD_CNT = 6,
	};

	DataXMLGroupBuyDailyBuyItem buyItem;
	DataXMLGroupBuyDailyReward 	rewards[REWARD_CNT];
};
//@end

//建筑皮肤
//
struct DataXMLBuildingSkinReletItem
{
	unsigned id;
	unsigned time;
	unsigned cost;

	DataXMLBuildingSkinReletItem()
		: id(0),time(0),cost(0)
	{

	}
};

struct DataXMLBuildingSkinRelet
{
	enum {
		ITEM_CNT = 4,
	};

	unsigned 					 id;
	DataXMLBuildingSkinReletItem items[ITEM_CNT];

	DataXMLBuildingSkinRelet() : id(0)
	{

	}
};

struct DataXMLBuildingSkinBuy
{
	unsigned id;
	unsigned eqid;
	unsigned cost;

	DataXMLBuildingSkinBuy()
		: id(0), eqid(0),cost(0)
	{

	}
};

struct DataXMLBuildingSkin
{
	enum {
		ITEM_CNT = 5,
	};

	DataXMLBuildingSkinBuy 		buys[ITEM_CNT];
	DataXMLBuildingSkinRelet   	relets[ITEM_CNT];
};
//@end
//7日登录
struct DataXMLTutorLoginItem
{
	enum {
		EUIP_CNT = 4,
		RS_CNT	 = 4,
	};
	unsigned id;
	unsigned day;
	unsigned rs[RS_CNT];
	unsigned gold;
	unsigned prosper;
	GiftEquipItem equips[EUIP_CNT];

	DataXMLTutorLoginItem()
		: id(0),day(0),gold(0),prosper(0)
	{
		memset(rs, 0, sizeof(rs));
	}
};

struct DataXMLTutorLogin
{
	enum {
		ITEM_CNT = 12,
	};

	DataXMLTutorLoginItem items[ITEM_CNT];
};

//霸业礼包
struct DataXMLImperialGiftItem
{
	enum {
		EUIP_CNT = 4,
	};

	unsigned id;
	unsigned end;   //需要等级
	unsigned cost;
	GiftEquipItem equips[EUIP_CNT];

	DataXMLImperialGiftItem()
		: id(0),end(0),cost(0)
	{

	}
};

struct DataXMLImperialGift
{
	enum {
		ITEM_CNT = 10,
	};

	DataXMLImperialGiftItem items[ITEM_CNT];
};

//限时冲级
struct DataXMLTimeLimitUpgradeItem
{
	enum {
			EUIP_CNT = 2,
	};

	unsigned gold;
	GiftEquipItem equips[EUIP_CNT];

	DataXMLTimeLimitUpgradeItem() : gold(0)
	{

	}
};

struct DataXMLTimeLimitUpgrade
{
	enum {
		ITEM_CNT = 8,
	};

	DataXMLTimeLimitUpgradeItem items[ITEM_CNT];
};

//充点小钱
struct DataXMLLittleRechargeZone
{
	enum {
		EQUIP_ITEMS = 4,
	};

	unsigned zoneStart;
	unsigned zoneEnd;
	GiftEquipItem items[EQUIP_ITEMS];
};

struct DataXMLLittleRecharge
{
	enum  {
		ZONE_CNT = 2,
	};
	DataXMLLittleRechargeZone zoneGeneral[ZONE_CNT];
	DataXMLLittleRechargeZone zone4399[ZONE_CNT];
};
//@end

//////////////////////////////////////////////////
//鸡年纳福
struct DataXMLYearFortuneItem
{
	enum {
		EQUIP_CNT = 1,
	};

	unsigned 		id;
	unsigned 		rate;
	GiftEquipItem 	equips[EQUIP_CNT];

	DataXMLYearFortuneItem():id(0),rate(0) {}
};

struct DataXMLYearFortuneLib
{
	enum {
		ITEM_CNT = 11,
	};

	unsigned 				id;
	DataXMLYearFortuneItem items[ITEM_CNT];

	DataXMLYearFortuneLib() : id(0){}

	int GetRandomItemOfId() const;
	DataXMLYearFortuneItem GetItem(unsigned id);
};

struct DataXMLYearFortune
{
	enum {
		LIB_CNT = 3,
		STAGE_CNT = 7,
	};
	DataXMLYearFortuneLib libs[LIB_CNT];
};


//寒假狂欢
class DataWinterHolidayRevelry
{
public:
	struct DataDrawRewardItem
	{
		DataDrawRewardItem(const Json::Value& json_data)
		{
			id = json_data["id"].asUInt();
			count = json_data["count"].asUInt();
			rate = json_data["rate"].asUInt();

			if (id == 0 || count == 0)
			{
				throw std::runtime_error("json_DataWinterHolidayRevelry_DrawRewardItem_error");
			}
		}

		DataDrawRewardItem() : id(0),count(0),rate(0) {}

		unsigned id;
		unsigned count;
		unsigned rate;
	};

	struct DataGetRewardItem
	{
		DataGetRewardItem(const Json::Value& json_data)
		{
			id  = json_data["id"].asUInt();
			need = json_data["need"].asUInt();
			count = json_data["count"].asUInt();
		}

		DataGetRewardItem() : id(0),need(0),count(0) {}

		unsigned id;
		unsigned need;
		unsigned count;
	};
public:
	DataWinterHolidayRevelry(const Json::Value& json);
	DataWinterHolidayRevelry():total_draw_reward_rate_(0) {}

	int RandomDrawRewardIndex() const;
	const DataWinterHolidayRevelry::DataDrawRewardItem& DrawRewardItem(int index) const;
	int GetRewardItemsSize() const;
	const DataWinterHolidayRevelry::DataGetRewardItem& GetRewardItem(int index) const;
private:
	unsigned total_draw_reward_rate_;
	std::vector<DataDrawRewardItem> _v_draw_reward;
	std::vector<DataGetRewardItem> 	_v_get_reward;
};

//信物强化
class DataTokenIntensify
{
public:
	class GoodsItem
	{
	public:
		GoodsItem(const Json::Value& jsonData)
		{
			index_ = jsonData["index"].asInt();
			item_id_ = jsonData["id"].asInt();
			count_	 = jsonData["count"].asInt();
			user_limit_ = jsonData["limit"].asInt();
			point_ = jsonData["point"].asInt();

			if (0 == item_id_|| 0 == count_ || 0 == user_limit_  || 0 == point_)
			{
				throw std::runtime_error("config_error");
			}
		}

		GoodsItem() : index_(0),item_id_(0),count_(0), user_limit_(0),point_(0)
		{}

		int Index() const { return index_; }
		int ItemId() const 	{ return item_id_; }
		int Count() const	{ return count_; }
		int UserLimit() const { return user_limit_; }
		int Point() const { return point_; }

		virtual ~GoodsItem() {}
	private:
		int index_;
		int item_id_;
		int count_;
		int user_limit_;
		int point_;
	};

	class ZoneItem : public GoodsItem
	{
	public:
		ZoneItem() : zone_limit_(0)
		{}

		ZoneItem(const Json::Value& jsonData)
			: GoodsItem(jsonData)
		{
			zone_limit_ = jsonData["zonelimit"].asInt();
			if (0 == zone_limit_)
			{
				throw std::runtime_error("config_error");
			}
		}

		int ZoneLimit() const { return zone_limit_; }
	private:
		int zone_limit_;
	};

	DataTokenIntensify() {}

	DataTokenIntensify(const Json::Value& jsonData)
	{
		Json::Value jsonZones;
		Json::Value jsonItems;
		Json::GetArray(jsonData, "zone", jsonZones);
		Json::GetArray(jsonData, "normal", jsonItems);

		for (size_t i = 0; i < jsonZones.size(); i++)
		{
			v_zone_items_.push_back(ZoneItem(jsonZones[i]));
		}

		for (size_t i = 0; i < jsonItems.size(); i++)
		{
			v_normal_items_.push_back(GoodsItem(jsonItems[i]));
		}

		if (v_normal_items_.empty() || v_zone_items_.empty())
		{
			throw std::runtime_error("config_items_empty");
		}
	}

	const std::vector<GoodsItem>& NormalItems() const { return v_normal_items_; }
	const std::vector<ZoneItem>& ZoneItems() const { return v_zone_items_; }

	const ZoneItem& GetZoneItem(int index) const
	{
		if (index < 0 || index >= (int)v_zone_items_.size())
		{
			throw std::runtime_error("out_zone_items");
		}

		return v_zone_items_[index];
	}

	const GoodsItem& GetGoodsItem(int index) const
	{
		if (index < 0 || index >= (int)v_normal_items_.size())
		{
			throw std::runtime_error("out_goods_items");
		}

		return v_normal_items_[index];
	}
private:
	std::vector<GoodsItem> v_normal_items_;
	std::vector<ZoneItem>  v_zone_items_;
};

//世间秘宝
class ConfigWorldTreasure
{
public:
	class GoodsItem
	{
	public:
		GoodsItem():id_(0),cnt_(0),prob_(0){}

		GoodsItem(const Json::Value& jsonData);


		unsigned Id() const { return id_; }
		unsigned Cnt() const { return cnt_; }
		unsigned Prob() const { return prob_; }
	private:
		unsigned id_;
		unsigned cnt_;
		unsigned prob_;
	};

	class AmountItem
	{
	public:
		AmountItem(): value_(0),items_(0) {}
		AmountItem(const Json::Value& jsonData);

		unsigned Value() const { return value_; }
		unsigned Items() const { return items_; }
	private:
		unsigned value_;  //额度
		unsigned items_;   //可兑换的密匙
	};
public:
	ConfigWorldTreasure() {}

	ConfigWorldTreasure(const Json::Value& jsonData);

	const AmountItem& GetAmount(int stage) const;
	int GetCostProps(int type) const;

	const std::vector<GoodsItem>& GetGoodsLib(int type) const;
	int RandomItem(const std::vector<int>& vExclude, int type) const;
	const GoodsItem& GetGoodsItem(int index, int type) const;
private:
	std::vector<GoodsItem>& GetGoodsLib(int type);
private:
	std::vector<AmountItem> v_amount_items_;

	std::vector<int> v_cost_props_;

	std::vector<GoodsItem> v_primary_lib_; //初级库
	std::vector<GoodsItem> v_middle_lib_; //
	std::vector<GoodsItem> v_high_lib_;
	std::vector<GoodsItem> v_super_lib_;
};

//武魂回馈
class ConfigSoulFeedback
{
public:
	class Item
	{
	public:
		Item():amount_(0) {}
		Item(const Json::Value& jsonData);

		int Amount() const { return amount_; }
		int EquipId(int idx) const;
		int EquipCnt(int idx) const;
	private:
		int amount_;
		std::vector<int> v_equips_id_;
		std::vector<int> v_equips_cnt_;
	};

	ConfigSoulFeedback() {}
	ConfigSoulFeedback(const Json::Value& jsonData);
	ConfigSoulFeedback(const char* name);

	virtual ~ConfigSoulFeedback() {}

	int ItemsSize() const { return v_rewards_.size(); }

	const Item& GetRewards(int index) const;
protected:
	std::vector<Item> v_rewards_;
};

//觉醒回馈
class ConfigAwakenFeedback : public ConfigSoulFeedback
{
public:
	ConfigAwakenFeedback() {}
	ConfigAwakenFeedback(const Json::Value& jsonData);
};

//铸魂打折
class ConfigCastSoulDiscount : public ConfigSoulFeedback
{
public:
	ConfigCastSoulDiscount() {}
	ConfigCastSoulDiscount(const Json::Value& jsonData);
};

//宝石折扣
class ConfigGemDiscount
{
public:
	class Item
	{
	public:
		Item():eq_id_(0),eq_cnt_(0), limit_(0) {}
		Item(const Json::Value& jsonData);
		int EquipId() const { return eq_id_; }
		int EquipCnt() const  { return eq_cnt_ ;}
		int Limit() const { return limit_; }
	private:
		int eq_id_; //
		int eq_cnt_;
		int limit_;
	};
public:
	ConfigGemDiscount()  {}
	ConfigGemDiscount(const Json::Value& jsonData);
	int 			ItemsSize() const { return v_items_.size(); }
	const Item&  	GetItem(int index) const;
	int 			GetUseCnt(int point) const;
private:
	std::vector<Item> v_items_;
	std::vector<int> v_stages_;
};

//金玉满堂
class ConfigTreasuresAllAround
	: public JsonItemsConfig<JsonLotteryItemCfg>
{
	typedef JsonItemsConfig<JsonLotteryItemCfg> base;
public:
	ConfigTreasuresAllAround() {}
	ConfigTreasuresAllAround(const Json::Value& data);
};

//将灵培养
class ConfigSpiritFoster
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigSpiritFoster() {}
	ConfigSpiritFoster(const Json::Value& data)
		: base(data["spirit_foster"])
	{

	}
};

//的卢凝魂
class ConfigChargeHorse
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigChargeHorse() {}
	ConfigChargeHorse(const Json::Value& data)
		: base(data[CONFIG_CHARGE_HORSE])
	{

	}
};

//vicky又要做个充值活动
class ConfigVickyAccX
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX() {}
	ConfigVickyAccX(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X])
	{

	}
};
//vicky又要做个充值活动1
class ConfigVickyAccX1
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX1() {}
	ConfigVickyAccX1(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X1])
	{

	}
};
//vicky又要做个充值活动2
class ConfigVickyAccX2
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX2() {}
	ConfigVickyAccX2(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X2])
	{

	}
};
//vicky又要做个充值活动3
class ConfigVickyAccX3
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX3() {}
	ConfigVickyAccX3(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X3])
	{

	}
};
//vicky又要做个充值活动4
class ConfigVickyAccX4
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX4() {}
	ConfigVickyAccX4(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X4])
	{

	}
};
//vicky又要做个充值活动5
class ConfigVickyAccX5
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyAccX5() {}
	ConfigVickyAccX5(const Json::Value& data)
		: base(data[CONFIG_VICKY_ACC_X5])
	{

	}
};
//机甲黄忠
class Confighuangzhong
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	Confighuangzhong() {}
	Confighuangzhong(const Json::Value& data)
		: base(data[CONFIG_huangzhong])
	{

	}
};
//vicky的开服活动
class ConfigVickyNewOpen
	: public JsonItemsConfig<JsonFeedbackItem>
{
	typedef JsonItemsConfig<JsonFeedbackItem> base;
public:
	ConfigVickyNewOpen() {}
	ConfigVickyNewOpen(const Json::Value& data)
		: base(data[CONFIG_VICKY_NEW_OPEN])
	{

	}
};

/********************************************************************/
/*  活动太多  先是抽象成模板  最后只能搞宏       */
#define CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME) \
		class CONFIG_NAME##_CONFIG \
			: public JsonItemsConfig<JsonFeedbackItem> \
		{ \
			typedef JsonItemsConfig<JsonFeedbackItem> base; \
		public: \
			CONFIG_NAME##_CONFIG() {} \
			CONFIG_NAME##_CONFIG(const Json::Value& data) \
				: base(data[CONFIG_NAME]) {} \
		};

#define GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME) \
	const CONFIG_NAME##_CONFIG& Get_##CONFIG_NAME() const {return m_##CONFIG_NAME;} \
	CONFIG_NAME##_CONFIG m_##CONFIG_NAME; \

#define INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME) m_##CONFIG_NAME = CONFIG_NAME##_CONFIG(data);
/********************************************************************/
//autolable3
CHARGE_DRAW_ACT_CONFIG(CONFIG_fuzhuhesui)
CHARGE_DRAW_ACT_CONFIG(CONFIG_zhuniandaji)
CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_qingrenjie)
CHARGE_DRAW_ACT_CONFIG(CONFIG_yuandan2018)
CHARGE_DRAW_ACT_CONFIG(CONFIG_yearend2018)
CHARGE_DRAW_ACT_CONFIG(CONFIG_winter2018)
CHARGE_DRAW_ACT_CONFIG(CONFIG_double11_2018)
CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_hao)
CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_reu)
CHARGE_DRAW_ACT_CONFIG(CONFIG_water_taotie)
CHARGE_DRAW_ACT_CONFIG(CONFIG_water_qilin)
CHARGE_DRAW_ACT_CONFIG(CONFIG_water_pheonix)
CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_nnom)
//vicky没想好名字的活动
CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NO_NAME)
CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_BINGSHU)
CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_QIANFU)
CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NNA)
///////////////////////////////////////////////////////////////

/*************rankBattleShop************************/
#define XML_HUFU_SHOP_ALL_ITEM 200
struct XMLHufuShopItem
{
	unsigned id, getItem, getCount, costCount, tab, times;
	XMLHufuShopItem()
	{
		id = costCount = tab = getItem = getCount = times = 0;
	}
};
struct DataXMLHufuShop
{
	XMLHufuShopItem shop[XML_HUFU_SHOP_ALL_ITEM];
};
/*************************************/

/*************equipment***************/
#define XML_EQUIPMENT_ALL_ITEM 5000
struct DataXMLEquipment
{
	unsigned equip[XML_EQUIPMENT_ALL_ITEM];
};
/*************************************/

/*************new_turntable_lottery************************/
#define XML_PARTITION_NUM 2
#define XML_FIRST_LAYER_NUM 6
#define XML_SECOND_LAYER_NUM 8

struct XMLLotteryPrize
{
	unsigned id, type_id, rate, prize_id, prize_num, total;
	XMLLotteryPrize()
	{
		id = type_id = rate = prize_id = prize_num = total = 0;
	}
};

struct XMLnewlottery
{
	unsigned start_id;
	unsigned end_id;
	unsigned openfloor;
	unsigned first_cash;
	unsigned second_cash;
	XMLLotteryPrize FirstLayer[XML_FIRST_LAYER_NUM];
	XMLLotteryPrize SecondLayer[XML_SECOND_LAYER_NUM];
	XMLnewlottery()
	{
		openfloor = start_id = end_id = first_cash= second_cash = 0;
	}
};

struct DataXMLnewlottery
{
	XMLnewlottery part_zone[XML_PARTITION_NUM];
};
/*************************************/

/*************juexue*****************/
#define XML_JUEXUE_NPC_NUM 		5
#define XML_JUEXUE_TYPE_NUM 	4
#define XML_JUEXUE_LEVEL_NUM 	3
#define XML_JUEXUE_RUBBISH_ID 	12000
#define XML_JUEXUE_EXP_ID 		13000
enum xml_juexue_type
{
	e_juexue_type_green	 	= 0,
	e_juexue_type_blue	 	= 1,
	e_juexue_type_purple	= 2,
	e_juexue_type_orange	= 3,
	e_juexue_type_exp	 	= 4,
	e_juexue_type_rubbish	= 5,
	e_juexue_type_max,
};
enum xml_juexue
{
	e_juexue_hp 				= 0,
	e_juexue_block	 			= 1,
	e_juexue_anti_block	 		= 2,
	e_juexue_anti_dodge	 		= 3,
	e_juexue_anti_crit			= 4,
	e_juexue_crit_times			= 5,
	e_juexue_anti_crit_times	= 6,
	e_juexue_extra	 			= 7,
	e_juexue_anti_extra	 		= 8,
	e_juexue_reflect	 		= 9,
	e_juexue_anti_reflect 		= 10,
	e_juexue_anti_speed 		= 11,
	e_juexue_max,
};
/****************************************/

/*************choujiang_zhuanpan************************/
#define XML_CHOUJIANG_RATE_FIRST 10
#define XML_CHOUJIANG_RATE_SECOND 24
#define XML_CHOUJIANG_PRIZE_NUM 24

struct XMLchoujiang
{
	unsigned index, type_id, id, num;
	XMLchoujiang()
	{
		index = type_id = id = num = 0;
	}
};


struct DataXMLchoujiang
{
	unsigned rate1[XML_CHOUJIANG_RATE_FIRST];
	unsigned rate2[XML_CHOUJIANG_RATE_SECOND];
	XMLchoujiang goods[XML_CHOUJIANG_PRIZE_NUM];
	DataXMLchoujiang()
	{
		memset(rate1,0,sizeof(rate1));
		memset(rate2,0,sizeof(rate2));
	}
};
/*************************************/

/*************choujiang_zhuanpan**********/
#define JIANGLING_CHENGZHANG_L 4
/*************************************/

/**********quest_reward***************/
#define REWARD_KEY 32
#define ACT_REWARD_NUM 1000
#define ACT_REWARD_LEN 256
struct XML_ACT_REWARD
{
	char act[REWARD_KEY];
	char id[REWARD_KEY];
	char reward[ACT_REWARD_LEN];
	XML_ACT_REWARD()
	{
		memset(act, 0, sizeof(act));
		memset(id, 0, sizeof(id));
		memset(reward, 0, sizeof(reward));
	}
};
struct DataXMLActReward
{
	XML_ACT_REWARD reward[ACT_REWARD_NUM];
};

#define GATE_REWARD_NUM 10000
#define GATE_REWARD_LEN 64
struct XML_GATE_REWARD
{
	unsigned level;
	char id[REWARD_KEY];
	char reward[GATE_REWARD_LEN];
	XML_GATE_REWARD()
	{
		level = 0;
		memset(id, 0, sizeof(id));
		memset(reward, 0, sizeof(reward));
	}
};
struct DataXMLGateReward
{
	XML_GATE_REWARD reward[GATE_REWARD_NUM];
};

#define QUEST_REWARD_NUM 3000
#define QUEST_REWARD_LEN 256
struct XML_QUEST_REWARD
{
	char id[REWARD_KEY];
	char reward[QUEST_REWARD_LEN];
	XML_QUEST_REWARD()
	{
		memset(id, 0, sizeof(id));
		memset(reward, 0, sizeof(reward));
	}
};
struct DataXMLQuestReward
{
	XML_QUEST_REWARD reward[QUEST_REWARD_NUM];
};

#define MAX_RES 4
struct XMLQuestReward
{
	int hex;
	int gol;
	int cas;
	int exp;
	int ene;
	int sou;
	int pro;
	int rs[MAX_RES];
	int hud; //default hero ud
	XMLQuestReward(){
		hex=0,gol=0,cas=0,exp=0,ene=0,sou=0,pro=0,hud=0;
		memset(rs,0,sizeof(rs));
	}
};
typedef map<string, map<string,string> > XML_ACTIVITY_CONFIG;
typedef map<int, map<string,string> > XML_OLGATE_CONFIG;
typedef map<string,string>  XML_QUEST_CONFIG;
/*************************************/

#define HEAVEN_NUM		151
#define DAOIST_NUM		121
#define HEAVEN_DAOIST_NUM		(HEAVEN_NUM + DAOIST_NUM)


struct XMLHeavenDaoist
{
	unsigned id;
	unsigned exp;
	unsigned res;
	unsigned needeq;
	unsigned per;

	XMLHeavenDaoist() : id(0), exp(0), res(0), needeq(0), per(0)
	{

	}
};


struct DataXMLHeavenDaoist
{
	XMLHeavenDaoist heavenDaoist[HEAVEN_DAOIST_NUM];
};


#define HEAVEN_JIE_NUM 13
#define DAOIST_JIE_NUM 13
struct XMLCostHeavenDaoist
{
	unsigned id;
	unsigned jie;
	unsigned cash;

	XMLCostHeavenDaoist() : id(0), jie(0), cash(0)
	{}
};
struct DataXMLCostHeavenDaoist
{
	XMLCostHeavenDaoist heavenDaoistCost[HEAVEN_JIE_NUM + DAOIST_JIE_NUM];
};


#define EIGHT_FORMATION_NUM 100
#define EIGHT_FORMATION_R_NUM 3
#define ID_INDX 9
struct XMLEightFormation
{
	unsigned id;
	unsigned exp;
	unsigned res;
	unsigned needeq;
	unsigned per;

	XMLEightFormation() : id(0), exp(0), res(0), needeq(0), per(0)
	{

	}

};

struct DataXMLEightFormation
{
	XMLEightFormation eightFormation[EIGHT_FORMATION_R_NUM][EIGHT_FORMATION_NUM+1];
	unsigned r[ID_INDX];
	DataXMLEightFormation()
	{
		memset(r, 0, sizeof(r));
	}
};

#define EIGHT_FORMATION_JIE_NUM 10
struct XMLCostEightFormation
{
	unsigned id;
	unsigned jie;
	unsigned cash;

	XMLCostEightFormation():id(0), jie(0), cash(0)
	{}
};

struct DataXMLCostEightFormation
{
	XMLCostEightFormation eightFormationCost[EIGHT_FORMATION_JIE_NUM+1];
};



#define XMLDOUBLE_PROP_NUM		6
#define XMLDOUBLE_TYPE_NUM		24

struct XMLDouble11Prop
{
	unsigned eqid;
	unsigned price;
	unsigned eqcnt;
	unsigned total;

	XMLDouble11Prop() : eqid(0), price(0), eqcnt(0), total(0)
	{
	}
};


struct DataXMLDouble11
{
	XMLDouble11Prop prop[XMLDOUBLE_TYPE_NUM][XMLDOUBLE_PROP_NUM];
};


#define XMLBETSHOP_ITEMNUM		24


struct XMLBetShopItem
{
	unsigned eqid;
	unsigned cost;
	unsigned times;
	unsigned c;

	XMLBetShopItem() : eqid(0), cost(0), times(0), c(0)
	{
	}
};


struct DataXMLBetShop
{
	XMLBetShopItem bsitem[XMLBETSHOP_ITEMNUM];
};


#define XMLBARBARKING_NUM			3
#define XMLBARBARKING_GATE_NUM		7

struct XMLBarbarItem
{
	unsigned eqid;
	unsigned c;
	unsigned score;
	unsigned cost;

	XMLBarbarItem() : eqid(0), c(0), score(0), cost(0)
	{
	}
};


struct DataXMLBarbar
{
	XMLBarbarItem reward[XMLBARBARKING_NUM][XMLBARBARKING_GATE_NUM];

	DataXMLBarbar()
	{
		memset(reward, 0, sizeof(reward));
	}
};


#define XMLFIVETIGER_CHAPTER_NUM	10
#define XMLFIVETIGER_GATE_NUM		10


struct DataXMLFiveTiger
{
	unsigned addyl[XMLFIVETIGER_CHAPTER_NUM + 5][XMLFIVETIGER_GATE_NUM + 5];
};


struct EggRewardItem
{
	string eqid;
	unsigned rate;
	unsigned count;
	unsigned warn;
};


struct EggReward
{
	unsigned weight;
	vector<EggRewardItem> items;
};

/*------------------------新绝世无双活动-----------------------------*/
#define MAX_HERO_NUM (20)

struct XMLNewJueShiWS
{
	unsigned id;
	unsigned point;
	unsigned  heroid;
	bool	  isHero;  //增加别的物品配置

	XMLNewJueShiWS():
		id(0),
		point(0),
		heroid(0),
		isHero(true)
	{

	}
};

struct DataXMLNewJueshiWS
{
	XMLNewJueShiWS  heroitems[MAX_HERO_NUM];
};
//@end


/*------------------------鸿运当头活动-----------------------------*/
#define  REFRESH_ITEMS_MAX (30)
#define  EXTRA_ITEMS_MAX (6)
#define  TURN_TABLE_ITEMS_MAX (6)

enum Oppor_knock
{
	TURN_BY_CASH = 0X0,
	TURN_BY_POINT,
	POOL_TO_LEFT,
	POOL_TO_RIGHT,
};

struct EquipmentRateInfo
{
	unsigned id;
	unsigned eqid;
	unsigned count;
	int rate;
	unsigned isHero;

	EquipmentRateInfo():
		id(0),
		eqid(0),
		count(0),
		rate(0),
		isHero(0)
	{
	}
};


struct XMLSecondPoolItem
{
	int  itemcount;
	EquipmentRateInfo  allitems[EXTRA_ITEMS_MAX];

	XMLSecondPoolItem():
		itemcount(0)
	{
		memset(allitems, 0, sizeof(allitems));
	}
};

struct XMLRefreshPoolItem
{
	int  itemcount;
	EquipmentRateInfo  allitems[REFRESH_ITEMS_MAX];

	XMLRefreshPoolItem():
		itemcount(0)
	{
		memset(allitems, 0, sizeof(allitems));
	}
};

struct DataXMLOpporknock
{
	int cashrate[TURN_TABLE_ITEMS_MAX];
	int pointrate[TURN_TABLE_ITEMS_MAX];

	XMLRefreshPoolItem refreshpools;

	XMLSecondPoolItem  leftpools;
	XMLSecondPoolItem  rightpools;

	DataXMLOpporknock()
	{
		memset(cashrate, 0, sizeof(cashrate));
		memset(pointrate, 0, sizeof(pointrate));
	}
};
//@end

//幸运连连活动
#define MAX_EQUIPMENT_ITEMS (40)
#define MAX_WEIGHT_ITEMS (6)
#define MAX_POOL_ITEMS (3)

enum Fortunately_again
{
	POOL_SEQUENCE_ONE = 0x0,
	POOL_SEQUENCE_TWO,
	POOL_SEQUENCE_THREE,

	POOL_SEQUCENCE_ALL = 0x10,
};

struct EquipmentInfo
{
	unsigned id;
	unsigned count;
	unsigned index;
	unsigned isHero;

	EquipmentInfo():
		id(0),
		count(0),
		index(0),
		isHero(0)
	{
	}
};

struct XMLFortunatelyRewardItems
{
	int weightrate[MAX_WEIGHT_ITEMS];
	int weightcount;

	EquipmentInfo  weightItems[MAX_WEIGHT_ITEMS][MAX_EQUIPMENT_ITEMS];

	XMLFortunatelyRewardItems():
		weightcount(0)
	{
		memset(weightrate, 0, sizeof(weightrate));
		memset(weightItems, 0, sizeof(weightItems));
	}
};

//索引，记录下标位置
struct EquipIndex
{
	int poolindex;
	int weightindex;
	int equipindex;

	EquipIndex():
		poolindex(0),
		weightindex(0),
		equipindex(0)
	{
	}
};

struct DataXMLFortunatelyAgain
{
	XMLFortunatelyRewardItems  poolitems[MAX_POOL_ITEMS];
};

//天命
#define MAX_TURLPLATE_POOL_ITEMS (4)

enum TurnPLATE
{
	POOL_TURN_SEQUENCE_ONE = 0x0,
	POOL_TURN_SEQUENCE_TWO,
	POOL_TURN_SEQUENCE_THREE,
	POOL_TURN_SEQUENCE_FOUR,
	POOL_TURN_SEQUENCE_MAX,
};

struct DataXMLTurnPlate
{
	XMLFortunatelyRewardItems  poolitems[MAX_TURLPLATE_POOL_ITEMS];
};

//充值自选
#define OPTIONAL_ITEMS_MAX (15)

struct XMLOptionalItems
{
	unsigned id;
	unsigned eqid;
	unsigned count;

	XMLOptionalItems():
		id(0),
		eqid(0),
		count(0)
	{
	}
};

struct DataXMLRechargeOptional
{
	unsigned itemcount;
	unsigned per;

	XMLOptionalItems items[OPTIONAL_ITEMS_MAX];

	DataXMLRechargeOptional():
		itemcount(0),
		per(0)
	{
	}
};

//小兵训练和研究
#define MAX_SOLDIER_LEVEL (150)
#define MAX_SOLDIER_KIND (17) //增加了两个新兵种, 种类+2

struct XMLSoldierLevelItems
{
	unsigned char locklevel;  //研究院等级
	unsigned char silvertype;

	unsigned rtime;  //研究花费时间
	unsigned ptime;  //训练花费时间

	unsigned cost;   //铁矿
	unsigned silver;  //粮食

	XMLSoldierLevelItems():
		locklevel(0),
		silvertype(0),
		rtime(0),
		ptime(0),
		cost(0),
		silver(0)
	{
	}
};

struct XMLSoldierKindItem
{
	unsigned char grade;
	unsigned sid;
	XMLSoldierLevelItems  levelitems[MAX_SOLDIER_LEVEL + 1];

	XMLSoldierKindItem():
		grade(0),
		sid(0)
	{

	}
};

struct DataXMLSoldierTrainAndUp
{
	XMLSoldierKindItem  soldieritems[MAX_SOLDIER_KIND];
};

//兵书遁甲技能
#define MAX_SKILL_LEVEL (10)
#define MAX_DAO_SKILL_ITEMS (5)
#define MAX_HEAVEN_SKILL_ITEMS (8)

struct XMLHeavenDaoSkillItem
{
	unsigned id;
	unsigned stage;
	unsigned bookid;
	unsigned char booknum[MAX_SKILL_LEVEL];

	XMLHeavenDaoSkillItem():
		id(0),
		stage(0),
		bookid(0)
	{
		memset(booknum, 0, sizeof(booknum));
	}
};

struct DataXMLHeavenDaoSkill
{
	XMLHeavenDaoSkillItem daoitem[MAX_DAO_SKILL_ITEMS];
	XMLHeavenDaoSkillItem heavenitem[MAX_HEAVEN_SKILL_ITEMS];
};
//@end


//fashion shop begin
struct XMLFashionShopItem
{
	unsigned id_;
	unsigned cost_;
	bool is_cash_;
	bool die_;
	unsigned days_;
	unsigned vip_;

	XMLFashionShopItem(): id_(0), cost_(0), is_cash_(false), die_(false), days_(0), vip_(0)
	{}
};

#define MAX_FASHION_SHOP_ITEMS (50)
struct DataXMLFashionShop
{
	XMLFashionShopItem fashion_shop_items[MAX_FASHION_SHOP_ITEMS];
};
//fashion shop end


//厚惠有期  begin
#define HOUHUIYOUQI_ZONE_SECTION 		 (3)
#define HOUHUIYOUQI_4399_ZONE_SECTION 	 (3)
#define HOUHUIYOUQI_BIG_TALBE_NUM 		 (5)
#define HOUHUIYOUQI_SMALL_TALBE_NUM 	 (10)
#define HOUHUIYOUQI_SMALL_TALBE_CAN_BUY  (7)

struct XMLHouHuiYouQiItem
{
	unsigned id_;
	unsigned count_;
	unsigned cost_;
	bool is_cash_;

	XMLHouHuiYouQiItem(): id_(0), count_(0), cost_(0), is_cash_(false)
	{}
};

struct XMLHouHuiYouQiSection
{
	unsigned zone_start_;
	unsigned zone_end_;
	unsigned big_table_charge_need_[HOUHUIYOUQI_BIG_TALBE_NUM];
	XMLHouHuiYouQiItem section_houhuiyouqi_[HOUHUIYOUQI_BIG_TALBE_NUM][HOUHUIYOUQI_SMALL_TALBE_NUM];

	XMLHouHuiYouQiSection(): zone_start_(0), zone_end_(0)
	{
		memset(big_table_charge_need_, 0, sizeof(big_table_charge_need_));
	}
};

struct DataXMLHouHuiYouQi
{
	XMLHouHuiYouQiSection houhuiyouqi_items[HOUHUIYOUQI_ZONE_SECTION];
	XMLHouHuiYouQiSection houhuiyouqi_4399_items[HOUHUIYOUQI_4399_ZONE_SECTION];
};
//厚惠有期 end


//超值折扣 begin
#define CHAOZHIZHEKOU_ZONE_SECTION 		     (3)
#define CHAOZHIZHEKOU_BIG_TALBE_NUM 		 (3)
#define CHAOZHIZHEKOU_SMALL_TALBE_NUM 	     (8)

struct XMLChaoZhiZheKouItem
{
	unsigned id_;
	unsigned count_;
	unsigned cost_;
	bool is_cash_;
	unsigned limit_;

	XMLChaoZhiZheKouItem(): id_(0), count_(0), cost_(0), is_cash_(false), limit_(0)
	{}
};

struct XMLChaoZhiZheKouSection
{
	unsigned zone_start_;
	unsigned zone_end_;
	unsigned big_table_charge_need_[CHAOZHIZHEKOU_BIG_TALBE_NUM];
	XMLChaoZhiZheKouItem section_chaozhizhekou_[CHAOZHIZHEKOU_BIG_TALBE_NUM][CHAOZHIZHEKOU_SMALL_TALBE_NUM];

	XMLChaoZhiZheKouSection(): zone_start_(0), zone_end_(0)
	{
		memset(big_table_charge_need_, 0, sizeof(big_table_charge_need_));
	}
};

struct DataXMLChaoZhiZheKou
{
	XMLChaoZhiZheKouSection chaozhizhekou_items[CHAOZHIZHEKOU_ZONE_SECTION];
};
//超值折扣 end


//约惠巨献 begin
#define YUEHUIJUXIAN_ZONE_SECTION 		     (3)
#define YUEHUIJUXIAN_4399_ZONE_SECTION 		 (2)
#define YUEHUIJUXIAN_BIG_TALBE_NUM 		 	 (5)
#define YUEHUIJUXIAN_SMALL_TALBE_NUM 	     (7)

struct XMLYueHuiJuXianItem
{
	unsigned id_;
	unsigned count_;
	unsigned cost_;
	bool is_cash_;

	XMLYueHuiJuXianItem(): id_(0), count_(0), cost_(0), is_cash_(false)
	{}
};

struct XMLYueHuiJuXianSection
{
	unsigned zone_start_;
	unsigned zone_end_;
	unsigned big_table_charge_need_[YUEHUIJUXIAN_BIG_TALBE_NUM];
	XMLYueHuiJuXianItem section_yuehuijuxian_[YUEHUIJUXIAN_BIG_TALBE_NUM][YUEHUIJUXIAN_SMALL_TALBE_NUM];

	XMLYueHuiJuXianSection(): zone_start_(0), zone_end_(0)
	{
		memset(big_table_charge_need_, 0, sizeof(big_table_charge_need_));
	}
};

struct DataXMLYueHuiJuXian
{
	XMLYueHuiJuXianSection yuehuijuxian_items[YUEHUIJUXIAN_ZONE_SECTION];
	XMLYueHuiJuXianSection yuehuijuxian_4399_items[YUEHUIJUXIAN_4399_ZONE_SECTION];
};
//约惠巨献 end


//全服限购  begin
#define LIMITBUYOFZONE_TALBE_NUM 		 	         (8)

#define LIMITBUYOFZONE_ZONE_QQ_SECTION 		         (3)
#define LIMITBUYOFZONE_ZONE_LY_SECTION 		         (1)
#define LIMITBUYOFZONE_ZONE_4399_SECTION 		     (2)

struct XMLLimitBuyOfZoneItem
{
	unsigned id_;
	unsigned cash_;
	unsigned cond_;
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned eq_q_;
	unsigned eq_ch_;

	XMLLimitBuyOfZoneItem(): id_(0), cash_(0), cond_(0), eqid_(0), eq_cnt_(0), eq_q_(0), eq_ch_(0)
	{}
};

struct XMLLimitBuyOfZoneSection
{
	unsigned zone_start_;
	unsigned zone_end_;
	XMLLimitBuyOfZoneItem section_limitbuyofzone_[LIMITBUYOFZONE_TALBE_NUM];

	XMLLimitBuyOfZoneSection(): zone_start_(0), zone_end_(0)
	{}
};

struct DataXMLLimitBuyOfZone
{
	XMLLimitBuyOfZoneSection limitbuyofzone_qq_items[LIMITBUYOFZONE_ZONE_QQ_SECTION];
	XMLLimitBuyOfZoneSection limitbuyofzone_ly_items[LIMITBUYOFZONE_ZONE_LY_SECTION];
	XMLLimitBuyOfZoneSection limitbuyofzone_4399_items[LIMITBUYOFZONE_ZONE_4399_SECTION];
};
//全服限购  end

//五行防御成长 begin
struct XMLFiveDefendGrowItem
{
	unsigned level_;
	unsigned value_;
	unsigned cost_;

	XMLFiveDefendGrowItem(): level_(0), value_(0), cost_(0)
	{}
};

#define FIVEDEFENDGROW_LEVEL		     (101)
struct DataXMLFiveDefendGrow
{
	XMLFiveDefendGrowItem fivedefendgrow_items_[FIVEDEFENDGROW_LEVEL];
};
//五行防御成长 end

//五行灵珠begin
struct XMLWuxingPearlItem
{
	unsigned cond_;
	unsigned eqid_;
	unsigned count_;

	XMLWuxingPearlItem(): cond_(0), eqid_(0), count_(0)
	{}
};

#define WUXING_PERAL_ITEM_COUNT		     (1)
struct DataXMLWuxingPearl
{
	XMLWuxingPearlItem wuxing_perl_items_[WUXING_PERAL_ITEM_COUNT];
};
//五行灵珠end


/***************国庆盛典   begin**********************/
//国庆登录
#define MAX_COUNTRY_DAY_LOGIN_OPEN_DAYS  (7)
struct XMLCountryDayLoginEquipItem
{
	unsigned eqid_;
	unsigned cnt_;
	unsigned q_;
	unsigned ch_;

	XMLCountryDayLoginEquipItem(): eqid_(0), cnt_(0), q_(0), ch_(0)
	{}
};

#define MAX_COUNTRY_DAY_LOGIN_EQUIP_CNT  (4)
struct XMLCountryDayLoginItem
{
	unsigned id_;
	unsigned days_;
	XMLCountryDayLoginEquipItem equip_items_[MAX_COUNTRY_DAY_LOGIN_EQUIP_CNT];

	XMLCountryDayLoginItem(): id_(0), days_(0)
	{}
};

#define COUNTRY_DAY_LOGIN_KINDS    (3)
struct DataXMLCountryDayLogin
{
	unsigned begin_ts_;
	unsigned end_ts_;
	XMLCountryDayLoginItem login_items_[COUNTRY_DAY_LOGIN_KINDS];

	DataXMLCountryDayLogin(): begin_ts_(0), end_ts_(0)
	{}
};


//国庆商店
#define MAX_COUNTRY_DAY_SHOP_DB_CNT (7)
struct XMLCountryDayShopItem
{
	unsigned id_;
	unsigned limit_;
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned eq_q_;
	unsigned eq_ch_;
	unsigned ts_;
	unsigned cash_;

	XMLCountryDayShopItem(): id_(0), limit_(0), eqid_(0), eq_cnt_(0), eq_q_(0), eq_ch_(0), ts_(0), cash_(0)
	{}
};

#define MAX_COUNTRY_DAY_SHOP_ITEMS  (13)
struct DataXMLCountryDayShop
{
	unsigned begin_ts_;
	unsigned end_ts_;
	XMLCountryDayShopItem shop_items_[MAX_COUNTRY_DAY_SHOP_ITEMS];

	DataXMLCountryDayShop(): begin_ts_(0), end_ts_(0)
	{}
};


//国庆福袋
struct XMLCountryDayBagItem
{
	unsigned id_;
	unsigned daily_pay_;
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned eq_q_;
	unsigned eq_ch_;

	XMLCountryDayBagItem(): id_(0), daily_pay_(0), eqid_(0), eq_cnt_(0), eq_q_(0), eq_ch_(0)
	{}
};

#define MAX_COUNTRY_DAY_BAG_ITEMS  (3)
struct DataXMLCountryDayBag
{
	unsigned begin_ts_;
	unsigned end_ts_;
	XMLCountryDayBagItem bag_items_[MAX_COUNTRY_DAY_BAG_ITEMS];

	DataXMLCountryDayBag(): begin_ts_(0), end_ts_(0)
	{}
};


struct DataXMLCountryDay
{
	DataXMLCountryDayLogin login_;
	DataXMLCountryDayShop  shop_;
	DataXMLCountryDayBag   bag_;
};
/***************国庆盛典   end**********************/


/***************心动特卖  begin**********************/
struct XMLHeartbeatBigSaleEquip
{
	unsigned eqid_;
	unsigned cnt_;
	unsigned q_;
	unsigned ch_;

	XMLHeartbeatBigSaleEquip(): eqid_(0), cnt_(0), q_(0), ch_(0)
	{}
};

struct XMLHeartbeatBigSaleItem
{
	unsigned id_;
	unsigned cash_;
	unsigned limit_;
	XMLHeartbeatBigSaleEquip reward_;

	XMLHeartbeatBigSaleItem(): id_(0), cash_(0), limit_(0)
	{}
};

#define HEART_BEAT_BIG_SALE_ITEM_NUM	(4)
struct DataXMLHeartbeatBigSaleSection
{
	unsigned start_zone_;
	unsigned end_zone_;
	XMLHeartbeatBigSaleItem section_items_[HEART_BEAT_BIG_SALE_ITEM_NUM];

	DataXMLHeartbeatBigSaleSection(): start_zone_(0), end_zone_(0)
	{}
};

#define HEART_BEAT_BIG_SALE_SECTION_NUM	 (2)
struct DataXMLHeartbeatBigSale
{
	DataXMLHeartbeatBigSaleSection all_items_[HEART_BEAT_BIG_SALE_SECTION_NUM];
};
/***************心动特卖   end**********************/


/***************五行商铺  begin**********************/
struct XMLFiveSpecialShopItem
{
	unsigned id_;
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned price_;
	unsigned limit_;

	XMLFiveSpecialShopItem(): id_(0), eqid_(0), eq_cnt_(0), price_(0), limit_(0)
	{}
};

struct XMLFiveDiscountShopItem
{
	unsigned id_;
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned price_;
	unsigned quan_;
	unsigned limit_;

	XMLFiveDiscountShopItem(): id_(0), eqid_(0), eq_cnt_(0), price_(0), quan_(0), limit_(0)
	{}
};

#define MAX_FIVE_SPECIAL_SHOP_ITEMS  	(30)
#define MAX_FIVE_DISCOUNT_SHOP_ITEMS  	(30)
struct DataXMLFiveShop
{
	unsigned quan_pay_;
	unsigned quan_count_;
	unsigned quan_limit_;
	XMLFiveSpecialShopItem five_special_shop_items_[MAX_FIVE_SPECIAL_SHOP_ITEMS];
	XMLFiveDiscountShopItem five_discount_shop_items_[MAX_FIVE_DISCOUNT_SHOP_ITEMS];

	DataXMLFiveShop(): quan_pay_(0), quan_count_(0), quan_limit_(0)
	{}
};
/***************五行商铺   end**********************/


/***************觉醒特惠  begin**********************/
struct XMLJueXingTeHuiItem
{
	unsigned id_;
	unsigned eqid_;
	unsigned price_;
	unsigned limit_;
	unsigned wj_cnt_;
	unsigned wj_jie_;

	XMLJueXingTeHuiItem(): id_(0), eqid_(0), price_(0), limit_(0), wj_cnt_(0), wj_jie_(0)
	{}
};

#define MAX_JUEXINGTEHUI_ITEMS  	(30)
struct DataXMLJueXingTeHui
{
	int item_real_cnt_;
	XMLJueXingTeHuiItem juexingtehui_items_[MAX_JUEXINGTEHUI_ITEMS];

	DataXMLJueXingTeHui(): item_real_cnt_(0)
	{}
};
/***************觉醒特惠   end**********************/


/**************免费兑换 begin**********************/
struct XMLFreeExchangeRewardEquipItem
{
	unsigned eqid_;
	unsigned cnt_;
	unsigned q_;
	unsigned ch_;

	XMLFreeExchangeRewardEquipItem(): eqid_(0), cnt_(0), q_(0), ch_(0)
	{}
};

struct XMLFreeExchangeItem
{
	unsigned id_;
	unsigned type_;
	unsigned eqid1_;
	unsigned need1_;
	unsigned eqid2_;
	unsigned need2_;
	unsigned limit_;
	XMLFreeExchangeRewardEquipItem reward_;

	XMLFreeExchangeItem(): id_(0), type_(0), eqid1_(0), need1_(0), eqid2_(0), need2_(0), limit_(0)
	{}
};

const int MAX_FREE_EXCHANGE_ITEMS_CNT = 15;
struct DataXMLFreeExchange
{
	unsigned item_real_cnt_;
	XMLFreeExchangeItem free_exchange_items_[MAX_FREE_EXCHANGE_ITEMS_CNT];
	DataXMLFreeExchange(): item_real_cnt_(0)
	{}
};
/**************免费兑换 end**********************/


/***************双11  begin**********************/
struct XMLDoubleElevenSmallItem
{
	unsigned id_;
	unsigned eqid_;
	unsigned cnt_;
	unsigned cash_;

	XMLDoubleElevenSmallItem(): id_(0), eqid_(0), cnt_(0), cash_(0)
	{}
};


const int DOUBLE_ELEVEN_SMALL_ITEMS_CNT = 4;
struct XMLDoubleElevenBigItem
{
	unsigned id_;
	unsigned limitbuy_;
	unsigned recharge_;
	unsigned rewardid_;
	unsigned rewardcnt_;
	XMLDoubleElevenSmallItem small_items_[DOUBLE_ELEVEN_SMALL_ITEMS_CNT];

	XMLDoubleElevenBigItem(): id_(0), limitbuy_(0), recharge_(0), rewardid_(0), rewardcnt_(0)
	{}
};

const int DOUBLE_ELEVEN_BIG_ITEMS_CNT = 5;
struct DataXMLDoubleEleven
{
	unsigned big_item_cnt_;
	XMLDoubleElevenBigItem doubleeleven_items_[DOUBLE_ELEVEN_BIG_ITEMS_CNT];

	DataXMLDoubleEleven(): big_item_cnt_(0)
	{}
};
/***************双11   end**********************/


/***************聚宝匣  begin**********************/
struct XMLJuBaoXiaTreasureCommonItem
{
	unsigned id_;
	unsigned amount_;
	unsigned rate_;

	XMLJuBaoXiaTreasureCommonItem(): id_(0), amount_(0), rate_(0)
	{}
};

const int JUBAOXIA_PRECIOUS_RATE_KINDS = 4;
struct XMLJuBaoXiaTreasurePreciousItem
{
	unsigned id_;
	unsigned amount_;
	unsigned rate_[JUBAOXIA_PRECIOUS_RATE_KINDS];
	bool is_hero_;

	XMLJuBaoXiaTreasurePreciousItem(): id_(0), amount_(0), is_hero_(false)
	{
		memset(rate_,0,sizeof(rate_));
	}
};

struct XMLJuBaoXiaDailyFreeItem
{
	unsigned id_;
	unsigned cnt_;

	XMLJuBaoXiaDailyFreeItem(): id_(0), cnt_(0)
	{}
};

struct XMLJuBaoXiaExchangeItem
{
	unsigned need_id_;
	unsigned need_cnt_;
	unsigned need_cash_;
	unsigned get_id_;
	unsigned get_cnt_;

	XMLJuBaoXiaExchangeItem(): need_id_(0), need_cnt_(0), need_cash_(0), get_id_(0), get_cnt_(0)
	{}
};

struct XMLJuBaoXiaKeyItem
{
	unsigned need_charge_;
	unsigned get_id_;
	unsigned get_cnt_;

	XMLJuBaoXiaKeyItem(): need_charge_(0), get_id_(0), get_cnt_(0)
	{}
};

const int JUBAOXIA_GET_KEY_CHANNEL_KINDS = 16;
const int JUBAOXIA_TREASURE_CNT = 25;
const int JUBAOXIA_COMMON_CNT = 24;
const int JUBAOXIA_PRECIOUS_CNT = 3;
const int JUBAOXIA_KEY_CNT = 14;
struct DataXMLJuBaoXia
{
	XMLJuBaoXiaTreasureCommonItem common_items_[JUBAOXIA_COMMON_CNT];
	XMLJuBaoXiaTreasurePreciousItem precious_items_[JUBAOXIA_PRECIOUS_CNT];
	XMLJuBaoXiaDailyFreeItem daily_free_item;
	XMLJuBaoXiaExchangeItem exchange_item;
	XMLJuBaoXiaKeyItem key_items[JUBAOXIA_KEY_CNT];

	DataXMLJuBaoXia()
	{}
};
/***************聚宝匣   end**********************/


/***************兵书进阶   begin**********************/
const int HEAVENSTEP_REWARD_KINDS = 11;
struct XMLHeavenStepRewardItem
{
	unsigned jie_id_;
	unsigned eqid_[HEAVENSTEP_REWARD_KINDS];
	unsigned cnt_[HEAVENSTEP_REWARD_KINDS];

	XMLHeavenStepRewardItem() : jie_id_(0)
	{
		memset(eqid_, 0, sizeof(eqid_));
		memset(cnt_, 0, sizeof(cnt_));
	}
};

const int HEAVENSTEP_JIE_NUM = 15;
struct DataXMLHeavenStep
{
	XMLHeavenStepRewardItem reward_items_[HEAVENSTEP_JIE_NUM];
	DataXMLHeavenStep()
	{}
};
/***************兵书进阶  end**********************/


/***************遁甲进阶   begin**********************/
const int DAOISTSTEP_REWARD_KINDS = 11;
struct XMLDaoistStepRewardItem
{
	unsigned jie_id_;
	unsigned eqid_[DAOISTSTEP_REWARD_KINDS];
	unsigned cnt_[DAOISTSTEP_REWARD_KINDS];

	XMLDaoistStepRewardItem() : jie_id_(0)
	{
		memset(eqid_, 0, sizeof(eqid_));
		memset(cnt_, 0, sizeof(cnt_));
	}
};

const int DAOISTSTEP_JIE_NUM = 12;
struct DataXMLDaoistStep
{
	XMLDaoistStepRewardItem reward_items_[DAOISTSTEP_JIE_NUM];
	DataXMLDaoistStep()
	{}
};
/***************遁甲进阶  end**********************/


/***************珍宝阁魂石   begin**********************/
struct XMLZhenBaoGeHeroItem
{
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned cash_;
	unsigned limit_times_;

	XMLZhenBaoGeHeroItem() : eqid_(0), eq_cnt_(0), cash_(0), limit_times_(0)
	{}
};

const int ZHENBAOGEHERO_BIG_NUM = 2;
const int ZHENBAOGEHERO_SMALL_NUM = 5;
struct DataXMLZhenBaoGeHero
{
	XMLZhenBaoGeHeroItem items_[ZHENBAOGEHERO_BIG_NUM][ZHENBAOGEHERO_SMALL_NUM];
	DataXMLZhenBaoGeHero()
	{}
};
/***************珍宝阁魂石  end**********************/


/***************珍宝阁宝石   begin**********************/
struct XMLZhenBaoGeBuildingItem
{
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned cash_;
	unsigned limit_times_;

	XMLZhenBaoGeBuildingItem() : eqid_(0), eq_cnt_(0), cash_(0), limit_times_(0)
	{}
};

const int ZHENBAOGEBUILDING_BIG_NUM = 2;
const int ZHENBAOGEBUILDING_SMALL_NUM = 5;
struct DataXMLZhenBaoGeBuilding
{
	XMLZhenBaoGeBuildingItem items_[ZHENBAOGEBUILDING_BIG_NUM][ZHENBAOGEBUILDING_SMALL_NUM];
	DataXMLZhenBaoGeBuilding()
	{}
};
/***************珍宝阁宝石  end**********************/


/***************魂石进阶   begin**********************/
struct XMLHeroStoneStepRewardItem
{
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned q_;

	XMLHeroStoneStepRewardItem() : eqid_(0), eq_cnt_(0), q_(0)
	{}
};

struct XMLHeroStoneStepItem
{
	unsigned id_;
	unsigned lv_;
	unsigned maxcount_;
	XMLHeroStoneStepRewardItem reward_;

	XMLHeroStoneStepItem() : id_(0), lv_(0), maxcount_(0)
	{}
};

const int HEROSTONESTEP_ITEM_CNT = 6;
struct DataXMLHeroStoneStep
{
	XMLHeroStoneStepItem items_[HEROSTONESTEP_ITEM_CNT];
	DataXMLHeroStoneStep()
	{}
};
/***************魂石进阶  end**********************/


/***************宝石进阶   begin**********************/
struct XMLBuildingStoneStepRewardItem
{
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned q_;

	XMLBuildingStoneStepRewardItem() : eqid_(0), eq_cnt_(0), q_(0)
	{}
};

struct XMLBuildingStoneStepItem
{
	unsigned id_;
	unsigned lv_;
	unsigned maxcount_;
	XMLBuildingStoneStepRewardItem reward_;

	XMLBuildingStoneStepItem() : id_(0), lv_(0), maxcount_(0)
	{}
};

const int BUILDINGSTONESTEP_ITEM_CNT = 6;
struct DataXMLBuildingStoneStep
{
	XMLBuildingStoneStepItem items_[BUILDINGSTONESTEP_ITEM_CNT];
	DataXMLBuildingStoneStep()
	{}
};
/***************宝石进阶  end**********************/

/***************成长开发   begin**********************/
struct XMLGrowDevelopRewardItem
{
	unsigned eqid_;
	unsigned eq_cnt_;
	unsigned q_;

	XMLGrowDevelopRewardItem() : eqid_(0), eq_cnt_(0), q_(0)
	{}
};

const int HEROGROWDEVELOP_SMALL_CNT = 5;
struct XMLGrowDevelopCertainJie
{
	unsigned level_;
	unsigned require_;
	XMLGrowDevelopRewardItem rewards_[HEROGROWDEVELOP_SMALL_CNT];

	XMLGrowDevelopCertainJie() : level_(0), require_(0)
	{}
};

const int HEROGROWDEVELOP_BIG_CNT = 5;
struct DataXMLGrowDevelop
{
	XMLGrowDevelopCertainJie items_[HEROGROWDEVELOP_BIG_CNT];
	DataXMLGrowDevelop()
	{}
};
/***************成长开发  end**********************/


/***************每日充值 begin**********************/
#define MAX_DAILY_OPTIONS 15

struct XMLDailyChargeReward
{
	unsigned id;
	unsigned coin;
	unsigned reward;

	XMLDailyChargeReward():
		id(0),
		coin(0),
		reward(0)
	{

	}
};

struct DataXMLDailyCharge
{
	XMLDailyChargeReward dailyreward[MAX_DAILY_OPTIONS];
};

/***************每日充值  end**********************/


/***************百宝箱 begin**********************/
#define MAX_ITEM_NUMS 20

struct XMLTreasureBox
{
	unsigned id;
	unsigned rate;
	GiftEquipItem item;  //装备或英雄

	XMLTreasureBox():
		id(0),
		rate(0)
	{
	}
};

struct DataXMLTreasureBox
{
	unsigned rewardnum;
	unsigned shownum;

	XMLTreasureBox rewarditems[MAX_ITEM_NUMS];
	XMLTreasureBox showitems[MAX_ITEM_NUMS];

	DataXMLTreasureBox():
		rewardnum(0),
		shownum(0)
	{

	}
};

/***************百宝箱  end**********************/

/***************信物系统  begin**********************/
#define MAX_NPC_NUM	(5)
#define MAX_FULL_NUM (7)
#define MAX_KEEPSAKE_NUM (7)
#define MAX_CHARACTER_NUM (4)
#define MAX_KEEPSAKE_LEVEL (10)
#define MAX_SLAVE_PROPNUM (3)
#define MAX_USER_LEVEL_LIMITS (3)
#define RESOURCE_ITEMS (4)
#define XINWU_FB 10

//NPC的产出信息
struct XMLNPCProduceInfo
{
	uint8_t npcid;
	uint16_t cost;
	uint16_t nextrate;
	int fallrate[MAX_FULL_NUM];   //正常情况掉落物品的概率
	int summonrate[MAX_FULL_NUM];   //召唤后的概率

	XMLNPCProduceInfo():
		npcid(0),
		cost(0),
		nextrate(0)
	{
		memset(fallrate, 0, sizeof(fallrate));
		memset(summonrate, 0, sizeof(summonrate));
	}
};

//等级和产出信物的概率关系
struct XMLLevelProduceRate
{
	uint16_t level;
	uint32_t keepsakeid[MAX_KEEPSAKE_NUM];
	int character_rate[MAX_CHARACTER_NUM][MAX_KEEPSAKE_NUM];  //不同品种，信物的出现概率

	XMLLevelProduceRate():
		level(0)
	{
		memset(keepsakeid, 0, sizeof(keepsakeid));
		memset(character_rate, 0, sizeof(character_rate));
	}
};

struct XMLKeepsakeProduce
{
	XMLNPCProduceInfo npcs[MAX_NPC_NUM];
	XMLLevelProduceRate level_produce[MAX_USER_LEVEL_LIMITS];

	XMLKeepsakeProduce()
	{
		memset(npcs, 0, sizeof(npcs));
		memset(level_produce, 0, sizeof(level_produce));
	}
};

struct XMLCharaterUpgrade
{
	uint32_t exp[MAX_KEEPSAKE_LEVEL];
	uint32_t resource[RESOURCE_ITEMS][MAX_KEEPSAKE_LEVEL];  //4种资源
	uint32_t convertcost[MAX_KEEPSAKE_LEVEL];  //转化石的消耗

	XMLCharaterUpgrade()
	{
		memset(exp, 0, sizeof(exp));
		memset(resource, 0, sizeof(resource));
		memset(convertcost, 0, sizeof(convertcost));
	}
};

//信物升级配置
struct XMLTokenUpgrade
{
	XMLCharaterUpgrade character_upgrade[MAX_CHARACTER_NUM];

	XMLTokenUpgrade()
	{
		memset(character_upgrade, 0, sizeof(character_upgrade));
	}
};

struct XMLTokenBase
{
	uint8_t slave_unlock_level[MAX_SLAVE_PROPNUM];
	uint16_t character_exp[MAX_CHARACTER_NUM];

	XMLTokenBase()
	{
		memset(slave_unlock_level, 0, sizeof(slave_unlock_level));
		memset(character_exp, 0, sizeof(character_exp));
	}
};

struct XMLXinWuFB
{
	unsigned firstReward[XINWU_FB];
	unsigned reward[XINWU_FB];
	XMLXinWuFB()
	{
		memset(firstReward, 0, sizeof(firstReward));
		memset(reward, 0, sizeof(reward));
	}
};

struct DataXMLKeepsake
{
	XMLTokenBase base;
	XMLKeepsakeProduce produce;
	XMLTokenUpgrade upgrade;

	uint32_t defective_eqid; //残品eqid
	uint32_t exp_props_eqid;  //经验石id

	XMLXinWuFB reward;

	DataXMLKeepsake():
		defective_eqid(0),
		exp_props_eqid(0)
	{

	}
};

/***************信物系统  end**********************/

/***************充值回馈-每日充值兵书 和遁甲 begin**********************/
#define MAX_CHARGE_FEEDBACK_NUMS (15)

struct XMLChargeFeedbackReward
{
	unsigned id;
	unsigned diamond;
	GiftEquipment equip;

	XMLChargeFeedbackReward():
		id(0),
		diamond(0)
	{

	}
};

struct DataXMLChargeFeedback
{
	XMLChargeFeedbackReward heaven[MAX_CHARGE_FEEDBACK_NUMS];
	XMLChargeFeedbackReward daoist[MAX_CHARGE_FEEDBACK_NUMS];
};

/***************充值回馈-每日充值兵书和遁甲 -end**********************/
#define MAX_CELEBRATE_NUMS (15)

struct XMLNewYearReward
{
	unsigned id;
	unsigned coin;
	unsigned diamond;

	GiftEquipment equip;

	XMLNewYearReward():
		id(0),
		coin(0),
		diamond(0)
	{

	}
};

struct DataXMLCelebrateNewYear
{
	XMLNewYearReward reward[MAX_CELEBRATE_NUMS];
};

/***************消费自选-begin**********************/
struct PayOptionalItem
{
	unsigned index;
	GiftEquipment equip;

	PayOptionalItem():
		index(0)
	{

	}

	void Clear()
	{
		index = 0;
		memset(&equip, 0, sizeof(equip));
	}
};
/***************消费自选-end**********************/

/***************合区活动-begin**********************/
#define EQUIP_ITEMS_MAX (5)
#define MAX_CHARGE_ITEMS (4)
#define MAX_VIP_ITEMS (5)
#define MAX_VIP_SUBQUENT (3)
#define MAX_RECOMPENSE_ITEMS (4)

//充值
struct HeQuChargeItem
{
	unsigned cash;
	unsigned itemnum;
	GiftEquipItem items[EQUIP_ITEMS_MAX];

	HeQuChargeItem():
		cash(0),
		itemnum(0)
	{
	}
};

//vip奖励
struct HeQuVIPItem
{
	unsigned limit_vip;
	unsigned itemnum;
	GiftEquipItem items[EQUIP_ITEMS_MAX];

	HeQuVIPItem():
		limit_vip(0),
		itemnum(0)
	{
	}
};

//合区补偿
struct HeQuRecompense
{
	unsigned minlevel;
	unsigned maxlevel;
	unsigned itemnum;
	GiftEquipItem items[EQUIP_ITEMS_MAX];

	HeQuRecompense():
		minlevel(0),
		maxlevel(0),
		itemnum(0)
	{
	}
};

struct DataXMLHequActivity
{
	HeQuChargeItem chargeitems[MAX_CHARGE_ITEMS];
	HeQuVIPItem vipitems[MAX_VIP_ITEMS][MAX_VIP_SUBQUENT];
	HeQuRecompense recomitems[MAX_RECOMPENSE_ITEMS];
};

/***************合区活动-end**********************/


/***************古卷奇书-begin**********************/
#define ANCIENT_SCROLL_ITEMS (8)
#define MAX_SCROLL_LEVEL	(151)

struct ScrollItem
{
	unsigned id;
	unsigned zhuzi;
	unsigned res[4];
	unsigned needeq;

	ScrollItem():
		id(0),
		zhuzi(0),
		needeq(0)
	{
		memset(res, 0, sizeof(res));
	}

};

struct DataXMLAncientScroll
{
	ScrollItem items[ANCIENT_SCROLL_ITEMS][MAX_SCROLL_LEVEL];
};

/***************古卷奇书-end**********************/

/***************保护旗帜升级-begin**********************/
#define MAX_FLAG_LEVEL (50)

struct DataXMLProtectFlag
{
	unsigned exps[MAX_FLAG_LEVEL];
	uint8_t eqcount[MAX_FLAG_LEVEL];
};
/***************保护旗帜升级-end**********************/

/***************保护女神-begin**********************/
#define MAX_REWARD_ITEM (32)
#define MAX_REWARD_EQUIP_ITEM (4)

struct ProtectGoddessRewardItem
{
	unsigned id;
	unsigned point;
	unsigned itemnum;

	GiftEquipItem items[MAX_REWARD_EQUIP_ITEM];

	ProtectGoddessRewardItem():
		id(0),
		point(0),
		itemnum(0)
	{

	}
};

struct DataXMLProtectGoddess
{
	ProtectGoddessRewardItem reward[MAX_REWARD_ITEM];
};

/***************保护女神-end**********************/

/*****************building*****************/
#define XML_BUILDING_RES 4
struct XMLBuildingItem
{
	int t, lv, cost[XML_BUILDING_RES], time,produce,capacity;
	XMLBuildingItem()
	{
		t = lv = time = 0;
		produce = capacity = 0;
		memset(cost, 0, sizeof(cost));
	}
};
#define XML_BUILDING_NUM 150*100
struct DataXMLBuilding
{
	XMLBuildingItem build[XML_BUILDING_NUM];
};
/*****************building*****************/


/*****************catapult*****************/
#define CATAPULT_NUM	121

struct XMLCatapult
{
	unsigned id;
	unsigned exp;
	unsigned res;
	unsigned needeq;
	unsigned per;

	XMLCatapult() : id(0), exp(0), res(0), needeq(0), per(0)
	{

	}
};


struct DataXMLCatapult
{
	XMLCatapult catapult[CATAPULT_NUM];
};


#define CATAPULT_JIE_NUM 13
struct XMLCostCatapult
{
	unsigned id;
	unsigned jie;
	unsigned cash;

	XMLCostCatapult() : id(0), jie(0), cash(0)
	{}
};
struct DataXMLCostCatapult
{
	XMLCostCatapult catapultCost[CATAPULT_JIE_NUM];
};

#define MAX_CATAPULT_SKILL_LEVEL (4)
#define MAX_CATAPULT_SKILL_ITEMS (5)
struct XMLCatapultSkillItem
{
	unsigned id;
	unsigned unlocklv;
	unsigned bookid[MAX_CATAPULT_SKILL_LEVEL];
	unsigned char booknum[MAX_CATAPULT_SKILL_LEVEL];

	XMLCatapultSkillItem():
		id(0),
		unlocklv(0)
	{
		memset(bookid, 0, sizeof(bookid));
		memset(booknum, 0, sizeof(booknum));
	}
};

struct DataXMLCatapultSkill
{
	XMLCatapultSkillItem skillitem[MAX_CATAPULT_SKILL_ITEMS];
};


/*****************catapult-end*****************/

/*****************chongzhizixuan-begin*********/
#define CHONGZHIZIXUAN_REWARD_COUNT 2
#define CHONGZHIZIXUAN_ITEM_COUNT 12
#define CHONGZHIZIXUAN_POOL_COUNT 4
struct DataXMLChongZhiZiXuanItem
{
	uint16_t id;
	GiftEquipItem reward[CHONGZHIZIXUAN_REWARD_COUNT];
};
struct DataXMLChongZhiZiXuanCharge
{
	uint16_t id;
	uint16_t times;
	uint32_t require;
};
struct DataXMLChongZhiZiXuanPool
{
	DataXMLChongZhiZiXuanItem item[CHONGZHIZIXUAN_ITEM_COUNT];
	DataXMLChongZhiZiXuanCharge charge[CHONGZHIZIXUAN_ITEM_COUNT];
};

struct DataXMLChongZhiZiXuan
{
	DataXMLChongZhiZiXuanPool pool[CHONGZHIZIXUAN_POOL_COUNT];
};

/*****************chongzhizixuan-end***********/
/*****************beauty-begin*****************/
#define XML_BEAUTY_REWARD_COUNT 5
#define XML_BEAUTY_ACTIVE_ITEM_COUNT 5
#define XML_BEAUTY_REWARD_ITEM_COUNT 10
struct XMLBeautyActiveItem {
	byte id;
	byte add;
	byte max;
	XMLBeautyActiveItem(): id(0), add(0), max(0) {
	}
};
struct XMLBeautyRewardItem {
	byte id;
	uint32_t require;
	GiftEquipItem reward[XML_BEAUTY_REWARD_COUNT];
};
struct DataXMLBeauty {
	XMLBeautyActiveItem active[XML_BEAUTY_ACTIVE_ITEM_COUNT];
	XMLBeautyRewardItem reward[XML_BEAUTY_REWARD_ITEM_COUNT];
};
/*****************beauty-end*******************/
/*****************investment-begin*************/
#define XML_INVESTMENT_RATE_NUM 3
#define XML_INVESTMENT_REWARD_NUM 10
#define XML_INVESTMENT_EQUIP_NUM 5
#define XML_INVESTMENT_RATE_MULTIPLE 100

struct XMLInvestmentReward {
	byte id;
	uint32_t require;
	GiftEquipItem reward[XML_INVESTMENT_EQUIP_NUM];
	XMLInvestmentReward():id(0),require(0){
	}
};
struct DataXMLInvestment {
	float rate[XML_INVESTMENT_RATE_NUM];
	float rate1[XML_INVESTMENT_RATE_NUM];
	XMLInvestmentReward item[XML_INVESTMENT_REWARD_NUM];
};
/*****************investment-end***************/
/*****************birdbridge-begin*************/
#define XML_BIRD_BRIDGE_REWARD_NUM 5
#define XML_BIRD_BRIDGE_ITEM_NUM 4
struct XMLBirdBridgeItem {
	byte id;
	uint32_t require;
	GiftEquipItem reward[XML_BIRD_BRIDGE_REWARD_NUM];
	XMLBirdBridgeItem(): id(0), require(0) {
	}
};
struct DataXMLBirdBridge {
	XMLBirdBridgeItem left[XML_BIRD_BRIDGE_ITEM_NUM];
	XMLBirdBridgeItem right[XML_BIRD_BRIDGE_ITEM_NUM];
	XMLBirdBridgeItem center;
};;
/*****************birdbridge-end***************/
/*****************uniontech-begin*************/
#define XML_MAX_UNIONTECH_NUM 27
#define XML_MAX_UNIONTECH_LEVEL 10
struct XMLUnionTechItem {
	unsigned id;
	unsigned studypoint[XML_MAX_UNIONTECH_LEVEL];
	unsigned gold[XML_MAX_UNIONTECH_LEVEL];
	unsigned wood[XML_MAX_UNIONTECH_LEVEL];
	unsigned eqpoint[XML_MAX_UNIONTECH_LEVEL];
	XMLUnionTechItem() : id(0) {
		memset(studypoint,0,sizeof(studypoint));
		memset(gold,0,sizeof(gold));
		memset(wood,0,sizeof(wood));
		memset(eqpoint,0,sizeof(eqpoint));
	}
};
struct DataXMLUnionTech {
	XMLUnionTechItem tech[XML_MAX_UNIONTECH_NUM];
};
/*****************uniontech-end***************/
/*****************圣诞活动-begin*************/
#define XML_SHENGDAN_REWARD_NUM 4
#define XML_SHENGDAN_CHOUJIANG_RATE_NUM 5
#define XML_SHENGDAN_XUYUAN_DANGCI_NUM 10
#define XML_SHENGDAN_CHARGE_DANGCI_NUM 9
#define XML_SHENGDAN_CONSUME_DANGCI_NUM 9
#define XML_SHENGDAN_EXANGE_DANGCI_NUM 10
struct XMLXuyuanDangciItem {
	unsigned id;
	unsigned require;
	GiftEquipItem reward[XML_SHENGDAN_REWARD_NUM];
	XMLXuyuanDangciItem(): id(0), require(0) {
	}
};
struct XMLExangeItem {
	unsigned id;
	unsigned count;
	unsigned require;
	GiftEquipItem reward[XML_SHENGDAN_REWARD_NUM];
	XMLExangeItem(): id(0), count(0), require(0) {
	}
};
struct DataXMLShengDan {
	GiftEquipItem day;
	unsigned rate[XML_SHENGDAN_CHOUJIANG_RATE_NUM];
	XMLXuyuanDangciItem vow[XML_SHENGDAN_XUYUAN_DANGCI_NUM];
	XMLXuyuanDangciItem change[XML_SHENGDAN_CHARGE_DANGCI_NUM];
	XMLXuyuanDangciItem consume[XML_SHENGDAN_CONSUME_DANGCI_NUM];
	XMLExangeItem exchange[XML_SHENGDAN_EXANGE_DANGCI_NUM];
};
/*****************圣诞活动-end*************/
/*****************小年活动-begin*************/
#define XML_XIAONIAN_CHARGE_DANGCI_NUM 6
#define XML_XIAONIAN_SHOP_DANGCI_NUM 8
#define XML_XIAONIAN_REWARD_NUM 4
struct XMLXiaoNianChargeItem {
	unsigned id;
	unsigned require;
	GiftEquipItem reward[XML_XIAONIAN_REWARD_NUM];
	XMLXiaoNianChargeItem(): id(0), require(0) {
	}
};
struct XMLXiaoNianShopItem {
	unsigned id;
	unsigned moneyType;
	unsigned require;
	GiftEquipItem reward[XML_XIAONIAN_REWARD_NUM];
	XMLXiaoNianShopItem(): id(0), moneyType(0), require(0) {
	}
};
struct DataXMLXiaoNian {
	XMLXiaoNianChargeItem charge[XML_XIAONIAN_CHARGE_DANGCI_NUM];
	XMLXiaoNianShopItem shop[XML_XIAONIAN_SHOP_DANGCI_NUM];
};
/*****************小年活动-end*************/
/*****************情人节玫瑰-begin*************/
#define XML_QINGRENJIE_NVSHEN_NUM 7
#define XML_QINGRENJIE_MEIGUI_REWARD_NUM 4
#define XML_QINGRENJIE_LEIJI_NUM 5
struct XMLQingRenJieMeiGuiItem {
	unsigned id;
	GiftEquipItem reward[XML_QINGRENJIE_MEIGUI_REWARD_NUM];
	XMLQingRenJieMeiGuiItem(): id(0) {
	}
};
struct XMLQingRenJieMeiGuiLeiJiItem {
	unsigned id;
	unsigned require;
	GiftEquipItem reward[XML_QINGRENJIE_MEIGUI_REWARD_NUM];
	XMLQingRenJieMeiGuiLeiJiItem(): id(0), require(0) {
	}
};
struct DataXMLQingRenJieMeiGui {
	XMLQingRenJieMeiGuiItem meigui[XML_QINGRENJIE_NVSHEN_NUM];
	XMLQingRenJieMeiGuiItem quanfu[XML_QINGRENJIE_NVSHEN_NUM];
	XMLQingRenJieMeiGuiLeiJiItem leiji[XML_QINGRENJIE_LEIJI_NUM];
};
/*****************情人节玫瑰-end*************/
/******************nianshou boss*****************/
#define XML_NIANSHOU_BOSS_REWARD_NUM 3
#define XML_NIANSHOU_BOSS_ITEM_NUM 5
struct XMLNianShouBossItem {
	byte id;
	uint32_t require;
	GiftEquipItem reward[XML_NIANSHOU_BOSS_REWARD_NUM];
	XMLNianShouBossItem(): id(0),require(0) {
	}
};
struct DataXMLNianShouBoss {
	XMLNianShouBossItem item[XML_NIANSHOU_BOSS_ITEM_NUM];
};
/**********************************************/

class CDataXML
{
private:
	CDataXML();
public:
	virtual ~CDataXML();
	int Init(const std::string &path, semdat sem=sem_xml, bool initconfig=false);
	static CDataXML* GetCDataXML();
	static CDataXML* GetInitXML();

	static int GetFile(const string &fname, string &path);
	static int readJsonConfFile(const string &fname, Json::Value &jdata);
	/*****************building*****************/
	int InitBuilding();
	int GetBuilding(unsigned t, unsigned lv, XMLBuildingItem& build);
	/***************Hero**********************/
	int InitHero();
	int GetHero(unsigned id, XMLHero& hero);
	int CheckHero(unsigned id);
	int RefreshHero(unsigned type,unsigned& hero1,unsigned& star1,unsigned& hero2,unsigned& star2,unsigned& hero3,unsigned& star3, bool purple = false);

	static unsigned Str2Hero(string& str);
	static string Hero2Str(unsigned id);
	/*************************************/

	/***************MixHero**********************/
	int InitMixHero();
	int GetMixHero(unsigned id, unsigned star, XMLSourceHero mixhero[XML_HERO_SOURCE]);
	/*************************************/

	/****************VIP*********************/
	int InitVIP();
	int GetVIP(unsigned index, XMLVIP& vip);
	int GetVIPCharge(unsigned vipcharge[XML_VIP_GRADE]);
	/*************************************/

	/***************EquipSub**********************/
	int InitEquipSub();
	int GetEquipSub(unsigned lvl, unsigned &stone, unsigned &gold, unsigned subNum, vector<string> &keep, vector<EquipSub> &subs);
	int GetEquipSubValue(unsigned lvl, string id, unsigned star, unsigned &value);
	int GetEquipSubStar(unsigned lvl, string id, unsigned value, unsigned &star);
	/*************************************/

	/*****************GiftBag 后台开礼包******************/
	int InitGiftBag();
	int GetGiftBag(unsigned uid,unsigned giftbag_id,unsigned count,Json::Value &data);
	int GetGiftBagLevel(unsigned id, XMLGifgBagLvl &item);
	/*************************************/

	/******************boats*******************/
	int InitBoats();
	int GetBoat(uint32_t boatId, XMLBoat &boat);
	int GetBoatType(unsigned &bt);
	/******************************************/

	/******************hammer*******************/
	int InitHammer();
	int TestHammerData();
	int GetHammer(map<uint32_t, Hammer> &mapHammer);
	int GetHammerAllServer(map<uint32_t, Hammer> &mapHammer);
	/******************************************/

	/**************TreasureHunt***********************/
	int InitTreasureHunt();
	int GetTreasureHunt(unsigned id, unsigned times, vector<TreasureHuntItem> &result);
	/*************************************/

	/*****************EquipIntensifys  装备强化******************/
	int InitEquipIntensifys();
	int GetEquipIntensifys(unsigned id, unsigned q_level, unsigned xingyunshi_count, Json::Value &result);
	int GetEquipIntensifysRate(unsigned id, unsigned q_level, unsigned xingyunshi_num, unsigned &result);
	/*************************************/

	/*****************EquipDismantling装备拆解******************/
	int GetEquipDismantling_xingyunshi(unsigned id, unsigned q_level, unsigned &xingyunshi_count);  //装备拆解获得幸运石为对应强化等级一键搞定所需的幸运石总量 *0.3,位于EquipIntensifys
	int GetEquipDismantling_qianghuashi(unsigned q_level, unsigned &q_id,  unsigned &q_number);	//装备拆解获得强化石位于olequipset
	int GetEquipDismantling_taozhuang(unsigned level, unsigned part, unsigned &num);	//套装拆解获得套装材料位于olequipset
	/*************************************/

	/*****************olequipset******************/
	int InitOlequipset();
	int GetBuildOrUpSetCailiao(unsigned level, unsigned part, Json::Value &data);
	int GetRefineCailiao(Json::Value &data, unsigned kind);
	int EquipSetWuxing(unsigned level, unsigned &count, unsigned &bs, bool &wuxingresult);
	int EquipSetBless(unsigned level, unsigned exp, unsigned &eqid, unsigned &count, unsigned &bs, unsigned &n_bless_level, unsigned &n_exp);
	int EquipSetShenWen(unsigned level, unsigned exp, unsigned &eqid, unsigned &count, unsigned &bs, unsigned &n_bless_level, unsigned &n_exp);
	int EquipSetShenGe(unsigned level, unsigned exp, unsigned eqid[3], unsigned count[3], unsigned &bs, unsigned &n_bless_level, unsigned &n_exp);

	/*************************************/


	/*****************payrank******************/
	int GetPayrank(unsigned uid ,unsigned lottery_number,unsigned point,vector<unsigned> &id,vector<unsigned> &count,vector<string> &type);
	/*************************************/

	/**************shop**********************/
	int InitShop();
	int GetShopItem(unsigned id, XMLShop &item);
	/****************************************/

	/**************WorldBattleShop**********************/
	int InitWorldBattleShop();
	int GetWorldBattleShopItem(unsigned id, XMLWorldBattleShopItem &item, unsigned &count);
	int GetWorldBattleKillRewards(Json::Value &data, const unsigned& index);
	int GetWorldBattleKillRewards(Json::Value &data);
	/****************************************/

	/**************RankBattleShop**********************/
	int InitRankBattleShop();
	int GetRankBattleShopItem(unsigned id, XMLRankBattleShopItem &item, unsigned &count);
	/****************************************/

	/**************HufuShop**********************/
	int InitHufuShop();
	int GetHufuShopItem(unsigned id, XMLHufuShopItem &item, unsigned &count);
	/****************************************/

	/**************FashionShop**********************/
	int InitFashionShop();
	int GetFashionShopItem(unsigned id, XMLFashionShopItem &item);
	/****************************************/

	/*************equipment*****************/
	int InitEquipment();
	int CheckEquipment(unsigned id);
	/****************************************/

	/*************powerup*****************/
	static float GetRandomGradePoint(int type, int grade, int level);
	static float GetMaxGradePoint(int grade, float point);
	static int GetGradeLevel(unsigned id, int &grade, int &level);
	static int GetHeroStepNeedHeroLevel(const int grade, int & level);
	static int GetHeroStepNeedBuildingLevel(const int grade, int & level);
	static int GetHeroStepNeedGoldCost(const int grade, int & coins);
	static int GetHeroStepNeedBSCost(const int grade, int & bs);
	/****************************************/

	/*************newlottery*****************/
	int InitNewLottery();
	int GetNewLottery(unsigned uid, unsigned level, vector <unsigned> &id, vector <unsigned> &type_id, vector <unsigned> &rate, vector <unsigned> &eqid, vector <unsigned> &num, vector <unsigned> &total, unsigned &openfloor, unsigned &cash);
	/****************************************/

	/*************juexue*****************/
	int GetJuexue(unsigned npc, bool zhaohuan, unsigned level, unsigned &cost, unsigned &id, unsigned &next);
	/****************************************/

	/*************qixi_choujiang*****************/
	int InitChoujiang();
	int GetChoujiangWupin(unsigned uid, unsigned floors, unsigned count, vector <unsigned> &awards_index_id, vector <unsigned> &awards_type_id,
			vector <unsigned> &awards_eqid, vector <unsigned> &awards_num, vector <unsigned> &limit_items);
	/****************************************/

	/*************qixi_choujiang*****************/
	int GetJianglingGrow(unsigned uid, unsigned &grow_value, unsigned &dan_growth, unsigned &prosper);
	/****************************************/

	/*************quest reward*****************/
	int InitActivityConfig();
	int InitOlGateConfig();
	int InitQuestConfig();
	int GetActivityConfig(const string &name, map<string, string> &config);
	int GetOlGateConfig(unsigned level, map<string, string> &config);
	int GetQuestConfig(const string &id, Json::Value &reward);
	/****************************************/

	int InitHeavenDaoist();
	int GetHeavenDaoistItem(const unsigned id, XMLHeavenDaoist &item);
	int GetHeavenDaoistLv(unsigned last, unsigned exp, unsigned &lv);

	int InitCostHeavenDaoist();
	int GetCostHeavenDaoist(bool is_heaven, unsigned jie_index, unsigned &cash);

	//八阵图
	int InitEightFormation();
	int GetEightFormationItem(const unsigned id, const unsigned idx, XMLEightFormation &item);
	int GetEightFormationLv(unsigned id, unsigned idx, unsigned exp, unsigned &lv);
	unsigned GetMaxExp(unsigned id, unsigned maxlv);

	int InitCostEightFormation();
	int GetCostEightFormation(unsigned jie_index, unsigned &cash);

	int InitDouble11();
	int GetDouble11AllData(DataXMLDouble11 &dataDouble);

	int InitEggReward();
	int GetEggItems(unsigned lock, Json::Value &newAct, vector<EggRewardItem> &items);

	int InitBetShop();
	int GetBetShopItem(unsigned eqid, XMLBetShopItem &item);

	//签到奖励
	int InitSignInReward();
	int GetSignInReward(int index, XMLSignInReward& reward);

	//邀请奖励
	int InitInviteReward();
	int GetInviteLevelItem(unsigned id, XMLInviteLevelGiftItem& reward);

	//武魂
	int InitWeaponSoulCost();
	int GetWeaponSoulCostItem(unsigned id, XMLWeaponSoulCostItem& item);

	//暑假前奏 @start
	int InitPreSummer();
	XMLPreSummerItem& GetPreSummerItem(unsigned id, unsigned type);
	unsigned GetPreSummerCost(unsigned index, unsigned type);
	//@end

	//天坛后台
	int InitTemple();
	XMLTempleItem GetTemplePrayItem(unsigned id);
	//@end

	//开区充值大礼包
	int InitNewRechargeBag();
	XMLNewRechargeRewardItem GetNewRechargeRewardItem(unsigned id);
	//@end

	//每日团购
	int InitGroupBuyDaily();
	void GetGroupBuyDailyBuyTtem(DataXMLGroupBuyDailyBuyItem& result);
	void GetGroupBuyDailyBuyReward(int id, DataXMLGroupBuyDailyReward& result);
	//@end

	//充点小钱
	int  InitLittleRecharge();
	void GetLittleRechargeReward(bool is4399, unsigned zoneId, DataXMLLittleRechargeZone& result);
	//@end

	//月度礼包
	int InitMonthGiftBag();
	unsigned GetMonthGiftBagEquipId(bool is4399, unsigned zoneid, unsigned index);
	//@end

	//组合商店
	int InitCombinedShop();
	void GetCombinedShopEquipItem(unsigned index, DataXMLCombinedShopItem& item);
	//@end

	//预告功能
	int InitNewerAdvance();
	void GetNewerAdvanceItem(unsigned id, DataXMLNewerAdvanceItem& item);
	//@end

	//步步为营兑换
	int InitTreasureHuntExchange();
	void GetTreasureHuntExchangeItem(unsigned index, bool isPoint, DataXMLTreasureHuntExchangeItem& item);

	//圣诞活动
	int InitChristmas();
	void GetChristmasExtraItem(unsigned id, DataXMLChristmasExtraItem& item);
	void GetChristmasEggItem(unsigned id, DataXMLChristmasEgg& item);

	//积分互换
	int InitPointExchange();
	void GetPointExchangeItem(unsigned index, DataXMLPointExchageRewardItem& item);
	void GetPointCutPriceItem(unsigned id, DataXMLPointCutPriceItem& item);
	unsigned GetPointCutPriceLvl(unsigned point);

	//建筑皮肤
	int InitBuildSkin();
	void GetBuildSkinBuy(unsigned id, DataXMLBuildingSkinBuy& buy_item);
	void GetBuildSkinRelet(unsigned id, unsigned type, DataXMLBuildingSkinReletItem& relet);

	//7日登录
	int InitTutorLogin();
	void GetTutorLoginItem(unsigned id, DataXMLTutorLoginItem& result);

	//霸业礼包
	int InitImperialGift();
	void GetImperialGift(unsigned id, DataXMLImperialGiftItem& result);

	//限时冲级
	int InitTimeLimitUpgrade();
	void GetTimeLimitUpgrade(unsigned index, DataXMLTimeLimitUpgradeItem& result);

	//鸡年纳福
	int InitYearFortune();
	DataXMLYearFortuneLib GetYearFortuneLib(unsigned id);
	void GetYearFortuneItem(unsigned libId, unsigned id, DataXMLYearFortuneItem& result);
	int  GetYearFortuneNeedPoint(unsigned index);

	//寒假狂欢
	int InitJsonWinterHolidayRevelry();
	const DataWinterHolidayRevelry& GetWinterHolidayRevelryConfig() const;

	//信物强化
	int InitTokenIntensify();
	const DataTokenIntensify& GetTokenIntensify() const;

	//世间秘宝
	int InitWorldTreasure();
	const ConfigWorldTreasure& GetConfigWorldTreasure() const;

	//武魂回馈
	int InitSoulFeedback();
	const ConfigSoulFeedback& GetConfigSoulFeedback() const;

	//觉醒回馈
	int InitAwakenFeedback();
	const ConfigAwakenFeedback& GetConfigAwakenFeedback() const;
	//铸魂打折
	int InitCastSoulDiscount();
	const ConfigCastSoulDiscount& GetConfigCastSoulDiscount() const;
	//宝石折扣
	int InitGemDiscount();
	const ConfigGemDiscount& GetConfigGemDiscount() const;
	//金玉满堂
	int InitTreasuresAllAround();
	const ConfigTreasuresAllAround& GetTreasureAllAround() const;
	//将灵培养
	int InitSpiritFoster();
	const ConfigSpiritFoster& GetSpiritFoster() const;
	//的卢凝魂
	int InitChargeHorse();
	const ConfigChargeHorse& GetChargeHorse() const;

	//vicky又要做个充值活动
	int InitVickyAccX();
	const ConfigVickyAccX& GetVickyAccX() const;
	const ConfigVickyAccX1& GetVickyAccX1() const;
	const ConfigVickyAccX2& GetVickyAccX2() const;
	const ConfigVickyAccX3& GetVickyAccX3() const;
	const ConfigVickyAccX4& GetVickyAccX4() const;
	const ConfigVickyAccX5& GetVickyAccX5() const;
	//机甲黄忠
	const Confighuangzhong& Gethuangzhong() const;
	//vicky的开服活动
	const ConfigVickyNewOpen& GetVickyNewOpen() const;
//autolable4
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_fuzhuhesui)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_zhuniandaji)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_qingrenjie)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_yuandan2018)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_yearend2018)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_winter2018)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_double11_2018)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_hao)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_reu)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_taotie)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_qilin)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_pheonix)
GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_nnom)
	//vicky没想好名字的活动
	GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NO_NAME)
	//兵书突破
	GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_BINGSHU)
	//千服同庆
	GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_QIANFU)
	//vicky懒得给我说名字的活动
	GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NNA)
	int InitBarbarKing();
	int GetBarbarKingItem(unsigned index, unsigned gate, XMLBarbarItem &item);

	int InitFiveTiger();
	int GetFiveTigerItem(unsigned chapter, unsigned sgate, unsigned egate, unsigned &yl, Json::Value &result);

	//新绝世无双
	int InitNewJueShiWS();
	int GetNewJueShiWSItem(unsigned id, XMLNewJueShiWS & item, unsigned & index);

	//鸿运当头活动
	int InitOpporKnockReward();
	int GetTurnRate(unsigned type, int * & prates);
	int GetOpporKnockRewardById(unsigned id, EquipmentRateInfo & equipitem);
	int GetRefreshPoolItem(XMLRefreshPoolItem & item);
	int GetSecondPoolItem(unsigned type, XMLSecondPoolItem & items);

	//幸运连连
	int InitFortunatelyAgain();
	int GetFortunatelyRewardItem(int type, XMLFortunatelyRewardItems & item);
	int GetSingleEquipItem(unsigned index, EquipmentInfo & iteminfo);

	//充值自选
	int InitRechargeOptional();
	int GetOptionalRewardItem(vector<unsigned> vctid, vector<XMLOptionalItems> & vctitem, unsigned & per);

	//小兵升级和训练
	int InitSoldierTrainAndUp();
	int GetSoldierLevelItem(unsigned sid, unsigned level, XMLSoldierLevelItems & levelitem, unsigned char & grade);

	//兵书遁甲技能
	int InitHeavenDAOSkill();
	int GetHeavenSkillItem(unsigned id, XMLHeavenDaoSkillItem & skillitem);
	int GetDAOSkillItem(unsigned id, XMLHeavenDaoSkillItem & skillitem);

	//天命
	int InitTurnPlate();
	int GetTurnPlateRewardItem(int type, XMLFortunatelyRewardItems & item);   //因为天命的数据结构与幸运连连相同
	int GetTurnPlateSingleEquipItem(unsigned index, EquipmentInfo & iteminfo);


	/**************厚惠有期**********************/
	int InitHouHuiYouQi();
	int GetHouHuiYouQiItem(unsigned sid, unsigned b_index, unsigned s_index, XMLHouHuiYouQiItem & item);
	int GetHouHuiYouQiBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right);
	/****************************************/


	/**************超值折扣**********************/
	int InitChaoZhiZheKou();
	int GetChaoZhiZheKouItem(unsigned sid, unsigned b_index, unsigned s_index, XMLChaoZhiZheKouItem & item);
	int GetChaoZhiZheKouBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right);
	/****************************************/


	/**************约惠巨献**********************/
	int InitYueHuiJuXian();
	int GetYueHuiJuXianItem(unsigned sid, unsigned b_index, unsigned s_index, XMLYueHuiJuXianItem & item);
	int GetYueHuiJuXianBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right);
	/****************************************/


	/**************全服限购**********************/
	int InitLimitBuyOfZone();
	int GetLimitBuyOfZoneItem(unsigned sid, unsigned index, XMLLimitBuyOfZoneItem & item);
	int GetLimitBuyOfZoneTableRight(unsigned sid, unsigned consume, unsigned & table_right);
	/****************************************/

	/**************五行防御成长**********************/
	int InitFiveDefendGrow();
	int GetFiveDefendGrowItem(unsigned level, XMLFiveDefendGrowItem & item);
	/****************************************/

	/**************国庆盛典**********************/
	int InitCountryDay();

	int GetCountryDayLoginItem(unsigned index, XMLCountryDayLoginItem & item);
	int GetCountryDayShopItem(unsigned index, XMLCountryDayShopItem & item);
	int GetCountryDayBagItem(unsigned index, XMLCountryDayBagItem & item);

	int GetCountryDayLoginOpenTime(unsigned & begin_ts, unsigned & end_ts);
	int GetCountryDayShopOpenTime(unsigned & begin_ts, unsigned & end_ts);
	int GetCountryDayBagOpenTime(unsigned & begin_ts, unsigned & end_ts);
	/****************************************/

	//五行灵珠
	int InitWuxingPearl();
	int GetWuxingPearlData(unsigned index, unsigned &cond, unsigned &eqid, unsigned &count);

	/**************心动特卖**********************/
	int InitHeartbeatBigSale();
	int GetHeartbeatBigSaleItem(unsigned sid, unsigned index, XMLHeartbeatBigSaleItem & item);
	/****************************************/

	/**************五行商铺 **********************/
	int InitFiveShop();
	int GetFiveSpecialShopItem(unsigned index, XMLFiveSpecialShopItem & item);
	int GetFiveDiscountShopItem(unsigned index, XMLFiveDiscountShopItem & item);
	int GetFiveShopQuan(unsigned & pay, unsigned & count, unsigned & limit);
	/****************************************/


	/**************觉醒特惠 **********************/
	int InitJueXingTeHui();
	int GetJueXingTeHuiItem(unsigned index, XMLJueXingTeHuiItem & item);
	int GetJueXingTeHuiItemsCnt(unsigned & cnt);
	/****************************************/

	//金秋十月 充值回馈
	int InitJinqiushiyueChongzhihuikui();
	int GetJinqiushiyue(unsigned index, unsigned type, unsigned& need, pair<unsigned, unsigned> &item);
	int GetChongzhihuikui(unsigned index, unsigned type, unsigned& need, pair<unsigned, unsigned> &item);

	//11月回馈
	int InitJinQiuNovember();
	int GetJinQiuNovember(unsigned index, unsigned & need, pair<unsigned, unsigned> & item);

	//充值送神纹符
	int InitAcchargeBackShenwen();
	int GetAcchargeBackShenwen(unsigned index, unsigned & need, pair<unsigned, unsigned> & item);

	//至尊宝箱
	int InitZhiZunBaoXiang();
	int GetZhiZunBaoXiangK(pair<unsigned, unsigned> &item);
	int GetZhiZunBaoXiangB(unsigned index, pair<unsigned, unsigned> &item);

	/**************免费兑换**********************/
	int InitFreeExchange();
	int GetFreeExchangeItem(unsigned index, XMLFreeExchangeItem & item);
	int GetFreeExchangeItemsCnt(unsigned & cnt);
	/****************************************/

	/**************双11**********************/
	int InitDoubleEleven();
	int GetDoubleElevenBigItem(unsigned big_index, XMLDoubleElevenBigItem & item);
	int GetDoubleElevenBigItemsCnt(unsigned & cnt);
	/****************************************/

	/**************聚宝匣**********************/
	int InitJuBaoXia();
	int GetJuBaoXiaCommonRate(map<unsigned, unsigned> & rate);
	int GetJuBaoXiaPreciousRate(unsigned circle, map<unsigned, unsigned> & rate);
	int GetJuBaoXiaCommonItem(unsigned index, XMLJuBaoXiaTreasureCommonItem & item);
	int GetJuBaoXiaPreciousItem(unsigned index, XMLJuBaoXiaTreasurePreciousItem & item);
	int GetJuBaoXiaDailyFreeItem(XMLJuBaoXiaDailyFreeItem & item);
	int GetJuBaoXiaExchangeItem(XMLJuBaoXiaExchangeItem & item);
	int GetJuBaoXiaKeyItem(unsigned index, XMLJuBaoXiaKeyItem & item);
	/****************************************/

	/**************兵书进阶**********************/
	int InitHeavenStep();
	int GetHeavenStepItem(unsigned jie, XMLHeavenStepRewardItem & item);
	/****************************************/

	/**************遁甲进阶**********************/
	int InitDaoistStep();
	int GetDaoistStepItem(unsigned jie, XMLDaoistStepRewardItem & item);
	/****************************************/

	/**************珍宝阁魂石**********************/
	int InitZhenBaoGeHero();
	int GetZhenBaoGeHeroItem(unsigned big_index, unsigned small_index, XMLZhenBaoGeHeroItem & item);
	/****************************************/

	/**************珍宝阁宝石**********************/
	int InitZhenBaoGeBuilding();
	int GetZhenBaoGeBuildingItem(unsigned big_index, unsigned small_index, XMLZhenBaoGeBuildingItem & item);
	/****************************************/

	/**************魂石进阶**********************/
	int InitHeroStoneStep();
	int GetHeroStoneStepItem(unsigned index, XMLHeroStoneStepItem & item);
	/****************************************/

	/**************宝石进阶**********************/
	int InitBuildingStoneStep();
	int GetBuildingStoneStepItem(unsigned index, XMLBuildingStoneStepItem & item);
	/****************************************/

	/**************成长开发**********************/
	int InitGrowDevelop();
	int GetGrowDevelopRewardItem(unsigned big_index, unsigned small_index, XMLGrowDevelopRewardItem & item);
	int GetGrowDevelopCond(unsigned level, unsigned & require);
	/****************************************/

	/**************每日充值**********************/
	int InitDailyChargeReward();
	int GetDailyChargeRewardItem(unsigned index, XMLDailyChargeReward & item);
	/**************每日充值**********************/

	/**************百宝箱**********************/
	int InitTreasureBox();
	int GetTreasureBoxRewardItems(DataXMLTreasureBox & treasureItems);
	int GetSpecificBoxReward(unsigned id, XMLTreasureBox & item);
	/************************************/

	/**************信物系统**********************/
	int InitKeepsake();
	int GetKeepSakeProduceCfg(XMLKeepsakeProduce & produce);  //加载产出配置
	int GetKeepSakeUpgradeCfg(XMLTokenUpgrade & upgrade);   //加载升级配置
	int GetKeepSakeBaseCfg(XMLTokenBase & base);  //基础配置
	int GetSakeDefective(unsigned & eqid);  //获取残品的eqid
	int GetSakeExpProps(unsigned & eqid);  //获取经验石的eqid
	int GetLevelIndex(unsigned level);  //根据玩家等级获取等级对应配置的索引
	unsigned GetXinWuReward(unsigned index, bool first);
	/************************************/

	/**************充值回馈**********************/
	int InitChargeFeedback();
	int GetChargeFeedbackRewardItem(unsigned index, string type, XMLChargeFeedbackReward & item);
	/************************************/

	/**************欢庆元旦**********************/
	int InitCelebrateNewYear();
	int GetCeleNewYearRewardItem(unsigned index, XMLNewYearReward & item);
	/************************************/

	/**************消费自选**********************/
	int InitPayOptional();
	int GetPayOptionalItem(vector<unsigned> & indexs, vector<PayOptionalItem> & items);

	/**************合区活动**********************/
	int InitHeQuActivity();
	int GetChargeRewardItem(unsigned index, HeQuChargeItem & item);
	int GetVIPRewardItem(unsigned vindex, unsigned sindex, HeQuVIPItem & item);
	int GetRecompenseRewardItem(unsigned index, HeQuRecompense & item);

	/**************古卷奇书**********************/
	int InitAncientScroll();
	int GetAncientItem(unsigned id, unsigned level, ScrollItem & item);

	/**************保护旗帜**********************/
	int InitProtectFlag();
	int GetProtectFlagPointer(DataXMLProtectFlag ** pflag);

	/**************保护女神**********************/
	int InitProtectGoddess();
	int GetProtectGoddessRewardItem(unsigned id, ProtectGoddessRewardItem ** pflag);

	/**************投石机**********************/
	int InitCatapult();
	int GetCatapultItem(const unsigned id, XMLCatapult &item);
	int GetCatapultLv(unsigned last, unsigned exp, unsigned &lv);

	int InitCostCatapult();
	int GetCostCatapult(unsigned jie_index, unsigned &cash);

	int InitCatapultSkill();
	int GetCatapultSkillItem(unsigned id, XMLCatapultSkillItem & skillitem);
	/**************投石机**********************/

	/**************chongzhizixuan**********************/
	int InitChongZhiZiXuan();
	int GetChongZhiZiXuanItem(unsigned pool, unsigned item, vector<GiftEquipItem> &data);
	int GetChongZhiZiXuanCharge(unsigned pool, unsigned charge, unsigned &count);

	/**************beauty******************************/
	int InitBeauty();
	int GetBeautyActive(unsigned id, XMLBeautyActiveItem &item);
	int GetBeautyReward(unsigned id, XMLBeautyRewardItem &item);

	/**************investment***************************/
	int InitInvestment();
	int GetInvestmentRate(vector<unsigned> &r, bool last);
	int GetInvestmentReward(unsigned id, XMLInvestmentReward &item);

	/**************birdbridge***************************/
	int InitBirdBridge();
	int GetBirdBridgeItem(unsigned type, unsigned id, XMLBirdBridgeItem &item);

	/**************UnionTech***************************/
	int InitUnionTech();
	int GetUnionTechItem(unsigned id, XMLUnionTechItem &item);
	void ViewUnionTech();

	/**************ShengDan2018***************************/
	int InitShengDan();
	void ViewShengDan();
	int GetShengDanItem( DataXMLShengDan &item);

	/**************XiaoNian2018***************************/
	int InitXiaoNian();
	int GetXiaoNianItem( DataXMLXiaoNian &item);

	/**************QingRenJieMeiGui***************************/
	int InitQingRenJieMeiGui();
	int GetQingRenJieMeiGuitem( DataXMLQingRenJieMeiGui &item);

	/**************NianShouBoss***************************/
	int InitNianShouBoss();
	int GetNianShouBossReward(unsigned id, XMLNianShouBossItem &data);

	/*解析XML函数指针*/
	typedef int (CDataXML::* ParseComplete)(void * , CMarkupSTL & xmlConf);

protected:

	static CDataXML* m_pData;
	bool m_init;

	/*****************building*****************/
	map<pair<unsigned,unsigned>, unsigned> m_mapBuilding;
	CShareMemory m_shBuilding;
	/***************Hero**********************/
	map<unsigned,pair<unsigned,unsigned> > m_mapXMLHeroRate[XML_HERO_RATE];
	map<unsigned,pair<unsigned,unsigned> > m_mapXMLHeroRatePurple;
	map<unsigned,unsigned> m_mapXMLHero;
	CShareMemory m_shHero;
	/*************************************/

	/****************MixHero*********************/
	CShareMemory m_shMixHero;
	/*************************************/

	/****************VIP*********************/
	CShareMemory m_shVIP;
	/*************************************/

	/***************EquipSub**********************/
	CShareMemory m_shEquipSub;
	map<EquipSubLevel, map<unsigned, string> > m_mapEquipSub;
	map<EquipSubItem, map<unsigned, EquipSub> > m_mapEquipSubItem;
	map<EquipSubLevel, map<string, map<unsigned, unsigned> > > m_mapEquipSubValue;
	map<EquipSubLevel, map<string, map<unsigned, unsigned> > > m_mapEquipSubStar;
	/*************************************/

	/****************Boats*********************/
	CShareMemory m_shBoats;
	vector<XMLBoat> m_vBoat;
	map<uint32_t, uint32_t> m_mapBoatType;
	/*************************************/

	/****************Hammer*********************/
	CShareMemory m_shHammer;
	map<uint32_t, Hammer> m_mapHammer;
	map<uint32_t, Hammer> m_mapHammerAllServer;
	/*************************************/

	/*************武魂 升级消耗****************************************/
	CShareMemory m_shpartpowerconfig;
	std::map<unsigned, unsigned> m_mapWeaponSoulCost;

	//std::map<unsigned, XMLWeaponSoulCostItem> m_mapWeaponSoulCost;
	/*************************************************************/

	/****************GiftBag******************/
	CShareMemory m_shsggiftbagconfig;
	map<unsigned,unsigned> m_mapXMLGiftBag;
	map<unsigned,vector<int> > m_mapXMLGiftBagRate;
	/*************************************/
	
	/****************SignInReward**************/
	CShareMemory m_shsgsigninnewconfig;
	/*******************************************/

	/****************InviteReward**************/
	CShareMemory m_shsginvitegiftconfig;
	std::map<unsigned, unsigned> m_mapXMLInvite;
	/*******************************************/

	/**************TreasureHunt***********************/
	CShareMemory m_shTreasureHunt;
	map<unsigned, map<unsigned, unsigned> > m_mapTreasureHunt;
	/*************************************/

	/****************equipintensifys******************/
	CShareMemory m_shequipintensifys;
	/*************************************/

	/****************olequipset******************/
	CShareMemory m_sholequipset;
	/*************************************/

	/****************Payrank******************/
	map<unsigned,unsigned> m_mapPayrank[PAYRANK_LEVEL],m_map4Payrank[PAYRANK_LEVEL];
	static const Payrank level_1[PAYRANK_COUNT];
	static const Payrank level_2[PAYRANK_COUNT];
	static const Payrank level_3[PAYRANK_COUNT];
	static const Payrank level_4_1[PAYRANK_COUNT];
	static const Payrank level_4_2[PAYRANK_COUNT];
	static const Payrank level_4_3[PAYRANK_COUNT];
	/*************************************/

	/**************shop**********************/
	CShareMemory m_shShop;
	map<unsigned,XMLShop> m_mapXMLShop;
	/****************************************/

	/**************worldBattleShop**********************/
	CShareMemory m_shWorldBattleShop;
	map<unsigned,XMLWorldBattleShopItem> m_mapXMLWorldBattleShop;
	/****************************************/

	/**************rankBattleShop**********************/
	CShareMemory m_shRankBattleShop;
	map<unsigned,XMLRankBattleShopItem> m_mapXMLRankBattleShop;
	/****************************************/

	/**************hufuShop**********************/
	CShareMemory m_shHufuShop;
	map<unsigned,XMLHufuShopItem> m_mapXMLHufuShop;
	/****************************************/

	/***************暑假前奏**************************/
	CShareMemory m_shPreSummer;
	//@end

	/***************天坛祈福**************************/
	CShareMemory m_shTemple;
	//@end

	//开区充值大礼包
	CShareMemory m_shNewRecharge;

	//每日团购
	CShareMemory m_shGroupBuyDaily;

	//充点小钱
	CShareMemory m_shLittleRecharge;

	//月度礼包
	CShareMemory m_shMonthGiftBag;

	//组合商店
	CShareMemory m_shCombinedShop;

	//预告功能
	CShareMemory m_shNewerAdvance;

	//步步为营兑换
	CShareMemory m_shTreasureHuntExchange;

	//圣诞活动
	CShareMemory m_shChristmas;

	//积分换礼
	CShareMemory m_shPointExchange;
	//建筑皮肤
	CShareMemory m_shBuildingSkin;
	//7日登录
	CShareMemory m_shTutorLogin;
	//霸业礼包
	CShareMemory m_shImperialGift;
	//限时冲级
	CShareMemory m_shTimeLimitUpgrade;
	//鸡年纳福
	CShareMemory m_shYearFortune;
	//寒假狂欢
	DataWinterHolidayRevelry m_JsonWinterHolidayRevelry;
	//信物强化
	DataTokenIntensify m_tokenIntensify;
	//世间秘宝
	ConfigWorldTreasure m_worldTreasure;
	//武魂回馈
	ConfigSoulFeedback m_soulFeedback;
	//觉醒回馈
	ConfigAwakenFeedback m_awakenFeedback;
	//铸魂打折
	ConfigCastSoulDiscount m_castSoulDiscount;
	//宝石折扣
	ConfigGemDiscount m_gemDiscount;
	//金玉满堂
	ConfigTreasuresAllAround m_treasuresAllAround;
	//将灵培养
	ConfigSpiritFoster m_spiritFoster;
	//的卢凝魂
	ConfigChargeHorse m_chargeHorse;
	//vicky又要做个充值活动
	ConfigVickyAccX m_vicky_acc_x;
	ConfigVickyAccX1 m_vicky_acc_x1;
	ConfigVickyAccX2 m_vicky_acc_x2;
	ConfigVickyAccX3 m_vicky_acc_x3;
	ConfigVickyAccX4 m_vicky_acc_x4;
	ConfigVickyAccX5 m_vicky_acc_x5;
	//机甲黄忠
	Confighuangzhong m_huangzhong;
	//vicky的开服活动
	ConfigVickyNewOpen m_VickyNewOpen;

	/************equipment***************/
	CShareMemory m_shEquipment;
	set<unsigned> m_setXMLEquipment;
	/****************************************/

	/************new_lottery***************/
	CShareMemory m_shnewlottery;
	map<unsigned, unsigned> m_mapXMLfirstlottery[XML_PARTITION_NUM];
	map<unsigned, unsigned> m_mapXMLsecondlottery[XML_PARTITION_NUM];
	/****************************************/

	/*************juexue*****************/
	static const unsigned juexue_cost[XML_JUEXUE_NPC_NUM];
	static const unsigned juexue_chance[XML_JUEXUE_NPC_NUM];
	static const unsigned juexue_fall[XML_JUEXUE_NPC_NUM + 1][e_juexue_type_max];
	static const unsigned juexue_level[XML_JUEXUE_LEVEL_NUM];
	static const unsigned juexue_type[XML_JUEXUE_LEVEL_NUM][XML_JUEXUE_TYPE_NUM][e_juexue_max];
	static const unsigned juexue_id[XML_JUEXUE_TYPE_NUM][e_juexue_max];
	map<unsigned, unsigned> m_mapXMLJuexueFall[XML_JUEXUE_NPC_NUM + 1];
	map<unsigned, unsigned> m_mapXMLJuexueType[XML_JUEXUE_LEVEL_NUM][XML_JUEXUE_TYPE_NUM];
	/****************************************/

	/************choujiang_zhuanpan***************/
	CShareMemory m_shchoujiang;
	map<unsigned, unsigned> m_mapFloor_1;
	map<unsigned, unsigned> m_mapFloor_2;
	/****************************************/

	/************jiangling***************/
	static const unsigned chengzhang[JIANGLING_CHENGZHANG_L][JIANGLING_CHENGZHANG_L];
	static const unsigned jiang_ling_rate[JIANGLING_CHENGZHANG_L - 1][JIANGLING_CHENGZHANG_L + 1][JIANGLING_CHENGZHANG_L - 2];
	map<unsigned, unsigned> m_mapjiangling_rate1;
	map<unsigned, unsigned> m_mapjiangling_rate2;
	map<unsigned, unsigned> m_mapjiangling_rate3;
	/****************************************/

	/************quest rewar***************/
	CShareMemory m_shActReward;
	map<string, unsigned> m_mapXMLActivityRewad;
	CShareMemory m_shGateReward;
	map<unsigned, unsigned> m_mapXMLOlGate;
	CShareMemory m_shQuestReward;
	map<string,unsigned> m_mapXMLQuest;
	/**************************************/

	CShareMemory m_shHeavenDaoist;
	map<unsigned, unsigned> m_mapXMLHeavenDaoist;

	CShareMemory m_shCostHeavenDaoist;
	map<unsigned, unsigned> m_mapCostHeavenDaoist;

	CShareMemory m_shEightFormation;
	map<unsigned, unsigned> m_mapXMLEightFormation[EIGHT_FORMATION_R_NUM];
	//每个阵型对应的对应的R
	unsigned eight_formation[ID_INDX];

	CShareMemory m_shCostEightFormation;
	map<unsigned, unsigned> m_mapCostEightFormation;

	CShareMemory m_shDouble11;

	vector<EggReward> m_eggrwd;

	CShareMemory m_shBetShop;
	map<unsigned, XMLBetShopItem> m_mapXMLBetShop;

	CShareMemory m_shBarbar;

	CShareMemory m_shFiveTiger;

	//新绝世无双
	CShareMemory m_shNewJueshiWS;
	map<unsigned, unsigned> m_mapJueshiWS;

	//鸿运当头
	CShareMemory  m_shOpporknock;
	map<unsigned, unsigned> m_mapRefresh;

	//幸运连连
	CShareMemory   m_shFortunatelyAgain;
	map<unsigned, EquipIndex> m_mapEquipIndex;

	//充值自选
	CShareMemory  m_shRechargeOptional;
	map<unsigned, unsigned> m_mapOptional;   //映射id与数组下标

	//小兵升级和训练
	CShareMemory  m_shSoldierTrainAndUp;
	map<unsigned, unsigned> m_mapSoldier;   //映射id与数组下标

	//兵书遁甲技能
	CShareMemory  m_shHeavenDaoSkill;
	map<unsigned, unsigned> m_mapHeaven;
	map<unsigned, unsigned> m_mapDAO;

	//天命
	CShareMemory   m_shTurnPlate;
	map<unsigned, EquipIndex> m_mapTurnEquipIndex;

	//时装殿
	CShareMemory   m_shFashionShop;
	map<unsigned, unsigned> m_mapFashionShopIndex;

	//厚惠有期
	CShareMemory   m_shHouHuiYouQi;
	map<unsigned, unsigned> m_mapMinZoneHouHuiYouQi;  //section_index, min_zone
	map<unsigned, unsigned> m_mapMaxZoneHouHuiYouQi;
	map<unsigned, map<unsigned, unsigned> > m_mapChargeHouHuiYouQi;  //section_index, big_table, cash
	map<unsigned, unsigned> m_map4399MinZoneHouHuiYouQi;  //section_index, min_zone
	map<unsigned, unsigned> m_map4399MaxZoneHouHuiYouQi;
	map<unsigned, map<unsigned, unsigned> > m_map4399ChargeHouHuiYouQi;  //section_index, big_table, cash

	//超值折扣
	CShareMemory   m_shChaoZhiZheKou;
	map<unsigned, unsigned> m_mapMinZoneChaoZhiZheKou;  //section_index, min_zone
	map<unsigned, unsigned> m_mapMaxZoneChaoZhiZheKou;
	map<unsigned, map<unsigned, unsigned> > m_mapChargeChaoZhiZheKou;  //section_index, big_table, cash

	//约惠巨献
	CShareMemory   m_shYueHuiJuXian;
	map<unsigned, unsigned> m_mapMinZoneYueHuiJuXian;  //section_index, min_zone
	map<unsigned, unsigned> m_mapMaxZoneYueHuiJuXian;
	map<unsigned, map<unsigned, unsigned> > m_mapChargeYueHuiJuXian;  //section_index, big_table, cash
	map<unsigned, unsigned> m_map4399MinZoneYueHuiJuXian;  //section_index, min_zone
	map<unsigned, unsigned> m_map4399MaxZoneYueHuiJuXian;
	map<unsigned, map<unsigned, unsigned> > m_map4399ChargeYueHuiJuXian;  //section_index, big_table, cash

	//全服限购
	CShareMemory   m_shLimitBuyOfZone;
	map<unsigned, map<unsigned, unsigned> > m_mapMinZoneLimitBuy;  //platform_index, section_index, min_zone
	map<unsigned, map<unsigned, unsigned> > m_mapMaxZoneLimitBuy;
	map<unsigned, map<unsigned, map<unsigned, unsigned> > > m_mapConsumeLimitBuy;  //platform_index, section_index, table, cash

	//五行防御成长
	CShareMemory   m_shFiveDefendGrow;

	//五行灵珠
	CShareMemory   m_shWuxingPearl;

	//国庆盛典
	CShareMemory   m_shCountryDay;

	//心动特卖
	CShareMemory   m_shHeartbeatBigSale;

	//五行商铺
	CShareMemory   m_shFiveShop;

	//觉醒特惠
	CShareMemory   m_shJueXingTeHui;

	//免费兑换
	CShareMemory   m_shFreeExchange;

	//双11
	CShareMemory   m_shDoubleEleven;

	//聚宝匣
	CShareMemory   m_shJuBaoXia;

	//兵书进阶
	CShareMemory   m_shHeavenStep;

	//遁甲进阶
	CShareMemory   m_shDaoistStep;

	//珍宝阁魂石
	CShareMemory   m_shZhenBaoGeHero;

	//珍宝阁宝石
	CShareMemory   m_shZhenBaoGeBuilding;

	//魂石进阶
	CShareMemory   m_shHeroStoneStep;

	//宝石进阶
	CShareMemory   m_shBuildingStoneStep;

	//成长开发
	CShareMemory   m_shGrowDevelop;

	//每日充值
	CShareMemory m_shDailyCharge;

	//百宝箱
	CShareMemory m_shTreasureBox;
	map<unsigned, unsigned> m_treasurebox;

	//信物系统
	CShareMemory m_shKeepsake;

	//充值回馈
	CShareMemory m_shChargeFeedback;

	//欢庆元旦
	CShareMemory m_shCelebrateNewYear;

	//合区活动
	CShareMemory m_shHequActivity;

	//古卷奇书
	CShareMemory m_shAncientScroll;

	//保护旗帜
	CShareMemory m_shProtectFlag;

	//保护女神
	CShareMemory m_shProtectGoddess;
	map<unsigned, unsigned> m_protectgoddess;

	//投石车
	CShareMemory m_shCatapult;
	map<unsigned, unsigned> m_mapXMLCatapult;

	//投石车花费
	CShareMemory m_shCostCatapult;
	map<unsigned, unsigned> m_mapCostCatapult;

	//投石车技能
	CShareMemory  m_shCatapultSkill;
	map<unsigned, unsigned> m_mapCatapultSkill;

	//金秋十月
	map<unsigned, pair<unsigned, pair<pair<unsigned, unsigned>, pair<unsigned, unsigned> > > > m_jinqiushiyue;
	//充值回馈
	map<unsigned, pair<unsigned, pair<pair<unsigned, unsigned>, pair<unsigned, unsigned> > > > m_chongzhihuikui;

	//11月回馈
	map<unsigned, pair<unsigned,pair<unsigned, unsigned> > > m_jinqiunovember;
	//充值送神纹符
	map<unsigned, pair<unsigned,pair<unsigned, unsigned> > > m_acchargebackshenwen;

	//至尊宝箱
	vector<pair<unsigned, pair<unsigned, unsigned> > > m_zhizunbaoxiang_kapai;
	vector<pair<unsigned, unsigned> > m_zhizunbaoxiang_baoxiang;

	map<unsigned, PayOptionalItem> m_payoptionals;

	//新充值自选
	CShareMemory m_shChongZhiZiXuan;

	//美人献礼
	CShareMemory m_shBeauty;

	//充值投资
	CShareMemory m_shInvestment;

	//鹊起相会
	CShareMemory m_shBirdBridge;

	//联盟科技
	CShareMemory m_shUnionTech;

	//圣诞2018
	CShareMemory m_shShengDan;

	//小年2018
	CShareMemory m_shXiaoNian;

	//情人节玫瑰
	CShareMemory m_shQingRenJieMeiGui;

	//年兽BOSS
	CShareMemory m_shNianShouBoss;
private:
	int genUsePool(unsigned opool, set<unsigned> &quforbid, unsigned &upool);
	int addforbidPool(unsigned forbid, set<unsigned> &quforbid);
	int GetHouHuiYouQiSection(unsigned sid, unsigned & section);
	int GetChaoZhiZheKouSection(unsigned sid, unsigned & section);
	int GetYueHuiJuXianSection(unsigned sid, unsigned & section);
	int GetLimitBuyOfZoneSection(const unsigned  & index_platform, unsigned sid, unsigned & section, const unsigned & total_zone_section);

	//解析XML的统一接口
	int ParseXMLInterface(void * pdata, int length, char * filename, CShareMemory& shmomory, ParseComplete pfun);

	//解析百宝箱
	int ParseXMLTreasure(void * data, CMarkupSTL & xmlConf);

	//信物
	int ParseXMLKeepSake(void * data, CMarkupSTL & xmlConf);
	int ParseXMLSakeProduce(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf);
	int ParseXMLSakeUpgrade(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf);
	int ParseXMLSakeBase(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf);
	int ParseXMLSakeOth(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf);
	int ParseXMLXinWuReward(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf);

	//充值回馈
	int ParseXMLChargeFeedback(void * data, CMarkupSTL & xmlConf);

	//欢庆元旦
	int ParseXMLCeleNewYear(void * data, CMarkupSTL & xmlConf);

	//合区活动
	int ParseXMLHeQuActivity(void *data, CMarkupSTL & xmlConf);
	int ParseXMLCharge(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf);
	int ParseXMLVIP(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf);
	int ParseXMLRecompense(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf);

	//古卷奇书
	int ParseXMLAncientScroll(void *data, CMarkupSTL & xmlConf);

	//保护旗帜
	int ParseXMLProtectFlag(void *data, CMarkupSTL & xmlConf);
	//保护女神
	int ParseXMLProtectGoddess(void *data, CMarkupSTL & xmlConf);
	//@end
};

#endif /* DATAXML_H_ */
