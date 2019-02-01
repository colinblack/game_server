/*
 *note 定义了农牧场模块间调用CGI主调ID，接口与DBC被调ID，操作接口ID
 *date 2009-09-11
 */
#ifndef _LS_VOTE_DEFINE_H
#define _LS_VOTE_DEFINE_H
#include "logapi.h"
//模块间调用(cgi调用DBC专用)

#define LS_VOTE_INIT(master)       loginit(master);
#define LS_VOTE_START                   logbegin;

#define LS_VOTE_ENDSUCC(master, slave, interface, ret)  logend(slave, interface, NULL, "", ret);
#define LS_VOTE_ENDERROR(master, slave, interface, ret) logend(slave, interface, NULL, "", ret); 

//#define LS_VOTE_INIT(master)                                   int g_LS_VOTE_CGI_MASTERID = master; CLogServerApp g_cLogApp(0,false,0); long long ll_StartTime, ll_EndTime;
//#define LS_VOTE_DECLARE						extern int g_LS_VOTE_CGI_MASTERID;// extern CLogServerApp g_cLogApp; extern long long ll_StartTime, ll_EndTime;
//#define LS_VOTE_INIT_EXTERN               		       extern int g_LS_VOTE_CGI_MASTERID; //extern CLogServerApp g_cLogApp; extern long long ll_StartTime, ll_EndTime;
//#define LS_VOTE_START                                              mtime(ll_StartTime);
//#define LS_VOTE_ENDSUCC(master, slave, interface, ret)  { mtime(ll_EndTime); g_cLogApp.setIni(master, slave, interface, "", 0, 0,(__FILE__), (__LINE__), g_cLogApp.getNowtime(),"", (ret), 0, (ll_EndTime-ll_StartTime) ); g_cLogApp.Write(1);}
//#define LS_VOTE_ENDERROR(master, slave, interface, ret) { mtime(ll_EndTime); g_cLogApp.setIni(master, slave, interface, "", 0, 0,(__FILE__), (__LINE__), g_cLogApp.getNowtime(),"", (ret), 1, (ll_EndTime-ll_StartTime) ); g_cLogApp.Write(1);}

//Add-Begin by dantezhu in 2010-01-18 16:32:10
// -----------------------------------------------------------------------------
//
// 调用结果，用于模块间调用,  API_Log_Write最后的参数
//
// -----------------------------------------------------------------------------
typedef enum
{
	LS_RET_SUCC = 0,	// 成功
	LS_RET_FAIL,		// 失败
	LS_RET_LOGICERROR,  // 逻辑失败
	LS_RET_DBERROR, 	// 数据库异常
	LS_RET_NETERROR, 	// 网络异常
	LS_RET_IOERROR, 	// IO异常
	LS_RET_OTHERERROR 	// 其它异常
} LogResult;


// -----------------------------------------------------------------------------
//
// 操作类型
//
// -----------------------------------------------------------------------------
#define LS_OP_INSERT			"insert"
#define LS_OP_SELECT			"select"
#define LS_OP_UPDATE			"update"
#define LS_OP_DELETE			"delete"
#define LS_OP_COUNT				"count"
//Add-End

