//AppDefine.h
//20110525	dada	create

#ifndef __APPDEFINE_H__
#define __APPDEFINE_H__

//all config

//server
//dat or xml or dir
#define APP_CONFIG_PATH						"../conf/app_config.xml"
#define APP_DOMAIN_CONFIG_PATH  			"../../pi/conf/domai_config.xml"
#define CONFIG_GATE_RAND_DIR				"/usr/local/monitor_sanguo/data/gate"
/*
#define CONFIG_GATE_RAND_DIR				"gate_rank_dir"
#define CONFIG_QQ_ITEM_INFO					"qq_item_info"
#define CONFIG_PLATFORM_MAPPING 			"platform_mapping"
#define CONFIG_ALL_DATA_LOG_PATH			"all_data_log"
#define CONFIG_ALL_SERVER_BASE_MATCH_PATH	"all_server_base_match_path"
#define CONFIG_ALL_SERVER_PERSON_MATCH_PATH	"all_server_person_match_path"
#define CONFIG_ALL_SERVER_LADDER_PATH		"all_server_ladder_path"
#define CONFIG_ALLS_MATCH_INST_PATH			"all_server_match_instance_path"
#define CONFIG_ALL_SERVER_RANK_PATH			"all_server_rank_path"
#define CONFIG_ALLIANCE_RECHARGE_DATA  		"alliance_recharge_data"
#define CONFIG_XML_PATH 					"xml_path"
#define CONFIG_GM_TH_SHM      				"/data/release/sgonline/data/gm_th.dat"
#define CONFIG_NOISE_SHM      				"/data/release/sgonline/data/noise.dat"
#define CONFIG_STRING_FILTER_DATA 			"string_filter_data"
#define CONFIG_DBC_SERVER					"dbc_server"
#define CONFIG_INIT_ARCHIVE					"init_archive"
#define CONFIG_NPC_DATA						"npc_data"
#define CONFIG_PRIZEMAILTEXT_PATH 			"prizeText"
#define CONFIG_BARBARIANKING_PATH 			"barbarian_king_path"
*/
#define DEFAULT_APP_PATH					"/data/release/sgonline/"
#define CONFIG_QQ_ITEM_INFO					"pi/conf/qq_item_info.xml"
#define CONFIG_PLATFORM_MAPPING 			"pi/conf/platform/platform_mapping.xml"
#define CONFIG_ALL_DATA_LOG_PATH			"datalog/"
#define CONFIG_ALL_SERVER_BASE_MATCH_PATH	"data/basematch.dat"
#define CONFIG_ALL_SERVER_PERSON_MATCH_PATH	"data/personmatch.dat"
#define CONFIG_ALL_SERVER_LADDER_PATH		"data/ladder.dat"
#define CONFIG_ALLS_MATCH_INST_PATH			"data/all_server_mathc_instance/"
#define CONFIG_ALL_SERVER_RANK_PATH			"data/allserverrank.dat"
#define CONFIG_ALLIANCE_RECHARGE_DATA  		"data/alliance_recharge/alliance_recharge.dat"
#define CONFIG_XML_PATH 					"pi/conf/xml/"
#define CONFIG_GM_TH_SHM      				"data/gm_th.dat"
#define CONFIG_NOISE_SHM      				"data/noise.dat"
#define CONFIG_STRING_FILTER_DATA 			"data/stringfilter.dat"
#define CONFIG_DBC_SERVER					"pi/conf/dbc_server.xml"
#define CONFIG_INIT_ARCHIVE					"pi/data/npc/0.dat"
#define CONFIG_NPC_DATA						"pi/data/npc/"
#define CONFIG_PRIZEMAILTEXT_PATH 			"pi/conf/prizeText/language_mapping.xml"
#define CONFIG_BARBARIANKING_PATH 			"data/"
#define ALL_SERVER_GUESS_DATA_PATH 			"data/guess.dat"
#define ALL_SERVER_PERSON_INST_PATH  		"data/personinst.dat"
#define CONFIG_CONSUME_RANK_PATH 			"data/consumerank.dat"
#define CONFIG_ALL_SERVER_NEW_WORLD_BATTLE_DATA		"data/allservernewworldbattle.dat"
#define CONFIG_ALL_SERVER_MAP_PATH			"data/allservermap.dat"
#define CONFIG_ALL_SERVER_MAP_BUFFER_PATH	"data/allservermapbuffer.dat"
#define CONFIG_GVG_MAP_DATA     			"data/gvgmap.dat"   //gvg
#define CONFIG_GVG_ROOM_DATA     			"data/gvgroom.dat"   //gvg
#define EVN_GVG_ROOM_NUM					"GVG_ROOM_NUM"
#define CONFIG_GVG_ROOM_RANK				"webroot/data/gvg/room"
#define CONFIG_PVP_MAP_DATA     			"data/pvpmap.dat"   //pvp
#define CONFIG_PVP_ROOM_DATA     			"data/pvproom.dat"   //pvp
#define EVN_PVP_ROOM_NUM					"PVP_ROOM_NUM"
#define CONFIG_SECRET_MAP_DATA				"data/secretmap.dat"
#define CONFIG_ARMORY_MAP_DATA 				"data/armorymap.dat"
#define CONFIG_FLUCARD_DATA					"data/flucard.dat"
#define CONFIG_TOWER_DEFENCE_DATA			"data/towerdefence.dat"

#define ALL_SERVER_ZONE_A					235
#define ALL_SERVER_ZONE_B					525
//config
#define CONFIG_INDEPEND			"independ"
#define CONFIG_CLIENT_DOMAIN	"client_domain"
#define CONFIG_FB_APP_SECRET "fb_app_secret"
#define CONFIG_FB_APP_ACCESS_TOKEN "fb_app_access_token"
#define CONFIG_FB_RTU_PAYMENTS_TOKEN "fb_rtu_payments_token"
#define CONFIG_FB_PAYMENT_PRODUCT "fb_payment_product"
#define CONFIG_VN_TEL_PNID "vn_tel_pnid"
#define CONFIG_VN_TEL_SGN "vn_tel_sgn"
#define CONFIG_4399_LOGIN_KEY "4399_login_key"
#define CONFIG_4399_PAY_KEY "4399_pay_key"
#define CONFIG_4399_OTHER_KEY "4399_other_key"
#define CONFIG_4399_GAME_NAME "4399_game_name"
#define CONFIG_4399_PAY_IP_1 "4399_pay_ip_1"
#define CONFIG_4399_PAY_IP_2 "4399_pay_ip_2"
#define CONFIG_4399_PAY_IP_3 "4399_pay_ip_3"
#define CONFIG_4399_PAY_IP_4 "4399_pay_ip_4"
#define CONFIG_4399_PAY_IP_5 "4399_pay_ip_5"
#define CONFIG_4399_ADMIN_IP "4399_admin_ip"

