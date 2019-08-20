/*
 * DataShootPointRank.cpp
 *
 *  Created on: 2015-10-19
 *      Author: Administrator
 */

#include "DataRotaryTableDraw.h"
#include "LogicCmdUnits.h"

int CDataRotaryTableFeedBackDraw::Init(const string &path, semdat sem)
{
	if (m_init)
		return 0;

	if (path.empty())
	{
		return R_ERR_PARAM;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	string datapath = MainConfig::GetAllServerPath(path);
	if(!m_sh.CreateOrOpen(datapath.c_str(), sizeof(DataRotaryTableDraw), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[CreateOrOpen error][path=%s]", datapath.c_str());
		return R_ERR_DATA;
	}
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (!m_sh.HasInit())
	{
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	m_init = true;
	return 0;
}

int CDataRotaryTableDraw::Init(const string &path, semdat sem)
{
	if (m_init)
		return 0;

	if (path.empty())
	{
		return R_ERR_PARAM;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	string datapath = MainConfig::GetAllServerPath(path);
	if(!m_sh.CreateOrOpen(datapath.c_str(), sizeof(DataRotaryTableDraw), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[CreateOrOpen error][path=%s]", datapath.c_str());
		return R_ERR_DATA;
	}
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (!m_sh.HasInit())
	{
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	m_init = true;
	return 0;
}


int CDataRotaryTableFeedBackDraw::GetDrawInfo(unsigned version,Json::Value &result)
{
	//获取抽奖记录信息
	vector<DataRotaryTableDrawUser> list;
	vector<int> left;

	Init(CONFIG_ROTATY_FEEDBACKK_DATA);
	GetList(version,list,left);

	result["log"] = Json::Value(Json::arrayValue);
	result["log"].resize(list.size());
	for (unsigned i=0; i<list.size(); ++i)
	{
		result["log"][i]["name"] = list[i].name;
		result["log"][i]["itemid"] = list[i].itemid;
		result["log"][i]["itemcnt"] = list[i].itemcnt;
		result["log"][i]["itemtype"] = list[i].itemtype;
	}
	result["left"] = Json::Value(Json::arrayValue);
	result["left"].resize(left.size());
	for (unsigned i=0; i<left.size(); ++i)
	{
		result["left"][i] = left[i];
	}
	return 0;
}

int CDataRotaryTableFeedBackDraw::Draw(unsigned uid,unsigned version,Json::Value &result)
{
	
	//抽奖、并将抽奖信息添加更新至共享内存中
	DataRotaryTableDrawUser user;
	user.uid = uid;
	CDataUserBasic dbUserBasic;
	string name;
	int ret = dbUserBasic.GetUserName(uid, PT_TEST, name);
	if (0 == ret)
	{
		strncpy(user.name, name.c_str(), sizeof(user.name)-1);
	}
	vector<DataRotaryTableDrawUser> list;
	vector<int> left;
	unsigned type = 0, id = 0;

	Init(CONFIG_ROTATY_FEEDBACKK_DATA);
	AddUser(version, user, list, type, id, left);

	result["log"] = Json::Value(Json::arrayValue);
	result["log"].resize(list.size());
	for (unsigned i=0; i<list.size(); ++i)
	{
		result["log"][i]["name"] = list[i].name;
		result["log"][i]["itemid"] = list[i].itemid;
		result["log"][i]["itemcnt"] = list[i].itemcnt;
		result["log"][i]["itemtype"] = list[i].itemtype;
	}
	result["left"] = Json::Value(Json::arrayValue);
	result["left"].resize(left.size());
	for (unsigned i=0; i<left.size(); ++i)
	{
		result["left"][i] = left[i];
	}
	result["type"] = type;//用于表示物品从哪个物品库中发放物品
	result["id"] = id;

	//发放奖励
	BaseCmdUnit base(uid);
	if(result["type"].asUInt() == 2)
	{
		//随机物品已抽完、获取固定奖励配置、发放奖励
		const RewardConfig::RewardItemCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFeedbackFixedItemcfg();

		//发放奖励
		base.ProvideCommonReward(itemcfg, "RotaryTableRandomFeedbackReward", result);
	}else if(result["type"].asUInt() == 1)
	{
		//等概率随机
		int random  = result["id"].asUInt() - 1;
		const ConfigActivity::RotaryTableCfg & tempcfg = ActivityConfigWrap().GetRotaryTableFeedBackItemcfg(random);

		ConfigActivity::RotaryTableCfg  itemcfg;
		if(tempcfg.type() == 2)
		{
			for(int i = 0; i < tempcfg.reward().heros_size(); i++)
			{
				RewardConfig::HeroItem *hero = itemcfg.mutable_reward()->add_heros();
				string heroid = "H";
				heroid.append(tempcfg.reward().heros(i).id());
				hero->set_id(heroid);
				hero->set_c(tempcfg.reward().heros(i).c());
			}
			for(int i = 0; i < tempcfg.reward().equips_size(); i++)
			{
				RewardConfig::EquipItem *equip = itemcfg.mutable_reward()->add_equips();
				equip->set_eqid(itemcfg.reward().equips(i).eqid());
				equip->set_ch(itemcfg.reward().equips(i).c());
			}

			//发放奖励
			base.ProvideCommonReward(itemcfg.reward(), "RotaryTableRandomFeedbackReward", result);
		}
		else
		{
			//发放奖励
			base.ProvideCommonReward(tempcfg.reward(), "RotaryTableRandomFeedbackReward", result);
		}
	}
	return 0;
}

int CDataRotaryTableFeedBackDraw::GetList(unsigned version, vector<DataRotaryTableDrawUser> &list, vector<int> &left)
{
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (version != pdata->version)
	{
		memset(pdata->list, 0, sizeof(pdata->list));
		memset(pdata->numprize, 0, sizeof(pdata->numprize));

		//初始化numprize数据
		unsigned giftsize = ActivityConfigWrap().GetRotaryTableFeedBackItemSize();
		for(int i = 0; i < giftsize; i++)
		{
			const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFeedBackItemcfg(i);
			pdata->numprize[i] = itemcfg.count();
		}

		pdata->version = version;
		pdata->listsize = 0;
	}

	//获取用户抽奖信息
	for(int i = 0; i < pdata->listsize; i++)
	{
		list.push_back(pdata->list[i]);
	}
	//获取物品剩余信息
	for(int i = 0; i < ActivityConfigWrap().GetRotaryTableFeedBackItemSize(); i++)
	{
		left.push_back(pdata->numprize[i]);
	}
	return 0;
}

int CDataRotaryTableFeedBackDraw::AddUser(unsigned version, DataRotaryTableDrawUser& user, vector<DataRotaryTableDrawUser> &list, unsigned &type,unsigned &id,vector<int> &left)
{
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (version != pdata->version)
	{
		memset(pdata->list, 0, sizeof(pdata->list));
		memset(pdata->numprize, 0, sizeof(pdata->numprize));
		//初始化numprize数据
		unsigned giftsize = ActivityConfigWrap().GetRotaryTableFeedBackItemSize();
		for(int i = 0; i < giftsize; i++)
		{
			const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFeedBackItemcfg(i);
			pdata->numprize[i] = itemcfg.count();
		}
		pdata->version = version;
		pdata->listsize = 0;
	}

	//记录可随机的物品
	vector<unsigned>randomgift;//记录物品id
	vector<unsigned>weight;//用当前数量记录权重
	randomgift.clear();
	weight.clear();
	unsigned giftsize = ActivityConfigWrap().GetRotaryTableFeedBackItemSize();
	for(int i = 0; i < giftsize; i++)
	{
		const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFeedBackItemcfg(i);
		if(pdata->numprize[i]  != 0)
		{
			unsigned giftid = itemcfg.id();
			randomgift.push_back(giftid);
			weight.push_back(pdata->numprize[i]);
		}
	}

	if(randomgift.size() == 0)
	{
		//记录物品类型,2标识从固定物品库中发放物品
		type = 2;
	}
	else
	{
		//记录物品类型,2标识从随机物品库中发放物品
		type = 1;

		//等概率随机,id用于标识随机礼包
		int target = 0;
		TurnLuckTable(weight,weight.size(),target);
		id = randomgift[target];

		//----------更新共享内存中numprize的剩余数量(numprize中的索引对应活动配置中的id - 1)
		pdata->numprize[id - 1] = pdata->numprize[id - 1] - 1;

		//-----------更新共享内存中userdata数据

		//获取新添加的user数据
		DataRotaryTableDrawUser data;
		const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFeedBackItemcfg(id -1);
		if(itemcfg.type() == 1)
		{
			data.itemid =  itemcfg.reward().equips(0).eqid();
			data.itemtype = itemcfg.type();
			data.itemcnt = itemcfg.reward().equips(0).c();
		}
		else if(itemcfg.type() == 2)
		{
			data.itemid = CTrans::STOI(itemcfg.reward().heros(0).id());
			data.itemtype = itemcfg.type();
			data.itemcnt = itemcfg.reward().heros(0).c();
			//error_log("itemid=%s,itemid_u=%u",itemcfg.reward().heros(0).id().c_str(),data.itemid);
		}
		data.uid = user.uid;
		strcpy(data.name,user.name);

		//----------更新共享内存中抽奖的用户数
		if(pdata->listsize < ROTARYTABLE_LIST_USER_COUNT)
			pdata->listsize += 1;

		//将pdata->list末尾添加新数据
		if(pdata->listsize == ROTARYTABLE_LIST_USER_COUNT)
		{
			for(int i = 0; i < ROTARYTABLE_LIST_USER_COUNT - 1; i++)
			{
				pdata->list[i] = pdata->list[i + 1];
			}
			pdata->list[pdata->listsize - 1] = data;
		}
		else
		{
			pdata->list[pdata->listsize - 1] = data;
		}

	}

	//获取用户抽奖信息
	for(int i = 0; i < pdata->listsize; i++)
	{
			list.push_back(pdata->list[i]);
	}
	//获取物品剩余信息
	for(int i = 0; i < giftsize; i++)
	{
		left.push_back(pdata->numprize[i]);
	}

	return 0;
}

int CDataRotaryTableFeedBackDraw::TurnLuckTable(vector<unsigned> & prates, int len, int & target)
{
	//获得概率总和
	int max = 0, last = 0;

	for(int i = 0 ; i < len; ++i)
	{
		max += prates[i];
	}

	int random = 0;

	//产生随机值
	random = Math::GetRandomInt(max);

	int j = 0;

	for (; j < len; ++j )
	{
		if (random < (last + prates[j]))
		{
			break;
		}

		last += prates[j];
	}

	target = j;

	return 0;
}

int CDataRotaryTableDraw::Draw(unsigned uid,unsigned costItemUd,unsigned version,Json::Value &result)
{
	//扣除抽奖道具
	CLogicEquipment logicEquipMent;
	const RewardConfig::RewardItemCfg & costcfg = ActivityConfigWrap().GetRotaryTableCostItemcfg();
	const int cost_equipid = costcfg.equips(0).eqid();
	int cost_count = costcfg.equips(0).c();
	int equd = costItemUd;
	int ret = logicEquipMent.UseEquipment(uid, cost_equipid, equd, cost_count, "RotaryTableCost");
	if (ret)
	{
		error_log("UseEquipment error. uid=%u,ud=%u,ret=%d", uid, equd, ret);
		throw runtime_error("use_eqiup_error");
	}

	//抽奖、并将抽奖信息添加更新至共享内存中
	DataRotaryTableDrawUser user;
	user.uid = uid;
	CDataUserBasic dbUserBasic;
	string name;
	ret = dbUserBasic.GetUserName(uid, PT_TEST, name);
	if (0 == ret)
	{
		strncpy(user.name, name.c_str(), sizeof(user.name)-1);
	}
	vector<DataRotaryTableDrawUser> list;
	vector<int> left;
	unsigned type = 0, id = 0;

	Init(CONFIG_ROTATYTABLEDRAW_DATA);
	AddUser(version, user, list, type, id, left);

	result["log"] = Json::Value(Json::arrayValue);
	result["log"].resize(list.size());
	for (unsigned i=0; i<list.size(); ++i)
	{
		result["log"][i]["name"] = list[i].name;
		result["log"][i]["itemid"] = list[i].itemid;
		result["log"][i]["itemcnt"] = list[i].itemcnt;
		result["log"][i]["itemtype"] = list[i].itemtype;
	}
	result["left"] = Json::Value(Json::arrayValue);
	result["left"].resize(left.size());
	for (unsigned i=0; i<left.size(); ++i)
	{
		result["left"][i] = left[i];
	}
	result["type"] = type;//用于表示物品从哪个物品库中发放物品
	result["id"] = id;


	//发放奖励
	BaseCmdUnit base(uid);
	if(result["type"].asUInt() == 2)
	{
		//随机物品已抽完、获取固定奖励配置、发放奖励
		const RewardConfig::RewardItemCfg & itemcfg = ActivityConfigWrap().GetRotaryTableFixedItemcfg();

		//发放奖励
		base.ProvideCommonReward(itemcfg, "RotaryTableRandomReward", result);
	}
	else if(result["type"].asUInt() == 1)
	{
		//等概率随机
		int random  = result["id"].asUInt() - 1;
		const ConfigActivity::RotaryTableCfg & tempcfg = ActivityConfigWrap().GetRotaryTableRandomItemcfg(random);


		ConfigActivity::RotaryTableCfg  itemcfg;
		if(tempcfg.type() == 2)
		{
			for(int i = 0; i < tempcfg.reward().heros_size(); i++)
			{
				RewardConfig::HeroItem *hero = itemcfg.mutable_reward()->add_heros();
				string heroid = "H";
				heroid.append(tempcfg.reward().heros(i).id());
				hero->set_id(heroid);
				hero->set_c(tempcfg.reward().heros(i).c());
			}
			for(int i = 0; i < tempcfg.reward().equips_size(); i++)
			{
				RewardConfig::EquipItem *equip = itemcfg.mutable_reward()->add_equips();
				equip->set_eqid(itemcfg.reward().equips(i).eqid());
				equip->set_ch(itemcfg.reward().equips(i).c());
			}

			//发放奖励
			base.ProvideCommonReward(itemcfg.reward(), "RotaryTableRandomReward", result);
		}
		else
		{
			//发放奖励
			base.ProvideCommonReward(tempcfg.reward(), "RotaryTableRandomReward", result);
		}
	}
	return 0;
}

int CDataRotaryTableDraw::GetDrawInfo(unsigned version,Json::Value &result)
{
	//获取抽奖记录信息
	vector<DataRotaryTableDrawUser> list;
	vector<int> left;

	Init(CONFIG_ROTATYTABLEDRAW_DATA);
	GetList(version,list,left);

	result["log"] = Json::Value(Json::arrayValue);
	result["log"].resize(list.size());
	for (unsigned i=0; i<list.size(); ++i)
	{
		result["log"][i]["name"] = list[i].name;
		result["log"][i]["itemid"] = list[i].itemid;
		result["log"][i]["itemcnt"] = list[i].itemcnt;
		result["log"][i]["itemtype"] = list[i].itemtype;
	}
	result["left"] = Json::Value(Json::arrayValue);
	result["left"].resize(left.size());
	for (unsigned i=0; i<left.size(); ++i)
	{
		result["left"][i] = left[i];
	}
	return 0;
}

int CDataRotaryTableDraw::GetList(unsigned version, vector<DataRotaryTableDrawUser> &list, vector<int> &left)
{
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (version != pdata->version)
	{
		memset(pdata->list, 0, sizeof(pdata->list));
		memset(pdata->numprize, 0, sizeof(pdata->numprize));

		//初始化numprize数据
		unsigned giftsize = ActivityConfigWrap().GetRotaryTableRandomCfgSize();
		for(int i = 0; i < giftsize; i++)
		{
			const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableRandomItemcfg(i);
			pdata->numprize[i] = itemcfg.count();
		}

		pdata->version = version;
		pdata->listsize = 0;
	}

	//获取用户抽奖信息
	for(int i = 0; i < pdata->listsize; i++)
	{
		list.push_back(pdata->list[i]);
	}
	//获取物品剩余信息
	for(int i = 0; i < ActivityConfigWrap().GetRotaryTableRandomCfgSize(); i++)
	{
		left.push_back(pdata->numprize[i]);
	}
	return 0;
}

int CDataRotaryTableDraw::AddUser(unsigned version, DataRotaryTableDrawUser& user, vector<DataRotaryTableDrawUser> &list, unsigned &type,unsigned &id,vector<int> &left)
{
	DataRotaryTableDraw *pdata = (DataRotaryTableDraw*)m_sh.GetAddress();
	if (pdata == NULL)
	{
		error_log("[GetAddress error]");
		return R_ERR_DATA;
	}
	CAutoLock lock(&m_sh,true);
	if (version != pdata->version)
	{
		memset(pdata->list, 0, sizeof(pdata->list));
		memset(pdata->numprize, 0, sizeof(pdata->numprize));
		//初始化numprize数据
		unsigned giftsize = ActivityConfigWrap().GetRotaryTableRandomCfgSize();
		for(int i = 0; i < giftsize; i++)
		{
			const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableRandomItemcfg(i);
			pdata->numprize[i] = itemcfg.count();
		}
		pdata->version = version;
		pdata->listsize = 0;
	}

	//记录可随机的物品
	vector<unsigned>randomgift;//记录物品id
	vector<unsigned>weight;//用当前数量记录权重
	randomgift.clear();
	weight.clear();
	unsigned giftsize = ActivityConfigWrap().GetRotaryTableRandomCfgSize();
	for(int i = 0; i < giftsize; i++)
	{
		const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableRandomItemcfg(i);
		if(pdata->numprize[i]  != 0)
		{
			unsigned giftid = itemcfg.id();
			randomgift.push_back(giftid);
			weight.push_back(pdata->numprize[i]);
		}
	}

	if(randomgift.size() == 0)
	{
		//记录物品类型,2标识从固定物品库中发放物品
		type = 2;
	}
	else
	{
		//记录物品类型,2标识从随机物品库中发放物品
		type = 1;

		//等概率随机,id用于标识随机礼包
		int target = 0;
		TurnLuckTable(weight,weight.size(),target);
		id = randomgift[target];

		//----------更新共享内存中numprize的剩余数量(numprize中的索引对应活动配置中的id - 1)
		pdata->numprize[id - 1] = pdata->numprize[id - 1] - 1;

		//-----------更新共享内存中userdata数据

		//获取新添加的user数据
		DataRotaryTableDrawUser data;
		const ConfigActivity::RotaryTableCfg & itemcfg = ActivityConfigWrap().GetRotaryTableRandomItemcfg(id -1);
		if(itemcfg.type() == 1)
		{
			data.itemid =  itemcfg.reward().equips(0).eqid();
			data.itemtype = itemcfg.type();
			data.itemcnt = itemcfg.reward().equips(0).c();
		}
		else if(itemcfg.type() == 2)
		{
			data.itemid = CTrans::STOI(itemcfg.reward().heros(0).id());
			data.itemtype = itemcfg.type();
			data.itemcnt = itemcfg.reward().heros(0).c();
			//error_log("itemid=%s,itemid_u=%u",itemcfg.reward().heros(0).id().c_str(),data.itemid);
		}
		data.uid = user.uid;
		strcpy(data.name,user.name);

		//----------更新共享内存中抽奖的用户数
		if(pdata->listsize < ROTARYTABLE_LIST_USER_COUNT)
			pdata->listsize += 1;

		//将pdata->list末尾添加新数据
		if(pdata->listsize == ROTARYTABLE_LIST_USER_COUNT)
		{
			for(int i = 0; i < ROTARYTABLE_LIST_USER_COUNT - 1; i++)
			{
				pdata->list[i] = pdata->list[i + 1];
			}
			pdata->list[pdata->listsize - 1] = data;
		}
		else
		{
			pdata->list[pdata->listsize - 1] = data;
		}

	}

	//获取用户抽奖信息
	for(int i = 0; i < pdata->listsize; i++)
	{
			list.push_back(pdata->list[i]);
	}
	//获取物品剩余信息
	for(int i = 0; i < giftsize; i++)
	{
		left.push_back(pdata->numprize[i]);
	}

	return 0;
}

int CDataRotaryTableDraw::TurnLuckTable(vector<unsigned> & prates, int len, int & target)
{
	//获得概率总和
	int max = 0, last = 0;

	for(int i = 0 ; i < len; ++i)
	{
		max += prates[i];
	}

	int random = 0;

	//产生随机值
	random = Math::GetRandomInt(max);

	int j = 0;

	for (; j < len; ++j )
	{
		if (random < (last + prates[j]))
		{
			break;
		}

		last += prates[j];
	}

	target = j;

	return 0;
}
