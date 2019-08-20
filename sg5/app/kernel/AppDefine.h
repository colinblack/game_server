//AppDefine.h
//20110525	dada	create

#ifndef __APPDEFINE_H__
#define __APPDEFINE_H__

//#define SG_16_VER

//#define SG_USE_CASH

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
#define CONFIG_RECHARGE_RANK_DIR			"data/recharge_rank/"
#define CONFIG_ALL_SERVER_NEW_WORLD_BATTLE_DATA		"data/allservernewworldbattle.dat"
#define CONFIG_NEW_WORLD_ALLIANCE_MAP_DATA 	"data/newworldalliancemap.dat"
#define CONFIG_ALLIANCE_TORCH_DATA 			"data/alliancetorch.dat"
#define CONFIG_NEW_WORLD_ALLIANCE_ROOM_DATA 	"data/newworldallianceroom.dat"
#define EVN_NEW_WORLD_ALLIANCE_ROOM_NUM			"NEW_WORLD_ALLIANCE_ROOM_NUM"
#define CONFIG_MVP_DATA 					"data/mvp.dat"
#define CONFIG_ROTATYTABLEDRAW_DATA 		"data/rotatytabledraw.dat"
#define CONFIG_CHICK_DATA 					"data/chick.dat"
#define CONFIG_ROTATY_FEEDBACKK_DATA		"data/rotatytablefeedback.dat"

//共享内存文件
#define DATA_KING_TREASURE	"data/kingtreasure.dat"
#define DATA_SEQUENCE_CHARGE "data/sequencecharge.dat"

#define ALL_SERVER_ZONE_A					391
#define ALL_SERVER_ZONE_B					704

#define LOCK_MAX 999

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

#define BRAVE_NEW_WORLD_FORT 2  //堡垒科技

#define Has_DemoReform(u, i) (((u>>i) & 0x01) != 0)
#define Set_DemoReform(u, i) u |= (0x01<<i)
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
#define CONFIG_NIANSHOU_DIR				"data/worldboss/"
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
#define DRAGON_SCALE_PATH				"data/dragon_scale.dat"		//龙鳞活动
#define CONFIG_DOUBLE11_PATH			"data/double11.dat"			// 双11活动
#define CONFIG_NEW_MATCH_DATA    		"data/newmatch.dat"
#define CONFIG_ALL_SERVER_MAP_PATH			"data/allservermap.dat"
#define CONFIG_ALL_SERVER_MAP_BUFFER_PATH	"data/allservermapbuffer.dat"
#define CONFIG_CROWD_FUNDING_DATA_PATH			"data/crowdfunding.dat"
#define CONFIG_ALL_SERVER_LORDS_PATH	"data/allserverlords.dat" //至尊榜
#define CONFIG_TOKEN_INTENSIFY_PATH	    "data/token_intensify.dat" //信物强化
#define CONFIG_BRAVE_NEW_WORLD_DATA    	"data/bravenewworld.dat"
#define CONFIG_ALLIANCE_CONSUME_DATA    	"data/allianceconsume.dat"
#define CONFIG_NEWYEAR_ACTIVNE_DATA    	"data/newyearactive.dat"
#define CONFIG_DOUBLE11_2018_PATH			"data/double11_2018.dat"			// 双11活动
#define CONFIG_QINGRENJIE_DATA    	"data/qingrenjie.dat"
#define CONFIG_CHONGBANG_WANGZHE_DATA    	"data/chongbangwangzhe.dat"
#define CONFIG_ZHOUNIANQING_QIANDAO_DATA    	"data/zhounianqing_qiandao.dat"
#define CONFIG_NEWDOUJIANG_DATA    					"data/newdoujiang.dat"
#define CONFIG_BRAVE_NEWWORLD_ACTION				"data/brave_new_action.json"
#define CONFIG_GIVEHELPACTION_DATA		"data/givehelpactionnew.dat"
//百服团购
#define CONFIG_ALLSERVER_GROUPBUYING_PATH "data/allservergroupbuy.dat"
#define CONFIG_QUNXING_DATA     					"data/qunxing.dat"

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
#define CONFIG_ALL_SERVER_RANK "all_server_rank"
#define CONFIG_ALLSERVER_PATH "all_server_match_server_path"
#define CONFIG_ALLS_MATCH_SERVER_PATH "cgi/allserverbasematch"
#define CONFIG_ALLS_RANK_PATH "cgi/allserverrank"
#define CONFIG_ALLSERVERRANK_PATH "all_server_rank_server_path"
#define CONFIG_ALLS_MAP_PATH "cgi/allservermap"
#define CONFIG_CROWD_FUNDING_PATH "cgi/crowdfunding"
#define CONFIG_ALLSERVER_GROUPBUY_PATH  "cgi/groupbuying"
#define CONFIG_MVP_PATH "cgi/mvp"
#define CONFIG_CHICK_PATH "cgi/chick"

//Lords 尊主
//#define CONFIG_ALLSSERVERLORDS_PATH "all_server_lords_path"
#define CONFIG_ALLSERVER_LORDS_CGI "cgi/allserverlords"
//activity ts & type & version
#define CONFIG_OPEN_TS         "open_ts"
#define CONFIG_BARBARIAN_BEGIN_TS "barbarian_begin_ts"
#define CONFIG_BARBARIAN_END_TS   "barbarian_end_ts"
#define CONFIG_PAY_TOTAL_BEGIN_TS "paytotal_begin_ts"
#define CONFIG_PAY_TOTAL_END_TS "paytotal_end_ts"
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


//转盘狂惠
#define CONFIG_ACTIVITY_ROTARY_TABLE_BEGIN_TS "activity_rotary_table_begin_ts"
#define CONFIG_ACTIVITY_ROTARY_TABLE_END_TS "activity_rotary_table_end_ts"
#define CONFIG_ACTIVITY_ROTARY_TABLE_VER "activity_rotary_table_ver"
#define CONFIG_ACTIVITY_ROTARY_TABLE_PF "activity_rotary_table_pf"

//转盘回馈
#define CONFIG_ACTIVITY_ZHUANPANHUIKUI_BEGIN_TS "activity_zhuanpanhuikui_begin_ts"
#define CONFIG_ACTIVITY_ZHUANPANHUIKUI_END_TS "activity_zhuanpanhuikui_end_ts"
#define CONFIG_ACTIVITY_ZHUANPANHUIKUI_VER "activity_zhuanpanhuikui_ver"
#define CONFIG_ACTIVITY_ZHUANPANHUIKUI_PF "activity_zhuanpanhuikui_pf"

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

//充值排行
#define CONFIG_ACTIVITY_RECHARGE_RANK_B_TS "activity_recharge_rank_b_ts"
#define CONFIG_ACTIVITY_RECHARGE_RANK_E_TS "activity_recharge_rank_e_ts"
#define CONFIG_ACTIVITY_RECHARGE_RANK_VER "activity_recharge_rank_ver"
#define CONFIG_ACTIVITY_RECHARGE_RANK_PF "activity_recharge_rank_pf"

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
#define CONFIG_ACTIVITY_YUANDAN_TYPE "activity_yuandan_type"

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

//塔楼外传
#define CONFIG_TOWER_ACTIVITY_BEGIN_TS "activity_tower_begin_ts"
#define CONFIG_TOWER_ACTIVITY_END_TS "activity_tower_end_ts"
#define CONFIG_TOWER_ACTIVITY_VER "activity_tower_ver"
#define CONFIG_TOWER_ACTIVITY_PF "activity_tower_pf"

