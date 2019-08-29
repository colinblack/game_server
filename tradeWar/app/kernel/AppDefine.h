#ifndef _APP_DEFINE_H_
#define _APP_DEFINE_H_

#define CONFIG_BUSINESS_LOG_DIR			"business_log_dir"
#define CONFIG_DBC_SERVER				"dbc_server"
#define CONFIG_DATA_LOG_PATH			"data_log_path"
#define CONFIG_LOG_LEVEL				"log_level"
#define CONFIG_LOG_PATH					"log_path"
#define CONFIG_LOG_NAME					"log_name"
#define CONFIG_LOG_REWIND				"log_rewind"
#define CONFIG_LOG_SIZE					"log_size"
#define CONFIG_LOG_RECORD_SIZE			"log_record_size"
#define CONFIG_STRING_FILTER_DATA 		"string_filter_data"
#define CONFIG_WHITE_LIST       		""

#define APP_CONFIG_PATH					"../conf/app_config.xml"
#define MAP_CONFIG_PATH					"maps_path"
#define RANK_EXP_DATA_PATH				"rank_exp"
#define RANK_COMBAT_DATA_PATH			"rank_combat"
#define RANK_TRANSPORT_DATA_PATH		"rank_transport"
#define NEW_SERVER_DATA_PATH			"new_server_rank"
#define AUTO_TRANSPORT_PATH				"auto_transport"
#define WORLD_BATTLE_PATH				"world_battle"
#define WANBA_GIFT_PATH					"wanba_gift"
#define BOSS_RANK_PATH					"boss_rank"
#define ARENA_RANK_PATH					"arena_rank"
#define ACT_RANK_PATH					"act_rank"

//逻辑配置文件名称
#define CONFIG_LANGUAGE					"language"
#define CONFIG_BUILDING_COMMON 			"sgbuilding"
#define CONFIG_BUILDING_DATA 			"sgbuildingdata"
#define CONFIG_BUILDING_QUANTITY 		"sgbuildingquantity"
#define CONFIG_NPC_BUILDING_DATA 		"gateBuildingData"
#define CONFIG_BUILDING_WALL	 		"wallConfig"
#define CONFIG_HERO_COMMON 				"olhero"
#define CONFIG_HERO_BORN 				"olheroborn"
#define CONFIG_EQUIPMENT_COMMON 		"olequipment"
#define CONFIG_HERO_SOUL	 			"herosoul"
#define CONFIG_TASK	 			        "task"
#define CONFIG_EXP	 			        "expconfig"
#define CONFIG_DEFEND_GATE				"defend_gate"
#define CONFIG_TRADE_GATE				"trade_config"
#define CONFIG_GATE 					"olgateconfig"
#define CONFIG_ACTIVENESS			    "activeness"
#define CONFIG_SKILLS                   "skills"
#define CONFIG_QQ_ITEM_INFO 	 		"qq_item_info"
#define CONFIG_PLATFORM_MAPPING 		"platform_mapping"
#define CONFIG_PLATFORM					"platform_config"
#define CONFIG_SGVIP					"sgvipconfig"
#define CONFIG_SOLDIER					"olsoldier"
#define CONFIG_FETE						"jisi"
#define CONFIG_INVITE					"sginvitegiftconfig"
#define CONFIG_GIFT_BAG					"sggiftbagconfig"
#define CONFIG_HERO_RECRUIT				"herorecruit"
#define CONFIG_GATE_TREASURE			"gatetreasure"
#define CONFIG_RESOURCE_TRANSPORT 		"resource_transport"
#define CONFIG_SHOP						"shop"
#define CONFIG_SHARE					"share"
#define CONFIG_SYS_MSG_DATA				"system_message_data"
#define CONFIG_ON_REPORT				"on_report"
#define CONFIG_MERCHANT_SHIP			"merchant_ship"
#define CONFIG_NPC_PATH					"npc_path"
#define CONFIG_SERVER_CONFIG			"server_config"
#define CONFIG_OPEN_SERVER				"open_server"
#define CONFIG_WANBA_PAY				"wanbapay"
#define CONFIG_RANDOM_QUEST				"randomquest"
#define CONFIG_RECYCLING				"recycling"
#define CONFIG_SEVEN_DAYS				"sevendays"
#define CONFIG_DAILY_SIGN				"dailysign"
#define CONFIG_SPECIAL_DISCOUNT			"specialdiscount"
#define CONFIG_STRONG					"strongconfig"
#define CONFIG_DAILY_BUY				"dailybuy"
#define CONFIG_ACTIVITY_TIME			"act_time"
#define CONFIG_WEIXIN					"weixin"

#define MEM_SESSION			91

