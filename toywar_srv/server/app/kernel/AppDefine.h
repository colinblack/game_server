//AppDefine.h
//20110525	dada	create

#ifndef __APPDEFINE_H__
#define __APPDEFINE_H__

//global
enum GameType
{
	GT_TOYWAR = 2,	//玩具军团/玩具大作战
	GT_MERCENARY = 4	//雇佣兵
};

//config

//#define APP_CONFIG_PATH	"/data/release/toywar/conf/app_config.xml"
#define APP_CONFIG_PATH	"../conf/app_config.xml"
#define CONFIG_PLATFORM_MAPPING "platform_mapping"
#define CONFIG_PLATFORM	"platform_config"
#define CONFIG_APP_PARAMS "app_params"
#define CONFIG_WHITE_LIST	"white_list"
#define CONFIG_ADMIN_LIST	"admin_list"
#define CONFIG_DATA_LOG_PATH	"data_log_path"
#define CONFIG_DBC_SERVER	"dbc_server"
#define CONFIG_LOG_LEVEL	"log_level"
#define CONFIG_LOG_PATH	"log_path"
#define CONFIG_LOG_NAME	"log_name"
#define CONFIG_LOG_REWIND	"log_rewind"
#define CONFIG_LOG_SIZE	"log_size"
#define CONFIG_LOG_RECORD_SIZE	"log_record_size"
#define CONFIG_INIT_ARCHIVE	"init_archive"
#define CONFIG_MAP_DATA	"map_data"
#define CONFIG_WORLD_USER_DATA	"world_user_data"
#define CONFIG_STRING_FILTER_DATA "string_filter_data"
#define CONFIG_NPC_DATA	"npc_data"
#define CONFIG_WF_COUNT	"wild_force_count"
#define CONFIG_GATE_COUNT	"gate_count"
#define CONFIG_CLIENT_DOMAIN	"client_domain"
#define CONFIG_INDEPEND	"independ"
#define CONFIG_WORLD_SIZE "world_size"
#define CONFIG_WORLD_NPC "world_npc"
#define CONFIG_WORLD_TERRAIN "world_terrain"
#define CONFIG_FORBID_USER "forbid_user"
#define CONFIG_BUSINESS_LOG_DIR "business_log_dir"

//DB
//对应DBC端口号和共享内存号为15200+ID
#define DB_USER_BASIC	1
#define DB_USER	2
#define DB_NEIGHBOUR	3
#define DB_USER_INTERACT	4
#define DB_USER_DATA	5
#define DB_PLATFORM_USER	6
#define DB_USER_EXTRA	7
#define DB_FRIEND	8
#define DB_GATE	12
#define DB_BASE	20
#define DB_USER_BASE	21
#define DB_BASE_EXTRA	22
#define DB_WORLD	23
#define DB_ATTACK	40
#define DB_USER_ATTACK	41
#define DB_MESSAGE	50
#define DB_USER_MESSAGE	51
#define DB_PAY	60
#define DB_PAY_HISTORY	61
#define DB_CASH_FLOW	62
#define DB_CONSUME	63
#define DB_INVENTORY	64
#define DB_ALLIANCE	70
#define DB_ALLIANCE_MEMBER	71
#define DB_ALLIANCE_MAPPING	72

#define MEM_SESSION	101
#define DB_USER_MAPPING	102
#define DB_ID_CTRL	103

//DB other
#define KEY_UID_CTRL	1
#define KEY_BASEID_CTRL	20
#define KEY_POSITION_CTRL	23
#define KEY_ATTACK_ID_CTRL	40
#define KEY_MESSAGE_ID_CTRL	50
#define KEY_PAY_ID_CTRL	61
#define KEY_CASH_FLOW_ID_CTRL 62
#define KEY_ALLIANCE_ID_CTRL 70
#define KEY_WYX_ORDER_ID_CTRL 127

//app define
#define USER_UID_START	10000000
#define UID_MIN	10000
#define UID_MAX	2000000000
#define ALLIANCE_ID_NULL	0
#define ALLIANCE_ID_MIN 2000000000
#define ALLIANCE_ID_START 2010000000
#define IsValidUid(uid) (uid >= UID_MIN && uid < UID_MAX)
#define IsAllianceId(id)	(id >= ALLIANCE_ID_MIN)
#define IsLegalUid(uid) (uid >= UID_MIN)
#define SESSION_TIME_OUT 3600	//会话超时
typedef vector<unsigned> UidList;

#define WF_UID	1000000