//信物强化
#define CONFIG_TOKEN_INTENSIFY_BEGIN_TS "activity_token_intensify_begin_ts"
#define CONFIG_TOKEN_INTENSIFY_END_TS 	"activity_token_intensify_end_ts"
#define CONFIG_TOKEN_INTENSIFY_VER 		"activity_token_intensify_ver"
#define CONFIG_TOKEN_INTENSIFY_PF 	 	"activity_token_intensify_pf"

//世间秘宝
#define CONFIG_WORLD_TREASURE_BEGIN_TS 	"activity_world_treasure_begin_ts"
#define CONFIG_WORLD_TREASURE_END_TS 	"activity_world_treasure_end_ts"
#define CONFIG_WORLD_TREASURE_VER		"activity_world_treasure_ver"
#define CONFIG_WORLD_TREASURE_PF		"activity_world_treasure_pf"

//武魂回馈
#define CONFIG_SOUL_FEEDBACK_BEGIN_TS	"activity_soul_feedback_begin_ts"
#define CONFIG_SOUL_FEEDBACK_END_TS		"activity_soul_feedback_end_ts"
#define CONFIG_SOUL_FEEDBACK_VER		"activity_soul_feedback_ver"
#define CONFIG_SOUL_FEEDBACK_PF			"activity_soul_feedback_pf"

//觉醒回馈
#define CONFIG_AWAKEN_FEEDBACK_BEGIN_TS "activity_awaken_feedback_begin_ts"
#define CONFIG_AWAKEN_FEEDBACK_END_TS	"activity_awaken_feedback_end_ts"
#define CONFIG_AWAKEN_FEEDBACK_VER		"activity_awaken_feedback_ver"
#define CONFIG_AWAKEN_FEEDBACK_PF		"activity_awaken_feedback_pf"

//铸魂打折
#define CONFIG_CAST_SOUL_BEGIN_TS 		"activity_cast_soul_begin_ts"
#define CONFIG_CAST_SOUL_END_TS			"activity_cast_soul_end_ts"
#define CONFIG_CAST_SOUL_VER			"activity_cast_soul_ver"
#define CONFIG_CAST_SOUL_PF				"activity_cast_soul_pf"

//宝石折扣
#define CONFIG_GEM_DISCOUNT_BEGIN_TS	"activity_gem_discount_begin_ts"
#define CONFIG_GEM_DISCOUNT_END_TS		"activity_gem_discount_end_ts"
#define CONFIG_GEM_DISCOUNT_VER			"activity_gem_discount_ver"
#define CONFIG_GEM_DISCOUNT_PF			"activity_gem_discount_pf"


//百宝箱充值抽奖
#define CONFIG_ACTIVITY_GALLERY_BEGIN_TS "activity_gallery_begin_ts"
#define CONFIG_ACTIVITY_GALLERY_END_TS "activity_gallery_end_ts"
#define CONFIG_ACTIVITY_GALLERY_VER "activity_gallery_ver"
#define CONFIG_ACTIVITY_GALLERY_PF "activity_gallery_pf"
#define CONFIG_ACTIVITY_GALLERY_TYPE "activity_gallery_type"
#define CONFIG_ACTIVITY_GALLERY_ITEM 20

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

//造化阁
#define CONFIG_ZAOHUA_BEGIN_TS "activity_zaohua_begin_ts"
#define CONFIG_ZAOHUA_END_TS "activity_zaohua_end_ts"
#define CONFIG_ZAOHUA_VER "activity_zaohua_ver"
#define CONFIG_ZAOHUA_PF "activity_zaohua_pf"

//特卖
#define CONFIG_TEMAI_BEGIN_TS "activity_temai_begin_ts"
#define CONFIG_TEMAI_END_TS "activity_temai_end_ts"
#define CONFIG_TEMAI_VER "activity_temai_ver"
#define CONFIG_TEMAI_PF "activity_temai_pf"

//卖资源
#define CONFIG_ZIYUAN_BEGIN_TS "activity_ziyuan_begin_ts"
#define CONFIG_ZIYUAN_END_TS "activity_ziyuan_end_ts"
#define CONFIG_ZIYUAN_VER "activity_ziyuan_ver"
#define CONFIG_ZIYUAN_PF "activity_ziyuan_pf"

// 点将台
#define CONFIG_DIANJIANGTAI_BEGIN_TS		"activity_dianjiangtai_begin_ts"
#define CONFIG_DIANJIANGTAI_END_TS		"activity_dianjiangtai_end_ts"
#define CONFIG_DIANJIANGTAI_VER			"activity_dianjiangtai_ver"
#define CONFIG_DIANJIANGTAI_PF			"activity_dianjiangtai_pf"

// 至尊洗练
#define CONFIG_ZHIZUN_BEGIN_TS		"activity_zhizun_begin_ts"
#define CONFIG_ZHIZUN_END_TS		"activity_zhizun_end_ts"
#define CONFIG_ZHIZUN_VER			"activity_zhizun_ver"
#define CONFIG_ZHIZUN_PF			"activity_zhizun_pf"

//龙鳞活动
#define CONFIG_ACTIVITY_DRAGON_SCALE_B_TS "activity_dragon_scale_b_ts"
#define CONFIG_ACTIVITY_DRAGON_SCALE_E_TS "activity_dragon_scale_e_ts"
#define CONFIG_ACTIVITY_DRAGON_SCALE_VER "activity_dragon_scale_ver"
#define CONFIG_ACTIVITY_DRAGON_SCALE_PF "activity_dragon_scale_pf"

// 端午节
#define CONFIG_DUANWUJIE_BEGIN_TS		"activity_duanwujie_begin_ts"
#define CONFIG_DUANWUJIE_END_TS			"activity_duanwujie_end_ts"
#define CONFIG_DUANWUJIE_VER			"activity_duanwujie_ver"
#define CONFIG_DUANWUJIE_PF				"activity_duanwujie_pf"

//套装材料活动
#define CONFIG_TAOZHUANG_BEGIN_TS		"activity_taozhuang_begin_ts"
#define CONFIG_TAOZHUANG_END_TS			"activity_taozhuang_end_ts"
#define CONFIG_TAOZHUANG_VER			"activity_taozhuang_ver"
#define CONFIG_TAOZHUANG_PF				"activity_taozhuang_pf"

//武将培养活动
#define CONFIG_PEIYANG_BEGIN_TS			"activity_peiyang_begin_ts"
#define CONFIG_PEIYANG_END_TS			"activity_peiyang_end_ts"
#define CONFIG_PEIYANG_VER				"activity_peiyang_ver"
#define CONFIG_PEIYANG_PF				"activity_peiyang_pf"

//武将培养活动
#define CONFIG_SUMMER_BEGIN_TS			"activity_summer_begin_ts"
#define CONFIG_SUMMER_END_TS			"activity_summer_end_ts"
#define CONFIG_SUMMER_VER				"activity_summer_ver"
#define CONFIG_SUMMER_PF				"activity_summer_pf"

// 限时兑换
#define CONFIG_LIMIT_BEGIN_TS			"activity_limit_begin_ts"
#define CONFIG_LIMIT_END_TS				"activity_limit_end_ts"
#define CONFIG_LIMIT_VER				"activity_limit_ver"
#define CONFIG_LIMIT_PF					"activity_limit_pf"

// 浪漫七夕
#define CONFIG_QIXI_BEGIN_TS			"activity_qixi_begin_ts"
#define CONFIG_QIXI_END_TS				"activity_qixi_end_ts"
#define CONFIG_QIXI_VER					"activity_qixi_ver"

//倍数转盘
#define CONFIG_MULTIPLE_WHEEL_BEGIN_TS	"activity_multiple_wheel_b_ts"
#define CONFIG_MULTIPLE_WHEEL_END_TS	"activity_multiple_wheel_e_ts"
#define CONFIG_MULTIPLE_WHEEL_VER		"activity_multiple_wheel_ver"