//定义cgi主调ID
#define LS_VOTE_CGI_PASTURE_ENTER                      413049
#define LS_VOTE_CGI_PASTURE_CLEAR_LOG              413050
#define LS_VOTE_CGI_PASTURE_GET_FEEDS              413051
#define LS_VOTE_CGI_PASTURE_GET_REPERTORY      413052
#define LS_VOTE_CGI_PASTURE_GET_USERINFO        413053
#define LS_VOTE_CGI_PASTURE_REGIST                     413054
#define LS_VOTE_CGI_PASTURE_UP_ANIMALHOUSE   413055
#define LS_VOTE_CGI_PASTURE_UP_TASK                  413056
#define LS_VOTE_CGI_PASTURE_BUY_ANIMAL            413057
#define LS_VOTE_CGI_PASTURE_GET_ANIMAL            413058  
#define LS_VOTE_CGI_PASTURE_FEED_FOOD              413059
#define LS_VOTE_CGI_PASTURE_GET_FOOD                413060
#define LS_VOTE_CGI_PASTURE_GET_EXP                   413061
#define LS_VOTE_CGI_PASTURE_HARVEST                   413062
#define LS_VOTE_CGI_PASTURE_DEMOLISH                 413063
#define LS_VOTE_CGI_PASTURE_HELP                         413064
#define LS_VOTE_CGI_PASTURE_POST_PRODUCT        413065
#define LS_VOTE_CGI_PASTURE_SALE_PRODUCT        413066
#define LS_VOTE_CGI_PASTURE_STEAL_PRODUCT      413067
#define LS_VOTE_CGI_PASTURE_SET_PARADE		 413078
#define LS_VOTE_CGI_PASTURE_GET_PARADE		 413079
#define LS_VOTE_CGI_PASTURE_TOOL				413084
#define LS_VOTE_CGI_PASTURE_PAYSRV			413087 
#define LS_VOTE_CGI_PASTURE_FEED_SPECIAL		413125
#define LS_VOTE_CGI_FARM_INVITE				204413130
#define LS_VOTE_CGI_FARM_XYCLASSGETEXP		204413131
#define LS_VOTE_CGI_FARM_ISINSTALLABLE		204413149 
#define LS_VOTE_CGI_PASTURE_NOTICE			216413155
#define LS_VOTE_CGI_FARM_WORKSHOP			204413152
#define LS_VOTE_CGI_PASTURE_MQZONE_HPAGE	204413159
#define LS_VOTE_CGI_PASTURE_MQZONE_POST		204413160
#define LS_VOTE_CGI_PASTURE_MQZONE_HARVEST	204413161
#define LS_VOTE_CGI_PASTURE_MQZONE_STEAL	204413162
#define LS_VOTE_CGI_PASTURE_MQZONE_FEED		204413163
#define LS_VOTE_CGI_PASTURE_MQZONE_OPTFLAG	204413164
#define LS_VOTE_CGI_PASTURE_MQZONE_MONEY	204413165
#define LS_VOTE_CGI_PASTURE_MQZONE_FOOD		204413166 
#define LS_VOTE_CGI_PASTURE_FIGHT 			204413154
#define LS_VOTE_CGI_WH_GET_PASTURE_REP		204413156
#define LS_VOTE_CGI_WH_DEL_PASTURE_REP		204413157

//定义被调ID
#define LS_VOTE_XIAOYOU						413033
#define LS_VOTE_DBC_FARM_REPERTORY                    413044
#define LS_VOTE_DBC_PASTURE_USER                        413046
#define LS_VOTE_DBC_PASTURE_ANIMAL                    413047
#define LS_VOTE_DBC_PASTURE_REPERTORY              413048
#define LS_VOTE_DBC_FARM_USER                              413043
#define LS_VOTE_DBC_FARM_ITEM                              413045
#define LS_VOTE_BITMAP_PASTURE_STEAL                413068
#define LS_VOTE_DBC_FARM_USER_DB                       413069
#define LS_VOTE_BIMAP_FARM_HUNPAI                     413072
#define LS_VOTE_DBC_PASTURE_REGISTCNT		413086
#define LS_VOTE_BIMAP_PASTURE_REGIST			413077
#define LS_VOTE_DBC_PASTURE_TOOL				413083
#define LS_VOTE_DIRTYCHECK_AGENT				413080
#define LS_VOTE_PASTURE_ENTER_SRV				413085
#define LS_VOTE_DBC_HAPPYFARM_CONF			413076
#define LS_VOTE_PASTURE_HELP_SRV				413092
#define LS_VOTE_PASTURE_STEAL_SRV				413100
#define LS_VOTE_QZONE_NICK_SRV				413126
#define LS_VOTE_XIAOYOU_NICK_SRV				413127
#define LS_VOTE_MQZONE							204413128
#define LS_VOTE_DBC_FARM_TOOL					204413153

