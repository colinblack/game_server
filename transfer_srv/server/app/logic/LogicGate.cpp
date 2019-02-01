/*
 * LogicGate
 *
 *  Created on: 2011-7-13
 *      Author: auto
 */

#include "LogicGate.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include "WeiyouxiPlatform.h"

const CLogicGate::GataConfig CLogicGate::s_configs[MAX_GATES] =
{
		{200,10000, 0, 0, 0, 0, 1001},
		{200,0, 10000, 0, 0, 0, 1002},
		{200,0, 0, 10000, 0, 0, 1003},
		{250,0, 0, 0, 10000, 0, 1004},
		{200,0, 0, 0, 0, 10, 1005},
		{300,20000, 0, 0, 0, 0, 1006},
		{150,0, 20000, 0, 0, 0, 1007},
		{600,0, 0, 20000, 0, 0, 1008},
		{120,0, 0, 0, 20000, 0, 1009},
		{2100,0, 0, 0, 0, 15, 1010},
		{140,30000, 0, 0, 0, 0, 1011},
		{80,0, 30000, 0, 0, 0, 1012},
		{80,0, 0, 30000, 0, 0, 1013},
		{160,0, 0, 0, 30000, 0, 1014},
		{2100,0, 0, 0, 0, 20, 1015},
		{400,40000, 0, 0, 0, 0, 1016},
		{400,0, 40000, 0, 0, 0, 1017},
		{200,0, 0, 40000, 0, 0, 1018},
		{500,0, 0, 0, 40000, 0, 1019},
		{3000,0, 0, 0, 0, 25, 1020},
		{300,50000, 0, 0, 0, 0, 1021},
		{160,0, 50000, 0, 0, 0, 1022},
		{300,0, 0, 50000, 0, 0, 1023},
		{200,0, 0, 0, 50000, 0, 1024},
		{800,0, 0, 0, 0, 30, 1025},
		{800,60000, 0, 0, 0, 0, 1026},
		{400,0, 60000, 0, 0, 0, 1027},
		{400,0, 0, 60000, 0, 0, 1028},
		{300,0, 0, 0, 60000, 0, 1029},
		{600,0, 0, 0, 0, 35, 1030},
		{500,70000, 0, 0, 0, 0, 1031},
		{200,0, 70000, 0, 0, 0, 1032},
		{350,0, 0, 70000, 0, 0, 1033},
		{400,0, 0, 0, 70000, 0, 1034},
		{600,0, 0, 0, 0, 40, 1035},
		{150,80000, 0, 0, 0, 0, 1036},
		{450,0, 80000, 0, 0, 0, 1037},
		{300,0, 0, 80000, 0, 0, 1038},
		{250,0, 0, 0, 80000, 0, 1039},
		{500,0, 0, 0, 0, 40, 1040},
		{250,90000, 0, 0, 0, 0, 1041},
		{350,0, 90000, 0, 0, 0, 1042},
		{500,0, 0, 90000, 0, 0, 1043},
		{300,0, 0, 0, 90000, 0, 1044},
		{700,0, 0, 0, 0, 40, 1045},
		{550,100000, 0, 0, 0, 0, 1046},
		{200,0, 100000, 0, 0, 0, 1047},
		{600,0, 0, 100000, 0, 0, 1048},
		{300,0, 0, 0, 100000, 0, 1049},
		{700,0, 0, 0, 0, 40, 1050},
		{300,110000, 0, 0, 0, 0, 1051},
		{700,0, 110000, 0, 0, 0, 1052},
		{400,0, 0, 110000, 0, 0, 1053},
		{600,0, 0, 0, 110000, 0, 1054},
		{200,0, 0, 0, 0, 40, 1055},
		{150,120000, 0, 0, 0, 0, 1056},
		{150,0, 120000, 0, 0, 0, 1057},
		{600,0, 0, 120000, 0, 0, 1058},
		{200,0, 0, 0, 120000, 0, 1059},
		{400,0, 0, 0, 0, 40, 1060},
		{400,120000, 0, 0, 0, 0, 1061},
		{400,0, 120000, 0, 0, 0, 1062},
		{300,0, 0, 120000, 0, 0, 1063},
		{350,0, 0, 0, 120000, 0, 1064},
		{500,0, 0, 0, 0, 45, 1065},
		{350,150000, 0, 0, 0, 0, 1066},
		{350,0, 150000, 0, 0, 0, 1067},
		{350,0, 0, 150000, 0, 0, 1068},
		{350,0, 0, 0, 150000, 0, 1069},
		{1400,0, 0, 0, 0, 45, 1070},
		{350,170000, 0, 0, 0, 0, 1071},
		{350,0, 170000, 0, 0, 0, 1072},
		{500,0, 0, 170000, 0, 0, 1073},
		{350,0, 0, 0, 170000, 0, 1074},
		{350,0, 0, 0, 0, 50, 1075},
		{350,200000, 0, 0, 0, 0, 1076},
		{350,0, 200000, 0, 0, 0, 1077},
		{350,0, 0, 200000, 0, 0, 1078},
		{350,0, 0, 0, 200000, 0, 1079},
		{1500,0, 0, 0, 0, 50, 1080},
		{700,220000, 0, 0, 0, 0, 1081},
		{700,0, 220000, 0, 0, 0, 1082},
		{500,0, 0, 220000, 0, 0, 1083},
		{500,0, 0, 0, 220000, 0, 1084},
		{700,0, 0, 0, 0, 55, 1085},
		{600,250000, 0, 0, 0, 0, 1086},
		{500,0, 250000, 0, 0, 0, 1087},
		{500,0, 0, 250000, 0, 0, 1088},
		{500,0, 0, 0, 250000, 0, 1089},
		{700,0, 0, 0, 0, 55, 1090},
};

