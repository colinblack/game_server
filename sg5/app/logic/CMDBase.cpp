/*
 * CMDBase.cpp
 *
 *  Created on: 2016-8-27
 *      Author: Administrator
 */

#include "CMDBase.h"
#include "LogicInc.h"
#include "RewardConfig.pb.h"

CCMDBase::CCMDBase():
_uid(0),
_lasttime(0),
_seqid(0),
_serverid(0),
_init(false),
_coins(0),
_cash(0),
_qle(0),
_yl(0),
_process_type(0),
_need_resource_log(false),
_gcbas_chg(0),
_gcbuy_chg(0),
_r1_chg(0),
_r2_chg(0),
_r3_chg(0),
_r4_chg(0),
_r5_chg(0),
_prosper_chg(0),
_bs_chg(0),
_qle_chg(0),
_exp_chg(0),
_yl_chg(0)
{
	_equip.clear();
	_hero.clear();
	_new_act.clear();
}

CCMDBase::~CCMDBase() {
}

int CCMDBase::Init(unsigned uid, unsigned lasttime, unsigned seqid)
{
	if (_init){
		return 0;
	}
	_uid = uid;
	_lasttime = lasttime;
	_seqid = seqid;
	CLogicUser logicUser;
	int ret = 0;
	ret = logicUser.GetUser(_uid, _user);
	if (ret){
		return ret;
	}
	return 0;
}
int CCMDBase::Check(void){
	if (IsBeingAttacked(_user.last_breath_time)){
		error_log("[being_attacked][uid=%u,last_breath_time=%u]",_user.uid,_user.last_breath_time);
		LOGIC_ERROR_RETURN_MSG("u_being_attacked");
	}
	if(_user.last_save_uid != _user.uid){
		error_log("[last_save_uid_mismatch][operator=%u,user_last_save_uid=%u]",_user.uid, _user.last_save_uid);
		LOGIC_ERROR_RETURN_MSG("last_save_uid_mismatch");
	}
	if (_lasttime != _user.last_save_time || _seqid != _user.lastseq + 1){
		error_log("[lasttime_mismatch][operator=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
			_user.uid, _lasttime, _user.last_save_time, _seqid, _user.lastseq);
		LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
	}
	_user.last_save_time = Time::GetGlobalTime();
	_lasttime = Time::GetGlobalTime();
	_user.lastseq = _seqid;
	return R_SUCCESS;
}
int CCMDBase::Save(void){
	int ret = 0;
	CLogicUser logicUser;
	ret = logicUser.SetUser(_uid, _user);
	if(ret){
		return ret;
	}
	return R_SUCCESS;
}
int CCMDBase::SaveNewAct(void)
{
	if (_new_act.empty()){
		return R_ERR_LOGIC;
	}
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(_uid, _new_act);
	if (ret){
		return ret;
	}
	return ret;
}
void CCMDBase::GetLastTimeAndSeq(Json::Value &result)
{
	result["lasttime"] = _lasttime;
	result["lastseq"] = _seqid;
	result["saveuserid"] = _uid;
}
void CCMDBase::ResourceLog(void)
{
	if (!_need_resource_log){
		return;
	}
	RESOURCE_LOG(
		"[save change][uid=%u,gcbaschg=%d,gcbase=%u,gcbuychg=%d,gcbuy=%u,r1chg=%d,r1=%u,r2chg=%d,r2=%u,r3chg=%d,r3=%u,r4chg=%d,r4=%u,r5chg=%d,r5=%u,addprosper=%d,prosper=%u,addbs=%d,bs=%u,qlechg=%d,qle=%d,expchg=%u,exp=%u,lvl=%u,ylchg=%u,ylres=%u,code=%s]",
		_uid, _gcbas_chg, _user.gcbase, _gcbuy_chg, _user.gcbuy, _r1_chg,
		_user.r1, _r2_chg, _user.r2, _r3_chg, _user.r3, _r4_chg, _user.r4, _r5_chg,
		_user.r5, _prosper_chg, _user.prosper, _bs_chg, _user.battle_spirits,
		_qle_chg,_qle,_exp_chg,_user.point,_user.level,_yl_chg,_yl,"");
}
int CCMDBase::ChangePay(int cash, int coins, const string &code)
{
	int ret = 0;
	CLogicPay logicPay;
	DataPay dataPay;
	Json::Value user_flag;
	Json::FromString(user_flag, _user.user_flag);
	bool bsave = false;
	ret = logicPay.ChangePay(_uid, cash, coins, dataPay, code, user_flag, bsave);
	if(ret){
		return ret;
	}
	if(bsave){
		_user.user_flag = Json::ToString(user_flag);
	}
	_coins = dataPay.coins;
	_cash = dataPay.cash;
	return 0;
}
int CCMDBase::ParseSimpleReward(const XMLActSimpleReward *p_arr, unsigned len, string &code, unsigned ats)
{
	int ret = 0;
	vector<ItemAdd> items;
	items.clear();
	vector<string> hero_ids;
	hero_ids.clear();
	vector<string> hero_codes;
	hero_codes.clear();
	int coins = 0;
	int cash = 0;
	Json::Value material = Json::Value(Json::arrayValue);
	material.resize(MAX_MATERIAL_TYPE);
	unsigned res1 = 0;
	unsigned res2 = 0;
	unsigned res3 = 0;
	unsigned prosper = 0;
	for(unsigned i=0; i<len; ++i){
		if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_EQUIP){
			if (p_arr[i].id == 0){
				continue;
			}
			items.push_back(ItemAdd(p_arr[i].id,p_arr[i].count,code,0,0,p_arr[i].xs?ats:0));
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_HERO){
			if (p_arr[i].id == 0){
				continue;
			}
			for(unsigned j=0; j<p_arr[i].count; ++j){
				hero_ids.push_back(CDataXML::Hero2Str(p_arr[i].id));
				hero_codes.push_back(code);
			}
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_GOLD){
			coins += p_arr[i].count;
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT1){
			ParseMaterial(material, 0, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT2){
			ParseMaterial(material, 1, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT3){
			ParseMaterial(material, 2, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT4){
			ParseMaterial(material, 3, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT5){
			ParseMaterial(material, 4, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT6){
			ParseMaterial(material, 5, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_MT7){
			ParseMaterial(material, 6, p_arr[i].count);
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_RES1){
			res1 += p_arr[i].count;
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_RES2){
			res2 += p_arr[i].count;
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_RES3){
			res3 += p_arr[i].count;
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_PROSPER){
			prosper += p_arr[i].count;
		}else if (p_arr[i].type == XML_ACT_SIMPLE_REWARD_TYPE_CASH){
			cash += p_arr[i].count;
		}
	}
	if (items.size() > 0){
		CLogicEquipment logicEquipment;
		ret = logicEquipment.AddItems(_uid, items, _equip, true);
		if (ret){
			return ret;
		}
	}
	if (hero_ids.size() > 0){
		CLogicHero logicHero;
		ret = logicHero.AddHeros(_uid, hero_ids, hero_codes, _hero);
		if (ret){
			return ret;
		}
	}
	coins = coins<0 ? 0 : coins;
	cash = cash<0 ? 0 : cash;
	if (coins>0 || cash>0){
		CLogicPay logicPay;
		DataPay dataPay;
		ret = logicPay.ChangePay(_uid, cash, coins, code, dataPay);
		if (ret){
			return ret;
		}
		_coins = dataPay.coins;
		_cash = dataPay.cash;
	}
	if (res1 > 0){
		_user.r1 += res1;
		_r1_chg = res1;
		_need_resource_log = true;
	}
	if (res2 > 0){
		_user.r2 += res2;
		_r2_chg = res2;
		_need_resource_log = true;
	}
	if (res3 > 0){
		_user.r3 += res3;
		_r3_chg = res3;
		_need_resource_log = true;
	}
	if (prosper > 0){
		_user.prosper += prosper;
		_prosper_chg = prosper;
		_need_resource_log = true;
	}
	CLogicUser logicUser;
	/*
	ret = logicUser.UpdateMaterial(_uid, material, _user.material);
	if (ret){
		return ret;
	}*/
	return 0;
}

int CCMDBase::ProvideCommonReward(const RewardConfig::RewardItemCfg & rewardcfg, const string & reason, unsigned endts)
{
	int ret = 0;
	vector<ItemAdd> equips;
	unsigned nowts = Time::GetGlobalTime();
	for (int i = 0; i < rewardcfg.equips_size(); ++i)
	{
		const RewardConfig::EquipItem& equipcfg = rewardcfg.equips(i);
		ItemAdd item(equipcfg.eqid(), equipcfg.c(), reason, equipcfg.ch(), equipcfg.q());
		if (equipcfg.has_ltime() && endts > nowts)
		{
			//限时道具
			item.ats = endts;
		}
		equips.push_back(item);
	}
	if (equips.size() > 0)
	{
		CLogicEquipment logicEquipment;
		ret = logicEquipment.AddItems(_uid, equips, _equip);
		if (ret)
		{
			return ret;
		}
	}
	//处理英雄
	vector<string> heros;
	vector<string> reasons;
	for (int i = 0; i < rewardcfg.heros_size(); ++i)
	{
		const RewardConfig::HeroItem& herocfg = rewardcfg.heros(i);
		for (int j = 0; j < herocfg.c(); ++j)
		{
			heros.push_back(herocfg.id());
			reasons.push_back(reason);
		}
	}
	//英雄
	if (heros.size() > 0)
	{
		CLogicHero logicHero;
		ret = logicHero.AddHeros(_uid, heros, reasons, _hero);
		if (ret)
		{
			return ret;
		}
	}
	//加资源
	unsigned rs[3] = { 0 };
	bool ischange = false;
	for (int i = 0; i < rewardcfg.res_size() && i < 3; ++i)
	{
		if (0 != rewardcfg.res(i))
		{
			ischange = true;
		}
		rs[i] = rewardcfg.res(i);
	}
	if (rs[0] > 0)
	{
		_user.r1 += rs[0];
		_r1_chg = rs[0];
		_need_resource_log = true;
	}
	if (rs[1] > 0)
	{
		_user.r2 += rs[1];
		_r2_chg = rs[1];
		_need_resource_log = true;
	}
	if (rs[2] > 0)
	{
		_user.r3 += rs[2];
		_r3_chg = rs[2];
		_need_resource_log = true;
	}
	//金币，钻石
	int coin = 0, cash = 0;
	if (rewardcfg.has_gold())
	{
		coin = rewardcfg.gold();
	}
	if (rewardcfg.has_diamond())
	{
		cash = rewardcfg.diamond();
	}
	if (coin > 0 || cash > 0)
	{
		CLogicPay logicPay;
		DataPay dataPay;
		ret = logicPay.ChangePay(_uid, cash, coin, reason, dataPay);
		if (ret)
		{
			return ret;
		}
		_coins = dataPay.coins;
		_cash = dataPay.cash;
	}
	return 0;
}

void CCMDBase::ParseMaterial(Json::Value &material, unsigned index, int count)
{
	if (index >= MAX_MATERIAL_TYPE){
		return;
	}
	if (material[index].isMember("d")){
		material[index]["d"] = material[0u]["d"].asInt() + count;
	}else{
		material[index]["d"] = count;
	}
}