//定义操作接口ID
#define LS_VOTE_XIAOYOU_CHECKFRIEND 			60007
#define LS_VOTE_DBC_FARM_REPERTORY_READ        60021
#define LS_VOTE_DBC_FARM_REPERTORY_WRITE      60022
#define LS_VOTE_DBC_PASTURE_USER_READ             60025
#define LS_VOTE_DBC_PASTURE_USER_WRITE           60026
#define LS_VOTE_DBC_PASTURE_ANIMAL_READ         60027
#define LS_VOTE_DBC_PASTURE_ANIMAL_WRITE       60028
#define LS_VOTE_DBC_PASTURE_REPERTORY_READ   60029
#define LS_VOTE_DBC_PASTURE_REPERTORY_WRITE 60030
#define LS_VOTE_DBC_FARM_USER_READ                   60019
#define LS_VOTE_DBC_FARM_USER_WRITE                 60020
#define LS_VOTE_DBC_FARM_ITEM_WRITE                 60035
#define LS_VOTE_DBC_FARM_ITEM_READ                   60023
#define LS_VOTE_BITMAP_PASTURE_STEAL_READ     60031
#define LS_VOTE_BITMAP_PASTURE_STEAL_WRITE   60032
#define LS_VOTE_DBC_FARM_USER_DB_READ            60033
#define LS_VOTE_DBC_FARM_USER_DB_WRITE          60034
#define LS_VOTE_BIMAP_FARM_HUNPAI_READ          60036
#define LS_VOTE_BIMAP_FARM_HUNPAI_WRITE        60037       
#define LS_VOTE_DBC_PASTURE_REGISTCNT_READ	60047
#define LS_VOTE_DBC_PASTURE_REGISTCNT_WRITE	60048
#define LS_VOTE_BIMAP_PASTURE_REGIST_READ	60040
#define LS_VOTE_BIMAP_PASTURE_REGIST_WRITE	60041
#define LS_VOTE_DBC_PASTURE_TOOL_READ		60044
#define LS_VOTE_DBC_PASTURE_TOOL_WRITE 		60045
#define LS_VOTE_DIRTYCHECK_AGENT_READ		60042
#define LS_VOTE_PASTURE_ENTER_SRV_READ		60046
#define LS_VOTE_DBC_HAPPYFARM_CONF_READ		60038
#define LS_VOTE_PASTURE_HELP_SRV_REQ			60049
#define LS_VOTE_PASTURE_STEAL_SRV_READ		60056
#define LS_VOTE_PASTURE_QZONE_NICK_REQ		60075
#define LS_VOTE_PASTURE_XIAOYOU_NICK_REQ	60076 
#define LS_VOTE_MQZONE_CHECKAPP_REQ			104060077
#define LS_VOTE_XIAOYOU_INVITE_FARMLAND		104060078
#define LS_VOTE_XIAOYOU_INVITE_PASTURE		104060079
#define LS_VOTE_XIAOYOU_GETFRIENDLIST		104060080 
#define LS_VOTE_DBC_FARMLAND_TOOL_READ		104060091
#define LS_VOTE_DBC_FARMLAND_TOOL_WRITE		104060092

//Add-Begin by dantezhu in 2010-01-18 16:00:57
#define LS_SERVER_FARMBASE					204090100
#define LS_IF_FARMBASE_GET					104090101
#define LS_IF_FARMBASE_SET					104090102
#define LS_IF_FARMBASE_DEL					104090103
//Add-End

//Add-Begin by dantezhu in 2010-03-17 19:37:07
#define LS_SERVER_APPBITMAP                 204060100
#define LS_IF_APPBITMAP_GET                 104060101
#define LS_IF_APPBITMAP_MULGET              104060102
#define LS_IF_APPBITMAP_SET                 104060103
////Add-End

#define LV_VOTE_REPORT( ret, callid, modelid ) \
	if ( 0 == ret ) \
	{ \
		LS_VOTE_ENDSUCC( g_LS_VOTE_CGI_MASTERID, callid, modelid, ret ); \
	} \
	else \
	{ \
		LS_VOTE_ENDERROR( g_LS_VOTE_CGI_MASTERID, callid, modelid, ret ); \
	}

