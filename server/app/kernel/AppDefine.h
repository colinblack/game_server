//AppDefine.h
//20110525	dada	create

#ifndef __APPDEFINE_H__
#define __APPDEFINE_H__

//config
#define APP_CONFIG_PATH						"../conf/app_config.xml"
#define APP_DOMAIN_CONFIG_PATH  			"../../pi/conf/domai_config.xml"

#define DEFAULT_APP_PATH					"/data/release/sgonline/"
#define CONFIG_ALL_DATA_LOG_PATH			"datalog/"
#define CONFIG_DBC_SERVER					"pi/conf/dbc_server.xml"
#define CONFIG_STRING_FILTER_DATA 			"data/stringfilter.dat"
#define CONFIG_JSON_PATH		 			"pi/conf/json/"

#define DEFAULT_APP_CONFIG_PATH				"conf/app_config.xml"
#define CONFIG_DATA_LOG_PATH				"datalog/"
#define CONFIG_BUSINESS_LOG_DIR 			"log/business/"
#define CONFIG_LOG_PATH						"log/"
#define CONFIG_DATA_PATH 					"data/"
#define CONFIG_SHM_PATH 					"shm/"

#define CONFIG_LOG_LEVEL		"log_level"
#define CONFIG_LOG_NAME			"log_name"
#define CONFIG_LOG_REWIND		"log_rewind"
#define CONFIG_LOG_SIZE			"log_size"
#define CONFIG_LOG_RECORD_SIZE	"log_record_size"

#define CONFIG_WHITE_LIST		"white_list"
#define CONFIG_ADMIN_LIST		"admin_list"
#define CONFIG_SRVID "server_id"
#define CONFIG_OPENTIME "open_ts"

#define BASE_FORBID_REASON_LEN 32
#define BASE_NAME_LEN 32
#define BASE_FIG_LEN 128

#define FRIEND_GIFT_LOG_LEN 4000

//延迟下线时间(秒)
#define OFFLINE_DELAY 60

#define SG17_KINGDOM 3
#define RAND_KINGDOM_CASH 100

#define BATTLE_FIELD_CITY_NEUTRAL  		13
#define BATTLE_FIELD_CITY_CAPITAL  		1
#define BATTLE_FIELD_CITY_KINGDOM_OTHER	81
#define BATTLE_FIELD_CITY_KINGDOM		(BATTLE_FIELD_CITY_CAPITAL+BATTLE_FIELD_CITY_KINGDOM_OTHER)
#define BATTLE_FIELD_CITY 				(BATTLE_FIELD_CITY_KINGDOM*3+BATTLE_FIELD_CITY_NEUTRAL)
#define BATTLE_FIELD_CITY_KINGDOM_SEQ	100

#define BATTLE_FIELD_HISTORY 24
#define BATTLE_FIELD_ROAD 404

#define BATTLE_FIELD_MOVE 3

#define BATTLE_FIELD_REWARD_R 10

#define SG17_HERO_NUM 5
#define DEMO_SHOW_UNIT 4
#define SG17_HERO_SOLDIER 5
#define SG17_HERO_SOLDIER_SUB 3
#define DEMO_SHOW_PAGE 8
enum DemoOfflineProperty
{
	DemoOfflineProperty_chp				= 0,//回血速度
	DemoOfflineProperty_soldier			= 1,//士兵排数
	DemoOfflineProperty_tech			= 2,//科技战法系数			//id
	DemoOfflineProperty_anti_tech		= 3,//科技抵抗系数			//id
	DemoOfflineProperty_hexp			= 4,//战斗中产出的英雄经验增加系数   //id
	DemoOfflineProperty_s_level			= 5,//兵种等级
	DemoOfflineProperty_u_level			= 6,//主公等级
	DemoOfflineProperty_b_level			= 7,//功勋宝箱系数

