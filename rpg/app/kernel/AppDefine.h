//AppDefine.h
//20110525	dada	create

#ifndef _APP_DEFINE_H_
#define _APP_DEFINE_H_

//config
#define APP_CONFIG_PATH			"../conf/app_config.xml"
#define CONFIG_SRVID			"server_id"
#define CONFIG_OPENTIME			"open_ts"
#define CONFIG_PLATFORM_MAPPING "platform_mapping"
#define CONFIG_PLATFORM			"platform_config"
#define CONFIG_ADMIN_LIST		"admin_list"
#define CONFIG_DATA_LOG_PATH	"data_log_path"
#define CONFIG_BUSINESS_LOG_DIR	"business_log_dir"
#define CONFIG_DBC_SERVER		"dbc_server"
#define CONFIG_LOG_LEVEL		"log_level"
#define CONFIG_LOG_PATH			"log_path"
#define CONFIG_LOG_NAME			"log_name"
#define CONFIG_LOG_REWIND		"log_rewind"
#define CONFIG_LOG_SIZE			"log_size"
#define CONFIG_LOG_RECORD_SIZE	"log_record_size"
#define CONFIG_STRING_FILTER_DATA "string_filter_data"
#define CONFIG_INIT_ARCHIVE		"init_archive"
#define CONFIG_CLIENT_DOMAIN	"client_domain"
#define CONFIG_MAP_DATA			"map_data"
#define CONFIG_NPC_DATA			"npc_data"
#define CONFIG_TCP_SERVER		"tcp_server"
#define CONFIG_QQ_ITEM_INFO		"qq_item_info"
#define CONFIG_WHITE_LIST       ""
#define CONFIG_WWM_PATH			"wwm_path"
#define CONFIG_SCENES_FILE		"scenes_file"
#define CONFIG_FORBID_MAP		"forbid_map"
#define CONFIG_PROPS_PATH		"props"
#define CONFIG_MAP_AREA_INFO	"map_area_info"
#define CONFIG_JSON_PATH		"conf/json/"
#define CONFIG_TREASURE_RECORD	"data/treasure_record.dat"
#define SESSION_DATA			"data"

//DB
//对应DBC端口号和共享内存号为18000+ID
#define DB_BASE               1
#define DB_POS                2
#define DB_LAST_SAFEAREA      3
#define DB_SKILL              4
#define DB_PAY                5
#define DB_ROLE               6
#define DB_MISSION            7
#define DB_ADVANCE            8
#define DB_EQUIP              9
#define DB_USER_MAPPING       10
#define DB_ID_CTRL            11
#define DB_ROLE_MAPPING       12
#define DB_SHENQI             13
#define DB_TREASURE			  14
#define DB_BAG_EXTEND         15
#define DB_FORGE              16
#define DB_ATTR				  17
#define	DB_ROLE_ATTR		  18
#define DB_ACTIVE			  19

#define MEM_SESSION           99

//DB other
#define KEY_UID_CTRL		      1
#define KEY_RID_CTRL 	          2
#define KEY_TEAM_ID_CTRL		  3
#define KEY_GUILD_ID_CTRL		  4

#define UID_MIN				10000000
#define UID_MAX				2000000000

#define HURT_TYPE_PHYSICAL 0x0001
#define HURT_TYPE_MAGIC 0x0002
#define HURT_TYPE_WIZARD 0x0004
#define HURT_TYPE_ALL 0x0007

#define DEFAULT_SAFEAREA_MAP 1
#define DEFAULT_SAFEAREA_X 87
#define DEFAULT_SAFEAREA_Y 90

#define RATE_ACCURACY  (0.0001)
#define RATE_BASE 10000
#define HIT_RATE_BASE 0.8
#define HIT_RATE_COEFFICIENT 0.2
// 白名-1 	灰名-8372224(0x7FC000) 	红名-65536(0x10000)
#define NAME_COLOR_WHITE -1
#define NAME_COLOR_GRAY 0x666666
#define NAME_COLOR_YELLOW 0x7FC000
#define NAME_COLOR_RED 0xFF0000