#define CONFIG_BAIDU_GAME_NAME	"baidu_game_name"
//not use
#define CONFIG_PLATFORM			"platform_config"
#define CONFIG_LEVEL_RESTRICT 60

//zone
//dat or xml or dir
/*
#define CONFIG_DATA_LOG_PATH			"data_log_path"
#define CONFIG_BUSINESS_LOG_DIR 		"business_log_dir"
#define CONFIG_LOG_PATH					"log_path"
#define CONFIG_MAP_DATA					"map_data"
#define CONFIG_INSTANCE_DATA			"instance_data"
#define CONFIG_BROADCAST_DATA			"broadcast_data"
#define CONFIG_ARENA_DIR				"arena_dir"
#define CONFIG_ALLIANCE_BATTLE_DIR		"alliance_battle_dir"
#define CONFIG_VEDIO_DIR				"vedio_dir"
#define CONFIG_FIGHTING_DATA			"fighting_data"
#define ADMIN_OP_LOG_DIR				"admin_log_dir"
#define CONFIG_WORLDBOSS_DIR			"worldboss_dir"
#define CONFIG_WORLDBOSS_MAP			"worldboss_map"
#define CONFIG_MATCH_DAT_PATH			"match_path"
#define CONFIG_BASE_MATCH_PATH			"base_match_path"
#define CONFIG_PERSON_MATCH_PATH		"person_match_path"
#define CONFIG_DRAGONBALL_DATA			"dragonball_data"
#define CONFIG_LADDER_PATH				"ladder_path"
#define POINTS_RANK              		"points_rank"
#define HUNDREDDAYSACTIVITY_RANK 		"hundreddaysactivity_rank"   //百日消费活动
#define QIXIJIE_PAY_RANK        		"qixijiepay_rank"   //七夕节
#define CONFIG_NOMINATE_ALLIANCE_PATH 	"nominate_alliance_path"
#define CONFIG_BARBARIANINVASION_PATH 	"barbarian_invasion_path"
#define CONFIG_WORLD_DATA   			"world_data"
#define CONFIG_WORLDNPC_DATA   			"worldnpc_data"
#define CONFIG_MYSTICALSHOP_PATH 		"mysticalshop_path"
#define CONFIG_RIVER_PATH 				"river_path"
#define CONFIG_PAYRANK          		"payrank"
#define CONFIG_TOP_TEN_USER_PATH 		"top_ten_user"
#define CONFIG_MATCH_INSTANCE_PATH 		"match_instance_path"
#define CONFIG_NEW_USER_REC_LIST_PATH 	"new_user_rec_list_path"
#define NATIONAL_WAR_RGT        "nationalwar_rgt"   //国战报名
#define GROUPS_FIGHTING         "groups_fighting"   //国战战斗
*/
#define DEFAULT_APP_CONFIG_PATH			"conf/app_config.xml"
#define CONFIG_DATA_LOG_PATH			"datalog/"
#define CONFIG_BUSINESS_LOG_DIR 		"log/business/"
#define CONFIG_LOG_PATH					"log/"
#define CONFIG_MAP_DATA					"data/map.dat"
#define CONFIG_INSTANCE_DATA			"data/instance/"
#define CONFIG_BROADCAST_DATA			"data/broadcast.dat"
#define CONFIG_ARENA_DIR				"data/arena/"
#define CONFIG_ALLIANCE_BATTLE_DIR		"data/alliance_battle/"
#define CONFIG_VEDIO_DIR				"vedio/"
#define ADMIN_OP_LOG_DIR				"adminlog/"
#define CONFIG_WORLDBOSS_DIR			"data/worldboss/"
#define CONFIG_MATCH_DAT_PATH			"data/match.dat"
#define CONFIG_BASE_MATCH_PATH			"data/basematch.dat"
#define CONFIG_PERSON_MATCH_PATH		"data/personmatch.dat"
#define CONFIG_DRAGONBALL_DATA			"data/dragonball.dat"
#define CONFIG_LADDER_PATH				"data/ladder.dat"
#define POINTS_RANK              		"data/points_rank.dat"
#define POINTS_RANK_ALL_SERVER          "data/points_rank_all_server.dat"
#define HUNDREDDAYSACTIVITY_RANK 		"data/hundreddaysactivity_rank.dat"   //百日消费活动
#define QIXIJIE_PAY_RANK        		"data/qixijiepay_rank.dat"   //七夕节
#define CONFIG_NOMINATE_ALLIANCE_PATH 	"data/nominate_alliance.dat"
#define CONFIG_BARBARIANINVASION_PATH 	"data/barbarianinvasion.dat"
#define CONFIG_WORLD_DATA   			"data/world_map.dat"
#define CONFIG_WORLDNPC_DATA   			"data/worldnpc.dat"
#define CONFIG_MYSTICALSHOP_PATH 		"data/mystialshop.dat"
#define CONFIG_RIVER_PATH 				"data/River.dat"
#define CONFIG_PAYRANK          		"data/payrank.dat"
#define CONFIG_TOP_TEN_USER_PATH 		"data/TopTenUser.dat"
#define CONFIG_MATCH_INSTANCE_PATH 		"data/match_instance/"
#define CONFIG_NEW_USER_REC_LIST_PATH 	"data/new_user_rec_list.dat"
#define NATIONAL_WAR_RGT        		"data/nationalwar_rgt.dat"   //国战报名
#define GROUPS_FIGHTING         		"data/groups_fighting.dat"   //国战战斗
#define HEQU_ALLIANCE_POINT 			"data/alliance_point.dat"   //合区联盟贡献活动
#define HEQU_WORLD_ATTACK 				"data/world_attack.dat"   //合区攻城拔寨
#define CONFIG_VIP_REBATES				"data/vip_rebates.dat"			// 合区vip返利
#define GUESS_DATA_PATH 				"data/guess.dat"
#define OPEN_AREA_PATH 					"data/openarea.dat"   //开区等级活动
#define CONFIG_NEW_WORLD_DATA   		"data/newworld.dat"
#define CONFIG_DIR_TOOL   				"tools/"
#define PERSON_INST_PATH  				"data/personinst.dat"
#define NEW_LOTTERY_PATH        		"data/new_lottery_data.dat"   //羊年轮盘
#define CONFIG_NEW_WORLD_BATTLE_DATA   	"data/newworldbattle.dat"
#define ACTIVITY_RESTRIC_DATA        	"data/activity_restric.dat"   //限购活动
#define CONFIG_BATTLE_DATA        		"data/battle.dat"   //斗将战场
#define CONFIG_BRAVE_NEW_WORLD_DATA     "data/bravenewworld.dat"   //gvg
#define CONFIG_NEW_MATCH_DATA    		"data/newmatch.dat"
#define CONFIG_BRAVE_NEW_WORLD_BATTLE_DATA     "data/bravenewworldbattle.dat"   //gvg
#define CONFIG_PREDATOR_ACTIVE_PATH 	"data/PredatorActive.dat"
#define DRAGON_SCALE_PATH				"data/dragon_scale.dat"		//龙鳞活动
#define CONFIG_KVK_DATA     			"data/kvk.dat"   //kvk
#define CONFIG_FVF_DATA     			"data/fvf.dat"   //fvf
#define CONFIG_DEMO_DATA     			"data/demo/demo.dat"   //demo

