/*
 * LogicMartialClubManager.cpp
 *
 *  Created on: 2018年8月31日
 *      Author: colin
 */

#include "LogicMartialClubManager.h"

DBCMartialClubWrap::DBCMartialClubWrap(unsigned index)
	: container_(DataMartialClubManager::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{
}


DBCMartialClubWrap::DBCMartialClubWrap(unsigned uid, unsigned id)
	: container_(DataMartialClubManager::Instance())
	, index_(container_->GetIndex(uid, id))
	, data_(container_->m_data->data[index_])
{

}

void DBCMartialClubWrap::FullMessage(ProtoMartialClub::MartialClubInfo *msg) const
{
	data_.SetMessage(msg);
	auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
	for(auto e : propIndex)
	{
		auto p = msg->add_props();
		p->set_id(e.first);
		p->set_count(data_.props[e.second]);
	}
}

 int LogicMartialClubManager::OnInit()
{
	 unsigned propsId[MARTIAL_CLUB_REAP_PROPS] = {SKILL_BOOK_ID, DRAGON_SCALE_ID};
	 for(int i = 0; i < MARTIAL_CLUB_REAP_PROPS; ++i)
	 {
		 m_props_index[propsId[i]] = i;
	 }

	 return 0;
}


int LogicMartialClubManager::FullMessage(unsigned uid, User::MartialClub* msg)
{
	vector<unsigned> vIndexs;
	map<unsigned, int> idxMap;
	DataMartialClubManager::Instance()->GetIndexs(uid, vIndexs);
	for(int i = 0; i < vIndexs.size(); ++i)
	{
		try
		{
			DBCMartialClubWrap club(vIndexs[i]);
			auto p = msg->add_club();
			idxMap[club.Obj().id] = i;
			club.FullMessage(p->mutable_clubinfo());
		}
		catch(const std::exception& e)
		{
			error_log("uid: %u, %s", uid, e.what());
			throw runtime_error("full_martial_message_error");
		}
	}

	vector<unsigned> vHeroIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(uid, vHeroIndexs);
	for(auto &index : vHeroIndexs)
	{
		try
		{
			DataMartialHero& data = DataMartialHeroManager::Instance()->GetDataByIndex(index);
			unsigned id = data.id / 10;
			if(idxMap.count(id) == 0)
				throw runtime_error("id_invalid");
			unsigned idx = idxMap[id];
			FullMessage(uid, data.id, msg->mutable_club(idx)->add_heroinfo());

		}
		catch(const std::exception& e)
		{
			error_log("uid: %u, %s", uid, e.what());
			throw runtime_error("full_martial_message_error");
		}
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoOpenMartialClubReq *req, ProtoMartialClub::ProtoOpenMartialClubResp* resp)
{
	//武馆是否开启
	unsigned grade = req->grade();
	if(!IsValidMartialGrade(grade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}
	if(DataMartialClubManager::Instance()->IsExistItem(uid, grade))
	{
		error_log("martial club already opend uid: %u", uid);
		throw runtime_error("martial_club_already_opend");
	}
	//判断玩家等级是否满足开馆条件
	DataBase& user = BaseManager::Instance()->Get(uid);
	auto& cfg = MartialClubCfgWarp().GetMartialClubByGrade(grade);
	//判断玩家等级
	if(user.level < cfg.unlocklevel())
	{
		error_log("user level no enough uid %u", uid);
		throw runtime_error("user_level_no_enough");
	}

	//开启武馆
	DataMartialClub& club = DataMartialClubManager::Instance()->GetData(uid, grade);

	if(cfg.rewards(0).levelupts() < club.win_count * MARTIAL_UP_LEVEL_TS_PER)
	{
		club.next_ts = Time::GetGlobalTime();
	}
	else
	{
		club.next_ts = Time::GetGlobalTime() + cfg.rewards(0).levelupts() - club.win_count * MARTIAL_UP_LEVEL_TS_PER;
	}

	club.level = 1;
	club.win_count = 0;
	int index = DataMartialClubManager::Instance()->GetIndex(uid, grade);
	DataMartialClubManager::Instance()->m_data->MarkChange(index);

	resp->set_nextts(club.next_ts);
	return R_SUCCESS;
}


int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetOwnerClubReq* req, ProtoMartialClub::ProtoGetOwnerClubResp* resp)
{
	unsigned grade = req->grade();

	vector<unsigned> vIndexs;
	DBCMartialClubWrap club(uid, grade);
	club.FullMessage(resp->mutable_info()->mutable_clubinfo());

	DataMartialHeroManager::Instance()->GetIndexs(uid, vIndexs);
	for(auto& index: vIndexs)
	{
		DataMartialHero &hero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(hero.id / 10 == grade)
		{
			try
			{
				FullMessage(uid, hero.id, resp->mutable_info()->add_heroinfo());
			}
			catch(const std::exception& e)
			{
				delete resp;
				error_log("uid: %u, %s", uid, e.what());
				return R_ERROR;
			}
		}
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetHeroReq* req)
{
	unsigned grade = req->grade();
	unsigned ownerUid = req->owneruid();

	if(!IsValidUid(ownerUid))
	{
		error_log("othuid invalid uid: %u", uid);
		throw runtime_error("othuid_invalid");
	}

	if(CMI->IsNeedConnectByUID(ownerUid))
	{
		ProtoMartialClub::ProtoCSGetHeroReq* msg = new ProtoMartialClub::ProtoCSGetHeroReq;
		msg->set_myuid(uid);
		msg->set_owneruid(ownerUid);
		msg->set_grade(grade);

		return ProtoManager::BattleConnectNoReplyByUID(ownerUid, msg);
	}

	OffUserSaveControl  offuserCtl(ownerUid);
	vector<unsigned> vIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(ownerUid, vIndexs);
	ProtoMartialClub::ProtoGetHeroResp* resp = new ProtoMartialClub::ProtoGetHeroResp;
	for(auto& index: vIndexs)
	{
		DataMartialHero &hero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(hero.id / 10 == grade)
		{
			try
			{
				hero.SetMessage(resp->add_hero());
			}
			catch(const std::exception& e)
			{
				delete resp;
				error_log("uid: %u, %s", uid, e.what());
				return R_ERROR;
			}
		}
	}

	return 	LMI->sendMsg(uid, resp) ? 0 : R_ERROR;
}


int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSGetHeroReq* req)
{
	unsigned myUid = req->owneruid();
	unsigned othUid = req->myuid();
	unsigned grade = req->grade();

	//加载玩家数据
	OffUserSaveControl  offuserCtl(myUid);

	vector<unsigned> vIndexs;
	DataMartialClubManager::Instance()->GetIndexs(myUid, vIndexs);

	ProtoMartialClub::ProtoCSGetHeroResp* resp = new ProtoMartialClub::ProtoCSGetHeroResp;
	for(auto& index: vIndexs)
	{
		DataMartialHero& data = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(data.id /10 == grade)
		{
			try
			{
				FullMessage(myUid, data.id, resp->add_hero());
			}
			catch(const std::exception& e)
			{
				delete resp;
				error_log("uid: %u, %s", myUid, e.what());
				return R_ERROR;
			}
		}
	}

	return LMI->sendMsg(othUid, resp) ? 0 : R_ERROR;
}


int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetPartTimeClubReq* req)
{
	vector<unsigned> vIndexs;
	DataDetachHeroManager::Instance()->GetIndexs(uid, vIndexs);
	map<unsigned, vector<DataDetachHero>> mapUser;

	ProtoMartialClub::ProtoGetPartTimeClubResp* resp = new ProtoMartialClub::ProtoGetPartTimeClubResp;
	for(auto& e : vIndexs)
	{
		DataDetachHero& hero = DataDetachHeroManager::Instance()->GetDataByIndex(e);
		if(hero.detach_uid == uid)
			continue;

		if(CMI->IsNeedConnectByUID(hero.detach_uid))
		{
			mapUser[hero.detach_uid].push_back(hero);
		}

		try
		{
			//加载玩家数据
			OffUserSaveControl  offuserCtl(hero.detach_uid);
			DataMartialClub& club = DataMartialClubManager::Instance()->GetData(hero.detach_uid, hero.detach_slot/10);
			auto p = resp->add_info();
			club.SetMessage(p->mutable_clubinfo());
			vector<unsigned> vIndexs;
			DataMartialHeroManager::Instance()->GetIndexs(hero.detach_uid, vIndexs);
			for(auto&index : vIndexs)
			{
				DataMartialHero&  data = DataMartialHeroManager::Instance()->GetDataByIndex(index);
				if(data.id /10 != hero.detach_slot/10)
					continue;
				FullMessage(hero.detach_uid, data.id, p->add_heroinfo());
			}
		}
		catch(const exception& e)
		{
			delete resp;
			error_log("get part time club error uid=%u: %s", uid, e.what());
			throw runtime_error("get_part_time_club_error");
		}
	}

	LMI->sendMsg(uid, resp);
	if(mapUser.size() == 0)
		return R_SUCCESS;

	for(auto& e1 : mapUser)
	{
		ProtoMartialClub::ProtoCSGetPartTimeClubReq* msg = new ProtoMartialClub::ProtoCSGetPartTimeClubReq;
		msg->set_myuid(uid);
		msg->set_othuid(e1.first);
		for(auto& e2 : e1.second)
		{
			auto p = msg->add_clubinfo();
			p->set_grade(e2.detach_slot/10);
			p->mutable_heroinfo()->set_coins(e2.detach_coins);
			p->mutable_heroinfo()->set_startts(e2.start_ts);
		}

		ProtoManager::BattleConnectNoReplyByUID(e1.first, msg);
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSGetPartTimeClubReq* req)
{
	unsigned myUid = req->othuid();
	//加载玩家数据
	OffUserSaveControl  offuserCtl(myUid);

	ProtoMartialClub::ProtoCSGetPartTimeClubResp* resp = new ProtoMartialClub::ProtoCSGetPartTimeClubResp;
	for(int i = 0; i < req->clubinfo_size(); ++i)
	{
		unsigned grade = req->clubinfo(i).grade();
		try
		{
			DataMartialClub& club = DataMartialClubManager::Instance()->GetData(myUid, grade);
			auto p = resp->add_info();
			club.SetMessage(p->mutable_clubinfo());
			vector<unsigned> vIndexs;
			DataMartialHeroManager::Instance()->GetIndexs(myUid, vIndexs);
			for(auto&index : vIndexs)
			{
				DataMartialHero&  data = DataMartialHeroManager::Instance()->GetDataByIndex(index);
				if(data.id / 10 != grade)
					continue;
				auto tmp = p->add_heroinfo();
				data.SetMessage(p->add_heroinfo());
				tmp->mutable_hero()->set_coins( req->clubinfo(i).heroinfo().coins());
				tmp->mutable_hero()->set_startts( req->clubinfo(i).heroinfo().startts());
			}
		}
		catch(const exception& e)
		{
			delete resp;
			error_log("get part time club error uid=%u : %s",myUid, e.what());
			throw runtime_error("get_part_time_club_error");
		}
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoSetHeroReq* req)
{
	unsigned grade = req->grade();
	//放置英雄的武馆所属的玩家id
	unsigned detachUid = req->detachuid();
	unsigned heroId = req->heroid();
	unsigned slot = req->slot();

	if(!IsValidUid(detachUid))
	{
		error_log("param error: %u", uid);
		throw runtime_error("param_error");
	}

	auto& cfg = MartialClubCfgWarp().GetMartialClubByGrade(grade);

	unsigned heroSize = cfg.capacity()+1;
	if(!IsValidMatialSlot(grade, heroSize, slot))
	{
		error_log("param error uid: %u, grade: %u, herosize: %u, slot: %u", uid, grade, heroSize, slot);
		throw runtime_error("param_error");
	}

	bool isExist = DataMartialHeroManager::Instance()->IsExistItem(detachUid, slot);
	if(isExist)
	{
		error_log("martial hero is exist uid: %u, slot: %u", uid, slot);
		throw runtime_error("martial_hero_is_exist");
	}


	if(CMI->IsNeedConnectByUID(detachUid))
	{
		ProtoMartialClub::ProtoCSSetHeroReq* msg = new ProtoMartialClub::ProtoCSSetHeroReq;
		try
		{
			msg->set_myuid(uid);
			msg->set_detachuid(detachUid);
			msg->set_grade(grade);
			msg->set_slot(slot);
			SetMessage(uid, heroId, msg->mutable_sethero());
		}
		catch(const exception& e)
		{
			delete msg;
			error_log("set hero error uid: %u", uid);
			throw runtime_error("set_hero_error");
		}

		return  ProtoManager::BattleConnectNoReplyByUID(detachUid, msg);
	}

	//加载玩家数据
	OffUserSaveControl offuserCtl(detachUid);

	if(!LogicMartialHeroManager::Instance()->IsValid(uid, detachUid, heroId, grade, slot))
	{
		error_log("set martial hero error uid: %u", uid);
		throw runtime_error("set_martial_hero_error");
	}

	//设置英雄
	int ret = LogicMartialHeroManager::Instance()->AddMartialHero(uid, detachUid, grade, req->heroid(), slot, "martial_hero");

	if(R_SUCCESS == ret)
	{
		unsigned incomeStartTs = 0;
		if(uid == detachUid)
		{
			DataMartialClub& club = DataMartialClubManager::Instance()->GetData(uid, grade);
			if(club.ini_income == 0)
			{
				//初始化收益
				club.income_start_ts = Time::GetGlobalTime();
				incomeStartTs = club.income_start_ts ;
				club.coin = cfg.rewards(0).reward().based().coin();
				auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
				auto& rewardCfg = cfg.rewards(0).reward();
				for(int i = 0; i < rewardCfg.props_size(); ++i)
				{
					unsigned idx = propIndex[rewardCfg.props(i).id()];
					club.props[idx] = rewardCfg.props(i).count();
				}
				club.ini_income = 1;
				int index = DataMartialClubManager::Instance()->GetIndex(uid, grade);
				DataMartialClubManager::Instance()->m_data->MarkChange(index);
			}
		}

		if(UserManager::Instance()->IsOnline(detachUid))
		{
			ProtoMartialClub::ProtoSetHeroResp* respOth = new ProtoMartialClub::ProtoSetHeroResp;
			try
			{
				SetMessage(uid, heroId, respOth->mutable_sethero());
				if(uid == detachUid)
					respOth->set_incomestartts(incomeStartTs);
			}
			catch(const exception& e)
			{
				delete respOth;
				error_log("set msg error uid: %u", uid);
				throw runtime_error("set msg erro");
			}

			LMI->sendMsg(detachUid, respOth);
		}

	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSSetHeroReq* req)
{
	unsigned myUid = req->detachuid();
	unsigned othUid = req->myuid();
	unsigned grade = req->grade();
	unsigned heroId = req->sethero().hero().heroid();
	unsigned slot	= req->slot();

	OffUserSaveControl offuserCtl(myUid);

	if(!LogicMartialHeroManager::Instance()->IsValid(othUid, myUid, heroId, grade, slot))
	{
		error_log("set martial hero error uid: %u", myUid);
		throw runtime_error("set_martial_hero_error");
	}

	bool isExist = DataMartialHeroManager::Instance()->IsExistItem(myUid, slot);
	if(isExist)
	{
		error_log("martial hero is exist uid: %u, heroid: %u", myUid, heroId);
		throw runtime_error("martial_hero_is_exist");
	}


	DataMartialHero& addHero = DataMartialHeroManager::Instance()->GetData(myUid, heroId);

	addHero.uid = myUid;
	addHero.id  = slot;
	addHero.owner_uid = othUid;
	addHero.club_grade = grade;

	memcpy(addHero.name, req->sethero().user().name().c_str(), sizeof(addHero.name));
	memcpy(addHero.fig, req->sethero().user().fig().c_str(), sizeof(addHero.fig));
	bool ret = DataMartialHeroManager::Instance()->UpdateItem(addHero);

	HERO_LOG("uid=%u,id=%u,act=%s, code=%s.ret=%d", myUid, addHero.id, "Add", "Martial_Hero", ret);

	if(UserManager::Instance()->IsOnline(myUid))
	{
		ProtoMartialClub::ProtoCSSetHeroResp* resp = new ProtoMartialClub::ProtoCSSetHeroResp;
		try
		{
			resp->mutable_sethero()->CopyFrom(req->sethero());
		}
		catch(const exception& e)
		{
			delete resp;
			error_log("set msg error uid: %u", myUid);
			throw runtime_error("set_msg_erro");
		}

		LMI->sendMsg(myUid, resp);
	}

	DBCMartialClubWrap data(myUid, grade);
	data.Obj().hero_size++;
	data.Obj().slots[slot%10-1] = 1;
	data.Save();

	ProtoMartialClub::ProtoCSSetHeroToBattleReq* battleReq = new ProtoMartialClub::ProtoCSSetHeroToBattleReq;
	battleReq->set_othuid(othUid);
	battleReq->set_heroid(heroId);
	battleReq->set_slot(slot);
	battleReq->set_level(data.Obj().level);
	battleReq->set_heronum(data.Obj().hero_size);

	return  ProtoManager::BattleConnectNoReplyByUID(othUid, battleReq);
}

int LogicMartialClubManager:: Process(ProtoMartialClub::ProtoCSSetHeroToBattleReq* req)
{
	unsigned othUid = req->othuid();
	unsigned heroId = req->heroid();
	unsigned slot 	= req->slot();

	//加载玩家数据
	OffUserSaveControl offuserCtl(othUid);

	//已经在武馆中的英雄
	DataDetachHero& hero = DataDetachHeroManager::Instance()->GetData(othUid, heroId);
	hero.Set(req->myuid(), req->level(), slot, req->heronum());

	DataDetachHeroManager::Instance()->UpdateItem(hero);
	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid , ProtoMartialClub::ProtoDelHeroReq* req)
{
	unsigned detachGrade = req->grade();
	unsigned heroId		 = req->heroid();
	unsigned slot		 = req->slot();

	unsigned heroSize = MartialClubCfgWarp().GetMartialClubByGrade(detachGrade).capacity()+1;
	if(!IsValidMatialSlot(detachGrade, heroSize, slot))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	bool isExist = DataMartialHeroManager::Instance()->IsExistItem(uid, slot);
	if(!isExist)
	{
		error_log("hero_not_exist uid: %u", uid);
		throw runtime_error("hero_not_exist");
	}

	//加载玩家数据
	unsigned ownerUid = DataMartialHeroManager::Instance()->GetData(uid, slot).owner_uid;
	OffUserSaveControl offuserCtl(ownerUid);
	if(!DataHeroManager::Instance()->IsExistItem(ownerUid, heroId))
	{
		error_log("hero_not_exist, uid: %u", uid);
		throw runtime_error("hero_not_exist");
	}
	DataDetachHeroManager::Instance()->DelItem(uid, heroId);
	DataMartialHeroManager::Instance()->DelItem(uid, slot);
	int idx = slot %10;

	DBCMartialClubWrap club(uid, detachGrade);
	club.Obj().slots[idx-1] = 0;
	club.Obj().hero_size--;
	club.Save();

	ProtoMartialClub::ProtoDelHeroResp* resp = new ProtoMartialClub::ProtoDelHeroResp;
	LogicManager::Instance()->sendMsg(uid, resp);

	if(CMI->IsNeedConnectByUID(ownerUid))
	{
		ProtoMartialClub::ProtoCSDelHeroReq* msg = new ProtoMartialClub::ProtoCSDelHeroReq;
		msg->set_heroid(heroId);
		msg->set_owneruid(ownerUid);
		return ProtoManager::BattleConnectNoReplyByUID(ownerUid, msg);
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSDelHeroReq* req)
{
	unsigned heroId = req->heroid();
	unsigned ownerUid = req->owneruid();

	OffUserSaveControl offuserCtl(ownerUid);

	if(!DataHeroManager::Instance()->IsExistItem(ownerUid, heroId))
	{
		error_log("hero_not_exist, uid: %u", ownerUid);
		throw runtime_error("hero_not_exist");
	}

	DataDetachHeroManager::Instance()->DelItem(ownerUid, heroId);

	return R_SUCCESS;
}



int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoDelParttimerReq* req)
{
	unsigned detachUid   = req->detachuid();
	unsigned detachGrade = req->grade();
	unsigned heroId		 = req->heroid();
	unsigned slot		 = req->slot();

	if(!IsValidUid(detachUid))
	{
		error_log("param error: %u", uid);
		throw runtime_error("param_error");
	}

	unsigned heroSize = MartialClubCfgWarp().GetMartialClubByGrade(detachGrade).capacity()+1;
	if(!IsValidMatialSlot(detachGrade, heroSize, slot))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	bool isExist = DataMartialHeroManager::Instance()->IsExistItem(detachUid, slot);
	if(!isExist)
	{
		error_log("hero_not_exist uid: %u", uid);
		throw runtime_error("hero_not_exist");
	}

	if(CMI->IsNeedConnectByUID(detachUid))
	{
		ProtoMartialClub::ProtoCSDelParttimerReq* msg = new ProtoMartialClub::ProtoCSDelParttimerReq;
		msg->set_myuid(uid);
		msg->set_detachuid(detachUid);
		msg->set_grade(detachGrade);
		msg->set_slot(slot);

		return ProtoManager::BattleConnectNoReplyByUID(detachUid, msg);
	}

	//加载玩家数据
	OffUserSaveControl offuserCtl(detachUid);

	DataMartialHeroManager::Instance()->DelItem(detachUid, slot);

	if(!DataHeroManager::Instance()->IsExistItem(uid, heroId))
	{
		error_log("hero_not_exist, uid: %u", uid);
		throw runtime_error("hero_not_exist");
	}

	DataDetachHeroManager::Instance()->DelItem(uid, heroId);
	int idx = slot %10;

	DBCMartialClubWrap club(detachUid, detachGrade);
	club.Obj().slots[idx-1] = 0;
	club.Obj().hero_size--;
	club.Save();


	if(UserManager::Instance()->IsOnline(detachUid))
	{
		ProtoMartialClub::ProtoCSDelParttimerResp *resp = new ProtoMartialClub::ProtoCSDelParttimerResp;
		LMI->sendMsg(detachUid, resp);
	}

	HERO_LOG("uid=%u,slot=%u,act=%s, code=%s", uid, slot, "Del", "delete_martial hero");

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSDelParttimerReq* req)
{
	unsigned myUid  = req->detachuid();
	unsigned othUid = req->myuid();
	unsigned grade	= req->grade();
	unsigned slot	= req->slot();
	unsigned heroId	= req->heroid();

	bool isExist = DataMartialHeroManager::Instance()->IsExistItem(myUid, slot);
	if(!isExist)
	{
		error_log("hero_not_exist uid: %u", myUid);
		throw runtime_error("hero_not_exist");
	}
	//加载玩家数据
	OffUserSaveControl offuserCtl(myUid);

	DataMartialHeroManager::Instance()->DelItem(myUid, slot);

	int idx = slot %10;
	DBCMartialClubWrap club(myUid, grade);
	club.Obj().slots[idx-1] = 0;
	club.Obj().hero_size--;
	club.Save();

	if(UserManager::Instance()->IsOnline(myUid))
	{
		ProtoMartialClub::ProtoCSDelParttimerResp *resp = new ProtoMartialClub::ProtoCSDelParttimerResp;
		LMI->sendMsg(myUid, resp);
	}

	HERO_LOG("uid=%u,slot=%u,act=%s, code=%s", myUid, slot, "Del", "delete_martial hero");


	ProtoMartialClub::ProtoCSDelParttimerToBattleReq* msg = new ProtoMartialClub::ProtoCSDelParttimerToBattleReq;
	msg->set_myuid(othUid);
	msg->set_heroid(heroId);

	return ProtoManager::BattleConnectNoReplyByUID(othUid, msg);

}


int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSDelParttimerToBattleReq* req)
{
	//加载玩家数据
	OffUserSaveControl offuserCtl(req->myuid());
	DataDetachHeroManager::Instance()->DelItem(req->myuid(), req->heroid());

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetInviteUserReq* req, ProtoMartialClub::ProtoGetInviteUserResp* resp)
{
	try
	{
		vector<unsigned> users;
		RefreshInviteUser(uid, users);
		auto info = resp->mutable_users();
		for(auto& uid : users)
		{
			auto p = info->Add();
			SetMessage(uid, p);
		}
	}
	catch(const exception& e)
	{
		error_log("get invite user error: uid: %u, %s", uid, e.what());
		throw runtime_error("get_invite_user_error");
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoInviteUserReq* req)
{
	unsigned othUid = req->othuid();
	unsigned grade = req->martialgrade();
	if(!IsValidMartialGrade(grade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	DataMartialClub& club = DataMartialClubManager::Instance()->GetData(uid, grade);
	unsigned size = MartialClubCfgWarp().GetMartialClubByGrade(grade).capacity();
	unsigned freeSlot = 0;
	for(int i = 1; i <= (int)size; ++i)
	{
		if(club.slots[i] == 0)
		{
			freeSlot = grade*10 + i +1;
			break;
		}
	}
	if(freeSlot == 0)
	{
		error_log("no free slot uid: %u", uid);
		throw runtime_error("no_free_slot");
	}

	DataBase& user = BaseManager::Instance()->Get(uid);

	if(CMI->IsNeedConnectByUID(othUid))
	{
		ProtoMartialClub::ProtoCSInviteUserReq* msg = new ProtoMartialClub::ProtoCSInviteUserReq;
		msg->set_myuid(uid);
		msg->set_othuid(othUid);
		msg->set_slot(freeSlot);
		msg->set_mylevel(user.level);
		msg->set_myfig(user.fig);
		msg->set_myname(user.name);
		msg->set_martialgrade(grade);
		return ProtoManager::BattleConnectNoReplyByUID(othUid, msg);
	}

	MartialClubItem postItem;
	postItem.type 	= e_Post_inviteUser;
	postItem.ts 	= Time::GetGlobalTime();
	postItem.grade  = grade;
	postItem.slot   = freeSlot;
	postItem.level  = user.level;
	postItem.uuid   = uid;
	memcpy(postItem.fig, user.fig, sizeof(postItem.fig));
	memcpy(postItem.name, user.name, sizeof(postItem.name));

	LogicPostManager::Instance()->AddPost(othUid, postItem);
	//给在线玩家发送邀请
	if(UserManager::Instance()->IsOnline(othUid))
	{
		ProtoNotify::PushInvitePost* msg = new ProtoNotify::PushInvitePost;
		postItem.SetMessage(msg->mutable_post());
		LMI->sendMsg(othUid, msg);
	}

	return R_SUCCESS;
}

int LogicMartialClubManager::Process(ProtoMartialClub::ProtoCSInviteUserReq* req)
{
	unsigned myUid = req->othuid();
	unsigned othUid = req->myuid();
	unsigned martialGrade = req->martialgrade();
	unsigned slot = req->slot();


	MartialClubItem postItem;
	postItem.uid 	= othUid;
	postItem.type 	= e_Post_inviteUser;
	postItem.ts 	= Time::GetGlobalTime();
	postItem.uuid   = othUid;
	postItem.grade  = martialGrade;
	postItem.slot   = slot;
	postItem.level   = req->mylevel();
	memcpy(postItem.fig, req->myfig().c_str(), sizeof(postItem.fig));
	memcpy(postItem.name, req->myname().c_str(), sizeof(postItem.name));

	LogicPostManager::Instance()->AddPost(myUid, postItem);

	if(UserManager::Instance()->IsOnline(myUid))
	{
		ProtoNotify::PushInvitePost* msg = new ProtoNotify::PushInvitePost;
		postItem.SetMessage(msg->mutable_post());
		return LMI->sendMsg(myUid, msg) ? 0 : R_ERROR;
	}

	return R_SUCCESS;
}


int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetIncomeReq* req, ProtoMartialClub::ProtoGetIncomeResp* resp)
{
	unsigned martialGrade = req->martialgrade();

	if(!IsValidMartialGrade(martialGrade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}
	if(!DataMartialClubManager::Instance()->IsExistItem(uid, martialGrade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	 DBCMartialClubWrap club(uid, martialGrade);

	 CommonGiftConfig::CommonModifyItem cfg;

	 cfg.mutable_based()->set_coin(club.Obj().coin);

	 for(auto & e: m_props_index)
	 {
		 auto p = cfg.add_props();
		 p->set_id(e.first);
		 p->set_count(club.Obj().props[e.second]);
	 }

	 club.Obj().coin = 0;
	 memset(club.Obj().props, 0 , sizeof(club.Obj().props));
	 club.Save();

	 LogicUserManager::Instance()->CommonProcess(uid, cfg, "get_martial_income", resp->mutable_commons());

	 return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetOtherIncomeReq* req)
{
	unsigned heroId = req->heroid();
	unsigned slot = req->slot();
	unsigned othUid = req->othuid();

	if(!IsValidUid(othUid))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	if(!DataHeroManager::Instance()->IsExistItem(uid, heroId))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	if(!DataMartialHeroManager::Instance()->IsExistItem(othUid, slot))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}
	DataDetachHero& detach = DataDetachHeroManager::Instance()->GetData(uid, heroId);
	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_coin(detach.detach_coins);



	ProtoMartialClub::ProtoGetOtherIncomeResp* resp = new ProtoMartialClub::ProtoGetOtherIncomeResp;
	LogicUserManager::Instance()->CommonProcess(uid, cfg, "get_other_martial_income", resp->mutable_commons());

	detach.detach_coins = 0;
	detach.start_ts = Time::GetGlobalTime();
	DataDetachHeroManager::Instance()->UpdateItem(detach);

	return LMI->sendMsg(uid, resp) ? 0 : R_ERROR;
}


int  LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoGetMartialClubReq* req, ProtoMartialClub::ProtoGetMartialClubResp* resp)
{

	vector<vector<DataMartialClub*>> club ;
	club.resize(4);
	//活跃武馆

	RecommandByVitality(uid, club[0]);

	//按星级推荐
	RecommandByGrade(uid, 1, club[1]);
	RecommandByGrade(uid, 2, club[2]);
	RecommandByGrade(uid, 3, club[3]);

	for(auto& e : club)
	{
		auto group = resp->add_group();
		for(auto v: e)
		{
			auto p = group->add_clubs();
			v->SetMessage(p->mutable_clubinfo());
			auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
			for(auto e : propIndex)
			{
				auto prop = p->mutable_clubinfo()->add_props();
				prop->set_id(e.first);
				prop->set_count(v->props[e.second]);
			}
		//	debug_log("------------------ recommend: uid: %u, martialgrade: %u, coins: %u -----------------", p->mutable_clubinfo()->uid(), p->mutable_clubinfo()->grade(), p->mutable_clubinfo()->coins());

			vector<unsigned> vHeroIndexs;
			DataMartialHeroManager::Instance()->GetIndexs(v->uid, vHeroIndexs);
			for(auto & index : vHeroIndexs)
			{
				DataMartialHero& hero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
				if(hero.id / 10 == v->id)
				{
					FullMessage(v->uid, hero.id, p->add_heroinfo());
				}
			}

		}
	}

	return R_SUCCESS;
}



int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoUpdateLevelReq* req, ProtoMartialClub::ProtoUpdateLevelResp* resp)
{
	unsigned grade = req->martialgrade();
	if(!IsValidMartialGrade(grade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	DBCMartialClubWrap club(uid, grade);
	if(Time::GetGlobalTime() < club.Obj().next_ts)
	{
		error_log("time not arrive uid: %u, ts: %u", uid, club.Obj().next_ts);
		throw runtime_error("time_not_arrive");
	}
	auto& cfg = MartialClubCfgWarp().GetMartialClubByGrade(grade);
	if(cfg.rewards(club.Obj().level).levelupts() < club.Obj().win_count * MARTIAL_UP_LEVEL_TS_PER)
	{
		club.Obj().next_ts = Time::GetGlobalTime();
	}
	else
	{
		club.Obj().next_ts = Time::GetGlobalTime() + cfg.rewards(0).levelupts() - club.Obj().win_count * MARTIAL_UP_LEVEL_TS_PER;
	}

	club.Obj().win_count = 0;
	club.Obj().level += 1;
	club.Save();

	resp->set_nextts(club.Obj().next_ts);
	return R_SUCCESS;
}

int LogicMartialClubManager::Process(unsigned uid, ProtoMartialClub::ProtoChangeNameReq* req)
{
	unsigned grade = req->grade();
	if(!IsValidMartialGrade(grade))
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	DBCMartialClubWrap club(uid, grade);
	memcpy(club.Obj().martial_name, req->name().c_str(), sizeof(club.Obj().martial_name));

	club.Save();

	return R_SUCCESS;
}


void LogicMartialClubManager::ALLMartialClubIncome(unsigned uid)
{
	//更新自己武馆收益
	vector<unsigned> vecIndexs;
	DataMartialClubManager::Instance()->GetIndexs(uid, vecIndexs);
	//每个武馆收益开始时戳和基础金币收益
	for(auto &e: vecIndexs)
	{
		DataMartialClub& club = DataMartialClubManager::Instance()->GetDataByIndex(e);
		SingleMartialClubIncome(uid, club.id);
	}

}


void LogicMartialClubManager::SingleMartialClubIncome(unsigned uid, unsigned grade)
{
	//更新武馆收益
	int index = DataMartialClubManager::Instance()->GetIndex(uid, grade);
	LogicMartialClubManager::Instance()->UpdateMartialClub(uid, index, Time::GetGlobalTime());

	//更新兼职武馆收益
	vector<unsigned> vIndexs;
	DataDetachHeroManager::Instance()->GetIndexs(uid, vIndexs);
	for(auto& index : vIndexs)
		LogicMartialClubManager::Instance()->UpdatePartTimeMartialClub(uid, index, Time::GetGlobalTime());
}

void LogicMartialClubManager::UpdateMartialClub(unsigned uid, unsigned index, unsigned endTs)
{
	DBCMartialClubWrap club(index);
	unsigned level = club.Obj().level;
	unsigned heroSize = club.Obj().hero_size;
	unsigned grade	= club.Obj().id;

	if(level < 1)
		return;
	if(heroSize == 0)
		return;
	unsigned startTs = club.Obj().income_start_ts;
	if(endTs < startTs)
	{
		error_log("param error uid : %u", uid);
		throw runtime_error("param_error");
	}

	unsigned gap = endTs - startTs;
	if(gap < 3600)
		return;
	if(gap > MARTIAL_CLUB_MAX_OFFLINE_TS)
		gap = MARTIAL_CLUB_MAX_OFFLINE_TS;

	MartialClubCfgWarp cfgWrap;
	auto& cfg = cfgWrap.GetMartialClubByGrade(grade).rewards(level-1);
	int baseCoin = cfg.reward().based().coin();
	unsigned baseMulti = cfgWrap.GetMartialClubByGrade(grade).multiple();
	if(DataMartialHeroManager::Instance()->IsExistItem(uid, grade*10+1))
		heroSize -= 1;
	unsigned multiple =(heroSize == 0 ? 1 : baseMulti * heroSize);
	club.Obj().coin += baseCoin * multiple * (gap / 3600);
	for(int i = 0; i < cfg.reward().props_size(); ++i)
	{
		auto propid = cfg.reward().props(i).id();
		int idx = m_props_index[propid];
		club.Obj().props[idx] += cfg.reward().props(i).count() * (gap /cfg.propsts());
	}
	//增加派遣英雄玩家收益
	club.Obj().income_start_ts = startTs + (gap / 3600) * 3600;
	club.Save();
}

void LogicMartialClubManager::UpdatePartTimeMartialClub(unsigned uid, unsigned index, unsigned endTs)
{
	DataDetachHero& hero = DataDetachHeroManager::Instance()->GetDataByIndex(index);
	if(hero.detach_uid == uid)
		return;

	unsigned startTs = hero.start_ts;

	unsigned heroNum = hero.hero_num;
	if(heroNum == 0)
	{
		error_log("logic error uid: %u", uid);
		throw runtime_error("logic_error");
	}
	if(endTs < startTs)
	{
		error_log("param error uid : %u", uid);
		throw runtime_error("param_error");
	}

	if(endTs - startTs < 3600)
		return;

	MartialClubCfgWarp cfgWrap;
	unsigned grade = hero.detach_slot/10;
	auto& cfg = cfgWrap.GetMartialClubByGrade(grade).rewards(hero.club_level-1);
	int baseCoin = cfg.reward().based().coin();
	unsigned baseMulti = cfgWrap.GetMartialClubByGrade(grade).multiple();
	heroNum -= 1;
	unsigned multiple =(heroNum == 0 ? 1 : baseMulti * heroNum);
	unsigned gap = endTs - startTs;
	if(gap > MARTIAL_CLUB_MAX_OFFLINE_TS)
		gap = MARTIAL_CLUB_MAX_OFFLINE_TS;

	hero.detach_coins += baseCoin * multiple * (gap / 3600);
	hero.start_ts = startTs + (gap / 3600) * 3600;

	DataDetachHeroManager::Instance()->UpdateItem(hero);
}

void LogicMartialClubManager::MartialOnlineIncome()
{
	vector<unsigned> onlineUser;
	UserManager::Instance()->GetOnlineUsers(onlineUser);

	for(auto& e : onlineUser)
		ALLMartialClubIncome(e);
}

void LogicMartialClubManager::MartialOfflineIncome(unsigned uid, unsigned offlineTs, unsigned loginTs)
{
	ALLMartialClubIncome(uid);
}




void LogicMartialClubManager::RefreshInviteUser(unsigned uid, vector<unsigned>& users)
{
	auto userMap = ResourceManager::Instance()->GetMap();
	//过滤掉自己
	if(userMap.count(uid) != 0)
		userMap.erase(uid);
	//优先选择在线玩家
	vector<unsigned> vecOnline;
	for(auto it = userMap.begin(); it != userMap.end();)
	{
		if(UMI->IsOnline(it->first))
		{
			vecOnline.push_back(it->first);
			userMap.erase(it++);
		}
		else
			it++;
	}


	SelectInviteUser(uid, vecOnline, users);
	if(users.size() == INVITE_USER_NUM)
		return;

	vector<unsigned> vecToday;
	for(auto it = userMap.begin(); it != userMap.end();)
	{
		if(Time::IsToday(LogicResourceManager::Instance()->Get(it->first).last_login_time))
		{
			vecToday.push_back(it->first);
			userMap.erase(it++);
		}
		else
			it++;
	}

	SelectInviteUser(uid, vecToday, users);

	//昨天登录过的
	if(users.size() == INVITE_USER_NUM)
		return;

	vector<unsigned> vecYesterday;
	for(auto it = userMap.begin(); it != userMap.end();)
	{
		if(Time::IsToday(LogicResourceManager::Instance()->Get(it->first).last_login_time + 86400))
		{
			vecYesterday.push_back(it->first);
			userMap.erase(it++);
		}
		else
			it++;
	}

	SelectInviteUser(uid, vecYesterday, users);

	if(users.size() == INVITE_USER_NUM)
		return;

	//在剩下的人中找
	vector<unsigned> vecLeft;
	for(auto& e : userMap)
	{
		vecLeft.push_back(e.first);
	}
	SelectInviteUser(uid, vecLeft, users);
}


void LogicMartialClubManager::SelectInviteUser(unsigned uid, vector<unsigned>& vecIn, vector<unsigned>& vecOut)
{
	if(vecOut.size() == INVITE_USER_NUM)
		return;
	unsigned left = INVITE_USER_NUM - vecOut.size();
	vector<int> res;
	LogicCommonUtil::GetRandoms(0, vecIn.size() - 1, left, res);
	for(auto& e: res)
	{
		if(vecOut.size() == INVITE_USER_NUM)
			return;
		vecOut.push_back(vecIn[e]);
	}
}

void LogicMartialClubManager::SetMessage(unsigned uid, unsigned heroId, ProtoMartialClub::MartialHeroInfo* msg)
{
	auto& rItem = LogicResourceManager::Instance()->Get(uid);
	msg->mutable_user()->set_uid(rItem.uid);
	msg->mutable_user()->set_level(rItem.level);
	msg->mutable_user()->set_fig(string(rItem.fig));
	msg->mutable_user()->set_name(string(rItem.name));

	if(!DataHeroManager::Instance()->IsExistItem(uid, heroId))
	{
		error_log("hero not exist, uid: %u, heroid: %u", uid, heroId);
		throw runtime_error("hero_not_exist");
	}

	DBCHeroWrap hero(uid, heroId);
	HeroAttr attr;
	hero.GetAttr(attr);
	msg->mutable_hero()->set_heroid(heroId);
}

void LogicMartialClubManager::SetMessage(unsigned uid, ProtoMartialClub::MartialClubUserInfo* msg)
{
	OffUserSaveControl offuserCtl(uid);
	auto& rItem = LogicResourceManager::Instance()->Get(uid);
	auto& gItem	= LogicUserGradeManager::Instance()->Get(uid);

	msg->set_uid(rItem.uid);
	msg->set_fig(string(rItem.fig));
	msg->set_name(string(rItem.name));
	msg->set_level(rItem.level);
	msg->set_grade(gItem.grade);

}


void LogicMartialClubManager::RecommandByVitality(unsigned uid, vector<DataMartialClub*>& club)
{
	auto& userMap = ResourceManager::Instance()->GetMap();

	map<unsigned, vector<DataMartialClub*>> mapToday;
	map<unsigned, vector<DataMartialClub*>> mapYesterDay;

	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		auto& item = LogicResourceManager::Instance()->Get(it.first);
		if(it.first != uid && Time::IsToday(item.ts))
		{
			vector<unsigned> vIndexs;
			DataMartialClubManager::Instance()->GetIndexs(it.first, vIndexs);
			for(auto & e : vIndexs)
			{
				DataMartialClub& data = DataMartialClubManager::Instance()->GetDataByIndex(e);
				mapToday[data.level].push_back(&data);
			}
		}
		else if(it.first != uid && Time::IsToday(item.ts + 86400))
		{
			vector<unsigned> vIndexs;
			DataMartialClubManager::Instance()->GetIndexs(it.first, vIndexs);
			for(auto & e : vIndexs)
			{
				DataMartialClub& data = DataMartialClubManager::Instance()->GetDataByIndex(e);
				mapYesterDay[data.level].push_back(&data);
			}
		}
	});

	for(auto & e : mapToday)
	{
		for(auto v : e.second)
		{
			if(club.size() == RCOMMANDE_PER_GROUP_NUM)
				return;
			club.push_back(v);
		}
	}

	for(auto & e : mapYesterDay)
	{
		for(auto v : e.second)
		{
			if(club.size() == RCOMMANDE_PER_GROUP_NUM)
				return;
			club.push_back(v);
		}
	}

}


void LogicMartialClubManager::RecommandByGrade(unsigned uid, unsigned grade, vector<DataMartialClub*>& club)
{
	auto& userMap = ResourceManager::Instance()->GetMap();
	map<unsigned, vector<DataMartialClub*>> mapGrade;

	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		auto& item = LogicResourceManager::Instance()->Get(it.first);
		if(it.first != uid && (Time::IsToday(item.ts) || Time::IsToday(item.ts + 86400)))
		{
			vector<unsigned> vIndexs;
			DataMartialClubManager::Instance()->GetIndexs(it.first, vIndexs);
			for(auto & e : vIndexs)
			{
				DataMartialClub& data = DataMartialClubManager::Instance()->GetDataByIndex(e);
				if(data.id == grade)
				{
					mapGrade[grade].push_back(&data);
					break;
				}
			}
		}
	});

	for(auto & e : mapGrade)
	{
		for(auto v : e.second)
		{
			if(club.size() == RCOMMANDE_PER_GROUP_NUM)
				return;
			club.push_back(v);
		}
	}
}


void LogicMartialClubManager::FullMessage(unsigned uid, unsigned id, ProtoMartialClub::MartialHeroInfo *msg)
{
	DataMartialHero& data = DataMartialHeroManager::Instance()->GetData(uid, id);
	data.SetMessage(msg);
	if(DataDetachHeroManager::Instance()->IsExistItem(data.owner_uid, data.heroid))
	{
		DataDetachHero& detach = DataDetachHeroManager::Instance()->GetData(data.owner_uid, data.heroid);
		msg->mutable_hero()->set_startts(detach.start_ts);
		msg->mutable_hero()->set_coins(detach.detach_coins);
	}
}