//全服砸罐子
#define CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS	"activity_hammerhit_allserver_b_ts"
#define CONFIG_HAMMERHIT_ALLSERVER_END_TS	"activity_hammerhit_allserver_e_ts"
#define CONFIG_HAMMERHIT_ALLSERVER_VER		"activity_hammerhit_allserver_ver"

// 双11
#define CONFIG_DOUBLE11_ALLSERVER_BEGIN_TS		"activity_double11_allserver_begin_ts"
#define CONFIG_DOUBLE11_ALLSERVER_END_TS		"activity_double11_allserver_end_ts"
#define CONFIG_DOUBLE11_ALLSERVER_VER			"activity_double11_allserver_ver"

//觉醒特惠
#define CONFIG_JUEXINGTEHUI_BEGIN_TS			"activity_juexingtehui_begin_ts"
#define CONFIG_JUEXINGTEHUI_END_TS				"activity_juexingtehui_end_ts"
#define CONFIG_JUEXINGTEHUI_VER					"activity_juexingtehui_ver"

//世外桃源
#define CONFIG_SHIWAITAOYUAN_BEGIN_TS			"activity_shiwaitaoyuan_begin_ts"
#define CONFIG_SHIWAITAOYUAN_END_TS				"activity_shiwaitaoyuan_end_ts"
#define CONFIG_SHIWAITAOYUAN_VER				"activity_shiwaitaoyuan_ver"

//武将升星
#define CONFIG_WUJIANGSHEGNXING_BEGIN_TS			"activity_wujiangshengxing_begin_ts"
#define CONFIG_WUJIANGSHEGNXING_END_TS				"activity_wujiangshengxing_end_ts"
#define CONFIG_WUJIANGSHEGNXING_VER					"activity_wujiangshengxing_ver"
#define CONFIG_WUJIANGSHEGNXING_ITEM  25
#define CONFIG_WUJIANGSHEGNXING_TYPE  5
#define CONFIG_WUJIANGSHEGNXING_MIN  3
#define CONFIG_WUJIANGSHEGNXING_MAX  7
#define CONFIG_WUJIANGSHEGNXING_TIMES 10

//福袋活动
#define CONFIG_FUDAIHUODONG_BEGIN_TS			"activity_fudaihuodong_begin_ts"
#define CONFIG_FUDAIHUODONG_END_TS				"activity_fudaihuodong_end_ts"
#define CONFIG_FUDAIHUODONG_VER					"activity_fudaihuodong_ver"


#define CONFIG_HITEGG_BEGIN_TS					"activity_hitegg_begin_ts"
#define CONFIG_HITEGG_END_TS					"activity_hitegg_end_ts"
#define CONFIG_HITEGG_VER						"activity_hitegg_ver"

#define CONFIG_LOTTERY_BEGIN_TS					"activity_lottery_begin_ts"
#define CONFIG_LOTTERY_END_TS					"activity_lottery_end_ts"
#define CONFIG_LOTTERY_VER						"activity_lottery_ver"

#define CONFIG_CHARGE_BINGSHU_BEGIN_TS			"activity_charge_bingshu_begin_ts"
#define CONFIG_CHARGE_BINGSHU_END_TS			"activity_charge_bingshu_end_ts"
#define CONFIG_CHARGE_BINGSHU_VERSION			"activity_charge_bingshu_ver"

#define CONFIG_JINQIUSHIYUE_BEGIN_TS			"activity_jinqiushiyue_begin_ts"
#define CONFIG_JINQIUSHIYUE_END_TS				"activity_jinqiushiyue_end_ts"

#define CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX		12

#define CONFIG_COMBINE_SHOP_BEGIN_TS			"activity_combine_shop_begin_ts"
#define CONFIG_COMBINE_SHOP_END_TS				"activity_combine_shop_end_ts"
#define CONFIG_COMBINE_SHOP_VERSION				"activity_combine_shop_ver"

//得道真人
#define CONFIG_DEDAOZHENREN_BEGIN_TS 			"activity_dedaozhenren_begin_ts"
#define CONFIG_DEDAOZHENREN_END_TS 				"activity_dedaozhenren_end_ts"
#define CONFIG_DEDAOZHENREN_VER 				"activity_dedaozhenren_ver"
#define CONFIG_DEDAOZHENREN_PF 					"activity_dedaozhenren_pf"

//暑假前奏
#define CONFIG_PRE_SUMMER_BEGIN_TS				"activity_pre_summer_begin_ts"
#define CONFIG_PRE_SUMMER_END_TS				"activity_pre_summer_end_ts"
#define CONFIG_PRE_SUMMER_VERSION				"activity_pre_summer_version"
//暑假前奏2
#define CONFIG_PRE_SUMMER2_BEGIN_TS				"activity_pre_summer2_begin_ts"
#define CONFIG_PRE_SUMMER2_END_TS				"activity_pre_summer2_end_ts"
#define CONFIG_PRE_SUMMER2_VERSION				"activity_pre_summer2_version"
//暑假前奏3
#define CONFIG_PRE_SUMMER3_BEGIN_TS				"activity_pre_summer3_begin_ts"
#define CONFIG_PRE_SUMMER3_END_TS				"activity_pre_summer3_end_ts"
#define CONFIG_PRE_SUMMER3_VERSION				"activity_pre_summer3_ver"

//新绝世无双
#define CONFIG_NEWJUESHIWS_BEGIN_TS 			"activity_new_jueshiws_begin_ts"
#define CONFIG_NEWJUESHIWS_END_TS 				"activity_new_jueshiws_end_ts"
#define CONFIG_NEWJUESHIWS_VER 					"activity_new_jueshiws_ver"
#define CONFIG_NEWJUESHIWS_PF 					"activity_new_jueshiws_pf"

//厚惠有期 favorable
#define CONFIG_LARGE_FAVORABLE_BEGIN_TS			"activity_large_favorable_begin_ts"
#define CONFIG_LARGE_RAVORABLE_END_TS			"activity_large_favorable_end_ts"
#define CONFIG_LARGE_RAVORABLE_VER				"activity_large_favorable_ver"
#define CONFIG_LARGE_RAVORABLE_PF				"activity_large_favorable_pf"

//鸿运当头
#define CONFIG_OPPOR_KNOCK_BEGIN_TS 			"activity_oppor_knock_begin_ts"
#define CONFIG_OPPOR_KNOCK_END_TS 				"activity_oppor_knock_end_ts"
#define CONFIG_OPPOR_KNOCK_VER 					"activity_oppor_knock_ver"
#define CONFIG_OPPOR_KNOCK_PF 					"activity_oppor_knock_pf"

//幸运连连
#define CONFIG_FORTUNATELY_BEGIN_TS 			"activity_fortunaty_again_begin_ts"
#define CONFIG_FORTUNATELY_END_TS 				"activity_fortunaty_again_end_ts"
#define CONFIG_FORTUNATELY_VER 					"activity_fortunaty_again_ver"
#define CONFIG_FORTUNATELY_PF 					"activity_fortunaty_again_pf"

//充值自选
#define CONFIG_RECHARGE_OPTIONAL_BEGIN_TS 		"activity_recharge_optional_begin_ts"
#define CONFIG_RECHARGE_OPTIONAL_END_TS 		"activity_recharge_optional_end_ts"
#define CONFIG_RECHARGE_OPTIONAL_VER 			"activity_recharge_optional_ver"
#define CONFIG_RECHARGE_OPTIONAL_PF 			"activity_recharge_optional_pf"