//not use
#define CONFIG_WHITE_LIST		"white_list"
#define CONFIG_ADMIN_LIST		"admin_list"
#define CONFIG_AUTO_LOGIN_URL	"auto_login_url"
//#define CONFIG_DRAGONBALL_ON	"dragonball_on"		//龙珠活动开关，1为打开，否则关闭
#define CONFIG_NEW_SERVER_TS    "new_server_ts"
//config
#define CONFIG_FORBID_USER      		"forbid_user"
#define CONFIG_MIN_WORLDBOSS_BLOOD	"min_worldboss_blood"
#define CONFIG_MAX_WORLDBOSS_BLOOD	"max_worldboss_blood"
#define CONFIG_LOG_LEVEL		"log_level"
#define CONFIG_LOG_NAME			"log_name"
#define CONFIG_LOG_REWIND		"log_rewind"
#define CONFIG_LOG_SIZE			"log_size"
#define CONFIG_LOG_RECORD_SIZE	"log_record_size"
#define CONFIG_TCP_SERVER		"tcp_server"
#define CONFIG_TCP_HOST			"tcp_host"
#define CONFIG_ACCESS_SERVER	"access_server"
#define CONFIG_ZONE_ID			"zoneid"
#define CONFIG_SERVER_ID       "server_id"
//#define CONFIG_AID_START        "aid_start"
//#define CONFIG_UID_MIN          "uid_min"
//#define CONFIG_UID_MAX          "uid_max"
#define CONFIG_NOMENAT_FRIEND_UID "nomenat_friend_uid"
#define CONFIG_ADMIN_UID      "admin_uid"
#define CONFIG_ALLIANCE_EXPENSES "alliance_expenses"
#define CONFIG_DEFAULT_KINGDOM "default_kingdom"
#define CONFIG_FULL "full"
#define CONFIG_ALL_SERVER "all_server"
#define CONFIG_ALLSERVER_PATH "all_server_match_server_path"
#define CONFIG_ALLS_MATCH_SERVER_PATH "cgi/allserverbasematch"
#define CONFIG_ALLS_RANK_PATH "cgi/allserverrank"
#define CONFIG_ALLSERVERRANK_PATH "all_server_rank_server_path"
#define CONFIG_ALLS_MAP_PATH "cgi/allservermap"
//activity ts & type & version
#define CONFIG_OPEN_TS         "open_ts"
#define CONFIG_BARBARIAN_BEGIN_TS "barbarian_begin_ts"
#define CONFIG_BARBARIAN_END_TS   "barbarian_end_ts"
#define CONFIG_PAY_TOTAL_BEGIN_TS "paytotal_begin_ts"
#define CONFIG_PAY_TOTAL_END_TS "paytotal_end_ts"
#define CONFIG_PAY_TOTAL_VERSION "paytotal_version"
#define CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS "payofhundreddays_begin_ts"    //百日消费活动
#define CONFIG_PAY_OF_HUNDRED_DAYS_END_TS "payofhundreddays_end_ts"
#define CONFIG_PAY_OF_HUNDRED_DAYS_VERSION "payofhundreddays_version"
#define CONFIG_PAY_OF_QIXIJIE_BEGIN_TS "payofqixijie_begin_ts"    //七夕节
#define CONFIG_PAY_OF_QIXIJIE_END_TS "payofqixijie_end_ts"
#define CONFIG_PAY_OF_QIXIJIE_PF "payofqixijie_pf"
#define CONFIG_PAY_OF_QIXIJIE_VERSION "payofqixijie_version"
#define CONFIG_PAY_OF_QIXIJIE_OPEN_SECOND "payofqixijie_open_second"
//幸运转盘
#define CONFIG_MERRYSOULS_BEGIN_TS "merrysoulsbegin_ts"    
#define CONFIG_MERRYSOULS_END_TS "merrysoulsend_ts"
#define CONFIG_MERRYSOULS_VERSION "merrysouls_version"
//活动平台配置
#define CONFIG_MERRYSOULS_PF "merrysouls_pf"
#define CONFIG_PAY_OF_HUNDRED_DAYS_PF "payofhundreddays_pf"
#define CONFIG_PAY_TOTAL_PF "paytotal_pf"
#define CONFIG_POINTS_PF "points_pf"
#define CONFIG_PAYRANK_PF "payrank_pf"
//充值返金type
#define CONFIG_PAYTOTAL_RETURN_TYPE "paytotal_return_type"