//对应DBC端口号和共享内存号为18000+ID
#define DB_USER				1
#define DB_USER_RESOURCE	2
#define DB_USER_STAT		3
#define DB_HERO				4
#define DB_BUILDING			5
#define DB_EQUIPMENT		6
#define DB_TASK 			7
#define DB_GATE				8
#define DB_PAY				9
#define DB_USER_MAPPING     10
#define DB_ID_CTRL			11
#define DB_EMAIL			12
#define DB_VIDEO			13
#define DB_STATE			14
#define DB_ACTIVENESS       15
#define DB_REWARD			16
#define DB_SKILL            17
#define DB_SOLDIER  		18
#define DB_SOCIAL  			19
#define DB_PRETASK			20
#define DB_WORKER			21
#define DB_TASK_MARKET		22
#define DB_DEFEND			23
#define DB_PAY_HISTORY      24
#define DB_TROOPS           25
#define DB_TOWER            26
#define DB_ACHIEVEMENT      27
#define DB_BOAT_ROB_LOG     28
#define DB_BATTLE_GATE      29
#define DB_BOAT				30
#define DB_BOAT_TRAIN		31
#define DB_RANDOM_QUEST		32
#define DB_ACTIVITY			33
#define DB_CHARGE_HISTORY	34
#define DB_GEM_POINT		35
#define DB_BOSS				36
#define DB_ARENA			37
#define DB_ARENA_LOG		38
#define DB_USER_INTERACT	39
#define DB_GUARD			40

//英雄职业定义
#define PROF_ARMY  1		//陆军
#define PROF_AIR   2		//空军
#define PROF_NAVY  3		//海军
#define PROF_ALL   3		//全军

//种族大类定义
#define RACE_TYPE_PLAYER 0      // 玩家
#define RACE_TYPE_HERO 1		// 英雄
#define RACE_TYPE_BUILDING 2	// 建筑
#define RACE_TYPE_EQUIPMENT 3 	// 装备
#define RACE_TYPE_HOSTAGE 4		// 人质
#define RACE_TYPE_PREY 5		// 暗杀对象
#define RACE_TYPE_WORLD_BOSS 6	// 世界BOSS
#define RACE_TYPE_STATION_NPC 7	// 驻守NPC
#define RACE_TYPE_ATTACK_NPC 8	// 进攻NPC
#define RACE_TYPE_SOLDIER 9		// 士兵
#define RACE_TYPE_HERO_CLONE 10 // 分身
#define RACE_TYPE_SUPER_WEAPON 11 //
#define RACE_TYPE_CANNON 12 //

//士兵类型
#define SOLDIER_TYPE_VEHICLE 0
#define SOLDIER_TYPE_ATTACK 1
#define SOLDIER_TYPE_DEFEND 2
#define SOLDIER_TYPE_WEAPON 3

//建筑类型定义
#define BUILDING_ID_BASE 1             //主城
#define BUILDING_ID_RESOURCE_R1 2      //金矿
#define BUILDING_ID_DEFEND_BARRACKS 5  //护卫营
#define BUILDING_ID_WEAPONS 7          //武器铺
#define BUILDING_ID_STORAGE_R2 10      //仓库
#define BUILDING_ID_PUB 14             //酒馆
#define BUILDING_ID_GARAGE 15          //车库
#define BUILDING_ID_WORKSHOP 16        //工坊
#define BUILDING_ID_LABORATORY 19      //实验室
#define BUILDING_ID_ATTACK_BARRACKS 21 //海盗营
#define BUILDING_ID_ALTAR 22           //祭坛
#define BUILDING_ID_STORAGE_R1 37      //金库
#define BUILDING_ID_RESOURCE_R2 39     //工厂

#define IS_VALID_RES_TYPE(type) (type == BUILDING_ID_RESOURCE_R1 || type == BUILDING_ID_RESOURCE_R2)

//建筑type
#define BUILDING_TYPE_STORAGE 1			// 仓库
#define BUILDING_TYPE_RESOURCE 2 		// 资源建筑
#define BUILDING_TYPE_SPECIAL 3			// 特殊建筑
#define BUILDING_TYPE_WALL 4			// 城墙
#define BUILDING_TYPE_SHRINE 5			// 荣誉建筑
#define BUILDING_TYPE_TOWER	6			// 塔
#define BUILDING_TYPE_TRAP 7			// 陷阱
#define BUILDING_TYPE_WUHU 8			// 五虎守护点
#define BUILDING_TYPE_WUHUTOWN 9		// 五虎将主塔
#define BUILDING_TYPE_DECORATION 10		// 装饰建筑

