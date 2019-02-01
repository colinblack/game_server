#ifndef __LOGIC_TAKE8_H__
#define __LOGIC_TAKE8_H__

#include "LogicInc.h"
#include <string>
using namespace std;

class CLogicTake8
{
public:
	//处理接收到的订单请求
	int ProcessOrder(
			const string &gameId,
			const string &orderId,
			const string &fbuid,
			int amt,
			const string &vcode);

	string m_outMsg;
};

#endif