#define CONFIG_PAYTOTAL_MIDDLE_TS "paytotal_middle_ts"
//双倍经验
#define CONFIG_DOUBLE_EXPERIENCE_BEGIN_TS "double_experience_begin_ts"
#define CONFIG_DOUBLE_EXPERIENCE_END_TS "double_experience_end_ts"
//发财树双倍
#define CONFIG_MONEYTREE_BEGIN_TS "moneytree_begin_ts"
#define CONFIG_MONEYTREE_END_TS "moneytree_end_ts"
#define CONFIG_MONEYTREE_PF "moneytree_pf"
//南蛮双倍
#define CONFIG_DOUBLE_BARBARIAN_BEGIN "double_barbarian_begin"
#define CONFIG_DOUBLE_BARBARIAN_END   "double_barbarian_end"
#define CONFIG_NANMAN_PF "nanman_pf"
//端午
#define CONFIG_GATE_ZONGZI_BEGIN_TS "gate_zongzi_begin_ts"
#define CONFIG_GATE_ZONGZI_END_TS "gate_zongzi_end_ts"
#define CONFIG_GATE_ZONGZI_PF "gate_zongzi_pf"
//21点
#define CONFIG_DIANJIANG_BEGIN_TS "dianjiang_begin_ts"
#define CONFIG_DIANJIANG_END_TS "dianjiang_end_ts"
#define CONFIG_DIANJIANG_VER "dianjiang_ver"
#define CONFIG_DIANJIANG_PF "dianjiang_pf"
//月度礼包
#define CONFIG_MONTH_LIBAO_BEGIN_TS "month_libao_begin_ts"
#define CONFIG_MONTH_LIBAO_END_TS "month_libao_end_ts"
#define CONFIG_MONTH_LIBAO_VER "month_libao_ver"
#define CONFIG_MONTH_LIBAO_PF "month_libao_pf"
//普天同庆
#define CONFIG_VIPBAG_BEGIN_TS "vipbag_begin_ts"
#define CONFIG_VIPBAG_END_TS "vipbag_end_ts"
#define CONFIG_VIPBAG_VER "vipbag_ver"
#define CONFIG_VIPBAG_PF "vipbag_pf"
//步步为赢
#define CONFIG_TREASURE_BEGIN_TS "treasure_hunt_begin_ts"
#define CONFIG_TREASURE_END_TS "treasure_hunt_end_ts"
#define CONFIG_TREASURE_VER "treasure_hunt_ver"
#define CONFIG_TREASURE_PF "treasure_hunt_pf"
//团购
#define CONFIG_TUANGOU_BEGIN_TS "tuangou_begin_ts"
#define CONFIG_TUANGOU_END_TS "tuangou_end_ts"
#define CONFIG_TUANGOU_VER "tuangou_ver"
#define CONFIG_TUANGOU_PF "tuangou_pf"
//欢乐卡牌
#define CONFIG_HAPPYCARD_BEGIN_TS "happycard_begin_ts"
#define CONFIG_HAPPYCARD_END_TS "happycard_end_ts"
#define CONFIG_HAPPYCARD_VER "happycard_ver"
#define CONFIG_HAPPYCARD_PF "happycard_pf"
//摸金
#define CONFIG_TOMB_TREASURE_BEGIN_TS "tomb_treasure_begin_ts"
#define CONFIG_TOMB_TREASURE_END_TS "tomb_treasure_end_ts"
#define CONFIG_TOMB_TREASURE_VER "tomb_treasure_ver"
#define CONFIG_TOMB_TREASURE_PF "tomb_treasure_pf"
//合区活动
#define CONFIG_HEQU_ACTIVITY_BEGIN_TS "hequ_activity_begin_ts"
#define CONFIG_HEQU_ACTIVITY_END_TS "hequ_activity_end_ts"
#define CONFIG_HEQU_ACTIVITY_VER "hequ_activity_ver"
#define CONFIG_HEQU_ACTIVITY_PF "hequ_activity_pf"

//洗练石活动
#define CONFIG_ACTIVITY_DIG_STONE_B_TS "activity_dig_stone_b_ts"
#define CONFIG_ACTIVITY_DIG_STONE_E_TS "activity_dig_stone_e_ts"
#define CONFIG_ACTIVITY_DIG_STONE_VER "activity_dig_stone_ver"
#define CONFIG_ACTIVITY_DIG_STONE_PF "activity_dig_stone_pf"

//武魂打折活动
#define CONFIG_ACTIVITY_WUHUN_B_TS "activity_wuhun_b_ts"
#define CONFIG_ACTIVITY_WUHUN_E_TS "activity_wuhun_e_ts"
#define CONFIG_ACTIVITY_WUHUN_VER "activity_wuhun_ver"
#define CONFIG_ACTIVITY_WUHUN_PF "activity_wuhun_pf"

//中秋活动
#define CONFIG_ACTIVITY_MOONCAKE_B_TS "activity_mooncake_b_ts"
#define CONFIG_ACTIVITY_MOONCAKE_E_TS "activity_mooncake_e_ts"
#define CONFIG_ACTIVITY_MOONCAKE_VER "activity_mooncake_ver"
#define CONFIG_ACTIVITY_MOONCAKE_PF "activity_mooncake_pf"

//珍宝阁
#define CONFIG_ACTIVITY_ZHENBAOGE_B_TS "activity_zhenbaoge_b_ts"
#define CONFIG_ACTIVITY_ZHENBAOGE_E_TS "activity_zhenbaoge_e_ts"
#define CONFIG_ACTIVITY_ZHENBAOGE_VER "activity_zhenbaoge_ver"
#define CONFIG_ACTIVITY_ZHENBAOGE_PF "activity_zhenbaoge_pf"
#define CONFIG_ACTIVITY_ZHENBAOGE_TYPE "activity_zhenbaoge_type"

//小R(SR small R)充值返利
#define CONFIG_SR_CHARGE_REBATES_BEGIN_TS "sr_charge_rebates_begin_ts"
#define CONFIG_SR_CHARGE_REBATES_END_TS "sr_charge_rebates_end_ts"
#define CONFIG_SR_CHARGE_REBATES_VER "sr_charge_rebates_ver"
#define CONFIG_SR_CHARGE_REBATES_PF "sr_charge_rebates_pf"

//大R(LR Large R)充值返利
#define CONFIG_LR_CHARGE_REBATES_BEGIN_TS "lr_charge_rebates_begin_ts"
#define CONFIG_LR_CHARGE_REBATES_END_TS "lr_charge_rebates_end_ts"
#define CONFIG_LR_CHARGE_REBATES_VER "lr_charge_rebates_ver"
#define CONFIG_LR_CHARGE_REBATES_PF "lr_charge_rebates_pf"

//临时强化石幸运石活动
#define CONFIG_ACTIVITY_SNAP_STONE_B_TS "activity_snap_stone_b_ts"
#define CONFIG_ACTIVITY_SNAP_STONE_E_TS "activity_snap_stone_e_ts"
#define CONFIG_ACTIVITY_SNAP_STONE_VER "activity_snap_stone_ver"
#define CONFIG_ACTIVITY_SNAP_STONE_PF "activity_snap_stone_pf"

//临时兵书活动
#define CONFIG_ACTIVITY_SNAP_BINGSHU_B_TS "activity_snap_bingshu_b_ts"
#define CONFIG_ACTIVITY_SNAP_BINGSHU_E_TS "activity_snap_bingshu_e_ts"
#define CONFIG_ACTIVITY_SNAP_BINGSHU_VER "activity_snap_bingshu_ver"
#define CONFIG_ACTIVITY_SNAP_BINGSHU_PF "activity_snap_bingshu_pf"

