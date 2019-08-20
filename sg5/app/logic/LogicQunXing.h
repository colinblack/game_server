/*
 * LogicActQunXing.h
 *
 *  Created on: 2019年7月9日
 *      Author: Administrator
 */

#ifndef LOGIC_QUNXING_H_
#define LOGIC_QUNXING_H_

#include "LogicInc.h"
#include "DataQunXing.h"

class CLogicQunXing: public LogicBase<CDataQunXing> {
public:
	CLogicQunXing();
	virtual ~CLogicQunXing();
	int GetInfo(unsigned uid, unsigned type, Json::Value &value);
	int AddGuest(unsigned uid, unsigned type, unsigned id, unsigned hud, unsigned hid, unsigned power, const string &smid, const string &hname, Json::Value &value);
	int DelGuest(unsigned uid, unsigned type, unsigned id, unsigned userid, Json::Value &value);
};

#endif /* LOGIC_QUNXING_H_ */
