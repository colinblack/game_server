#include "LogicUpdates.h"

int CLogicUpdates::AddUpdates(unsigned uid, Json::Value &data, bool isother)
{
	if (!data.isArray())
	{
		error_log("[updates type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("data_updates_error");
	}
	CDataUpdates db;
	int ret = 0;
	Json::FastWriter writer;
	for (unsigned i = 0; i < data.size(); i++)
	{
		if (!data[i].isObject() || !data[i].isMember("ts")
				|| !data[i]["ts"].isIntegral())
		{
			error_log("[updates data error][uid=%u,i=%d]",uid,i);
			DATA_ERROR_RETURN_MSG("data_updates_error");
		}
		if(isother)
			data[i]["isother"] = 1;
		unsigned ts = data[i]["ts"].asUInt();
		ret = db.AddUpdates(uid, ts, writer.write(data[i]));
		if (ret != 0)
		{
			error_log("[AddUpdates fail][uid=%u,i=%d,ret=%d]",uid,i,ret);
			DATA_ERROR_RETURN_MSG("db_add_updates_fail");
		}
	}
	return 0;
}

int CLogicUpdates::GetUpdates(unsigned uid, Json::Value &data, bool onlyother)
{
	Json::Reader reader;
	CDataUpdates db;
	vector<DataUpdates> datas;
	int ret = db.GetUpdates(uid, datas);
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	if (ret != 0)
	{
		error_log("[GetUpdates fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_updates_fail");
	}
	if(onlyother)
	{
		for(vector<DataUpdates>::iterator it = datas.begin();it!=datas.end();)
		{
			Json::Value temp;
			if(!reader.parse((*it).data, temp) || !temp.isMember("isother") || temp["isother"] != 1)
				it = datas.erase(it);
			else
				++it;
		}
	}
	data.resize(datas.size());
	for (unsigned i = 0; i < datas.size(); i++)
	{
		if (!reader.parse(datas[i].data, data[i]))
		{
			error_log("[parse updates fail][uid=%u,i=%d]",uid,i);
			DATA_ERROR_RETURN_MSG("db_updates_data_error");
		}
	}
	return 0;
}

int CLogicUpdates::RemoveUpdatesBeforeTs(unsigned uid, unsigned ts)
{
	CDataUpdates db;
	int ret = db.RemoveUpdatesBeforeTs(uid, ts);
	if (ret != 0)
	{
		error_log("[RemoveUpdatesBeforeTs fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_rm_updates_fail");
	}
	return 0;
}