	DemoOfflineProperty_max,
};
enum DemoHeroProperty
{
	DemoHeroProperty_hp				= 0,//血量
	DemoHeroProperty_attack			= 1,//攻击
	DemoHeroProperty_defend			= 2,//防御
	DemoHeroProperty_skill_extra	= 3,//额外战法
	DemoHeroProperty_skill_anti		= 4,//抵抗额外战法
	DemoHeroProperty_attack_extra	= 5,//额外平砍
	DemoHeroProperty_attack_anti	= 6,//抵抗额外平砍
	DemoHeroProperty_int			= 7,//统
	DemoHeroProperty_str			= 8,//勇
	DemoHeroProperty_level			= 9,//等级
	DemoHeroProperty_power			= 10,//战力

	DemoHeroProperty_max,
};
enum DemoFightProperty
{
	DemoFightProperty_hp				= 0,//血量
	DemoFightProperty_attack			= 1,//攻击
	DemoFightProperty_defend			= 2,//防御
	DemoFightProperty_skill_extra		= 3,//额外战法
	DemoFightProperty_skill_anti		= 4,//抵抗额外战法
	DemoFightProperty_attack_extra		= 5,//额外平砍
	DemoFightProperty_attack_anti		= 6,//抵抗额外平砍
	DemoFightProperty_int				= 7,//统
	DemoFightProperty_str				= 8,//勇
	DemoFightProperty_level				= 9,//等级
	DemoFightProperty_power				= 10,//战力
	DemoFightProperty_soldier			= 11,//士兵排数
	DemoFightProperty_tech				= 12,//科技战法系数
	DemoFightProperty_anti_tech			= 13,//科技抵抗系数
	DemoFightProperty_hexp				= 14,//战斗中产出的英雄经验增加系数
	DemoFightProperty_s_level			= 15,//兵种等级
	DemoFightProperty_u_level			= 16,//主公等级

	DemoFightProperty_max,
};
enum DemoGType
{
	DemoGType_1				= 1,
	DemoGType_2				= 2,
	DemoGType_3				= 3,
	DemoGType_4				= 4,
};
enum DemoS
{
	DemoS_skill				= 0,
	DemoS_shpae_1			= 1,
	DemoS_shpae_2			= 2,
	DemoS_shpae_3			= 3,
	DemoS_shpae_a			= 4,

	DemoS_unchosen,
};
enum BattleFieldMissonStatus
{
	BattleFieldMissonStatus_defend_lose		= 0,
	BattleFieldMissonStatus_defend_win  	= 1,
	BattleFieldMissonStatus_defending		= 2,
	BattleFieldMissonStatus_defend_over		= 3,
	BattleFieldMissonStatus_attack_lose		= 4,
	BattleFieldMissonStatus_attack_win  	= 5,
	BattleFieldMissonStatus_attacking		= 6,
	BattleFieldMissonStatus_attack_over		= 7,

	BattleFieldMissonStatus_max
};
enum NPCUIDType
{
	e_normal_npc		= 1,//城防军
	e_attack_npc		= 2,//远征军
	e_defend_npc		= 3,//禁卫军
	e_vision_npc		= 4,//玩家幻影
	e_gate_npc			= 5,//闯关敌人
	e_act_npc			= 6,//活动npc
	e_vision_other		= 7,//玩家镜像，竞技场等用
	e_ttt_npc			= 8,//偷袭珍珠港npc
	e_nb_npc			= 9,//精英部队npc
};
enum BattleType
{
	e_battle_city			= 1,//攻城
	e_battle_rush			= 2,//单挑
	e_battle_gate			= 3,//闯关
	e_battle_ladder			= 4,//竞技场
	e_battle_ship			= 5,//草船
	e_battle_temp			= 6,//为前端提供接口
};
#define IS_SEND_REWARD(type) (type == e_battle_gate || type == e_battle_ladder)
#define LADDER_NPC_ID  9000111

