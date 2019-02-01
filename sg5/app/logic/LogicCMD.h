/*
 * LogicCMD.h
 *
 *  Created on: 2014-5-6
 *      Author: Ralf
 */

#ifndef LOGICCMD_H_
#define LOGICCMD_H_


#include "LogicInc.h"
#include "LogicCmdBase.h"
#include "LogicCmdUnits.h"

// 绿色刷新
#define REFRESH_GREEN 0
// 蓝色刷新
#define REFRESH_BLUE 1
// 紫色刷新
#define REFRESH_PURPLE 2

#define REFRESH_COST_TIME 1
#define REFRESH_COST_COIN 2
#define REFRESH_COST_CASH 3
#define REFRESH_COST_ITEM 4
#define REFRESH_COST_VIP  5

#define ACC_COST_GREEN 5
#define ACC_COST_BLUE 20
#define ACC_COST_PURPLE 100

#define ZHAO_MU_LING 42015

#define DESS_DIAMOND_MAX 1800

#define SHOP_FLAG 0.8f
#define SHOP_VIP_NUM 27

#define LUCKY_STONE_ID 11112
#define LUCKY_STONE_8_ID 11113
#define LUCKY_STONE_9_ID 11114
#define LUCKY_STONE_10_ID 11115
#define LUCKY_STONE_ALL_LEVEL_ID 11119

//限级强化幸运石eqid
#define QLIMIT_LUCK_STONE_6_ID	11171
#define QLIMIT_LUCK_STONE_7_ID	11172
#define QLIMIT_LUCK_STONE_8_ID	11173
#define QLIMIT_LUCK_STONE_9_ID	11174

#define GET_EN_STONE_ID(level) (4200+level)
#define EN_STONE_ID_1_T 11164
#define EN_STONE_ID_3_T 11123
#define EN_STONE_ID_5_T 11117
#define EN_STONE_ID_6_T 11120
#define EN_STONE_ID_7_T 11121
#define EN_STONE_ID_8_T 11122
#define EN_STONE_ID_9_T 11118
#define EN_STONE_ID_10_T 11165
#define GET_SNAP_SOUL_EQID(level) (level+4900)
#define GET_SNAP_BUILDSTONE_EQID(level) (level+4800)
#define WUXINGZHU_ID 4031

#define ADD_SOUL_COIN 	1
#define ADD_SOUL_P    	500
#define ADD_SOUL_MAX    6000
#define SOUL_LVL		120
#define SOUL_LVL_ADD 	110
#define SOUL_EXP 		40

#define JUEXUE_XIULIAN 20
#define JUEXUE_BAGLIST		20
#define JUEXUE_ADD_SEXP		600
//每1经验所消耗的龙鳞值
#define PER_EXP_DRAGON_SCALE 50

#define SOLDIER_SKILL_CHARACTER_LEVEL 3
#define SOLDIER_SKILL_LEVEL_MAX 10
//士兵技能等级所需的经验和品质的对应关系
const unsigned SOLDIER_SKILL_CHARACTER_EXP[SOLDIER_SKILL_CHARACTER_LEVEL][SOLDIER_SKILL_LEVEL_MAX] = {
	{0,	200, 400, 800,  1600, 3200, 6400,  12800, 25600, 51200},
	{0,	400, 800, 1600, 3200, 6400,	12800, 25600, 51200, 102400},
	{0, 800, 1600, 3200, 6400, 12800, 25600, 51200,	102400,	204800},
};

//士兵技能初始经验与品质的对应关系
const unsigned INITIAL_CHARATER_EXP[SOLDIER_SKILL_CHARACTER_LEVEL] = {60, 120, 240};

#define KINGDOM_WAR_CHARACTER_LEVEL 3
#define KINGDOM_WAR_LEVEL_MAX 10
//争霸石头等级所需的经验和品质的对应关系
const unsigned KINGDOM_WAR_EXP[KINGDOM_WAR_CHARACTER_LEVEL][KINGDOM_WAR_LEVEL_MAX] = {
	{0,	200, 400, 800,  1600, 3200, 6400,  12800, 25600, 51200},
	{0, 520, 1550, 4350, 10000, 15500, 24030, 40840, 67390, 111190},
	{0, 2590,7760,21740,50000,77500,120130,204210,336950, 555970},
};

const unsigned INITIAL_CHARATER_EXP_1[KINGDOM_WAR_CHARACTER_LEVEL] = {0, 10, 50};

#define EXP_STONE_ID 25000 //小兵经验石id
#define EXP_STONE_VALUE   600 //小兵经验石加的经验

#define EXP_STONE_ID_1 7100 //玉石经验石id
#define EXP_STONE_VALUE_1   10 //玉石经验石加的经验


#define JIANGLING_SKILL 50

#define SJ_4399_EXCHANGE 64
#define XSK_4399_EXCHANGE 32

#define XSK_BAIDU_EXCHANGE	16

#define COST_CREDIT_NUM		10
#define COST_CREDIT_NUM_4399 1
#define GET_BALANCE_NUM		1

#define HERO_POWER_2_UP 6050
#define HERO_POWER_3_UP 6051
#define HERO_POWER_2_MAX 130
#define HERO_POWER_2_UP_LIMIT 6052
#define HERO_POWER_2_UP_LIMIT_2 6053
#define HERO_POWER_2_UP_LIMIT_3 6057
#define HERO_POWER_2_UP_LIMIT_4 6056
#define HERO_POWER_2_UP_AWAKEN 6054

//限级祝福
#define BLESS_EQUIP_LIMIT_3 5203
#define BLESS_EQUIP_LIMIT_5 5204
#define BLESS_EQUIP_LIMIT_7 5205

//商店代金券
#define SHOP_PAY_VOUCHER   2040

enum ProductShopType
{
	WorldBattleShop = 0,
	RankBattleShop,
	HufuShop,
	ProductShopTypeNum,
};

#define NAT_CHOUJIANG_FREE_NUM		3
//挖矿
#define NAT_DIGEQUIP_SUBSTONE_FREE_NUM		5
//步步为赢
#define NAT_TREASURE_HUNT_FREE_NUM		5

#define TOMB_NUM		5
#define TOTAL_TOMB_ACT_COUNT		100
#define SKIP_STEP_COST				200

#define GET_DRAG_NUM				5
#define DRAG_LIST_NUM				9

#define TOMB_LOCK					0
#define TOMB_UNLOCK					1

#define TOUCH_TOMB_DEFAULT_ID		0
#define TOUCH_TOMB_SKIP_ID			3
#define TOUCH_TOMB_MAX_ID			4

enum TouchGoldType
{
	TouchReset = 0,
	TouchTurn,
	TouchAKeyTurn,
	TouchSkip,
	TouchTypeNum,
};


#define PROTECT_TOKEN_ID				4082
#define PROTECT_TOKEN_TS				(10 * 60)


#define MAXLV		120
#define HEAVEN_MAXLV 150
#define DAOIST_MAXLV 120
#define MAXEXP_1		1630446571
#define MAXEXP_8		93437736
#define HEAVEN_PREFIX		1000
#define DAOIST_PREFIX		8000
#define MAXEXP_CATAPULT  	93431626
#define EIGHT_FORMATION_MAXLV 100


enum HitEggType
{
	HitEgg_OneType = 0,
	HitEgg_SeriesType = 1,
	HitEgg_RandomType = 2,
	HitEgg_Num,
};


#define HITEGG_REWARD	2
#define HITEGG_OPEN		1			// 可以砸
#define HITEGG_CLOSE	0			// 已砸过
#define HITEGG_COST_NUM		100
#define HITEGG_NUM			9
#define HITEGG_EQNUM		2

#define BETSHOP_VERSION		3

#define GETMEDAL_VERSION		1
#define GETMEDAL_NUM			5

#define NEWWORLD_KILL_VERSION  2
#define NEWWORLD_KILL_NUM	   12

enum RefineType
{
	Refine = 0,
	ShenZhu = 1,
	ShenQi = 2,
	RefineTypeMax
};

enum SynthesisType
{
	Soldier = 0,
	KingdomWar = 1,
	SynthesisTypeMax
};

//提升丹的eqid
#define FEED_TOKEN_DAN	19001

//五行攻击珠
#define FIVE_DEFEND_KINDS 5
#define FIVE_DEFEND_SOUL_DAN 76001
#define FIVE_ATTACK_SYNTHETIC_COUNT 4

//福袋 移后台
#define FUDAI_BAG_KINDS (3)
const unsigned FUDAI_COST[FUDAI_BAG_KINDS] = {1000, 50000, 100000};
const unsigned FUDAI_EQIP[FUDAI_BAG_KINDS] = {50090, 50091, 50092};