#define LS_VOTE_REPORT_PASTURE_USER_WRITE( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_USER, LS_VOTE_DBC_PASTURE_USER_WRITE )
#define LS_VOTE_REPORT_PASTURE_USER_READ( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_USER, LS_VOTE_DBC_PASTURE_USER_READ )
#define LS_VOTE_REPORT_BITMAP_PASTURE_STEAL_WRITE( ret ) 	LV_VOTE_REPORT( ret, LS_VOTE_BITMAP_PASTURE_STEAL, LS_VOTE_BITMAP_PASTURE_STEAL_WRITE )
#define LS_VOTE_REPORT_BITMAP_PASTURE_STEAL_READ( ret )		LV_VOTE_REPORT( ret, LS_VOTE_BITMAP_PASTURE_STEAL, LS_VOTE_BITMAP_PASTURE_STEAL_READ )
#define LV_VOTE_REPORT_PASTURE_ANIMAL_WRITE( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_ANIMAL, LS_VOTE_DBC_PASTURE_ANIMAL_WRITE )
#define LV_VOTE_REPORT_PASTURE_ANIMAL_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_ANIMAL, LS_VOTE_DBC_PASTURE_ANIMAL_READ )
#define LV_VOTE_REPORT_FARMLAND_REPERTORY_WRITE( ret )		LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_REPERTORY, LS_VOTE_DBC_FARM_REPERTORY_WRITE )
#define LV_VOTE_REPORT_FARMLAND_REPERTORY_READ( ret )		LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_REPERTORY, LS_VOTE_DBC_FARM_REPERTORY_READ )
#define LV_VOTE_REPORT_FARMLAND_USER_WRITE( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_USER, LS_VOTE_DBC_FARM_USER_WRITE )
#define LV_VOTE_REPORT_FARMLAND_USER_READ( ret )				LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_USER, LS_VOTE_DBC_FARM_USER_READ )
#define LV_VOTE_REPORT_PASTURE_REPERTORY_WRITE( ret )             LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_REPERTORY, LS_VOTE_DBC_PASTURE_REPERTORY_WRITE )
#define LV_VOTE_REPORT_PASTURE_REPERTORY_READ( ret )               LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_REPERTORY, LS_VOTE_DBC_PASTURE_REPERTORY_READ )
#define LS_VOTE_REPORT_PASTURE_ITEM_READ( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_ITEM, LS_VOTE_DBC_FARM_ITEM_READ )
#define LS_VOTE_REPORT_PASTURE_ITEM_WRITE( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_ITEM, LS_VOTE_DBC_FARM_ITEM_WRITE )
#define LS_VOTE_REPORT_PASTURE_REGISTCNT_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_REGISTCNT, LS_VOTE_DBC_PASTURE_REGISTCNT_READ)
#define LS_VOTE_REPORT_PASTURE_REGISTCNT_WRITE( ret )		LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_REGISTCNT, LS_VOTE_DBC_PASTURE_REGISTCNT_WRITE)
#define LS_VOTE_REPORT_BIMAP_PASTURE_REGIST_READ( ret )		LV_VOTE_REPORT( ret, LS_VOTE_BIMAP_PASTURE_REGIST, LS_VOTE_BIMAP_PASTURE_REGIST_READ)
#define LS_VOTE_REPORT_BIMAP_PASTURE_REGIST_WRITE( ret )		LV_VOTE_REPORT( ret, LS_VOTE_BIMAP_PASTURE_REGIST, LS_VOTE_BIMAP_PASTURE_REGIST_WRITE)
#define LS_VOTE_REPORT_DIRTYCHECK_AGENT_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DIRTYCHECK_AGENT, LS_VOTE_DIRTYCHECK_AGENT_READ)
#define LS_VOTE_REPORT_BIMAP_FARM_HUNPAI_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_BIMAP_FARM_HUNPAI, LS_VOTE_BIMAP_FARM_HUNPAI_READ)
#define LS_VOTE_REPORT_BIMAP_FARM_HUNPAI_WRITE( ret )		LV_VOTE_REPORT( ret, LS_VOTE_BIMAP_FARM_HUNPAI, LS_VOTE_BIMAP_FARM_HUNPAI_WRITE)
#define LS_VOTE_REPORT_PASTURE_TOOL_READ( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_TOOL, LS_VOTE_DBC_PASTURE_TOOL_READ )
#define LS_VOTE_REPORT_PASTURE_TOOL_WRITE( ret ) 				LV_VOTE_REPORT( ret, LS_VOTE_DBC_PASTURE_TOOL, LS_VOTE_DBC_PASTURE_TOOL_WRITE )
#define LS_VOTE_REPORT_PASTURE_ENTER_SRV_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_PASTURE_ENTER_SRV, LS_VOTE_PASTURE_ENTER_SRV_READ)
#define LS_VOTE_REPORT_HAPPYFARM_CONF_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_HAPPYFARM_CONF, LS_VOTE_DBC_HAPPYFARM_CONF_READ)
#define LS_VOTE_REPORT_PASTURE_HELP_SRV_REQ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_PASTURE_HELP_SRV, LS_VOTE_PASTURE_HELP_SRV_REQ )
#define LS_VOTE_REPORT_PASTURE_STEAL_SRV_READ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_PASTURE_STEAL_SRV, LS_VOTE_PASTURE_STEAL_SRV_READ)
#define LS_VOTE_REPORT_PASTURE_QZONE_NICK_REQ( ret )			LV_VOTE_REPORT( ret, LS_VOTE_QZONE_NICK_SRV, LS_VOTE_PASTURE_QZONE_NICK_REQ )
#define LS_VOTE_REPORT_PASTURE_XIAOYOU_NICK_REQ( ret )		LV_VOTE_REPORT( ret, LS_VOTE_XIAOYOU_NICK_SRV, LS_VOTE_PASTURE_XIAOYOU_NICK_REQ )
#define LS_VOTE_REPORT_MQZONE_CHECKAPP_REQ(ret)				LV_VOTE_REPORT( ret, LS_VOTE_MQZONE, LS_VOTE_MQZONE_CHECKAPP_REQ )
#define LS_VOTE_REPORT_XYINVITE_FARMLAND(ret)				LV_VOTE_REPORT( ret, LS_VOTE_XYINVITE, LS_VOTE_XYINVITE_FARMLAND )
#define LS_VOTE_REPORT_XYINVITE_PASTURE(ret)					LV_VOTE_REPORT( ret, LS_VOTE_XYINVITE, LS_VOTE_XYINVITE_PASTURE )
#define LV_VOTE_REPORT_FARMLAND_USER_DB_WRITE( ret )			LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_USER_DB, LS_VOTE_DBC_FARM_USER_DB_WRITE )
#define LV_VOTE_REPORT_FARM_TOOL_READ( ret )					LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_TOOL, LS_VOTE_DBC_FARMLAND_TOOL_READ )
#define LV_VOTE_REPORT_FARM_TOOL_WRITE( ret )					LV_VOTE_REPORT( ret, LS_VOTE_DBC_FARM_TOOL, LS_VOTE_DBC_FARMLAND_TOOL_WRITE )
#define LV_VOTE_REPORT_FARM_BASE_READ( ret )					LV_VOTE_REPORT( ret, LS_SERVER_FARMBASE, LS_IF_FARMBASE_GET)
#define LV_VOTE_REPORT_FARM_BASE_WRITE( ret )					LV_VOTE_REPORT( ret, LS_SERVER_FARMBASE, LS_IF_FARMBASE_SET)


