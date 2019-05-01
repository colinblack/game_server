/*
 * Bot.cpp
 *
 *  Created on: 2016-11-23
 *      Author: Ralf
 */

#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init())
	{
		cout << "init error";
		return 1;
	}

	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_OPEN_TS))
		return 0;

	if(argc < 5)
	{
		cout<<"para error"<<endl;
		return 1;
	}
	string openid = argv[1];
	unsigned kingdom = atoi(argv[2]);
	unsigned id = atoi(argv[3]);
	unsigned serverid = atoi(argv[4]);
	unsigned re = 0;
	if(argc > 5)
		re = atoi(argv[5]);

	Config::SelectDomain(serverid, serverid);
	OPUserInfo userinfo;
	userinfo.OpenId = openid;
	string iopenid, via;
	unsigned uid = 0;
	bool isNewUser = false;
	CLogicUserMapping LogicUserMapping;
	int ret = LogicUserMapping.LoginPlatformUser(PT_TEST, userinfo, iopenid, uid,isNewUser,via);
	if(ret != 0)
	{
		cout<<"mapping login error!"<<endl;
		return ret;
	}

	int ts = 2700 + Math::GetRandomInt(600);
	int w = Math::GetRandomInt(ts);
	if(re == 0)
		Time::Sleep(w, 0);
	ts -= w;

	Bot::RequestLogin * loginmsg = new Bot::RequestLogin;
	loginmsg->set_uid(uid);
	loginmsg->set_kingdom(kingdom);
	loginmsg->set_id(id);
	loginmsg->set_reload(re > 0);
	CSG17Packet loginpacket;
	loginpacket.cmd = PROTOCOL_BOT;
	loginpacket.m_msg = loginmsg;
	ret = BattleSocket::Send(serverid, &loginpacket);
	if(ret)
	{
		cout<<"send login error"<<endl;
		return ret;
	}
	CSG17Packet loginreply;
	ret = BattleSocket::Receive(serverid, &loginreply);
	if(ret)
	{
		cout<<"recv login error"<<endl;
		return ret;
	}
	Bot::ReplyLogin* rmsg = (Bot::ReplyLogin*)loginreply.m_msg;
	ret = rmsg->ret();
	if(ret)
	{
		cout<<"reply error."<<endl;
		return ret;
	}

	if(re == 0)
	{
		Time::Sleep(3, 0);
		Bot::RequestCity * citymsg = new Bot::RequestCity;
		citymsg->set_uid(uid);
		CSG17Packet citypacket;
		citypacket.cmd = PROTOCOL_BOT;
		citypacket.m_msg = citymsg;
		ret = BattleSocket::Send(serverid, &citypacket);
		if(ret)
			cout<<"send city error"<<endl;
		Time::Sleep(250, 0);
		while(1)
		{
			Bot::RequestMove * movemsg = new Bot::RequestMove;
			movemsg->set_uid(uid);
			CSG17Packet movepacket;
			movepacket.cmd = PROTOCOL_BOT;
			movepacket.m_msg = movemsg;
			ret = BattleSocket::Send(serverid, &movepacket);
			if(ret)
				cout<<"send move error"<<endl;

			w = 270 + Math::GetRandomInt(60);
			ts -= w;
			if(ts <= 0)
				break;
			Time::Sleep(w, 0);
		}
	}

	Time::Sleep(3, 0);
	Bot::RequestLogout * logoutmsg = new Bot::RequestLogout;
	logoutmsg->set_uid(uid);
	CSG17Packet logoutpacket;
	logoutpacket.cmd = PROTOCOL_BOT;
	logoutpacket.m_msg = logoutmsg;
	ret = BattleSocket::Send(serverid, &logoutpacket);
	if(ret)
		cout<<"send logout error"<<endl;

	return 0;
}