//充值送星级
#define CONFIG_RECHARGE_SEND_UPGRADE_BEGIN_TS 	"activity_recharge_send_upgrade_begin_ts"
#define CONFIG_RECHARGE_SEND_UPGRADE_END_TS 	"activity_recharge_send_upgrade_end_ts"
#define CONFIG_RECHARGE_SEND_UPGRADE_VER 		"activity_recharge_send_upgrade_ver"
#define CONFIG_RECHARGE_SEND_UPGRADE_PF 		"activity_recharge_send_upgrade_pf"


//国庆盛典
#define CONFIG_GUOQING_HAPPY_BEGIN_TS 	"activity_guoqing_happy_begin_ts"
#define CONFIG_GUOQING_HAPPY_END_TS 	"activity_guoqing_happy_end_ts"
#define CONFIG_GUOQING_HAPPY_VER 		"activity_guoqing_happy_ver"
#define CONFIG_GUOQING_HAPPY_PF 		"activity_guoqing_happy_pf"


//五行灵珠
#define CONFIG_WUXING_PEARL_BEGIN_TS		"activity_wuxing_pearl_begin_ts"
#define CONFIG_WUXING_PEARL_END_TS			"activity_wuxing_pearl_end_ts"
#define CONFIG_WUXING_PEARL_VER				"activity_wuxing_pearl_ver"
#define CONFIG_WUXING_PEARL_PF				"activity_wuxing_pearl_pf"


//五行商铺
#define CONFIG_WUXING_SHOP_BEGIN_TS			"activity_wuxing_shop_begin_ts"
#define CONFIG_WUXING_SHOP_END_TS			"activity_wuxing_shop_end_ts"
#define CONFIG_WUXING_SHOP_VER				"activity_wuxing_shop_ver"
#define CONFIG_WUXING_SHOP_PF				"activity_wuxing_shop_pf"

#define CONFIG_ZHIZUNBAOXIANG_BEGIN_TS			"activity_zhizunbaoxiang_begin_ts"
#define CONFIG_ZHIZUNBAOXIANG_END_TS			"activity_zhizunbaoxiang_end_ts"
#define CONFIG_ZHIZUNBAOXIANG_VERSION			"activity_zhizunbaoxiang_ver"


//双11
#define CONFIG_DOUBLEELEVEN_BEGIN_TS			"activity_doubleeleven_begin_ts"
#define CONFIG_DOUBLEELEVEN_END_TS				"activity_doubleeleven_end_ts"
#define CONFIG_DOUBLEELEVEN_VER					"activity_doubleeleven_ver"
#define CONFIG_DOUBLEELEVEN_PF				    "activity_doubleeleven_pf"


//11月回馈
#define JINQIUNOVEMBER_INDEX		(11)
#define CONFIG_JINQIUNOVEMBER_BEGIN_TS			    "activity_jinqiunovember_begin_ts"
#define CONFIG_JINQIUNOVEMBER_END_TS				"activity_jinqiunovember_end_ts"
#define CONFIG_JINQIUNOVEMBER_VER					"activity_jinqiunovember_ver"
#define CONFIG_JINQIUNOVEMBER_PF				    "activity_jinqiunovember_pf"


//充值送神纹符
#define ACCHARGEBACKSHENWEN_INDEX		(3)
#define CONFIG_ACCHARGEBACKSHENWEN_BEGIN_TS			    "activity_acchargebackshenwen_begin_ts"
#define CONFIG_ACCHARGEBACKSHENWEN_END_TS				"activity_acchargebackshenwen_end_ts"
#define CONFIG_ACCHARGEBACKSHENWEN_VER					"activity_acchargebackshenwen_ver"
#define CONFIG_ACCHARGEBACKSHENWEN_PF				    "activity_acchargebackshenwen_pf"


//国庆福袋
#define CONFIG_COUNTRY_BAG_BEGIN_TS			"activity_country_bag_begin_ts"
#define CONFIG_COUNTRY_BAG_END_TS			"activity_country_bag_end_ts"
#define CONFIG_COUNTRY_BAG_VER				"activity_country_bag_ver"
#define CONFIG_COUNTRY_BAG_PF				"activity_country_bag_pf"

//vikcy的无节操累计充值活动
#define CONFIG_VICKY_ACC_BEGIN_TS			"activity_vicky_acc_begin_ts"
#define CONFIG_VICKY_ACC_END_TS				"activity_vicky_acc_end_ts"
#define CONFIG_VICKY_ACC_VER				"activity_vicky_acc_ver"
#define CONFIG_VICKY_ACC_PF					"activity_vicky_acc_pf"


//寒假狂欢  HolidayRevelry
#define CONFIG_HOLIDAY_REVELRY_BEGIN_TS		"activity_holiday_revelay_begin_ts"
#define CONFIG_HOLIDAY_REVELRY_END_TS		"activity_holiday_revelay_end_ts"
#define CONFIG_HOLIDAY_REVELRY_VER			"activity_holiday_revelay_ver"
#define CONFIG_HOLIDAY_REVELRY_PF			"activity_holiday_revelay_pf"

//vikcy的联盟消费
#define CONFIG_ALLIANCE_CONSUME_BEGIN_TS	"activity_alliance_consume_begin_ts"
#define CONFIG_ALLIANCE_CONSUME_END_TS		"activity_alliance_consume_end_ts"
#define CONFIG_ALLIANCE_CONSUME_VER			"activity_alliance_consume_ver"
#define CONFIG_ALLIANCE_CONSUME_PF			"activity_alliance_consume_pf"

//鸡年纳福
#define CONFIG_VICKY_CHICK_BEGIN_TS			"activity_vicky_chick_begin_ts"
#define CONFIG_VICKY_CHICK_END_TS			"activity_vicky_chick_end_ts"
#define CONFIG_VICKY_CHICK_PF				"activity_vicky_chick_pf"

//vikcy的消费自选活动
#define CONFIG_VICKY_PAY_BEGIN_TS			"activity_vicky_pay_begin_ts"
#define CONFIG_VICKY_PAY_END_TS				"activity_vicky_pay_end_ts"
#define CONFIG_VICKY_PAY_VER				"activity_vicky_pay_ver"
#define CONFIG_VICKY_PAY_PF					"activity_vicky_pay_pf"

//装备强化活动
#define CONFIG_EQUIP_STRENGTHEN_BEGIN_TS	"activity_equip_strengthen_begin_ts"
#define CONFIG_EQUIP_STRENGTHEN_END_TS		"activity_equip_strengthen_end_ts"
#define CONFIG_EQUIP_STRENGTHEN_VER			"activity_equip_strengthen_ver"
#define CONFIG_EQUIP_STRENGTHEN_PF			"activity_equip_strengthen_pf"