const int DESS_RATE[3][5] = {
		{2, 5, 10, 27, 100},
		{5, 10, 20, 40, 100},
		{5, 10, 20, 50, 100}};
const int DESS_STONE[3][5] = {
		{8, 5, 4, 3, 2},
		{7, 5, 4, 3, 2},
		{10, 5, 4, 3, 2}};
const int DESS_COST[3] = {15, 50, 200};
const int DESS_TIME[3] = {40, 50, 20};
const int DESS_STONE_ID[3] = {4011, 4012, 4013};

const unsigned SOUL_LVL_EXP[SOUL_LVL] = {50,110,224,382,585,832,1124,1460,1841,2266,2735,3249,3808,4410,5057,5749,6485,7266,8091,8960,9874,10832,11835,12882,13973,15109,16290,17514,18784,20097,21455,22858,24305,25796,27332,28912,30537,32206,33920,35678,37480,39327,41218,43154,45134,47159,49228,51341,53499,55702,57948,60240,62575,64955,67380,69849,72362,74920,77522,80169,82860,85595,88375,91199,94068,96982,99939,102941,105988,109079,112214,115394,118618,121887,125200,128558,131960,135406,138897,142432,146012,149636,153305,157018,160775,164577,168423,172314,176249,180229,184253,188321,192434,196591,200793,205039,209330,213665,218045,222468,251388,282560,315902,351283,388518,427369,467541,508684,550396,592226,621837,651063,679709,707577,734464,760170,784495,807245,828233,847282};

const int DRAGON_SCALE_RATE[8] = {100, 400, 700, 910, 960, 985, 995, 1000};
const int DRAGON_SCALE_GET[8] = {1000, 1500, 2000, 3000, 5000, 8000, 10000, 15000};
//龙鳞活动额外奖励
const int DRAGON_SCALE_EXTRA_RATE[4] = {20, 50, 80, 100}; //概率对应转盘次数，绝学令，五虎重置令，龙鳞
const int DRAGON_SCALE_EXTRA_ITEM_ID[2] = {4075, 4076};	//4075五虎重置令，4076绝学令
#define   DRAGON_SCALE_EXTRA_AWARD_NUM	3500
//龙鳞活动消耗龙鳞数
#define   DRAGON_SCALE_GET_TIMES	7	//前几次消耗不固定，可配
const int DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES+1] = {0, 2500, 5500, 9500, 15000, 22500, 32500, 45500};
#define   DRAGON_SCALE_COST_INVARIANT 15000 //之后消耗是固定的
//龙鳞活动消耗钻石数
#define   DRAGON_SCALE_DIAMOND_GET_TIMES	8 //前几次消耗不固定，可配
const int DRAGON_SCALE_COST_DIAMOND[DRAGON_SCALE_DIAMOND_GET_TIMES] = {6, 8, 11, 14, 18, 23, 25, 27};
#define   DRAGON_SCALE_COST_DIAMOND_INVARIANT 30 //之后消耗是固定的

#define DRAGON_SCALE_ACTIVITY_SHARE_GIFT_ID		50055

//成长基金
#define LEN_FUND 7
#define TIMES_LIMIT_FUND_BUY 30
#define CASH_ONE_FUND 100
#define COINS_ONE_FUND 0
#define FIRST_BACK_COINS_RATE 0.5
const unsigned LVL_FUND_BACK[LEN_FUND] = {60,65,70,75,80,85,90};
const unsigned COINS_FUND_BACK[LEN_FUND] = {30,40,50,80,100,120,130};
const unsigned CASH_FUND_BACK[LEN_FUND] = {0,0,50,30,20,0,0};

//橙色牌
const int HAPPY_CARD_ORANGE_RATE[3] = {0, 50, 100};
const int HAPPY_CARD_ORANGE_EACH_RATE[3][21] =
{
		{700, 1400, 2200, 3000, 3800, 4600, 5400, 6200, 7000, 7850, 8550, 9275, 10000},
		{600, 1200, 1850, 2500, 3150, 3800, 4500, 5350, 6050, 6750, 7400, 8050, 8700, 9350, 10000},
		{700, 900, 1100, 1300, 1500, 1660, 1820, 1980, 2140, 2300, 3000, 3700, 4400, 5100, 5800, 6500, 7200, 7900, 8600, 9300, 10000}
};
const int HAPPY_CARD_ORANGE_EACH_ID_COUNT[3][21][2] =
{
		{{4474, 3}, {4464, 2}, {4484,2}, {4404,2}, {4424,2}, {4434,2}, {4444,2}, {4454,2}, {50049,1}, {696,1}, {4031,30}, {4405,1}, {40161,1}},
		{{11112,30}, {40161,3}, {4206,15}, {4306,1}, {4336,1}, {4346,1}, {4116,1}, {618,1}, {4326,1}, {4356,1}, {4406,1}, {4486,1}, {4426,1}, {4436,1}, {4456,1}},
		{{628,1}, {4309,1}, {4329,1}, {4359,1}, {50037,1}, {4408,1}, {4428,1}, {4438,1}, {4488,1}, {4458,1}, {672,1}, {673,1}, {674,1}, {675,1}, {676,1}, {677,1}, {678,1}, {679,1}, {683,1}, {684,1}, {685,1}}
};

//白色，绿色，蓝色，紫色牌
const int HAPPY_CARD_RATE[4] = {2800, 5500, 8200, 10000};
const int HAPPY_CARD_EACH_RATE[4][21] =
{
		{625, 1250, 1900, 2550, 3200, 3825, 4450, 5075, 5700, 6325, 6950, 7575, 8200, 8800, 9400, 10000}, //白色
		{625, 1275, 1925, 2575, 3225, 3875, 4525, 5175, 5825, 6450, 7075, 7700, 8325, 8950, 9575, 10000},	//绿色
		{500, 1000, 1550, 2100, 2700, 3300, 3900, 4500, 5100, 5700, 6300, 6900, 7300, 7700, 8100, 8450, 8750, 9050, 9350, 9650, 10000},	//蓝色
		{470, 945, 1420, 1895, 2370, 2845, 3320, 3795, 4270, 4745, 5220, 5695, 6175, 6655, 7135, 7615, 8095, 8575, 9250, 10000}	//紫色
};
const int HAPPY_CARD_EACH_ID_COUNT[4][21][2] =
{
		{{4202,2},{50053,2},{4303,1},{4333,1},{4343,1},{4015,4},{4011,25},{4065,5},{4463,1},{4473,1},{4413,1},{42015,3},{50027,3},{4022,2},{50040,1},{4443,1}},	//白色
		{{4023,2},{4353,2},{4323,2},{42015,5},{4204,2},{42010,2},{50033,1},{11111,1},{11112,1},{4463,2},{4473,2},{4413,2},{4483,2},{4423,2},{4433,2},{4453,2}},	//绿色
		{{4015,14},{42015,7},{4205,3},{50024,2},{4303,3},{4353,3},{4333,3},{4323,3},{4343,3},{4031,6},{42010,3},{50034,1},{4413,3},{4473,3},{4463,3},{4423,3},{4433,3},{4453,3},{4483,3},{4443,3},{50042,1}},	//蓝色
		{{11112,4},{4024,4},{50033,4},{50025,2},{11111,4},{4203,4},{4324,2},{4304,2},{4334,2},{4344,2},{4354,2},{4424,2},{4484,2},{4434,2},{4404,2},{4454,2},{4444,2},{50045,4},{40161,2},{50034,1}}	//紫色
};

//战马每级对应经验
const unsigned HORSE_MAX_EXP[] =
{
	0, 50, 150, 255, 362, 474, 588, 705, 825, 949, 1082, 1223, 1370, 1520, 1673, 1826, 1995, 2178,
	2378, 2597, 2836, 3092, 3351, 3626, 3920, 4238, 4581, 4952, 5353, 5792, 6267, 6781, 7337, 7939,
	8590, 9294, 10057, 10881, 11773, 12739, 13758, 14859, 16048, 17331, 18718, 20215, 21833, 23579,
	25466, 27503, 29676, 32020, 34550, 37279, 40224, 43402, 46831, 50531, 54523, 58830, 63478, 68492,
	73903, 79742, 86041, 92839, 100173, 108087, 116626, 125839, 135780, 146507, 158081, 170570, 183874,
	198216, 213677, 230344, 248311, 267431, 287756, 309337, 332228, 356481, 382148, 409280, 437930, 467709,
	499046, 531983, 566562, 602822, 640800, 680529, 720000, 761040, 804419, 849467, 897037, 947271, 1000318
};