#define SET_MAT_1 21001
#define SET_MAT_2 21002
#define SET_MAT_3 21003
enum BattleRewardType
{
	e_battle_reward_type_coin		= 0,
	e_battle_reward_type_food		= 1,
	e_battle_reward_type_wood		= 2,
	e_battle_reward_type_iron		= 3,
	e_battle_reward_type_order		= 4,
	e_battle_reward_type_longlin	= 5,
	e_battle_reward_type_set_1		= 6,
	e_battle_reward_type_set_2		= 7,
	e_battle_reward_type_set_3		= 8,

	e_battle_reward_type_max,
};
enum CityScale
{
	e_city_sacle_1					= 1,
	e_city_sacle_2					= 2,
	e_city_sacle_3					= 3,
	e_city_sacle_4					= 4,
};
enum CityRewardType
{
	e_city_reward_type_empty		= 0,
	e_city_reward_type_iron			= 1,
	e_city_reward_type_set_1		= 2,
	e_city_reward_type_set_2		= 3,
	e_city_reward_type_set_3		= 4,

	e_city_reward_type_max,
};

enum GateType
{
	e_gt_rush				= 0xFFFF,	//battle.type=e_battle_rush;	hero.gate
	e_gt_ladder				= 0xFFFE,	//battle.type=e_battle_ladder;	hero.gate
	e_gt_ladder_min			= 1,		//battle.type=e_battle_ladder;	battle.gate
	e_gt_ladder_max			= 100,		//battle.type=e_battle_ladder;	battle.gate
	e_gt_official_min		= 5000,		//battle.type=e_battle_ladder;	battle.gate
	e_gt_official_max		= 11000,	//battle.type=e_battle_ladder;	battle.gate
	e_gt_city_min			= 20000,	//battle.type=e_battle_ladder;	battle.gate
	e_gt_city_max			= 21000,	//battle.type=e_battle_ladder;	battle.gate
	e_gt_ship				= 0xFFFD,	//battle.type=e_battle_ship;	hero.gate
	e_gt_fog_min			= 10000,	//battle.type=e_battle_gate;	hero.gate & battle.gate
	e_gt_fog_max			= 10032,	//battle.type=e_battle_gate;	hero.gate & battle.gate
	e_gt_trial_min			= 10100,	//battle.type=e_battle_gate;	hero.gate & battle.gate
	e_gt_trial_max			= 10199,	//battle.type=e_battle_gate;	hero.gate & battle.gate
};

enum WingManID
{
	e_WingManID_1		= 31001,//1.5倍战术伤害
	e_WingManID_2		= 31002,//100%抵御敌方技能
	e_WingManID_3		= 31003,//被摧毁时，对当前敌方造成僚机血量最大值25%伤害
	e_WingManID_4		= 31004,//敌方防御低于本方时，造成1.5倍战术，平砍伤害
	e_WingManID_5		= 31005,//增加20%攻击属性
	e_WingManID_6		= 31006,//增加20%防御属性
	e_WingManID_7		= 31007,//增加20%统属性
	e_WingManID_8		= 31008,//增加20%穿甲属性
	e_WingManID_9		= 31009,//增加20%重甲属性
};
#define WING_EFFECT_1 1.5
#define WING_EFFECT_3 0.25
#define WING_EFFECT_4 1.5
#define WING_EFFECT_5 1.2

#define VIP_HERO_ID_7 1233
#define VIP_HERO_EFFECT_7 1.5
#define VIP_HERO_ID_8 1226
#define VIP_HERO_ID_9 1230
#define VIP_HERO_EFFECT_9 10

