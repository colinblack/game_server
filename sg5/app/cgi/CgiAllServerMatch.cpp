/*
 * CgiAllServerMatc.cpp
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */


#include "LogicInc.h"

class CCgiAllServerMatch : public CCgiBase
{

public:

	CCgiAllServerMatch() : CCgiBase("allservermatch")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("viewbasematch", ViewBaseMatch)
	CGI_SET_ACTION_MAP("applybasematch", ApplyBaseMatch)
	CGI_SET_ACTION_MAP("reportbasematch", ReportBaseMatch)
	CGI_SET_ACTION_MAP("viewbaseapplyers", ViewBaseApplyers)
	CGI_SET_ACTION_MAP("viewbaseregular", ViewBaseRegular)
	CGI_SET_ACTION_MAP("viewpersonmatch", ViewPersonMatch)
	CGI_SET_ACTION_MAP("applypersonmatch", ApplyPersonMatch)
	CGI_SET_ACTION_MAP("reportpersonmatch", ReportPersonMatch)
	CGI_SET_ACTION_MAP("guessapply", GuessApply)
	CGI_SET_ACTION_MAP("guessview", GuessView)
	CGI_SET_ACTION_MAP("loadallserverbmatch", LoadBaseMatch)
	CGI_SET_ACTION_MAP("loadallserverpmatch", LoadPersonMatch)
	CGI_SET_ACTION_MAP("viewladder", ViewLadder)
	CGI_SET_ACTION_MAP("refreshladder", RefreshLadder)
	CGI_SET_ACTION_MAP("reportladder", ReportLadder)
	CGI_SET_ACTION_MAP("viewtop1", ViewTopOne)
	CGI_SET_ACTION_MAP("getalliancerecharge", GetAllianceRecharge)
	CGI_SET_ACTION_MAP("reportalliancerecharge", ReportAllianceRecharge)
	CGI_SET_ACTION_MAP("getbarbariankingrank", GetBarbarianKingRank)
	CGI_SET_ACTION_MAP("barbarianingpoint", BarbarianingPoint)
	CGI_SET_ACTION_MAP("getconsumeranklist", GetConsumeRankList)
	CGI_SET_ACTION_MAP("setconsumeuser", SetConsumeUser)
	CGI_SET_ACTION_MAP("getAllServerNewWorldBattlelist", GetAllServerNewWorldBattlelist)
	CGI_SET_ACTION_MAP("setAllServerNewWorldBattleAttack", SetAllServerNewWorldBattleAttack)
	CGI_SET_ACTION_MAP("setAllServerNewWorldBattleArmy", SetAllServerNewWorldBattleArmy)
	CGI_SET_ACTION_MAP("setAllServerNewWorldBattleResult", SetAllServerNewWorldBattleResult)
	CGI_SET_ACTION_MAP("getRechargeRanklist", GetRechargeRankList)
	CGI_SET_ACTION_MAP("setRechargeUser", SetRechargeUser)
	CGI_SET_ACTION_MAP("getPointsRanklist", GetPointsRanklist)
	CGI_SET_ACTION_MAP("setPointsUser", SetPointsUser)
	CGI_SET_ACTION_MAP("RotaryTableDraw", RotaryTableDraw)
	CGI_SET_ACTION_MAP("GetRotaryTableRewardInfo", GetRotaryTableRewardInfo)
	CGI_SET_ACTION_MAP("Double11", Double11)
	CGI_SET_ACTION_MAP("GetDouble11Rcnt", GetDouble11Rcnt)
	CGI_ACTION_MAP_END

	int ViewBaseMatch()
	{
		CLogicAllServerBaseMatch logicBaseMatch;
		unsigned aid = CCGIIn::GetCGIInt("aid");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		int ret = logicBaseMatch.GetBaseMatchInfo(aid, uid, m_jsonResult);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewbasematch&uid=%u&aid=%u", uid, aid);
		return R_SUCCESS;
	}

