/*
 * CLogicEmail.cpp
 *
 *  Created on: 2012-7-26
 *      Author: Administrator
 */

#include "LogicEmail.h"
#include "AdAnalize.h"

#define EMAIL_MAX_NUM 100

CLogicEmail::CLogicEmail() {
	// TODO Auto-generated constructor stub

}

CLogicEmail::~CLogicEmail() {
	// TODO Auto-generated destructor stub


} /* namespace DBCache */
int CLogicEmail::GetInboxEmailList(unsigned uid, vector<DataEmail> &vEmail)
{
	int ret;
	CDataEmail dbEmail;
	ret = dbEmail.GetInboxEmailList(uid, vEmail);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			return 0;
		}
		error_log("[GetEmailList fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_email_list_fail");
	}
	vector<uint64_t> vEmail_Id;
	while(vEmail.size() > EMAIL_MAX_NUM)
	{
		vEmail_Id.push_back(vEmail[0].email_id);
		vEmail.erase(vEmail.begin());
	}
	if(!vEmail_Id.empty())
		dbEmail.DeleteEmails(uid, vEmail_Id);
	return 0;

}

int CLogicEmail::GetOutboxEmailList(unsigned uid, vector<DataEmail> &vEmail)
{
	int ret;
	CDataEmail dbEmail;
	ret = dbEmail.GetOutboxEmailList(uid, vEmail);
	if(ret != 0 ) // 无收件箱
	{
		if(ret == R_ERR_NO_DATA)
		{
			return 0;
		}
		error_log("[GetEmailList fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_email_list_fail");
	}
	vector<uint64_t> vEmail_Id;
	while(vEmail.size() > EMAIL_MAX_NUM)
	{
		vEmail_Id.push_back(vEmail[0].email_id);
		vEmail.erase(vEmail.begin());
	}
	if(!vEmail_Id.empty())
		dbEmail.DeleteEmails(uid, vEmail_Id);
	return 0;

}

int CLogicEmail::GetInboxEmailListJson(unsigned uid, vector<DataEmail> &vEmail ,Json::Value &value)
{

	int ret = 0;
	ret = GetInboxEmailList(uid, vEmail);
	if(ret != 0)
	{
		error_log("[GetEmailList fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_email_list_fail");
	}

	Json::Value data;
	Json::Reader reader;
	int iCount = vEmail.size();
	char attach_flag[2];
	memset(attach_flag,0x00,sizeof(attach_flag));
	for(int i = 0; i < iCount; i++)
	{

		value["emaillist"][i]["email_id"] = Convert::UInt64ToString(vEmail[i].email_id);
		value["emaillist"][i]["title"] = vEmail[i].title;
		value["emaillist"][i]["text"] = vEmail[i].text;
		value["emaillist"][i]["from_uid"] = vEmail[i].opposite_uid;
		value["emaillist"][i]["from_name"] = vEmail[i].from_name;
		value["emaillist"][i]["to_uid"] = vEmail[i].uid;
		value["emaillist"][i]["to_name"] = vEmail[i].to_name;
		value["emaillist"][i]["post_ts"] = vEmail[i].post_ts;
		value["emaillist"][i]["read_ts"] = vEmail[i].read_ts;
		snprintf(attach_flag,sizeof(attach_flag),"%d",vEmail[i].attach_flag);
		value["emaillist"][i]["attach_flag"] = string(attach_flag);

		if(!vEmail[i].attachments.empty() &&!reader.parse(vEmail[i].attachments,value["emaillist"][i]["attachments"]))
		{
			error_log("[parse fail][uid=%u,attachments=%s,i=%u]",uid,vEmail[i].attachments.c_str(),i);
		}

	}
	return 0;
}

int CLogicEmail::GetOutboxEmailListJson(unsigned uid, vector<DataEmail> &vEmail ,Json::Value &value)
{

	int ret = 0;
	unsigned time = Time::GetGlobalTime();
	vector<DataEmail>::iterator it ;
	Json::Value data;
	Json::Reader reader;
	ret = GetOutboxEmailList(uid, vEmail);
	if(ret != 0)
	{
		error_log("[GetEmailList fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_email_list_fail");
	}

	it = vEmail.begin();
	for(;it != vEmail.end();it++)
	{
		if( time - it->post_ts > GET_EMAIL_TIME_LIMIT )
		{
			it = vEmail.erase(it);
		}
	}
	int iCount = vEmail.size();
	char attach_flag[2];
	memset(attach_flag,0x00,sizeof(attach_flag));
	for(int i = 0; i < iCount; i++)
	{
		// 发件箱能查看最近两个月发送的邮件
		value["emaillist"][i]["email_id"] = Convert::UInt64ToString(vEmail[i].email_id);
		value["emaillist"][i]["title"] = vEmail[i].title;
		value["emaillist"][i]["text"] = vEmail[i].text;
		value["emaillist"][i]["from_uid"] = vEmail[i].uid;
		value["emaillist"][i]["from_name"] = vEmail[i].from_name;
		value["emaillist"][i]["to_uid"] = vEmail[i].opposite_uid;
		value["emaillist"][i]["to_name"] = vEmail[i].to_name;
		value["emaillist"][i]["post_ts"] = vEmail[i].post_ts;
		value["emaillist"][i]["read_ts"] = vEmail[i].read_ts;
		snprintf(attach_flag,sizeof(attach_flag),"%d",vEmail[i].attach_flag);
		value["emaillist"][i]["attach_flag"] = string(attach_flag);

		if(!vEmail[i].attachments.empty() && !reader.parse(vEmail[i].attachments,value["emaillist"][i]["attachments"]))
			error_log("[parse fail][uid=%u,attachments=%s,i=%u]",uid,vEmail[i].attachments.c_str(),i);
	}

	return 0;
}


