#include "LogicFriendManager.h"

const int LogicFriendManager::Grade_Prestige[max_grades_value] = {100,500,1200,2000,5000};
const int LogicFriendManager::Grade_Cash[max_grades_value] = {100,150,200,250,300};

int LogicFriendManager::NewUserInit(unsigned uid)
{
	DataFriendGiftManager::Instance()->New(uid);

	return 0;
}

int LogicFriendManager::LoginCheck(unsigned uid)
{
	//检查好友数据是否加载进内存
	int ret = DataFriendManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataFriendManager::Instance()->LoadBuff(uid);
	}

	//检查好友赠送是否加载进内存
	ret = DataFriendGiftManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataFriendGiftManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)  //没有好友赠送数据，则需初始化
		{
			NewUserInit(uid);
		}
	}

	return ret;
}


int LogicFriendManager::Process(unsigned uid, ProtoFriend::OpenFriendWindowReq *reqmsg, ProtoFriend::OpenFriendWindowResp * respmsg)
{
	OpenFriendWindow(uid, respmsg);

	return 0;
}

int LogicFriendManager::OpenFriendWindow(unsigned uid, ProtoFriend::OpenFriendWindowResp * respmsg)
{
	//好友信息
	FullMessage(uid, respmsg->mutable_friendall());

	//好友赠礼信息
	FullMessage(uid, respmsg->mutable_friendgift());

	return 0;
}


int LogicFriendManager::Process(unsigned uid, ProtoFriend::AddFriendReq *reqmsg, ProtoFriend::AddFriendResp * respmsg)
{
	unsigned friend_uid = reqmsg->othuid();

	AddFriend(uid, friend_uid, respmsg);

	return 0;
}

int LogicFriendManager::AddFriend(unsigned uid, unsigned othuid, ProtoFriend::AddFriendResp * respmsg)
{
	//判断好友上限
	vector<unsigned> indexs;
	DataFriendManager::Instance()->GetFriends(uid, indexs);

	if (indexs.size() >= max_friend_num)
	{
		error_log("friend num is max. uid=%u", uid);
		throw runtime_error("friend_num_max");
	}

	//是否已添加该好友
	bool isexist = DataFriendManager::Instance()->IsFriendExist(uid, othuid);

	if (isexist)
	{
		error_log("friend is exist. uid=%u,frienduid=%u", uid, othuid);
		throw runtime_error("friend_already_exist");
	}

	//添加好友
	DataFriend datafriend;
	datafriend.uid = uid;
	datafriend.friend_uid = othuid;

	DataFriendManager::Instance()->AddBuff(datafriend);

	//记录日志
	int code = operate_of_add;
	LogFriendOperate(uid, othuid, code);

	//填写协议数据
	//设置好友完整信息
	SetFriendMessage(datafriend, respmsg->mutable_yourfriend());

	//设置好友赠送信息
	FullMessage(uid, respmsg->mutable_friendgift());

	return 0;
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::DelFriendReq *reqmsg, ProtoFriend::DelFriendResp *respmsg)
{
	unsigned friend_uid = reqmsg->othuid();

	DelFriend(uid, friend_uid);

	return 0;
}

int LogicFriendManager::DelFriend(unsigned uid, unsigned othuid)
{
	//是否已添加该好友
	bool isexist = DataFriendManager::Instance()->IsFriendExist(uid, othuid);

	if (!isexist)
	{
		error_log("friend is not exist. uid=%u,frienduid=%u", uid, othuid);
		throw runtime_error("friend_not_exist");
	}

	DataFriend& datafriend = DataFriendManager::Instance()->GetFriend(uid, othuid);

	//删除好友
	DataFriendManager::Instance()->DeleteFriend(datafriend);

	return 0;
}

int LogicFriendManager::Process(unsigned uid, ProtoFriend::SendGiftReq *reqmsg, ProtoFriend::SendGiftResp *respmsg)
{
	unsigned friend_uid = reqmsg->othuid();

	SendFriendGift(uid, friend_uid, respmsg);

	return 0;
}

