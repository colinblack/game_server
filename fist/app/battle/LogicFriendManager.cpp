/*
 * LogicFriendManager.cpp
 *
 *  Created on: 2018年8月24日
 *      Author: colin
 */

#include "LogicFriendManager.h"

DBCFriendWrap::DBCFriendWrap(unsigned index)
	: container_(DataConcernManager::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{
}

DBCFriendWrap::DBCFriendWrap(unsigned uid, unsigned id)
	: container_(DataConcernManager::Instance())
	, index_(container_->GetIndex(uid, id))
	, data_(container_->m_data->data[index_])
{
}

void DBCFriendWrap::UpdateDonationTs(unsigned ts)
{
	data_.donationTs = ts;
	Save();
}

bool DBCFriendWrap::UpdateBattleTs()
{
	if(Time::IsToday(data_.battleTs))
		return false;
	data_.battleTs = Time::GetGlobalTime();
	Save();
	return true;
}

void DBCFriendWrap::UpdateBattle(int type)
{
	data_.battle = type;
	Save();
}

void DBCFriendWrap::FullMessage(unsigned uid, ProtoFriend::RecommendInfo* friends)
{
	LogicFriendManager::Instance()->FullMessage(uid, friends);
	data_.SetMessage(friends);
}

int LogicFriendManager::FullMessage(unsigned uid, User::FriendInfo*msg)
{
	vector<unsigned> vIndexs;
	DataConcernManager::Instance()->GetIndexs(uid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DBCFriendWrap data(vIndexs[i]);
		unsigned otherId = data.Obj().id;
		try
		{
		//加载对方数据
			OffUserSaveControl  offuserCtl(otherId);
			data.FullMessage(otherId, msg->add_info());
		}
		catch(const std::exception &e)
		{
			error_log("uid: %u, id: %u, %s", uid, data.Obj().id, e.what());
		}
	}

	return 0;
}


void LogicFriendManager::FullMessage(unsigned uid, ProtoFriend::RecommendInfo* msg)
{
	//加载对方数据
	OffUserSaveControl  offuserCtl(uid);

	auto& rItem = LogicResourceManager::Instance()->Get(uid);
	auto& gItem	= LogicUserGradeManager::Instance()->Get(uid);
	msg->set_uid(rItem.uid);
	msg->set_fig(string(rItem.fig));
	msg->set_name(string(rItem.name));
	msg->set_level(rItem.level);
	msg->set_grade(gItem.grade);
	msg->set_onlinets(rItem.ts);
	for(int i = 0; i < MAX_FORMATION_HERO; ++i)
	{
		if(rItem.heros[i].id == 0)
			continue;
		msg->add_heroid(rItem.heros[i].id);
	}
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::ProtoRecommendUserReq* req, ProtoFriend::ProtoRecommendUserResp* resp)
{
	try
	{
		vector<unsigned> users;
		RecommendUser(uid, users);
		auto info = resp->mutable_user();
		for(auto& uid : users)
		{
			auto p = info->Add();
			FullMessage(uid, p);
		}
	}
	catch(const exception& e)
	{
		error_log("recommend: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::ProtoConcernReq* req)
{
	unsigned otherId = req->otherid();

	if(CMI->IsNeedConnectByUID(otherId))
	{
		ProtoFriend::ProtoConcernResp* resp = new ProtoFriend::ProtoConcernResp;
		try
		{
			Concern(uid, otherId);
			DBCFriendWrap friends(uid, otherId);
			friends.Obj().SetMessage(resp->mutable_info());
		}
		catch(const exception& e)
		{
			delete resp;
			error_log("uid: %u, %s", uid, e.what());
			return R_ERROR;
		}
		LMI->sendMsg(uid, resp);

		ProtoFriend::ProtoCSConcernReq *msg = new ProtoFriend::ProtoCSConcernReq;
		msg->set_myuid(uid);
		msg->set_othuid(otherId);
		return ProtoManager::BattleConnectNoReplyByUID(otherId, msg);
	}
	Concern(uid, otherId);

	return 0;
}

int LogicFriendManager::Process(ProtoFriend::ProtoCSConcernReq* req)
{
	unsigned myUid = req->othuid();
	unsigned otherId = req->myuid();
	ProtoFriend::ProtoCSConcernResp* resp = new ProtoFriend::ProtoCSConcernResp;

	resp->set_myuid(myUid);
	FullMessage(myUid, resp->mutable_info());

	return LMI->sendMsg(otherId, resp) ? 0 : R_ERROR;

}


int LogicFriendManager::Process(unsigned uid, ProtoFriend::ProtoCancelConcernReq* req)
{
	unsigned otherUid = req->otherid();
	//判断对方是否已在你的关注列表中
	if (!DataConcernManager::Instance()->IsExistItem(uid, otherUid))
	{
		error_log("user not in concern list. uid=%u,othuid=%u", uid, otherUid);
		throw runtime_error("user_not_concerned");
	}

	//对方uid是否有效
	if(!IsValidUid(otherUid))
	{
		error_log("othuid is invalid. uid=%u,othuid=%u", uid, otherUid);
		throw runtime_error("param_uid_invalid");
	}

	//从关注列表中删除
	DataConcernManager::Instance()->DelItem(uid, otherUid);

	return 0;
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::ProtoGetFriendsReq* req)
{
	vector<unsigned> vIndexs;
	map<unsigned, vector<unsigned>> zoneUids;
	DataConcernManager::Instance()->GetIndexs(uid, vIndexs);
	ProtoFriend::ProtoGetFriendsResp *resp = new ProtoFriend::ProtoGetFriendsResp;
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DBCFriendWrap data(vIndexs[i]);
		unsigned otherId = data.Obj().id;
		if(!IsValidUid(data.Obj().id))
			continue;

		if(CMI->IsNeedConnectByUID(otherId))
		{
			data.Obj().SetMessage(resp->add_user());
			unsigned zone = Config::GetZoneByUID(otherId);
			zoneUids[zone].push_back(otherId);
		}
		else
		{
			try
			{
				data.FullMessage(data.Obj().id, resp->add_user());
			}
			catch(const std::exception &e)
			{
				delete resp;
				error_log("uid: %u, %s", uid, e.what());
				return R_ERROR;
			}
		}
	}

	for(auto& v : zoneUids)
	{
		ProtoFriend::ProtoCSGetFriendsReq* friendsReq = new ProtoFriend::ProtoCSGetFriendsReq;
		friendsReq->set_myuid(uid);
		unsigned otherId = v.second.front();
		for(auto& e : v.second)
		{
			friendsReq->add_othuid(e);
		}
		ProtoManager::BattleConnectNoReplyByUID(otherId, req);
	}

	return LMI->sendMsg(uid, resp) ? 0: R_ERROR;
}

int LogicFriendManager::Process(ProtoFriend::ProtoCSGetFriendsReq* req)
{
	ProtoFriend::ProtoCSGetFriendsResp *resp = new ProtoFriend::ProtoCSGetFriendsResp;
	resp->set_myuid(req->myuid());

	for(int i = 0; i < req->othuid_size(); ++i)
	{
		unsigned myuid = req->othuid(i);
		FullMessage(myuid, resp->add_info());
	}

	return LMI->sendMsg(req->myuid(), resp);
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::ProtoDonatePowerReq* req)
{
	unsigned otherId = req->otherid();
	//判断对方是否已在你的关注列表中
	if (!DataConcernManager::Instance()->IsExistItem(uid, otherId))
	{
		error_log("user not in concern list. uid=%u,othuid=%u", uid, otherId);
		throw runtime_error("user_not_concerned");
	}

	DBCFriendWrap data(uid, otherId);

	//是否已赠送
	if(Time::IsToday(data.Obj().donationTs))
		throw runtime_error("donateTs_error");

	//系统好友
	if(uid == otherId)
	{
		data.UpdateDonationTs(Time::GetGlobalTime());
		ProtoFriend::ProtoDonatePowerResp* msg = new ProtoFriend::ProtoDonatePowerResp;
		return LMI->sendMsg(otherId, msg) ? 0 : R_ERROR;
	}
	//跨服赠送
	if(CMI->IsNeedConnectByUID(otherId))
	{
		ProtoFriend::ProtoCSDonatePowerReq *msg = new ProtoFriend::ProtoCSDonatePowerReq;
		msg->set_othuid(otherId);

		return ProtoManager::BattleConnectNoReplyByUID(otherId, msg);
	}
	DonateFriendPower(otherId);

	return R_SUCCESS;
}

int LogicFriendManager::Process(ProtoFriend::ProtoCSDonatePowerReq* req)
{
	unsigned myUid = req->othuid();
	DBCUserBaseWrap userWrap(myUid);
	DonateFriendPower(myUid);

	return R_SUCCESS;
}

void LogicFriendManager::RecommendUser(unsigned uid, vector<unsigned>& users)
{
	auto userMap = ResourceManager::Instance()->GetMap();

	vector<unsigned> vIndexs;
	vector<unsigned> friends;
	DataConcernManager::Instance()->GetIndexs(uid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DataConcern& data = DataConcernManager::Instance()->GetDataByIndex(vIndexs[i]);
		friends.push_back(data.id);
	}
	//过滤自己
	if(userMap.count(uid) != 0)
		userMap.erase(uid);
	//过滤掉好友
	for(auto& id : friends)
	{
		if(userMap.count(id) != 0)
			userMap.erase(id);
	}

	//在线
	set<unsigned> onlineSet;
	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		if(UMI->IsOnline(it.first))
		{
			onlineSet.insert(it.first);
		}
	});
	SelectUser(uid, onlineSet, users);

	//今天登陆过的
	if(users.size() == RECOMMEND_USER_NUM)
		return;

	set<unsigned> todaySet;
	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		if(LogicResourceManager::Instance()->Get(it.first).last_login_time && onlineSet.count(it.first) == 0)
			todaySet.insert(it.first);
	});
	SelectUser(uid, todaySet, users);

	//昨天登录过的
	if(users.size() == RECOMMEND_USER_NUM)
		return;

	set<unsigned> yesterdaySet;
	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		if(Time::IsToday(LogicResourceManager::Instance()->Get(it.first).last_login_time + 86400))
			yesterdaySet.insert(it.first);	
	});
	SelectUser(uid, yesterdaySet, users);


	//近3天登录过的
	if(users.size() == RECOMMEND_USER_NUM)
		return;

	set<unsigned> threedaySet;
	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		if(Time::IsToday(LogicResourceManager::Instance()->Get(it.first).last_login_time+ 86400*3))
			threedaySet.insert(it.first);
	});
	SelectUser(uid, threedaySet, users);
}

