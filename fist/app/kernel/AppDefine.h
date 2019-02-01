//AppDefine.h
//20110525	dada	create

#ifndef __APPDEFINE_H__
#define __APPDEFINE_H__

//config
#define APP_CONFIG_PATH						"../conf/app_config.xml"
#define APP_DOMAIN_CONFIG_PATH  			"../../pi/conf/domai_config.xml"

#define DEFAULT_APP_PATH					"/data/release/sg17/"
#define CONFIG_ALL_DATA_LOG_PATH			"datalog/"
#define CONFIG_DBC_SERVER					"pi/conf/dbc_server.xml"
#define CONFIG_STRING_FILTER_DATA 			"data/stringfilter.dat"
#define CONFIG_JSON_PATH		 			"pi/conf/json/"
#define CONFIG_MAP_PATH			"pi/conf/home.map"

#define DEFAULT_APP_CONFIG_PATH				"conf/app_config.xml"
#define CONFIG_DATA_LOG_PATH				"datalog/"
#define CONFIG_BUSINESS_LOG_DIR 			"log/business/"
#define CONFIG_LOG_PATH						"log/"
#define CONFIG_DATA_PATH 					"data/"
#define CONFIG_SHM_PATH 					"shm/"
#define CONFIG_ROOM_PATH 					"room/"
#define CONFIG_SAVE_PATH 					"save/"
#define GRADE_RANK_PATH                     "webroot/rankdata/grade_rank_"
#define GRADE_RESULT_RANK_PATH              "webroot/rankdata/grade_result_rank_"



#define CONFIG_LOG_LEVEL		"log_level"
#define CONFIG_LOG_NAME			"log_name"
#define CONFIG_LOG_REWIND		"log_rewind"
#define CONFIG_LOG_SIZE			"log_size"
#define CONFIG_LOG_RECORD_SIZE	"log_record_size"

#define CONFIG_WHITE_LIST		"white_list"
#define CONFIG_ADMIN_LIST		"admin_list"
#define CONFIG_SRVID "server_id"
#define CONFIG_OPENTIME "open_ts"
#define CONFIG_BASE "base"

#define BASE_FORBID_REASON_LEN 32
#define BASE_NAME_LEN 32
#define BASE_FIG_LEN 128
//玩家最大等级
#define USER_MAX_LEVEL 100

//延迟下线时间(秒)
#define OFFLINE_DELAY 60
#define TUTOR_MAX 55555

//英雄技能最大等级
#define MAX_HERO_SKILL_LEVEL  10

//最大英雄数
#define MAX_HERO_NUM 50

//最大可选英雄
#define MAX_FORMATION_HERO 2
#define MAX_BATTLE_PROPS 2

//体力恢复间隔
#define POWER_RECOVER_PER_SEC   (6*60)

//体力上限
#define POWER_MAX 100

//体力道具每天使用次数上限
#define POWER_PROP_TIMES 2

//好友每次赠送体力
#define POWER_DONATE_PER 5
//每日最大赠送体力值
#define POWER_DAILY_MAX_DONATE 150
//pve体力最小值
#define PVE_POWER_MIN 10

//段位
#define USER_GRADE_INDEX 7
#define GRADE_SEASON 14
#define GRADE_DAILY_SCORE 100
#define GRADE_PER_SCORE 10
#define RECORD_GRADE_LEN 5

//图鉴碎片类型
#define ARCHIVE_CHIP_TYPE 6

//最大荣誉值
#define MAX_HONOR 50000

//每次增加或减少荣誉值
#define PER_HONOR 10

//一次推荐玩家人数
#define RECOMMEND_USER_NUM 10

//最大好友数
#define MAX_FRIEND_NUM 50

//挂历离线奖励时长
#define ONHOOK_OFLINE_REWARD_TS  (86400*2)

//武馆最大星级
#define MAX_MARTIAL_CUB_GRADE	3
//武馆每次推荐邀请玩家人数
#define INVITE_USER_NUM	6