int LogicFriendManager::SendFriendGift(unsigned uid, unsigned othuid, ProtoFriend::SendGiftResp * respmsg)
{
	//判断好友用户是否在线
	if (!UserManager::Instance()->IsOnline(othuid))  //在线
	{
		error_log("friend not online. uid=%u,frienduid=%u", uid, othuid);
		throw runtime_error("friend_not_online");
	}

	unsigned now = Time::GetGlobalTime();

	//判断是否有赠送次数
	DataFriendGift& send_gift = DataFriendGiftManager::Instance()->GetFriendGift(uid);

	//先判断是否跨天，跨天要重置次数
	if (CTime::GetDayInterval(send_gift.send_gift_ts, now))  //跨天，重置次数
	{
		ResetFriendGift(send_gift, now);
	}

	if (send_gift.send_gift_times >= max_send_gift_num)
	{
		error_log("send gift times already max. uid=%u", uid);
		throw runtime_error("send_gift_times_max");
	}

	//判断该好友是否已赠送过
	DataFriend& datafriend = DataFriendManager::Instance()->GetFriend(uid, othuid);

	if (0 == CTime::GetDayInterval(datafriend.send_gift_ts, now))
	{
		error_log("friend gift already sended in today. uid=%u,receuid=%u", uid, othuid);
		throw runtime_error("friend_already_sended_today");
	}

	//以接受者为主体的赠送方式
	ReceiveGift(uid, othuid);

	//赠送完毕
	datafriend.send_gift_ts = now;
	DataFriendManager::Instance()->UpdateFriend(datafriend);

	send_gift.send_gift_times += 1;
	send_gift.send_gift_ts = now;

	int code = operate_of_send;
	LogFriendOperate(uid, othuid, code);

	DataFriendGiftManager::Instance()->UpdateDataFriendGift(send_gift);

	//设置好友完整信息
	SetFriendMessage(datafriend, respmsg->mutable_yourfriend());

	//设置好友赠送信息
	send_gift.SetMessage(respmsg->mutable_friendgift());

	return 0;
}

int LogicFriendManager::ResetFriendGift(DataFriendGift & friendgift, unsigned now)
{
	friendgift.send_gift_times = 0;
	friendgift.send_gift_ts = now;

	friendgift.receive_gift_times = 0;
	friendgift.receive_gift_ts = now;

	return 0;
}

int LogicFriendManager::ReceiveGift(unsigned senduid, unsigned receieveuid)
{
	//给接受者加钞票和威望
	//判断好友用户是否在线
	if (!UserManager::Instance()->IsOnline(receieveuid))  //在线
	{
		error_log("friend not online. uid=%u,frienduid=%u", senduid, receieveuid);
		throw runtime_error("friend_not_online");
	}

	unsigned now = Time::GetGlobalTime();
	DataFriendGift& receive_gift = DataFriendGiftManager::Instance()->GetFriendGift(receieveuid);

	//判断是否跨天
	if (CTime::GetDayInterval(receive_gift.receive_gift_ts, now))  //跨天，重置次数
	{
		ResetFriendGift(receive_gift, now);
	}

	if (receive_gift.receive_gift_times >= max_receive_gift_num)
	{
		error_log("receive gift times already max. uid=%u,receuid=%u", senduid, receieveuid);
		throw runtime_error("friend_recvgift_times_max");
	}

	DBCUserBaseWrap userwrap(receieveuid);
	userwrap.AddResource(gift_contain_coin, 0, 0, 0, "FriendGift");

	//直接加威望
	int oldprestige = receive_gift.prestige;

	receive_gift.prestige += per_gift_contain_prestige;

	if (receive_gift.prestige > Grade_Prestige[receive_gift.grades - 1])
	{
		receive_gift.prestige = Grade_Prestige[receive_gift.grades - 1];
	}

	receive_gift.receive_gift_times += 1;
	receive_gift.receive_gift_ts = now;

	LogFriendOperate(receieveuid, senduid, operate_of_receive);  //日志的主体是接受者本身

	DataFriendGiftManager::Instance()->UpdateDataFriendGift(receive_gift);

	int add_prestige = receive_gift.prestige - oldprestige;
	ProtoFriend::ReceiveGiftPushReq * pushmsg = new ProtoFriend::ReceiveGiftPushReq;

	//设置推送的信息
	pushmsg->mutable_coin()->set_value(gift_contain_coin);
	pushmsg->mutable_coin()->set_total_value(userwrap.Obj().coin);

	pushmsg->mutable_prestige()->set_value(add_prestige);
	pushmsg->mutable_prestige()->set_total_value(receive_gift.prestige);

	pushmsg->set_recv_times(receive_gift.receive_gift_times);
	pushmsg->set_recv_ts(receive_gift.receive_gift_ts);

	LogicManager::Instance()->sendMsg(receieveuid, pushmsg);

	return 0;
}


int LogicFriendManager::Process(unsigned uid, ProtoFriend::ReceivePrestigeRewardReq *reqmsg, ProtoFriend::ReceivePrestigeRewardResp *respmsg)
{
	ReceivePrestigeReward(uid, respmsg);

	return 0;
}