enum MissionType
{
	mission_type_first_login	= 1,    //首次登录游戏
	mission_type_upgrade_building,    //升级子建筑
	mission_type_register,    //注册游戏名
	mission_type_gate,    //闯关
	mission_type_productivity,   //资源总产量
	mission_type_pray,   //祭祀
	mission_type_purchase,  //购买装备
	mission_type_herodress,   //穿戴装备
	mission_type_herohp_recover,  //英雄血量恢复
	mission_type_tech_research,  //科技研究
	mission_type_hegemony_kill,  //争霸杀敌
	mission_type_hegemony_feats,  //争霸功勋
	mission_type_recruit,  //招募英雄
	mission_type_autoupgrade, //使用自动建造
	mission_type_hammer,  //使用黄金加速锤子
	mission_type_character_buy, //购买指定品质装备
	mission_type_character_dress,  //穿戴指定品质装备
	mission_type_hero_upgrade, //英雄升级任务
	mission_type_num_dress,  //穿戴指定数量的装备
	mission_type_governaffair,  //政务事件处理
	mission_type_open_exploitbox,  //开启功勋宝箱
	mission_type_equipshop_refresh, //装备商店刷新
	mission_type_foggate_success,  //通过迷雾战
	mission_type_world_move, //世界移动
	mission_type_tech_done,  //科技研究完成
};

enum MissConditionType
{
	mission_condition_whether = 1,
	mission_condition_single,
	mission_condition_double,
	mission_condition_triple,
	mission_condition_assemble,
};

enum EquipType
{
	equip_type_normal = 1,   //普通装备
	equip_type_medal,  //勋章，特殊饰品
	equip_type_props,  //道具
	equip_type_suit_one = 4,     //套装一
	equip_type_suit_two = 5,  //套装二
	equip_type_suit_three = 6,   //套装三
	equip_type_suit_four = 16,  //套装四
	equip_type_suit_five = 17,   //套装五
	equip_type_max,
};

enum EquipSmeltType
{
	smelt_type_of_normal = 1,   //普通洗练
	smelt_type_of_super,   //超级洗练
};

enum EquipCharaterType
{
	charater_type_white = 1,
	charater_type_green,
	charater_type_blue,
	charater_type_yellow,
	charater_type_red,
	charater_type_purple,
	charater_type_max,
};

enum EquipSubType
{
	sub_type_one = 1,
	sub_type_two,
	sub_type_three,
	sub_type_four,
	sub_type_max,
};

enum DailyMissionType
{
	daily_mission_type_productivity	= 1,    //产量提升
    daily_mission_type_affair,  //处理政务
    daily_mission_type_smelt, //装备洗练
    daily_mission_type_blackmarket, //黑市兑换
    daily_mission_type_pkfield, //竞技场挑战
    daily_mission_type_upgrade_weapon,  //提升军工
    daily_mission_type_minesupport, //矿藏援建
    daily_mission_type_gate,  //闯关挑战
    daily_mission_type_exploit, //世界功勋
    daily_mission_type_kill, //世界杀敌
    daily_mission_type_refresheqshop,  //装备商店刷新
    daily_mission_type_parade, //阅兵
    daily_mission_type_official, //军职挑战
};

enum AchievementType
{
	achievement_type_productivity	= 1, //产量提示
	achievement_type_openmine,  //开矿
	achievement_type_minesupport,  //援建
	achievement_type_unlockhero,  //解锁英雄
	achievement_type_hprecover,  //瞬间回血
	achievement_type_joindepartment,  //加入部门
	achievement_type_official,  //获得官职
	achievement_type_affair,  //处理政务
	achievement_type_loyalexchange,  //民忠满意度兑换
	achievement_type_parade,  //阅兵
	achievement_type_dailymission,  //3星每日任务奖励领取
	achievement_type_weaponlevel, //军工等级
	achievement_type_character_equip,  //指定品质装备
	achievement_type_star_equip,  //四星装备
	achievement_type_extraproperty,  //额外属性
	achievement_type_character_component,  //指定品质部件
	achievement_type_tech_research,  //科技研究
	achievement_type_composesuit,  //套装合成
	achievement_type_rush,  //单挑
	achievement_type_kill,  //杀敌
	achievement_type_march, //突进
	achievement_type_retreat, //撤退
	achievement_type_occupycity, //占领城市
	achievement_type_foggate,  //迷雾闯关
};

