/*
 * CgiAlliance.cpp
 *
 *  Created on: 2018年4月19日
 *      Author: Ralf
 */



#include "LogicInc.h"

class CCgiAlliance : public CCgiBase
{
public:

	CCgiAlliance() : CCgiBase("Alliance")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(Alliance)

	int Alliance()
	{
		int ret = 0;
		string said = CCGIIn::GetCGIStr("aid");
		m_jsonResult["alliance"].resize(0);
		vector<string> r;
		String::Split(said, '_', r);
		CDataAlliance dba;
		CDataAllianceMember dbm;
		for(int i=0;i<r.size();i++)
		{
			unsigned aid = CTrans::STOI64(r[i]);
			DataAlliance d;
			d.alliance_id = aid;
			ret = dba.Get(d);
			if(ret == 0)
			{
				vector<DataAllianceMember> m;
				DataAllianceMember k;
				k.alliance_id = aid;
				m.push_back(k);
				dbm.Get(m);
				Json::Value t;
				t["allianceId"] = d.alliance_id;
				t["name"] = d.name;
				t["flag"] = d.flag;
				t["applyType"] = d.apply_type;
				t["applyLevelLimit"] = d.apply_level_limit;
				t["memberCount"] = (unsigned)m.size();
				t["description"] = d.description;
				t["raceTotalPoint"] = d.race_total_point;
				m_jsonResult["alliance"].append(t);
			}
			else
				error_log("load alliance=%u ret=%d", aid, ret);
		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiAlliance)