const int HERO_LEARN_HORSE_MAX = 1000318;
const int HERO_LEARN_HORSE_HEXP = 25;
const int HERO_LEARN_HORSE_EQID_1 = 17001;
const int HERO_LEARN_HORSE_EQID_2 = 17002;
const int HERO_LEARN_HORSE_EQ_1 = 4;
const int HERO_LEARN_HORSE_EQ_2 = 1;
const int UPGRADE_HORSE_MAX = 20;
const int DEGREE_HORESE_MAX = 2;
const int UPGRADE_HORSE_EQID = 17003;   //凝魂丹
const int ELEVATE_HORSE_EQID = 17004;  //升阶丹
const int SUPER_UPGRADE_HORSE_EQID = 17005;  //固魂丹

const int UPGRADE_HORSE_EQ[UPGRADE_HORSE_MAX] = {220 ,330 ,400 ,500 ,650 ,900 ,1400 ,2600 ,4650 ,8350, 44, 66, 80, 100, 130, 180, 280, 520, 930, 1670};
const int UPGRADE_2_HORSE_EQ[UPGRADE_HORSE_MAX] = {220 ,330 ,400 ,500 ,650 ,900 ,1400 ,2600 ,4650 ,8350,220 ,330 ,400 ,500 ,650 ,900 ,1400 ,2600 ,4650 ,8350};

const int ELEVATE_HORSE_EQ[DEGREE_HORESE_MAX] = {30,0};

//联盟夺宝 各宝箱概率
const unsigned ALLAINCE_SNATCH_RATE[5] = {25,50,70,85,100};

enum happyCardType
{
	happyCard_White = 0,
	happyCard_Green,
	happyCard_Blue,
	happyCard_Purple,
	happyCard_Orange,

	happyCard_TypeMax
};

enum happyCardActionType
{
	happyCard_BeginGame = 0,
	happyCard_Refresh,
	happyCard_BeginDraw,
	happyCard_Draw,
	happyCard_Collect,
	happyCard_ChargeBack,

	happyCard_ActionTypeMax
};

//烽火点将(21点)
const int POKER_POINT_RATE[9] = {1900, 3800, 5800, 7800, 8800, 9800, 9950, 9999, 10000}; //13点~21点 概率
const int POKER_CARD_NUM_RATE[3][4] =
{
	{3,11,13},//小于15 牌数2,3,4
	{5,14,18,21},//小于20 牌数2,3,4,5
	{5,13,15}//20 或者 21 牌数3,4,5
};
const int POKER_LIST_3_NUM[9] = {8, 9, 10, 10, 10, 10, 9, 8, 7};
const int POKER_LIST_3[9][10][3] =
{
	{{1,2,10},{1,3,9},{1,4,8},{1,5,7},{2,3,8},{2,4,7},{2,5,6},{3,4,6}},//13
	{{1,3,10},{1,4,9},{1,5,8},{1,6,7},{2,3,9},{2,4,8},{2,5,7},{3,4,7},{3,5,6}},//14
	{{1,4,10},{1,5,9},{1,6,8},{2,3,10},{2,4,9},{2,5,8},{2,6,7},{3,4,8},{3,5,7},{4,5,6}},//15
	{{1,5,10},{1,6,9},{1,7,8},{2,4,10},{2,5,9},{2,6,8},{3,4,9},{3,5,8},{3,6,7},{4,5,7}},//16
	{{1,6,10},{1,7,9},{2,5,10},{2,6,9},{2,7,8},{3,4,10},{3,5,9},{3,6,8},{4,5,8},{4,6,7}},//17
	{{1,7,10},{1,8,9},{2,6,10},{2,7,9},{3,5,10},{3,6,9},{3,7,8},{4,5,9},{4,6,8},{5,6,7}},//18
	{{1,8,10},{2,7,10},{2,8,9},{3,6,10},{3,7,9},{4,5,10},{4,6,9},{4,7,8},{5,6,8}},//19
	{{1,9,10},{2,8,10},{3,7,10},{3,8,9},{4,6,10},{4,7,9},{5,6,9},{5,7,8}},//20
	{{2,9,10},{3,8,10},{4,7,10},{4,8,9},{5,6,10},{5,7,9},{6,7,8}}//21
};
const int POKER_LIST_4_NUM[9] = {3, 5, 6, 7, 7, 8, 8, 8, 8};
const int POKER_LIST_4[9][8][4] ={
    {{1,2,3,7},{1,2,4,6},{1,3,4,5}},//13
    {{1,2,3,8},{1,2,4,7},{1,2,5,6},{1,3,4,6},{2,3,4,5}},//14
    {{1,2,3,9},{1,2,4,8},{1,2,5,7},{1,3,5,6},{1,3,4,7},{2,3,4,6}},//15
    {{1,2,4,9},{1,2,5,8},{1,3,4,8},{1,3,5,7},{1,4,5,6},{2,3,5,6},{2,3,4,7}},//16
    {{1,2,4,10},{1,2,5,9},{1,3,4,9},{1,3,5,8},{1,4,5,7},{2,3,5,7},{2,3,4,8}},//17
    {{1,2,5,10},{1,3,5,9},{1,3,4,10},{1,3,5,10},{1,4,6,7},{2,3,6,7},{2,3,5,8},{3,4,5,6}},//18
    {{1,2,6,10},{1,3,6,9},{1,3,5,10},{1,4,5,10},{1,4,6,8},{2,3,6,8},{2,3,5,9},{3,4,5,7}},//19
    {{1,2,7,10},{1,3,7,9},{1,3,6,10},{2,3,5,10},{1,4,7,8},{2,4,6,8},{2,4,5,9},{3,4,5,8}},//20
    {{1,2,8,10},{1,3,8,9},{1,3,7,10},{1,4,6,10},{1,4,7,9},{2,4,6,9},{2,4,5,10},{3,4,5,9}},//21
};
const int POKER_LIST_5_NUM[7] = {1, 1, 2, 2, 5, 6, 7};
const int POKER_LIST_5[7][7][5] =
{
	{{1,2,3,4,5}},//15
	{{1,2,3,4,6}},//16
	{{1,2,3,4,7}, {1,2,3,5,6}},//17
	{{1,2,3,4,8}, {1,2,3,5,7}},//18
	{{1,2,3,4,9}, {1,2,3,5,8},{1,2,3,6,7},{1,2,4,5,7},{1,3,4,5,6}},//19
	{{1,2,3,4,10}, {1,2,3,5,9},{1,2,3,6,8},{1,2,4,5,8},{1,3,4,5,7},{2,3,4,5,6}},//20
	{{1,2,3,5,10}, {1,2,4,5,9},{1,2,4,6,8},{1,2,3,7,8},{1,3,4,5,8},{1,3,4,6,7},{2,3,4,5,7}}//21
};
const int POKER_LIST_6[6] ={1,2,3,4,5,6};
const int POKER_REWARD_NUM[11] = {6,6,6,6,6,6,11,11,3,6,1};
const int POKER_REWARD[11][11][2] =
{
		{{4423,2},{4463,2},{4433,2},{4443,2},{4204,4},{50014,1}},//13
		{{4483,2},{4473,2},{4453,2},{4403,2},{50033,2},{50014,1}},//14
		{{4484,1},{4474,1},{4454,1},{4404,1},{50034,3},{50014,2}},//15
		{{4424,1},{4464,1},{4434,1},{4444,1},{50033,4},{50014,2}},//16
		{{4424,2},{4464,2},{4434,2},{4444,2},{4205,6},{50015,1}},//17
		{{4484,2},{4474,2},{4454,2},{4404,2},{50033,7},{50015,1}},//18
		{{4425,1},{4465,1},{4435,1},{4445,1},{4485,1},{4475,1},{4455,1},{4405,1},{50015,2},{4206,6},{50033,13}},//19
		{{4425,2},{4465,2},{4435,2},{4445,2},{4485,2},{4475,2},{4455,2},{4405,2},{50016,1},{4207,5},{623,2}},//20
		{{50008,1},{50036,1},{50037,1}},//21
		{{4423,2},{4463,2},{4433,2},{4443,2},{4204,4},{50014,1}},//21<
		{{50044,1}} //21点 1,2,3,4,5,6
};
enum pokerType
{
	poker_BeginGame = 0,
	poker_Draw,
	poker_GetReward,

	pokerTypeMax
};

