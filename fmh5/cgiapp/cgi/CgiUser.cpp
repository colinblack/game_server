/*
 * CgiUser.cpp
 *
 *  Created on: 2018年4月19日
 *      Author: Ralf
 */



#include "LogicInc.h"

class CCgiUser : public CCgiBase
{
public:

	CCgiUser() : CCgiBase("User")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(User)

	int User()
	{

		int ret = 0;
		string suid = CCGIIn::GetCGIStr("uid");
		vector<string> r;
		String::Split(suid, '_', r);
		CDataBase dba;
		DataBase d;
		m_jsonResult["uid"].resize(0);
		for(int i=0;i<r.size();i++)
		{
			unsigned uid = CTrans::STOI64(r[i]);

			if(!IsValidUid(uid))
			{
//				error_log("not a valid uid=%u", uid);
				continue;
			}
			d.uid = uid;
			ret = dba.Get(d);
			if(ret == 0)
			{
				Json::Value obj;
				obj["folkUid"] = d.uid;
				obj["level"] = d.level;
				obj["name"] = d.name;
				obj["fig"] = d.fig;
				obj["blueInfo"] = d.blue_info;
				obj["isHaveMonthCard"] = (d.flag >> base_falg_id_is_have_month_card) & 1;
				obj["isHaveLifeCard"] = (d.flag >> base_falg_id_is_have_life_card) & 1;
				obj["vipLevel"] = d.viplevel;
				obj["lastLoginTime"] = d.last_login_time;
				obj["registerTime"] = d.register_time;
				m_jsonResult["uid"].append(obj);
			}
			else
				error_log("load base fail uid=%u ret=%d suid=%s", uid, ret,suid.c_str());
		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiUser)


