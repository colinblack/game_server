#include "LogicInc.h"

#define WYX_INVITE_URL	"http://game.weibo.com/home/widget/selector?target=self&appId=%s&mode=naf&action=%s%%3Fopenid%%3D%s&excludeIds=%s&pageSize=20&content=%s&callback=%s%%3Fiopenid%%3D%s"

const char WYX_INVITE_PAGE[] =
	"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">"
	"<html xmlns=\"http://www.w3.org/1999/xhtml\">"
	"<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /></head>"
	"<body>"
	"<form method=\"post\" action=\"http://game.weibo.com/home/widget/requestForm\" id=\"createToolFriend\" target=\"_self\">"
	"<input type=\"hidden\" name=\"target\" value=\"self\" />"
	"<input type=\"hidden\" name=\"appId\" value=\"%s\" />"
	"<input type=\"hidden\" name=\"modes\" value=\"naf\" />"
	"<input type=\"hidden\" name=\"selectedMode\" value=\"naf\" />"
	"<input type=\"hidden\" name=\"action\" value=\"%s?openid=%s\" />"
	"<input type=\"hidden\" name=\"excludedIds\" value=\"%s\" />"
	"<input type=\"hidden\" name=\"pageSize\" value=\"16\" />"
	"<input type=\"hidden\" name=\"content\" value=\"%s\" />"
	"<input type=\"hidden\" name=\"callback\" value=\"%s?iopenid=%s\" />"
	"</form>"
	"<script type=\"text/javascript\">"
	"function postForm(){document.getElementById(\"createToolFriend\").submit();}"
	"if(window.attachEvent){window.attachEvent(\"onload\", postForm);}"
	"else if(window.addEventListener){window.addEventListener(\"load\", postForm, false);}"
	"</script>"
	"</body>";

class CCgiWyxInvite : public CCgiBase
{
public:

	CCgiWyxInvite() : CCgiBase("wyx/invite")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(SinaWbEntry)

	int SinaWbEntry()
	{
		if(OpenPlatform::GetType() != PT_WEIYOUXI)
		{
			return R_ERR_REFUSE;
		}

		static bool s_init = false;
		static string s_appId;
		static string s_inviteUrl;
		static string s_inviteContent;
		static string s_gameEntry;
		static unsigned s_lastUpdate = 0;
		static map<string, string> s_mapInviteHistory;
		if(!s_init)
		{
			s_appId = OpenPlatform::GetPlatform()->GetAppId();
			s_inviteUrl = OpenPlatform::GetPlatform()->GetConfig("invite_url"); //Crypt::UrlEncode(OpenPlatform::GetPlatform()->GetConfig("invite_url"));
			s_inviteContent = OpenPlatform::GetPlatform()->GetConfig("invite_content");	//Crypt::UrlEncode(OpenPlatform::GetPlatform()->GetConfig("invite_content"));
			s_gameEntry = OpenPlatform::GetPlatform()->GetConfig("game_entry");	//Crypt::UrlEncode(OpenPlatform::GetPlatform()->GetConfig("game_entry"));
			s_init = true;
		}

		if(!Time::IsToday(s_lastUpdate))
		{
			s_mapInviteHistory.clear();
		}
		s_lastUpdate = Time::GetGlobalTime();

		string openid = CCGIIn::GetCGIStr("openid");
		string ids = CCGIIn::GetCGIStr("ids");
		map<string, string>::iterator itr = s_mapInviteHistory.find(openid);
		string excludedIds;
		if(itr != s_mapInviteHistory.end())
		{
			excludedIds = itr->second;
		}
		if(!ids.empty())
		{
			if(excludedIds.empty())
			{
				excludedIds = ids;
			}
			else
			{
				excludedIds = excludedIds + "," + ids;
			}
			s_mapInviteHistory[openid] = excludedIds;
		}

		//string redirectUrl;
		//String::Format(redirectUrl, WYX_INVITE_URL, s_appId.c_str(), s_inviteUrl.c_str(), openid.c_str(),
		//		excludedIds.c_str(), s_inviteContent.c_str(), s_gameEntry.c_str(), openid.c_str());
		//CgiUtil::HttpRedirect(redirectUrl);

		string content;
		String::Format(content, WYX_INVITE_PAGE, s_appId.c_str(), s_inviteUrl.c_str(), openid.c_str(),
				excludedIds.c_str(), s_inviteContent.c_str(), s_gameEntry.c_str(), openid.c_str());
		CgiUtil::PrintText(content);

		CGI_SEND_LOG("openid=%s&ids=%s&excludedIds=%s&redirect=ok", openid.c_str(), ids.c_str(), excludedIds.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiWyxInvite)
