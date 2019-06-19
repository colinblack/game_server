#ifndef __PROTO_H__
#define __PROTO_H__

enum system_command
{
	SYS_ECHO					= 0001,       /* echo */
	SYS_ONLINE					= 0002,       /* get online */
	SYS_SETUP					= 0003,       /* setup table */

	SERVER_REGISTER_REQ          = 7000, /* 玩牌服务器注册 */
	LINK_DB_CLIENT_BREAK         = 7001, /* 数据中心与数据库服务器断开连接 */

	SERVER_CONFIGURE_REQ         = 7002, /* 请求获取玩牌服务器当前配置 */
	SERVER_CONFIGURE_RES         = 7003, /* 返回玩牌服务器当前配置 */
	UPDATE_SERVER_CONFIGURE_REQ  = 7004, /* 请求更新玩牌服务器配置 */
	UPDATE_SERVER_CONFIGURE_RES  = 7005, /* 返回更新玩牌服务器后的配置 */

	SERVER_UPDATE_MONEY				= 7006, /* 非玩牌服务器请求更新同步玩家金币到玩牌服务器 */
	SERVER_UPDATE_USER_INFO			= 7007, /* 玩牌服务器请求更新玩家数据库数据与玩家在其他玩牌服务器内存数据 */
	SERVER_UPDATE_DB_TASK_REQ       = 7008, /* 玩牌服务器请求更新玩家数据库任务数据 */
	SERVER_UPDATE_DB_TALLY_REQ      = 7009, /* 玩牌服务器请求更新流水信息到数据库 */
	SERVER_SPEAK_INFO_WRITE_REQ     = 7010, /* 玩牌服务器请求更新大喇叭信息到数据库 */
	SERVER_USER_BROKE_WRITE_REQ     = 7011, /* 玩牌服务器请求更新玩家破产信息到数据库 */
	SERVER_USER_ZID_INFO_WRITE_REQ  = 7012, /* 玩牌服务器请求更新玩家当前场次的vid，zid信息 */
	SERVER_ADD_ROBOT_MONEY			= 7104, /* 玩牌服务器请求加机器人金币 */
	SERVER_INFORM_USER_VID_TO_DATASV= 7105, /* 玩牌服务器通知datasvr玩家成功进入该场 */
	SERVER_SET_BANKER_TAG_TO_DB		= 7106,  /* 玩牌服务器请求存储当庄标志 */
	SERVER_SAVE_POOL_TO_DB			= 7107, /* 玩牌服务器请求存储奖池数据 */
	SERVER_GET_POOL_FROM_DB			= 7108, /* 玩牌服务器请求当前桌子奖池数据 */
	SERVER_GET_POOL_BACK			= 7109, /* 数据库返回奖池数据给玩牌服务器 */
	SERVER_SAVE_USER_OTHER_INFO		= 7110, /* 玩牌服务器存储玩家其他相关的数据 */
	SERVER_SAVE_GAME_INFO			= 7111, /* 玩牌服务器存储其他游戏相关数据 */
	SERVER_GET_GAME_INFO			= 7112, /* 玩牌服务器请求获取其他游戏相关数据 */
	SERVER_GET_GAME_INFO_BACK		= 7113, /* 返回游戏数据给玩牌服务器 */
	SERVER_LAOHUJI_INFO				= 7114, /* 玩牌服务器推送老虎机消息到流水DB与大喇叭服务器 */
	SERVER_INCR_USER_TIPS			= 7115, /* 玩牌服务器请求增减玩家免费提示次数 */
	SERVER_RECONNECT_REQ			= 7201, /* 平台用于统计客户端重连 */
	/* 对战 */
	SERVER_DZ_GAME_START_REQ		= 7210, /* 对战模式玩牌服务器请求游戏开始 */
	SERVER_DZ_GAME_START_RES		= 7211, /* 对战模式玩牌服务器请求游戏开始返回 */
	SERVER_DZ_UPDATE_USER_INFO		= 7212, /* 对战模式玩牌服务器更新玩家个人信息 */
	SERVER_DZ_UPDATE_USER_INFO_LITTLE= 7213, /* 对战模式玩牌服务器更新玩家个人信息小结算 */
	SERVER_DZ_DISSOLVE_ROOM_REQ	 	= 7214, /* 对战模式玩牌服务器解散房间请求 */
	SERVER_DZ_DISSOLVE_ROOM_RES	    = 7215, /* 对战模式玩牌服务器解散房间返回 */
	SERVER_ALL_PLAYER_DOWN			= 7217, /* 玩牌服务器通知datasvr 房间里所有的玩家已经断线或者退出 */
	SERVER_DELETE_ROOM_REQ			= 7219, /* datasvr发送给玩牌服务器，查询是否可以删掉房间 */
	SERVER_DELETE_ROOM_RESP			= 7218, /* 玩牌服务器发送给datasvr， 回复是否可以删掉房间 */
	SERVER_LOGOUT_ROOM_REQ			= 7220, /* 玩牌服务器请求退出房间 */
	SERVER_LOGOUT_ROOM_RESP			= 7221, /* 退出房间成功返回 */
	