enum EquipPropertyType
{
	//.攻击 2.防御 3.血量 4.强壮 5.掌控 6.强攻  7.强防  8-14 攻防血强壮等等百分比加成*
	property_type_attack = 1,
	property_type_defend,
	property_type_hp,
	property_type_strong,
	property_type_control,
	property_type_strong_attack,
	property_type_strong_defend,
	property_type_attack_percent,
	property_type_defend_percent,
	property_type_hp_percent,
	property_type_strong_percent,
	property_type_control_percent,
	property_type_strong_attack_percent,
	property_type_strong_defend_percent,
	property_type_max,
};

enum ResourceType
{
	resource_type_coin = 1, //银币
	resource_type_wood,  //木材
	resource_type_food,  //粮食
	resource_type_iron,  //镔铁
	times_type_order,  //募兵令
};

enum ComponentType
{
	component_type_normal = 1,  //普通部件
	component_type_props, //经验道具
};

enum PlatformType
{
	PT_UNKNOW 		= -1,	//未知
	PT_TEST 		= 0,	//测试平台
	PT_FACEBOOK 	= 1,	//Facebook平台中文版
	PT_PENGYOU		= 2, 	//朋友平台
	PT_RENREN 		= 3,	//人人平台
	PT_QZONE 		= 4,	//QZONE平台
	PT_SINAWB 		= 5,	//新浪微博
	PT_WEIYOUXI 	= 6,	//新浪微游戏
	PT_KUAIWAN 		= 7,	//快玩平台
	PT_MIXI 		= 8,	//Mixi平台
	PT_TXWEIBOAPP 	= 9,	//腾讯微博应用平台
	PT_MOBAGE 		= 10,	//日本Yahoo!Mobage平台
	PT_TXWEIBO 		= 11,	//腾讯微博
	PT_KAIXIN 		= 12,	//开心网
	PT_FETION 		= 13,	//飞信
	PT_VN 			= 14,	//英文版自建平台
	PT_3366 		= 15,	//3366
	PT_qqgame		= 16,	//qq游戏大厅
	PT_TW			= 17, 	//台湾BSG
	PT_EN			= 18,	//FB英文版
	PT_DO			= 19,	//英文版联运
	PT_4399			= 20,	//4399联运
	PT_C9			= 21,	//C9
	PT_SOGOU		= 22,	//搜狗游戏联运平台
	PT_7477			= 23,   //7477联运
	PT_TX_C9		= 24,   //tx-c9
	PT_KW			= 25,  	//mix for PT_7477
	PT_7K			= 26,	//mix for PT_7477
	PT_360UU		= 27,	//mix for PT_7477
	PT_QD			= 28,	//mix for PT_7477
	PT_V1			= 29,	//mix for PT_7477
	PT_66YOU		= 30,	//mix for PT_7477
	PT_51IGAME		= 31,	//mix for PT_7477
	PT_HUANLEYUAN	= 32,	//mix for PT_7477
	PT_BAIDU	    = 33,	//baidu联运

	PT_MAX,
};
#define Is_QQ_Platform(Platform) (Platform == PT_PENGYOU || Platform == PT_QZONE || Platform == PT_3366 || Platform == PT_qqgame || Platform == PT_TX_C9)

#define BATTLE_OCCUPY_REWARD 100
#define BATTLE_F_OCCUPY_REWARD 20
#define BATTLE_RUSH_REWARD 10
#define BATTLE_VISION_REWARD 50
#define BATTLE_FLY_REWARD 10

#define BATTLE_RANGE_1 1
#define BATTLE_RANGE_2 3
#define BATTLE_RANGE_3 5

#define BATTLE_MISSION_1_S 10
#define BATTLE_MISSION_2_S 15
#define BATTLE_MISSION_3_S 20
#define BATTLE_MISSION_1_E 11
#define BATTLE_MISSION_2_E 16
#define BATTLE_MISSION_3_E 22

