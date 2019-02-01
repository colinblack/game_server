/*
 * LogicMartialHeroManager.cpp
 *
 *  Created on: 2018年9月3日
 *      Author: colin
 */

#include "LogicMartialHeroManager.h"

DBCMartialHeroWrap::DBCMartialHeroWrap(unsigned index)
	: container_(DataMartialHeroManager::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{

}




DBCMartialHeroWrap::DBCMartialHeroWrap(unsigned uid, unsigned heroid)
	: container_(DataMartialHeroManager::Instance())
	, index_(container_->GetIndex(uid, heroid))
	, data_(container_->m_data->data[index_])
{

}

/*void DBCMartialHeroWrap::FullMessage(ProtoMartialClub::MartialHeroInfo* msg)
{
	data_.SetMessage(msg);
}*/

int LogicMartialHeroManager::Process(ProtoMartialClub::ProtoCSMartialHeroInfo* req)
{
	unsigned uid = req->uid();

	OffUserSaveControl  offuserCtl(uid);
	for(int i = 0; i < req->attr_size(); ++i)
	{
		DataMartialHero& martialHero = DataMartialHeroManager::Instance()->GetData(uid, req->attr(i).detachslot());
		martialHero.hp = req->attr(i).hp();
		martialHero.att = req->attr(i).att();
		martialHero.def = req->attr(i).def();
		martialHero.crit = req->attr(i).critstrike();
		martialHero.acrit = req->attr(i).critresist();
		martialHero.dodge = req->attr(i).dodge();
		martialHero.adodge = req->attr(i).hit();
		martialHero.critt = req->attr(i).critrate();
		martialHero.speed = req->attr(i).first();
		int index = DataMartialHeroManager::Instance()->GetIndex(uid, req->attr(i).detachslot());
		DataMartialHeroManager::Instance()->m_data->MarkChange(index);
	}

	return R_SUCCESS;

}


int LogicMartialHeroManager::AddMartialHero(unsigned uid, unsigned detachUid, unsigned grade, unsigned heroid,  unsigned slot, string reason)
{
	DataMartialHero& addHero = DataMartialHeroManager::Instance()->GetData(detachUid, slot);
	if(!DataHeroManager::Instance()->IsExistItem(uid, heroid))
	{
		error_log("hero not exist, uid: %u", uid);
		throw runtime_error("hero_not_exist");
	}

	DBCHeroWrap	hero(uid, heroid);

	HeroAttr attr;
	hero.GetAttr(attr);
	addHero.heroid = heroid;
	addHero.owner_uid = uid;
	addHero.club_grade = grade;

	LogicHeroManager::Instance()->GetHeroAttr(uid, heroid, addHero);

	DBCUserBaseWrap user(uid);
	addHero.owner_level = user.Obj().level;

	memcpy(addHero.fig, user.Obj().fig, sizeof(addHero.fig));
	memcpy(addHero.name, user.Obj().name, sizeof(addHero.name));
	memcpy(addHero.skill, hero.Obj().skill, sizeof(addHero.skill));

	bool ret = DataMartialHeroManager::Instance()->UpdateItem(addHero);


	DBCMartialClubWrap data(detachUid, grade);
	data.Obj().hero_size++;
	data.Obj().slots[slot%10-1] = 1;
	data.Save();

	//已经在武馆中的英雄
	DataDetachHero& detachHero = DataDetachHeroManager::Instance()->GetData(uid, heroid);
	detachHero.Set(detachUid, data.Obj().level, slot, data.Obj().hero_size);
	DataDetachHeroManager::Instance()->UpdateItem(detachHero);


	LogicMartialClubManager::Instance()->SingleMartialClubIncome(detachUid, grade);
	HERO_LOG("uid=%u,slot=%u,act=%s, code=%s, ret=%d", uid, slot, "Add", reason.c_str(), ret);

	return R_SUCCESS;
}

void LogicMartialHeroManager::UpdateMartialHeroInfo(unsigned uid)
{
	vector<unsigned> vIndexs;
	DataDetachHeroManager::Instance()->GetIndexs(uid, vIndexs);
	map<unsigned, vector<unsigned>> other;
	for(auto& e : vIndexs)
	{
		DataDetachHero& detachHero = DataDetachHeroManager::Instance()->GetDataByIndex(e);

		if(CMI->IsNeedConnectByUID(detachHero.detach_uid))
		{
			other[detachHero.detach_uid].push_back(detachHero.id);
			continue;
		}
		OffUserSaveControl  offuserCtl(detachHero.detach_uid);
		DataMartialHero& martialHero = DataMartialHeroManager::Instance()->GetData(detachHero.detach_uid, detachHero.detach_slot);
		LogicHeroManager::Instance()->GetHeroAttr(uid, detachHero.id, martialHero);

		DataHero& hero = DataHeroManager::Instance()->GetData(uid, detachHero.id);
		memcpy(martialHero.skill, hero.skill, sizeof(martialHero.skill));

		DataMartialHeroManager::Instance()->UpdateItem(martialHero);
	}

	for(auto& e1 : other)
	{
		ProtoMartialClub::ProtoCSMartialHeroInfo* msg = new ProtoMartialClub::ProtoCSMartialHeroInfo;
		msg->set_uid(e1.first);
		for(auto& e2 : e1.second)
		{
			DBCHeroWrap hero(uid, e2);
			auto p = msg->add_attr();
			DataDetachHero& detachHero = DataDetachHeroManager::Instance()->GetData(uid, e2);
			p->set_detachslot(detachHero.detach_slot);
			hero.FullMessage(p, 0);
		}
		ProtoManager::BattleConnectNoReplyByUID(e1.first, msg);
	}

}


bool LogicMartialHeroManager::IsValid(unsigned uid, unsigned setUid, unsigned heroId, unsigned grade, unsigned slot)
{
	//判断能否设置

	auto& cfg = MartialClubCfgWarp().GetMartialClubByGrade(grade);

	DataMartialClub& data = DataMartialClubManager::Instance()->GetData(setUid, grade);

	if(data.hero_size == cfg.capacity() + 1)
	{
		error_log("isvalid herosize:%u, capacity: %u", data.hero_size, cfg.capacity());
		return false;
	}

	if(slot % 10 == 1 && setUid != uid)
	{
		error_log("isvalid slot: %u, setUid: %u, uid: %u", slot, setUid, uid);
		return false;
	}

	if(!DataHeroManager::Instance()->IsExistItem(uid, heroId))
	{
		error_log("hero not exist, uid=%u, heroid=%u", uid, heroId);
		return false;
	}

	if(DataDetachHeroManager::Instance()->IsExistItem(uid, heroId))
	{
		error_log("hero is exist, uid=%u", uid);
		return false;
	}

	vector<unsigned> vIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(setUid, vIndexs);
	for(auto &e : vIndexs)
	{
		DataMartialHero& clubHero = DataMartialHeroManager::Instance()->GetDataByIndex(e);
		if(clubHero.id / 10 == grade && uid == clubHero.owner_uid)
		{
			error_log("isvalid uid: %u, owner_uid: %u", uid, clubHero.owner_uid);
			return false;
		}
	}

	return true;
}

/*
void LogicMartialHeroManager::FullMessage(unsigned uid, User::MartialHero* msg)
{
	vector<unsigned> vIndexs;
	DataMartialClubManager::Instance()->GetIndexs(uid, vIndexs);

	for(auto& index : vIndexs)
	{
		DataMartialHero& data = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		data.SetMessage(msg->add_heroinfo());
	}
}

*/


