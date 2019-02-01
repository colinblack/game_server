#include "LogicInc.h"

class CCgiMessage : public CCgiBase
{

public:

	CCgiMessage() : CCgiBase("message")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("send", SendMessage)
	CGI_SET_ACTION_MAP("get", GetMessage)
	CGI_SET_ACTION_MAP("remove", RemoveMessage)
	CGI_SET_ACTION_MAP("sendhelpreward", SendHelpReward)
	CGI_SET_ACTION_MAP("verify", Verify)
	CGI_SET_ACTION_MAP("sendemail", SendEmail)
	CGI_SET_ACTION_MAP("getuserinfo", GetUserInfo)
	CGI_ACTION_MAP_END

	int SendMessage()
	{
		unsigned toUid = 0;
		if (!Json::GetUInt(m_data, "targetid", toUid))
			toUid = 0;
		string type;
		if (!Json::GetString(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}
		CLogicMessage logicMsg;
		int ret = 0;
		if (type == "message")
		{
			string message;
			if (toUid == 0 || !Json::GetString(m_data, "message", message))
				return R_ERR_PARAM;
			StringFilter::Replace(message);
			ret = logicMsg.Chat(m_uid, toUid, message);
			if (ret != 0)
				return ret;
		}
		else if (type == "request")
		{
			string way;
			if (!Json::GetString(m_data, "way", way))
				return R_ERR_PARAM;
			if (way == "add")
			{
				if (toUid == 0 || !Json::IsObject(m_data, "message"))
					return R_ERR_PARAM;
				ret = logicMsg.AddRequest(m_uid, toUid, m_data["message"]);
				if (ret != 0)
					return ret;
			}
			else if (way == "accept")
			{
				uint64_t msgid = 0;
				if (toUid == 0 || !Json::GetUInt64(m_data, "msgid", msgid))
					return R_ERR_PARAM;
				ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_ACCEPT, m_data["message"]);
				if (ret != 0)
					return ret;
			}
			else if (way == "reject")
			{
				uint64_t msgid = 0;
				if (toUid == 0 || !Json::GetUInt64(m_data, "msgid", msgid))
					return R_ERR_PARAM;
				ret = logicMsg.ReplyRequest(m_uid, toUid, msgid, MS_REJECT, m_data["message"]);
				if (ret != 0)
					return ret;
			}
			else if (way == "cancel")
			{
				uint64_t msgid = 0;
				if (!Json::GetUInt64(m_data, "msgid", msgid))
					msgid = 0;
				string mtype;
				if (!Json::GetString(m_data, "mtype", mtype))
					mtype = "alliance_join";
				ret = logicMsg.CancelRequest(m_uid, mtype, msgid);
				if (ret != 0)
					return ret;
			}
			else
			{
				return R_ERR_PARAM;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}

		CGI_SEND_LOG("action=send&uid=%u&toUid=%u&type=%s", m_uid, toUid, type.c_str());
		return R_SUCCESS;
	}

	int GetMessage()
	{
		string type;
		if (!Json::GetString(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}
		unsigned quid = 0;
		if (!Json::GetUInt(m_data, "quid", quid) || quid == 0)
		{
			quid = m_uid;
		}

		Json::Reader reader;
		CLogicMessage logicMsg;
		int ret = 0;
		if (type == "message")
		{
			int toward = TOWARD_RECV;
			if (!Json::GetInt(m_data, "toward", toward))
				toward = TOWARD_RECV;
			ret = logicMsg.GetChatJson(quid, toward, m_jsonResult["res"]);
			if (ret != 0)
				return ret;
		}
		else if (type == "request")
		{
			string mtype;
			int toward;
			int status;
			Json::GetString(m_data, "mtype", mtype);
			if(!Json::GetInt(m_data, "toward", toward) ||
					!Json::GetInt(m_data, "status", status))
			{
				PARAM_ERROR_RETURN();
			}
			if (toward < 0 || toward > TOWARD_TYPE_ALL
					|| status < MS_UN_PROCESS || status > MS_STATUS_ALL)
			{
				PARAM_ERROR_RETURN();
			}

			vector<string> vecMtypes;
			if(!mtype.empty())
			{
				CBasic::StringSplitTrim(mtype, "|", vecMtypes);
			}
			set<string> mtypes(vecMtypes.begin(), vecMtypes.end());

			ret = logicMsg.GetRequestJson(quid, mtypes, toward, status, m_jsonResult["res"]);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}

		CGI_SEND_LOG("action=get&uid=%u&quid=%u&type=%s", m_uid, quid, type.c_str());
		return R_SUCCESS;
	}

	int RemoveMessage()
	{
		int ret;
		string type;
		uint64_t messageId;
		if (!Json::GetString(m_data, "type", type) ||
			!Json::GetUInt64(m_data, "messageid", messageId))
		{
			return R_ERR_PARAM;
		}
		CLogicMessage logicMessage;
		if(type == "message")
		{
			ret = logicMessage.RemoveChat(m_uid, messageId);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			return R_ERR_PARAM;
		}
		CGI_SEND_LOG("action=remove&uid=%u&messageid=%llu&type=%s", m_uid, messageId, type.c_str());
		return R_SUCCESS;
	}

	int SendHelpReward()
	{
		int ret;
		string itemid;
		int count;
		if(!Json::GetString(m_data, "itemid", itemid) ||
			!Json::GetInt(m_data, "count", count))
		{
			PARAM_ERROR_RETURN();
		}
		CLogicUserInteract logicInteract;
		uint64_t messageId;
		ret = logicInteract.SendHelpReward(m_uid, itemid, count, messageId);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["messageid"] = Convert::UInt64ToString(messageId);
		CGI_SEND_LOG("action=sendhelpreward&uid=%u&itemid=%s&count=%d&messageid=%llu",
				m_uid, itemid.c_str(), count, messageId);
		return R_SUCCESS;
	}

	int Verify()
	{
		int ret = LogicSso::Verify(m_uid);
		if (ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=verify&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int SendEmail()
	{
		int ret;
		Email::MailMessage mail;
		if(!Config::GetValue(mail.Server, "smtp_server") ||
			!Config::GetValue(mail.From, "mail_sender"))
		{
			error_log("[config_error][server=%s,from=%s]", mail.Server.c_str(), mail.From.c_str());
			ERROR_RETURN(R_ERR_REFUSE);
		}
		unsigned uid;
		if(!Json::GetUInt(m_data, "to", uid) ||
			!Json::GetString(m_data, "subject", mail.Subject) ||
			!Json::GetString(m_data, "body", mail.Body))
		{
			PARAM_ERROR_RETURN();
		}
		Json::Value userExtraData;
		CHECK_CALL(LogicUser::GetExtraData(uid, userExtraData));
		if(!Json::GetString(userExtraData, "email", mail.To))
		{
			DataUserBasic userBasic;
			CHECK_CALL(LogicUserBasic::GetUser(uid, OpenPlatform::GetType(), userBasic));
			Json::Value extraData;
			Json::FromString(extraData, userBasic.extra_data);
			Json::GetString(extraData, "email", mail.To);
			if(mail.To.empty())
			{
				ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "no_email");
			}
		}
		if(!Email::SendMail(mail))
		{
			error_log("[send_mail_fail][uid=%u,to=%u,email=%s]", m_uid, uid, mail.To.c_str());
		}
		if(!Json::IsObject(userExtraData, "istat"))
		{
			userExtraData["istat"] = Json::Value(Json::objectValue);
		}
		Json::Value &istat = userExtraData["istat"];
		unsigned lastEmailTime = 0;
		unsigned emailCount = 0;
		Json::GetUInt(istat, "let", lastEmailTime);
		if(Time::IsToday(lastEmailTime))
		{
			emailCount++;
		}
		else
		{
			Json::GetUInt(istat, "ec", emailCount);
			emailCount = 0;
		}
		istat["let"] = Time::GetGlobalTime();
		istat["ec"] = emailCount;
		LogicUser::SetExtraData(uid, userExtraData);
		CGI_SEND_LOG("action=sendemail&uid=%u&to=%u&email=%s", m_uid, uid, mail.To.c_str());
		return R_SUCCESS;
	}

	int GetUserInfo()
	{
		unsigned userid = 0;
		if (!Json::GetUInt(m_data, "userid", userid) || !IsValidUid(userid))
		{
			PARAM_ERROR_RETURN();
		}
		int ret = LogicUser::GetUserInfo(userid, m_jsonResult);
		if (ret != 0)
			return ret;

		CGI_SEND_LOG("action=getuserinfo&uid=%u", m_uid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiMessage)
