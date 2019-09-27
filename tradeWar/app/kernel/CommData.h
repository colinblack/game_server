/*
 * CommData.h
 *
 *  Created on: 2015-8-24
 *      Author: Administrator
 */

#ifndef COMMDATA_H_
#define COMMDATA_H_

#include "Common.h"
//add属性
#define AP_LEVEL 0				//等级
#define AP_HA 1					//物攻
#define AP_MA 2					//魔攻
#define AP_HD 3					//物防
#define AP_MD 4					//魔防
#define AP_IP 5					//闪避
#define AP_BP 6					//暴击概率
#define AP_BV 7					//暴击倍数
#define AP_SP 8					//移速
#define AP_RP 9					//攻速
#define AP_EV 10				//总免伤值
#define AP_EP 11				//总免伤百分比
#define AP_HE 12				//物理免伤值
#define AP_HEP 13				//物理免伤百分比
#define AP_ME 14				//魔法免伤值
#define AP_MEP 15				//魔法免伤百分比
#define AP_TA 16				//总伤害加成
#define AP_HR 17				//命中值
#define AP_RANGE 18 			//攻击范围
#define AP_HP 19				//血量
#define AP_MP 20				//魔量
#define AP_MAX_HP 21 			//最大血量
#define AP_MAX_MP 22 			//最大魔量
#define AP_EQ_XI 23  			//装备洗练次数
#define AP_RIDE_STAR 24 		//坐骑ID
#define AP_FRONE_TIME 25		//冷冻时间
#define AP_MAX_CAPACITY 26		//兵营，资源建筑等的最大容量
#define AP_CAPACITY 27			//当前容量
#define AP_X 28					//坐标位置
#define AP_Y 29					//坐标位置
#define	AP_UD 30				//建筑，英雄，装备的唯一ID
#define AP_TYPE	31				//建筑，英雄，装备的种类，统一用数字表示
#define AP_COUNT 32				//对应可叠加装备，代表数量
#define AP_QUALITY 33			//装备品质/颜色,将领星级
#define AP_STRONG 34			//装备强化等级
#define AP_DEADLINE 35			//装备过期时间
#define AP_UPTS 36				//最后一次更新时间
#define AP_CB 37				//建造剩余时间
#define AP_CU 38				//升级剩余时间
#define AP_CR 39				//建筑修复剩余时间，武将回血剩余时间
#define AP_CP 40				//资源类建筑产满剩余时间
#define AP_STATUS 41			//对英雄:1 主将，2驻将，对装备:0:在背包 1:装在英雄身上 9:删除
#define AP_HERO_BUNKER 42		//驻将驻守建筑UD,工人正在建造或升级的建筑
#define AP_EXP 43				//将领经验
#define AP_STAR 44				//将领星级
#define AP_PT 45				//将领潜能值,浮点数
#define AP_GRADE 46				//将领潜能阶
#define AP_ZHEN 47				//将领在斗将中的位置
#define AP_BS_LVL 48			//天生技等级
#define AP_BS_LVL2 49			//第二个天生技等级
#define AP_P1 50				//勇气(攻击)
#define AP_P2 51				//魅力(暴击)
#define AP_P3 52				//战略(防御)
#define AP_P4 53				//智谋(闪避)
#define AP_P5 54				//统帅(生命)
#define AP_ATTACK_BUILDING 55	//对建筑伤害比例
#define AP_ATTACK_AIR 56		//对空伤害比例
#define AP_ATTACK_ARMY 57		//对地伤害比例
#define AP_ATTACK_NAVY 58		//对海伤害比例
#define AP_COUNTRY 59			//英雄所属国家
#define AP_PROF 60				//英雄职业(1:陆,2:空,3:海)
#define AP_HUD 61				//装备挂在英雄ud身上
#define AP_SPLASH 62			//溅射范围
#define AP_EBP 63				//抗暴击
#define AP_TRAIN_GAIN_EXP 64	//训练获得经验值
#define AP_STATE 65				//出战/非出战
#define AP_RIDE_SCIENCE1 66		//座驾科技等级(FF--科技4;FF--科技3;FF--科技2;FF--科技1)  // 弃用
#define AP_RIDE_SCIENCE2 67		//座驾科技等级(FF--科技8;FF--科技7;FF--科技6;FF--科技5)  // 弃用
#define AP_UPGRADE_SLOT 68		//升级槽位
#define AP_COMBAT 69			//英雄战力,建筑城防
#define AP_STONE_EUD 70			//宝石镶嵌装备
#define AP_STONE_SLOT 71		//宝石镶嵌位置  1,2,3,4,5
#define AP_EFFECT 72			//伤害效果
#define AP_STAT 73              //状态
#define AP_DIZZY 74             //眩晕
#define AP_INVINCIBLE 75        //无敌
#define AP_CD_TIME 76      		//英雄CD时间(俘虏释放时间)
#define AP_RIDE_LEVEL 77      	//座驾等级
#define AP_EQUIP_LOCK 78		//装备开锁信息
#define AP_SPIRIT 79      		//将灵
#define AP_DEFINE_NAME 80      	//自定义名字
#define AP_DEFINE_URL 81      	//自定义头像
#define AP_WALL_HS 82           //城墙方向
#define AP_HURT 83				//直接伤害
#define AP_ENERGY 84			//英雄精力
#define AP_CE 85				//英雄精力恢复时间
#define AP_MAX_ENERGY 86		//英雄精力上限
#define AP_LOCK_COUNT 87		//锁定个数

