/*
 * CgiAllServerRank.cpp
 *
 *  Created on: 2014-7-10
 *      Author: Ralf
 *      这个CGI只能运行一个进程实例，为解决大量数据排行处理
 */


#include "LogicInc.h"

class CCgiAllServerRank : public CCgiBase
{

public:

	CCgiAllServerRank() : CCgiBase("allserverrank")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("fight", Fight)
	CGI_SET_ACTION_MAP("start", Start)
	CGI_SET_ACTION_MAP("over", Over)
	CGI_SET_ACTION_MAP("rank", Rank)
	CGI_ACTION_MAP_END

	int Fight()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		AllServerRankUser user;
		unsigned count, day, dayts, nextuid;

		int ret = 0;
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank();
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}

		ret = data->GetUser(uid, user, count, day, dayts, nextuid);
		if (ret != 0)
			return ret;

		m_jsonResult["count"] = count;
		m_jsonResult["day"] = day;
		m_jsonResult["dayts"] = dayts;
		m_jsonResult["nextuid"] = nextuid;
		m_jsonResult["lvl"] = user.lvl;
		m_jsonResult["tfight"] = user.tfight;
		m_jsonResult["tcwin"] = user.tcwin;
		m_jsonResult["tbeat"] = user.tbeat;
		m_jsonResult["swin"] = user.swin;
		m_jsonResult["slose"] = user.slose;
		m_jsonResult["sbeat"] = user.sbeat;
		m_jsonResult["sdefend"] = user.sdefend;
		m_jsonResult["shigh"] = user.shigh;
		m_jsonResult["slow"] = user.slow;
		m_jsonResult["flag"] = user.flag;
		m_jsonResult["tscore"] = user.tscore;
		m_jsonResult["score"] = user.score;
		m_jsonResult["name"] = user.name;
		m_jsonResult["history"].resize(ALL_SERVER_RANK_HISTORY);
		for(unsigned i=0;i<ALL_SERVER_RANK_HISTORY;++i)
		{
			m_jsonResult["history"][i]["uid"] = user.history[i].uid;
			m_jsonResult["history"][i]["ts"] = user.history[i].ts;
			m_jsonResult["history"][i]["result"] = user.history[i].result;
			m_jsonResult["history"][i]["name"] = user.history[i].name;
		}

		CGI_SEND_LOG("action=fight&uid=%u", uid);
		return R_SUCCESS;
	}

	int Start()
	{
		unsigned attacker = CCGIIn::GetCGIInt("attacker");
		unsigned defender = CCGIIn::GetCGIInt("defender");
		if (!IsValidUid(attacker) || !IsValidUid(defender))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		int ret = 0;
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank();
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}
		ret = data->StartFight(attacker, defender);
		if (ret != 0)
			return ret;
		CGI_SEND_LOG("action=start&attacker=%u&defender=%u", attacker, defender);
		return R_SUCCESS;
	}

	int Over()
	{
		unsigned attacker = CCGIIn::GetCGIInt("attacker");
		unsigned defender = CCGIIn::GetCGIInt("defender");
		unsigned win = CCGIIn::GetCGIInt("win");
		unsigned lvl = CCGIIn::GetCGIInt("lvl");
		string attackername = CCGIIn::GetCGIStr("attackername");
		string defendername = CCGIIn::GetCGIStr("defendername");
		if (!IsValidUid(attacker) || !IsValidUid(defender))
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		int ret = 0;
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank();
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}
		int score;
		ret = data->SetResult(attacker, defender, win>0, lvl, attackername, defendername, score);
		if (ret != 0)
			return ret;

		m_jsonResult["score"] = score;

		CGI_SEND_LOG("action=over&attacker=%u&defender=%u&win=%u", attacker, defender, win);
		return R_SUCCESS;
	}

	int Rank()
	{
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank();
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}

		const AllServerRankUIDMap &uidmap = data->GetAllServerRankUIDMap();
		const AllServerRankScoreMap &scoremap = data->GetAllServerRankScoreMap();

		unsigned i=0;
		m_jsonResult["rank"].resize(0);
		for(AllServerRankScoreMap::const_reverse_iterator rit=scoremap.rbegin();rit!=scoremap.rend();++rit)
		{
			++i;
			if(i > 300)
				break;

			Json::Value temp;
			if(uidmap.count(rit->second))
			{
				temp["uid"] = rit->second;
				temp["swin"] = uidmap.find(rit->second)->second.swin;
				temp["slose"] = uidmap.find(rit->second)->second.slose;
				temp["score"] = uidmap.find(rit->second)->second.score;
				temp["name"] = uidmap.find(rit->second)->second.name;
			}

			m_jsonResult["rank"].append(temp);
		}

		CGI_SEND_LOG("action=rank");
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiAllServerRank)

