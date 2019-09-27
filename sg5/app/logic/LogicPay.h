#ifndef __LOGIC_PAY_H__
#define __LOGIC_PAY_H__

#include "LogicInc.h"

//支付状态
enum PayStatusType
{
	PST_PENDING = 0, //未成交
	PST_OK = 1,	//成交
	PST_BACK = 2,	//chargeback
};

#ifdef SG_16_VER
#define HERO_COIN_CASH 100
#else
#define HERO_COIN_CASH 5000
#endif
#define HERO_COIN_CASH_4399 500
#define HERO_COIN_NUM 10
#define HERO_COIN_NUM_4399 1

//支付通道类型
enum PayChannelType
{
	PCT_UNKNOW				= -1,	//未知
	PCT_TEST				= 0,	//测试平台
	PCT_FACEBOOK_CREDITS	= 1,	//Facebook Credits
	PCT_QQ					= 2,	//QQ平台
	PCT_RENREN				= 3,	//人人
	PCT_ROCKPAY				= 4, 	//RockPay
	PCT_TAKE8				= 5,	//Take8
	PCT_KUAIWAN				= 6,	//快玩
	PCT_WEIYOUXI			= 7,
	PCT_VN					= 8,
	PCT_QQGAME				= 9,
	PCT_BSG                 = 10,
};

enum PayFlag
{
	PAY_FLAG_CHARGE 	= 1,
	PAY_FLAG_ADMIN 		= 2,
	PAY_FLAG_COST_ALL 	= 4,
	PAY_FLAG_NO_REPLY	= 8,
};

struct User_Pay
{
	unsigned ts;
	int cash;
	int coins;

	User_Pay()
	{
		ts = cash = coins = 0;
	}
};

class CLogicPay
{
public:
	int InitailizePay(unsigned uid);
	int AddUser(unsigned uid, unsigned cash = 0);
	int GetPay(unsigned uid, DataPay &pay);

	int AddAlliancePay(unsigned aid, const string &type, int coins = 0);
	int GetAlliancePay(unsigned aid, DataAlliancePay &pay);
	int ChangeAlliancePay(unsigned aid, int coins, const string &type, int count = 1);

	int AddPayHistory(DataPayHistory &payHistory);
	int GetPayHistory(unsigned uid, uint64_t payId, DataPayHistory &payHistory);
	int GetPayHistory(unsigned uid, PayChannelType channel, const string &channelPayId, DataPayHistory &payHistory);
	int GetPayHistory(unsigned uid, unsigned startTs, unsigned endTs, unsigned &totalPay);
	int SetPayHistoryStatus(unsigned uid, uint64_t payId, PayStatusType status);
	int SetPayHistoryStatus(unsigned uid, PayChannelType channel, const string &channelPayId, PayStatusType status);

	//修改货币的原始接口，须在调用前读取user_flag，调用后保存user_flag，只用于处理充值和前端发来的order
	int ChangePay(unsigned uid, int cash, int coins, DataPay &pay, const string &type, Json::Value &user_flag, bool &bsave, unsigned flag = 0, bool iskuafufenghuo=false);

	int FixConsumeRank(unsigned uid);

	//增加了order_log的修改货币的原始接口，须在调用前读取user_flag，调用后保存user_flag，只用于处理后端产生的order
	int ProcessOrderForBackend(unsigned uid, int cash, int coins, DataPay &pay, const string &type, Json::Value &user_flag, bool &bsave, unsigned flag = 0, bool iskuafufenghuo=false);

	//修改货币的简易接口1，不保存user_flag， 不返回pay，只用于处理系统功能产生的货币变化
	int ChangePay(unsigned uid, int cash, int coins, const string &type, unsigned flag = 0);

	//修改货币的简易接口2，不保存user_flag， 但是返回pay，只用于处理系统功能产生的货币变化
	int ChangePay(unsigned uid, int cash, int coins, const string &type, DataPay &pay, unsigned flag = 0);

	//处理充值邮件和累计充值的接口，在ChangePay后调用，最后保存user
	int DoPay(unsigned uid, DataUser &user, const unsigned cash);

	//修改英雄积分的原始接口，须在调用前读取user_flag，调用后保存user_flag，只用于处理前端发来的order
	int ChangePayHeroCoins(unsigned uid,int coins2,const string &type, Json::Value &user_flag);

	int Try(unsigned uid, int cash, int coins);
private:
	int addPaymentByDay(Json::Value &userFlag, int accCharge);
	int addUserConsumeByDay(Json::Value &userFlag, int coins = 0, int cash = 0);

	//处理活动，只在ChangePay里调用
	int SetUserPayRank(unsigned uid, int cash, Json::Value &user_flag, bool &bsave);
	int SetUserPayTotal(unsigned uid, int cash, Json::Value &user_flag, bool &bsave);
	int SetHundredDaysActivities(unsigned uid, int cash, Json::Value &user_flag);    //百日消费活动
	int SetConsumeRank(unsigned uid, int cash, Json::Value &user_flag, bool iskuafufenghuo=false);    //百日消费活动
	int SetRechargeRank(unsigned uid, int cash, Json::Value &user_flag);   //充值排行榜

	//修改英雄积分的原始接口，须在调用前读取user_flag，调用后保存user_flag，只用于处理充值在ChangePay里调用
	int AddHeroCoins(unsigned uid,int cash,const string &type, Json::Value &user_flag);
};


#endif	//LOGICPAY_H_