	int ApplyBaseMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.Apply(uid);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=applybasematch&uid=%u", uid);
		return R_SUCCESS;
	}

	int ReportBaseMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAllServerBaseMatch logicBaseMatch;
		int order = CCGIIn::GetCGIInt("order");
		int result = CCGIIn::GetCGIInt("result");
		int ret = logicBaseMatch.ReportResult(uid, order, result);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=reportbasematch&uid=%u&order=%d&result=%d", uid, order, result);
		return R_SUCCESS;
	}

	int ViewBaseApplyers()
	{
		unsigned aid = CCGIIn::GetCGIInt("aid");
		if (!IsAllianceId(aid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.GetApplyPlayers(aid, m_jsonResult);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewbaseapplyers&aid=%u", aid);
		return R_SUCCESS;
	}

	int ViewBaseRegular()
	{
		unsigned aid = CCGIIn::GetCGIInt("aid");
		if (!IsAllianceId(aid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.GetRegularScore(aid, m_jsonResult);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewbaseregular&aid=%u", aid);
		return R_SUCCESS;
	}

	int GuessApply()
	{
		unsigned gid = CCGIIn::GetCGIInt("gid");
		unsigned coins = CCGIIn::GetCGIInt("coins");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int type = CCGIIn::GetCGIInt("type");
		int lev = CCGIIn::GetCGIInt("level");
		if ( coins <= 0 || type > 2 || type < 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CGI_SEND_LOG("action=guessapply&uid=%u&gid=%d&coins=%d", uid, gid, coins);

		int stage = 10;
		if(type == 0)
		{
			CLogicMatch match;
			if(match.GetStage(stage) != 0){
				error_log("get stage failed");
				return R_ERR_LOGIC;
			}
		}
		else if(type == 1)
		{
			CLogicAllServerBaseMatch match;
			if(match.GetStage(stage) != 0){
				error_log("get stage failed");
				return R_ERR_LOGIC;
			}
		}
		else
		{
			CLogicAllServerPersonMatch match;
			if(match.GetStage(stage,lev) != 0){
				error_log("get stage failed");
				return R_ERR_LOGIC;
			}
		}

		if(stage != 10){
			error_log("stage expect 10 but %d",stage);
			return R_ERR_LOGIC;
		}

		/*
		CLogicPay logicPay;
		DataPay data_pay;
		if(logicPay.GetPay(uid,data_pay) != 0)
		{
			error_log("get %u's cash failed",m_uid);
			return R_ERR_DB;
		}
		if(data_pay.coins < unsigned(coins * PER_BET_COINS))
		{
			error_log("user %u's coins not enough[%u,%u]",m_uid,data_pay.coins,coins * PER_BET_COINS);
			return R_ERR_LOGIC;
		}
		*/

		CLogicUser logicUser;
		int ret = logicUser.ChangeBet(uid,coins*-1*PER_BET_COINS, true);
		if(ret == 0)
		{
			CLogicAllServerGuess logicAllServerGuess;
			int ret = logicAllServerGuess.ApplyGuess(uid,gid,coins,type,lev);
			if (0 != ret)
			{
				error_log("user %u apply guess failed [%u %u]", m_uid, gid, coins);
				logicUser.ChangeBet(uid,coins*PER_BET_COINS, true);
				return R_ERR_LOGIC;
			}
		}
		else
			return ret;

		//logicPay.ChangePay(uid,0,coins*-1*PER_BET_COINS,"MATCHGUESSAPPLY",1);
		return R_SUCCESS;
	}

	int GuessView()
	{
		int type = CCGIIn::GetCGIInt("type");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if(type > 2 || type < 0){
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		int level = CCGIIn::GetCGIInt("level");

		CLogicAllServerGuess logicAllServerGuess;
		int ret = logicAllServerGuess.ViewGuess(uid,m_jsonResult,type,level);
		if (0 != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GuessViewA&uid=%u,level=%d",uid,level);
		return 0;
	}

	int ViewPersonMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			return R_ERR_PARAM;
		}
		int level = 0;
		level = CCGIIn::GetCGIInt("level");
		CLogicAllServerPersonMatch logicPersonMatch;
		int ret = logicPersonMatch.GetBaseMatchInfo(uid, m_jsonResult,level);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewpersonmatch&uid=%u,level=%d", uid, level);
		return 0;
	}

	int ApplyPersonMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			error_log("not valid uid,%u", uid);
			return R_ERR_PARAM;
		}
		int level = CCGIIn::GetCGIInt("level");

		CLogicAllServerPersonMatch logicPersonMatch;
		int ret = logicPersonMatch.Apply(uid,level);
		//error_log("[Apply ret=%d]",ret);
		if (ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=applypersonmatch&uid=%u,level=%d", uid, level);

		return R_SUCCESS;
	}

	int ReportPersonMatch()
	{
		CLogicAllServerPersonMatch logicPersonMatch;
		int order = CCGIIn::GetCGIInt("order");
		int result = CCGIIn::GetCGIInt("result");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int level = CCGIIn::GetCGIInt("level");
		if (!IsValidUid(uid))
		{
			return R_ERR_PARAM;
		}
		int ret = logicPersonMatch.ReportResult(uid, order, result,level);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=reportallserverpersonmatch&uid=%u&order=%d&result=%d,level=%d",
				uid, order, result,level);
		return R_SUCCESS;
	}

	int LoadBaseMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned userid = CCGIIn::GetCGIInt("userid");
		if (!IsValidAllServerBMatchInstId(uid))
		{
			return R_ERR_PARAM;
		}
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.Load(uid, userid, m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=loadbasemtach&operated=%u&operator=%u", uid, userid);
		return 0;
	}

	int LoadPersonMatch()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned userid = CCGIIn::GetCGIInt("userid");
		if (!IsValidAllServerPersonMatchId(uid))
		{
			return R_ERR_PARAM;
		}
		CLogicAllServerPersonMatch logicPersonMatch;
		int ret = logicPersonMatch.Load(uid,userid,m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=loadpersonmtach&operated=%u&operator=%u", uid, userid);
		return 0;
	}

	int ViewLadder()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned level = CCGIIn::GetCGIInt("level");
		CLogicAllServerLadder logicLadder;
		int ret = logicLadder.ViewLadder(uid, m_jsonResult,level);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int RefreshLadder()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned level = CCGIIn::GetCGIInt("level");
		CLogicAllServerLadder logicLadder;
		int ret = logicLadder.Refresh(uid, m_jsonResult,level);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=refreshladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ReportLadder()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned level = CCGIIn::GetCGIInt("level");
		string data = CCGIIn::GetCGIStr("data");
		//debug_log("uid=%u,level=%u,data=%s",uid,level,data.c_str());
		Json::Value jsonData;
		Json::Reader reader;
		reader.parse(data,jsonData);
		CLogicAllServerLadder logicLadder;
		int ret = logicLadder.ReportResult(uid, jsonData, level);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=reportladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ViewTopOne()
	{
		CLogicAllServerLadder logicLadder;
		int ret = logicLadder.ViewTopOne(m_jsonResult["top1"]);
		if (0 != ret)
		{
			return ret;
		}
		return 0;
	}

	int GetAllianceRecharge()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		CLogicRechargeAlliance logicAllianceRecharge;
		int ret = logicAllianceRecharge.ReplyRechargeAllianceData(jsonData,m_jsonResult);
		return ret;
	}

	int ReportAllianceRecharge()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		CLogicRechargeAlliance logicAllianceRecharge;
		return logicAllianceRecharge.ReceiveRechargeAllianceData(jsonData);
	}

	int GetBarbarianKingRank()
	{
		unsigned group = CCGIIn::GetCGIInt("group");
		CLogicBarbarianKing logicBarbarianKing;
		return logicBarbarianKing.ReplyBKList(group,m_jsonResult["barbariankingrank"]);
	}
	int BarbarianingPoint()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned uid;
		Json::GetUInt(jsonData, "uid", uid);

		CLogicBarbarianKing logicBarbarianKing;
		CGI_SEND_LOG("action=barbarianingpoint&uid=%u", uid);
		return logicBarbarianKing.ReplyBKChallenger(jsonData);
	}

	int GetConsumeRankList()
	{
		CLogicConsumeRank logicConsumeRank;
		return logicConsumeRank.ReplyList(m_jsonResult["getconsumeranklist"]);
	}
	int SetConsumeUser()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned uid = 0, cashDay = 0, cashAll = 0;
		Json::GetUInt(jsonData, "uid", uid);
		Json::GetUInt(jsonData, "cashDay", cashDay);
		Json::GetUInt(jsonData, "cashAll", cashAll);
		string name;
		Json::GetString(jsonData, "name", name);

		CLogicConsumeRank logicConsumeRank;
		CGI_SEND_LOG("action=setconsumeuser&uid=%u", uid);
		return logicConsumeRank.ReplyUser(uid, cashDay, cashAll, name, m_jsonResult["setconsumeuser"]);
	}

	int GetAllServerNewWorldBattlelist()
	{
		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		return logicAllServerNewWorldBattle.ReplyList(m_jsonResult["getAllServerNewWorldBattlelist"]);
	}
	int SetAllServerNewWorldBattleAttack()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned attack = 0, kingdom = 0, defend = 0;
		Json::GetUInt(jsonData, "attack", attack);
		Json::GetUInt(jsonData, "kingdom", kingdom);
		Json::GetUInt(jsonData, "defend", defend);

		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		CGI_SEND_LOG("action=setAllServerNewWorldBattleAttack&attack=%u&kingdom=%u&defend=%u", attack,kingdom,defend);
		return logicAllServerNewWorldBattle.ReplyAttack(attack, kingdom, defend, m_jsonResult["setAllServerNewWorldBattleAttack"]);
	}
	int SetAllServerNewWorldBattleArmy()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned serverid = 0, domain = 0;
		Json::GetUInt(jsonData, "serverid", serverid);
		Json::GetUInt(jsonData, "domain", domain);
		unsigned army[3];
		army[0] = jsonData["army"][0u].asUInt();
		army[1] = jsonData["army"][1u].asUInt();
		army[2] = jsonData["army"][2u].asUInt();
		string host;
		Json::GetString(jsonData, "host", host);

		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		CGI_SEND_LOG("action=setAllServerNewWorldBattleArmy");
		return logicAllServerNewWorldBattle.ReplyArmy(serverid, domain, army, host);
	}
	int SetAllServerNewWorldBattleResult()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned defend = 0, result = 0;
		Json::GetUInt(jsonData, "defend", defend);
		Json::GetUInt(jsonData, "result", result);

		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		CGI_SEND_LOG("action=setAllServerNewWorldBattleResult");
		return logicAllServerNewWorldBattle.ReplyResult(defend, result);
	}

	int GetRechargeRankList()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicRechargeRank logicRechargeRank;
		return logicRechargeRank.ReplyList(uid, m_jsonResult["getRechargeRanklist"]);
	}
	int SetRechargeUser()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned uid = 0, cashDay = 0, cashAll = 0;
		Json::GetUInt(jsonData, "uid", uid);
		Json::GetUInt(jsonData, "cashDay", cashDay);
		Json::GetUInt(jsonData, "cashAll", cashAll);
		string name;
		Json::GetString(jsonData, "name", name);

		CLogicRechargeRank logicRechargeRank;
		CGI_SEND_LOG("action=setRechargeUser&uid=%u", uid);
		return logicRechargeRank.ReplyUser(uid, cashDay, cashAll, name, m_jsonResult["setRechargeUser"]);
	}

	int GetPointsRanklist()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicPointsRank logicPointsRank;
		return logicPointsRank.ReplyList(uid, m_jsonResult["getPointsRanklist"]);
	}

	int SetPointsUser()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}

		unsigned uid = 0, pointsDay = 0, pointsAll = 0;
		Json::GetUInt(jsonData, "uid", uid);
		Json::GetUInt(jsonData, "pointsDay", pointsDay);
		Json::GetUInt(jsonData, "pointsAll", pointsAll);
		string name;
		Json::GetString(jsonData, "name", name);

		CLogicPointsRank logicPointsRank;
		CGI_SEND_LOG("action=setPointsUser&uid=%u", uid);
		return logicPointsRank.ReplyUser(uid, pointsDay, pointsAll, name, m_jsonResult["setPointsUser"]);
	}

	int RotaryTableDraw()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}
		unsigned uid = 0,version = 0,itemud = 0;
		Json::GetUInt(jsonData, "uid", uid);
		Json::GetUInt(jsonData,"version",version);
		Json::GetUInt(jsonData,"costItemUd",itemud);

		CDataRotaryTableDraw draw;
		draw.Draw(uid,itemud,version,m_jsonResult["list"]);
		return 0;
	}
	int GetRotaryTableRewardInfo()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;

		if(!reader.parse(data,jsonData))
		{
			error_log("error para: %s",data.c_str());
			return -1;
		}
		unsigned version = 0;
		Json::GetUInt(jsonData,"version",version);

		CDataRotaryTableDraw draw;
		draw.GetDrawInfo(version,m_jsonResult["list"]);
		return 0;
	}

	int Double11()
	{
		unsigned type = CCGIIn::GetCGIInt("type");
		unsigned id = CCGIIn::GetCGIInt("id");
		XMLDouble11Prop prop;
		bool nocnt;
		Json::Value rcnt(Json::arrayValue);
		int ret = CLogicDouble11().BuyOneProp(type, id, prop, nocnt, rcnt, true);
		if (ret != 0)
			return ret;

		m_jsonResult["nocnt"] = nocnt;
		m_jsonResult["rcnt"] = rcnt;
		m_jsonResult["prop"]["eqid"] = prop.eqid;
		m_jsonResult["prop"]["price"] = prop.price;
		m_jsonResult["prop"]["eqcnt"] = prop.eqcnt;
		m_jsonResult["prop"]["total"] = prop.total;

		CGI_SEND_LOG("action=Double11");
		return R_SUCCESS;
	}

	int GetDouble11Rcnt()
	{
		Json::Value rcnt(Json::arrayValue);
		int ret = CLogicDouble11().GetRemainCount(rcnt, true);
		if (ret != 0)
			return ret;
		m_jsonResult["rcnt"] = rcnt;
		CGI_SEND_LOG("action=GetDouble11Rcnt");
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiAllServerMatch)

