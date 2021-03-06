#include "LogicLadder.h"

CDataLadder* CLogicLadder::GetCDataLadder()
{
	GET_MEM_DATA_SEM(CDataLadder, CONFIG_LADDER_PATH, sem_ladder,false)
	/*static CDataLadder* pladder = NULL;
	if (!pladder)
	{
		pladder = new CDataLadder();
		if (pladder->Init(Config::GetValue(CONFIG_LADDER_PATH)) != 0)
		{
			delete pladder;
			pladder = NULL;
		}
	}
	return pladder;*/
}

void CLogicLadder::CheckLadderJson(Json::Value &ladder, bool *init)
{

	if (ladder.isMember("upts"))
	{
		if (init) *init = false;
		if (ladder["winMax"].asInt() < ladder["win"].asInt())
			ladder["winMax"] = ladder["win"];
		if (!IsValidLadderRank(ladder["rankMax"].asInt()) && IsValidLadderRank(ladder["rank"].asInt()))
			ladder["rankMax"] = ladder["rank"];
		if (IsValidLadderRank(ladder["rankMax"].asInt()) && IsValidLadderRank(ladder["rank"].asInt())
				&& ladder["rankMax"].asInt() > ladder["rank"].asInt())
			ladder["rankMax"] = ladder["rank"];
		unsigned upts = ladder["upts"].asUInt();
		if (CTime::GetDayInterval(upts, Time::GetGlobalTime()) != 0)
		{
			ladder["win"] = 0;
		}
	}
	else
	{
		if (init) *init = true;
		ladder["upts"] = Time::GetGlobalTime();
		ladder["rank"] = -1;
		ladder["rankMax"] = -1;
		ladder["win"] = 0;
		ladder["winMax"] = 0;
		ladder["prs"][0u] = -1;
		ladder["prs"][1u] = -1;
		ladder["prs"][2u] = -1;
		ladder["prs"][3u] = -1;
		ladder["prs"][4u] = -1;
		ladder["log"].resize(0);
	}
}

void CLogicLadder::RandLadderPlayers(Json::Value &ladder)
{
	int rank = ladder["rank"].asInt();
	int begin = 1, num = 0;
	if (rank == -1)
	{
		begin = 901;
		num = 100;
	}
	else if (rank > 1 && rank <= 1000)
	{
		begin = rank > 100 ? rank - 100 : 1;
		num = rank - begin;
	}
	for (unsigned i = 0; i < 5; i++)
	{
		ladder["prs"][i] = -1;
	}
	if (num > 0 && num <= 100)
	{
		if (num <= 5)
		{
			int i = 0;
			for (; i < num; i++)
				ladder["prs"][i] = begin + i;
		}
		else
		{
			bool mark[100];
			memset(mark, 0, sizeof(mark));
			int rest = num;
	        for (int k = 0; k < 5; k++,rest--)
	        {
				int r = Math::GetRandomInt(rest) + 1;
				int j = 0;
				while (r > 0 && j < 100)
				{
					if (mark[j++]) continue;
					r--;
				}
				mark[j - 1] = true;
	        }
	        unsigned ndx = 0;
			for (int k = 0; k < num; k++)
			{
				if (ndx >= 5) break;
				if (!mark[k]) continue;
				ladder["prs"][ndx++] = begin + k;
			}
		}
	}
}

