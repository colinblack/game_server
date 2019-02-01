/*
 * LogicUserGradeManager.cpp
 *
 *  Created on: 2018年8月8日
 *      Author: colin
 */

#include "LogicUserGradeManager.h"


UserGradeItem& LogicUserGradeManager::Get(unsigned uid)
{
	int index = UserGradeManager::Instance()->GetIndex(uid);
	if(index < 0)
		index = this->Init(uid);

	return UserGradeManager::Instance()->m_data->item[index];
}


int LogicUserGradeManager::Init(unsigned uid)
{
	int idx = UserGradeManager::Instance()->GetIndex(uid);
	if(idx < 0)
	{
		int ret = UserGradeManager::Instance()->Add(uid);
		if(ret != R_SUCCESS)
		{
			throw std::runtime_error("data_error");
		}

		idx = UserGradeManager::Instance()->GetIndex(uid);
		if (idx < 0)
		{
			throw std::runtime_error("data_error");
		}
	}

	return idx;
}

unsigned LogicUserGradeManager::Match(unsigned uid, unsigned grade)
{
	int idx = grade -1;
	unsigned ret = 0;
	while(idx >= 0)
	{
		ret = UserGradeManager::Instance()->GetUserRandom(uid, idx);
		if(0 != ret)
			break;
		--idx;
	}
	return ret;
}

void LogicUserGradeManager::UpdateScore(unsigned uid, unsigned score)
{
	int index = UserGradeManager::Instance()->GetIndex(uid);
	if (index < 0)
	{
		error_log("data_error uid: %u", uid);
		throw runtime_error("data_error");
	}

	UserGradeItem& item = UserGradeManager::Instance()->m_data->item[index];
	if(item.daily_score > (GRADE_DAILY_SCORE-GRADE_PER_SCORE))
		return;

	item.daily_score += GRADE_PER_SCORE;
	item.score += GRADE_PER_SCORE;
	auto& grade = GradeCfgWarp().Grade();
	unsigned maxlv  = grade.score_size();
	if(item.grade == maxlv)
		return ;

	unsigned nextScore = grade.score(item.grade);

	if(item.score >= nextScore)
	{
		item.grade += 1;
		//段位升级
		auto& reward =  GradeCfgWarp().Grade().upgrade(item.grade-1).reward();
		UserGradeManager::Instance()->UpdateGradeIndex(uid, (int)item.grade-2, (int)item.grade-1);
		ProtoPush::PushGradeUp *msg = new ProtoPush::PushGradeUp;
		LogicUserManager::Instance()->CommonProcess(uid, reward, "grade_up_reward", msg->mutable_commons());
		LogicManager::Instance()->sendMsg(uid, msg);
	}

}

void LogicUserGradeManager::FullMessage(unsigned uid, User::GradeBattle* msg)
{
	UserGradeItem& item = Get(uid);
	msg->set_grade(item.grade);
	msg->set_dailyscore(item.daily_score);
	msg->set_score(item.score);
	msg->set_ts(item.daily_reward_ts);
}

void LogicUserGradeManager::UserGradeRank()
{
	auto& gradeMap = UserGradeManager::Instance()->GetMap();
	map<unsigned,  set<unsigned>> result;
	for(auto& e : gradeMap)
	{
		result[Get(e.first).grade].insert(e.first);
	}

	unsigned itemSize = gradeMap.size() > RANK_SIZE ? RANK_SIZE:  gradeMap.size();
	Json::Value array;
	for(auto iter1 = result.rbegin(); iter1 != result.rend(); ++iter1)
	{
		if(array["grade_rank"].size() == itemSize)
			break;

		for(auto iter2 = iter1->second.rbegin(); iter2 != iter1->second.rend(); ++iter2)
		{
			Json::Value item;
			item["uid"] = *iter2;
			auto& rItem =  LogicResourceManager::Instance()->Get(*iter2);
			item["name"] = rItem.name;
			item["fig"] = rItem.fig;
			item["grade"] = iter1->first;
			array["grade_rank"].append(item);
		}
	}

	string path = Config::GetPath(GRADE_RANK_PATH) +  CTrans::ITOS(Config::GetIntValue(CONFIG_SRVID)) + ".json";
	fstream output(path.c_str(), ios::out);
	output << array.toStyledString();
	output.close();
}


void LogicUserGradeManager::UserGradeResultRank()
{
	auto& gradeMap = UserGradeManager::Instance()->GetMap();
	map<double, set<unsigned>> result;
	for(auto& e : gradeMap)
	{
		unsigned win = Get(e.first).win;
		unsigned battleCnt = Get(e.first).battle_cnt;
		result[win/(double)battleCnt].insert(e.first);
	}
	unsigned itemSize = gradeMap.size() > RANK_SIZE ? RANK_SIZE:  gradeMap.size();
	Json::Value array;
	for(auto iter1 = result.rbegin(); iter1 != result.rend(); ++iter1)
	{
		if(array["result_rank"].size() == itemSize)
			break;

		for(auto iter2 = iter1->second.rbegin(); iter2 != iter1->second.rend(); ++iter2)
		{
			Json::Value item;
			item["uid"] = *iter2;
			auto& rItem =  LogicResourceManager::Instance()->Get(*iter2);
			item["name"] = rItem.name;
			item["fig"] = rItem.fig;
			item["result"] = iter1->first;
			array["result_rank"].append(item);
		}
	}

	string path = Config::GetPath(GRADE_RESULT_RANK_PATH) +  CTrans::ITOS(Config::GetIntValue(CONFIG_SRVID)) + ".json";
	fstream output(path.c_str(), ios::out);
	output << array.toStyledString();
	output.close();
}
