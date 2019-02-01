/*
 * LogicNewMatch.cpp
 *
 *  Created on: 2015-10-23
 *      Author: Ralf
 */

#include "LogicNewMatch.h"

int CLogicNewMatch::Get(unsigned uid, Json::Value &result)
{
	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	const DataNewMatch& res = pData->Get();

	result["stage"] = res.stage;
	if(res.stage == e_NewMatchStage_apply_regular)
	{
		result["rank"].resize(DATA_NEW_MATCH_RANK);
		for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
		{
			result["rank"][i]["name"] = res.rank[i].name;
			result["rank"][i]["aname"] = res.rank[i].aname;
			result["rank"][i]["fig"] = res.rank[i].fig;
			result["rank"][i]["score"] = res.rank[i].score;
		}

		NewMatchUser user;
		NewMatchUserMap::const_iterator it = res.user.find(uid);
		if(it != res.user.end())
			user = it->second;

		result["self"]["score"] = user.score;
		result["self"]["turn"] = user.turn;

		result["self"]["index"].resize(DATA_NEW_MATCH_HERO);
		for(unsigned i=0;i<DATA_NEW_MATCH_HERO;++i)
			result["self"]["index"][i] = user.index[i];

		result["self"]["hero"].resize(DATA_NEW_MATCH_HERO);
		for(unsigned i=0;i<DATA_NEW_MATCH_HERO;++i)
		{
			result["self"]["hero"][i]["hid"] = user.hero[i].hid;
			result["self"]["hero"][i]["job"] = user.hero[i].job;
			result["self"]["hero"][i]["level"] = user.hero[i].level;
			result["self"]["hero"][i]["hp"] = user.hero[i].hp;
			result["self"]["hero"][i]["property"].resize(BattleRoomHeroProperty_max);
			for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
				result["self"]["hero"][i]["property"][k] = user.hero[i].property[k];
		}
	}
	else
	{
		NewMatchGuess guess;
		NewMatchGuessMap::const_iterator it = res.guess.find(uid);
		if(it != res.guess.end())
			guess = it->second;

		result["guess"] = guess.guess;
		result["bet"] = guess.bet;

		result["top8"].resize(8);
		for(unsigned i=0;i<8;++i)
		{
			result["top8"][i]["uid"] = res.top8[i].uid;

			result["top8"][i]["index"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
				result["top8"][i]["index"][j] = res.top8[i].index[j];

			result["top8"][i]["hero"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			{
				result["top8"][i]["hero"][j]["hid"] = res.top8[i].hero[j].hid;
				result["top8"][i]["hero"][j]["job"] = res.top8[i].hero[j].job;
				result["top8"][i]["hero"][j]["level"] = res.top8[i].hero[j].level;
				result["top8"][i]["hero"][j]["hp"] = res.top8[i].hero[j].hp;
				result["top8"][i]["hero"][j]["property"].resize(BattleRoomHeroProperty_max);
				for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
					result["top8"][i]["hero"][j]["property"][k] = res.top8[i].hero[j].property[k];
			}
			result["top8"][i]["aname"] = res.top8[i].aname;
			result["top8"][i]["fig"] = res.top8[i].fig;
			result["top8"][i]["name"] = res.top8[i].name;
		}

		result["top4"].resize(4);
		for(unsigned i=0;i<4;++i)
		{
			result["top4"][i]["uid"] = res.top4[i].uid;

			result["top4"][i]["index"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
				result["top4"][i]["index"][j] = res.top4[i].index[j];

			result["top4"][i]["hero"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			{
				result["top4"][i]["hero"][j]["hid"] = res.top4[i].hero[j].hid;
				result["top4"][i]["hero"][j]["job"] = res.top4[i].hero[j].job;
				result["top4"][i]["hero"][j]["level"] = res.top4[i].hero[j].level;
				result["top4"][i]["hero"][j]["hp"] = res.top4[i].hero[j].hp;
				result["top4"][i]["hero"][j]["property"].resize(BattleRoomHeroProperty_max);
				for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
					result["top4"][i]["hero"][j]["property"][k] = res.top4[i].hero[j].property[k];
			}
			result["top4"][i]["aname"] = res.top4[i].aname;
			result["top4"][i]["fig"] = res.top4[i].fig;
			result["top4"][i]["name"] = res.top4[i].name;
		}

		result["top2"].resize(2);
		for(unsigned i=0;i<2;++i)
		{
			result["top2"][i]["uid"] = res.top2[i].uid;

			result["top2"][i]["index"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
				result["top2"][i]["index"][j] = res.top2[i].index[j];

			result["top2"][i]["hero"].resize(DATA_NEW_MATCH_HERO);
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			{
				result["top2"][i]["hero"][j]["hid"] = res.top2[i].hero[j].hid;
				result["top2"][i]["hero"][j]["job"] = res.top2[i].hero[j].job;
				result["top2"][i]["hero"][j]["level"] = res.top2[i].hero[j].level;
				result["top2"][i]["hero"][j]["hp"] = res.top2[i].hero[j].hp;
				result["top2"][i]["hero"][j]["property"].resize(BattleRoomHeroProperty_max);
				for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
					result["top2"][i]["hero"][j]["property"][k] = res.top2[i].hero[j].property[k];
			}
			result["top2"][i]["aname"] = res.top2[i].aname;
			result["top2"][i]["fig"] = res.top2[i].fig;
			result["top2"][i]["name"] = res.top2[i].name;
		}
	}

	return 0;
}

int CLogicNewMatch::Apply(unsigned uid, Json::Value &data)
{
	if(!data.isMember("hero") || !data["hero"].isArray() || data["hero"].size()!= DATA_NEW_MATCH_HERO)
		return R_ERR_PARAM;

	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	NewMatchUser user;
	user.uid = uid;
	Json::GetString(data, "aname", user.aname);
	Json::GetString(data, "fig", user.fig);
	Json::GetString(data, "name", user.name);
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		Json::GetUInt(data["hero"][j], "hid", user.hero[j].hid);
		Json::GetUInt(data["hero"][j], "job", user.hero[j].job);
		Json::GetUInt(data["hero"][j], "level", user.hero[j].level);
		for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
			user.hero[j].property[k] = data["hero"][j]["property"][k].asInt();
	}

	int ret = pData->Apply(user);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewMatch::ChangeIndex(unsigned uid, Json::Value &data)
{
	if(!data.isMember("index") || !data["index"].isArray() || data["index"].size()!= DATA_NEW_MATCH_HERO)
		return R_ERR_PARAM;

	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	unsigned index[DATA_NEW_MATCH_HERO];
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
		index[j] = data["index"][j].asUInt();

	int ret = pData->ChangeIndex(uid, index);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewMatch::Fight(unsigned uid, Json::Value &result)
{
	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	NewMatchUser user[2];
	int ret = pData->Fight(uid, user);
	if(ret)
		return ret;

	unsigned reward = 0;
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		if(!user[0].hero[j].dead())
			++reward;
	}
	if(reward)
	{
		CLogicUser logicUser;
		ret = logicUser.ChangeBet(uid,reward*5);
		if(ret)
			return ret;
	}

	result["score"] = user[0].score;
	result["turn"] = user[0].turn;
	result["user"].resize(2);
	for(unsigned i=0;i<2;++i)
	{
		result["user"][i]["index"].resize(DATA_NEW_MATCH_HERO);
		for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			result["user"][i]["index"][j] = user[i].index[j];

		result["user"][i]["hero"].resize(DATA_NEW_MATCH_HERO);
		for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
		{
			result["user"][i]["hero"][j]["hid"] = user[i].hero[j].hid;
			result["user"][i]["hero"][j]["job"] = user[i].hero[j].job;
			result["user"][i]["hero"][j]["level"] = user[i].hero[j].level;
			result["user"][i]["hero"][j]["hp"] = user[i].hero[j].hp;
			result["user"][i]["hero"][j]["property"].resize(BattleRoomHeroProperty_max);
			for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
				result["user"][i]["hero"][j]["property"][k] = user[i].hero[j].property[k];
		}
	}

	const DataNewMatch& res = pData->Get();
	result["rank"].resize(DATA_NEW_MATCH_RANK);
	for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
	{
		result["rank"][i]["name"] = res.rank[i].name;
		result["rank"][i]["aname"] = res.rank[i].aname;
		result["rank"][i]["fig"] = res.rank[i].fig;
		result["rank"][i]["score"] = res.rank[i].score;
	}

	return 0;
}

int CLogicNewMatch::Guess(unsigned uid, unsigned guess, unsigned bet)
{
	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	CLogicUser logicUser;
	int ret = logicUser.ChangeBet(uid,-1*(int)bet);
	if(ret)
		return ret;

	ret = pData->Guess(uid, guess, bet);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewMatch::Reward()
{
	CDataNewMatch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	set<unsigned> top8, top4;
	unsigned top2 = 0, top = 0;
	const DataNewMatch& data = pData->Get();

	for(int i=0;i<8;++i)
	{
		if(IsValidUid(data.top8[i].uid))
			top8.insert(data.top8[i].uid);
	}
	for(int i=0;i<4;++i)
	{
		if(IsValidUid(data.top4[i].uid))
		{
			top8.erase(data.top4[i].uid);
			top4.insert(data.top4[i].uid);
		}
	}
	for(int i=0;i<2;++i)
	{
		if(IsValidUid(data.top2[i].uid))
			top4.erase(data.top2[i].uid);
	}
	unsigned win = 0;
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		if(data.top2[1].hero[j].dead())
			++win;
	}
	if(win >= DATA_NEW_MATCH_HERO/2 + 1)
	{
		top = data.top2[0].uid;
		top2 = data.top2[1].uid;
	}
	else
	{
		top2 = data.top2[0].uid;
		top = data.top2[1].uid;
	}

	CLogicPay logicPay;
	CLogicUpdates logicUpdates;
	for(set<unsigned>::iterator it=top8.begin();it!=top8.end();++it)
	{
		logicPay.ChangePay(*it,0,50,"NEW_MATCH_TOP8");

		Json::Value update;
		update["s"] = "NEWMATCHTOP";
		update["coins"] = 50;
		update["rank"] = 8;
		update["ts"] = Time::GetGlobalTime();
		logicUpdates.AddUpdates(*it, update,true);
	}
	for(set<unsigned>::iterator it=top4.begin();it!=top4.end();++it)
	{
		logicPay.ChangePay(*it,0,100,"NEW_MATCH_TOP4");

		Json::Value update;
		update["s"] = "NEWMATCHTOP";
		update["coins"] = 100;
		update["rank"] = 4;
		update["ts"] = Time::GetGlobalTime();
		logicUpdates.AddUpdates(*it, update,true);
	}
	{
		logicPay.ChangePay(top2,0,200,"NEW_MATCH_TOP2");

		Json::Value update;
		update["s"] = "NEWMATCHTOP";
		update["coins"] = 200;
		update["rank"] = 2;
		update["ts"] = Time::GetGlobalTime();
		logicUpdates.AddUpdates(top2, update,true);
	}
	{
		logicPay.ChangePay(top,0,300,"NEW_MATCH_TOP");

		Json::Value update;
		update["s"] = "NEWMATCHTOP";
		update["coins"] = 300;
		update["rank"] = 1;
		update["ts"] = Time::GetGlobalTime();
		logicUpdates.AddUpdates(top, update,true);
	}

	unsigned winCoins = 0, failCoins = 0;
	for(NewMatchGuessMap::const_iterator it=data.guess.begin();it!=data.guess.end();++it)
	{
		if(it->second.guess == top)
			winCoins += it->second.bet;
		else
			failCoins += it->second.bet;
	}
	CLogicUser logicUser;
	float r = (float)failCoins / (float)winCoins * 0.9f;
	for(NewMatchGuessMap::const_iterator it=data.guess.begin();it!=data.guess.end();++it)
	{
		if(it->second.guess == top)
		{
			int reward = (float)it->second.bet * r;
			if(reward < 1)
				reward = 1;
			logicUser.ChangeBet(it->second.uid, it->second.bet + reward);

			Json::Value update;
			update["s"] = "NEWMATCHGUESS";
			update["bet"] = it->second.bet + reward;
			update["ts"] = Time::GetGlobalTime();
			logicUpdates.AddUpdates(it->second.uid, update,true);
		}
	}

	return 0;
}