//rate属性
#define AP_HA_RATE 100			//物攻加成百分比
#define AP_HD_RATE 101			//物防加成百分比
#define AP_MOVE_SPEED_RATE 102 	//移速加成百分比
#define AP_ATTACK_SPEED_RATE 103//攻速加成百分比
#define AP_BP_RATE 104			//暴击增加百分比
#define AP_HP_RECOVE_RATE	105 //回血速度加成百分比
#define AP_MP_RECOVE_RATE	106	//回魔速度加成百分比
#define AP_HIRE_FRONE_RATE	107	//武将馆招将冷却时间提升百分比
#define AP_TRAIN_FRONE_RATE 108	//武将训练经验加成百分比
#define AP_MA_RATE 109			//魔攻提升百分比
#define AP_MD_RATE 110			//魔防提升百分比
#define AP_HP_RATE 111			//血量提升百分比
#define AP_MP_RATE 112			//魔法提升百分比
#define AP_CAPACITY_RATE 113	//容量提升百分比
#define AP_PRODUCT_RATE 114		//资源类建筑生产速度提升百分比
#define AP_IP_RATE	115			//闪避值提升百分比
#define AP_SKILL_CTL_RATE 116	//豁免控制技能百分比
#define AP_SKILL_STRONG_RATE 117//技能伤害加深百分比
#define AP_SKILL_WEEK_RATE	118	//技能伤害抵抗百分比
#define AP_SKILL_STATE_UP_RATE 119//状态技能增强百分比
#define AP_HR_RATE 120				//命中值
#define AP_EBP_RATE 121           	// 抗暴击百分比
#define AP_BASE_RATE 122			// 基础属性百分比
#define AP_BUDDY_POS 124

#define AP_MAX 124				//属性数量最大值


#define EQ_STATUS_HERO 1		//装备穿在英雄身上
#define EQ_STATUS_BUILDING 2		//宝石镶嵌在建筑上

typedef union{
	float  		pf;
	int32_t 	pi;
	uint32_t 	pui;
}Property;

typedef std::map<int,Property> PropertySets;
//洗练属性
struct SmithAttr
{
	uint8_t attrId;
	Property attrVal;
};

struct EquipmentBase{
	uint32_t ud;
	uint16_t t;	//装备类别
	uint8_t	 c; //数量
	uint8_t  q; //装备品质
	uint8_t  strong; //强化等级
	uint8_t status; //0在背包 1已装备 9删除
	uint32_t heroUd; //归属英雄，status = 1有效
	uint8_t hand_pos;//0左手 1右手
	uint32_t dead_line; //过期时间
	std::vector<SmithAttr> attrs; //洗练附加属性
};

