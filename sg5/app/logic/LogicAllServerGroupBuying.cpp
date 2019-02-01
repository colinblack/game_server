#include "LogicAllServerGroupBuying.h"
#include "LogicCmdBase.h"

int CLogicAllServerGroupBuying::Load(unsigned uid, Json::Value& result)
{
	CheckActivity();

	unsigned version = GetConfigVersion();

	CDataAllServerGroupBuying* pgroup = DataWrap();
	//设置团购信息，发送给前端
	pgroup->SetGroupBuyingMsg(uid, result);

	result["version"] = version;

	return 0;
}

int CLogicAllServerGroupBuying::Join(unsigned uid, unsigned id, Json::Value& result)
{
	CheckActivity();

	//参数判断
	if(id < 1 || id > max_items_nums)
	{
		error_log("param error. uid=%u,id=%u", uid, id);
		throw runtime_error("param error");
	}

	//判断是否参加了团购
	CDataAllServerGroupBuying* pgroup = DataWrap();

	bool isjoin = pgroup->IsUserJoinGroup(id, uid);

	if (isjoin)
	{
		error_log("user already join the groupbuying. uid=%u,id=%u", uid, id);
		throw runtime_error("user_already_join");
	}

	int join_people = 0;  //参加团购的玩家个数

	try
	{
		DataGroupBuyingItem & groupItem = pgroup->GetGroupItem(id);
		join_people = groupItem.customers.size();
	}
	catch(runtime_error &e)
	{
		;
	}

	GroupBuyingConfigWrap groupbuywrap;
	const GroupBuyingConfig::GroupBuyingItem & itemcfg = groupbuywrap.GetGroupBuyingItemcfg(id);

	int oldstage = groupbuywrap.GetStageByCount(id, join_people);
	int nowstage = groupbuywrap.GetStageByCount(id, join_people + 1);

	//扣钻，根据最新的阶段读取
	int cash = itemcfg.people(nowstage).price();

	UserWrap userwrap(uid, true);

	char costreason[50] = {0};
	sprintf(costreason, "GroupBuying_Join_%u", id);

	userwrap.CostAsset(cash, 0, costreason, result);

	//发奖励
	BaseCmdUnit baseunit(uid);
	baseunit.ProvideCommonReward(itemcfg.reward(), "GroupBuying_Join", result);

	//将新加入的玩家添加到团购内存中
	pgroup->JoinGroupBuying(uid, id, nowstage);

	unsigned nowpeople = join_people + 1;

	//判断是否有返钻
	if (nowstage > oldstage)
	{
		DataGroupBuyingItem & groupItem = pgroup->GetGroupItem(id);

		for(map<unsigned int, DataGroupBuyingUser>::iterator giter = groupItem.customers.begin(); giter != groupItem.customers.end(); ++giter)
		{
			//给所有处于上一次阶段的人返钻
			if (giter->second.back_stage == oldstage)
			{
				//返钻
				unsigned interuid = giter->second.uid;

				//返回的价格应该是old与new之间的价格差
				if (itemcfg.people(nowstage).price() < itemcfg.people(oldstage).price())
				{
					int distance = itemcfg.people(oldstage).price() - itemcfg.people(nowstage).price();

					UserWrap userwrap(interuid, true);
					char szreason[50] = {0};
					sprintf(szreason, "GroupBuying_Back_%u_%d", id, nowstage);

					Json::Value temp;
					userwrap.AddCashCoin(distance, 0, szreason, temp);

					//更新返钻的用户的返钻阶段
					pgroup->UpdateBackStage(interuid, id, nowstage);

					//发邮件
					SendBackEmail(id, interuid, nowpeople, distance);
				}
			}
		}
	}

	pgroup->Save();

	//设置团购信息，发送给前端
	pgroup->SetGroupBuyingMsg(uid, result);

	return 0;
}

int CLogicAllServerGroupBuying::SendBackEmail(unsigned id, unsigned interuid, unsigned number, unsigned cash)
{
	Json::Value updates;

	updates["s"] = "GroupBuyingBack";
	updates["id"] = id;
	updates["num"] = number;
	updates["cash"] = cash;

	updates["ts"] = Time::GetGlobalTime();

	CLogicUpdates logicupdate;

	logicupdate.AddUpdate(interuid, updates, true);

	return 0;
}

int CLogicAllServerGroupBuying::CheckActivity()
{
	bool isactive = IsActivityOpen();

	if (!isactive)
	{
		error_log("activity not open");
		throw runtime_error("activity_not_open");
	}

	//判断版本号
	unsigned version = GetConfigVersion();

	CDataAllServerGroupBuying* pgroup = DataWrap();

	//获取所有团购活动的信息
	DataGroupBuing & datagroupbuy = pgroup->GetBuyingItems();

	if (datagroupbuy.version != version)
	{
		//更新数据
		pgroup->ResetGroupBuying(version);
	}

	return 0;
}

bool CLogicAllServerGroupBuying::IsActivityOpen()
{
	//判断活动是否开启，读取本地配置
	ActInfoConfig actcfg("allserver_groupbuy");

	return actcfg.IsActive();
}

int CLogicAllServerGroupBuying::GetConfigVersion()
{
	ActInfoConfig actcfg("allserver_groupbuy");

	return actcfg.Version();
}

CDataAllServerGroupBuying* CLogicAllServerGroupBuying::DataWrap()
{
	CDataAllServerGroupBuying* p = GetData();

	if (NULL == p)
	{
		throw std::runtime_error("Get_AllServer_Groupbuying_data_error");
	}

	return p;
}