//羊年轮盘抽奖
#define CONFIG_ACTIVITY_NEW_LOTTERY_B_TS "activity_new_lottery_b_ts"
#define CONFIG_ACTIVITY_NEW_LOTTERY_E_TS "activity_new_lottery_e_ts"
#define CONFIG_ACTIVITY_NEW_LOTTERY_VER "activity_new_lottery_ver"
#define CONFIG_ACTIVITY_NEW_LOTTERY_PF "activity_new_lottery_pf"

//屠魔双倍
#define CONFIG_ACTIVITY_TUMO_DOUBLE_B_TS "activity_tumo_double_b_ts"
#define CONFIG_ACTIVITY_TUMO_DOUBLE_E_TS "activity_tumo_double_e_ts"
#define CONFIG_ACTIVITY_TUMO_DOUBLE_VER "activity_tumo_double_ver"
#define CONFIG_ACTIVITY_TUMO_DOUBLE_PF "activity_tumo_double_pf"

//消费排行
#define CONFIG_ACTIVITY_CONSUME_RANK_B_TS "activity_consume_rank_b_ts"
#define CONFIG_ACTIVITY_CONSUME_RANK_E_TS "activity_consume_rank_e_ts"
#define CONFIG_ACTIVITY_CONSUME_RANK_VER "activity_consume_rank_ver"
#define CONFIG_ACTIVITY_CONSUME_RANK_PF "activity_consume_rank_pf"

//临时遁甲活动
#define CONFIG_ACTIVITY_SNAP_DUNJIA_B_TS "activity_snap_dunjia_b_ts"
#define CONFIG_ACTIVITY_SNAP_DUNJIA_E_TS "activity_snap_dunjia_e_ts"
#define CONFIG_ACTIVITY_SNAP_DUNJIA_VER "activity_snap_dunjia_ver"
#define CONFIG_ACTIVITY_SNAP_DUNJIA_PF "activity_snap_dunjia_pf"

//元旦活动
#define CONFIG_ACTIVITY_YUANDAN_B_TS "activity_yuandan_b_ts"
#define CONFIG_ACTIVITY_YUANDAN_E_TS "activity_yuandan_e_ts"
#define CONFIG_ACTIVITY_YUANDAN_VER "activity_yuandan_ver"
#define CONFIG_ACTIVITY_YUANDAN_PF "activity_yuandan_pf"

//临时魂石宝石活动
#define CONFIG_ACTIVITY_GEM_STONE_B_TS "activity_gem_stone_b_ts"
#define CONFIG_ACTIVITY_GEM_STONE_E_TS "activity_gem_stone_e_ts"
#define CONFIG_ACTIVITY_GEM_STONE_VER "activity_gem_stone_ver"
#define CONFIG_ACTIVITY_GEM_STONE_PF "activity_gem_stone_pf"
#define CONFIG_ACTIVITY_GEM_STONE_TYPE "activity_gem_stone_type"

//镜像活动
#define CONFIG_ACTIVITY_MIRROR_BEGIN_TS "activity_mirror_begin_ts"
#define CONFIG_ACTIVITY_MIRROR_END_TS "activity_mirror_end_ts"
#define CONFIG_ACTIVITY_MIRROR_VER "activity_mirror_ver"
#define CONFIG_ACTIVITY_MIRROR_PF "activity_mirror_pf"
#define CONFIG_ACTIVITY_MIRROR_TYPE "activity_mirror_type"

//多人镜像
#define CONFIG_ACTIVITY_FAIRYLAND_BEGIN_TS "activity_fairyland_begin_ts"
#define CONFIG_ACTIVITY_FAIRYLAND_END_TS "activity_fairyland_end_ts"
#define CONFIG_ACTIVITY_FAIRYLAND_VER "activity_fairyland_ver"
#define CONFIG_ACTIVITY_FAIRYLAND_PF "activity_fairyland_pf"

//限购活动
#define CONFIG_ACTIVITY_RESTRICTION_B_TS "activity_restriction_b_ts"
#define CONFIG_ACTIVITY_RESTRICTION_E_TS "activity_restriction_e_ts"
#define CONFIG_ACTIVITY_RESTRICTION_VER "activity_restriction_ver"
#define CONFIG_ACTIVITY_RESTRICTION_PF "activity_restriction_pf"

//聚宝盆
#define CONFIG_ACTIVITY_TRE_BOWL_B_TS "activity_tre_bowl_b_ts"
#define CONFIG_ACTIVITY_TRE_BOWL_E_TS "activity_tre_bowl_e_ts"
#define CONFIG_ACTIVITY_TRE_BOWL_VER "activity_tre_bowl_ver"
#define CONFIG_ACTIVITY_TRE_BOWL_PF "activity_tre_bowl_pf"

//百宝箱充值抽奖
#define CONFIG_ACTIVITY_GALLERY_BEGIN_TS "activity_gallery_begin_ts"
#define CONFIG_ACTIVITY_GALLERY_END_TS "activity_gallery_end_ts"
#define CONFIG_ACTIVITY_GALLERY_VER "activity_gallery_ver"
#define CONFIG_ACTIVITY_GALLERY_PF "activity_gallery_pf"
#define CONFIG_ACTIVITY_GALLERY_TYPE "activity_gallery_type"

//充值联盟为单位的活动
#define CONFIG_ALLIANCE_RECHARGE_BEGIN_TS "alliance_recharge_begin_ts"
#define CONFIG_ALLIANCE_RECHARGE_END_TS "alliance_recharge_end_ts"
#define CONFIG_ALLIANCE_RECHARGE_VER "alliance_recharge_ver"
#define CONFIG_ALLIANCE_RECHARGE_PF "alliance_recharge_pf"
#define CONFIG_ALLIANCE_RECHARGE_TYPE "alliance_recharge_type"
//蓝钻充值活动
#define CONFIG_VIP_CHARGE_BEGIN_TS "vip_charge_begin_ts"
#define CONFIG_VIP_CHARGE_END_TS "vip_charge_end_ts"
#define CONFIG_VIP_CHARGE_PF "vip_charge_pf"
#define CONFIG_VIP_CHARGE_VER "vip_charge_version"
#define CONFIG_VIP_CHARGE_TYPE "vip_charge_type"
#define CONFIG_POINTS_BEGIN_TS "points_begin_ts"
#define CONFIG_POINTS_END_TS   "points_end_ts"
#define CONFIG_POINTS_VERSION   "points_rank_version"
#define CONFIG_MYSTICALSHOP_RANGE_TS "mysticalshop_range_time"
#define CONFIG_PAYRANK_BEGIN_TS "payrank_begin_ts"
#define CONFIG_PAYRANK_END_TS   "payrank_end_ts"
#define CONFIG_PAYRANK_VERSION   "payrank_version"
#define CONFIG_PAYRANK_TYPE   "payrank_type"
#define CONFIG_DRAGONBALL_ACTIVITY_TS "dragon_activity_ts"
#define CONFIG_SUNCE_BEGIN_TS "sunce_begin_ts"
#define CONFIG_SUNCE_END_TS "sunce_end_ts"