	SERVER_ROOM_CONFIG_REQ			= 10004,/* 请求房间配置 */
	SERVER_ROOM_CONFIG_RES			= 10005,/* 房间配置返回 */
	SERVER_REQUEST_RECOVER_DATA		= 10010,/* 向恢复服请求数据 */
	SERVER_RECOVER_DATA_RES			= 10011,/* 恢复服数据返回 */
	SERVER_RECOVER_DATA_OVER		= 10012,/* 恢复服数据返回结束 */

};

enum client_command
{
	CLIENT_LOGIN_REQ				= 1001,     /* 登录 */
	CLIENT_LOGOUT_REQ				= 1002,		/* 退出 */
	CLIENT_READY_REQ				= 1003,	    /* 准备 */
	CLIENT_BET_REQ		 			= 1004,		/* 操作 */
	CLIENT_CHAT_REQ					= 1005,
	CLIENT_FACE_REQ					= 1006,
	CLIENT_CHANGE_REQ            = 1007,		/* 换桌 */
	CLIENT_ROBOT_REQ             = 1008,		/* 托管 */
	CLIENT_INFO_REQ              = 1009,		/* 个人信息 */
	CLIENT_TABLE_INFO_REQ        = 1010,		/* 牌桌信息 */
	CLIENT_EMOTION_REQ           = 1011,      	/* 互动表情 */
	CLIENT_PROP_REQ              = 1012,      	/* game prop */
	CLIENT_BOX_REQ               = 1013,
	CLIENT_ACTIVE_REQ            = 1014,
	CLIENT_BETTING_REQ           = 1015,		/* 外围下注 */
	CLIENT_UPTABLE_INFO_REQ      = 1016,		/* 上桌列表 */
	CLIENT_UPTABLE_APPLY_REQ     = 1017,		/* 申请上桌 */
	CLIENT_DOWNTABLE_AHEAD_REQ   = 1018,		
	CLIENT_DOWNTABLE_REQ         = 1019,		/* 申请下桌 */
	CLIENT_RETURN_REQ            = 1020,
	CLIENT_DAEMONIZE_REQ         = 1021,
	CLINET_UPBANKER_REQ          = 1022,
	CLINET_UPBANKER_INFO_REQ     = 1023,
	CLINET_DOWN_BANKER_REQ       = 1024,
	CLINET_HEART_BEAT_REQ        = 1025,		/* 心跳 */

	CLINET_TREND_REQ             = 1040,
	CLIENT_ALL_PLAYERS_REQ       = 1051,
	CLIENT_UP_GUEST_REQ          = 1052,
	CLIENT_DOWN_GUEST_REQ        = 1053,
	CLIENT_POOL_INFO_REQ         = 1054,
	CLINET_OTHER_SHOW_REQ        = 1056,		/* 亮牌 */
	CLIENT_CHOOSE_CARDS_REQ		 = 1057,
	CLIENT_TIP					 = 1059,	
	CLIENT_CHOSE_BETS_NUM		 = 1060,
	CLIENT_DETAL_INFO_REQ        = 1070,

	CLIENT_RANK_REQ              = 1080,
	CLIENT_HISTORY_REQ           = 1090,		

	CLIENT_PREPLAY_ONE_REQ		 = 1091,    	/*叫地主*/
	CLIENT_PREPLAY_TWO_REQ		 = 1092,		/*抢地主*/
	CLIENT_PLAY_CARD_REQ 		 = 1093,		/*玩牌*/
	CLIENT_WIN					 = 1094,
	CLIENT_PC					 = 1095,	
	CLIENT_ROBOT_NEED_REQ		 = 1096,	
	//解散房间
	CLIENT_DISSOLVE_ROOM_REQ	 = 10000,
	CLIENT_DISSOLVE_ACTION_REQ   = 10001,
	/* 对战 */
	CLIENT_DZ_LOGIN_REQ			 = 1200,

