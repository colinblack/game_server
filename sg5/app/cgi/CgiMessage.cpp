#include "LogicInc.h"
#include "LogicQQPay.h"

class CCgiMessage : public CCgiBase
{

public:

	CCgiMessage() : CCgiBase("message")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		//SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("send", SendMessage)
	CGI_SET_ACTION_MAP("get", GetMessage)
	CGI_SET_ACTION_MAP("remove", RemoveMessage)
	CGI_SET_ACTION_MAP("sendhelpreward", SendHelpReward)
	CGI_SET_ACTION_MAP("worldboss", GetWorldBoss)
	CGI_SET_ACTION_MAP("nianshou", GetNianShou)
	CGI_SET_ACTION_MAP("allianceboss", GetAllianceBoss)
	CGI_SET_ACTION_MAP("lastallianceboss", GetLastAllianceBoss)
	CGI_SET_ACTION_MAP("viewladder", ViewLadder)
	CGI_SET_ACTION_MAP("viewallserverladder", ViewAllServerLadder)
	CGI_SET_ACTION_MAP("refreshladder", RefreshLadder)
	CGI_SET_ACTION_MAP("refreshallserverladder", RefreshAllServerLadder)
	CGI_SET_ACTION_MAP("reportladder", ReportLadder)
	CGI_SET_ACTION_MAP("reportallserverladder", ReportAllServerLadder)
	CGI_SET_ACTION_MAP("gethelphist", GetHelpHist)
	CGI_SET_ACTION_MAP("dragonball", GetDragonball)
	//CGI_SET_ACTION_MAP("setmarketquest", SetMarketTask)
	//CGI_SET_ACTION_MAP("getmarketquest", GetMarketTask)
	CGI_SET_ACTION_MAP("setmarketquest", AddMarketTask)
	CGI_SET_ACTION_MAP("viewallserverladdertop1", ViewAllServerLadderTop1)
	CGI_SET_ACTION_MAP("ViewAllServerRank", ViewAllServerRank)
	CGI_SET_ACTION_MAP("GetAllServerRank", GetAllServerRank)
	CGI_SET_ACTION_MAP("getAllServerNewWorldBattlelist", GetAllServerNewWorldBattlelist)
	CGI_SET_ACTION_MAP("setAllServerNewWorldBattleAttack", SetAllServerNewWorldBattleAttack)
	CGI_SET_ACTION_MAP("GetAllServerMVP", GetAllServerMVP)
	CGI_SET_ACTION_MAP("StartAllServerMVP", StartAllServerMVP)
	CGI_SET_ACTION_MAP("EndAllServerMVP", EndAllServerMVP)
	CGI_SET_ACTION_MAP("SetAllServerMVP", SetAllServerMVP)
	CGI_SET_ACTION_MAP("StartAllServerBattleMVP", StartAllServerBattleMVP)
	CGI_SET_ACTION_MAP("EndAllServerBattleMVP", EndAllServerBattleMVP)
	CGI_SET_ACTION_MAP("gameapi_real_name_query", gameapi_real_name_query)
	CGI_SET_ACTION_MAP("idcard_time", idcard_time)
	CGI_SET_ACTION_MAP("NewWorldFight", NewWorldFight)
	CGI_SET_ACTION_MAP("EndAllServerNewWorldFightMVP", EndAllServerNewWorldFightMVP)
	CGI_SET_ACTION_MAP("GetChickReg", GetChickReg)
	CGI_SET_ACTION_MAP("ChickReg", ChickReg)
	CGI_ACTION_MAP_END