void CLogicGate::GetRewardJson(GataConfig& data, Json::Value& result)
{
	result["cap"] = data.cap;
	result["r1"] = data.r1;
	result["r2"] = data.r2;
	result["r3"] = data.r3;
	result["r4"] = data.r4;
	result["gold"] = data.gold;
}

void CLogicGate::GetGateJson(DataGate& data, Json::Value& result)
{
	result["uid"] = data.uid;
	result["level"] = data.level;
	result["is_win"] = data.is_win;
	result["dare_times"] = data.dare_times;
	result["win_score"] = data.win_score;
	result["best_score"] = data.best_score;
	result["lose_score"] = data.lose_score;
	result["last_save_time"] = data.last_save_time;
	result["status"] = data.status;


	// int use_time; // 已使用时间. 一次闯关
	// int use_resource; // 使用兵的人口. 一次闯关
}

void CLogicGate::GetGateRankJson(DataRank& data, Json::Value& result)
{
	result["uid"] = data.uid;
	result["best_score"] = data.best_score;
	result["avatar"] = data.avatar;
	result["name"] = data.name;
	result["rank"] = data.rank;
}

const CLogicGate::GataConfig& CLogicGate::GetConfig(int level)
{
	level--;
	// s_configs
	return s_configs[level];
}

// -1 出错. 0. 有数据. 1没数据
int CLogicGate::IsGateExist(unsigned uid, int level)
{
	DataGate tmp;
	int ret = GetGate(uid, level, tmp);

	return ret;
}