int CLogicLadder::ViewLadder(unsigned uid, Json::Value &result)
{
	CDataLadder* pladder = GetCDataLadder();
	if (!pladder)
	{
		DB_ERROR_RETURN_MSG("init_ladder_fail");
	}
	DataUserData userData;
	CLogicUserData logicUserData;
	int ret = logicUserData.GetUserData(uid, userData);
	if (ret != 0)
		return ret;
	int rank = -1;
	ret = pladder->GetRank(uid, rank);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("get_ladder_rank_fail");
	}
	Json::Value &ladder = result["ladder"];
	Json::Reader reader;
	if (!userData.ladder.empty() && !reader.parse(userData.ladder, ladder))
	{
		DB_ERROR_RETURN_MSG("parse_ladder_fail");
	}
	bool bInit = false;
	bool needSave = false;
	CheckLadderJson(ladder, &bInit);
	if (bInit || ladder["rank"].asInt() != rank)
	{
		ladder["rank"] = rank;
		RandLadderPlayers(ladder);
		needSave = true;
		if (bInit)
		{
			ladder["rankMax"] = rank;
		}
	}
	if (needSave)
	{
		ladder["upts"] = Time::GetGlobalTime();
		ret = logicUserData.SetLadder(uid, ladder);
		if (ret != 0)
			return ret;
	}

	int rank1 = ladder["prs"][0u].asInt();
	int rank2 = ladder["prs"][1u].asInt();
	int rank3 = ladder["prs"][2u].asInt();
	int rank4 = ladder["prs"][3u].asInt();
	int rank5 = ladder["prs"][4u].asInt();
	LadderItem player1;
	LadderItem player2;
	LadderItem player3;
	LadderItem player4;
	LadderItem player5;
	LadderItem top[3];
	pladder->GetFivePlayers(rank1, rank2, rank3, rank4, rank5,
			player1, player2, player3, player4, player5,
			top);

	Json::Value &players = result["players"];
	players.resize(0);
	if (IsValidLadderRank(rank1))
	{
		Json::Value json;
		json["rank"] = rank1;
		json["uid"] = player1.uid;
		json["level"] = player1.level;
		json["name"] = player1.name;
		json["pic"] = player1.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank2))
	{
		Json::Value json;
		json["rank"] = rank2;
		json["uid"] = player2.uid;
		json["level"] = player2.level;
		json["name"] = player2.name;
		json["pic"] = player2.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank3))
	{
		Json::Value json;
		json["rank"] = rank3;
		json["uid"] = player3.uid;
		json["level"] = player3.level;
		json["name"] = player3.name;
		json["pic"] = player3.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank4))
	{
		Json::Value json;
		json["rank"] = rank4;
		json["uid"] = player4.uid;
		json["level"] = player4.level;
		json["name"] = player4.name;
		json["pic"] = player4.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank5))
	{
		Json::Value json;
		json["rank"] = rank5;
		json["uid"] = player5.uid;
		json["level"] = player5.level;
		json["name"] = player5.name;
		json["pic"] = player5.pic;
		players.append(json);
	}

	Json::Value &topt = result["top"];
	topt.resize(0);
	for(unsigned i=0;i<3;++i)
	{
		Json::Value json;
		json["rank"] = i+1;
		json["uid"] = top[i].uid;
		json["level"] = top[i].level;
		json["name"] = top[i].name;
		json["pic"] = top[i].pic;
		topt.append(json);
	}

	return 0;
}