/**
 * 单个建筑网络包结构：
 * 总长度+BuildingBase
 */
struct BuildingBase{
	uint32_t ud;	//建筑唯一编号
	uint16_t t;		//代表建筑种类，如城墙，主城，伏兵处之类
	uint8_t l;		//建筑等级
	int8_t status;	//状态0正常，9删除该建筑
	int32_t x;
	int32_t y;
	uint32_t upts;	//最后一次更新时间
	uint32_t cb;	//建造剩余时间，0代表不在建造状态
	uint32_t cu;	//升级剩余时间，0代表不在升级状态
	uint32_t cr;	//修复剩余时间，0代表非损坏状态
	uint32_t cp;	//资源类建筑产满剩余时间
};
/*
 * 玩家资源
 */
struct Resource
{
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
};

struct HeroBase{
	uint32_t ud;	//英雄唯一编号
	char     htype[10];	//英雄种类
	uint8_t  l;		//英雄等级
	uint8_t  def;	//1 主将，2驻将
	uint32_t upts;	//最后一次更新时间
	uint32_t cu;	//升级剩余时间，0代表不在升级状态
	uint32_t cr;	//修复剩余时间，0代表非损坏状态
};

enum {
	SKILL_USE_SUCCESS,
	SKILL_USE_INVALD_SKILL,
	SKILL_USE_IN_CD,
	SKILL_USE_COST_NOT_ENOUGH,
	SKILL_USE_TO_FAR,
	SKILL_USE_NEED_MORE_MP
};


#define RET_NO_EXIST_PROP 0 // 不存在的属性
// json对象中获取UInt参数
#define GET_UINT_ATTR_FROM_JSON(props, obj, attr, AP_MACRO) \
	uint32_t attr = 0; \
	string attr##Str; \
	if(Json::GetString(obj, #attr, attr##Str)) \
	{ \
		props[AP_MACRO].pui = CTrans::STOI(attr##Str); \
	} \
	else \
	{ \
		if(Json::GetUInt(obj, #attr, attr)) \
		{ \
			props[AP_MACRO].pui = attr; \
		} \
	}
// json对象中获取Float参数
#define GET_FLOAT_ATTR_FROM_JSON(props, obj, attr, AP_MACRO) \
	uint32_t attr = 0; \
	string attr##Str; \
	if(Json::GetString(obj, #attr, attr##Str)) \
	{ \
		props[AP_MACRO].pf = CTrans::STOF(attr##Str); \
	} \
	else \
	{ \
		if(Json::GetUInt(obj, #attr, attr)) \
		{ \
			props[AP_MACRO].pf = attr; \
		} \
	}

// json对象中获取参数存储到结构体中
#define GET_ATTR_FROM_JSON(obj, attr) \
	uint32_t attr = 0; \
	string attr##Str; \
	if(Json::GetString(obj, #attr, attr##Str)) \
	{ \
		eic.attr = CTrans::STOI(attr##Str); \
	} \
	else \
	{ \
		if(Json::GetUInt(obj, #attr, attr)) \
		{ \
			eic.attr = attr; \
		} \
	} \

// json对象中获取参数存储到结构体中
#define GET_FLOAT_FROM_JSON(obj, attr) \
	uint32_t attr = 0; \
	string attr##Str; \
	Json::GetString(obj, #attr, attr##Str); \
	eic.attr = CTrans::STOF(attr##Str); \

// xml对象中获取参数
#define GET_UINT_ATTR_FROM_XML(xmlConf, attr, AP_MACRO) \
	string attr##Str = xmlConf.GetAttrib(#attr); \
	if(!attr##Str.empty()) \
	{ \
		props[AP_MACRO].pui = CTrans::STOI(attr##Str); \
	}

#define DELETE_TOKEN(str) (str.substr(1,str.length() - 2))


#define AP_STAT_DIZZY 1
#define AP_STAT_INVINCIBLE 2
#endif /* COMMDATA_H_ */
