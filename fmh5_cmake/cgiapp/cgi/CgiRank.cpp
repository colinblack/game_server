#include "LogicInc.h"

class CCgiRank : public CCgiBase
{
public:

	CCgiRank() : CCgiBase("Rank")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(Rank)

	int GetShopCoin(unsigned uid,Json::Value & data)
	{
		CDataShopSellCoin dbshop;
		vector<DataShopSellCoin>datashop;
		DataShopSellCoin shop;
		shop.uid = uid;
		datashop.push_back(shop);

		//获取时间戳
		unsigned cur_ts = Time::GetGlobalTime();
		struct tm ptm;
		time_t tm = cur_ts;
		localtime_r(&tm, &ptm);

		unsigned ret = dbshop.Get(datashop);
		if(ret == 0 && datashop[0].id != 0){//证明已取到数据
			//1.获取昨天起始时间戳
			unsigned lastdayts = cur_ts - ((ptm.tm_hour + 1 *24) * 3600 + ptm.tm_min * 60 + ptm.tm_sec);
			//2.获取前前天的时间戳
			unsigned sevendayts = cur_ts - ((ptm.tm_hour + 7 *24) * 3600 + ptm.tm_min * 60 + ptm.tm_sec);
			//3.获取前30天的时间戳
			unsigned thirtydayts = cur_ts - ((ptm.tm_hour + 30 *24) * 3600 + ptm.tm_min * 60 + ptm.tm_sec);

			//初始化
			data["lastdaycoin"] = 0;
			data["sevendaycoin"] = 0;
			data["thirtydaycoin"] = 0;

			//统计昨日收入金币
			for(int i = 0; i < datashop.size(); i++)
			{
				if(datashop[i].id == lastdayts)
				{
					data["lastdaycoin"] = datashop[i].value;
					break;
				}
			}

			//统计前七天收入金币
			for(int i = 0; i < datashop.size(); i++)
			{
				if(datashop[i].id >= sevendayts && datashop[i].id <= lastdayts)
				{
					data["sevendaycoin"] = data["sevendaycoin"].asUInt() + datashop[i].value;
				}
			}

			//统计前30天收入的金币
			for(int i = 0; i < datashop.size(); i++)
			{
				if(datashop[i].id >= thirtydayts && datashop[i].id <= lastdayts)
				{
					data["thirtydaycoin"] = data["thirtydaycoin"].asUInt() + datashop[i].value;
				}
			}
		}else {
			data["lastdaycoin"] = 0;
			data["sevendaycoin"] = 0;
			data["thirtydaycoin"] = 0;
		}

		return 0;
	}

	int Rank()
	{

		int ret1 = 0;
		string suid = CCGIIn::GetCGIStr("uid");
		vector<string> r;
		String::Split(suid, '_', r);
		CDataBase dbbase;
		DataBase database;
		m_jsonResult["uid"].resize(0);
		for(int i=0;i<r.size();i++)
		{
			unsigned uid = CTrans::STOI64(r[i]);

			if(!IsValidUid(uid))
			{
//				error_log("not a valid uid=%u", uid);
				continue;
			}
			//获取玩家商店金币收入统计
			Json::Value obj;
			GetShopCoin(uid,obj);

			//获取玩家信息
			database.uid = uid;
			ret1 = dbbase.Get(database);
			if(ret1 == 0)
			{
				obj["uid"] = database.uid;
				obj["level"] = database.level;
				obj["name"] = database.name;
				obj["fig"] = database.fig;
				obj["accthumbsup"]=database.accthumbsup;
				obj["prosperity"]=database.prosperity;
				m_jsonResult["uid"].append(obj);
			}
			else
				error_log("load base fail uid=%u ret1=%d", uid, ret1);
		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiRank)
