#include "LogicPropsManager.h"
#include "ServerInc.h"

int LogicPropsManager::NewUser(unsigned uid)
{
	DataItemManager::Instance()->Init(uid);

	//读取新手文档中的配置，进行新道具的放送
	const UserCfg::User& userCfg = UserCfgWrap().User();

	//发放物品
	DataCommon::CommonItemsCPP reward;
	LogicUserManager::Instance()->CommonProcess(uid, userCfg.initprops(), "NewUser", &reward);

	return 0;
}

int LogicPropsManager::CheckLogin(unsigned uid)
{
	DataItemManager::Instance()->Init(uid);

	return 0;
}

int LogicPropsManager::CostProps(unsigned uid, unsigned propsud, unsigned propsid, unsigned count, string reason, DataCommon::PropsAllChangeCPP * msg)
{
	//判断道具是否存在
	if (!DataItemManager::Instance()->IsExistItem(uid, propsud))
	{
		error_log("props's ud is not exist. uid=%u,ud=%u", uid, propsud);
		throw runtime_error("props_not_exist");
	}

	//获取道具
	DataItem & dataprops = DataItemManager::Instance()->GetData(uid, propsud);

	if (dataprops.props_id != propsid)
	{
		error_log("props's id is not same. uid=%u,ud=%u.needeqid=%u", uid, propsud, propsid);
		throw std::runtime_error("props_not_same");
	}

	//判断道具数量是否足够
	if (dataprops.item_cnt < count)
	{
		error_log("props not enough. uid=%u,ud=%u,count=%u", uid, propsud, count);
		throw std::runtime_error("props_not_enough");
	}

	dataprops.item_cnt -= count;
	string logtype;

	int restcount = dataprops.item_cnt;

	DataCommon::PropsChangeCPP* costpropsmsg = msg->add_propsitem();
	costpropsmsg->set_change(count);
	dataprops.SetMessage(costpropsmsg->mutable_props());

	if (0 == dataprops.item_cnt)  //道具已用完，删除
	{
		logtype = "Del";
		DataItemManager::Instance()->DelProps(dataprops);
	}
	else
	{
		logtype = "Sub";
		DataItemManager::Instance()->UpdateItem(dataprops);
	}

	PROPS_LOG("uid=%u,id=%u,propsid=%d,act=%s,chg=%d,count=%d,code=%s.",
			uid, propsud, propsid, logtype.c_str(), count, restcount, reason.c_str());

	return 0;
}

int LogicPropsManager::AddProps(unsigned uid, unsigned propsid, unsigned count, string reason, DataCommon::PropsAllChangeCPP * msg)
{
	//先判断是否可叠加
	if (IsAllowOverlay(propsid))
	{
		//可叠加道具
		DataItem additem;
		additem.uid = uid;
		additem.item_cnt = count;
		additem.props_id = propsid;

		AddPropsImpl(additem, reason, msg);
	}
	else
	{
		//不可叠加道具，批量添加
		for(unsigned i = 0; i < count; ++i)
		{
			DataItem additem;
			additem.uid = uid;
			additem.item_cnt = 1;
			additem.props_id = propsid;

			AddPropsImpl(additem, reason, msg);
		}
	}

	return 0;
}

int LogicPropsManager::AddPropsImpl(DataItem & props, string & reason, DataCommon::PropsAllChangeCPP * msg)
{
	unsigned uid = props.uid;
	unsigned propsid = props.props_id;

	if (IsAllowOverlay(propsid) && DataItemManager::Instance()->IsPropsExist(uid, propsid))
	{
		//道具可叠加，并且道具存在
		unsigned ud = DataItemManager::Instance()->GetPropsUd(uid, propsid);

		//获取道具
		DataItem & dataprops = DataItemManager::Instance()->GetData(uid, ud);

		//更新旧有道具
		dataprops.item_cnt += props.item_cnt;
		DataItemManager::Instance()->UpdateItem(dataprops);

		DataCommon::PropsChangeCPP* addpropsmsg = msg->add_propsitem();

		addpropsmsg->set_change(props.item_cnt);
		dataprops.SetMessage(addpropsmsg->mutable_props());

		PROPS_LOG("uid=%u,id=%u,propsid=%d,act=%s,chg=%d,count=%d,code=%s.",
				uid, dataprops.id, propsid, "Add", props.item_cnt, dataprops.item_cnt, reason.c_str());
	}
	else
	{
		//新增道具
		unsigned ud = DataItemManager::Instance()->GetUserNextUd(uid);
		props.id = ud;

		DataItemManager::Instance()->AddNewProps(props);

		DataCommon::PropsChangeCPP* addpropsmsg = msg->add_propsitem();

		addpropsmsg->set_change(props.item_cnt);
		props.SetMessage(addpropsmsg->mutable_props());

		PROPS_LOG("uid=%u,id=%u,propsid=%d,act=%s,chg=%d,count=%d,code=%s.",
				uid, props.id, propsid, "Add", props.item_cnt, props.item_cnt, reason.c_str());
	}

	return 0;
}

bool LogicPropsManager::IsAllowOverlay(unsigned propsid)
{
	//根据eqid获取配置文件中的叠加配置选项
	int limit = ItemCfgWrap().GetPropsItem(propsid).limitnum();

	return (limit > 1 ? true : false);
}

int LogicPropsManager::GetStorageUsedSpace(unsigned uid, unsigned type) const
{
	//遍历所有道具，根据location计算
	vector<unsigned> indexs;
	DataItemManager::Instance()->GetIndexs(uid, indexs);
	ItemCfgWrap itemcfgwrap;
	int count = 0;

	for(size_t i = 0; i < indexs.size(); ++i)
	{
		DataItem & item = DataItemManager::Instance()->GetDataByIndex(indexs[i]);

		const ConfigItem::PropItem & propscfg = itemcfgwrap.GetPropsItem(item.props_id);

		if (propscfg.location() == type)
		{
			//类型一致
			count += item.item_cnt;
		}
	}

	return count;
}