int CLogicLadder::Refresh(unsigned uid, Json::Value &result)
{
	CDataLadder* pladder = GetCDataLadder();
	if (!pladder)
	{
		DB_ERROR_RETURN_MSG("init_ladder_fail");
	}
	DataUserData userData;
	CLogicUserData logicUserData;
	int ret = logicUserData.GetUserData(uid, userData);
	if (ret != 0)
		return ret;
	Json::Value &ladder = result["ladder"];
	Json::Reader reader;
	if (userData.ladder.empty() || !reader.parse(userData.ladder, ladder))
	{
		DB_ERROR_RETURN_MSG("parse_ladder_fail");
	}
	CheckLadderJson(ladder);
	RandLadderPlayers(ladder);
	ladder["upts"] = Time::GetGlobalTime();
	ret = logicUserData.SetLadder(uid, ladder);
	if (ret != 0)
		return ret;

	int rank1 = ladder["prs"][0u].asInt();
	int rank2 = ladder["prs"][1u].asInt();
	int rank3 = ladder["prs"][2u].asInt();
	int rank4 = ladder["prs"][3u].asInt();
	int rank5 = ladder["prs"][4u].asInt();
	LadderItem player1;
	LadderItem player2;
	LadderItem player3;
	LadderItem player4;
	LadderItem player5;
	LadderItem top[3];
	pladder->GetFivePlayers(rank1, rank2, rank3, rank4, rank5,
			player1, player2, player3, player4, player5,
			top);

	Json::Value &players = result["players"];
	players.resize(0);
	if (IsValidLadderRank(rank1))
	{
		Json::Value json;
		json["rank"] = rank1;
		json["uid"] = player1.uid;
		json["level"] = player1.level;
		json["name"] = player1.name;
		json["pic"] = player1.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank2))
	{
		Json::Value json;
		json["rank"] = rank2;
		json["uid"] = player2.uid;
		json["level"] = player2.level;
		json["name"] = player2.name;
		json["pic"] = player2.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank3))
	{
		Json::Value json;
		json["rank"] = rank3;
		json["uid"] = player3.uid;
		json["level"] = player3.level;
		json["name"] = player3.name;
		json["pic"] = player3.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank4))
	{
		Json::Value json;
		json["rank"] = rank4;
		json["uid"] = player4.uid;
		json["level"] = player4.level;
		json["name"] = player4.name;
		json["pic"] = player4.pic;
		players.append(json);
	}
	if (IsValidLadderRank(rank5))
	{
		Json::Value json;
		json["rank"] = rank5;
		json["uid"] = player5.uid;
		json["level"] = player5.level;
		json["name"] = player5.name;
		json["pic"] = player5.pic;
		players.append(json);
	}

	Json::Value &topt = result["top"];
	topt.resize(0);
	for(unsigned i=0;i<3;++i)
	{
		Json::Value json;
		json["rank"] = i+1;
		json["uid"] = top[i].uid;
		json["level"] = top[i].level;
		json["name"] = top[i].name;
		json["pic"] = top[i].pic;
		topt.append(json);
	}

	return 0;
}