const unsigned HERO_POWER_2_UP_COST[HERO_POWER_2_MAX][3] = {
		{500,0,0},
		{1,26,55},
		{1,27,61},
		{1,28,67},
		{1,29,73},
		{1,31,81},
		{1,32,89},
		{1,34,98},
		{1,35,108},
		{1,37,119},
		{2,39,131},
		{2,41,144},
		{2,42,159},
		{2,44,175},
		{2,46,193},
		{2,49,212},
		{2,51,233},
		{2,53,256},
		{2,56,282},
		{2,58,310},
		{2,61,341},
		{2,64,376},
		{2,67,414},
		{2,70,455},
		{2,73,501},
		{2,76,551},
		{2,80,606},
		{2,84,666},
		{2,88,733},
		{2,92,806},
		{6,96,886},
		{6,100,975},
		{6,105,1073},
		{7,110,1180},
		{7,115,1298},
		{7,120,1428},
		{8,126,1571},
		{8,132,1728},
		{9,138,1900},
		{9,144,2091},
		{9,151,2300},
		{9,158,2530},
		{9,165,2783},
		{9,172,3062},
		{9,180,3368},
		{9,189,3705},
		{9,197,4076},
		{9,206,4484},
		{9,216,4932},
		{9,226,5426},
		{10,236,5969},
		{10,247,6566},
		{10,259,7222},
		{11,271,7944},
		{11,283,8739},
		{11,296,9613},
		{11,310,10574},
		{12,324,11632},
		{12,339,12795},
		{12,355,14075},
		{13,371,15482},
		{14,388,17031},
		{15,406,18734},
		{16,425,20608},
		{17,444,22668},
		{17,465,24936},
		{19,486,27429},
		{20,508,30172},
		{21,532,33190},
		{22,556,36509},
		{26,582,40159},
		{26,609,44175},
		{26,637,48593},
		{26,666,53453},
		{26,697,58798},
		{26,729,64678},
		{26,762,71146},
		{26,797,78260},
		{27,834,86086},
		{27,872,94695},
		{27,913,104164},
		{27,955,114580},
		{27,998,126038},
		{27,1044,138642},
		{27,1092,152507},
		{27,1143,167758},
		{27,1195,184534},
		{27,1250,202987},
		{27,1308,223285},
		{27,1368,245614},
		{32,1431,270176},
		{32,1497,297193},
		{32,1566,326912},
		{32,1638,359603},
		{32,1713,395564},
		{32,1792,435121},
		{32,1900,478633},
		{32,2014,526496},
		{33,2134,579145},
		{33,2262,637060},
		{33, 2285, 638335},
		{33, 2308, 639611},
		{33, 2331, 641530},
		{33, 2354, 643455},
		{33, 2378, 646029},
		{33, 2402, 648613},
		{33, 2426, 651207},
		{33, 2450, 653812},
		{33, 2474, 657081},
		{33, 2499, 660366},
		{34, 2524, 673574},
		{34, 2549, 687045},
		{35, 2575, 700786},
		{35, 2601, 714802},
		{36, 2627, 729098},
		{36, 2653, 743680},
		{36, 2679, 758553},
		{36, 2706, 773724},
		{37, 2733, 789199},
		{37, 2761, 804983},
		{37, 2788, 813033},
		{37, 2816, 821163},
		{38, 2844, 829375},
		{38, 2873, 837668},
		{38, 2901, 846045},
		{38, 2930, 854505},
		{38, 2960, 863050},
		{39, 2989, 871681},
		{39, 3019, 880398},
		{39, 3049, 889202}
};
const unsigned HERO_POWER_3_UP_MAX[13] = {0,0,5,10,15,20,30,40,50,50,50,50,50};


//倍数转盘
enum MultipleWheelType
{
	MultipleWheelType_One = 0,
	MultipleWheelType_Ten,

	MultipleWheelType_Max
};
#define MULTIPLE_WHEEL_REWARD_NUM 8
#define MULTIPLE_WHEEL_MULTIPLE_NUM 8
const unsigned MULTIPLE_WHEEL_REWARD_ID[MULTIPLE_WHEEL_REWARD_NUM] = {713, 6050, 50045, 11112, 5200, 51005, 714, 4011};
const unsigned MULTIPLE_WHEEL_REWARD_COUNT[MULTIPLE_WHEEL_REWARD_NUM] = {2,5,1,1,2,2,1,7};
const unsigned MULTIPLE_WHEEL_REWARD_RATE[MULTIPLE_WHEEL_REWARD_NUM] = {15, 26, 37, 49, 60, 66, 77, 100};

const unsigned MULTIPLE_WHEEL_MULTIPLE[MULTIPLE_WHEEL_MULTIPLE_NUM] = {3,5,10,15,20,25,30,40};
const unsigned MULTIPLE_WHEEL_MULTIPLE_RATE[MULTIPLE_WHEEL_MULTIPLE_NUM] = {280, 570, 860, 920, 960, 990, 997, 1000};

#define CHANGE_NAME_CARD_ID  1910

//Activity of MixHero
const unsigned WJ_SHENGXING_STAR[CONFIG_WUJIANGSHEGNXING_ITEM] = {2,2,2,2,2, 3,4,4,4,4, 4,4,4,4,4, 5,5,5,5,5, 7,7,7,7,7};
const unsigned WJ_SHENGXING_CH[CONFIG_WUJIANGSHEGNXING_ITEM] = {1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5};

//Activity of dedaozhenren
#define DEDAOZHENREN_PERSON_NUM 4
#define DEDAOZHENREN_PRODUCT_NUM_KINDS 4
#define DEDAOZHENREN_HUIFU_TIMES 100
#define DEDAOZHENREN_VISIT_CASH 600
#define ZHUHUNFU_ID 1909
const unsigned DEDAOZHENREN_UNLOCK_RATE[DEDAOZHENREN_PERSON_NUM] = {30,20,10,0};
const unsigned DEDAOZHENREN_HUIFU_CASH[DEDAOZHENREN_PERSON_NUM]  = {15,25,35,55};
const unsigned DEDAOZHENREN_HUIFU_RATE[DEDAOZHENREN_PERSON_NUM][DEDAOZHENREN_PRODUCT_NUM_KINDS]        = {{83,94,98,100},{76,92,97,100},{61,83,95,100},{44,71,91,100}};
const unsigned DEDAOZHENREN_HUIFU_PRODUCT_NUM[DEDAOZHENREN_PERSON_NUM][DEDAOZHENREN_PRODUCT_NUM_KINDS] = {{1,2,3,4},{2,6,8,8},{4,6,9,12},{6,10,14,20}};

//qq面板
#define QQPANEL_ADD_EQUIP_KINDS 5
const unsigned QQPANEL_ADD_EQUIP_ID[QQPANEL_ADD_EQUIP_KINDS] = {40121,4015,4201,4002,42015};
const unsigned QQPANEL_ADD_EQUIP_COUNT[QQPANEL_ADD_EQUIP_KINDS] = {5,5,10,5,5};

//黄钻新手礼包
#define YELLOW_DIAMOND_NEWUSER_EQUIP_KINDS 3
const unsigned YELLOW_DIAMOND_NEWUSER_ADD_EQUIP_ID[YELLOW_DIAMOND_NEWUSER_EQUIP_KINDS] = {4201,4004,4001};
const unsigned YELLOW_DIAMOND_NEWUSER_ADD_EQUIP_COUNT[YELLOW_DIAMOND_NEWUSER_EQUIP_KINDS] = {1,1,1};

//蓝钻新手礼包
#define BLUE_DIAMOND_NEWUSER_EQUIP_KINDS 3
#ifdef SG_16_VER
const unsigned BLUE_DIAMOND_NEWUSER_ADD_EQUIP_ID[BLUE_DIAMOND_NEWUSER_EQUIP_KINDS] = {11112,4402,4301};
#else
const unsigned BLUE_DIAMOND_NEWUSER_ADD_EQUIP_ID[BLUE_DIAMOND_NEWUSER_EQUIP_KINDS] = {11112,4403,4302};
#endif
const unsigned BLUE_DIAMOND_NEWUSER_ADD_EQUIP_COUNT[BLUE_DIAMOND_NEWUSER_EQUIP_KINDS] = {3,3,3};

//蓝钻每日礼包
#define BLUE_DIAMOND_DAILY_GIFT_LEVEL 7
const unsigned BLUE_DIAMOND_DAILY_4015_GIFT_COUNT[BLUE_DIAMOND_DAILY_GIFT_LEVEL] = {1,1,1,2,2,2,3};
const unsigned BLUE_DIAMOND_DAILY_50040_GIFT_COUNT[BLUE_DIAMOND_DAILY_GIFT_LEVEL] = {1,1,1,2,2,2,2};