//UID取值范围
#define UID_ADMIN           10000000
#define UID_MIN				10000000
#define UID_MAX				2000000000
#define UID_ZONE			500000
#define ALLIANCE_ID_MIN		1000000
#define ALLIANCE_ID_MAX		10000000
#define IS_VALID_PLAYER_UID(uid) ((uid) > UID_MIN && (uid) < UID_MAX)
#define IS_VALID_ALLIANCE_ID(id) ((id) >= ALLIANCE_ID_MIN && (id) < ALLIANCE_ID_MAX)
#define IS_VALID_NPC_UID(uid) ((uid) < ALLIANCE_ID_MIN && (uid) >= 0)// 有效NPC uid

//ID索引序号
#define KEY_UID_CTRL			1	// UID
#define KEY_EMAIL_ID_CTRL		2	// 邮件ID
#define KEY_ALLIANCE_ID_CTRL	3	// 联盟ID
#define KEY_PAY_HISTORY_ID_CTRL	4	//

//战场实体状态
#define STATE_APPEAR 1
#define STATE_DISAPPEAR 0

//地图坐标点类型
#define MAP_LAND 1
#define MAP_WATER 2
#define MAP_MOUTAIN 3

//奖励状态
#define REWARD_FORBIT 0		//不可领
#define REWARD_AVAILABLE 1	//可领
#define REWARD_ALREADY 2	//已领

//建筑一键恢复花费金币
#define BUILDING_FULL_HP_COST 10

//红心范围
#define MAX_USER_HELP_COUNT 10
#define MIN_USER_HELP_COUNT -10

//排行榜记录长度
#define MAX_RANK_SIZE 100

#define U64_LOW(val) (val & 0X00000000FFFFFFFF)
#define U64_HIGH(val) ((val >> 32) & 0X00000000FFFFFFFF)
#define MAKE64(a,b,c) 	(*((uint64_t*)(&(a)))) = ((uint64_t)(b) << 32) | (c)
#define MAKE32(a,b,c) 	(*((uint32_t*)(&(a)))) = ((uint32_t)(b) << 16) | (c)
#define MAKE_SKILL_ID_64(id,ud,race,skillId)  (*((uint64_t*)(&(id)))) = ((uint64_t)(ud) << 32) | ((uint64_t)(race) << 16)|(skillId)

//第一攻击者转移时间间隔(s)
#define FIRST_ATTACKER_INTERVAL 6

//挂机奖励间隔时间
#define AUTO_REWRAD_INTERVAL 60

//运输队列长度
#define MAX_MERCHANT_NUM 5

struct ResourceInfo {
	uint32_t uid;
	int32_t r1;
	uint32_t r1_max;
	int32_t r2;
	uint32_t r2_max;
	int32_t r3;
	uint32_t r3_max;
	int32_t r4;
	uint32_t r4_max;
	ResourceInfo() :
			uid(0), r1(0), r1_max(0), r2(0), r2_max(0), r3(0), r3_max(0), r4(0), r4_max(0) {
	}
};

struct AwardInfo {
	uint32_t type;
	uint32_t id;
	uint32_t count;
	AwardInfo() {
		type = 0;
		id = 0;
		count = 0;
	}
	inline bool operator==(uint32_t type) const {
		return this->type == type;
	}
	AwardInfo& operator=(const AwardInfo &d) {
		this->type = d.type;
		this->id = d.id;
		this->count = d.count;
		return *this;
	}
	void Clear() {
		type = 0;
		id = 0;
		count = 0;
	}
};