//武馆收益道具种类
#define MARTIAL_CLUB_REAP_PROPS 2

//武馆最大离线收益
#define MARTIAL_CLUB_MAX_OFFLINE_TS (86400*2)

//每组推荐武馆数
#define RCOMMANDE_PER_GROUP_NUM 4

//武馆最大容量
#define	MARTIAL_CLUB_MAX_SIZE 4

//武馆升级时间减少系数
#define MARTIAL_UP_LEVEL_TS_PER (60*60)

//每天限制踢馆次数
#define MARTIAL_BATTLE_DAILY_MAX_COUNT 10

//武馆保护时间
#define MARTIAL_BATTLE_PROTECT_TS	(2*60*60)

//最大邀请玩家奖励数
#define MAX_INVITE_REWARD_NUM 15

//排位赛真玩家
#define GRADE_BATTLE_USER 100

//排行榜统计人数
#define RANK_SIZE 1000

//一场杯赛人数
#define CHAMPIONSHIP_PLAYER_NUM 8

//杯赛添加机器人时间间隔
#define CHAMPIONSHIP_TIME_GAP 5

//新手引导最大步数
#define TUTORIAL_MAX_STAGE 10000

//杯赛最大回合数
#define CHAMPIONSHIP_MAX_TURN 4
//杯赛种类
#define CHAMPIONSHIP_TYPE 7

//每场比赛最大机器人数
#define CHAMPIONSHIP_PER_ROBOTS 8


//杯赛第一回合比赛人数
#define TURN_1 8
//杯赛第二回合比赛人数
#define TURN_2 4
//杯赛第三回合比赛人数
#define TURN_3 2
//杯赛结束剩下人数
#define LEFT  1

//杯赛每一回合开始战斗时长
#define PER_TURN_START_TIME 25

//杯赛下一回合等待时长
#define PER_TURN_BATTLE_TIME 50

//杯赛时长
#define CHAMPIONSHIP_TIME (60*10)


enum OnhookType
{
	e_onhook_exp  = 0,	//挂机经验
	e_onhook_coin = 1,	//挂机金币
	e_onhook_max,
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
	PT_51WAN	    = 34,	//
	PT_YUNQU	    = 35,	//
	PT_XUNLEI	    = 36,	//
	PT_TIEXUE	    = 37,	//
	PT_FENGHUANG    = 38,	//
	PT_7k7k		    = 39,	//
	PT_360		    = 40,	//
	PT_YLT		    = 41,	//
	PT_CYXC		    = 42,	//
	PT_WB_AND	    = 43,	//手q玩吧安卓
	PT_LIMI		    = 44,	//厘米秀
	PT_WB_IOS	    = 45,	//手q玩吧IOS
	PT_WX			= 46,	//微信
    PT_HD        =47,//赫达sdk

	PT_MAX,
};

#define Is_QQ_Platform(Platform) (Platform == PT_PENGYOU || Platform == PT_QZONE || Platform == PT_3366 || Platform == PT_qqgame || Platform == PT_TX_C9)
#define INC_POW(now, last) ((now - last)/POWER_RECOVER_PER_SEC)
#define IsValidMatialSlot(grade, size, slot) ( grade*10 < slot && slot <= (grade*10 + size))
#define IsValidMartialGrade(grade) (0 < grade && grade < 4)

//图鉴
#define ARCHIVE_LENGTH	50
//图鉴碎片
#define ARCHIVE_CHIP_LENGTH 50

#define ARCHIVE_CHIP_NUM 9
//技能
#define HERO_SKILL_LENGTH	4

//npc最大关卡值
#define NPC_MAX_STAGE	100

//最大龙珠索引
#define MAX_DRAGON_BALL_INDEX 8
//龙魂id
#define DRAGON_SCALE_ID 7
//技能书id
#define SKILL_BOOK_ID 6

#define LIMIT_TIMES_PROPS_LEN 3

//最大星级数
#define MAX_STAR_NUM 5

//杯赛每回合最大时间
#define CHAMPION_TURN_MAX_TIME 6