void LogicFriendManager::SelectUser(unsigned uid, set<unsigned>& userSet, vector<unsigned> &users)
{
	if(users.size() == RECOMMEND_USER_NUM)
		return;

	//搜索等级范围
	DBCUserBaseWrap userWrap(uid);
	int level = userWrap.Obj().level;
	const int range = 5;
	int min = level - range;
	int max = level + range;

	if(min <= 0)
		min = 1;
	if(max > USER_MAX_LEVEL)
		max = USER_MAX_LEVEL;

	set<unsigned> levelSet;

	std::for_each(userSet.begin(), userSet.end(), [&](unsigned id){
		auto& item = LogicResourceManager::Instance()->Get(id);
		if(item.level >= (unsigned)min && item.level <= (unsigned)max)
			levelSet.insert(id);
	});
	unsigned left = RECOMMEND_USER_NUM - users.size();

	vector<int> res;
	LogicCommonUtil::GetRandoms(0, levelSet.size() - 1, left, res);


	for(auto& i : res)
	{
		auto iter = levelSet.begin();
		advance(iter, i);
		users.push_back(*iter);
	}
}

int LogicFriendManager::Concern(unsigned uid, unsigned otherId)
{
	//对方是否已在关注列表中
	if(DataConcernManager::Instance()->IsExistItem(uid, otherId))
	{
		error_log("user already in concern list. uid=%u,othuid=%u", uid, otherId);
		throw runtime_error("user_already_concerned");
	}

	//对方uid是否有效
	if(!IsValidUid(otherId))
	{
		error_log("othuid is invalid. uid=%u,othuid=%u", uid, otherId);
		throw runtime_error("param_uid_invalid");
	}
	//判断好友数量是否达到上限
	vector<unsigned> indexs;
	DataConcernManager::Instance()->GetIndexs(uid, indexs);
	if (indexs.size() >= MAX_FRIEND_NUM)
	{
		error_log("concern nums max. uid=%u,othuid=%u", uid, otherId);
		throw runtime_error("concern_num_max");
	}
	//添加关注
	DataConcernManager::Instance()->GetData(uid, otherId);

	return R_SUCCESS;
}

int LogicFriendManager::DonateFriendPower(unsigned otherId)
{
	DBCUserBaseWrap userWrap(otherId);

	if(userWrap.Obj().daily_power >= POWER_DAILY_MAX_DONATE)
	{
		error_log("donation max");
		throw runtime_error("max_donation");
	}
	//恢复体力
	userWrap.RecoverPower(Time::GetGlobalTime(), userWrap.Obj().recover_time);
	if(UserManager::Instance()->IsOnline(otherId))
	{
		ProtoFriend::ProtoDonatePowerResp* msg = new ProtoFriend::ProtoDonatePowerResp;
		CommonGiftConfig::CommonModifyItem cfg;
		cfg.mutable_based()->set_power(POWER_DONATE_PER);
		LogicUserManager::Instance()->CommonProcess(otherId, cfg, "danate_power_online", msg->mutable_commons());
		return LMI->sendMsg(otherId, msg) ? 0 : R_ERROR;
	}
	else
	{
		return AsynManager::Instance()->Add(otherId, e_asyn_power, POWER_DONATE_PER);
	}

	return R_SUCCESS;
}