	/* 跑胡子游戏 */
	CLIENT_PHZ_OUT_CARD_REQ		 = 1300,			//出牌命令
	CLIENT_PHZ_OPERATE_CARD_REQ	 = 1301,			//操作扑克
	CLIENT_PHZ_CHANGE_CARD_REQ	 = 1302,			//请求交换扑克
	CLIENT_PHZ_UPDATE_CARD_REQ	 = 1303,			//请求更新扑克
	CLIENT_PHZ_PIAO_REQ			 = 1304,			//请求飘
	CLIENT_PHZ_PRE_OPERATE_REQ	 = 1305,			//预操作请求
	CLIENT_PHZ_OFFLINE_INFO_REQ	 = 1306,			//断线信息请求
	CLIENT_PHZ_HAND_DETAIL_REQ	 = 1307,			//手牌详情请求
	CLIENT_PHZ_FINAL_END_REQ	 = 1400,			//最终结算面板请求
	CLIENT_PHZ_GAINS_REQ		 = 1401,			//战绩请求
};

enum client_action
{
	PLAYER_CALL           = 2001,       /* call */
	PLAYER_RAISE          = 2002,       /* raise */
	PLAYER_COMPARE        = 2003,       /* compare */
	PLAYER_SEE            = 2004,		/* see */
	PLAYER_FOLD           = 2005,       /* fold */
	PLAYER_ALLIN          = 2006,		/* all in */
	PLAYER_ALLIN_COMPARE  = 2007,		/* all in compare */
};

enum prop_item
{
	CHANGE_CARD				= 3001,			/* change card */
	FORBIDDEN_CARD			= 3002,			/* forbidden compare card */
	DOUBLE_CARD_FOUR		= 3003,			/* compare four multiple bet card */
	DOUBLE_CARD_SIX			= 3004,			/* compare six multiple bet card */
	DOUBLE_CARD_EIGHT		= 3005,			/* compare eight multiple bet card */
	NOSEE_CARD				= 3006,			/* cannot see */
};

enum server_command
{
	SERVER_LOGIN_SUCC_UC       		 = 4000,
	SERVER_LOGIN_SUCC_BC       		 = 4001,
	SERVER_LOGIN_ERR_UC         	 = 4002,
	SERVER_REBIND_UC				 = 4003,
	SERVER_LOGOUT_SUCC_BC			 = 4004,
	SERVER_LOGOUT_ERR_UC			 = 4005,
	SERVER_TABLE_INFO_UC			 = 4006,	/* 牌桌信息 */
	SERVER_READY_SUCC_BC			 = 4007,	/* 准备成功 */
	SERVER_READY_ERR_UC				 = 4008,
	SERVER_GAME_START_BC			 = 4009,
	SERVER_NEXT_BET_BC				 = 4010,	/* 下一个执行动作的玩家 */
	SERVER_BET_SUCC_BC				 = 4011,	/* 玩家操作结果的广播 */
	SERVER_BET_SUCC_UC				 = 4012,
	SERVER_BET_ERR_UC                = 4013,
	SERVER_GAME_END_BC				 = 4014,	/* 游戏结束 */
	SERVER_GAME_PREREADY_BC          = 4015,
	SERVER_CHAT_BC					 = 4016,
	SERVER_FACE_BC					 = 4017,
	SERVER_ROBOT_SER_UC              = 4018,
	SERVER_ROBOT_NEED_UC             = 4019,
	SERVER_UPDATE_INFO_BC			 = 4020,
	SERVER_EMOTION_BC				 = 4021,
	SERVER_PROP_SUCC_UC              = 4022,
	SERVER_PROP_SUCC_BC              = 4023,
	SERVER_PROP_ERR_UC               = 4024,
	SERVER_BOX_SUCC_BC				 = 4025,
	SERVER_ACTIVE_SUCC_UC            = 4026,
	SERVER_BETTING_SUCC_UC			 = 4027,	/* 押注成功 */
	SERVER_ACTIVE_UPDATE_BC			 = 4028,	/* 旁观押注更新 */
	SERVER_UPTABLE_INFO_UC			 = 4029,	/* 上桌列表信息 */
	SERVER_APPLY_UPTABLE_UC			 = 4030,	/* 申请上桌成功单播 */
	SERVER_UPTABLE_SUCC_BC			 = 4031,	/* 有玩家上桌 */
	SERVER_AHEAD_DOWNTABLE_UC		 = 4032,
	SERVER_DOWNTABLE_SUCC_BC		 = 4033,	/* 有玩家下桌 */
	SERVER_START_BET_BC				 = 4034,	/* 押注开始 打鸟*/
	SERVER_STOP_BET_BC				 = 4035,	/* 停止外围押注 打鸟 */
	SERVER_WIN_UC					 = 4036,	/* 押注奖励返还 */
	SERVER_BETTING_ERR_UC			 = 4037,	/* 押注失败 打鸟*/
	SERVER_UPTABLE_ERR_UC			 = 4038,	/* 上桌失败 */
	SERVER_RETURN_UC                 = 4039,
	SERVER_REWARD_SUCC_UC            = 4040,
	SERVER_DAEMONIZE_SUCC_UC		 = 4041,
	SERVER_BANKER_CANDIDATE_UC       = 4042,
	SERVER_COMPARE_INFO_BC           = 4043,
	SERVER_DOWN_BANKER_UC            = 4044,
	SERVER_GIVE_UP_BANKER_BC         = 4045,	
	SERVER_GET_BANKER_BC             = 4046,
	SERVER_SHORT_UPTABLE_INFO_BC     = 4049,