//DB
//对应DBC端口号和共享内存号为18000+ID
#define DB_EXCHANGE_CODE    4
#define DB_NAME				7

#define DB_BASE             101
#define DB_BASE_BUFF        5000
#define DB_BASE_FULL        1

#define DB_ITEM             110
#define DB_ITEM_FULL        200

#define DB_HERO				112
#define DB_HERO_FULL		50

#define DB_CONCERN			113
#define DB_CONCERN_FULL		50

#define DB_MARTIAL_CLUB		114
#define DB_MARTIAL_CLUB_FULL 5

#define DB_MARTIAL_HERO		115
#define DB_MARTIAL_HERO_FULL 10

#define DB_INVITE		116
#define DB_INVITE_FULL 	20

#define DB_DETACH_HERO	117
#define DB_DETACH_HERO_FULL  20

//通用活动
#define DB_GAME_ACTIVITY 102
#define DB_GAME_ACTIVITY_FULL 50
//通用活动中活动数据的个数
#define DB_GAME_DATA_NUM 15
//充值历史
#define DB_CHARGE_HISTORY 103
#define DB_CHARGE_HISTORY_FULL 15

//建筑
#define DB_BUILD 121
#define DB_BUILD_FULL  (MAP_LENGTH * MAP_WIDTH)

#define DB_CROPLAND  122
#define DB_CROPLAND_FULL 200

#define DB_PRODUCEEQUIP 123
#define DB_PRODUCEEQUIP_FULL 13

#define DB_ANIMAL 124
#define DB_ANIMAL_FULL 63

#define DB_EQUIPMENT_STAR 125
#define DB_EQUIPMENT_STAR_FULL 20

#define MEM_SESSION			91
#define SESSION_DATA		"data"


#define MEMORY_RESOURCE       301
#define MEMORY_USER_GRADE	  304
#define MEMORY_PROPERTY_NUM DB_BASE_BUFF*10

#define MEMORY_ASYN       302
#define MEMORY_ASYN_NUM   5

enum ASYN_TYPE
{
	e_asyn_cash				= 0,
	e_asyn_coin				= 1,
	e_asyn_accrecharge		= 2,
	e_asyn_exp				= 3,
	e_asyn_r1				= 4,
	e_asyn_r2				= 5,
	e_asyn_r3				= 6,
	e_asyn_r4				= 7,
	e_asyn_power			= 8,

	e_asyn_max				= 10000,
};

//通知系统
#define MEMORY_NOTIFY	303
#define NOTIFY_CONTENT_LEN 128
#define PER_USER_MAX_NOTIFY	 20

//@end

//邮箱
#define MEMORY_POST	305
#define PER_USER_MAX_POST 50

//杯赛
#define MEMORY_CHAMPIONSHIP 306
#define MEMORY_MATCH_NUM 5000
#define MEMORY_CHAMPIONSHIP_NUM 500

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
#define PROTOCOL_EVENT_BATTLE_CONNECT 102 //battle间通信
#define PROTOCOL_EVENT_BATTLE_FORWARD 103 //battle间转发给用户

enum ActivityID
{
	e_Activity_max
};
enum SigNum
{
	e_Sig_Save			= 64,
	e_Sig_data_log		= 63,
	e_Sig_try_clear		= 62,
	e_Sig_print_info	= 61, //打印resource_manager的信息
};
enum CurCMD
{
	e_CMD_none			= 0,
	e_CMD_new			= 1,
	e_CMD_login			= 2,

	e_CMD_max
};

enum PostType
{
	e_Post_randomUser		= 0, //随机挑战玩家
	e_Post_inviteUser		= 1, //邀请玩家英雄加入自己武馆
	e_post_martialBattle	= 2, //踢馆战报

	e_Post_max
};

enum Build_Direct
{
	direct_right = 0,  //朝右
	direct_down  = 1,  //朝下
};