//武魂强化返道具活动
#define CONFIG_PART_STONE_BEGIN_TS "part_stone_begin_ts"
#define CONFIG_PART_STONE_END_TS "part_stone_end_ts"
#define CONFIG_PART_STONE_VER "part_stone_ver"
#define CONFIG_PART_STONE_PF "part_stone_pf"

//老用户召回活动
#define CONFIG_OLD_USER_BEGIN_TS "old_user_begin_ts"
#define CONFIG_OLD_USER_END_TS "old_user_end_ts"
#define CONFIG_OLD_USER_VER "old_user_ver"
#define CONFIG_OLD_USER_PF "old_user_pf"

//12款刷将活动
#define CONFIG_REFRESH_HERO_12_BEGIN_TS "refresh_hero_12_begin_ts"
#define CONFIG_REFRESH_HERO_12_END_TS "refresh_hero_12_end_ts"
#define CONFIG_REFRESH_HERO_12_VER "refresh_hero_12_ver"
#define CONFIG_REFRESH_HERO_12_PF "refresh_hero_12_pf"
#define CONFIG_REFRESH_HERO_12_TYPE "refresh_hero_12_type"

//全服砸罐子
#define CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS	"activity_hammerhit_allserver_b_ts"
#define CONFIG_HAMMERHIT_ALLSERVER_END_TS	"activity_hammerhit_allserver_e_ts"
#define CONFIG_HAMMERHIT_ALLSERVER_VER		"activity_hammerhit_allserver_ver"

//类攻城掠夺活动
#define CONFIG_PREDATOR_BEGIN_TS 	"cfg_predator_active_begin_ts"
#define CONFIG_PREDATOR_END_TS 		"cfg_predator_active_end_ts"
#define CONFIG_PREDATOR_VERSION		"cfg_predator_active_version"
#define CONFIG_PREDATOR_PLATFORM	"cfg_predator_active_platform"

//龙鳞活动
#define CONFIG_ACTIVITY_DRAGON_SCALE_B_TS "activity_dragon_scale_b_ts"
#define CONFIG_ACTIVITY_DRAGON_SCALE_E_TS "activity_dragon_scale_e_ts"
#define CONFIG_ACTIVITY_DRAGON_SCALE_VER "activity_dragon_scale_ver"
#define CONFIG_ACTIVITY_DRAGON_SCALE_PF "activity_dragon_scale_pf"

//海底寻宝活动
#define CONFIG_SMASHEGG_BEGIN_TS 	"activity_smash_egg_begin_ts"
#define CONFIG_SMASHEGG_END_TS 		"activity_smash_egg_end_ts"
#define CONFIG_SMASHEGG_VERSION		"activity_smash_egg_ver"
#define CONFIG_SMASHEGG_PLATFORM	"activity_smash_egg_pf"

//CoralActive 公会建设活动  珊瑚
#define CONFIG_CORAL_ACTIVE_BEGIN_TS 	"activity_coral_begin_ts"
#define CONFIG_CORAL_ACTIVE_END_TS 		"activity_coral_end_ts"
#define CONFIG_CORAL_ACTIVE_VERSION 	"activity_coral_version"

//许愿树活动
#define CONFIG_WISHTREE_BEGIN_TS 	"activity_wish_tree_begin_ts"
#define CONFIG_WISHTREE_END_TS 		"activity_wish_tree_end_ts"
#define CONFIG_WISHTREE_VERSION	"activity_wish_tree_ver"
#define CONFIG_WISHTREE_PLATFORM	"activity_wish_tree_pf"

//DB
//对应DBC端口号和共享内存号为39100+ID
#define DB_USER_MAPPING		1
#define DB_ID_CTRL			2
#define DB_BLACK_USER       3
#define DB_EXCHANGE_CODE    4
#define DB_GOODS            5
#define DB_MARKET_TASK	    6
#define DB_PAY_HISTORY		51

#define MEM_SESSION			91
//DB other
#define KEY_UID_CTRL		1
#define KEY_PAY_ID_CTRL 	2
#define KEY_ATTACK_ID_CTRL	3
#define KEY_MESSAGE_ID_CTRL	4
#define KEY_ALLIANCE_ID_CTRL 5
#define KEY_SECINC_ID_CTRL	6
#define KEY_PROMOTION_ID_CTRL     7
#define KEY_EXCHANGE_CODE_ID_CTRL 8