#define AI_ACTION_PLAY_TIME 400

//白银VIP时间
#define VIP_BAIYIN_TIME (10*24*3600)
//黄金VIP时间
#define VIP_HUANGJIN_TIME (30*24*3600)
//至尊VIP时间
#define VIP_ZHIZUN_TIME (180*24*3600)
//体验VIP时间
#define VIP_TIYAN_TIME (24*3600)

#define U64_LOW(val) (val & 0X00000000FFFFFFFF)
#define U64_HIGH(val) ((val >> 32) & 0X00000000FFFFFFFF)
#define U32_LOW(val) (val & 0X0000FFFF)
#define U32_HIGH(val) ((val >> 16) & 0X0000FFFF)


#define GET_BIT(a,n)	(a&(1<<n))
#define SET_BIT(a,n)	(a|=(1<<n))
#define CLEAR_BIT(a,n)	(a&=~(1<<n))
#define CFG_MAKE_KEY_FOUR(v1,v2,v3,v4) (((((((v1) << 24) | (v2)))<<16)|(v3<<8))|v4)
#define CFG_MAKE_KEY_THREE(v1,v2,v3) ((((((v1) << 16) | (v2)))<<8)|v3)
#define CFG_MAKE_KEY(v1,v2) (((v1) << 20) | (v2))

//动作音效
#define VOICE_HUMAN_ATTACK 67

#define MAX_EQUIP_COUNT 1000
#define MAX_PRICE 2100000000

#define MIN_TRADE_LEVEL 35
#define MIN_TALK_WORLD_LEVEL 30
#define MAX_SHORTCUT_IDX 15
#define MAX_ROLE_PER_USER 3
#define HUMAN_RECOVE_INTERVAL 60
#define DROP_EQUIP_BROADCAST_LEVEL 40

//坐骑升级
#define MOUNT_UP_HORNOR 1000
#define MOUNT_UP_HORNOR_EXP 300
#define MOUNT_UP_YB 10
#define MOUNT_UP_YB_EXP 2000
#define MOUNT_UP_BATCH_YB 500
#define MOUNT_UP_BATCH_LOOP 50

//大刀守卫，弓箭守卫
#define MONSTER_BROADSWORD_GUARD 187
#define MONSTER_BOW_ADN_ARROW_GUARD 188

// 活动
#define DRUMS_ARENA_MAP 39

//human状态标记宏
#define CAN_TRANSFER_FORBID_FLAG 0X01
#define DIE_WITHOUT_PUNISH_FLAG 0X02
#define KILL_HUMAN_WITHOUT_PUNISH_FLAG 0X04
#define ENTER_CARBON_FORBID 0X08

#define MAX_DISPLAY_ROLE_LIST_SIZE 3

#define MAX_ATTACK_SPEED 300
#define MAX_MOVE_SPEED 300

#define BUFF_SIZE 2048
#define MAX_DEVIATE_DISTANCE 10

// 禁用加速器参数
#define MAX_ACC_COUNT 30
#define MAX_ACC_INTERVAL 15

//仓库一页最大容量
#define MAX_STORE_COUNT 40
#define MAX_GRID_COUNT 56
#define INIT_BAG_GRID 40
#define INIT_MARKETGRID_COUNT 30

#define MONEY_GOLD					(110010001)
#define MONEY_COIN					(110030001)
#define MONEY_EXP					(120010001)
#define MONEY_REINCARN_EXP			(110080001)
#define MONEY_MAGIC_EXP				(110060001)
#define MONEY_MAGIC_PIECE			(110120001)
#define MONEY_TREASURE_EQUIP		(110110001)
#define MONEY_TREASURE_DIANFENG		(110110003)
#define MONEY_TREASURE_SANJIE		(110110004)

#define IS_MONEY(t)						\
	t == MONEY_GOLD ||					\
	t == MONEY_COIN ||					\
	t == MONEY_REINCARN_EXP ||			\
	t == MONEY_MAGIC_EXP ||				\
	t == MONEY_MAGIC_PIECE ||			\
	t == MONEY_TREASURE_EQUIP ||		\
	t == MONEY_TREASURE_DIANFENG ||		\
	t == MONEY_TREASURE_SANJIE	 		\