int CLogicEmail::AddEmail(DataEmail &data,vector<uint64_t> &vto_uid,Json::Value &attachments,PlatformType platform)
{

	int ret = 0;
	CLogicUser logicUser;
	DataUser user;
	CLogicUserBasic logicUserBasic;
	DataUserBasic userBasic;
	vector<uint64_t>::const_iterator end_it = vto_uid.end();
	unsigned now = Time::GetGlobalTime();
	CDataEmail cDataEmail;
	DataEmail data2;
	data2 = data;
	data2.opposite_uid = data.uid;
	if(data.uid == ADMIN_UID)
	{
		userBasic.name="系统管理员";
		user.viplevel = 0;
	}else
	{
		logicUserBasic.GetUserBasicLimit(data.uid,platform,userBasic);
		logicUser.GetUserLimit(data.uid,user);

		if(user.level < 15 && user.viplevel < 3)
			return 0;
	}
	data.from_name = userBasic.name;
	data2.from_name = userBasic.name;
	data.post_flag = 2;   //发件
	data2.post_flag = 1;  //收件
	Json::Value temp;
	Json::FastWriter writer;
	temp["text"] = data.text;
	temp["vt"] = userBasic.vip_type;
	temp["vl"] = userBasic.vip_level;
	temp["vip"] = user.viplevel;
	data.text = data2.text = writer.write(temp);
	//info_log("[add email][temptext=%s]", temptext.c_str());
	/*		装备和英雄，资源都改为后台直接发
	Json::Value vvipRewardEq;  //装备update
	vvipRewardEq[0u]["s"]="vvipRewardEq";
	vvipRewardEq[0u]["reward"] = attachments["equipment"];
	vvipRewardEq[0u]["ts"] = now + 1;

	Json::Value vvipRewardHero; //武将update
	vvipRewardHero[0u]["s"] = "vvipRewardHero";
	vvipRewardHero[0u]["reward"] = attachments["heros"];
	vvipRewardHero[0u]["ts"] = now + 2;
	Json::Value vvipRewardRes; //资源update

	vvipRewardRes[0u]["s"] = "vvipRewardRes";
	vvipRewardRes[0u]["reward"] = attachments["resource"];
	vvipRewardRes[0u]["ts"] = now + 3;
	*/


	Json::Value updates;
	updates[0u]["s"] = "NEWEMAIL";
	updates[0u]["ts"] = now;
	updates[0u]["name"] = data.from_name;

	for(vector<uint64_t>::const_iterator it = vto_uid.begin(); it != end_it; it++)
	{
		data.opposite_uid = *it;
		data2.uid =  *it;
		ret = logicUserBasic.GetUserBasicLimit(data2.uid,platform,userBasic);
		if(0 != ret)
		{
			error_log("get userbasic limit failed uid=%u",data.uid);
			//return ret;
		}
		data.to_name = data2.to_name = userBasic.name;
		if(data.uid != ADMIN_UID)
		{
			ret = cDataEmail.AddEmail(data);
			if(0 != ret)
			{
				return ret;
			}
		}
		ret = cDataEmail.AddEmail(data2);
		if(0 != ret)
		{
			continue;
		}
		CLogicUpdates logicUpdates;
		ret = logicUpdates.AddUpdates(data.opposite_uid,updates);

		/*装备和英雄，资源都改为后台直接发
		if(attachments["equipment"].size()!=0)
		{
			logicUpdates.AddUpdates(data.opposite_uid,vvipRewardEq);
		}
		if(attachments["heros"].size()!=0)
		{
			logicUpdates.AddUpdates(data.opposite_uid,vvipRewardHero);
		}
		if(attachments["resource"]["r1"].asInt()!=0 || attachments["resource"]["r2"].asInt()!=0  || attachments["resource"]["r3"].asInt()!=0 || attachments["resource"]["r4"].asInt()!=0)
		{
			logicUpdates.AddUpdates(data.opposite_uid,vvipRewardRes);
		}
		*/

		if(0 != ret)
		{
			error_log("add updates failed ,uid=%u",data.opposite_uid);
		}
	}

	return 0;
}