int CLogicLadder::ReportResult(unsigned uid, const Json::Value &data)
{
	unsigned fuid = 0;
	int flevel = 0;
	int frank = 0;
	string fname;
	string fpic;
	unsigned tuid = 0;
	int tlevel = 0;
	int trank = 0;
	string tname;
	string tpic;
	int win = 0;

	Json::GetUInt(data, "fuid", fuid);
	Json::GetInt(data, "flevel", flevel);
	Json::GetInt(data, "frank", frank);
	Json::GetString(data, "fname", fname);
	Json::GetString(data, "fpic", fpic);
	Json::GetUInt(data, "tuid", tuid);
	Json::GetInt(data, "tlevel", tlevel);
	Json::GetInt(data, "trank", trank);
	Json::GetString(data, "tname", tname);
	Json::GetString(data, "tpic", tpic);

	if (!Json::GetInt(data, "win", win)
			|| !IsValidUid(fuid) || fuid != uid
			|| (frank != -1 && !IsValidLadderRank(frank)) || !IsValidLadderRank(trank))
	{
		error_log("[invalid_param][uid=%u,fuid=%u,tuid=%u,frank=%d,trank=%d,win=%d]",
				uid,fuid,tuid,frank,trank,win);
		PARAM_ERROR_RETURN_MSG("invalid_param");
	}

	DataUserData fUserData;
	DataUserData tUserData;
	CLogicUserData logicUserData;
	int ret = logicUserData.GetUserData(fuid, fUserData);
	if (ret != 0)
		return ret;
	if (IsValidUid(tuid))
	{
		ret = logicUserData.GetUserData(tuid, tUserData);
		if (ret != 0)
			return ret;
	}

	Json::Value fLadder;
	Json::Value tLadder;
	Json::Reader reader;
	if (!fUserData.ladder.empty() && !reader.parse(fUserData.ladder, fLadder))
	{
		DATA_ERROR_RETURN_MSG("parse_fladder_fail");
	}

	if (IsValidUid(tuid) &&!tUserData.ladder.empty() && !reader.parse(tUserData.ladder, tLadder))
	{
		DATA_ERROR_RETURN_MSG("parse_tladder_fail");
	}

	CheckLadderJson(fLadder);
	CheckLadderJson(tLadder);

	if (win == 1)
	{
		int win_unm = fLadder["win"].asInt()+1;
		fLadder["win"] = win_unm ;

		ret = BroadcastWinNumber(fuid, win_unm);
		if (0 != ret)
		{
			error_log("BroadCastWinNumber error! fuid=%u", fuid);
		}

		CDataLadder* pladder = GetCDataLadder();
		if (!pladder)
		{
			DB_ERROR_RETURN_MSG("init_ladder_fail");
		}
		LadderError error = LE_SUCCESS;
		ret  = pladder->Win(frank, fuid, flevel, fname, fpic,
				trank, tuid, tlevel, tname, tpic, Time::GetGlobalTime(), error);
		if (ret != 0)
		{
			error_log("[ladder win][uid=%u,frank=%d,fuid=%u,trank=%d,tuid=%u,error=%d]",
					uid,frank,fuid,trank,tuid,error);
			DB_ERROR_RETURN_MSG("set_ladder_fail");
		}
		fLadder["rank"] = frank;
		tLadder["rank"] = trank;
		RandLadderPlayers(fLadder);
		RandLadderPlayers(tLadder);
		if (1 == frank)
		{
			ret = BroadcastWinNumber(fuid,win_unm,true);
			if (0 != ret)
			{
				error_log("Broadcast number one error! fuid=%u", fuid);
			}
		}
	}
	else
	{
		fLadder["win"] = 0;
	}

	Json::Value flog;
	flog["ts"] = Time::GetGlobalTime();
	flog["name"] = tname;
	flog["win"] = win;
	flog["rank"] = fLadder["rank"].asInt();
	flog["toward"] = 1;
	fLadder["log"].append(flog);
	unsigned size = fLadder["log"].size();
	if (size > 4)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			fLadder["log"][i] = fLadder["log"][size - 4 + i];
		}
		fLadder["log"].resize(4);
	}

	if (IsValidUid(tuid))
	{
		Json::Value tlog;
		tlog["ts"] = Time::GetGlobalTime();
		tlog["name"] = fname;
		tlog["win"] = win == 1 ? 0 : 1;
		tlog["rank"] = tLadder["rank"].asInt();
		tlog["toward"] = 0;
		tLadder["log"].append(tlog);
		size = tLadder["log"].size();
		if (size > 4)
		{
			for (unsigned i = 0; i < 4; i++)
			{
				tLadder["log"][i] = tLadder["log"][size - 4 + i];
			}
			tLadder["log"].resize(4);
		}
	}
	fLadder["upts"] = Time::GetGlobalTime();
	ret = logicUserData.SetLadder(fuid, fLadder);
	if (ret != 0)
		return ret;
	if (IsValidUid(tuid))
	{
		tLadder["upts"] = Time::GetGlobalTime();
		ret = logicUserData.SetLadder(tuid, tLadder);
		if (ret != 0)
			return ret;
	}
	return 0;
}

int CLogicLadder::BroadcastWinNumber(unsigned uid, int win, bool top)
{
	return 0;//暂时屏蔽

	string message;
	if (top)
	{
		message = "天下无敌！";
	}
	else
	{
		switch (win)
		{
		case 3:
			message = "好犀利！";
			break;
		case 5:
			message = "好勇猛！";
			break;
		case 10:
			message = "好无敌！";
			break;
		default:
			break;
		}
	}

	if (message.empty())
	{
		return 0;
	}

	string userName;
	CDataUserBasic dbUserBasic;
	int ret = dbUserBasic.GetUserName(uid, OpenPlatform::GetType(),userName);
	if (0 != ret)
	{
		error_log("GetUserName error! uid=%u", uid);
		return ret;
	}
	string subMsg;
	if (top)
	{
		String::Format(subMsg, "%s在竞技场排名赛中排名天下第一！", userName.c_str());
	}
	else
	{
		String::Format(subMsg, "%s在竞技场排名赛中取得%d连胜！", userName.c_str(), win);
	}
	message.append(subMsg);

	CLogicAdmin logicadmin;

	ret = logicadmin.BroadCast(message);
	if (0 != ret)
	{
		error_log("Broadcast error!");
		return ret;
	}

	return 0;
}
