/*
 * RalfPart.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: 36397
 */

#include "LogicInc.h"
#include "LogicCMD.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);
	int ret = 0;

	{
		fstream fin("uid_wuhun");
		if (!fin.good()) {
			cout << "open uid_wuhun fail" << endl;
			goto NEXT;
		}
		CLogicEquipment eq;
		while (!fin.eof() && fin.good()) {
			unsigned uid = 0;
			fin >> uid;
			if(!IsValidUid(uid))
				continue;
			Json::Value data;
			ret = eq.GetEquipment(uid, uid, data);
			if(ret)
			{
				cout<<"load eq error,uid="<<uid<<endl;
				continue;
			}
			for(unsigned i=0;i<data.size();++i)
			{
				unsigned id = 0;
				Json::GetUInt(data[i], "id", id);
				if(id == 15002)
				{
					unsigned ud = 0;
					Json::GetUInt(data[i], "ud", ud);
					data[i]["count"] = 22925;
					ret = eq.Chg(uid, ud, data[i]);
					if(ret)
						cout<<"save eq error,uid="<<uid<<endl;
					else
						cout<<"eq success,uid="<<uid<<endl;
					break;
				}
			}
		}
	}
NEXT:
	{
		fstream fin("use_wuhun");
		if (!fin.good()) {
			cout << "open use_wuhun fail" << endl;
			goto OVER;
		}
		CLogicCMD cmd;
		CLogicUser us;
		Json::Reader reader;
		Json::FastWriter writer;
		while (!fin.eof() && fin.good()) {
			unsigned uid = 0;
			int count = 0;
			fin >> uid >> count;
			if(!IsValidUid(uid))
				continue;
			Json::Value tech;
			DataUser user;
			ret = us.GetUser(uid, user);
			if(ret)
			{
				cout<<"load user error,uid="<<uid<<endl;
				continue;
			}
			reader.parse(user.user_tech, tech);
			if(tech.isMember("part") && tech["part"].isArray() && tech["part"].size() == 10){
				string o, n;
				o = writer.write(tech["part"]);
				bool fix = true;
				while(count > 0){
					unsigned f = 0;
					for(unsigned i=0;i<tech["part"].size();++i)
					{
						if(count <= 0)
							break;
						unsigned p = tech["part"][i].asUInt();
						if(p > 100 || p == 0)
						{
							++f;
							//cout<<"p:"<<p<<",f="<<f<<endl;
							continue;
						}
						int cost;
						ret = cmd.CalcWeaponBySoulCost(uid, p, cost);
						if(ret)
						{
							++f;
							//cout<<"config p:"<<p<<",f="<<f<<endl;
							continue;
						}
						count -= cost;
						tech["part"][i] = p - 1;
					}
					if(f == 10)
					{
						cout<<"tech error,uid="<<uid<<",o="<<o<<endl;
						fix = false;
						break;
					}
				}
				if(fix)
				{
					user.user_tech = writer.write(tech);
					ret = us.SetUser(uid, user);
					if(ret)
						cout<<"save user error,uid="<<uid<<endl;
					else{
						n = writer.write(tech["part"]);
						cout<<"tech success,uid="<<uid<<",old="<<o<<",new="<<n<<endl;
					}
				}
			}
			else
				cout<<"tech size error,uid="<<uid<<endl;
		}
	}
OVER:
	{
		fstream fin("uid_eq");
		if (!fin.good()) {
			cout << "open uid_eq fail" << endl;
			goto END;
		}
		CLogicEquipment eq;
		while (!fin.eof() && fin.good()) {
			unsigned uid = 0;
			fin >> uid;
			if(!IsValidUid(uid))
				continue;

			Json::Value data;
			ret = eq.AddOneItem(uid, 15001, 22925, "uid_eq", data, false);
			if(ret)
				cout<<"add eq error,uid="<<uid<<endl;
			else
				cout<<"eq success,uid="<<uid<<endl;
		}
	}
END:
{
	fstream fin("uid_fix");
	if (!fin.good()) {
		cout << "open uid_fix fail" << endl;
		goto LAST;
	}
	Json::Reader reader;
	CLogicUser us;
	CLogicSecinc logicSecinc;
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		if(!IsValidUid(uid))
			continue;

		Json::Value newAct;
		Json::Value tech;
		DataUser user;
		ret = us.GetUser(uid, user);
		if(ret)
		{
			cout<<"load user error,uid="<<uid<<endl;
			continue;
		}
		reader.parse(user.user_tech, tech);
		if(!tech.isMember("part") || !tech["part"].isArray() || tech["part"].size() != 10)
		{
			cout<<"load tech error,uid="<<uid<<endl;
			continue;
		}
		ret = logicSecinc.GetSecinc(uid, NAT_PART_STONE, newAct);
		if(ret || !newAct.isMember("p") || !newAct["p"].isArray() || newAct["p"].size() != 10)
		{
			cout<<"load newAct error,uid="<<uid<<endl;
			continue;
		}
		bool f = false;
		for(unsigned i=0;i<10;++i)
		{
			if(tech["part"][i].asInt() < newAct["p"][i].asInt())
			{
				f = true;
				newAct["p"][i] = tech["part"][i];
			}
		}
		if(f)
		{
			ret = logicSecinc.SetOneSecinc(uid, newAct);
			if(ret)
			{
				cout<<"save newAct error,uid="<<uid<<endl;
				continue;
			}
		}
	}
}
LAST:
	return 0;
}