	int SendMessage()
	{
		unsigned toUid = 0;
		if(!Json::IsArray(m_data, "targetid"))
		{
			if (!Json::GetUInt(m_data, "targetid", toUid))
				toUid = 0;
		}
		string type;
		if (!Json::GetString(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}
		CLogicMessage logicMsg;
		int ret = 0;
		if (type == "message")
		{
			string message;
			if (toUid == 0 || !Json::GetString(m_data, "message", message))
				return R_ERR_PARAM;
			StringFilter::Replace(message);
			ret = logicMsg.Chat(m_uid, toUid, message);
			if (ret != 0)
				return ret;
		}
		else if (type == "request")
		{
			string way;
			if (!Json::GetString(m_data, "way", way))
				return R_ERR_PARAM;
			if (way == "add")
			{
				if (toUid == 0 || !Json::IsObject(m_data, "message"))
					return R_ERR_PARAM;
				ret = logicMsg.AddRequest(m_uid, toUid, m_data["message"]);
				if (ret != 0)
					return ret;
			}
			else if (way == "accept")
			{
				uint64_t msgid = 0;
				if (!Json::IsArray(m_data, "msgid"))
				{
					if (toUid == 0 || !Json::GetUInt64(m_data, "msgid", msgid))
						return R_ERR_PARAM;
					ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_ACCEPT, m_data["message"]);
					if (ret != 0)
						return ret;
				}
				else
				{
					if (!Json::IsArray(m_data, "targetid"))
					{
						return R_ERR_PARAM;
					}

					Json::Value messageId;
					Json::Value targetID;
					if (!Json::GetArray(m_data, "targetid", targetID)
						|| !Json::GetArray(m_data, "msgid", messageId))
					{
						return R_ERR_PARAM;
					}
					if (targetID.size() != messageId.size())
					{
						return R_ERR_PARAM;
					}
					for (unsigned int i=0; i<messageId.size(); i++)
					{
						if (!Json::GetUInt64(messageId, i, msgid))
						{
							continue;
						}
						if (!Json::GetUInt(targetID, i, toUid))
						{
							continue;
						}
						ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_ACCEPT, m_data["message"]);
						if (ret != 0)
							return ret;
						}
				}
			}
			else if (way == "reject")
			{
				uint64_t msgid = 0;
				if (!Json::IsArray(m_data, "msgid"))
				{
					if (toUid == 0 || !Json::GetUInt64(m_data, "msgid", msgid))
						return R_ERR_PARAM;
					ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_REJECT, m_data["message"]);
					if (ret != 0)
						return ret;
				}
				else
				{
					if (!Json::IsArray(m_data, "targetid"))
					{
						return R_ERR_PARAM;
					}

					Json::Value messageId;
					Json::Value targetID;
					if (!Json::GetArray(m_data, "targetid", targetID)
						|| !Json::GetArray(m_data, "msgid", messageId))
					{
						return R_ERR_PARAM;
					}
					if (targetID.size() != messageId.size())
					{
						return R_ERR_PARAM;
					}
					for (unsigned int i=0; i<messageId.size(); i++)
					{
						if (!Json::GetUInt64(messageId, i, msgid))
						{
							continue;
						}
						if (!Json::GetUInt(targetID, i, toUid))
						{
							continue;
						}
						ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_REJECT, m_data["message"]);
						if (ret != 0)
							return ret;
					}
				}
			}
			else if (way == "cancel")
			{
				uint64_t msgid = 0;
				if (!Json::GetUInt64(m_data, "msgid", msgid))
					msgid = 0;
				string mtype;
				if (!Json::GetString(m_data, "mtype", mtype))
					mtype = "alliance_join";
				ret = logicMsg.CancelRequest(m_uid, mtype, msgid);
				if (ret != 0)
					return ret;
			}
			else
			{
				return R_ERR_PARAM;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}

		CGI_SEND_LOG("action=send&uid=%u&toUid=%u&type=%s", m_uid, toUid, type.c_str());
		return R_SUCCESS;
	}

	int GetMessage()
	{
		string type;
		if (!Json::GetString(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}
		unsigned quid = 0;
		if (!Json::GetUInt(m_data, "quid", quid) || quid == 0)
		{
			quid = m_uid;
		}

//		if (!Json::GetUInt(m_data, "quid", quid) || quid == 0)
//		{
//			quid = m_uid;
//		}

		Json::Reader reader;
		CLogicMessage logicMsg;
		vector<DataMessage> msgVec;
		int ret = 0;
		if (type == "message")
		{
			int toward = TOWARD_RECV;
			if (!Json::GetInt(m_data, "toward", toward))
				toward = TOWARD_RECV;
			ret = logicMsg.GetChat(quid, toward, msgVec);
			if (ret != 0)
				return ret;
			Json::Value json;
			json.resize(msgVec.size());
			for (unsigned i = 0; i < msgVec.size(); i++)
			{
				json[i]["msgid"] = Convert::UInt64ToString(msgVec[i].message_id);
				json[i]["from"] = msgVec[i].from_uid;
				json[i]["to"] = msgVec[i].to_uid;
				json[i]["from_pt"] = msgVec[i].from_platform;
				json[i]["from_name"] = msgVec[i].from_user_name;
				json[i]["to_pt"] = msgVec[i].to_platform;
				json[i]["to_name"] = msgVec[i].to_user_name;
				json[i]["time"] = msgVec[i].time;
				json[i]["msg"] = msgVec[i].content;
			}
			m_jsonResult["res"] = json;
		}
		else if (type == "request")
		{
			string mtype;
			int toward;
			int status;
			Json::GetString(m_data, "mtype", mtype);
			if(!Json::GetInt(m_data, "toward", toward) ||
					!Json::GetInt(m_data, "status", status))
			{
				PARAM_ERROR_RETURN();
			}
			if (toward < 0 || toward > TOWARD_TYPE_ALL
					|| status < MS_UN_PROCESS || status > MS_STATUS_ALL)
			{
				PARAM_ERROR_RETURN();
			}

			vector<string> vecMtypes;
			if(!mtype.empty())
			{
				CBasic::StringSplitTrim(mtype, "|", vecMtypes);
			}
			set<string> mtypes(vecMtypes.begin(), vecMtypes.end());

			ret = logicMsg.GetRequestJson(quid, mtypes, toward, status, m_jsonResult["res"]);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}

		CGI_SEND_LOG("action=get&uid=%u&quid=%u&type=%s", m_uid, quid, type.c_str());
		return R_SUCCESS;
	}

	int RemoveMessage()
	{
		int ret;
		string type;
		uint64_t messageId;
		if (!Json::GetString(m_data, "type", type) ||
			!Json::GetUInt64(m_data, "messageid", messageId))
		{
			return R_ERR_PARAM;
		}
		CLogicMessage logicMessage;
		if(type == "message")
		{
			ret = logicMessage.RemoveChat(m_uid, messageId);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}
		CGI_SEND_LOG("action=remove&uid=%u&messageid=%llu&type=%s", m_uid, messageId, type.c_str());
		return R_SUCCESS;
	}

	int SendHelpReward()
	{
		int ret;
		string itemid;
		int count;
		if(!Json::GetString(m_data, "itemid", itemid) ||
			!Json::GetInt(m_data, "count", count))
		{
			PARAM_ERROR_RETURN();
		}
		CLogicUserInteract logicInteract;
		uint64_t messageId;
		ret = logicInteract.SendHelpReward(m_uid, itemid, count, messageId);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["messageid"] = Convert::UInt64ToString(messageId);
		CGI_SEND_LOG("action=sendhelpreward&uid=%u&itemid=%s&count=%d&messageid=%llu",
				m_uid, itemid.c_str(), count, messageId);
		return R_SUCCESS;
	}

	int GetWorldBoss()
	{
		CLogicWorldBoss logicWorldBoss;
		int ret = logicWorldBoss.GetWorldBossInfo(m_uid, m_jsonResult["worldboss"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=worldboss&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetNianShou()
	{
		unsigned id;
		Json::GetUInt(m_data, "id", id);
		unsigned bossid;
		Json::GetUInt(m_data, "bossid", bossid);
		CLogicNianShou logicNianShou;
		int ret = logicNianShou.GetNianShouInfo(m_uid, m_jsonResult["nianshou"], bossid, id);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=nianshou&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetAllianceBoss()
	{
		CLogicAllianceBoss logicAllianceBoss;
		int ret = logicAllianceBoss.GetAllianceBossInfo(m_uid, m_jsonResult["allianceboss"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=allianceboss&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int GetLastAllianceBoss()        //上次屠魔排名以及最后一击
	{
		CLogicAllianceBoss logicAllianceBoss;
		int ret = logicAllianceBoss.GetLastAllianceBossInfo(m_uid, m_jsonResult["lastallianceboss"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=lastallianceboss&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ViewLadder()
	{
		CLogicLadder logicLadder;
		int ret = logicLadder.ViewLadder(m_uid, m_jsonResult);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=viewladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ViewAllServerLadder()
	{
		string uid;
		String::Format(uid, "%u", m_uid);
		string url = "action=viewladder";
		url.append("&uid=").append(uid);

		string level;
		if (!Json::GetString(m_data, "level", level))
		{
			PARAM_ERROR_RETURN_MSG("level");
		}
		url.append("&level=").append(level);

		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=viewallserverladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int RefreshLadder()
	{
		CLogicLadder logicLadder;
		int ret = logicLadder.Refresh(m_uid, m_jsonResult);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=refreshladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int RefreshAllServerLadder()
	{
		string uid;
		String::Format(uid, "%u", m_uid);
		string url = "action=refreshladder";
		url.append("&uid=").append(uid);

		string level;
		if (!Json::GetString(m_data, "level", level))
		{
			PARAM_ERROR_RETURN_MSG("level");
		}
		url.append("&level=").append(level);

		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=refreshallserverladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetDragonball()
	{
		CLogicDragonball logicBall;
		int ret = logicBall.GetDragonballs(m_jsonResult["dragonballs"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=dragonball&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ReportLadder()
	{
		CLogicLadder logicLadder;
		int ret = logicLadder.ReportResult(m_uid, m_data["data"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=reportladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int ReportAllServerLadder()
	{
		string uid;
		String::Format(uid, "%u", m_uid);
		string url = "action=reportladder";
		url.append("&uid=").append(uid);

		if (!m_data.isMember("data"))
		{
			PARAM_ERROR_RETURN_MSG("data");
		}
		string data = Json::ToString(m_data["data"]);
		url.append("&data=").append(Crypt::UrlEncode(data));

		string level;
		if (!Json::GetString(m_data, "level", level))
		{
			PARAM_ERROR_RETURN_MSG("level");
		}
		url.append("&level=").append(level);

		CLogicAllServerBaseMatch logicBaseMatch;
		Json::Value result;
		int ret = logicBaseMatch.RequestBaseMatch(url,result);
		if (0 != ret)
		{
			//error_log("[RequestBaseMatch fail][url=%s]",url.c_str());
			return ret;
		}

		CGI_SEND_LOG("action=reportallserverladder&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetHelpHist()
	{
		CLogicHelpHist logiclasthelp;
		int ret = logiclasthelp.GetHelpHist(m_uid, m_jsonResult["helplist"]);
		if (0 != ret)
		{
			return ret;
		}
		return R_SUCCESS;
	}
/*
	int SetMarketTask()
	{
		int ret = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN();
		}
		if (!Json::IsArray(m_data, "quest"))
		{
			PARAM_ERROR_RETURN();
		}
		Json::Value quest;
		if (!Json::GetArray(m_data, "quest", quest))
		{
			PARAM_ERROR_RETURN();
		}

		CLogicMarketTask logicMarketTask;
		int flag = 0;
		string contractid;
		string sttaskid;
		for (int i=0; i<quest.size(); ++i)
		{
			if (!Json::GetString(quest[i], "marketquestid", contractid))
			{
				error_log("get marketquestid fail,i=%d", i);
				continue;
			}
			if (!Json::GetString(quest[i], "param", sttaskid))
			{
				error_log("get taskid fail,i=%d", i);
				continue;
			}
			if (!Json::GetInt(quest[i], "finish", flag))
			{
				error_log("get finish fail,i=%d", i);
				continue;
			}
			ret = logicMarketTask.SetMarketTask(openid, contractid, sttaskid, flag);
			if (0 != ret)
			{
				error_log("SetMarketTask fail,ret=%d", ret);
				continue;
			}
			if (1 == flag)
			{
				CLogicQQPay logicQQPay;
				string pf = "qzone";
				string pfkey;
				if(!Json::GetString(m_data, "pfkey", pfkey))
				{
					PARAM_ERROR_RETURN();
				}
				string openkey;
				if(!Json::GetString(m_data, "openkey", openkey))
				{
					PARAM_ERROR_RETURN();
				}
				string zoneid;
				string appid;
				if(!Json::GetString(m_data, "appid", appid))
				{
					PARAM_ERROR_RETURN();
				}

				ret = logicQQPay.InformTaskCompleted(pf, pfkey, openid, openkey, zoneid, appid, contractid);
				if(0 != ret)
				{
					return ret;
				}
			}
		}
		return 0;
	}

	int GetMarketTask()
	{
		int ret = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN();
		}

		CLogicMarketTask logicMarketTask;
		vector<DataMarketTask> data;
		ret = logicMarketTask.GetMarketTask(openid, data);
		if (0 != ret)
		{
			return ret;
		}
		Json::Value questRet = Json::Value(Json::arrayValue);
		vector<DataMarketTask>::iterator itr = data.begin();

		for (; itr!=data.end(); ++itr)
		{
			Json::Value &temp = questRet[questRet.size()];
			temp["marketquestid"] = itr->contractid;
			temp["finish"] = itr->flag;
			temp["param"] = itr->taskid;
		}
		m_jsonResult["quest"] = questRet;
		return 0;
	}
*/
	int AddMarketTask()
	{
		int ret = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN();
		}
		if (!Json::IsArray(m_data, "quest"))
		{
			PARAM_ERROR_RETURN();
		}
		Json::Value quest;
		if (!Json::GetArray(m_data, "quest", quest))
		{
			PARAM_ERROR_RETURN();
		}

		CLogicMarketTask logicMarketTask;
		int flag = 0;
		string contractid;
		string sttaskid;
		for (int i=0; i<quest.size(); ++i)
		{
			if (!Json::GetString(quest[i], "marketquestid", contractid))
			{
				error_log("get marketquestid fail,i=%d", i);
				continue;
			}
			if (!Json::GetString(quest[i], "param", sttaskid))
			{
				error_log("get taskid fail,i=%d", i);
				continue;
			}
			ret = logicMarketTask.AddMarketTask(openid, contractid, sttaskid, 0);
			if (0 != ret)
			{
				error_log("AddMarketTask fail,ret=%d", ret);
				continue;
			}
		}

		return 0;
	}

	int ViewAllServerLadderTop1()
	{
		string url = "action=viewtop1";
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url, m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}
		return 0;
	}

	int ViewAllServerRank()
	{
		string uid;
		String::Format(uid, "%u", m_uid);
		string url = "action=fight";
		url.append("&uid=").append(uid);

		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,m_jsonResult["ViewAllServerRank"],CONFIG_ALLS_RANK_PATH, true);
		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=ViewAllServerRank&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetAllServerRank()
	{
		string url = "action=rank";

		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,m_jsonResult["GetAllServerRank"],CONFIG_ALLS_RANK_PATH, true);
		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetAllServerRank&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetAllServerNewWorldBattlelist()
	{
		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		int ret = logicAllServerNewWorldBattle.GetList(m_jsonResult["getAllServerNewWorldBattlelist"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=getAllServerNewWorldBattlelist&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int SetAllServerNewWorldBattleAttack()
	{
		unsigned attack = 0, kingdom = 0, defend = 0;
		Json::GetUInt(m_data, "attack", attack);
		Json::GetUInt(m_data, "kingdom", kingdom);
		Json::GetUInt(m_data, "defend", defend);

		if(!attack || !defend || !kingdom || kingdom > 3)
			return R_ERR_PARAM;

		CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
		int ret = logicAllServerNewWorldBattle.SetAttack(m_uid, attack, kingdom, defend, m_jsonResult["setAllServerNewWorldBattleAttack"]);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=setAllServerNewWorldBattleAttack&uid=%u&attack=%u&kingdom=%u&defend=%u",m_uid,attack,kingdom,defend);
		return R_SUCCESS;
	}

	int GetAllServerMVP()
	{
		string url = "action=GetAllServerMVP";
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		m_jsonResult["mvp"] = t["mvp"];
		m_jsonResult["fightmvp"] = t["fightmvp"];
		m_jsonResult["battlemvp"] = t["battlemvp"];
		m_jsonResult["allmvp"] = t["allmvp"];

		CGI_SEND_LOG("action=GetAllServerMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int StartAllServerMVP()
	{
		unsigned rank = 0;
		Json::GetUInt(m_data, "rank", rank);

		string url = "action=StartAllServerMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank);
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		bool cash = true;
		do
		{
			CLogicUser logicUser;
			DataUser dataUser;
			AUTO_LOCK_USER(m_uid)
			ret = logicUser.GetUser(m_uid, dataUser);
			if(ret)
			{
				cash = false;
				break;
			}
			Json::Value user_flag;
			bool bsave = false;
			Json::Reader().parse(dataUser.user_flag, user_flag);
			DataPay payData;
			ret = CLogicPay().ProcessOrderForBackend(m_uid, -20, 0, payData, "StartAllServerMVP", user_flag, bsave);
			if(ret)
			{
				cash = false;
				break;
			}
			if(bsave)
			{
				dataUser.user_flag = Json::FastWriter().write(user_flag);
				ret = logicUser.SetUser(m_uid, dataUser);
				if(ret)
				{
					cash = false;
					break;
				}
			}
		}while(0);
		if(!cash)
		{
			string url = "action=EndAllServerMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank)
					   + "&win=0&data={}";
			Json::Value t;
			CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
			return R_ERR_LOGIC;
		}

		CGI_SEND_LOG("action=StartAllServerMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int EndAllServerMVP()
	{
		unsigned rank = 0, win = 0;
		Json::GetUInt(m_data, "rank", rank);
		Json::GetUInt(m_data, "win", win);
		string data;
		if(win)
		{
			string name, sign, fig;
			CLogicUserBasic().GetWorldUserInfo(m_uid, PT_TEST, sign, fig, name);
			Json::Value t;
			t["sign"] = sign;
			t["fig"] = fig;
			t["name"] = name;
			t["mcity"] = m_data["mcity"];
			t["hero"] = m_data["hero"];
			data = Json::FastWriter().write(t);
		}
		else
			data = "{}";

		string url = "action=EndAllServerMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank)
				   + "&win=" + CTrans::UTOS(win) + "&data=" + data;
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=EndAllServerMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int SetAllServerMVP()
	{
		string sign;
		Json::GetString(m_data, "sign", sign);
		if(!StringFilter::Check(sign))
		{
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "forbidden_sign");
		}

		string url = "action=SetAllServerMVP&uid=" + CTrans::UTOS(m_uid) + "&sign=" + sign;
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		CLogicUserBasic().SetWorldUserInfo(m_uid, PT_TEST, sign);

		CGI_SEND_LOG("action=SetAllServerMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int StartAllServerBattleMVP()
	{
		unsigned rank = 0;
		Json::GetUInt(m_data, "rank", rank);

		string url = "action=StartAllServerBattleMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank);
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		bool cash = true;
		do
		{
			CLogicUser logicUser;
			DataUser dataUser;
			AUTO_LOCK_USER(m_uid)
			ret = logicUser.GetUser(m_uid, dataUser);
			if(ret)
			{
				cash = false;
				break;
			}
			Json::Value user_flag;
			bool bsave = false;
			Json::Reader().parse(dataUser.user_flag, user_flag);
			DataPay payData;
			ret = CLogicPay().ProcessOrderForBackend(m_uid, -20, 0, payData, "StartAllServerBattleMVP", user_flag, bsave);
			if(ret)
			{
				cash = false;
				break;
			}
			if(bsave)
			{
				dataUser.user_flag = Json::FastWriter().write(user_flag);
				ret = logicUser.SetUser(m_uid, dataUser);
				if(ret)
				{
					cash = false;
					break;
				}
			}
		}while(0);
		if(!cash)
		{
			string url = "action=EndAllServerBattleMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank)
					   + "&win=0&data={}";
			Json::Value t;
			CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
			return R_ERR_LOGIC;
		}

		CGI_SEND_LOG("action=StartAllServerBattleMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int EndAllServerBattleMVP()
	{
		unsigned rank = 0, win = 0;
		Json::GetUInt(m_data, "rank", rank);
		Json::GetUInt(m_data, "win", win);
		string data;
		if(win)
		{
			string name, sign, fig;
			CLogicUserBasic().GetWorldUserInfo(m_uid, PT_TEST, sign, fig, name);
			Json::Value t;
			t["sign"] = sign;
			t["fig"] = fig;
			t["name"] = name;
			t["hero"] = m_data["hero"];
			data = Json::FastWriter().write(t);
		}
		else
			data = "{}";

		string url = "action=EndAllServerBattleMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank)
				   + "&win=" + CTrans::UTOS(win) + "&data=" + data;
		Json::Value t;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, t, CONFIG_MVP_PATH, true);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=EndAllServerBattleMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int gameapi_real_name_query()
	{
		string openid, openkey;
		Json::GetString(m_data, "openid", openid);
		Json::GetString(m_data, "openkey", openkey);
		string appid = OpenPlatform::GetPlatform()->GetAppId();
		string appkey = OpenPlatform::GetPlatform()->GetAppKey();

		string url = "http://openapi.minigame.qq.com/v3/user/gameapi_real_name_query?";
		string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/user/gameapi_real_name_query") + "&";
		string qsig = "appid=" + appid + "&openid=" + openid + "&openkey=" + openkey;
		string qstr = "appid=" + Crypt::UrlEncodeForTX(appid) + "&openid="
				+ Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);
		osig += Crypt::UrlEncodeForTX(qsig);
		string key = appkey + "&";
		string bsig = Crypt::HmacSha1(osig, key);
		string sig;
		Crypt::Base64Encode(sig, bsig);
		url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);


		string response;
		if (!Network::HttpGetRequest(response, url) || response.empty())
		{
			error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s]",
					openid.c_str(), openkey.c_str(), response.c_str());
			error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
			return -1;
		}
		Json::Value value;
		if(!Json::Reader().parse(response, value))
		{
			error_log("[json parse fail][openid=%s,openkey=%s,response=%s]",
					openid.c_str(), openkey.c_str(), response.c_str());
			error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
			return -1;
		}
		int ret;
		if (!Json::GetInt(value, "ret", ret) || ret != 0)
		{
			error_log("[get_info fail][openid=%s,openkey=%s,msg=%s]",
					openid.c_str(), openkey.c_str(), response.c_str());
			error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
			return -1;
		}

		m_jsonResult["response"] = value;

		CGI_SEND_LOG("action=gameapi_real_name_query&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int idcard_time()
	{
		string idcard, openid;
		Json::GetString(m_data, "idcard", idcard);
		Json::GetString(m_data, "openid", openid);

		if(idcard.empty() || openid.empty())
			return R_ERR_PARAM;

		set<string> open_id;
		CDataIdcard dbid;
		dbid.GetAllIdcard(idcard, open_id);
		if(!open_id.count(openid))
		{
			dbid.AddIdcard(idcard, openid);
			open_id.insert(openid);
		}

		unsigned ext = 0;
		CDataUserMapping dbUserMapping;
		CDataUser dbUser;
		for(set<string>::iterator it=open_id.begin();it!=open_id.end();++it)
		{
			vector<unsigned> uids;
			dbUserMapping.GetAllMapping(*it,uids);
			for(vector<unsigned>::iterator iter=uids.begin();iter!=uids.end();++iter)
			{
				unsigned e = 0, l = 0;
				dbUser.GetExt(*iter, l, e);
				if(!CTime::IsDiffDay(l, Time::GetGlobalTime()))
					ext += e;
			}
		}

		m_jsonResult["ext"] = ext;

		CGI_SEND_LOG("action=idcard_time&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int NewWorldFight()
	{
		if(!m_data.isMember("fighter") || !m_data["fighter"].isArray() || m_data["fighter"].size() != 2)
			return R_ERR_PARAM;
		NewWorldHero fighter[2][NEW_WORLD_HERO_INDEX];
		for(unsigned i=0;i<2;i++)
		{
			if(!m_data["fighter"][i].isArray() || m_data["fighter"][i].size() == 0 || m_data["fighter"][i].size() > NEW_WORLD_HERO_INDEX)
				return R_ERR_PARAM;
			unsigned uid = ADMIN_UID + i + 1;
			for(unsigned j=0;j<m_data["fighter"][i].size();++j)
			{
				Json::Value& para = m_data["fighter"][i][j];
				unsigned level = 1;
				Json::GetUInt(para, "level", level);
				unsigned job = 1;
				Json::GetUInt(para, "job", job);
				unsigned type = 0;
				Json::GetUInt(para, "type", type);
				fighter[i][j].index.uid		= uid;
				fighter[i][j].index.index	= j;
				fighter[i][j].level			= level;
				fighter[i][j].job			= (job - 1)%NewWorldHeroJob_max;
				fighter[i][j].type			= (type - 1)%NewWorldHeroJob_max;
				if(para.isMember("property") && para["property"].isArray() && para["property"].size()<=NewWorldProperty_max)
				{
					for(unsigned k=0;k<para["property"].size();++k)
						fighter[i][j].property[k] = para["property"][k].asUInt();
				}
				fighter[i][j].hp = fighter[i][j].property[NewWorldProperty_hp];
			}
		}

		Json::Value& res = m_jsonResult["res"];
		res.resize(0);
		unsigned i = 0, j = 0;
		int a, b;
		while(i < NEW_WORLD_HERO_INDEX && j < NEW_WORLD_HERO_INDEX && fighter[0][i].index.uid && fighter[1][j].index.uid)
		{
			CDataNewWorld::attacking(fighter[0][i], fighter[1][j], a, b);
			Json::Value t;
			t.resize(0);
			t.append(fighter[0][i].hp);
			t.append(fighter[1][j].hp);
			res.append(t);
			if(fighter[0][i].hp <= 0)
				i++;
			if(fighter[1][j].hp <= 0)
				j++;
		}

		CGI_SEND_LOG("action=NewWorldFight&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int EndAllServerNewWorldFightMVP()
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(m_uid)
		int ret = logicUser.GetUser(m_uid, dataUser);
		if(ret)
			return ret;
		Json::Value user_flag;
		bool bsave = false;
		Json::Reader().parse(dataUser.user_flag, user_flag);
		DataPay payData;
		ret = CLogicPay().ProcessOrderForBackend(m_uid, -20, 0, payData, "EndAllServerNewWorldFightMVP", user_flag, bsave);
		if(ret)
			return ret;
		if(bsave)
		{
			dataUser.user_flag = Json::FastWriter().write(user_flag);
			ret = logicUser.SetUser(m_uid, dataUser);
			if(ret)
				return ret;
		}

		unsigned rank = 0, win = 0;
		Json::GetUInt(m_data, "win", win);
		string data;
		if(win)
		{
			Json::GetUInt(m_data, "rank", rank);
			string name, sign, fig;
			CLogicUserBasic().GetWorldUserInfo(m_uid, PT_TEST, sign, fig, name);
			Json::Value t;
			t["sign"] = sign;
			t["fig"] = fig;
			t["name"] = name;
			t["hero"] = m_data["hero"];
			data = Json::FastWriter().write(t);

			string url = "action=EndAllServerNewWorldFightMVP&uid=" + CTrans::UTOS(m_uid) + "&rank=" + CTrans::UTOS(rank)
					   + "&win=" + CTrans::UTOS(win) + "&data=" + data;
			Json::Value tt;
			ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, tt, CONFIG_MVP_PATH, true);
			if (ret)
				return ret;
		}

		CGI_SEND_LOG("action=EndAllServerNewWorldFightMVP&uid=%u",m_uid);
		return R_SUCCESS;
	}

	int GetChickReg()
	{
		string url = "action=GetChickReg&uid=" + CTrans::UTOS(m_uid);
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, m_jsonResult["GetChickReg"], CONFIG_CHICK_PATH, true);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=GetChickReg&uid=%u",m_uid);
		return R_SUCCESS;
	}
	int ChickReg()
	{
		if(!m_data.isMember("fighter") || !m_data["fighter"].isArray() || m_data["fighter"].size() != CHICK_HERO)
			return R_ERR_PARAM;

		unsigned l = 0, p[NewWorldProperty_max] = {0};
		for(unsigned i=0;i<CHICK_HERO;++i)
		{
			l += m_data["fighter"][i]["level"].asUInt();
			if(m_data["fighter"][i].isMember("property") && m_data["fighter"][i]["property"].isArray() && m_data["fighter"][i]["property"].size()<=NewWorldProperty_max)
			{
				for(unsigned k=0;k<m_data["fighter"][i]["property"].size();++k)
					p[k] += m_data["fighter"][i]["property"][k].asUInt();
			}
		}
		l = l / CHICK_HERO;
		for(int i=0;i<NewWorldProperty_max;++i)
			p[i] = p[i] / CHICK_HERO;

		string name, fig;
		unsigned level;
		Json::GetString(m_data, "name", name);
		Json::GetString(m_data, "fig", fig);
		Json::GetUInt(m_data, "level", level);

		Json::Value t;
		t["level"] = level;
		t["fig"] = fig;
		t["name"] = name;
		t["hero"]["level"] = l;
		t["hero"]["property"].resize(0);
		for(int i=0;i<NewWorldProperty_max;++i)
			t["hero"]["property"].append(p[i]);
		string data = Json::FastWriter().write(t);

		string url = "action=ChickReg&uid=" + CTrans::UTOS(m_uid) + "&data=" + data;
		int ret = CLogicAllServerBaseMatch().RequestBaseMatch(url, m_jsonResult["ChickReg"], CONFIG_CHICK_PATH, true);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=ChickReg&uid=%u",m_uid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiMessage)