#define MAIN_BASE_ID	0
#define SUB_BASE_ID_START	1000000
#define BASE_ID_START	10000000
#define IsNpcBase(baseid)	(baseid > MAIN_BASE_ID && baseid < SUB_BASE_ID_START)
#define IsUserBaseIndex(baseid)	(baseid == MAIN_BASE_ID || baseid >= SUB_BASE_ID_START)
#define IsBaseIndex(baseid) (baseid < BASE_ID_START)
#define IsSubBase(baseid) (baseid >= SUB_BASE_ID_START)
#define WF_BASE_ID_START 1
#define ROBOT_BASE_ID_START 500
#define GATE_BASE_ID_START 1000
#define MAX_SUB_BASE_ID	1000100
#define NPC_ADMIN_ID	10000

#define NEW_USER_CASH	1000	//新用户金币数
#define NEW_USER_MUSHROOM_TIME (5 * 24 * 60 * 60)	//新手蘑菇时间
#define NEW_USER_PROTECT (1 * 24 * 60 * 60)	//新手保护时间
#define NEW_SUB_BASE_PROTECT (12 * 60 * 60)	//新分基地保护时间
#define DAMAGE_PROTECT_LV1 (18 * 60 * 60)	//破坏保护时间1
#define DAMAGE_PROTECT_LV2 (36 * 60 * 60)	//破坏保护时间2
#define DAMAGE_PROTECT_NEW (18 * 60 * 60)	//新破坏保护时间
#define DAMAGE_PROTECT_SUB_BASE	(60 * 60)	//分基地保护时间
#define ATTACK_LEVEL_LIMIT	4	//进攻等级差限制
#define ATTACK_TIMEOUT 60	//进攻冷却时间
#define ATTACK_MAX_TIME 600	//最大进攻时间
#define ATTACK_HISTORY_TIME (2 * 7 * 24 * 60 * 60)	//进攻日志时间
#define ONLINE_TIMEOUT	60	//在线冷却时间
#define LOGIN_PROTECT_TIME	(10 * 60)	//登录进攻保护时间
#define GATE_TIMES_DAILY	5	//每日关卡挑战次数
#define MAX_ATTACK_HISTORY	66	//最大进攻历史数
#define WF_REFRESH_TIME	(3 * 24 * 60 * 60)	//野怪刷新时间
#define WORLD_WF_REFRESH_TIME	(24 * 60 * 60)	//世界野怪刷新时间
#define GET_ALLIANCE_COUNT	10	//每次取联盟数
#define ALLIANCE_ACTIVE_COUNT 50	//联盟动态数
#define ALLIANCE_MEMBER_ATTACK_COUNT 10	//联盟成员被攻击记录数
#define ALLIANCE_ENEMY_TIME (1 * 7 * 24 * 60 * 60)	//联盟仇敌记录时间
#define TRUCE_TIME (7 * 24 * 60 * 60)	//求和
#define IsOnline(t) (t + ONLINE_TIMEOUT > Time::GetGlobalTime())
#define WORLD_OCCUPY_DAMAGE_LIMIT	90	//占领基地破坏要求
#define WORLD_TERRAIN_HORIZON	100	//地平线

//session
#define SESSION_DATA "data"

//error
#define KEY_RESULT "error"
#define KEY_PARAMS "params"

//Error
#define KEY_ERR_UNKNOW	"unknow_error"
#define KEY_ERR_USER_ONLINE "user_online"
#define KEY_ERR_BEING_PROTECTED "being_protected"
#define KEY_ERR_BEING_ATTACKED "being_attacked"
#define KEY_ERR_YOU_BEING_ATTACKED "you_being_attacked"

//Platform
#define WYX_LEADERBOARD_GATE_ID	1
#define WYX_LEADERBOARD_RESOURCE_ID	1
#define WYX_LEADERBOARD_LEVEL_ID	2
#define WYX_LEADERBOARD_POINT_ID	2
#define WYX_LEADERBOARD_ATTACK_ID	3
#define WYX_ACHIEVEMENT_LEVEL_BASE	0
#define WYX_ACHIEVEMENT_GATE_BASE	5
#define WYX_ACHIEVEMENT_LOOT_BASE	10
#define WYX_ACHIEVEMENT_ATTACK_BASE	15
#define WYX_ACHIEVEMENT_COMMAND_BASE	20
#define WYX_ACHIEVEMENT_QUEST_BASE	25
#define WYX_ACHIEVEMENT_INVITE_BASE	30
#define WYX_ACHIEVEMENT_HELP_BASE	35
#define WYX_ACHIEVEMENT_LOCK_BASE	40
#define WYX_ACHIEVEMENT_MUSHROOM_BASE	45
#define WYX_ACHIEVEMENT_WORKER_BASE	50

#endif	//__APPDEFINE_H__