int CLogicEmail::AddEmail(DataEmail &data,vector<uint64_t> &vto_uid, bool bUpdates,PlatformType platform)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser user;
	CLogicUserBasic logicUserBasic;
	DataUserBasic userBasic;
	vector<uint64_t>::const_iterator end_it = vto_uid.end();
	unsigned now = Time::GetGlobalTime();
	CDataEmail cDataEmail;
	DataEmail data2;
	data2 = data;
	data.post_ts = data2.post_ts = now;
	data2.opposite_uid = data.uid;
	if(data.uid == ADMIN_UID)
	{
		userBasic.name="系统管理员";
		user.viplevel = 0;
	}
	else
	{
		logicUserBasic.GetUserBasicLimitWithoutPlatform(data.uid,userBasic);
		logicUser.GetUserLimit(data.uid,user);

		if(user.level < 15 && user.viplevel < 3)
			return 0;

		string con = data.from_name + data.title + data.text;
		OnAdAnalize(data.uid, user.viplevel, user.level, con);
	}
	data.from_name = userBasic.name;
	data2.from_name = userBasic.name;
	data.post_flag = 2;   //发件
	data2.post_flag = 1;  //收件
	if(bUpdates)
		data2.text = data.text;
	else
	{
		Json::Value temp;
		Json::FastWriter writer;
		temp["text"] = data.text;
		temp["vt"] = userBasic.vip_type;
		temp["vl"] = userBasic.vip_level;
		temp["vip"] = user.viplevel;
		data.text = data2.text = writer.write(temp);
	}
	//info_log("[add email][temptext=%s]", temptext.c_str());

	string poster = CTrans::UTOS(data.uid);
	for(vector<uint64_t>::const_iterator it = vto_uid.begin(); it != end_it; it++)
	{
		if(!IsValidUid(*it))
			continue;

		if(data.uid != ADMIN_UID)
		{
			string black_list;
			CLogicUserNomenate logicUserNomenate;
			logicUserNomenate.getFriendBlackList(*it, black_list);
			if(black_list.find(poster) != string::npos)
				continue;
		}

		data.opposite_uid = *it;
		data2.uid =  *it;
		ret = logicUserBasic.GetUserBasicLimitWithoutPlatform(data2.uid,userBasic);
		if(0 != ret)
		{
			error_log("get userbasic limit failed uid=%u",data.uid);
			//return ret;
		}
		data.to_name = data2.to_name = userBasic.name;
		if(data.uid != ADMIN_UID)
		{
			ret = cDataEmail.AddEmail(data);
			if(0 != ret)
			{
				return ret;
			}
		}
		ret = cDataEmail.AddEmail(data2);
		if(0 != ret)
		{
			continue;
//			return ret;
		}
		if(!bUpdates)
		{
			Json::Value updates;
			CLogicUpdates logicUpdates;
			updates[0u]["s"] = "NEWEMAIL";
			updates[0u]["ts"] = now;
			updates[0u]["name"] = data.from_name;
			ret = logicUpdates.AddUpdates(data.opposite_uid,updates);
			if(0 != ret)
			{
				error_log("add updates failed ,uid=%u",data.opposite_uid);
			}
		}
	}

	return 0;
}

int CLogicEmail::GetAttachments(unsigned uid, const vector<uint64_t> &vEmail_Id,vector<string> &attchments)
{
	int ret = 0;
	CDataEmail cDataEmail;
	ret = cDataEmail.GetAttachments(uid,vEmail_Id,attchments);
	if(0 != ret)
	{
		return ret;
	}

	ret = cDataEmail.SetAttach_Flag(uid,vEmail_Id);
	if(0 != ret)
	{
		return ret;
	}
	return 0;
}




int CLogicEmail::DeleteEmails(unsigned uid,const vector<uint64_t> &vEmail_Id)
{
	int ret = 0;
	CDataEmail cDataEmail;
	ret = cDataEmail.DeleteEmails(uid, vEmail_Id);
	if(0 != ret)
	{
		return ret;
	}
	return 0;
}
int CLogicEmail::ReadEmail(unsigned uid,const uint64_t email_Id,DataEmail &data)
{
	int ret = 0;
	CDataEmail cDataEmail;
	ret = cDataEmail.ReadEmail(uid,email_Id,data);

	if(0 != ret)
	{


		return ret;
	}
	if(data.read_ts == 0)
	{

		ret = cDataEmail.SetReadTime(uid,email_Id);
		if(0 != ret)
		{

			return ret;
		}

	}
	return 0;
}

void CLogicEmail::OnAdAnalize(unsigned uid, unsigned vip, unsigned lvl, string& msg)
{
	if(!AdAnalize::getFlag())
	{
		//debug_log("ad_error");
		return;
	}
	ChatMsg c;
	c.uid = uid;
	c.vip = CTrans::UTOS(vip);
	c.lvl = CTrans::UTOS(lvl);
	c.msg = msg;
	c.type = "mail";
	int serverid = 0;
	Config::GetDomain(serverid);
	c.srvListen = CTrans::UTOS(serverid);
	AdAnalize::getInstance()->sendData(c);
}