//活动名称宏
//古卷专项活动
#define CONFIG_SCROLL_ACTIVITY "scroll_activity"
//天帝宝库
#define CONFIG_KING_TREASURE "king_treasure"
//古卷回馈
#define CONFIG_SCROLL_FEEDBACK "scroll_feedback"
//七日觉醒
#define CONFIG_SEVENDAYS_AWAKEN "sevenday_awaken"
//令牌提升
#define CONFIG_TOKEN_UPGRADE "token_upgrade"
//套装打造
#define CONFIG_BUILD_SUIT "build_suit"
//祝福积分
#define CONFIG_BLESS_POINT "bless_point"
//双倍福利
#define CONFIG_DOUBLE_WELFARE "double_welfare"
//灵珠进阶
#define CONFIG_PEARL_ADVANCE	"pearl_advance"
//绝学转盘
#define CONFIG_UNIQUE_DIAL	"uniqueknowledge_dial"
//的卢凝魂
#define CONFIG_CHARGE_HORSE	"charge_horse"
//精元礼包
#define CONFIG_SPIRIT_VITALITY "spirit_vitality"
//熔炉熔炉
#define CONFIG_FORGE_SMELT "forge_smelt"
//紫将转盘
#define CONFIG_HERO_DIAL "hero_dial"
//三国争霸
#define CONFIG_KINGDOM_WAR	"kingdom_war"
//一钻福利
#define CONFIG_ONEDIAMOND "onediamond_welfare"
//七夕回馈
#define CONFIG_QIXI_FEEDBACK "qixi_feedback"
//好运礼包
#define CONFIG_FORTUNE_PACKS "fortune_packs"
//七天好礼
#define CONFIG_SEVENDAYS_PACKS "sevenday_packs"
//冰凰来袭
#define CONFIG_ICEPHOENIX "ice_phoenix"
//秋日回馈
#define CONFIG_AUTUMN_FEEDBACK "autumn_feedback"
//保护旗帜
#define CONFIG_PROTECT_FLAG "protect_flag"
//密钥豪礼
#define CONFIG_KEY_LUXURYGIFT "key_luxurygift"
//畅享小礼
#define CONFIG_ENJOY_SMALLGIFT	"enjoy_smallgift"
//幸运好礼
#define CONFIG_LUCKY_GIFT	"lucky_gift"
//年末好礼
#define CONFIG_YEAREND_GIFT	"yearend_gift"
//元旦好礼
#define CONFIG_NEWYEAR_GIFT	"newyear_gift"

//转盘狂惠
#define CONFIG_ROTARYTABLE_GIFT "rotary_table"

//转盘回馈
#define CONFIG_ROTARYTABLEFEEDBACK_GIFT "zhuanpanhuikui"

//小兵宝物
#define CONFIG_BATMANTREASURE_GIFT "batman_treasure"

//暑假精选
#define CONFIG_SUMMERCHAEGE_GIFT "summer_charge"

//暑假回馈
#define CONFIG_SUMMERREWARD_GIFT "summer_reward"

//开服有礼
#define CONFIG_OPENSERVER_GIFT	"openserver_gift"
//黑金强化
#define CONFIG_BLACK_ENHANCE "blackgold_enhance"

//国庆中秋双节活动
#define CONFIG_TWOHOLIDAY_ENJOY "twoholiday_acc"

//星石置换
#define CONFIG_STAR_STONE_CHG "star_stone_chg"
//vicky的充值活动x
#define CONFIG_VICKY_ACC_X "vicky_acc_x"
#define CONFIG_VICKY_ACC_X1 "vicky_acc_x1"
#define CONFIG_VICKY_ACC_X2 "vicky_acc_x2"
#define CONFIG_VICKY_ACC_X3 "vicky_acc_x3"
#define CONFIG_VICKY_ACC_X4 "vicky_acc_x4"
#define CONFIG_VICKY_ACC_X5 "vicky_acc_x5"

//红人榜
#define CONFIG_NEWYEAR_ACTIVE "newyearActive"

//任务好礼
#define CONFIG_TASK_GIFT "task_gift"

//机甲黄忠
#define CONFIG_huangzhong "huangzhong_items"

//vicky的开服活动
#define CONFIG_VICKY_NEW_OPEN "vicky_new_open"

//新充值自选
#define CONFIG_CHONGZHI_ZIXUAN "chongzhizixuan"

//美人献计
#define CONFIG_BEAUTY "beauty"

//充值投资
#define CONFIG_INVESTMENT "chongzhitouzi"

//鹊桥相会
#define CONFIG_BIRDBRIDGE "birdbridge"

//喜迎国庆
#define CONFIG_CHINADAY_WELCOME    "chinaday_welcome"

#define CONFIG_GUO_QING_KUANG_HUAN  "guoqingkuanghuan"

#define CONFIG_OPTIONAL_PAY          "optional_pay"

#define CONFIG_QINGRENJIE_MEIGUI          "qingrenjie_meigui"

#define CONFIG_NIANSHOU_BOSS          "nianshouboss"

#define CONFIG_ZHENGBASHADI_CHONGBANG "zhengbashadi_chongbang"

#define CONFIG_LUEDUOTONGQIAN_CHONGBANG "lueduotongqian_chongbang"

#define CONFIG_ZHOUNIANQING_QIANDAO "zhounianqing_qiandao"

#define CONFIG_ZHOUNIANQING_GOUMAI "zhounian_shangdian"

#define CONFIG_anniversary_chongzhi "anniversary_chongzhi"

#define CONFIG_chengyuantisheng "chengyuantisheng"

#define ACTIVITY_TIME_TOUZIDAFANLI "touzidafanli"

#define ACTIVITY_TIME_GUYU "guyu"

#define ACTIVITY_TIME_ERTONGJIE "childrenDaysActivity"

#define ACTIVITY_TIME_STONE "xingshijifen"

#define ACTIVITY_TIME_OLDTONEW "oldToNew"

#define ACTIVITY_TIME_wuyiqingdian "wuyiqingdian"

#define CONFIG_GIVEHELPACTION "zhulidaxingdong"

#define ACTIVITY_TIME_QUNXING "qunxing"

#define ACTIVITY_TIME_QITIANJINJIE "qitianjinjie"


/********************************************************************/
/*  活动太多  先是抽象成模板  最后只能搞宏
 * 定义配置字段的宏，例如 #define CONFIG_NAME "some_act_name"
 * enum NewActType 中枚举变量要定义成  NAT_CONFIG_NAME 的形式
 * ActivityConfig.cpp 中 const char* all_activity_table[] 添加 CONFIG_NAME
 * DataXML.h 中 实现宏  CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME)
 * class CDataXML 中 实现宏  GET_CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME)
 * int CDataXML::InitVickyAccX()  中 实现宏 INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_NAME)
 * LogicCMDUnit.h  中 实现宏  CHARGE_DRAW_ACT(CONFIG_NAME)
 * class CCgiSave 中 实现宏 CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_NAME)
 * CgiSave.cpp 中CGI_ACTION_DEFAULT_MAP_BEGIN 下实现宏  CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_NAME)
 */
/********************************************************************/
//autolable1
#define CONFIG_yongguansanjun "yongguansanjun"
#define CONFIG_wuyiqingdian_leiji "wuyiqingdian_leiji"
#define CONFIG_yvre618_2 "yvre618_2"
#define CONFIG_yvre618_1 "yvre618_1"
#define CONFIG_toushichejineng "toushichejineng"
#define CONFIG_chongbang_3 "chongbang_3"
#define CONFIG_zhuanshucanjuan "zhuanshucanjuan"
#define CONFIG_baihuahuikui_3 "baihuahuikui_3"
#define CONFIG_baihuahuikui_2 "baihuahuikui_2"
#define CONFIG_baihuahuikui_1 "baihuahuikui_1"
#define CONFIG_guyv_leiji "guyv_leiji"
#define CONFIG_chengyuantisheng_2 "chengyuantisheng_2"
#define CONFIG_chengyuantisheng_1 "chengyuantisheng_1"
#define CONFIG_lueduotongqian_chongbang "lueduotongqian_chongbang"
#define CONFIG_anniversary_leiji "anniversary_leiji"
#define CONFIG_anniversary_meiri "anniversary_meiri"
#define CONFIG_zhengbashadi_chongbang "zhengbashadi_chongbang"
#define CONFIG_hanjiajingxuan "hanjiajingxuan"
#define CONFIG_fuzhuhesui "fuzhuhesui"
#define CONFIG_zhuniandaji "zhuniandaji"
#define CONFIG_vicky_qingrenjie "vicky_qingrenjie"
#define CONFIG_yuandan2018 "yuandan2018"
#define CONFIG_yearend2018 "yearend2018"
#define CONFIG_winter2018 "winter2018"
#define CONFIG_double11_2018 "double11_2018"
#define CONFIG_SHENGDAN_2018 "shengdan_2018"
#define CONFIG_XIAONIAN_2018 "xiaonian_2018"
#define CONFIG_mid_aug_hao "mid_aug_hao"
#define CONFIG_mid_aug_reu "mid_aug_reu"
#define CONFIG_water_taotie "water_taotie"
#define CONFIG_water_qilin "water_qilin"
#define CONFIG_water_pheonix "water_pheonix"
#define CONFIG_vicky_nnom "vicky_nnom"
//vicky没想好名字的活动
#define CONFIG_VICKY_NO_NAME "vicky_no_name"
#define CONFIG_VICKY_BINGSHU "vicky_bingshu"
#define CONFIG_VICKY_QIANFU  "vicky_qianfu"
#define CONFIG_VICKY_NNA 	 "vicky_nna"

