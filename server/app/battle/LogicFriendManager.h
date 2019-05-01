#ifndef LOGIC_FRIEND_MANAGER_H
#define LOGIC_FRIEND_MANAGER_H

#include "ServerInc.h"

class LogicFriendManager : public BattleSingleton, public CSingleton<LogicFriendManager>
{
private:
	friend class CSingleton<LogicFriendManager>;
	LogicFriendManager(){};
	virtual ~LogicFriendManager(){}

public:
	enum
	{
		operate_of_add	= 1, //添加好友
		operate_of_receive	= 2, //接收赠礼
		operate_of_send	 = 3, //赠送赠礼
		max_grades_value = 5,  //奖励最大档
		per_gift_contain_prestige = 10, //威望值
		max_friend_num = 20, //好友上限
		max_send_gift_num = 20, //最大赠送次数
		max_receive_gift_num = 20, //最大接收次数

		max_log_nums = 40,  //日志条数
		gift_contain_coin	= 10000, //钞票
	};

	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	//打开窗口
	int Process(unsigned uid, ProtoFriend::OpenFriendWindowReq *reqmsg, ProtoFriend::OpenFriendWindowResp * respmsg);

	//添加好友
	int Process(unsigned uid, ProtoFriend::AddFriendReq *reqmsg, ProtoFriend::AddFriendResp * respmsg);

	//删除好友
	int Process(unsigned uid, ProtoFriend::DelFriendReq *reqmsg, ProtoFriend::DelFriendResp *respmsg);

	//赠送礼物
	int Process(unsigned uid, ProtoFriend::SendGiftReq *reqmsg, ProtoFriend::SendGiftResp *respmsg);

	//领取威望奖励
	int Process(unsigned uid, ProtoFriend::ReceivePrestigeRewardReq *reqmsg, ProtoFriend::ReceivePrestigeRewardResp *respmsg);

	int LogFriendOperate(unsigned uid, unsigned othuid, unsigned code);
	int FullMessage(unsigned uid, ProtoFriend::FriendCPPAll* msg);
	int FullMessage(unsigned uid, ProtoFriend::FriendGiftCPP* msg);

private:
	//打开窗口
	int OpenFriendWindow(unsigned uid, ProtoFriend::OpenFriendWindowResp * respmsg);

	//添加好友
	int AddFriend(unsigned uid, unsigned othuid, ProtoFriend::AddFriendResp * respmsg);

	//删除好友
	int DelFriend(unsigned uid, unsigned othuid);

	//赠送礼物
	int SendFriendGift(unsigned uid, unsigned othuid, ProtoFriend::SendGiftResp * respmsg);

	//重置赠送礼物信息
	int ResetFriendGift(DataFriendGift & friendgift, unsigned now);

	//接收礼物
	int ReceiveGift(unsigned senduid, unsigned receieveuid);

	//领取威望奖励
	int ReceivePrestigeReward(unsigned uid, ProtoFriend::ReceivePrestigeRewardResp *respmsg);

	//设置好友的完整信息
	int SetFriendMessage(DataFriend & datafriend, ProtoFriend::FriendCPP * msg);

private:
	static const int Grade_Prestige[max_grades_value];
	static const int Grade_Cash[max_grades_value];
};

#endif //LOGIC_FRIEND_MANAGER_H
