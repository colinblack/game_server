/*
 * ProcessOpportunityKnockForHank.cpp
 *
 *  Created on: 2016-7-22
 *      Author: zkw
 *      Purpose: hank need for activity bug OpportunityKnock
 */


#include "LogicInc.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"need file"<<endl;
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	//读文件
	int ret = 0;
	map<unsigned, vector<ItemAdd> > del_equips;
	del_equips.clear();
	ifstream fin(argv[1]);
	if (!fin.good())
	{
		cout<<"file error"<<endl;
		return 1;
	}
	while (!fin.eof() && fin.good())
	{
		unsigned temp_uid = 0, temp_eqid = 0, temp_chg = 0;
		fin >> temp_uid >> temp_eqid >> temp_chg;
		if (IS_UN_OVERLAY_ID(temp_eqid))
		{
			cout << "IS_UN_OVERLAY_ID "
				 << temp_uid << " "
				 << temp_eqid << " "
				 << temp_chg
				 << endl;
			continue;
		}
		if (temp_uid)
		{
			ItemAdd eqip;
			eqip.eqid = temp_eqid;
			eqip.count = temp_chg;
			eqip.ch = 0;
			eqip.q = 0;
			eqip.reason = "admin_del_for_opportunity_knock";
			del_equips[temp_uid].push_back(eqip);
		}
	}

	cout <<"uid  " << "eqid  "<<"max_del_count  " <<"have_count  "  <<"real_del_count" << endl;

	//遍历进行删除
	for(map<unsigned, vector<ItemAdd> >::iterator iter = del_equips.begin(); iter != del_equips.end(); ++iter)
	{
		//某uid 要删除 的所有装备
		unsigned temp_uid = iter->first;
		vector<ItemAdd> equip_items = iter->second;

		//取uid 档里 的所有装备
		CLogicEquipment logicEquip;
		Json::Value equip_data;
		ret = logicEquip.GetEquipment(temp_uid, temp_uid, equip_data);
		if(ret)
			return ret;

		for(vector<ItemAdd>::iterator it=equip_items.begin(); it != equip_items.end(); ++it)
		{
			for(int i=0; i<equip_data.size(); ++i)
			{
				if(equip_data[i]["id"].asUInt() == it->eqid)
				{
					unsigned del_count = (it->count <= equip_data[i]["count"].asUInt()) ? it->count : equip_data[i]["count"].asUInt();
					cout << temp_uid << " "
						 << equip_data[i]["id"].asUInt() << " "
						 << it->count << " "
						 << equip_data[i]["count"].asUInt() << " "
						 << del_count <<endl;
					it->count -= del_count;
					string reason = "admin_del_for_opportunity_knock";
					ret = logicEquip.UseEquipment(temp_uid, equip_data[i]["id"].asUInt(), equip_data[i]["ud"].asUInt(), del_count, reason);
					if(ret)
						return ret;
					break;
				}
			}
		}
	}

	cout << "ok" << endl;
	return 0;
}







