#include "LogicSecinc.h"
/* 2014901 Ralf change to save activity
int CLogicSecinc::AddSecinc(unsigned uid, unsigned eqid, unsigned amount)
{
	if (amount == 0) return 0;
	uint64_t tempid = 0;
	CLogicIdCtrl logicIdCtrl;
	int ret = logicIdCtrl.GetNextId(KEY_SECINC_ID_CTRL, tempid);
	if (ret != 0)
	{
		error_log("[GetNextId fail][ret=%d,uid=%u,eqid=%d,amount=%d]",
				ret, uid, eqid, amount);
		DB_ERROR_RETURN_MSG("get_secinc_id_fail");
	}
	DataSecinc secinc;
	secinc.uid = uid;
	secinc.sid = tempid;
	Json::Value data;
	data["sid"] = secinc.sid;
	data["d"]["t"] = 1;
	data["d"]["id"] = eqid;
	data["d"]["q"] = amount;
	Json::FastWriter writer;
	secinc.data = writer.write(data);
	CDataSecinc secincDb;
	ret = secincDb.AddSecinc(uid, secinc.sid, secinc.data);
	if (ret != 0)
	{
		error_log("[AddSecinc fail][ret=%d,uid=%u,eqid=%d,amount=%d]",
				ret, uid, eqid, amount);
		DB_ERROR_RETURN_MSG("add_secinc_fail");
	}
	return 0;
}

int CLogicSecinc::ProcessSecinc(unsigned uid, const Json::Value &data)
{
	if (!data.isArray())
	{
		error_log("[secinc type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("secinc_type_error");
	}
	CDataSecinc secincDb;
	unsigned size = data.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (!data[i].isIntegral())
		{
			error_log("[secinc data error][uid=%u,i=%u]",uid,i);
			DATA_ERROR_RETURN_MSG("secinc_data_error");
		}
		unsigned sid = data[i].asUInt();
		int ret = secincDb.RemoveSecinc(uid, sid);
		if (ret != 0)
		{
			error_log("[RemoveSecinc fail][uid=%u,sid=%u]",uid,sid);
			DB_ERROR_RETURN_MSG("remove_secinc_fail");
		}
	}
	return 0;
}
*/

int CLogicSecinc::GetSecinc(unsigned uid, Json::Value &data)
{
	CDataSecinc secincDb;
	vector<DataSecinc> datas;
	int ret = secincDb.GetSecinc(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetSecinc fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_secinc_fail");
	}
	data.resize(0);
	Json::Reader reader;
	int err = 0;
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value temp;
		if(!datas[i].data.empty() && reader.parse(datas[i].data, temp))
			data.append(temp);
		else
		{
			error_log("[parse secinc fail][uid=%u,newAct=%s]",uid,datas[i].data.c_str());
			++err;
		}
	}
	if(err)
	{
		DATA_ERROR_RETURN_MSG("parse_secinc_fail");
	}
	return 0;
}

int CLogicSecinc::SetSecinc(unsigned uid, Json::Value &data)
{
	if(!data.isArray())
	{
		error_log("[ReplaceSecinc data error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("replace_secinc_fail");
	}
	CDataSecinc secincDb;
	Json::FastWriter writer;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if(!data[i].isMember("id"))
		{
			error_log("[Secinc no id][uid=%u]", uid);
			DB_ERROR_RETURN_MSG("secinc_no_id");
		}

		std::string szData = writer.write(data[i]);
		if (szData.size() > 128)
		{
			error_log("uid: %u, id: %u, data_size: %d", uid, data[i]["id"].asUInt(), szData.size());
			DATA_ERROR_RETURN_MSG("save_secinc_data_too_long");
		}

		int ret = secincDb.ReplaceSecinc(uid, data[i]["id"].asUInt(), szData);
		if (ret)
		{
			error_log("[ReplaceSecinc fail][ret=%d,uid=%u]", ret, uid);
			DB_ERROR_RETURN_MSG("replace_secinc_fail");
		}
	}
	return 0;
}

int CLogicSecinc::GetSecinc(unsigned uid, unsigned sid, Json::Value &data)
{
	CDataSecinc secincDb;
	string str;
	int ret = secincDb.GetSecinc(uid, sid, str);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetSecinc fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_secinc_fail");
	}
	if(ret)
		return ret;
	Json::Reader reader;
	if(!str.empty() && !reader.parse(str, data))
	{
		error_log("[parse secinc fail][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("parse_secinc_fail");
	}
	return 0;
}

int CLogicSecinc::SetOneSecinc(unsigned uid, Json::Value &data)
{
	CDataSecinc secincDb;
	Json::FastWriter writer;
	if(!data.isMember("id"))
	{
		error_log("[Secinc no id][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("secinc_no_id");
	}

	std::string szData = writer.write(data);
	if (szData.size() > 128)
	{
		error_log("uid: %u, id: %u, data_size: %d, data: %s", uid, data["id"].asUInt(), szData.size(), szData.c_str());
		DATA_ERROR_RETURN_MSG("save_secinc_data_too_long");
	}

	int ret = secincDb.ReplaceSecinc(uid, data["id"].asUInt(), szData);
	if (ret)
	{
		error_log("[ReplaceSecinc fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("replace_secinc_fail");
	}
	return 0;
}

int CLogicSecinc::ImportSecinc(unsigned uid, Json::Value &data)
{
	int ret;
	CDataSecinc secincDb;
	Json::FastWriter writer;

	ret = secincDb.RemoveSecinc(uid);
	if(ret)
	{
		error_log("[RemoveSecinc error][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("RemoveSecinc_Fail");
	}

	if(!data.isArray())
		return 0;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if(!data[i].isMember("id"))
		{
			error_log("[Secinc no id][uid=%u]", uid);
			DB_ERROR_RETURN_MSG("secinc_no_id");
		}
		ret = secincDb.ReplaceSecinc(uid, data[i]["id"].asUInt(), writer.write(data[i]));
		if (ret)
		{
			error_log("[ReplaceSecinc fail][ret=%d,uid=%u]", ret, uid);
			DB_ERROR_RETURN_MSG("replace_secinc_fail");
		}
	}
	return 0;
}