#define CONFIG_FREE_EXCHG          "free_exchg"//兑换自选

#define CONFIG_DOUBLE11_2018_BEGIN_TS	"activity_double11_2018_begin_ts"
#define CONFIG_DOUBLE11_2018_END_TS		"activity_double11_2018_end_ts"
#define CONFIG_DOUBLE11_2018_VER		"activity_double11_2018_ver"

///////////////////////////////////////////////////////////////

//DB
//对应DBC端口号和共享内存号为39100+ID
#define DB_PAY				1
#define DB_PAY_HISTORY		2
#define DB_USER_BASIC		3
#define DB_USER				4
#define DB_QUEST			5
#define DB_BUILDING			6
#define DB_EQUIPMENT		7
#define DB_GATE				8
#define DB_HERO				9
#define DB_TRIBUTE			10
#define DB_UPDATES			11
#define DB_NEIGHBOUR		12
#define DB_USER_INTERACT	13
#define DB_ATTACK			14
#define DB_USER_ATTACK		15
#define DB_MESSAGE			16
#define DB_USER_MESSAGE		17
#define DB_USER_DATA		18
#define DB_USER_TEXT		19
#define DB_INVENTORY		20
#define DB_PLATFORM_USER	21
#define DB_ALLIANCE			22
#define DB_ALLIANCE_MEMBER	23
#define DB_ALLIANCE_MAPPING	24
#define DB_INSTANCE			25
#define DB_SECINC			26
#define DB_EMAIL			27
#define DB_INVITE_MAPPING   28
#define DB_BASE_EXTRA       29
#define DB_HELP_HISTORY     30
#define DB_EXCHANGE_CODE     31
#define DB_PROMOTION_MAPPINT 32
#define DB_ALLIANCE_PAY      33

#define DB_USER_RANK      	 34
#define DB_GOODS             35
#define DB_MARKET_TASK	     36
#define DB_WEAPON	         37
#define DB_BLACK_USER        38
#define DB_ALLIANCE_MSG      39
#define DB_ALLIANCE_INTERACT 40
#define DB_MATCH_INSTANCE    41


#define MEM_SESSION			91
#define DB_USER_MAPPING		92
#define DB_ID_CTRL			93
#define DB_USER_NOMENATE	95
#define DB_USER_ACCCHARGE	96

#define DB_VIP_CHARGE		97
#define DB_RANK				98

#define DB_NAME				99
#define DB_IDCARD			100
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
#define ATTACK_NPC_2_MAX	300
#define ATTACK_NPC_3_MAX	350
#define NPC_UID_MAX			500
#define IsNPCUid(uid)		((uid >= NPC_UID_MIN && uid < NPC_UID_MAX) || (uid >= WORLD_NPC_UID_MIN && uid < ALL_NPC_UID_MAX))
#define IsGateNPCUid(uid)	(uid >= NPC_UID_MIN && uid < GATE_NPC_UID_MAX )
#define IsCityNPCUid(uid)	(uid > GATE_NPC_UID_MAX && uid <= ATTACK_NPC_3_MAX )
#define WORLD_NPC_UID_MIN	70001
#define WORLD_NPC_UID_MAX	70100
#define WUHUJIANG_NPC_UID_MIN	70101
#define WUHUJIANG_NPC_UID_MAX	70200
#define BNW_NPC_UID_MIN	70201
#define BNW_NPC_UID_MAX	70400
#define ALL_NPC_UID_MAX		90000
#define IsWuhujiangNPCUid(uid)	(uid >= WUHUJIANG_NPC_UID_MIN && uid < WUHUJIANG_NPC_UID_MAX)
#define IsWorldNPCUid(uid)	(uid >= WORLD_NPC_UID_MIN && uid < WORLD_NPC_UID_MAX)
#define IsBNWNPCUid(uid)	(uid >= BNW_NPC_UID_MIN && uid < BNW_NPC_UID_MAX)
#define IsOtherNPCUid(uid)	((uid > ATTACK_NPC_3_MAX && uid < NPC_UID_MAX) || (uid >= WORLD_NPC_UID_MIN && uid < ALL_NPC_UID_MAX))
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
#define NIAN_SHOU_ID_MIN	50011
#define NIAN_SHOU_ID_MAX	50012
#define IsValidWorldBossId(id)	(id >= WORLD_BOSS_ID_MIN && id <= WORLD_BOSS_ID_MAX)
#define IsValidNianShouId(id)	(id >= NIAN_SHOU_ID_MIN && id <= NIAN_SHOU_ID_MAX)
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

#define NEW_USER_CASH		0	//新用户钻石数
#define NEW_USER_COINS		200  //新用户金币数
#define NEW_USER_R1			7000
#define NEW_USER_R1_MAX		7000
#define NEW_USER_R2			7000
#define NEW_USER_R2_MAX		7000
#define NEW_USER_R3			7000
#define NEW_USER_R3_MAX		7000
#define NEW_USER_R4			7000
#define NEW_USER_R4_MAX		7000
#define NEW_USER_R5			0
#define NEW_USER_R5_MAX		0
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
#define BNW_ATTACK_MAX_TIME	660	//BNW最大进攻时间
#define RANK_ATTACK_MAX_TIME 540//RANK最大进攻时间
#define MVP_ATTACK_MAX_TIME 540//MVP最大进攻时间
#define NEW_DOUJIANG_ATTACK_MAX_TIME	660	//冲榜3期斗将最大进攻时间
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

//待定新活动
#define MAX_EXTRA_ITEMS 14

#define ARENA_REWARD 50
#define ARENA_COST 10

#define MAX_MATERIAL_TYPE 8 //材料种类

//道具替换钻石金币
//紫色密钥
enum PropReplaceCoin
{
	purple_key	= 2024,  //紫色密钥
	blue_key	= 2025,  //蓝色密钥
	green_key	= 2026,  //绿色密钥
	refresh_key = 2027,
	refresh_key_low = 2028,
	protect_flag_build = 2050,  //保护旗帜建造令
	flag_upgrade_costA = 2051, //旗帜升级消耗的道具A
};

enum ResourceType
{
	resource_rice = 1,
	resource_stone = 2,
	resource_wood = 3,
	resource_iron = 4,
};

enum FCM_TYPE
{
	e_fcm_normal	= 0,
	e_fcm_half		= 1,
	e_fcm_none		= 2,

	e_fcm_max
};
const double FCM_VALUE[e_fcm_max] = {1.0, 0.5, 0};

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
	LT_BNW,			//烽火大陆
	LT_MVP,			//名人堂
	LT_SUB_ATTACK,  //副本

	LT_UNKNOW
};