//app define
#define ADMIN_UID			10000000
#define UID_MIN				10000000
#define UID_MAX				2000000000
#define UID_ZONE			500000
#define IsValidUid(uid)		(uid > UID_MIN && uid < UID_MAX)
#define NPC_UID_MIN			1
#define GATE_NPC_UID_MAX	200
#define ATTACK_NPC_1_MAX  	250
#define GATE_NPC_NEW_MAX	400
#define NPC_UID_MAX			500
#define IsNPCUid(uid)		((uid >= NPC_UID_MIN && uid <= NPC_UID_MAX) || (uid >= WORLD_NPC_UID_MIN && uid < ALL_NPC_UID_MAX))
#define IsGateNPCUid(uid)	((uid >= NPC_UID_MIN && uid <= GATE_NPC_UID_MAX) || (uid > ATTACK_NPC_1_MAX && uid <= GATE_NPC_NEW_MAX))
#define IsCityNPCUid(uid)	(uid > GATE_NPC_UID_MAX && uid <= ATTACK_NPC_1_MAX )
#define WORLD_NPC_UID_MIN	70001
#define WORLD_NPC_UID_MAX	70100
#define WUHUJIANG_NPC_UID_MIN	70101
#define WUHUJIANG_NPC_UID_MAX	70200
#define ALL_NPC_UID_MAX		90000
#define IsWuhujiangNPCUid(uid)	(uid >= WUHUJIANG_NPC_UID_MIN && uid < WUHUJIANG_NPC_UID_MAX)
#define IsWorldNPCUid(uid)	(uid >= WORLD_NPC_UID_MIN && uid < WORLD_NPC_UID_MAX)
#define IsOtherNPCUid(uid)	((uid > GATE_NPC_NEW_MAX && uid <= NPC_UID_MAX) || (uid >= WORLD_NPC_UID_MIN && uid < ALL_NPC_UID_MAX))
#define ALLIANCE_ID_NULL	0
#define ALLIANCE_ID_MIN		2000000000
#define ALLIANCE_ID_START	2010000000
#define AID_ZONE			500000
#define IsAllianceId(id)	(id >= ALLIANCE_ID_MIN)
#define IsLegalUid(uid)		(uid >= UID_MIN)
#define ARENA_ID_MIN		10001
#define ARENA_ID_MAX		10015
#define IsValidArenaId(id) (id >= ARENA_ID_MIN && id <= ARENA_ID_MAX)
#define INSTANCE_ID_MIN		20001
#define INSTANCE_ID_MAX		20025
#define IsValidInstanceId(id) (id >= INSTANCE_ID_MIN && id <= INSTANCE_ID_MAX)
#define FIGHTING_ID_MIN		30001
#define FIGHTING_ID_MAX		30001
#define IsValidFightingId(id) (id >= FIGHTING_ID_MIN && id <= FIGHTING_ID_MAX)
#define FIGHT_ARENA_ID_MIN	40001    //擂台
#define FIGHT_ARENA_ID_MAX	40015
#define IsValidFightArenaId(id) (id >= FIGHT_ARENA_ID_MIN && id <= FIGHT_ARENA_ID_MAX)
#define WORLD_BOSS_ID_MIN	50001
#define WORLD_BOSS_ID_MAX	50004
#define IsValidWorldBossId(id)	(id >= WORLD_BOSS_ID_MIN && id <= WORLD_BOSS_ID_MAX)
#define ALLIANCE_BOSS_ID	50005   //帮会屠魔
#define IsValidAllianceBossId(id)	(id == ALLIANCE_BOSS_ID)
#define SESSION_TIME_OUT	3600	//会话超时
typedef vector<unsigned>	UidList;
#define MULTI_BATTLE_ID_MIN 60001
#define MULTI_BATTLE_ID_MAX 60015
#define IsValidMultiBattleId(id) (id >= MULTI_BATTLE_ID_MIN && id <= MULTI_BATTLE_ID_MAX)
#define BASEMATCH_INST_UID	100000
#define BMATCH_INST_ID_MIN	100001
#define BMATCH_INST_ID_MAX	200000
#define IsValidBMatchInstId(id)	(id >= BMATCH_INST_ID_MIN && id < BMATCH_INST_ID_MAX)
#define PERSONMATCH_INST_UID 200000
#define PERSONMATCH_INST_ID_MIN  200001
#define PERSONMATCH_INST_ID_MAX	 220000
#define IsValidPersonMatchId(id) (id >= PERSONMATCH_INST_ID_MIN && id < PERSONMATCH_INST_ID_MAX)
#define ALL_SERVER_BMATCH_INST_ID_MIN	300001
#define ALL_SERVER_BMATCH_INST_ID_MAX	400000
#define IsValidAllServerBMatchInstId(id)	(id >= ALL_SERVER_BMATCH_INST_ID_MIN && id < ALL_SERVER_BMATCH_INST_ID_MAX)
#define ALL_SERVER_PERSONMATCH_INST_ID_MIN	400001
#define ALL_SERVER_PERSONMATCH_INST_ID_MAX	500000
#define IsValidAllServerPersonMatchId(id)	(id >= ALL_SERVER_PERSONMATCH_INST_ID_MIN && id < ALL_SERVER_PERSONMATCH_INST_ID_MAX)
#define ALLIANCE_BATTLE_ID_MIN		90000
#define ALLIANCE_BATTLE_ID_MAX		99999
#define IsValidAllianceBattleId(id) (id >= ALLIANCE_BATTLE_ID_MIN && id <= ALLIANCE_BATTLE_ID_MAX)

#define IsValidWorldType(type) (type >=0 && type < 20)
#define MAX_WORLD_NPC_COUNT 10000

#define NEW_USER_CASH		90	//新用户钻石数
#define NEW_USER_COINS		0  //新用户金币数
#define NEW_USER_R1			12000
#define NEW_USER_R1_MAX		100000
#define NEW_USER_R2			12000
#define NEW_USER_R2_MAX		100000
#define NEW_USER_R3			12000
#define NEW_USER_R3_MAX		100000
#define NEW_USER_R4			12000
#define NEW_USER_R4_MAX		100000
#define NEW_USER_R5			0
#define NEW_USER_R5_MAX		0
#define NEW_USER_RK			5000
#define TOTORIAL_FINISH		10000
#define TRIBUTE_INTERVAL	(3*3600)
#define NEW_DAILY_GCBASE	200
#define DAILY_GCBASE		0
#define DAILY_NEW_GCBASE	40
#define GCBASE_LIMIT		300
#define ONLINE_TIMEOUT		60	//在线冷却时间
#define ATTACK_TIMEOUT		60	//攻击冷却时间
#define BATTLE_TIMEOUT		60	//pve活动保护冷却时间
#define ATTACK_MAX_TIME		360	//最大进攻时间
//#define ATTACK_PRO_TIME		665	//被攻击保护10分钟，别人不能攻击  ralf 20141225
#define ATTACK_PRO_TIME		900
#define DRAGON_BALL_PROTECT 300
#define DEFEND_MAX_TIME		1800 //最大进攻时间
#define SUBBASE_PROTECTED_LEVEL_1 (3600 * 6)
#define SUBBASE_PROTECTED_LEVEL_2 (3600 * 12)

#define ATTACK_HISTORY_TIME	(14*24*60*60)	//进攻日志时间
#define MAX_ATTACK_HISTORY	66	//最大进攻历史数
#define TRUCE_TIME			(7*24*3600)
#define NEW_USER_PROTECT	(3*60*60)	//新手保护时间
#define DAMAGE_PROTECT_LV1	(18*60*60)	//破坏保护时间1
#define DAMAGE_PROTECT_LV2	(36*60*60)	//破坏保护时间2
#define CON_PROTECT_TIME	3600		//连续被攻击保护时间
#define GET_ALLIANCE_COUNT	10	//每次取联盟数
#define WORLD_OCCUPT_NEW_PROTECT_TIME  (3600)
#define ALLIANCE_ACTIVE_COUNT 10	//联盟动态数
#define ALLIANCE_MEMBER_ATTACK_COUNT 10	//联盟成员被攻击记录数
#define ALLIANCE_ENEMY_TIME (1 * 7 * 24 * 60 * 60)	//联盟仇敌记录时间
#define GET_EMAIL_TIME_LIMIT (2 * 31 * 24 * 60 * 60)