#define BATTLE_CITY_REWARD_1 12
#define BATTLE_CITY_REWARD_2 17
#define BATTLE_CITY_REWARD_3 19
#define BATTLE_CITY_REWARD_4 22

#define LADDER_REWARD_T 19
#define KILL_RANK_REWARD 22

#define RMI_PAY_HIS 7
//DB
//对应DBC端口号和共享内存号为18000+ID
#define DB_NAME				7

#define DB_BASE             101
#define DB_BATTLE_REWARD	102
#define DB_BUILDING			150
#define DB_BUILD_QUEUE		151
#define DB_NPC_PASS			152
#define	DB_SCIENCE			153
#define DB_WEAPON			154
#define DB_GEM				155
#define DB_LIMIT_SHOP		156
#define DB_CASH_BACK		157
#define DB_TIME_LIMIT_PROP	158
#define DB_SMELT_ACTIVITY	159
#define DB_TOUCH_GOLD		160
#define DB_HUGE_DISCOUNT	161

#define DB_BASE_BUFF        5000
#define DB_BASE_FULL        1

//建筑
#define DB_BUILDING_FACTOR	(80)
//闯关
#define DB_NPC_PASS_FACTOR	(90)
//科技
#define DB_SCIENCE_FACOTR (60) //id数量
//武器
#define DB_WEAPON_FACOTR (6) //数量
//宝石
#define DB_GEM_FACTOR (16) //
//限时道具
#define DB_TIME_LIMIT_PROP_FACTOR (10)
//超值钜惠
#define DB_HUGE_DISCOUNT_FACTOR (3)

//装备商店
#define DB_EQUIP_SHOP       110
#define DB_EQUIP_SHOP_FULL	6

//物品
#define DB_EQUIPMENT	111
#define DB_EQUIPMENT_FULL	500

//英雄
#define DB_HERO		112
#define DB_HERO_FULL	50

//任务
#define DB_MISSION  113
#define DB_MISSION_FULL	50

//黄钻
#define DB_YELLOW_VIP  114
#define DB_YELLOWVIP_FULL      1

//集市
#define DB_MARKET 115
#define DB_MARKET_FULL 1

//累积登录
#define DB_CUMULATION_LOGIN 116
#define DB_CUMULATIONLOGIN_FULL 1
//广结名士活动
#define DB_NPCACTIVITY	117
//迷雾战
#define DB_FOGGATE  118
#define DB_FOGGATE_FULL 40
//部件
#define DB_COMPONET 119
#define DB_COMPONET_FULL  40
//部件产出
#define DB_COMPONET_PRODUCE	120
//每日任务
#define DB_DAILY_MISSION	121
#define DB_DAILY_MISSION_FULL	5
//成就
#define DB_ACHIEVEMENT	122
#define DB_ACHIEVEMENT_FULL	 300
//好友
#define DB_FRIEND	123
#define DB_FRIEND_FULL	30
//好友赠礼
#define DB_FRIEND_GIFT	124
//剧本战
#define DB_OPERA_BATTLE 125
#define DB_OPERA_BATTLE_FULL 60
//摇骰子
#define DB_SHAKE_DICE	126
//资源副本
#define DB_RESOURCE_COPY 127
#define DB_RESOURCE_COPY_FULL 20
//机型试炼
#define DB_MODEL_TRIAL	128
//跨国商人
#define DB_CROSS_BUSINESS 129
//部件售卖
#define DB_SELL_COMPONENT 130

#define MEM_SESSION			91
#define SESSION_DATA		"data"


#define MEMORY_BATTLE       301
#define MEMORY_HERO_PROPERTY  302
#define MEMORY_HERO_PROPERTY_NUM 50000
#define MEMORY_RESOURCE       303
#define MEMORY_ASYN       304
enum ASYN_TYPE
{
	e_asyn_cash				= 0,
	e_asyn_coin				= 1,
	e_asyn_wood				= 2,
	e_asyn_food				= 3,
	e_asyn_iron				= 4,
	e_asyn_npc_1			= 5,
	e_asyn_npc_2			= 6,
	e_asyn_npc_3			= 7,
	e_asyn_accrecharge		= 8,
	e_asyn_exp				= 9,
	e_asyn_market			= 10,  //龙鳞