struct Point {
	int x;
	int y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point& operator =(const Point& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
	inline bool operator ==(const Point & other) const {
		return ((this->x == other.x) && (this->y == other.y));
	}
	inline bool operator !=(const Point& other) const {
		return (this->x != other.x) || (this->y != other.y);
	}
};

struct ResourceCost {
	uint32_t r1;		//金币
	uint32_t r2;		//货物
	uint32_t r3;		//
	uint32_t r4;		//
	uint32_t tl;		//体力
	uint32_t p1;		//民忠
	uint32_t p2;		//回收宝箱积分
	uint32_t p3;		//世界战争资源
	ResourceCost() :
			r1(0), r2(0), r3(0), r4(0), tl(0), p1(0), p2(0), p3(0) {
	}
	double sum() const {
		double s = r1 + r2 + r3 + r4;
		return s;
	}
	uint32_t ResSum() const {
		return r1 + r2;
	}
	uint32_t AllSum() {
		return r1 + r2 + r3 + r4 + tl + p1 + p2 + p3;
	}
};

//奖励类型
enum AWARD_TYPE {
	AWARD_TYPE_ITEM = 0,   //物品
	AWARD_TYPE_PEXP = 1,   //玩家经验
	AWARD_TYPE_DIAMOND = 2,   //钻石
	AWARD_TYPE_R1 = 3,   //金币
	AWARD_TYPE_R2 = 4,   //货物
	AWARD_TYPE_R1_RATE = 5,   //金币仓库百分比
	AWARD_TYPE_R2_RATE = 6,   //货物仓库百分比
	AWARD_TYPE_ENERGY = 7,   //体力
	AWARD_TYPE_SOLDIER = 8,   //士兵
	AWARD_TYPE_SKILL = 9,   //法术
	AWARD_TYPE_BOX = 11,  //宝箱
	AWARD_TYPE_LOYAL = 12,  //民忠
	AWARD_TYPE_MAX
};

//装备类型
enum EQUIP_TYPE {
	EQUIP_TYPE_GEM = 7,		//宝石
	EQUIP_TYPE_MAX
};

//排行榜类型
enum RankDataType {
	e_RankDataTypeExp = 1,			// 奖杯
	e_RankDataTypeCombat = 2,		// 军力
	e_RankDataTypeTransport = 3,	// 运输
	e_RankDataTypeMax
};

//开服排行榜类型
enum NEW_SERVER_RANK_TYPE {
	NEW_SERVER_RANK_TYPE_SOLDIER = 1,		//招兵买马
	NEW_SERVER_RANK_TYPE_EXP = 2,			//奖杯比拼
	NEW_SERVER_RANK_TYPE_POWER = 3,			//军力对决
	NEW_SERVER_RANK_TYPE_TRANSPORT = 4,		//商行天下
	NEW_SERVER_RANK_TYPE_CONSUME = 5,		//一掷千金
	NEW_SERVER_RANK_TYPE_GEM = 6,			//符文夺魁
	NEW_SERVER_RANK_TYPE_WORLD_BATTLE = 7,	//世界战争
	NEW_SERVER_RANK_TYPE_COINS = 8,			//金币消耗
	NEW_SERVER_RANK_TYPE_MAX
};

//限时活动排行
enum ACT_RANK_TYPE {
	ACT_RANK_TYPE_SOLDIER = 1,			//招兵买马
	ACT_RANK_TYPE_EXP = 2,				//奖杯比拼
	ACT_RANK_TYPE_POWER = 3,			//军力对决
	ACT_RANK_TYPE_BOAT = 4,				//商行天下
	ACT_RANK_TYPE_CONSUME = 5,			//一掷千金
	ACT_RANK_TYPE_ARENA = 6,			//问鼎巅峰
	ACT_RANK_TYPE_MAX
};

//活动类型
enum ActivityType {
	e_ActivityTypeExpRank = 1,			//开服奖杯榜
	e_ActivityTypePowerRank = 2,		//开服军力榜
	e_ActivityTypeTransportRank = 3,	//开服运输榜
	e_ActivityTypeConsumeRank = 4,		//开服消费榜
	e_ActivityTypeSevenTask = 5,		//开服七天任务
	e_ActivityTypeDailyBuyBag = 6,		//限时大礼包
	e_ActivityTypeDailyChargeEquip = 7,	//每日充值物品
	e_ActivityTypeDailyChargeCash = 8,	//每日充值钻石
	e_ActivityTypeContinueCharge = 9,	//连续充值
	e_ActivityTypeLuckyLottery = 10,	//每日寻宝-转盘
	e_ActivityTypeSoldierRank = 11,		//开服士兵榜
	e_ActivityTypeGemRank = 12,			//开服宝石榜
	e_ActivityTypeCoinsRank = 13,		//开服金币榜
	e_ActivityTypeWorldBattleRank = 14,	//开服世界战争榜
	e_ActivityTypeSevenDayTask = 15,	//七日目标
	e_ActivityTypeSoldierRankNew = 16,	//新招兵买马
	e_ActivityTypeExpRankNew = 17,		//新奖杯比拼
	e_ActivityTypePowerRankNew = 18,	//新军力比拼
	e_ActivityTypeBoatRankNew = 19,		//新商行天下
	e_ActivityTypeConsumeRankNew = 20,	//新一掷千金
	e_ActivityTypeArenaRankNew = 21,	//新问鼎巅峰
	e_ActivityTypeDailyBuyBagNew = 22,	//新限时大礼包
	e_ActivityTypeDChargeEquipNew = 23,	//新每日充值物品
	e_ActivityTypeDChargeCashNew = 24,	//新每日充值钻石
	e_ActivityTypeCChargeNew = 25,		//新连续充值
	e_ActivityTypeMax
};

#endif	//_APP_DEFINE_H_