	SERVER_MULTI_BETS				 = 4060,	/* 选择倍率 */
	SERVER_CHOSE_COMPLETE			 = 4065,	/* 完成组牌 */
	SERVER_COMPARE_CARDS_BC			 = 4066,	/* 结算 */
	SERVER_TIP						 = 4067,	/* 没用的 */
	SERVER_SECOND_CARD				 = 4068,	/* 第二轮明牌 */
	SERVER_THIRD_CARD				 = 4069,	/* 第三轮明牌 */
	SERVER_GAME_DARK_CARD			 = 4075,	/* 第一轮发的暗牌 */
	SERVER_START_COUNTDOWN			 = 4084,	/* 普通场的 */
	SERVER_CHANGE_BANKER			 = 4085,	/* 普通场的 */
	SERVER_BET_OVERSTEP_UC			 = 4086,
	SERVER_BETS_BC					 = 4087,

	SERVER_TREND_UC                  = 4100,
	SERVER_ALL_PLAYER_INFO_UC        = 4110,
	SERVER_UP_GUEST_SEAT_ERROR_UC    = 4111,
	SERVER_UP_GUEST_SEAT_SUC_BC      = 4112,
	//SERVER_DOWN_GUEST_SEAT_ERR_UC  = 4113,
	SERVER_DOWN_GUEST_SEAT_BC        = 4114,
	SERVER_POOL_INFO_UC              = 4115,

	SERVER_POOL_ALTER_BC             = 4116,
	SERVER_ROBOT_SER                 = 4117,
	SERVER_COMMUNITY_BC              = 4118,

	SERVER_TWO_COMMUNITY_UC          = 4119,
	SERVER_EMOTION_NOSEAT_BC         = 4120,
	SERVER_OTHER_SHOW_BC             = 4121,	/* 亮牌 */
	SERVER_BANNE_UC 			     = 4122,
	SERVER_GAME_RESULT_BC			 = 4123,
	SERVER_UPBANKER_ERR_UC			 = 4124,

	SERVER_DETAL_INFO_UC             = 4140,
	SERVER_DETAL_INFO_ERROR_UC       = 4141,

	SERVER_RANK_UC                   = 4160,
	SERVER_LOTTERY_SHOW_CARDS        = 4170,
	SERVER_HISTORY_UC                = 4171,
	SERVER_MULTI_OF_LOSE_BC          = 4210,
	SERVER_COPARE_RESULT_FORROBOT    = 4212,

