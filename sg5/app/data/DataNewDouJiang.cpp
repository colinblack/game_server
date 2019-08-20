#include "DataNewDouJiang.h"
#include "ConfigManager.h"
#include "LogicUser.h"
#include "LogicPay.h"
#include "LogicUpdates.h"
#include "LogicUnitWrap.h"
#include "LogicCmdBase.h"

CDataNewDouJiang::CDataNewDouJiang(string path)
	: DataBase(path)
{
	m_msg = new NewDouJiang::NewDouJiang();

}

int CDataNewDouJiang::Init()
{
	int ret = Parse();
	if(ret && ret != R_ERR_NO_DATA)
		return ret;

	m_data.Parse(*(NewDouJiang::NewDouJiang *)m_msg);

	CheckVersion();

	((NewDouJiang::NewDouJiang *)m_msg)->Clear();

	return 0;
}

void CDataNewDouJiang::CheckVersion()
{
	ActInfoConfig actconfig(CONFIG_chongbang_3);
	if(m_data.ver != actconfig.Version())
	{
		m_data.ver = actconfig.Version();
		m_data.rewarded = 0;
		m_data.user.clear();
	}
}

int CDataNewDouJiang::Save()
{
	m_data.Serialize((NewDouJiang::NewDouJiang *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//debug_log("%s",m_msg->DebugString().c_str());

	((NewDouJiang::NewDouJiang *)m_msg)->Clear();

	return 0;
}
int CDataNewDouJiang::Sig(int sig)
{
	return 0;
}

int CDataNewDouJiang::SetZhenRong(unsigned uid,const vector<unsigned>& p, Json::Value & result)
{
	if (p.size() != 9)
	{
		LOGIC_ERROR_RETURN_MSG("size");
	}
	if(!m_data.user.count(uid) || m_data.user[uid].uid == 0)
	{
		m_data.user[uid].uid = uid;
		m_data.user[uid].seq = 0;
	}
	m_data.user[uid].szheros.clear();
	for (vector<unsigned>::const_iterator it = p.begin();it!=p.end();++it) {
		m_data.user[uid].szheros.insert(*it);
	}
	m_data.user[uid].GetJson(result);
	return 0;
}

int CDataNewDouJiang::GetZhenRong(unsigned uid, Json::Value & result)
{
	if(!m_data.user.count(uid))
	{
		return 0;
	}
	for (set<unsigned>::iterator it = m_data.user[uid].szheros.begin();it!=m_data.user[uid].szheros.end();++it) {
		result["list"].append(*it);
	}
	return 0;
}

int CDataNewDouJiang::GetMyList(unsigned uid, Json::Value & result)
{
	if(!m_data.user.count(uid))
	{
		return 0;
	}
	CheckUserHerosTs(uid);
	m_data.user[uid].GetJson(result);
	return 0;
}

int CDataNewDouJiang::GetDuanWei(int score)
{
	if (score <= 2000)
		return 1;
	if (score <= 4000)
		return 2;
	if (score <= 6000)
		return 3;
	if (score <= 8000)
		return 4;
	return 5;
}

int CDataNewDouJiang::PiPei(unsigned uid, unsigned seq,Json::Value & result)
{
	if(!m_data.user.count(uid))
	{
		LOGIC_ERROR_RETURN_MSG("请重新登录或设置防守阵容");
	}

	if(seq != m_data.user[uid].seq)
	{
		error_log("[seq_error][uid=%u,seq=%d,m_data.user[uid].seq=%d]",uid,seq,m_data.user[uid].seq);
		return R_ERR_PARAM;
	}

	result["seq"] = ++m_data.user[uid].seq;

	CheckUserHerosTs(uid);

	if (m_data.user[uid].numpp >= 20)
	{
		LOGIC_ERROR_RETURN_MSG("匹配次数超过今日上限");
	}

	int total_point = m_data.user[uid].pppoint+m_data.user[uid].zspoint+m_data.user[uid].fcpoint;
	unsigned duanwei_self = GetDuanWei(total_point);
	map<unsigned, vector<unsigned> > duanwei;
	for (map<unsigned, DataNewDouJiangUser>::iterator it = m_data.user.begin(); it!=m_data.user.end();++it) {
		if (it->first != uid && !(m_data.user[it->first].flist.count(uid) && m_data.user[it->first].flist[uid].ts + NEW_DOUJIANG_ATTACK_MAX_TIME > Time::GetGlobalTime())) {
			duanwei[GetDuanWei((it->second).pppoint+(it->second).zspoint+(it->second).fcpoint)].push_back(it->first);
		}
	}
	for (unsigned i=duanwei_self;i>0;i--) {
		if (duanwei[i].size()) {
			result["pipeiuid"] = duanwei[i][Math::GetRandomInt(duanwei[i].size())];
			debug_log("uid=%u,pipeiuid=%u",uid,result["pipeiuid"].asUInt());
			return 0;
		}
	}


	result["pipeiuid"] = 0;
	return 0;
}

void CDataNewDouJiang::CheckUserHerosTs(unsigned uid)
{
	if (!Time::IsToday(m_data.user[uid].ts))
	{
		m_data.user[uid].ts = Time::GetGlobalTime();
		m_data.user[uid].ppheros.clear();
		m_data.user[uid].fcheros.clear();
		m_data.user[uid].zsheros.clear();
		m_data.user[uid].numpp = 0;
	}
}

int CDataNewDouJiang::StartAttack(unsigned uid, unsigned type, unsigned uid2, unsigned hud, unsigned seq, unsigned ud, Json::Value & result, unsigned fcts)
{
	if(!m_data.user.count(uid))
	{
		LOGIC_ERROR_RETURN_MSG("请重新登录或设置防守阵容");
	}
	if(uid2)
	{
		if (!m_data.user.count(uid2))
		{
			LOGIC_ERROR_RETURN_MSG("user2_not_exist");
		}

		if (m_data.user[uid2].flist.count(uid) && m_data.user[uid2].flist[uid].ts + NEW_DOUJIANG_ATTACK_MAX_TIME > Time::GetGlobalTime())
		{
			LOGIC_ERROR_RETURN_MSG("你与该玩家的战斗还未结束");
		}

		m_data.user[uid2].flist[uid].uid = uid;
		m_data.user[uid2].flist[uid].ts = Time::GetGlobalTime();
		m_data.user[uid2].flist[uid].type = type;
	}
	else if (type!=1)
	{
		LOGIC_ERROR_RETURN_MSG("不能追杀或复仇NPC");
	}

	if(seq != m_data.user[uid].seq)
	{
		error_log("[seq_error][uid=%u,seq=%d,m_data.user[uid].seq=%d]",uid,seq,m_data.user[uid].seq);
		return R_ERR_PARAM;
	}
	CheckUserHerosTs(uid);
	int ret;
	CLogicEquipment logicEquipment;
	set<unsigned> & hlist = type == 1 ? m_data.user[uid].ppheros : (type == 2 ? m_data.user[uid].fcheros : m_data.user[uid].zsheros);
	int & uidpoint = type == 1 ? m_data.user[uid].pppoint : (type == 2 ? m_data.user[uid].fcpoint : m_data.user[uid].zspoint);
	if (hlist.count(hud))
	{
		LOGIC_ERROR_RETURN_MSG("hud");
	}
	string reason = "StartAttack_"+CTrans::UTOS(type)+"_"+CTrans::UTOS(uid2);
	if (type == 1)
	{
		m_data.user[uid].numpp++;
	}
	if (type == 2)
	{
		bool find = false;
		for (list<DataNewDouJiangHistory>::iterator it = m_data.user[uid].his.begin(); it!=m_data.user[uid].his.end();++it)
		{
			if (!it->hasfc && it->uid == uid2 && it->ts==fcts && 0 == it->type)
			{
				find = true;
				it->hasfc = true;
			}
		}
		if (!find)
		{
			LOGIC_ERROR_RETURN_MSG("只能复仇防御匹配");
		}
		ret = logicEquipment.UseEquipment(uid, 23018, ud, 1, reason);
		if (ret)
			return ret;
	}
	if (type == 3)
	{
		ret = logicEquipment.UseEquipment(uid, 23017, ud, 1, reason);
		if (ret)
			return ret;
	}

	hlist.insert(hud);

	//限时目标奖励
	CLogicSecinc logicSecinc;
	Json::Value newAct;
	unsigned max_id = 0;
	ActInfoConfig actconfig(CONFIG_chongbang_3);
	ret = logicSecinc.GetSecinc(uid, NAT_xianshi_mubiao_3,newAct);
	if (R_ERR_NO_DATA == ret || newAct["v"].asUInt() != actconfig.Version())
	{
		CLogicChongBang logicChongBang;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		DataXMLXianShiMuBiao config;
		ret = dataXML->GetXianShiMuBiaoReward(config);
		if (ret)
		{
			return ret;
		}
		for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
			if (max_id < config.huodong[2].equip[j].id)
				max_id = config.huodong[2].equip[j].id;
		logicChongBang.ResetNewAct(newAct,NAT_xianshi_mubiao_3,actconfig.Version(),max_id);
	}
	newAct["a"][type][0u] = newAct["a"][type][0u].asUInt() + 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret) {
		error_log("SetOneSecinc error. uid=%u",uid);
	}

	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}

int CDataNewDouJiang::SetResult(unsigned uid, unsigned type, unsigned uid2, unsigned win, unsigned hud, unsigned seq, unsigned ud, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_chongbang_3);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity_is_over");
	}
	if(!m_data.user.count(uid))
	{
		LOGIC_ERROR_RETURN_MSG("请重新登录或设置防守阵容");
	}
	if(seq != m_data.user[uid].seq)
	{
		error_log("[seq_error][uid=%u,seq=%d,m_data.user[uid].seq=%d]",uid,seq,m_data.user[uid].seq);
		return R_ERR_PARAM;
	}
	if (win > 9)
	{
		PARAM_ERROR_RETURN_MSG("win");
	}
	if(uid2)
	{
		if (!m_data.user.count(uid2))
		{
			LOGIC_ERROR_RETURN_MSG("user2_not_exist");
		}

		if (!m_data.user[uid2].flist.count(uid) || m_data.user[uid2].flist[uid].type != type ||
				m_data.user[uid2].flist[uid].ts + NEW_DOUJIANG_ATTACK_MAX_TIME < Time::GetGlobalTime())
		{
			LOGIC_ERROR_RETURN_MSG("attack_mismatch");
		}

	}
	else if (type!=1)
	{
		LOGIC_ERROR_RETURN_MSG("不能追杀或复仇NPC");
	}
	CheckUserHerosTs(uid);
	int ret;
	//CLogicEquipment logicEquipment;
	int & uidpoint = type == 1 ? m_data.user[uid].pppoint : (type == 2 ? m_data.user[uid].fcpoint : m_data.user[uid].zspoint);
	/*
	set<unsigned> & hlist = type == 1 ? m_data.user[uid].ppheros : (type == 2 ? m_data.user[uid].fcheros : m_data.user[uid].zsheros);
	if (hlist.count(hud))
	{
		LOGIC_ERROR_RETURN_MSG("hud");
	}
	*/
	int add,minus;
	string reason = "SetResult_"+CTrans::UTOS(type)+"_"+CTrans::UTOS(uid2);
	if (type == 1)
	{
		add = 100;
		minus = 50;
	}
	if (type == 2)
	{
		add = 100;
		minus = 100;
		/*
		ret = logicEquipment.UseEquipment(uid, 6055, ud, 1, reason);
		if (ret)
			return ret;
		*/
	}
	if (type == 3)
	{
		add = 150;
		minus = 200;
		/*
		ret = logicEquipment.UseEquipment(uid, 6054, ud, 1, reason);
		if (ret)
			return ret;
		*/
	}
	if (Time::GetGlobalTime() > actconfig.EndTS() - 2*3600)
	{
		add = 0;
		minus = 0;
	}
	uidpoint += add*win;
	if (uid2 && m_data.user.count(uid2)) {
		int & uid2point = type == 1 ? m_data.user[uid2].pppoint : (type == 2 ? m_data.user[uid2].fcpoint : m_data.user[uid2].zspoint);
		uid2point -= minus*win;
	}

	//hlist.insert(hud);

	DataNewDouJiangHistory his;
	his.uid = uid;
	his.type = type-1;
	his.n = win;
	his.ts = Time::GetGlobalTime();
	his.point = -minus*win;
	his.hasfc = false;
	if(uid2)
	{
		//(m_data.user[uid2].his.size() >= 20)
			//m_data.user[uid2].his.pop_front();
		m_data.user[uid2].his.push_back(his);
	}
	his.uid = uid2;
	his.point = add*win;
	his.type += 3;
	//if(m_data.user[uid].his.size() >= 20)
	//	m_data.user[uid].his.pop_front();
	m_data.user[uid].his.push_back(his);

	//限时目标奖励
	CLogicSecinc logicSecinc;
	Json::Value newAct;
	unsigned max_id = 0;
	ret = logicSecinc.GetSecinc(uid, NAT_xianshi_mubiao_3,newAct);
	if (ret)//因为是战斗结束，所以不应该存在no_data
		return ret;
	/*
	if (R_ERR_NO_DATA == ret || newAct["v"].asUInt() != actconfig.Version())
	{
		CLogicChongBang logicChongBang;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		DataXMLXianShiMuBiao config;
		ret = dataXML->GetXianShiMuBiaoReward(config);
		if (ret)
		{
			return ret;
		}
		for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
			if (max_id < config.huodong[2].equip[j].id)
				max_id = config.huodong[2].equip[j].id;
		logicChongBang.ResetNewAct(newAct,NAT_xianshi_mubiao_3,actconfig.Version(),max_id);
	}
	*/
	newAct["a"][0u][0u] = newAct["a"][0u][0u].asUInt() + win;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret) {
		error_log("SetOneSecinc error. uid=%u",uid);
	}

	if (uid2)
	{
		Json::Value newAct_2;
		Json::FastWriter writer;
		ret = logicSecinc.GetSecinc(uid2, NAT_xianshi_mubiao_3,newAct_2);
		if (R_ERR_NO_DATA == ret || newAct_2["v"].asUInt() != actconfig.Version())
		{
			CLogicChongBang logicChongBang;
			CDataXML *dataXML = CDataXML::GetCDataXML();
			DataXMLXianShiMuBiao config;
			ret = dataXML->GetXianShiMuBiaoReward(config);
			if (ret)
			{
				return ret;
			}
			for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
				if (max_id < config.huodong[2].equip[j].id)
					max_id = config.huodong[2].equip[j].id;
			debug_log("max_id=%u",max_id);
			logicChongBang.ResetNewAct(newAct_2,NAT_xianshi_mubiao_3,actconfig.Version(),max_id);
		}
		newAct_2["a"][4u][0u] = newAct_2["a"][4u][0u].asUInt() + 1;
		ret = logicSecinc.SetOneSecinc(uid2, newAct_2);
		if (ret) {
			error_log("SetOneSecinc error. uid2=%u",uid2);
		}

		m_data.user[uid2].flist.erase(uid);
	}

	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}


