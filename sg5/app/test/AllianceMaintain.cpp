#include "LogicInc.h"

static int EmailToMembers(unsigned allianceId, int days);

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "Kernel init failed!" << endl;
		return 0;
	}
	Config::SetDomain(0);

	int ret;
	CLogicIdCtrl logicIdCtrl;
	uint64_t u64Id;
	ret = logicIdCtrl.GetCurrentId(KEY_ALLIANCE_ID_CTRL, u64Id);
	if(ret != 0)
	{
		printf("get alliance id fail %d\n", ret);
		return ret;
	}

	unsigned minAllianceId = ALLIANCE_ID_START;
	string serverid;
	unsigned zone;
	if (Config::GetValue(serverid, CONFIG_SERVER_ID))
	{
		Convert::StringToUInt(zone, serverid);
		minAllianceId = Config::GetAIDStart(zone);
	}

	string buffer;
	map<unsigned,int> lowPointAllianceList;
	ret = File::Read("./LowPointAlliance.dat", buffer);
	if (0 == ret)
	{
		Json::Value data;
		if (Json::FromString(data, buffer))
		{
			unsigned aid = 0;
			int times = 0;
			for (unsigned i=0; i<data.size(); ++i)
			{
				if (Json::GetUInt(data[i], "aid", aid))
				{
					if (!IsAllianceId(aid))
					{
						continue;
					}
					times = 0;
					Json::GetInt(data[i], "times", times);
					lowPointAllianceList[aid] = times;
				}
			}
		}
	}

	CDataAlliance dbAlliance;
	DataAlliance alliance;
	CLogicAlliance logicAlliance;
	unsigned allianceId = minAllianceId + 1;
	unsigned expenses = 0;
	string configBuffer;
	if (!Config::GetValue(configBuffer, CONFIG_ALLIANCE_EXPENSES))
	{
		cout << "Get config alliance_expenses failed!" << endl;
		return R_ERROR;
	}
	vector<string> config;
	CBasic::StringSplitTrim(configBuffer, ",", config);
	if (config.size() != 10)
	{
		cout << "config size is error,size=" << config.size() << endl;
		return R_ERROR;
	}
	vector<unsigned> allianceList;
	for(; allianceId <= (unsigned)u64Id; allianceId++)
	{
		ret = dbAlliance.GetAllianceLimit(allianceId, alliance);
		if(ret != 0)
		{
			continue;
		}
		if(alliance.status != AS_ACTIVE)
		{
			continue;
		}
		allianceList.push_back(allianceId);

		if (!Convert::StringToUInt(expenses, config[alliance.level - 1]))
		{
			continue;
		}

		if (alliance.curr_point < expenses)
		{
			if (lowPointAllianceList[alliance.alliance_id] <= 6)
			{
				lowPointAllianceList[alliance.alliance_id]++;
				EmailToMembers(alliance.alliance_id, 7 - lowPointAllianceList[alliance.alliance_id]);
			}
		}
		else
		{
			alliance.curr_point -= expenses;
			ret = dbAlliance.SetAllianceLimit(alliance);
			if (0 != ret)
			{
				cout << "SetAllianceLimit failed! aid=" << allianceId << endl;
				continue;
			}
			lowPointAllianceList[alliance.alliance_id] = 0;

			if(alliance.level >= 5)
				logicAlliance.SetR5(alliance.alliance_id);
		}
	}

	Json::Value wData = Json::Value(Json::arrayValue);
	for (vector<unsigned>::iterator aItr=allianceList.begin(); aItr!=allianceList.end(); ++aItr)
	{
		if (lowPointAllianceList[*aItr] >= 7)
		{
			cout << "alliance " << *aItr << " no enough point for seven dates." << endl;
			ret = logicAlliance.RemoveAlliance(*aItr);
			if (0 != ret)
			{
				cout << "remove alliance failed!aid=" << *aItr << endl;
			}
		}
		else if (lowPointAllianceList[*aItr] > 0)
		{
			Json::Value &tempData = wData[wData.size()];
			tempData["aid"] = *aItr;
			tempData["times"] = lowPointAllianceList[*aItr];
		}
	}

	buffer.clear();
	buffer = Json::ToString(wData);
	ret = File::Write("./LowPointAlliance.dat", buffer);
	if (0 != ret)
	{
		cout << "Write file failed!" << endl;
		return ret;
	}
	return 0;
}

static int EmailToMembers(unsigned allianceId, int days)
{
	Json::Value temp;
	temp["s"] = "AllianceMaintain";
	temp["days"] = days;
	temp["ts"] = Time::GetGlobalTime();
	int ret;
	DataEmail data;
	data.title = "AllianceMaintain";
	data.text = Json::ToString(temp);
	data.post_ts = Time::GetGlobalTime();
	data.attach_flag = 0;
	data.from_name = "";
	data.uid = UID_MIN;
	CDataUserBasic dbUserBasic;
	string name;
	CDataAllianceMember dbMember;
	vector<DataAllianceMember> members;
	CDataEmail dbEmail;
	ret = dbMember.GetMembers(allianceId, members);
	if (0 != ret)
	{
		cout << "EmailToMembers get members failed! aid=" << allianceId << ",ret=" << ret << endl;
		return ret;
	}

	CLogicEmail logicEmail;
	vector<uint64_t> vto_uid;

	for (vector<DataAllianceMember>::iterator itr=members.begin(); itr!=members.end(); ++itr)
	{
		vto_uid.push_back(itr->uid);
	}

	ret = logicEmail.AddEmail(data,vto_uid,true);
	if (0 != ret)
	{
		cout << "EmailToMembers AddEmail fail,alliance=" << allianceId << ",ret=" << ret << endl;
		return ret;
	}

	return 0;
}