//蓝钻等级礼包
#define BLUE_DIAMOND_LEVEL_GIFT_LEVEL 10
const unsigned BLUE_DIAMOND_LEVEL_GIFT_ADD_EQUIP_ID[BLUE_DIAMOND_LEVEL_GIFT_LEVEL] = {42015,42015,42015,4201,4201,11112,11112,11112,4402,4302};
const unsigned BLUE_DIAMOND_LEVEL_GIFT_ADD_EQUIP_COUNT[BLUE_DIAMOND_LEVEL_GIFT_LEVEL] = {5,10,20,20,25,10,15,20,10,5};

//品质与等级关联的经验
#define CHARACTER_LEVEL 5
#define TOKEN_LEVEL_MAX 10

//令牌等级所需的经验和品质的对应关系
const unsigned TOKEN_CHARACTER_EXP[CHARACTER_LEVEL][TOKEN_LEVEL_MAX + 1] = {
		{0, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600},
		{0, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200},
		{0, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400},
		{0, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400, 204800},
		{0, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400, 204800, 409600}
};

//令牌额外经验与品质的对应关系
const unsigned EXTRA_CHARATER_EXP[CHARACTER_LEVEL] = {15, 30, 60, 120, 240};


///////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef int (BaseCmdUnit::*ActionImpl)(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
/**
 * @uid 用户ID
 * @baseUser --ture： CLogicUser::GetUserLimit 接口; false:  CLogicUser::GetUser 接口
 * @parms 接口需要的参数
 * @result 结果返回
 */