#define IsOnlineUser(t)		(Time::GetGlobalTime()<ONLINE_TIMEOUT+(t))
#define IsInProtect(t)		(Time::GetGlobalTime()<(t))
#define IsBeingAttacked(t)	(Time::GetGlobalTime()<ATTACK_TIMEOUT+(t))
#define IsBattle(t)			(Time::GetGlobalTime()<BATTLE_TIMEOUT+(t))
#define IsAttackFinished(t)	(Time::GetGlobalTime()>ATTACK_MAX_TIME+(t))
#define IsValidWorldPos(worldpos) (((worldpos / 1000) >=1) && ((worldpos / 1000) <=500) && ((worldpos % 1000 >=1) && ((worldpos % 1000) <= 500)))
#define IsDragonBallProtectFinished(t)	(Time::GetGlobalTime()<DRAGON_BALL_PROTECT+(t))
#define IsDefendFinished(t)	(Time::GetGlobalTime()>DEFEND_MAX_TIME+(t))
//session
#define SESSION_DATA		"data"

//error
#define KEY_RESULT			"error"
#define KEY_ERROR_MESSAGE	"errMsg"
#define KEY_PARAMS			"params"

#define SET_NPC_BIT(data, npcId)	data[(npcId-1)/8] |= (1<<(npcId-1)%8)
#define CLEAR_NPC_BIT(data, npcId)	data[(npcId-1)/8] &= ~(1<<(npcId-1)%8)
#define IS_SET_NPC_BIT(data, npcId)	data[(npcId-1)/8] & (1<<(npcId-1)%8)

//exchange code
#define CODE_SIZE 12

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

enum LoadType
{
	LT_LOGIN,		//登录建造
	LT_BUILD,		//建造
	LT_SUBBASE,		//分基地建造
	LT_DEFEND,		//本基地战斗
	LT_VIEW, 		//查看
	LT_ATTACK,		//攻击
	LT_RANK,		//攻打副本的竞赛
	LT_CHALLENGE,	//攻打副本的挑战
	LT_SPORTS,		//第三方竞技场
	LT_REPLAY,		//录像
	LT_DRAGON,		//绣球
	LT_LADDER,		//攻打副本的竞技场
	LT_NEW_WORLD,	//gvg
	LT_GVG,			//gvg

	LT_UNKNOW
};

enum NewActType
{
	NAT_MOONCAKE_1 				= 1,//中秋活动 1
	NAT_MOONCAKE_2 				= 2,//中秋活动 2
	NAT_ZHENBAOGE				= 3,//珍宝阁
	NAT_NEWWORLD_MISSION_1		= 4,//国家任务1
	NAT_RANK_BATTLE_1			= 5,//段位赛1
	NAT_RANK_BATTLE_2			= 6,//段位赛2
	NAT_HUFU					= 7,//虎符商城
	NAT_CAIHUA					= 8,//彩花商店
	NAT_NEWWORLD_MISSION_2		= 9,//国家任务2
	NAT_NEWWORLD_SOHP			= 10,//国战商店
	NAT_YUANDAN_SOHP			= 11,//元旦商店
	NAT_LINSHI_BINGSHU			= 12,//临时兵书
	NAT_LINSHI_DUNJIA			= 13,//临时遁甲
	NAT_JIFEN_DUIHUAN			= 14,//积分兑换
	NAT_XINCHUN_HONGBAO			= 15,//新春红包
	NAT_TURN_TABLE				= 16,//新春转盘
	NAT_BASE_LOCATION			= 17,//建筑布局
	NAT_LIMIT_BUY				= 18,//限时抢购
	NAT_FAIRY_BAG				= 19,//福禄仙袋
	NAT_JINGJI_BANZANG			= 20,//竞技场积分商城
	NAT_FETE					= 23,//祭祀
	NAT_LONGLIN					= 27,//龙鳞转盘
	NAT_CHOUJIANG				= 29,//幸运大转盘
	NAT_TOUCH1					= 34,//摸金1
	NAT_TOUCH2					= 53,//摸金2
	NAT_HAMMERHIT_ALLSERVER		= 50,//全服砸罐子
	NAT_DAILY_TASK				= 100,//日常任务
	NAT_R5						= 101,//勋章
	NAT_UNLOCK_1				= 102,//目标系统
	NAT_UNLOCK_2				= 103,//目标系统
	NAT_UNLOCK_3				= 104,//目标系统
	NAT_CORAL					= 106,//珊瑚
	NAT_PIRATE_WARRIOR_THROUGH  = 111, //海盗勇士通关
	NAT_PIRATE_WARRIOR_FIRST	= 112,  //海盗勇士首次通关
	NAT_TECHNOLOGY				= 203,//科技系统
	NAT_RESET_CREDIT_SHOP		= 204,//刷新积分商店
	NAT_REFRESH_LADDR_SHOP		= 209,//刷新海贝商店
	NAT_WORLD_REWARD			= 210,//国战宝箱
	NAT_REFRESH_DIAMOND_SHOP	= 211,//刷新钻石商店
	NAT_VIP_GIFT_BAG			= 212,//vip礼包
	NAT_SECRET_MAP				= 214,//公会藏宝图
	NAT_GUILD_CRAFT_MISSION     = 215,  //公会争霸任务奖励
	NAT_FLUCARD					= 217, 	//福卡
	NAT_TOWER_DEFENCES			= 218,  //塔防闯关
	NAT_TAVERN					= 219,  //酒馆
	NAT_TGPACCESS				= 220,  //TCP接入奖励
	NAT_NEW_DAILY_TASK_REFRESH	= 221,  //新版每日任务
	NAT_NEW_DAILY_TASK_FIRST	= 222,  //新版每日任务详情一组
	NAT_NEW_DAILY_TASK_SECOND	= 223,  //新版每日任务详情二组
	NAT_ACTIVITY_SMASH_EGG		= 224,  //砸蛋
	NAT_CORAL_ACTIVITY			= 225,  //公会活动 珊瑚
	NAT_ACTIVITY_WISH_TREE		= 226,  //许愿树活动
	NAT_MAX
};
#endif	//__APPDEFINE_H__