struct DataNewDouJiangRank {
	unsigned uid;
	int point;
	DataNewDouJiangRank(unsigned tuid, int tpoint) :
			uid(tuid), point(tpoint) {
	}
};
bool cmp_DataNewDouJiangRank(const DataNewDouJiangRank & a, const DataNewDouJiangRank & b)
{
	if (a.point > b.point) return true;
	return false;
}


int CDataNewDouJiang::GetRankList(unsigned uid, Json::Value & result)
{
	vector<DataNewDouJiangRank> ranklist;
	for (map<unsigned, DataNewDouJiangUser>::iterator it = m_data.user.begin(); it!=m_data.user.end();++it) {
		ranklist.push_back(DataNewDouJiangRank(it->first, (it->second).pppoint+(it->second).zspoint+(it->second).fcpoint));
	}
	sort(ranklist.begin(),ranklist.end(),cmp_DataNewDouJiangRank);
	result["rank"] = Json::Value(Json::arrayValue);
	CLogicUserBasic logicUserBasic;
	CDataAlliance da;
	int i=0;

	ActInfoConfig actconfig(CONFIG_chongbang_3);
	bool reward = false;
	if (actconfig.IsActive() && Time::GetGlobalTime()>=actconfig.EndTS()-3600*2 && !m_data.rewarded) {
		reward = true;
		m_data.rewarded = true;
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLXianShiMuBiao config;
	int ret = dataXML->GetXianShiMuBiaoReward(config);
	if (ret)
	{
		return ret;
	}

	for (vector<DataNewDouJiangRank>::iterator iter=ranklist.begin(); iter!=ranklist.end(); ++iter)
	{
		//if (i < max_size)
		//{
			result["rank"][i]["uid"] = iter->uid;
			result["rank"][i]["point"] = iter->point;
			string name;
			logicUserBasic.GetName(iter->uid, name);
			result["rank"][i]["name"] = name;
		//}
		if (iter->uid == uid) {
			result["myrank"]["rank"] = i+1;
			result["myrank"]["point"] = iter->point;
		}
		if (i+1 <= 100 && reward)
		{
			if (i+1 == 1)
			{
				CLogicChongBang logicChongBang;
				logicChongBang.SetUser(3, iter->uid);
			}
			CLogicUpdates logicUpdates;
			for (unsigned loop = 0;loop < MAX_XIANSHI_MUBIAO_RANK_NUM;loop++)
				if (config.huodong[2].rank[loop].rank1 <= i+1 && i+1 <=config.huodong[2].rank[loop].rank2)
				{
					Json::Value equip;
					vector<GiftEquipItem> reward;
					string code = "chongbang_3_rank_"+CTrans::ITOS(i+1);
					for (int k=0;k<XML_XIANSHI_MUBIAO_RANK_REWARD_NUM;k++)
						reward.push_back(config.huodong[2].rank[loop].reward[k]);
					BaseCmdUnit basecmdUnit(iter->uid);
					basecmdUnit.AddGiftEquips(reward, code, equip);

					Json::Value updates;
					updates["s"] = "CHONGBANG3RANK";
					updates["uid"] = iter->uid;
					updates["ts"] = Time::GetGlobalTime();
					updates["rank"] = i+1;
					logicUpdates.AddUpdate(iter->uid,updates,true);
				}
		}
		i++;
	}
	return 0;
}

int CDataNewDouJiang::GetZhanBao(unsigned uid, Json::Value &result)
{
	if(!m_data.user.count(uid))
	{
		LOGIC_ERROR_RETURN_MSG("请重新登录或设置防守阵容");
	}

	result["his"].resize(0);
	for(list<DataNewDouJiangHistory>::iterator it=m_data.user[uid].his.begin();it!=m_data.user[uid].his.end();++it)
	{
		Json::Value t;
		it->GetJson(t);
		result["his"].append(t);
	}
	return 0;
}
