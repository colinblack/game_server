/*
 * LogicPay.h
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#ifndef LOGICPAY_H_
#define LOGICPAY_H_

#include "LogicInc.h"

//支付状态
enum PayStatusType
{
	PST_PENDING = 0, //未成交
	PST_OK = 1,	//成交
};

//支付通道类型
enum PayChannelType
{
	PCT_UNKNOW = -1,	//未知
	PCT_TEST = 0,	//测试平台
	PCT_FACEBOOK_CREDITS = 1,	//Facebook Credits
	PCT_QQ = 2,	//QQ平台
	PCT_RENREN = 3,	//人人
	PCT_ROCKPAY = 4, 	//RockPay
	PCT_TAKE8 = 5,	//Take8
	PCT_KUAIWAN = 6,	//快玩
	PCT_WEIYOUXI = 7,	//微游戏
	PCT_MOBAGE = 8,	//Yahoo!Mobage
	PCT_KAIXIN = 9,	//开心网
	PCT_17BI = 10	//一起币
};

class CLogicPay
{

public:

	int AddUser(unsigned uid, unsigned cash = 0);
	int GetCash(unsigned uid, unsigned &cash);
	int ChangeCash(unsigned uid, const string &type, int cash, int count, unsigned data, unsigned &balance);
	int BuyCash(unsigned uid, int cash, int credit);
	int ChangeCash(unsigned uid, const string &type, int cash, int count = 1);

	int AddPayHistory(DataPayHistory &payHistory);
	int GetPayHistory(unsigned uid, uint64_t payId, DataPayHistory &payHistory);
	int GetPayHistory(unsigned uid, PayChannelType channel, const string &channelPayId, DataPayHistory &payHistory);
	int SetPayHistory(unsigned uid, uint64_t payId, const DataPayHistory &payHistory);
	int SetPayHistoryStatus(unsigned uid, uint64_t payId, PayStatusType status);
	int SetPayHistoryStatus(unsigned uid, PayChannelType channel, const string &channelPayId, PayStatusType status);

	int AddCashFlow(DataCashFlow &flow);
	int GetCashFlows(unsigned uid, unsigned startTime, unsigned endTime, vector<DataCashFlow> &flows);

	int OnPay(unsigned uid, int cash, int credit);

};

#endif	//LOGICPAY_H_