/*************** caller id ***************/ 
#define CALLER_CGI_PLANT        413081
#define CALLER_CGI_GETALLINFO   413112 
#define CALLER_CGI_GETUSERSEED  413113
#define CALLER_CGI_RECLAIM      413115 
#define CALLER_CGI_GETSEEDINFO  413117
#define CALLER_CGI_BUYSEED      413119
#define CALLER_CGI_PLANT_MQZONE         413130
#define CALLER_CGI_GETUSERSEED_MQZONE   413131
#define CALLER_CGI_MIX                  204413132 /* not used */
#define CALLER_CGI_BUYDOG               204413138
#define CALLER_CGI_RECLAIM_PAY          204413139
#define CALLER_CGI_WELCOME              204413140
#define CALLER_CGI_GETTOOLS             204413141
#define CALLER_CGI_SETHEALTH            204413143
#define CALLER_CGI_SENDCHAT             413108
#define CALLER_CGI_CLEARFEED            413111
#define CALLER_CGI_CLEARCHAT            413110
#define CALLER_CGI_GETSTATUS_FILTER     413094
#define CALLER_API_INDEX                413038
#define CALLER_SVR_PLANT    		    204413249
#define CALLER_CGI_STEAL 413037
#define CALLER_CGI_CANVAS 216413144
#define CALLER_CGI_INDEX				413036
#define CALLER_CGI_GETUSERCROP			413089
#define CALLER_CGI_INDEX_MQZONE			413037
#define CALLER_CGI_EXCHANGE				216413142 
#define CALLER_CGI_MISSION				413124
#define CALLER_CGI_FLOWER_GET_CARD	 	413101
#define CALLER_CGI_FLOWER_RECEIVED		413102
#define CALLER_CGI_FLOWER_SEND			413103
#define CALLER_CGI_FLOWER_DEL_MSG_MQZONE 216000005
#define CALLER_CGI_UPGRADE 216000006