int LogicFriendManager::ReceivePrestigeReward(unsigned uid, ProtoFriend::ReceivePrestigeRewardResp *respmsg)
{
	DataFriendGift& friendgift = DataFriendGiftManager::Instance()->GetFriendGift(uid);

	//判断威望值是否满足档次要求
	if (friendgift.prestige < Grade_Prestige[friendgift.grades - 1])
	{
		error_log("prestige is not enough. uid=%u,prestige=%u,grades=%u", uid, friendgift.prestige, friendgift.grades);
		throw runtime_error("prestige_not_enough");
	}

	friendgift.prestige = 0;
	int addcash = Grade_Cash[friendgift.grades - 1];

	if (friendgift.grades < max_grades_value)
	{
		friendgift.grades += 1;
	}

	DBCUserBaseWrap userwrap(uid);
	userwrap.AddCash(addcash, "PrestigeExchange");

	DataFriendGiftManager::Instance()->UpdateDataFriendGift(friendgift);

	respmsg->set_cash(userwrap.Obj().cash);
	friendgift.SetMessage(respmsg->mutable_friendgift());

	return 0;
}

int LogicFriendManager::LogFriendOperate(unsigned uid, unsigned othuid, unsigned code)
{
	DataFriendGift& friendgift = DataFriendGiftManager::Instance()->GetFriendGift(uid);

	Json::Value logvalue;
	unsigned now= Time::GetGlobalTime();

	int year = 0, month = 0, day = 0;

	LogicCommonUtil::GetDate(now, year, month, day);

	logvalue["d"] = day;
	logvalue["m"] = month;
	logvalue["c"] = code;
	logvalue["uid"] = othuid;

	//获取对方的名字,从resourcemanager里获取，因为可能对方不在线
	int index = ResourceManager::Instance()->GetIndex(othuid);

	if (-1 == index)
	{
		logvalue["name"] = "";
	}
	else
	{
		logvalue["name"] = ResourceManager::Instance()->m_data->item[index].name;
	}

	Json::Value logdata(Json::arrayValue);
	string strlog(friendgift.log_data);

	if (strlog.empty())
	{
		strlog = "[]";
	}

	bool issuccess = Json::FromString(logdata, strlog);

	if (!issuccess)
	{
		//解析失败，则清空
		logdata.clear();
	}

	logdata.append(logvalue);

	if (logdata.size() > max_log_nums)  //数组超长，删除第一个元素
	{
		Json::Value temp(logdata);
		logdata.clear();

		for(int i = 0; i < max_log_nums; ++i)
		{
			logdata.append(temp[i+1]);
		}
	}

	Json::FastWriter writer;
	strlog  = writer.write(logdata);

	memset(friendgift.log_data, 0, sizeof(friendgift.log_data));
	//strncpy(friendgift.log_data, strlog.c_str(), FRIEND_GIFT_LOG_LEN);
	snprintf(friendgift.log_data, FRIEND_GIFT_LOG_LEN, "%s", strlog.c_str());

	DataFriendGiftManager::Instance()->UpdateDataFriendGift(friendgift);

	return 0;
}

int LogicFriendManager::FullMessage(unsigned uid, ProtoFriend::FriendGiftCPP* msg)
{
	DataFriendGift& friendgift = DataFriendGiftManager::Instance()->GetFriendGift(uid);
	friendgift.SetMessage(msg);

	return 0;
}

int LogicFriendManager::FullMessage(unsigned uid, ProtoFriend::FriendCPPAll* msg)
{
	vector<unsigned> indexs;

	DataFriendManager::Instance()->GetFriends(uid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataFriend& datafriend = DataFriendManager::Instance()->GetFriend(indexs[i]);

		SetFriendMessage(datafriend, msg->add_friends());
	}

	return 0;
}

int LogicFriendManager::SetFriendMessage(DataFriend & datafriend, ProtoFriend::FriendCPP * friend_msg)
{
	datafriend.SetMessage(friend_msg);

	//补充好友的额外信息.比如国家，名称，等级
	int index = ResourceManager::Instance()->GetIndex(datafriend.friend_uid);

	if (-1 == index)
	{
		return 0;
	}

	friend_msg->set_kindom(ResourceManager::Instance()->m_data->item[index].kingdom);
	friend_msg->set_name(ResourceManager::Instance()->m_data->item[index].name);
	friend_msg->set_level(ResourceManager::Instance()->m_data->item[index].property[DemoOfflineProperty_u_level]);

	//判断是否在线
	if (UserManager::Instance()->IsOnline(datafriend.friend_uid))  //在线
	{
		friend_msg->set_isonline(true);
	}
	else
	{
		friend_msg->set_isonline(false);
	}

	return 0;
}