#define NEW_STONE_NUM 3

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
	NAT_ZAOHUAGE_1				= 20,//造化阁1
	NAT_ZAOHUAGE_2				= 21,//造化阁2
	NAT_TEMAI					= 22,//心动特卖
	NAT_FETE					= 23,//祭祀
	NAT_DIANJIANGTAI_1			= 24,//点将台1
	NAT_DIANJIANGTAI_2			= 25,//点将台2
	NAT_ZHIZUN_XILIAN			= 26,//至尊洗炼
	NAT_LONGLIN					= 27,//龙鳞转盘
	NAT_DUANWU					= 28,//端午活动
	NAT_CHOUJIANG				= 29,//幸运大转盘
	NAT_TAOZHUANG				= 30,//套装材料
	NAT_PEIYANG_1				= 31,//培养活动
	NAT_PEIYANG_2				= 32,//培养活动
	NAT_DESTINY					= 33,//??
	NAT_TOUCH1					= 34,//摸金1
	NAT_HAPPYCARD_1				= 35,//欢乐卡牌1
	NAT_POKER					= 36,//烽火点将
	NAT_VIP_SHOP				= 37,//VIP商店
	NAT_HAPPYCARD_2				= 38,//欢乐卡牌2
	NAT_4399_SHOP				= 42,//4399限时抢购
	NAT_SUMMER					= 43,//夏日活动
	NAT_FREEEXCHANGE			= 44,//免费兑换
	NAT_TANABATA				= 45,//七夕活动
	NAT_R5						= 46,//勋章(联盟夺宝)
	NAT_SOGOU					= 47,//搜狗平台相关
	NAT_MULTIPLEWHEEL			= 48,//倍数转盘
	NAT_HAMMERHIT_ALLSERVER		= 50,//全服砸罐子
	NAT_DOUBLE11				= 51,//双11
	NAT_JUEXINGTEHUI			= 52,//觉醒特惠
	NAT_TOUCH2					= 53,//摸金2
	NAT_FREE_MIX_HERO_1			= 54,//武将升星
	NAT_FREE_MIX_HERO_2			= 55,//武将升星
	NAT_FUDAI					= 56,//福袋
	NAT_SHENGDAN				= 57,//圣诞
	NAT_EGG						= 58,//砸金蛋
	NAT_MEDAL					= 59,//领取勋章
	NAT_NEWWORLD_FB				= 60,//国战副本
	NAT_SUPER_REDUCE			= 61,//超值折扣
	NAT_DIGEQUIP_SUBSTONE		= 62,//挖矿
	NAT_TREASURE_HUNT			= 63,//步步为赢
	NAT_NEWWORLD_FB_2			= 64,//国战副本2
	NAT_GVG_1					= 65,//gvg
	NAT_GVG_2					= 66,//gvg
	NAT_GVG_3					= 67,//gvg
	NAT_GVG_4					= 68,//gvg
	NAT_COMBINED_SHOP			= 69, //组合商店
	NAT_TENCENT_MANAGER			= 70,//腾讯电脑管家
	NAT_DEDAO_ZHENREN		    = 71,//得道真人
	NAT_PRE_SUMMER				= 72,//暑假前奏
	NAT_NEW_JUESHIWS			= 73, //新绝世无双
	NAT_HOUHUIYOUQI			    = 74, //厚惠有期
	NAT_LORDS					= 75, //尊主榜
	NAT_OPPOR_KNOCK				= 76, //鸿运当头
	NAT_FORTUNATELY_AGAIN		= 77, //幸运连连
	NAT_RECHARGE_OPTIONAL		= 78, //充值自选
	NAT_PRESENT_GIFT_UPGRADE	= 79, //充值送星级
	NAT_TEMPLE_PRAY				= 80, //天坛祈福
	NAT_NEW_RECHARGE			= 81, //开区充值礼包

	NAT_GUOQING_LOGIN			= 83, //国庆登录
	NAT_GUOQING_SHOP_ONE	    = 84, //国庆商店1
	NAT_GUOQING_SHOP_TWO		= 85, //国庆商店2
	NAT_GUOQING_FUDAI			= 86, //国庆福袋
	NAT_WUXING_PEARL			= 87, //五行珠
	NAT_WUXING_TEMAI_SHOP		= 88,  //五行特卖商店
	NAT_WUXING_COUPON_SHOP		= 89,  //五行折扣券商店
	NAT_WUXING_COUPON	    	= 90,  //五行折扣卷
	NAT_CHONGZHIHUIKUI	    	= 91,  //充值回馈
	NAT_JINQIUSHIYUE	    	= 92,  //金秋十月
	NAT_ZHIZUNBAOXIANG	    	= 93,  //至尊宝箱
	NAT_DOUBLEELEVEN	    	= 94,  //双11
	NAT_PART_STONE		    	= 95,  //武魂强化
	NAT_JINQIUNOVEMBER	    	= 96,  //11月回馈
	NAT_ACCHARGEBACKSHENWEN	    = 97,  //充值送神纹符
	NAT_KEEP_SAKE				= 98, //信物系统
	NAT_VICKY_ACC				= 99, //vikcy的无节操累计充值活动
	NAT_XINWU_FB				= 100, //信物副本
	NAT_HOLIDAY_REVELAY			= 101, //寒假狂欢
	NAT_VICKY_CHICK				= 102, //鸡年纳福
	NAT_VICKY_PAY				= 103, //消费自选
	NAT_TOWER_ACTIVI_1			= 104, //塔楼外传
	NAT_TOWER_ACTIVI_2			= 105, //塔楼外传
	NAT_TOKEN_INTENSIFY			= 106, //信物强化
	NAT_WORLD_TREASURE			= 107, //世界秘宝
	NAT_WORLD_TREASURE_EXT		= 108, //世界秘宝
	NAT_EQUIPSTRENGTHEN			= 109, //装备强化活动
	NAT_SOUL_FEEDBACK			= 110, //武魂回馈
	NAT_AWAKEN_FEEDBACK			= 111, //觉醒回馈
	NAT_GEM_DISCOUNT			= 112, //宝石折扣
	NAT_ALLIANCE_CONSUME		= 113, //联盟消费
	NAT_CAST_SOUL				= 114, //铸魂打折
	NAT_TREASURES_AROUND		= 115, //金玉满堂
	NAT_SPIRIT_FOSTER			= 116, //将灵培养
	NAT_SCROLL_SPECIAL			= 117, //古卷专项活动
	NAT_KING_TREASURE			= 118, //天帝宝库
	NAT_SCROLL_FEEDBACK			= 119, //古卷回馈
	NAT_SEVENDAY_AWAKEN			= 120, //七日觉醒
	NAT_TOKEN_UPGRADE			= 121, //令牌提升
	NAT_BUILD_SUIT				= 122, //打造套装
	NAT_BLESS_POINT				= 123, //祝福积分
	NAT_DOUBLE_WELFARE			= 124, //双倍福利
	NAT_PEARL_ADVANCE			= 125, //灵珠进阶
	NAT_UNIQUEKNOWLEDGE_DIAL	= 126, //绝学转盘
	NAT_SPIRIT_VITALITY			= 127, //精元礼包
	NAT_CHARGE_HORSE			= 128, //的卢凝魂
	NAT_PRE_SUMMER2				= 129, //暑假前奏2
	NAT_FORGE_SMELT				= 130, //熔炉熔炼
	NAT_HERO_DIAL				= 131, //紫将转盘
	NAT_KINGDOM_WAR				= 132, //三国争霸
	NAT_ONE_DIAMOND_WELFARE		= 133, //一钻福利
	NAT_QIXI_FEEDBACK			= 134, //七夕回馈
	NAT_FORTUNE_PACKS			= 135, //好运礼包
	NAT_SEVENDAY_PACKS			= 136, //七天好礼
	NAT_ICE_PHOENIX				= 137,  //冰凰来袭
	NAT_AUTUMN_FEEDBACK			= 138,  //秋日回馈
	NAT_PROTECT_FLAG			= 139,  //保护旗帜
	NAT_EVERYDAYRECHARGE        = 140, //国庆中秋双节活动--每日充值
	NAT_EVERYDAYONLINE          = 141, //国庆中秋双节活动--每日在线
	NAT_ENJOYSTORE              = 142, //国庆中秋双节活动--畅享商店
	NAT_VIPREWARD               = 143, //国庆中秋双节活动--vip奖励
	NAT_KEYLUXURY_GIFT			= 144,  //密钥豪礼
	NAT_ENJOY_SMALLGIFT			= 145,  //畅享小礼
	NAT_LUCKY_GIFT				= 146, //幸运好礼
	NAT_YEAREND_GIFT			= 147, //年末好礼
	NAT_NEWYEARE_GIFT			= 148, //元旦好礼
	NAT_OPENSERVER_GIFT			= 149, //开服有礼
	NAT_STAR_STONE_CHG			= 150, //星石置换
	NAT_VICKY_ACC_X				= 151, //vicky又要做个充值活动
	NAT_VICKY_ACC_X1			= 152, //vicky又要做个充值活动1
	NAT_VICKY_ACC_X2			= 153, //vicky又要做个充值活动2
	NAT_VICKY_ACC_X3			= 154, //vicky又要做个充值活动3
	NAT_VICKY_ACC_X4			= 155, //vicky又要做个充值活动4
	NAT_VICKY_ACC_X5			= 156, //vicky又要做个充值活动5
	NAT_NEWYEAR_ACTIVE			= 157, //红人榜
	NAT_GVG_SEC					= 158, //国战小秘书
	NAT_TASK_GIFT				= 159, //任务好礼
	NAT_huangzhong				= 160, //机甲黄忠
	NAT_ROTARYTABLE             = 161, //转盘狂惠
	NAT_VICKY_NEW_OPEN			= 162, //vicky的开服活动
	NAT_CONFIG_VICKY_NO_NAME    = 163, //vickyvicky没想好名字的活动
	NAT_CONFIG_VICKY_BINGSHU	= 164, //兵书突破
	NAT_CONFIG_VICKY_QIANFU		= 165, //千服同庆
	NAT_NEWWORLD_KILL_REWARDS   = 166, //国战杀敌奖励
	NAT_BATMANTREASURE          = 167, //小兵宝物
	NAT_SUMMERCHARGE            = 168, //暑期精选
	NAT_SUMMERREWARD            = 169, //暑假回馈
	NAT_CHONGZHIZIXUAN          = 170, //
	NAT_BEAUTY_ACTIVE           = 171, //美人献计活跃
	NAT_BEAUTY_REWARD           = 172, //美人献计奖励
	NAT_INVESTMENT              = 173, //充值投资
	NAT_CONFIG_VICKY_NNA        = 174, //vicky懒得给我说名字的活动
	NAT_ACTIVITY_BIRDBRIDGE     = 175, //鹊桥相会
	NAT_CONFIG_vicky_nnom		= 176,
	NAT_BRAVENEWWORLD_HUOYUE_NEW_NEW_ACT_NUM 	= 177,
	NAT_BRAVENEWWORLD_TASK_NEW_NEW_ACT_NUM 		= 178,
    NAT_CONFIG_water_pheonix	= 179,
	NAT_CONFIG_water_qilin		= 180,
	NAT_CONFIG_water_taotie		= 181,
	NAT_CONFIG_mid_aug_reu		= 182,
	NAT_CONFIG_mid_aug_hao		= 183,
	NAT_PRE_SUMMER3				= 184, //暑假前奏3
	NAT_CHINADAY_WELCOME	    = 187,  //喜迎国庆活动
	NAT_PATIONAL_PAY            = 188,  //充值自选活动
	NAT_GUO_QING_KUANG_HUAN 	= 189,//国庆狂欢
	NAT_FREE_EXCHG				= 190, //兑换自选

	NAT_CONFIG_double11_2018	= 191,
	NAT_DOUBLE11_2018			= 192,//双11
	NAT_SHENGDAN_2018			= 193,