/*************** callee id ***************/ 
#define CALLEE_SVR_PLANT        413082 
#define CALLEE_DBC_FEED         413098 
#define CALLEE_DBC_CHAT         413109 
#define CALLEE_DBC_USER         413043
#define CALLEE_DBC_REP          413044 
#define CALLEE_DBC_TOOL         413114 
#define CALLEE_CONF             413116
#define CALLEE_FARMHUNPAI    413118
#define CALLEE_DBC_ITEM         413045 
#define CALLEE_BITMAP_LIMIT     204413137 
#define CALLEE_CONFIG_CENTER    204413142
#define CALLEE_XY_BITMAP         216413145 
#define CALLEE_PDBC_FEED        204413155
#define CALLEE_COUNTDOWN_SVR    216413153
#define CALLEE_DBC_FRIENDFILTER 413095
#define CALLEE_MEM_XY_NICKNAME  216000002
#define CALLEE_DB_USER          413069
#define CALLEE_DB_FARM          216413148 
#define CALLEE_MEM_FARM         413042
#define CALLEE_SVR_STEAL		413039
#define CALLEE_CARD         	216000003
#define CALLEE_FLOWER         	216000004
#define CALLEE_BITMAP_YELLOW	216413149

/*************** interface id ***************/ 
#define IFC_PLANT               60043  
#define IFC_GET_FEED            60054
#define IFC_SET_FEED			60055
#define IFC_CLEARFEED			60064
#define IFC_GET_CHAT            60061
#define IFC_SET_CHAT			60062
#define IFC_CLEARCHAT			60063
#define IFC_SET_FARMHUNPAI 60010
#define IFC_GET_FARM            60017 
#define IFC_SET_FARM            60018 
#define IFC_GET_USER            60019 
#define IFC_GET_REP             60021 
#define IFC_GET_TOOL            60065
#define IFC_PARSE_CONF          60066
#define IFC_GET_SEEDINFO        60067 
#define IFC_SET_REP             60068
#define IFC_SET_USER            60069
#define IFC_GET_ITEM            60023
#define IFC_SET_ITEM            104060035
#define IFC_ADD_ITEM		60058
#define IFC_GET_BITMAP_LIMIT    104060075 
#define IFC_SET_BITMAP_LIMIT    104060076 
#define IFC_GET_CONFIG_CENTER   104060081
#define IFC_SET_DB_FARM    104060086
#define IFC_SELECT_FEED         104060097
#define IFC_INSERT_FEED         104060098
#define IFC_DELETE_FEED         104060099
#define IFC_SET_COUNTDOWN       104060089
#define IFC_GET_FRIENDFILTER    60050
#define IFC_DBC_PURGE           116000012	//农场dbc purge
#define IFC_DBC_REPLACE         116000011	//农场dbc replace
#define IFC_DBC_DELETE          116000010	//农场dbc删除
#define IFC_DBC_INSERT          116000009	//农场dbc插入
#define IFC_DBC_UPDATE          116000008	//农场dbc更新
#define IFC_DBC_GET             116000004	//农场dbc读取
#define IFC_GET_XYBITMAP 104060082
#define IFC_SET_XYBITMAP 104060083
#define IFC_STEAL 60024
#define IFC_GET_BITMAP_YELLOW	116000003


#endif
