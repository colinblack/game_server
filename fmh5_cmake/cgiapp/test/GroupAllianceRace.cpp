/*
 *GroupAllianceRace.cpp
 *
 *  Created on: 2016-10-10
 *      Author: City
 */

#include "LogicInc.h"
#include <fstream>
#include "Admin.pb.h"

map<uint32_t, Admin::SetAllianceRaceGroup *> mGroup;
unsigned nowTs = 0;
const int maxGroupSize = 50;	// 每50个组打包在一起
int sendGroup(unsigned aSrvId, Admin::SetAllianceRaceGroup * sGroup)
{
	if(sGroup == NULL)
	{
		cerr << "sGroup is NULL" << endl;
		return -1;
	}
	sGroup->set_ts(nowTs);
	//发送协议
	CSG17Packet packet;
	packet.cmd = PROTOCOL_ADMIN;
	packet.m_msg = sGroup;
	int ret = BattleSocket::Send(aSrvId, &packet);
	if(ret)
	{
		cout<<"send system error"<<endl;
		return ret;
	}
	cout << "send srvId=" << aSrvId << endl;
	return 0;
}
int addGroup(Admin::AllianceRaceGroup *pGroup)
{
	if(pGroup == NULL)
	{
		error_log("pGroup is NULL");
		return -1;
	}
	if(pGroup->item_size() == 0)
	{
		return 0;
	}
	set<uint32_t> mSrvId;
	for(int i = 0; i < pGroup->item_size(); ++i)	// 将每个联盟竞赛组数据发到一个联盟组所在的battle服务器
	{
		const Admin::AllianceRaceGroupItem& item = pGroup->item(i);
		uint32_t aSrvId = Config::GetZoneByAID(item.aid());
		mSrvId.insert(aSrvId);
	}
	for(set<uint32_t>::iterator iter = mSrvId.begin(); iter != mSrvId.end(); ++iter)
	{
		uint32_t aSrvId = *iter;

		if(mGroup.find(aSrvId) == mGroup.end())
		{
			mGroup[aSrvId] = new Admin::SetAllianceRaceGroup;
		}
		Admin::SetAllianceRaceGroup * sGroup = mGroup[aSrvId];
		if(sGroup == NULL)
		{
			cout << "sGroup is NULL" << endl;
			return -1;
		}
		sGroup->add_group()->CopyFrom(*pGroup);

		if(sGroup->group_size() >= maxGroupSize)	// 组的数量达到50就打包发送
		{
			if(sendGroup(aSrvId, sGroup) != 0)
			{
				cerr << "sendGroup fail" << endl;
				return -1;
			}
			mGroup.erase(aSrvId);
		}
	}

	return 0;
}
int main(int argc, char* argv[])
{
	if (!Kernel::Init())
	{
		cout << "init error";
		return 1;
	}

	if (argc != 3)
	{
		cout << "param error. usage: ./GroupAllianceRace ts file"<<endl;
		return 1;
	}
	nowTs = CTrans::STOI64(argv[1]);
	string filepath = argv[2];
	ifstream inputfile(filepath.c_str(), ios::in);

	if (!inputfile.is_open())
	{
		cout<<"file open error."<<filepath<<endl;
		return 1;
	}

	string itemstr;
	vector<string> vctItems;
	int line = 0;
	cout << "nowTs=" << nowTs << endl;
	Admin::AllianceRaceGroup *pGroup = new Admin::AllianceRaceGroup;
	if(pGroup == NULL)
	{
		error_log("pGroup is NULL");
		return 1;
	}
//	Admin::SetAllianceRaceGroup * sGroup = new Admin::SetAllianceRaceGroup;
	int groupId = -1;
	while(!inputfile.eof())
	{
		++line;
		//uid,id,count
		getline(inputfile, itemstr);

		if (itemstr.empty())
		{
			continue;
		}

		String::Split(itemstr, ' ', vctItems);

		if (vctItems.size() < 6)
		{
			cout<<"wrong data format in line:"<<line<<",data:"<<itemstr<<endl;
			continue;
		}

		int gid = CTrans::STOI(vctItems[0].c_str());
		unsigned aid	= CTrans::STOI64(vctItems[1].c_str());
		unsigned raceLevel = CTrans::STOI(vctItems[2].c_str());
		unsigned activeTs = CTrans::STOI64(vctItems[3].c_str());
		unsigned flag = CTrans::STOI(vctItems[4].c_str());
		unsigned count = CTrans::STOI(vctItems[5].c_str());
		if (!IsAllianceId(aid))
		{
			cout<<"wrong data value in line:"<<line<<",data:"<<itemstr<<endl;
			continue;
		}
		if(groupId != gid)	// 新的一组
		{
			if(addGroup(pGroup) != 0)	// 把上一组加到发送队列中
			{
				error_log("addGroup fail");
				return -1;
			}
			groupId = gid;
			pGroup->clear_item();
		}

		Admin::AllianceRaceGroupItem* pItem = pGroup->add_item();
		if(pItem == NULL)
		{
			cout<<"pItem is NULL"<< endl;
			return -1;
		}
		pItem->set_aid(aid);
		pItem->set_count(count);
	}
	if(addGroup(pGroup) != 0)	// 把上一组加到发送队列中
	{
		error_log("addGroup fail");
		return -1;
	}

	for(map<uint32_t, Admin::SetAllianceRaceGroup *>::iterator gIter = mGroup.begin(); gIter != mGroup.end(); ++gIter)
	{
		Admin::SetAllianceRaceGroup *sGroup = gIter->second;
		if(sGroup != NULL)
		{
			if(sendGroup(gIter->first, sGroup) != 0)
			{
				cerr << "sendGroup fail" << endl;
				return -1;
			}
		}
	}


	cout<<"batch success"<<endl;

	return 0;
}


