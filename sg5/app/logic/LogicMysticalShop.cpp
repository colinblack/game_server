/*
 * LogicMysticalShop.cpp
 *
 *  Created on: 2012-12-26
 *      Author: colin
 */
#include "LogicMysticalShop.h"
#include "LogicUnitWrap.h"

CLogicMysticalShop::CLogicMysticalShop()
{

}

CLogicMysticalShop::~CLogicMysticalShop()
{

}

CDataMysticalShop* CLogicMysticalShop::GetCDataMysticalShop()
{
	GET_MEM_DATA_SEM(CDataMysticalShop,CONFIG_MYSTICALSHOP_PATH,sem_mysticalshop,false)
	/*static CDataMysticalShop* pdata = NULL;
	if (!pdata)
	{
		pdata = new CDataMysticalShop();
		if (0 != pdata->Init(Config::GetValue(CONFIG_MYSTICALSHOP_PATH)))
		{
			delete pdata;
			pdata = NULL;
		}
	}
	return pdata;*/
}

int CLogicMysticalShop::InitMysticalShop()
{
	CDataMysticalShop *pdata = GetCDataMysticalShop();
	if(pdata == NULL)
	{
		return -1;
	}
	int ret = pdata->InitMysticalShop();
	return ret;
}

int CLogicMysticalShop::GetTopEquipNum(DataEquipItem dataEquipItem[],  int &equipNum)
{
	CDataMysticalShop *pdata = GetCDataMysticalShop();
	if(pdata == NULL)
	{
		return -1;
	}
	int ret = pdata->GetTopEquipNum(dataEquipItem, equipNum);
	if(0 != ret)
	{
		return ret;
	}
	return ret;

}

int CLogicMysticalShop::PayMysticalEquip(unsigned uid, string name, unsigned eid, Json::Value &result)
{
	CDataMysticalShop *pdata = GetCDataMysticalShop();
	if(pdata == NULL)
	{
		return -1;
	}
	unsigned index = 0;

	//判断是否已购买或者是否还有可购买物品
	int ret = pdata->PayMysticalEquip(uid, eid, index);  //只用于获取物品在池中的索引

	if (ret)
	{
		error_log("PayMysticalEquip error. uid=%u,eid=%u,ret=%d" , uid, eid, ret);
		return ret;
	}

	//扣钻
	string reason = "MysticalShop";
	DataEquipItem equipitem;

	try
	{
		DataEquipItem & dataequip = pdata->GetEquipItemByIndex(index);
		UserWrap userWrap(uid, false); //使用true,调用getuserlimit，反之，调用getuser

		userWrap.CostAsset(dataequip.price, 0, reason, result);

		equipitem = dataequip;
	}
	catch(exception &e)
	{
		error_log("exception happen. uid=%u, reason=%s", uid, e.what());
		return R_ERROR;
	}

	//发放物品
	char eqid[100] = {0};
	sprintf(eqid, "%u", equipitem.eid);

	if (eqid[0] == '3' || 0 == strncmp(eqid, "130", 3))
	{
		//英雄
		std::vector<std::string> vHeros;
		std::vector<std::string> vReasons;

		for(int i = 0; i < 1; ++i)
		{
			vHeros.push_back(CDataXML::Hero2Str(equipitem.eid));
			vReasons.push_back(reason);
		}

		CLogicHero logicHero;

		if (0 != logicHero.AddHeros(uid, vHeros, vReasons, result["heros"]))
		{
			error_log("add heros error. uid=%u", uid);
			LOGIC_ERROR_RETURN_MSG("add_heros_error");
		}
	}
	else
	{
		vector<ItemAdd> vItemAdds;
		ItemAdd item;
		item.eqid = equipitem.eid;
		item.reason = reason;
		item.count = 1;

		vItemAdds.push_back(item);
		CLogicEquipment logicEquipMent;

		ret = logicEquipMent.AddItems(uid, vItemAdds, result["equipments"], true);

		if(ret)
		{
			error_log("Add_Equip_error uid=%u， ret=%u", uid, ret);
			LOGIC_ERROR_RETURN_MSG("add_equipitems_failed");
		}
	}

	//记录黑市的购买
	ret = pdata->RecordMysticalEquip(uid, name, eid, index);

	return ret;
}

int CLogicMysticalShop::GetInfobuys(DataEquipSells dataEquipSells[], int &buyNums)
{
	CDataMysticalShop *pdata = GetCDataMysticalShop();
	if(pdata == NULL)
	{
		return -1;
	}
	int ret = pdata->GetInfobuys(dataEquipSells, buyNums);
	if(0 != ret)
	{
		return ret;
	}
	return ret;

}