int CLogicGate::ActiveNewGate(unsigned uid, int level, DataGate& data, int buildingLevel)
{
	int ret  = 0;
	ret = IsGateExist(uid, level+1);
	if (ret < 0){
		error_log("[IsGateExist fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		DB_ERROR_RETURN();
	}

	if (ret != R_ERR_NO_DATA){
		return -1; // 要激的关卡已开启. 不需要激活
	}


	ret = CreateGate(uid, level, data, buildingLevel);
	if (ret != 0)
	{
		return ret;
	}

	CDataGate gatedata;
	ret = gatedata.AddGate(data);
	if (ret != 0)
	{
		error_log("[AddGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		DB_ERROR_RETURN();
	}

	return 0;
}

int CLogicGate::CaleLoseScore(DataGate& data)
{
	if (data.use_resource == 0 && data.use_time == 0)
	{
		return 0;
	}

	int loseScore = 0;

	const GataConfig& config = GetConfig(data.level);
	int cap = config.cap;
	loseScore = data.use_time/LOST_SCORE_BY_TIME + (data.use_resource*LOST_SCORE_BY_RESOURE)/cap;

	data.lose_score += loseScore;

	// 计算完一次
	data.use_resource = 0;
	data.use_time = 0;

	return 0;
}

int CLogicGate::CaleBestScore(DataGate& data)
{
	int best = data.best_score;

	data.win_score = BASE_SCORE - data.lose_score;
	if (data.win_score <= 0) data.win_score = 0;

	if (best > data.win_score)
	{
		data.best_score = best;
	}
	else
	{
		data.best_score = data.win_score;
	}

	if (data.best_score > BASE_SCORE - 100)
	{
		data.best_score -= 100;
	}

	return 0;
}

int CLogicGate::ReduceOneTime(unsigned uid, int& timeleft)
{
	DataUserExtra data;
	int ret = 0;

	ret = LogicUser::GetGateTimes(uid, data);
	if (ret != 0)
	{
		error_log("[GetGateTimes fail][ret=%d,uid=%d]", ret, uid);
		return ret;

	}

	if (data.gate_left_times > 0)
	{
		data.gate_left_times--;
	}
	else if(data.gate_extra_times > 0)
	{
		data.gate_extra_times--;
	}
	else
	{
		error_log("[no times fail][ret=%d,uid=%d]", ret, uid);
		PARAM_ERROR_RETURN();
	}

	timeleft = data.gate_left_times + data.gate_extra_times;

	ret = LogicUser::SetGateTimes(data);
	if (ret != 0)
	{
		error_log("[SetGateTimes fail][ret=%d,uid=%d]", ret, uid);
		return ret;
	}

	return 0;
}

int CLogicGate::ResetGate(DataGate& data)
{
	data.use_resource = 0;
	data.use_time = 0;
	data.best_score = 0;
	data.win_score = 0;
	data.dare_times = 0;
	data.is_win = 0;
	data.level = 0;
	data.uid = 0;
	data.lose_score = 0;
	data.status = 0;


	return 0;
}

bool CLogicGate::IsLevelMax(int lastLevel)
{
	if (lastLevel >= MAX_GATES)
	{
		return true;
	}
	return false;
}

// 下一关的限制条件. 1. 小于最大关数. 2. 小于对应等级的关数.
// 建筑等级暂时由客户端发起
bool CLogicGate::CheckLevel(int lastLevel, int buildingLevel)
{
	if (lastLevel < 0 || lastLevel >= MAX_GATES || lastLevel >= buildingLevel*ONE_LEVEL_GATES)
	{
		return false;
	}
	return true;
}

int CLogicGate::CreateGate(unsigned uid, int lastLevel, DataGate &data, int buildingLevel)
{
	// 检测lastLevel. 需要对应建筑等级
	if (!CheckLevel(lastLevel, buildingLevel))
	{
		PARAM_ERROR_RETURN();
	}

	ResetGate(data);
	data.level = lastLevel+1;
	data.uid = uid;
	data.last_save_time = 0;

	return 0;
}

int CLogicGate::ActiveNewLevel(unsigned uid, int level, int buildingLevel, DataGate& data)
{
	// 传入的level是要开启的上一级
	int ret = ActiveNewGate(uid, level-1, data, buildingLevel);
	if (ret != 0)
	{
		error_log("[ActiveNewGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}
	return 0;
}

int CLogicGate::ResetStatus(unsigned uid, int level)
{
	int ret = 0;
	DataGate data;
	ret = GetGate(uid, level, data);
	if (ret != 0){
		return ret;
	}

	if (data.status != DataGate::UNGATE){
		data.status = DataGate::UNGATE;
		ret = UpdateGate(data);
		if (ret != 0){
			return ret;
		}
	}

	return 0;
}

int CLogicGate::AddTimes(unsigned uid, int& timeleft, int& usecach)
{
	int ret = 0;

	CLogicPay pay;
	usecach = BUY_DARE_TIMES_PER_GOLD;
	ret = pay.ChangeCash(uid, "GATETIME", BUY_DARE_TIMES_PER_GOLD);
	if (ret != 0)
	{
		error_log("[ChangeCash fail][ret=%d,uid=%d]", ret, uid);
		return ret;
	}

	DataUserExtra data;
	ret = LogicUser::GetGateTimes(uid, data);
	if (ret != 0)
	{
		error_log("[GetGateTimes fail][ret=%d,uid=%d]", ret, uid);
		return ret;
	}

	data.gate_extra_times += BUY_DARE_TIMES_PER_COUNT;
	timeleft = data.gate_left_times + data.gate_extra_times;
	ret = LogicUser::SetGateTimes(data);
	if (ret != 0)
	{
		error_log("[SetGateTimes fail][ret=%d,uid=%d]", ret, uid);
		return ret;
	}

	return 0;
}

int CLogicGate::GetGateRank(unsigned uid, int level, vector<DataRank>& outRankList)
{
	// 好友列表
	int ret = 0;
	UidList friends;
	ret = LogicFriend::GetFriends(uid, OpenPlatform::GetType(), friends);
	if (ret != 0)
	{
		return ret;
	}

	// 获得全球前5名
	const vector<DataRank>& rankList = GetGateRankOfLevel(level);
	if (ret != 0)
	{
		DATA_ERROR_RETURN();
	}
	for (unsigned i = 0; i < GOBAL_RANK_COUNT && i < rankList.size(); i++)
	{
		outRankList.push_back(rankList[i]);
	}

	//
	unsigned maxCount = MAX_RANK_COUNT;
	unsigned addCount = outRankList.size();
	vector<DataRank> rankFriendList;

	// 获得好友 - 闯关分数
	UidList::iterator ibegin = friends.begin();
	UidList::iterator iend = friends.end();
	UidList::iterator i = ibegin;
	unsigned index = 0;
	for (; i != iend; i++)
	{
		index = i - ibegin;

		bool isexist = false;
		for (unsigned j = 0; j < outRankList.size(); j++)
		{
			if (outRankList[j].uid == *i)
			{
				isexist = true;
				break;
			}
		}

		if (isexist) continue;

		DataGate gatedata;
		ret = GetGate(*i, level, gatedata);
		if (ret != 0)
		{
			continue;
		}

		DataRank rankFriend;
		rankFriend.uid = *i;
		rankFriend.best_score = gatedata.best_score;
		rankFriendList.push_back(rankFriend);
	}

	// 排序//rankFriendList.
	std::sort(rankFriendList.begin(), rankFriendList.end());



	// 好友名字跟头像
	for (unsigned i = 0; i < rankFriendList.size() && i < maxCount-addCount; i++)
	{
		DataUserBasic datauser;
		ret = LogicUserBasic::GetUserSmart(rankFriendList[i].uid, OpenPlatform::GetType(), datauser);
		if (ret != 0)
		{
			continue;
		}

		rankFriendList[i].name = datauser.name;
		rankFriendList[i].avatar = datauser.figure_url;
	}

	// 添加5个好友排行榜中
	for (unsigned index = 0; index < maxCount-addCount-1 && index < rankFriendList.size(); index++)
	{
		rankFriendList[index].rank = GetGateRankl(rankFriendList[index].uid, level);
		outRankList.push_back(rankFriendList[index]);
	}

	// 自己在不在前面的名次中
	bool selfin = false;
	for (unsigned index = 0; index < outRankList.size(); index++)
	{
		if (outRankList[index].uid == uid)
		{
			selfin = true;
			break;
		}
	}

	if (selfin)
	{
		if (rankFriendList.size() > maxCount-addCount-1)
		{
			outRankList.push_back(rankFriendList[maxCount-addCount-1]);
		}
	}
	else
	{
		// 添加自己到最后一名. 查自己信息
		DataGate gatedata;
		ret = GetGate(uid, level, gatedata);
		if (ret != 0)
		{
			return ret;
		}

		DataRank rankFriend;
		rankFriend.uid = uid;
		rankFriend.best_score = gatedata.best_score;
		DataUserBasic datauser;
		ret = LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), datauser);
		if (ret != 0)
		{
			return ret;
		}

		rankFriend.name = datauser.name;
		rankFriend.avatar = datauser.figure_url;
		rankFriend.rank = GetGateRankl(uid, level);
		outRankList.push_back(rankFriend);
	}

	// 如果好友的排名数没有超过11个. 则用全球排名补充
	if (outRankList.size() < maxCount)
	{
		unsigned len = maxCount - outRankList.size();
		unsigned index = 0;
		for (unsigned i = GOBAL_RANK_COUNT; i < rankList.size(); i++)
		{
			if (uid != rankList[i].uid)
			{
				bool isExist = false;
				for (unsigned j = 0; j < outRankList.size(); j++)
				{
					if (rankList[i].uid == outRankList[j].uid)
					{
						isExist = true;
						break;
					}
				}

				if (!isExist){
					outRankList.push_back(rankList[i]);
					index++;
					if (index >= len){
						break;
					}
				}
			}
		}
	}


	return 0;
}

int CLogicGate::AddGate(unsigned uid, const DataGate &data)
{
	CDataGate gatedata;
	int ret = gatedata.AddGate(data);
	if (ret != 0)
	{
		error_log("[AddGate fail][ret=%d,uid=%d,level=%d]", ret, uid, data.level);
		DATA_ERROR_RETURN();
	}

	return 0;
}
int CLogicGate::UpdateGate(DataGate &gate)
{
	CDataGate gatedata;
	int ret = gatedata.UpdateGate(gate);
	if (ret != 0)
	{
		error_log("[UpdateGate fail][ret=%d,uid=%d,level=%d]", ret, gate.uid, gate.level);
		DB_ERROR_RETURN();
	}

	return 0;
}

int CLogicGate::GetGate(unsigned uid, int level, DataGate &gate)
{
	CDataGate gatedata;
	int ret = gatedata.GetGate(uid, level, gate);
	if (ret < 0)
	{
		error_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		DB_ERROR_RETURN();
	}
	else
		return ret;
	/**else if (ret == R_ERR_NO_DATA)
	{
		info_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		DB_ERROR_RETURN_MSG("get_gate_fail");
	}*/

	return 0;
}
int CLogicGate::GetGates(unsigned uid, vector<DataGate>& gates)
{
	CDataGate gatedata;
	int ret = gatedata.GetGates(uid, gates);
	if (ret == 0)
	{
		return 0;
	}
	else if (ret == R_ERR_NO_DATA)
	{
		DataGate newgate;
		int activeret = ActiveNewGate(uid, 0, newgate, 1);
		if (activeret != 0)
		{
			error_log("[ActiveNewGate fail][uid=%d]", uid);
			return activeret;
		}

		gates.push_back(newgate);
	}
	else
	{
		error_log("[GetGates fail][ret=%d,uid=%d]", ret, uid);
		DB_ERROR_RETURN();
	}

	return 0;
}

int CLogicGate::GetJsonGates(unsigned uid, Json::Value& result)
{
	vector<DataGate> gates;

	int ret = GetGates(uid, gates);
	if (ret != 0)
	{
		return ret;
	}

	if (gates.size() > 0)
	{
		result.resize(gates.size());

		vector<DataGate>::iterator iterbegin = gates.begin();
		vector<DataGate>::iterator iterend = gates.end();
		vector<DataGate>::iterator iter = iterbegin;
		int index= 0;

		for (; iter != iterend; iter++)
		{
			index = iter - iterbegin;
			result[index]["best_score"] = iter->best_score;
			result[index]["level"] = iter->level;
		}
	}

	return 0;
}

int CLogicGate::BeginGate(unsigned uid, int level, DataGate& data, int& timeleft)
{
	// DataGate data;
	int ret = 0;

	ret = ReduceOneTime(uid, timeleft);
	if (ret != 0)
	{
		error_log("[ReduceOneTime fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	ret = GetGate(uid, level, data);
	if (ret != 0)
	{
		error_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	// 计算一次挑战结束.损失分数. 并重置使用资源跟时间
	CaleLoseScore(data);

	data.status = DataGate::GATING;
	data.dare_times++;
	ret = UpdateGate(data);
	if (ret != 0)
	{
		error_log("[BeginGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	return 0;
}

int CLogicGate::UpdateGating(unsigned uid, int level, int useTime, int useResource, DataGate& data)
{
	// DataGate data;
	int ret = GetGate(uid, level, data);
	if (ret != 0)
	{
		error_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	// 如果　不是正在闯关不可以更新
	if (data.status != DataGate::GATING){
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_gating");
	}

	if (useTime > 0)
	{
		data.use_time += useTime;
	}

	if (useResource > 0)
	{
		data.use_resource += useResource;
	}

	data.last_save_time = time(0);

	ret = UpdateGate(data);
	if (ret != 0)
	{
		error_log("[UpdateGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	return 0;
}

int CLogicGate::EndGate(unsigned uid, int level, int useTime, int useResource, int iswin, DataGate& data,
		int& hasNewGate, DataGate& newgate, GataConfig &reward, int buildingLevel)
{
	// DataGate data;
	int ret = GetGate(uid, level, data);
	if (ret != 0)
	{
		error_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	if (useTime > 0)
	{
		data.use_time += useTime;
	}
	if (useResource > 0)
	{
		data.use_resource += useResource;
	}

	// 计算一次挑战结束.损失分数. 并重置使用资源跟时间
	CaleLoseScore(data);

	int tmpWinScore = data.win_score;

	int lastWintimes = data.is_win;


	if (iswin != 0)
	{
		if(OpenPlatform::GetType() == PT_WEIYOUXI)
		{
			if(lastWintimes <= 0)
			{
				string openid;
				string openkey;
				ret = LogicSso::GetOpenKey(uid, openid, openkey);
				if(ret == 0)
				{
//					if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(openid, openkey, WYX_LEADERBOARD_GATE_ID, level) != 0)
//					{
//						error_log("[set_leaderboard_fail][uid=%u,lid=%u,value=%u,error=%s]",
//								uid, WYX_LEADERBOARD_GATE_ID, level, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
//					}
					if(level > 0 && level <= 50 && level % 10 == 0)
					{
						int gateAchvId = WYX_ACHIEVEMENT_GATE_BASE + level / 10;
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, gateAchvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uid, gateAchvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
				}
			}
		}


		CaleBestScore(data);
		tmpWinScore = data.win_score;

		// if (data.is_win == 0)
		// {
			if (ActiveNewGate(uid, level, newgate, buildingLevel) == 0)
			{
				// 可以开启新关卡
				hasNewGate = 1;
			}
		// }
		data.is_win++;
		data.dare_times = 0;
		data.win_score = 0;
	}

	ret = UpdateGate(data);
	data.win_score = tmpWinScore;
	data.status = DataGate::UNGATE;
	if (ret != 0)
	{
		error_log("[UpdateGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	// 加资源
	// if (iswin != 0)
	// {
		// 未胜利之前tmpWinScore为0. 所以计算出来值也都是0. 最好还是加上iswin的判断

		const GataConfig& config = GetConfig(level);
		config.Clone(reward);

		double winRate = 1.0*tmpWinScore/BASE_SCORE;
		reward.Reduce(lastWintimes, winRate, level);

		if (reward.r1 != 0 || reward.r2 != 0 || reward.r3 != 0 || reward.r4 != 0)
		{
			ret = LogicUser::ChangeResource(uid, reward.r1, reward.r2, reward.r3, reward.r4);
			if (ret != 0)
			{
				error_log("[ChangeResource fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
				// CopyErrorFrom(user);
				return ret;
			}
		}
		if (reward.gold != 0)
		{
			CLogicPay pay;
			ret = pay.ChangeCash(uid, "GATERW", reward.gold);
			if (ret != 0)
			{
				error_log("[ChangeCash fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
				// CopyErrorFrom(pay);
				return ret;
			}
		}
	// }

	return 0;
}

//
int CLogicGate::RestartGate(unsigned uid, int level, DataGate& data)
{
	int ret = 0;

	ret = GetGate(uid, level, data);
	if (ret != 0)
	{
		error_log("[GetGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	int iswin = data.is_win;
	int bestScore = data.best_score;
	ResetGate(data);
	data.uid = uid;
	data.level = level;
	data.is_win = iswin;
	data.best_score = bestScore;

	ret = UpdateGate(data);
	if (ret != 0)
	{
		error_log("[UpdateGate fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	const GataConfig& config = GetConfig(level);
	ret = LogicBase::RemoveBase(uid, (unsigned)config.baseid);
	if (ret != 0)
	{
		error_log("[RestartGate RemoveBase fail][ret=%d,uid=%d,level=%d]", ret, uid, level);
		return ret;
	}

	return 0;
}

vector<DataRank> CLogicGate::gateRanks[GATA_LEVEL_MAX];

const vector<DataRank>& CLogicGate::GetGateRankOfLevel(int level)
{
	static VRankOfLvl nullRank;
	static unsigned int rankUpdateTime = 0;

	if (level < 1 || level > GATA_LEVEL_MAX)
		return nullRank;

	unsigned int now = time(0);
	if (now - rankUpdateTime < 900)
		return gateRanks[level - 1];

	string dateDir = Config::GetValue("gate_top_dir");
	if (dateDir.empty())
		dateDir = "/usr/local/monitor_toy/data/gate/";
	string prefix = "top_";
	string suffix = ".txt";
	char buff[512];
	for (int i = 0; i < GATA_LEVEL_MAX; i++)
	{
		gateRanks[i].clear();
		string filePath = dateDir + prefix + CTrans::ITOS(i+1) + suffix;
		ifstream fin(filePath.c_str());
		if (!fin)
		{
			//error_log("[file no found][file=%s]",filePath.c_str());
			continue;
		}
		int count = 0;
		while (fin.getline(buff, sizeof(buff)))
		{
			if (string("") == buff)
				continue;
			istringstream iss(buff);
			DataRank dataRank;
			dataRank.uid = 0;
			dataRank.rank = ++count;
			dataRank.best_score = 0;
			iss >> dataRank.uid >> dataRank.name
				>> dataRank.best_score >> dataRank.avatar;
			if (dataRank.uid == 0)
				continue;
			gateRanks[i].push_back(dataRank);
		}
	}
	return gateRanks[level - 1];
}

int CLogicGate::GetGateRankl(unsigned uid, int level)
{
	const VRankOfLvl &vRank = GetGateRankOfLevel(level);
	VRankOfLvl::const_iterator it = vRank.begin();
	for (; it != vRank.end(); it++)
	{
		if (it->uid == uid)
			return it->rank;
	}
	return 0;
}