template<class T>
int LogicCmdAction(unsigned uid, bool baseUser, const BaseCmdParams& params, ActionImpl impl, Json::Value& result)
{
	try
	{
		//To lock user
		AUTO_LOCK_USER(uid)
		UserWrap user(uid, baseUser);
		int ret = user.CheckSession(params.LastTime(), params.SeqId(), result);
		if (ret != R_SUCCESS)
		{
			error_log("ret: %d", ret);
			return ret;
		}

		T unit(user);
		ret = (&unit->*impl)(user, params, result);
		if (ret != R_SUCCESS)
		{
			error_log("ret: %d", ret);
			return ret;
		}

		user.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}


class CLogicCMD
{
public:
	int UpgradeBuilding(unsigned uid, unsigned id, bool tv, string bq, unsigned fcm, Json::Value &result, unsigned lasttime,unsigned seqid);
	int FastUpgradeBuilding(unsigned uid, unsigned id, unsigned type, unsigned ud, unsigned count, string bq, unsigned help, Json::Value &result, unsigned lasttime,unsigned seqid);
	int GMUpgradeBuilding(unsigned uid, Json::Value& data, Json::Value &result, unsigned lasttime,unsigned seqid);
	int GMAddExp(unsigned uid, Json::Value &result, unsigned lasttime,unsigned seqid);
	int ExpMaxAdd(unsigned uid, unsigned type, Json::Value &result, unsigned lasttime,unsigned seqid);
	int RefreshHero(unsigned uid, unsigned refreshType, unsigned sourceType, Json::Value &result, unsigned zmlud,unsigned &lasttime,unsigned &seqid);
	int UpgradeHero(unsigned uid, int target, int source[XML_HERO_SOURCE], Json::Value &result,unsigned &lasttime,unsigned &seqid);
	int UpgradeHeroForActivity(unsigned uid, int target, int source[XML_HERO_SOURCE], Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetUpgradeHeroForActivity(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ChargeBackHappyCard(unsigned uid, Json::Value &result,unsigned &lasttime,unsigned &seqid);
	int ChangeEquipSub(unsigned uid, unsigned equip, unsigned lvl, unsigned stone, unsigned type, unsigned spirit, unsigned free, Json::Value &keep, Json::Value &result,unsigned lasttime,unsigned seqid);
	int EquipSubAct1(unsigned uid, unsigned equip, string& osub, string& nsub, unsigned lvl, Json::Value &result,unsigned lasttime,unsigned seqid);
	int EquipSubAct2(unsigned uid, unsigned equip, unsigned all, unsigned lvl, Json::Value &result,unsigned lasttime,unsigned seqid);
	int TreasureHunt(unsigned uid, unsigned type, unsigned times, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int DigEquipSubStone(unsigned uid, unsigned type, unsigned equd, Json::Value &result,unsigned &lasttime,unsigned &seqid);

	int useGiftBag(unsigned uid, unsigned ud, unsigned count, Json::Value &result, unsigned seqid, unsigned lasttime);	//使用礼包
	int Payrank_activity(unsigned uid, unsigned lottery_number ,unsigned point, Json::Value &result, unsigned lasttime, unsigned seqid); //消费积分抽奖活动
	int BuyBet(unsigned uid,unsigned bet, Json::Value &result, unsigned lasttime, unsigned seqid);  //商店金币购买彩花
	int GetEquipIntensifys(unsigned uid, const Json::Value data, Json::Value &result, unsigned lasttime, unsigned seqid);  //装备强化
	int QianghuaDismantlingEquip(unsigned uid, unsigned equip_level, unsigned equip_ud, unsigned q_level, Json::Value &result, unsigned lasttime, unsigned seqid);  //装备强化拆解
	int TaozhuangDismantlingEquip(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid); //装备套装拆解
	int SyntheticGem(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid); //宝石合成
	int MeltOldSoulStone(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid); //新宝石
	int SynNewSoulStone(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid); //新宝石
	int SynNewSoulStoneUp(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid); //新宝石
	int DivinePower(unsigned uid,  Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);  //天将神力
	int StarStone(unsigned uid,  Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);  //星石
	int EveryDayRecharge(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);  //国庆活动--每日累充
	int EveryDayOnline(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);  //国庆活动--每日在线
	int EnjoyStore(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);  //国庆活动--畅享商店
	int VipReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);  //国庆活动--vip奖励

	int UpgradeGem(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid); //升级宝石
	int UpgradeTenWeapon(unsigned uid, unsigned id, unsigned equd, unsigned times, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid); //升级十大神兵

	int BuildEquipSet(unsigned uid, unsigned part, unsigned occupation, Json::Value &result, unsigned lasttime, unsigned seqid); //打造套装
	int UpgradeEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid); //升级套装
	int RefineEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned kind = 0); //套装精炼
	int WuxingEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid); //套装洗五行
	int BlessEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &param, Json::Value &result, unsigned lasttime, unsigned seqid); //套装祝福
	int ShenWenEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid); //套装神纹
	int ShenGeEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid); //神器神格

	int Shop(unsigned uid, unsigned id, unsigned count, unsigned flag, unsigned type, unsigned vip, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int ProductShop(unsigned uid, unsigned type, unsigned costUd, unsigned id, Json::Value &result, unsigned &lasttime,unsigned &seqid); //以物易物的商店
	int FashionShop(unsigned uid, unsigned id, unsigned count, bool is_cash, Json::Value &result, unsigned &lasttime,unsigned &seqid);   //时装商店

	int HammerHit(unsigned uid, unsigned equd, int hitCount, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int HammerHitAllServer(unsigned uid, unsigned equd, int hitCount, Json::Value &result, unsigned &lasttime,unsigned &seqid);

	int UseShip(unsigned uid, unsigned torch, unsigned classType, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int RefreshShip(unsigned uid, unsigned refreshType, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid);

	int HeroPowerUp(unsigned uid, unsigned heroud, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int HeroPower2Up(unsigned uid, unsigned heroud, unsigned equd, unsigned specialud, unsigned equd1, unsigned equd2, unsigned equd3, unsigned equd4, unsigned type, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int HeroPower3Up(unsigned uid, unsigned heroud, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int liandan(unsigned uid, const Json::Value &data, Json::Value &result, unsigned lasttime,unsigned seqid);
	int keyao(unsigned uid, unsigned eqid, unsigned equd, unsigned heroud, Json::Value &result, unsigned lasttime,unsigned seqid);

	int godh(unsigned uid, unsigned equd, unsigned index1, unsigned index2, Json::Value &result, unsigned lasttime,unsigned seqid);

	int HeroLearnHorse(unsigned uid, unsigned heroud, unsigned equd1, unsigned equd2, Json::Value &result, unsigned lasttime,unsigned seqid, unsigned once);
	//升级
	int UpgradeHorse(unsigned uid, unsigned horseud, unsigned equd, unsigned equd_2, Json::Value &result, unsigned lasttime,unsigned seqid);
	//升阶
	int ElevateHorse(unsigned uid, unsigned horseud, unsigned equd, Json::Value &result, unsigned lasttime,unsigned seqid);

	int AddSoul(unsigned uid, bool isCash, unsigned type, Json::Value &result, unsigned &lasttime,unsigned &seqid);

	int NewLotteryActivity(unsigned uid, unsigned level, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid); //羊年转盘抽奖
	int GetNewLotteryData(unsigned uid, Json::Value &result);
	static CDataNewlottery* GetNewLotteryData();

	int JueXueOneKeyFullLevel(unsigned uid, Json::Value &result, unsigned &lasttime,unsigned &seqid);


	int Juexue(unsigned uid, bool all, Json::Value &result, unsigned &lasttime,unsigned &seqid);
	int SellJuexue(unsigned uid, unsigned type, unsigned isell, Json::Value &result, unsigned lasttime, unsigned seqid);
	int CollectJuexue(unsigned uid, unsigned type, unsigned icoll, Json::Value &result, unsigned lasttime, unsigned seqid);
	int SynthJuexue(unsigned uid, unsigned type, unsigned icomb, unsigned iby, Json::Value &result, unsigned lasttime, unsigned seqid);
	int LoadJuexue(unsigned uid, unsigned type, unsigned heroud, unsigned ihero, unsigned ibag, Json::Value &result, unsigned lasttime, unsigned seqid);
	int LoadSynth(unsigned uid, unsigned type, unsigned index, unsigned heroud, Json::Value &result, unsigned lasttime, unsigned seqid);

	int QixiChoujiangActivity(unsigned uid, unsigned count, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid); //幸运大转盘

	int GetJianglingGrow(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid); //将灵成长
	int GetJianglingSkillsDraw(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid); //将灵技能

	int DragonScaleActivity(unsigned uid, unsigned type, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	//十次龙鳞转盘
	int DragonScaleTensActivity(unsigned uid, unsigned type, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	int DragonScaleAllFree(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);

	int GetDragonScaleData(unsigned uid, Json::Value &result);
	static CDataDragonScaleGiftBag* GetDragonScaleData();

	int HappyCard(unsigned uid, unsigned type, const Json::Value &iData, Json::Value &result, unsigned lasttime, unsigned seqid);//欢乐卡牌
	int Poker21(unsigned uid, unsigned type, const vector<unsigned> &iData, unsigned lasttime, unsigned seqid, Json::Value &result); //烽火点将（21点）
	int R5(unsigned uid, unsigned count, Json::Value &reslut, unsigned lasttime, unsigned seqid);
	int MultipleWheel(unsigned uid, unsigned type, unsigned lasttime, unsigned seqid, Json::Value &result);
	int HitEgg(unsigned uid, unsigned type, unsigned index, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	int RefreshHitEgg(unsigned uid, unsigned lock, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	int BetShop(unsigned uid, unsigned index, unsigned eqid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetMedal(unsigned uid, unsigned type, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetWorldReward(unsigned uid, unsigned index, unsigned eqid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetKillReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int BuyQiRi(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid); //购买七日基金
	int GetQiRi(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid); //获取七日基金
	int GetGiftBagLvl(unsigned uid, unsigned id, Json::Value &result, unsigned lasttime, unsigned seqid); //获取等级礼包
	int GetGiftBagVip(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid); //获取Vip礼包
	int FirstRechargeReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid); //首充奖励
	int GrowthFund(unsigned uid, bool is_buy, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid); //成长基金
	int DeDaoZhenRenVisit(unsigned uid, Json::Value &result, unsigned seqid, unsigned lasttime); //得道真人拜访
	int DeDaoZhenRenDrawPicture(unsigned uid, unsigned person, unsigned equd, Json::Value &result, unsigned seqid, unsigned lasttime); //得道真人绘符

	int HeroFm(unsigned uid,unsigned index,unsigned index1,unsigned hud,unsigned eq_ud,Json::Value &result,unsigned &lasttime,unsigned &seqid);

	//领取签到奖励
	int SignInReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ProvideSignInReward(unsigned uid, int dayLevel, DataUser& dataUser, Json::Value &result); //发放登录奖励

    //领取邀请奖励
    int GetInviteReward(unsigned uid, unsigned rewardid, Json::Value &result, unsigned lasttime, unsigned seqid);
    int VerifyInviteRewardOfLevelCondition(unsigned uid, const XMLInviteLevelGiftItem& item);
    int ProvideInviteLevelReward(unsigned uid, const XMLInviteLevelGiftItem& item, Json::Value &result);
    int ProvideInviteDayReward(unsigned uid, Json::Value &result);

    //领取每日任务奖励
    int DailyQuestReward(unsigned uid, unsigned index, bool type, bool blue_torch_burning, Json::Value& result, unsigned lasttime, unsigned seqid);
    int ProvideDailyQuestReward(unsigned uid, unsigned index, bool blue_torch_burning, DataUser& dataUser, const Json::Value& dailyQuest, Json::Value &result);

    //领取VIP礼包
    int VipGiftBag(unsigned uid, unsigned vipLevel, Json::Value& result, unsigned lasttime, unsigned seqid);
    int ProvideVipGiftBag(unsigned uid, unsigned vipLevel, DataUser& dataUser, Json::Value& result);

    //VIP界面的充值礼包
    int RechargeGiftBag(unsigned uid, unsigned id, Json::Value& result, unsigned lasttime, unsigned seqid);
    int ProvideRechargeGiftBag(unsigned uid, unsigned id, Json::Value& result);

    //腾讯电脑管家
    int LoginGiftOfTencentPCManager(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    int InstallGiftOfTencentPCManager(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);

    //qq面板 后端移植
    int QQPanelGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    //黄钻礼包 后端移植
    int YellowDiamondNewUserGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    int YellowDiamondDailyGiftBag(unsigned uid, unsigned yellow_level, bool is_year, Json::Value& result, unsigned lasttime, unsigned seqid);
    //蓝钻礼包 后端移植
    int BlueDiamondNewUserGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    int BlueDiamondDailyGiftBagOneKeyBackAll(unsigned uid, unsigned blue_level, bool is_year, bool is_luxury, Json::Value& result, unsigned lasttime, unsigned seqid);
    int BlueDiamondDailyGiftBagSingle(unsigned uid, unsigned blue_level, bool is_year, bool is_luxury, unsigned kinds_blue_gift, Json::Value& result, unsigned lasttime, unsigned seqid);
    int BlueDiamondLevelGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    //强化武器
    //使用器魂
    int IntensifyWeaponBySoul(unsigned uid, unsigned index, Json::Value& result, unsigned lasttime, unsigned seqid);
    //使用钻石
    int IntensifyWeaponBySoul(unsigned uid, unsigned index, unsigned equipUId1, unsigned equipUId2, unsigned equipUd3, unsigned equipUd4, Json::Value& result, unsigned lasttime, unsigned seqid);
    int GetPartStone(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid);
    //获取武将馆等级
    int GetGeneralBuildingLevel(unsigned uid, unsigned& level);
    //计算消耗
    int CalcWeaponBySoulCost(unsigned uid, unsigned level, int& cost);

    //招募武将
    int RecruitHero(unsigned uid, string heroid, Json::Value& result, unsigned zmlud, int index, unsigned lasttime, unsigned seqid);

    //暑假前奏 @start
    int PreSummerExchange(unsigned uid, unsigned id, unsigned type, Json::Value& result, unsigned lasttime, unsigned seqid);
    int PreSummerCurPoint(unsigned uid, unsigned type, Json::Value& result, unsigned lasttime, unsigned seqid);
    //@end

    //新绝世无双
    int GetNewJueshiWushuang(unsigned uid, unsigned id, Json::Value& result, unsigned lasttime, unsigned seqid);

    //令牌吞噬
    int FeedToken(unsigned uid, unsigned equd, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid);
    int VerifyCondition(unsigned uid, Json::Value & self, Json::Value & others);

    //尊主榜膜拜
    int LordWorship(unsigned uid, int id, int type, Json::Value &result, unsigned lasttime, unsigned seqid);

    //每日团购
    int GroupBuyDailyBuy(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
    int GroupBuyDailyReward(unsigned uid, int index, Json::Value &result, unsigned lasttime, unsigned seqid);
    //@end

    //开区礼包
    int NewRecharge(unsigned uid, int id, Json::Value &result, unsigned lasttime, unsigned seqid);

    //充点小钱
    int LittleRecharge(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);

    //鸿运当头,转转盘
    int GetOpportunityKnockReward(unsigned uid, unsigned times, unsigned equd, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid);
    int ProvideReward(unsigned uid, unsigned excludeNum, unsigned equd, Json::Value & data, Json::Value & newact, Json::Value & result, Json::Value & user_flag, bool isPointPay);
    int RefreshNewItems(unsigned uid, unsigned oldindex, Json::Value &newact);
    int TurnLuckTable(int * prates, int len, int & target);  //从概率数组中，按照概率,随机抽取结果

    //充值自选
    int GetRechargeOptionalReward(unsigned uid, unsigned rewardcnt,Json::Value &data, Json::Value & result, unsigned lasttime, unsigned seqid);

	/*----------------消费自选-begin------------------*/
    int CheckPayOptionVersion(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
	int GetPayOptionalReward(unsigned uid, unsigned rewardcnt,Json::Value &data, Json::Value & result, unsigned lasttime, unsigned seqid);
	/*----------------消费自选-end------------------*/

    //充值送星级
    int UpgradeHeroForRecharge(unsigned uid, unsigned index, unsigned heroud, Json::Value & result, unsigned lasttime, unsigned seqid);

    //武将训练
    int StartHeroTrain(unsigned uid, unsigned index, unsigned heroud, unsigned blv, Json::Value & result, unsigned lasttime, unsigned seqid);
    int ImroveHeroTrainExp(unsigned uid, unsigned equd, unsigned tindex, Json::Value & result, unsigned lasttime, unsigned seqid);
    int EndHeroTrain(unsigned uid, unsigned type, unsigned tindex, Json::Value & result, unsigned lasttime, unsigned seqid);

    //小兵训练
    int StartSoldierTrain(unsigned uid, string sid, int count, unsigned type, unsigned costtype, Json::Value & result, unsigned lasttime, unsigned seqid);
    int EndSoldierTrain(unsigned uid, unsigned type, unsigned bindex, Json::Value & result, unsigned lasttime, unsigned seqid);

    //小兵研究
    int StartSoldierResearch(unsigned uid, string sid, unsigned rlevel, unsigned type, unsigned costtype, Json::Value & result, unsigned lasttime, unsigned seqid);
    int CancelSoldierResearch(unsigned uid, string sid, Json::Value & result, unsigned lasttime, unsigned seqid);
    int EndSoldierResearch(unsigned uid, string sid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);
    int SynthSoldierSkill(unsigned uid, unsigned equd, unsigned type, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid, int kind = Soldier, unsigned expud = 0, unsigned expcount = 0);

    //技能
    int UpgradeInnateSkill(unsigned uid, unsigned heroud, Json::Value & result, unsigned lasttime, unsigned seqid);
    int StartSkillTrain(unsigned uid, unsigned heroud, string skid, Json::Value equds, unsigned sectime, unsigned costpro, Json::Value & result, unsigned lasttime, unsigned seqid);
    int EndSkillTrain(unsigned uid, unsigned sindex, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);
    int UpgradeHevenDaoSkill(unsigned uid, unsigned index, unsigned type, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid);
    int UpgradeCatapultSkill(unsigned uid, unsigned index, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid);
    int CommderSkilLearn(unsigned uid, unsigned heroud,unsigned equd,  Json::Value & result, unsigned lasttime, unsigned seqid);
    int PotianSkilLearn(unsigned uid, unsigned heroud,string skid,Json::Value &m_data, Json::Value & result, unsigned lasttime, unsigned seqid);

    //福禄金袋
    int CalcuteFairyBag(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
    int GetFairyBagReward(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);

    //每日充值
    int GetDailyChargeCoinReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);

	/*----------------充值回馈begin------------------*/
    //兵书
    int GetChargeFeedbackHeavenReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);
    //遁甲
    int GetChargeFeedbackDaoistReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);
	/*----------------充值回馈遁end------------------*/

    //兵书
    int GetCelebrateNewYearReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);

	//百宝箱
    //检验版本号
    int CheckTreasureVersion(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	//刷新百宝箱
	int RefreshTreasureBox(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	//抽奖
	int LotteryTreasureBoxReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	//十次抽奖
	int LotteryMultiTreasureBoxReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);

	/*----------------信物系统begin------------------*/
	//单个产出
	int OnceKeepsakeProduce(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	//一键产出
	int OneKeyKeepsakeProduce(unsigned uid, unsigned equd, unsigned times, Json::Value &result, unsigned lasttime, unsigned seqid);
	//召唤
	int SummonNPC(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	//一键卖出
	int OneKeySoldDefective(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	//吞噬
	int FeedKeepsake(unsigned uid, unsigned equd, unsigned convertud, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid);
	//信物一键满级
	int KeepsakeOneKeyFullLevel(unsigned uid, unsigned ud_hero_post, unsigned ud_keepsake, Json::Value &result, unsigned lasttime, unsigned seqid);
	/*----------------信物系统end------------------*/

	//装备强化活动
	int CheckEquipStrengthenVersion(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetStrengthenChargeReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);

	/*----------------合区活动begin------------------*/
	int GetHequChargeReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetHequVIPeward(unsigned uid, unsigned vindex, unsigned subindex, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetHequRecompenseReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetHequBuzhuReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetHequbuchangLevel(unsigned uid);
	/*----------------合区活动end------------------*/

    //@end

	/**
	 * @param uid: 操作这uid
	 * @param data: 传入参数，json数组
	 * @param reward_data: 传出参数 ，奖励的资源信息
	 * @param newEqDatas: 传出参数，奖励的武将信息，json数组
	 * @param hero: 传出参数，奖励的武将ID信息
	 */
	int QuestReward(
			unsigned uid,
			Json::Value &data,
			XMLQuestReward &reward_data,
			Json::Value &newEqDatas,
			vector<string> &hero);
	int GetActivityReward(const string &questid,
			int rewardid,
			XMLQuestReward &reward_data,
			Json::Value &newEqDatas,
			vector<string> &hero);
	int GetOlGateReward(int level,
			int id,
			XMLQuestReward &reward_data,
			Json::Value &newEqDatas,
			vector<string> &hero,
			bool freward,
			int ch);
	int GetQuestReward(int id,
			XMLQuestReward &reward_data,
			Json::Value &newEqDatas,
			vector<string> &hero);
	int GetBarbarReward(unsigned uid, Json::Value &data, Json::Value &newEqDatas);
	int GetFiveTigerReward(unsigned uid, string &user_tech, Json::Value &data, Json::Value &result);

    int YingLingNormal(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);
    int YingLingAdvance(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);
    int YingLingExp(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);
    int YingLingStar(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);

	int ChangeName(unsigned uid, string& name, string& openid, string& figure, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ChangeNameAfterFirst(unsigned uid, string& name, unsigned equd, string& openid, string& figure,  Json::Value &result, unsigned lasttime, unsigned seqid);
	int SJ4399(unsigned uid, string& code, string& openid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int XSK4399(unsigned uid, string& code, string& openid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int XSKBaidu(unsigned uid, string& code, string& openid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int CreditShop(unsigned uid, unsigned eqid, unsigned b4399, Json::Value &result, unsigned lasttime, unsigned seqid);
	int TouchGold(unsigned uid, unsigned type, unsigned id, unsigned listindex, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ProtectToken(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeavenDaoist(unsigned uid, unsigned type, unsigned count, const Json::Value &equd, bool is_cash, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned oneclick);
	int Catapult(unsigned uid, unsigned count, const Json::Value &equd, int is_cash, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned oneclick);
	int MergeEquipment(unsigned uid, const vector< vector<unsigned> > &uds, Json::Value &result, unsigned lasttime, unsigned seqid);//将同样ud的装备合并到一起
	int EightFormation(unsigned uid, unsigned formation_id, unsigned count, const Json::Value &equd, unsigned cash, unsigned r, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned oneclick);

	int Double11(unsigned uid, unsigned type, unsigned id, bool allserver, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ShengDan2018(unsigned uid, const Json::Value & input, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetDouble11Rcnt(unsigned uid, bool allserver, Json::Value &result, unsigned lasttime, unsigned seqid);

	int XiaoNian2018(unsigned uid, const Json::Value & input, Json::Value &result, unsigned lasttime, unsigned seqid);

	int Sell(unsigned uid, const Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid);

	int HouHuiYouQi(unsigned uid, unsigned b_index, unsigned s_index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int BigHarvestRewardCoins(unsigned uid, const Json::Value &bid_arr, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid);
	int MoneyTreeRewardCoins(unsigned uid, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ChaoZhiZheKou(unsigned uid, unsigned b_index, unsigned s_index, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid);
	int YueHuiJuXian(unsigned uid, unsigned b_index, unsigned s_index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int LimitBuyOfZone(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveDefendGrow(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveAttackGrow(unsigned uid, const Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveAttackActivity(unsigned uid, const Json::Value data, Json::Value &result, unsigned lasttime, unsigned seqid);

	int CountryDayLogin(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int CountryDayShop(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int CountryDayBag(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ResetCountryDayShop(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeartbeatBigSale(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeartbeatBigSaleReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveBigSaleShop(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveCouponShop(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FiveShopReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JueXingTeHui(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JueXingTeHuiReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FuDai(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FreeExchange(unsigned uid, unsigned order, unsigned ud_left, unsigned ud_right, Json::Value &result, unsigned lasttime, unsigned seqid);
	int FreeExchangeReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int DoubleEleven(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int DoubleElevenReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaDailyGetLantian(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaExchange(unsigned uid, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaGetKey(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaGetTreasure(unsigned uid, unsigned order, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaOneKey(unsigned uid, unsigned order, unsigned ud, Json::Value &SecincData, Json::Value &equip, Json::Value &hero,  CDataXML *dataXML);
	int JuBaoXiaGetTreasureOneKey(unsigned uid, Json::Value orders, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JuBaoXiaReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeavenStep(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int DaoistStep(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ZhenBaoGeHero(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ZhenBaoGeBuilding(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeroStoneStep(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int BuildingStoneStep(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JinQiuNovember(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int AcchargeBackShenwen(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid);
	int HeroGrowStep(unsigned uid, unsigned hero_ud, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GrowDevelopGet(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid);

	int JinQiuShiYue(unsigned uid, unsigned index, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ChongZhiHuiKui(unsigned uid, unsigned index, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ZhiZunBaoXiang(unsigned uid, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid);
	int JiFenDuiHuan(unsigned uid, unsigned id, Json::Value &result, unsigned lasttime, unsigned seqid);
	int ProcessTribute(unsigned uid, unsigned id, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid);
	int MeltEquip(unsigned uid, unsigned ud1, unsigned ud2, unsigned ud3, unsigned lvl, unsigned spirit, Json::Value &result,unsigned lasttime,unsigned seqid);

    int VickyAcc(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);

    int GetXinWuFB(unsigned uid, unsigned index, unsigned pay, Json::Value & result, unsigned lasttime, unsigned seqid);

    int TowerStepUp(unsigned uid, unsigned bdid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid);
    int TowerUnlock(unsigned uid, unsigned bdid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid);

    int UpGradeBNW(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
    int FastUpGradeBNW(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
    int UpGradeBNWTech(unsigned uid, unsigned ud, unsigned job, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);
    int FastUpGradeBNWTech(unsigned uid, unsigned job, Json::Value & result, unsigned lasttime, unsigned seqid);
    int Learjyt(unsigned uid, unsigned ud, Json::Value & result, unsigned lasttime, unsigned seqid);
    int LearnJM(unsigned uid, unsigned ud, unsigned id, Json::Value & result, unsigned lasttime, unsigned seqid);

	/*---------------古卷专项活动begin------------------*/
    int LoadScrollActivity(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
    //完成事件
    int CompleteAffair(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);
    //活跃值奖励
    int GetActiveReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);
	/*----------------古卷专项活动end------------------*/

	/*---------------天帝宝库活动begin------------------*/
    //开箱子
    int OpenKingTreasure(unsigned uid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid);
    //领取奖励
    int ReceiveKingTreasure(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
    //回收奖励
    int RecycleKingTreasure(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid);
	/*----------------天帝宝库活动end------------------*/

    //古卷回馈
    int ReceiveScrollFeedback(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid);

    //七日觉醒
    int ReceiveSevenDayAwaken(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid);

    int HeroExtraStone(unsigned uid, unsigned heroud, unsigned equd, unsigned index, Json::Value &result, unsigned lasttime,unsigned seqid);

    int FashionStar(unsigned uid, unsigned id, unsigned ud, unsigned id1, unsigned ud1, unsigned id2, unsigned ud2, Json::Value &result, unsigned lasttime,unsigned seqid);

    int JihuoChenghao(unsigned uid, unsigned id, unsigned ud, unsigned heroud, Json::Value &result, unsigned lasttime,unsigned seqid);

    int PeidaiChenghao(unsigned uid, unsigned heroud, unsigned chenghao, Json::Value &result, unsigned lasttime,unsigned seqid);

    int ZhuanyiChenghao(unsigned uid, unsigned heroud1, unsigned heroud2, Json::Value &result, unsigned lasttime,unsigned seqid);

private:
	int deductSource(unsigned uid, int viplvl, unsigned refreshType, unsigned sourceType, Json::Value &result, Json::Value &stats, unsigned zmlud, Json::Value &user_flag, bool &bsave);
	int deductTime(unsigned uid, unsigned refreshType, Json::Value &stats, Json::Value &result);  // 使用免费时间
	int deductCoin(unsigned uid, unsigned refreshType, Json::Value &result, Json::Value &user_flag, bool &bsave);	 // 使用金币
	int deductCash(unsigned uid, unsigned refreshType, Json::Value &result, Json::Value &user_flag, bool &bsave);	 // 使用钻石
	int deductItem(unsigned uid, unsigned refreshType, Json::Value &result, unsigned zmlud);  // 使用招募令
	int deductVip(unsigned uid, int viplvl, unsigned refreshType, Json::Value &stats, Json::Value &result);   // 使用vip次数

	//获取铸魂阶层
	int GetZhuhunClass(unsigned exp);

	int getCoinOrCashCost(unsigned refreshType);
	unsigned getZhaomulingNum(unsigned coin){return unsigned((coin * 0.1 * 1.2 + 0.9999999) / 1) ;}

	int getSubNumByCh(unsigned ch);

	int checkLastSaveUID(DataUser &user);
	int checkLastSaveTime(DataUser &user,unsigned lasttime,unsigned seqid);

	int parseQuestReward(const Json::Value &data,
		XMLQuestReward &reward_data,
		Json::Value &newEqDatas,
		vector<string> &hero,		const string &code);

	int getHappyCardShowArr(Json::Value &newAct);

	int getDragonlist(Json::Value &dragonlist, const unsigned id);
	int getUselist(Json::Value &uselist, const Json::Value &draglist, unsigned &dragScale);
	int resetTouch(Json::Value &dragonlist, Json::Value &uselist, const unsigned id);
	int initDouble11NewAct(Json::Value &newAct, bool allserver);
	int initShengdanNewAct(Json::Value &newAct, unsigned non_zero, bool day=false);
	int initXiaonianNewAct(Json::Value &newAct);
	int deterDouble11TS(unsigned type, bool allserver);
	int adjustJuexueList(Json::Value &xllist, unsigned &zcount);
	int isJsonNameArrSize(const Json::Value &data, const string &name, const unsigned size);
	int initHitEggNewAct(Json::Value &newAct, unsigned reset = 0);
	int refreshHitEggNewAct(Json::Value &newAct, unsigned lock = 2);
	int getHitEggEquip(Json::Value &newAct, unsigned lock = 2);
	int getHitEggNewAct(unsigned uid, Json::Value &newAct, bool &isfirst);
	int checkHeroId(Json::Value &herojx, unsigned id, unsigned ihero);
	int getBetShopNewAct(unsigned uid, Json::Value &newAct);
	int initBetShopNewAct(Json::Value &newAct, bool reset = true);
	int initGetMedalNewAct(unsigned type, Json::Value &newAct, bool reset = true);
	int initGetNewWorldKillNewAct(Json::Value &newAct, bool reset = true);
	bool AidForBlueDiamondDailyGiftBag(const string& str_gift_get, Json::Value& stats, Json::Value& result);
	int HeroPowerUpSendReward(unsigned uid, unsigned heroud, float pt, CDataXML * dataXML, Json::Value & hero, Json::Value &result);

	friend class UserWrap;

	//获取活动时间范围内的充值钻石数
	int  GetCashFromActivity(Json::Value & user_flag, int begints, int endts, unsigned & cash);
	//获取活动时间范围内，消费的钻石数
	int  GetUsedCashFromActivity(Json::Value & user_flag, int begints, int endts, unsigned & cash);

	//调用者必须是使用CLogicUser::GetUser加载的dataUser
	int _useGiftBag(DataUser& dataUser, unsigned giftbagId, unsigned count, Json::Value &result);

	//抽取转盘
	int RollDragonTable(unsigned uid, Json::Value & newAct, Json::Value & result, unsigned & yinliang);
};

#endif /* LOGICCMD_H_ */