NAT_CONFIG_winter2018			= 194,
NAT_CONFIG_yearend2018			= 195,
NAT_CONFIG_yuandan2018			= 196,
	NAT_XIAONIAN_2018			= 197,
	NAT_QINGRENJIE_MEIGUI		= 198,
NAT_CONFIG_vicky_qingrenjie			= 199,
NAT_CONFIG_zhuniandaji			= 200,
NAT_CONFIG_fuzhuhesui			= 201,
	NAT_NIANSHOU_BOSS           = 202,
NAT_CONFIG_hanjiajingxuan			= 203,
NAT_CONFIG_zhengbashadi_chongbang			= 204,
	NAT_xianshi_mubiao_1           = 205,
	NAT_zhounianqing_qiandao       = 206,
NAT_CONFIG_anniversary_meiri			= 207,
NAT_CONFIG_anniversary_leiji			= 208,
	NAT_zhounianqing_goumai			= 209,
	NAT_xianshi_mubiao_2           = 210,
NAT_CONFIG_lueduotongqian_chongbang			= 211,
	NAT_xianshi_chengyuansuipian_chouqu     = 212,
NAT_CONFIG_chengyuantisheng_1			= 213,
NAT_CONFIG_chengyuantisheng_2			= 214,
ACTIVITY_TOUZIDAFANLI_ACT_NUM_1 = 215,
ACTIVITY_TOUZIDAFANLI_ACT_NUM_2 = 216,
ACTIVITY_TOUZIDAFANLI_ACT_NUM_3 = 217,
NAT_CONFIG_guyv_leiji			= 218,
ACTIVITY_GUYU_JIFEN             = 219,
NAT_CONFIG_guyv_meiri			= 220,
NAT_CONFIG_baihuahuikui_1			= 221,
NAT_CONFIG_baihuahuikui_2			= 222,
NAT_CONFIG_baihuahuikui_3			= 223,
NAT_CONFIG_zhuanshucanjuan			= 224,
NAT_CONFIG_chongbang_3			= 225,
NAT_xianshi_mubiao_3			= 226,
NAT_CONFIG_toushichejineng			= 227,
NAT_CONFIG_childrenDaysActivity			= 228,
NAT_CONFIG_yvre618_1			= 229,
NAT_CONFIG_yvre618_2			= 230,
ACTIVITY_GUYU_JINJIE            = 231,
NAT_CONFIG_binghunturndish      = 232,
ACTIVITY_STONE_JIFEN			= 233,
ACTIVITY_KUANGHUAN_618          = 234,
ACTIVITY_WUYIQINGDIAN_MEIRI     = 235,
NAT_CONFIG_wuyiqingdian_leiji			= 236,
NAT_ROTARYTABLE_FEEDBACK		= 237,  //转盘回馈
NAT_CONFIG_yongguansanjun			= 238,
NAT_CONFIG_givehelpaction       = 239,
NAT_ACT_QUNXINGHUIJU			= 240,	//群星汇聚活动
NAT_NEW_WORLD_HERO_NUM			= 241,	//争霸武将开孔
ACTIVITY_QITIANJINJIE_MEIRI		= 242,	//七日进阶活动
NAT_MAX
};

#endif	//__APPDEFINE_H__