enum BuildType
{
	build_type_corpland = 0,   //农地
	build_type_animal_residence = 1,  //动物住所
	build_type_animal			= 2,  //动物
	build_type_produce_equipment = 3,  //生产设备
	build_type_fruit_tree = 4,  //果树
	build_type_decorate = 5,   //装饰
	build_type_storage = 10,  //仓库
	build_type_house = 11,  //房子
};

enum StorageType
{
	type_granary = 1, //粮仓
	type_warehouse = 2, //货仓
};

//玩家属性类型
enum PropertyType
{
	type_coin	= 1,
	type_cash	= 2, //钻石
	type_exp	= 3, //如果用户升级了会额外推送升级协议
	type_level	= 4, //等级
	type_power	= 5, //体力
};

//生产线状态
enum ProduceStatus
{
	status_free 	= 0,  //空闲
	status_hungry 	= 0,  //饥饿
	status_growup 	= 1,  //成长
	status_procing	= 1, //生产中
	status_harvest 	= 2,  //收获
	status_suspend	= 2, //暂停生产
	status_full		= 2, //饱腹
};

enum EquipmentStarProperty
{
	property_type_coin = 1,  //金币加成
	property_type_exp = 2,  //经验加成
	property_type_time = 3,  //生产时间缩短
};

//exchange code
#define CODE_SIZE 12
#define CODE_TYPE 32//0-31

#define CMI ConfigManager::Instance()

//定时任务类型
enum RoutineType
{
	routine_type_build 	= 1,  //建筑和各生产线
	routine_type_order	= 2,  //订单
	routine_type_truck 	= 3,  //卡车
	routine_type_ship 	= 4,  //航运
};
//加速消耗类型
enum RoutineSpeedUpType
{
	routine_speed_cash = 0,
	routine_speed_item = 1,
};

enum HeroProperty
{
	HeroProperty_hp				= 0, //血量
	HeroProperty_attack			= 1, //攻击
	HeroProperty_defend			= 2, //防御
	HeroProperty_first			= 3, //先手
	HeroProperty_hit			= 4, //命中
	HeroProperty_dodge			= 5, //闪避
	HeroProperty_crit_strike	= 6, //暴击
	HeroProperty_crit_resist	= 7, //抗暴击
	HeroProperty_crit_rate		= 8, //暴击伤害

	HeroProperty_max,
};

//道具类型
enum AllItemType
{
	item_type_hp 			= 0,  //血量
	item_type_rage 		= 1,  //怒气
	item_type_att 		= 2,  //攻击
	item_type_skill		= 3,  //技能书
	item_type_strength 	= 4,  //体力
	item_type_dragon		= 5,  //龙魂

	item_type_max
};

enum BattleDemoHeroSkillType
{
	e_skill_0	= 0,
	e_skill_1	= 1,
	e_skill_2	= 2,
	e_skill_3	= 3,

	e_skill_max
};
enum BattleDemoItemNum
{
	e_item_0	= 0,
	e_item_1	= 1,

	e_item_max 	= 2,
	e_item_full	= 4
};
enum BattleDemoItemType
{
	e_item_hp		= 0,
	e_item_power	= 1,
	e_item_att		= 2,

	e_item_type_max
};
enum BattleDemoSide
{
	e_att			= 0,
	e_def			= 1,

	e_side_max
};
#define BDC_S(CN) ConfigManager::Instance()->battleDemoConfig.m_config.CN()
#define BDC_A(CN, CI) ConfigManager::Instance()->battleDemoConfig.m_config.CN(CI)

enum URL_ACT_TYPE
{
	e_url_act_none		= 0,
	e_url_act_1			= 1,//1邀请活动链接
	e_url_act_2			= 2,//2挑战随机玩家复仇链接
	e_url_act_3			= 3,//3图鉴交换链接
	e_url_act_4			= 4,//4邀请好友送图鉴链接
	e_url_act_5			= 5,//5武馆邀请链接
};

enum Winner
{
	att_win 	= 1, //攻方胜
	def_win		= 2, //守方胜
};

#endif	//__APPDEFINE_H__