	e_asyn_max				= 10000,
};
#define MEMORY_LADDER       305
#define LADDER_ITEM			100
#define LADDER_ENEMY		5

#define MEMORY_OFFICIAL		306   //官职系统
#define MEMORY_MINE			307   //矿洞
//剧本战
#define MEMORY_OPERA_BATTLE	308
#define MAX_DIFFICULTY 3
#define MAX_STAR_VALUE 5
#define MAX_BATTLE_NUM 20

//通知系统
#define MEMORY_NOTIFY	309
#define NOTIFY_CONTENT_LEN 128
#define PER_USER_MAX_NOTIFY	 20

//偷袭珍珠港
#define MEMORY_ATTACK_HARBOR 310

//@end

#define ADMIN_UID			10000000
#define UID_MIN				10000000
#define UID_MAX				2000000000
#define UID_ZONE			500000
#define IsValidUid(uid)		(uid > UID_MIN && uid < UID_MAX)
#define ALLIANCE_ID_NULL	0
#define ALLIANCE_ID_MIN		2000000000
#define ALLIANCE_ID_START	2010000000
#define AID_ZONE			500000
#define IsAllianceId(id)	(id >= ALLIANCE_ID_MIN)



//error
#define KEY_RESULT			"error"
#define KEY_ERROR_MESSAGE	"errMsg"
#define KEY_PARAMS			"params"


#define BUFF_SIZE 2048


#define U64_LOW(val) (val & 0X00000000FFFFFFFF)
#define U64_HIGH(val) ((val >> 32) & 0X00000000FFFFFFFF)
#define U32_LOW(val) (val & 0X0000FFFF)
#define U32_HIGH(val) ((val >> 16) & 0X0000FFFF)
#define LOW_8(val) (val & 0X000000FF)
#define MAKE64(a,b,c) 	(*((uint64_t*)(&(a)))) = ((uint64_t)(b) << 32) | (c)

#define AddtoVct(filed)  if (0 != filed) {vctsubs.push_back(filed);}

//内部通讯命令字
#define PROTOCOL_EVENT_SECOND_TIMER 101

enum ActivityID
{
	e_Activity_NPC		= 1,//广结名士
	e_Activity_Shop		= 2,//限时商店
	e_Activity_CashBack = 3, //充值返现
	e_Activity_Smelt	= 4, //洗练放送
	e_Activity_TouchGold= 5, //摸金校尉
	e_Activity_HugeDiscound = 6, //超值钜惠
	e_Activity_ShakeDice = 7, //摇骰子
	e_Activity_LittleCharge = 8, //充点小钱
	e_Activity_EnlivenKill	= 9, //杀敌活跃
	e_Activity_SellComponent	= 10, //部件售卖
	e_Activity_max
};
enum SigNum
{
	e_Sig_Save			= 64,
	e_Sig_data_log		= 63,
	e_Sig_battle_log	= 62,
	e_Sig_try_clear		= 61,
	e_Sig_print_info	= 60, //打印resource_manager的信息
	e_Sig_battle_over	= 59,
};
enum CurCMD
{
	e_CMD_none			= 0,
	e_CMD_new			= 1,
	e_CMD_login			= 2,

	e_CMD_max
};

enum NotifyID
{
	e_Notify_Killrank		= 1, //杀敌排行榜
	e_Notify_Mine			= 2,  //矿藏
	e_Notify_Enlivenkill 	= 3, //杀敌活跃排行榜
	e_Notify_Arena			= 4, //竞技场
	e_Notify_DepartKick		= 5, //官员系统T人
	e_Notify_AttackHarbor	= 6,  //偷袭珍珠港
};

#endif	//__APPDEFINE_H__