#define AP_STAT_STAND			0x1
#define AP_STAT_MOVE			0x2
#define AP_STAT_RIDE			0x4
#define AP_STAT_ZANZEN			0x8
#define AP_STAT_MARKET			0x10
#define AP_STAT_SING			0x20
#define AP_STAT_BATTLE			0x40
#define AP_STAT_DIE				0x80
#define AP_STAT_MOVE_FORBID		0x0100
#define AP_STAT_DIZZY			0x0200
#define AP_STAT_AUTO_BATTLE		0x0400
#define AP_STAT_RETURN_BURN		0x0800
#define AP_STAT_DISABLE_SKILLCD	0x1000
#define AP_STAT_CHALLENGE		0x2000
#define AP_STAT_TRAFFIC			0x4000
#define AP_STAT_COUPLE_ZANZEN	0x8000
#define AP_STAT_BODY_CHANGE		0x10000
#define AP_STAT_SWIMMING		0x20000
#define AP_STAT_KISS_SWIMMING	0x40000
#define AP_STAT_FAST_BATTLE		0x80000
#define AP_STAT_KISS_LAND		0x100000
#define AP_STAT_CORPS_BATTLE	0x200000
#define AP_STAT_CARRIER			0x400000
#define AP_STAT_PASSENGGER		0x800000
#define AP_STAT_DONGFANG		0x1000000
#define AP_STAT_OWN_PET			0x2000000
#define AP_STAT_HERO_FIT		0x4000000
#define AP_STAT_GM				0x8000000
#define AP_STAT_MAX_COUNT		0x10000000

//怪物id最大值
#define ID_MONSTER_MAX 100000
#define ID_START_HUMAN 2000000
#define ID_START_OTHERS 1000000
#define ID_END_OTHERS 2000000

//每次怪物AI驱动扫描的人数
#define MOUNSTER_AI_PER_LOOP 100
//第一攻击者转移时间间隔(s)
#define FIRST_ATTACKER_INTERVAL 6
//攻击伤害值超过第一攻击者多少比例时转移第一攻击者
#define FIRST_ATTACKER_CHANGE 1.2
//怪物AI每次处理的怪物数
#define MONSTER_AI_SCAN_MONSTERS 400
//怪物AI处理一轮最大时长（毫秒）
#define MONSTER_AI_SCAN_MAX_TIME 10

//延迟下线时间(秒)
#define OFFLINE_DELAY 3

//职业定义
#define JOB_SOLIDER 1
#define JOB_MAGIC 2
#define JOB_WIZARD 3

//死亡恢复
#define DIE_RECOVER 0.1

#define MAX_ROLE_COUNT 5




#define NORMAL_RUNE_COUNT 8
#define SPECIAL_RUNE_COUNT 2
#define SPECIAL_RUNE_ID_BASE 100

#define ATTR_DB_ADD(data) \
		{\
			CDataAttr db; \
			DataAttr* pData = (DataAttr*)&data; \
			if(0 != db.AddData(*pData)){\
				error_log("add attr data to db failed");\
			}\
		}

#define ATTR_DB_SET(data) \
		{\
			CDataAttr db; \
			DataAttr* pData = (DataAttr*)&data; \
			if(0 != db.SetData(*pData)){\
				error_log("set attr data to db failed");\
			}\
		}


#define ROLE_ATTR_DB_ADD(data) \
		{\
			CDataRoleAttr db; \
			DataRoleAttr* pData = (DataRoleAttr*)&data; \
			if(0 != db.AddData(*pData)){\
				error_log("add role_attr data to db failed");\
			}\
		}

#define ROLE_ATTR_DB_SET(data) \
		{\
			CDataRoleAttr db; \
			DataRoleAttr* pData = (DataRoleAttr*)&data; \
			if(0 != db.SetData(*pData)){\
				error_log("set role_attr data to db failed");\
			}\
		}



#endif	/* _APP_DEFINE_H_ */