	SERVER_PREPLAY_ONE_BC		 	 = 4214,		/* 开始叫地主 */
	SERVER_PREPLAY_ONE_SUCC_BC	 	 = 4215,		/* 叫地主操作成功 */
	SERVER_PREPLAY_TWO_BC		 	 = 4216,		/* 抢地主 */	
	SERVER_PREPLAY_TWO_SUCC_BC	 	 = 4217,		/* 抢地主成功 */
	SERVER_LANDLORD_BC 			 	 = 4218,		/* 地主广播 */
	SERVER_PLAY_CARD_BC				 = 4219,		/* 玩牌 */
	SERVER_PLAY_CARD_SUCC_BC		 = 4220,		/* 玩牌成功 */
	SERVER_PLAY_CARD_ERR_BC		     = 4221,		/* 玩牌错误 */
	SERVER_ROBOT_BC					 = 4222,		/* 托管 */
	SERVER_COMFIMATION_TASK_BC		 = 4223,		/* 确定底牌和手牌任务 */
	SERVER_TASK_SUCC_BC				 = 4224,		/* 有手牌或底牌任务 */
	SEVER_BOOM_BC					 = 4225, 		/* 炸弹广播 */
	SEVER_COUNT_CARD	             = 4226,		/* */
	SERVER_GAME_SINGLECARD			 = 4227,		/* 最后手牌广播 */
	SERVER_PLAYER_WIN				 = 4228,
	SERVER_ROUND_END				 = 4229,		/* 回合达到最大回合 */  
	SEVER_PC_BC						 = 4230,
	SERVER_GAME_START_UC			 = 4231,		/* 游戏开始单播，发牌 */
	SERVER_PLAYER_OFFLINE_BC		 = 5130,        //离线广播
	//解散房间
	SERVER_APPLY_DISSOLVE_ROOM_ERR_UC 	= 15000,
	SERVER_APPLY_DISSOLVE_ROOM_SUCC_BC 	= 15001,
	SERVER_DISSOLVE_ACTION_SUCC_BC 		= 15002,
	SERVER_DISSOLVE_ROOM_RESULT_BC		= 15003,	
	SERVER_VIDEO_DATA_SAVE				= 10002,   //保存录像数据
	SERVER_VIDEO_DATA_ERR_RESP			= 10003,   //保存录像错误
	/* 对战 */
	SERVER_DZ_LOGIN_SUCC_RES		= 4400, /* 对战模式登录成功返回 */
	SERVER_DZ_LOGIN_ERR_RES			= 4401, /* 对战模式登录失败返回 */
	/* 心跳返回 */
	SERVER_HEART_BEAT_RES           = 5014,
	/* 跑胡子游戏 */
	SERVER_PHZ_OPERATE_NOTIFY		= 6000,			//操作提示
	SERVER_PHZ_OPERATE_CARD_RES		= 6001,			//操作结果回应
	SERVER_PHZ_OUT_CARD_NOTIFY		= 6002,			//出牌提示
	SERVER_PHZ_OUT_CARD_RES			= 6003,			//用户出牌结果回应
	SERVER_PHZ_SEND_CARD			= 6004,			//发牌命令
	SERVER_PHZ_CHANGE_CARD_RES		= 6005,			//交换扑克返回
	SERVER_PHZ_UPDATE_CARD_RES		= 6006,			//更新扑克返回
	SERVER_PHZ_OPERATE_RES			= 6007,			//操作回应
	SERVER_PHZ_UPDATE_ABANDON_CARD	= 6008,			//更新放弃的牌
	SERVER_PHZ_START_PIAO			= 6009,			//开始飘操作
	SERVER_PHZ_PIAO_SUCC			= 6010,			//飘成功
	SERVER_PHZ_PIAO_ERR				= 6011,			//飘失败
	SERVER_PHZ_XIANG_GONG			= 6012,			//相公返回
	SERVER_PHZ_PRE_OPERATE_RES		= 6013,			//预操作返回
	SERVER_PHZ_PRE_OPERATE_NOTIFY	= 6014,			//预操作提示
	SERVER_PHZ_OFFLINE_INFO_RES		= 6015,			//断线信息返回
	SERVER_PHZ_OFFLINE_INFO_ERR		= 6016,			//断线信息错误返回
	SERVER_PHZ_CHOU_NOTIFY			= 6017,			//臭牌提示
	SERVER_PHZ_HAND_DETAIL_RES		= 6018,			//手牌详情返回
	SERVER_PHZ_FINAL_END_RES		= 6100,			//最终结算返回
	SERVER_PHZ_GAINS_RES			= 6101,			//战绩返回
	SERVER_PHZ_CYCLE_END		    = 6019          //一圈结束
};

#endif
