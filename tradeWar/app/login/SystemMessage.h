/*
 * SystemMessage.h
 *
 *  Created on: 2018年2月4日
 *      Author: Administrator
 */

#ifndef SYSTEMMESSAGE_H_
#define SYSTEMMESSAGE_H_

#include "Kernel.h"
#include "PbMessage.h"
#include "Award.h"

struct SystemMessageSend
{
	uint32_t ts;
	uint32_t uid;
	string user_name;
	Json::Value msg;

	SystemMessageSend(): ts(0), uid(0)
	{
		user_name.clear();
		msg.clear();
	}
};

struct SystemMessageInfo
{
	uint32_t ts;
	uint32_t uid;
	string user_name;
	string defend_name;
	map<byte,uint32_t> msg;
	vector<AwardInfo> reward;

	SystemMessageInfo() : ts(0), uid(0)
	{
		user_name.clear();
		msg.clear();
		reward.clear();
	}
	~SystemMessageInfo()
	{
		user_name.clear();
		msg.clear();
		reward.clear();
	}
	void parse(const SysgemMsg::SysgemMsgItem & item)
	{
		this->ts = item.ts();
		this->uid = item.uid();
		this->user_name = item.user_name();
		for (int i = 0; i < item.data_size(); ++i)
		{
			this->msg[item.data(i).k()] = item.data(i).v();
		}
		for (int i = 0; i < item.reward_size(); ++i)
		{
			AwardInfo info;
			info.type = item.reward(i).t();
			info.id = item.reward(i).id();
			info.count = item.reward(i).c();
			this->reward.push_back(info);
		}
	}
	void Serialize(SysgemMsg::SysgemMsgItem * item)
	{
		if (item == NULL)
		{
			return;
		}
		item->set_ts(this->ts);
		item->set_uid(this->uid);
		item->set_user_name(this->user_name);

		map<byte, uint32_t>::iterator itr = this->msg.begin();
		for (; itr != this->msg.end(); ++itr)
		{
			SysgemMsg::SysgemMsgData *data = item->add_data();
			if (data == NULL)
			{
				continue;
			}
			data->set_k(itr->first);
			data->set_v(itr->second);
		}

		vector<AwardInfo>::iterator rewardItr = this->reward.begin();
		for (; rewardItr != this->reward.end(); ++rewardItr)
		{
			SysgemMsg::SysgemMsgReward *data = item->add_reward();
			if (data == NULL)
			{
				continue;
			}
			data->set_t(rewardItr->type);
			data->set_id(rewardItr->id);
			data->set_c(rewardItr->count);
		}
	}
	bool operator==(uint32_t ts) const
	{
		return this->ts == ts;
	}
};

struct SystemMessageUserItem
{
	uint32_t uid;
	uint32_t ts;

	SystemMessageUserItem() :
			uid(0), ts(0)
	{
	}

};

enum SystemMessageType
{
	SystemMessageGate = 1,        // 闯过一个章节
	SystemMessageBuyBag = 2,      // 购买礼包
	SystemMessageBoatBag = 3,     // 跑商宝箱
	SystemMessageVip = 4,         // 购买VIP
	SystemMessageRob = 5,         // 掠夺
	SystemMessageBuySpecial = 6,  // 购买特别优惠
	SystemMessageTimeLimitBag = 7,// 限购礼包
	SystemMessageDeserveBag = 8,  // 超值宝库
	SystemMessageFirstCharge = 9, // 首充
	SystemMessageMax
};

enum SystemMessageDataPro
{
	SystemMessageDataProType = 1,
	SystemMessageDataProLevel = 2,
	SystemMessageDataProR1 = 3,
	SystemMessageDataProR2 = 4,
	SystemMessageDataProId = 5
};

class SystemMessage
{
public:
	virtual ~SystemMessage();
	static SystemMessage* getInstance()
	{
		static SystemMessage instance;
		return &instance;
	}
	bool onLogin(uint32_t uid);
	bool onHeartBeat(uint32_t uid);
	bool init();
	bool save();
	bool addGate(uint32_t uid, uint32_t level);
	bool addBuyBag(uint32_t uid, uint32_t id, const Award *award);
	bool addBoatBag(uint32_t uid, uint32_t id, const Award *award);
	bool addBuyVip(uint32_t uid, uint32_t id);
	bool addRob(uint32_t uid, uint32_t id, uint32_t res);
	bool addSpecial(uint32_t uid, uint32_t id, const Award *award);
	bool addTimeLimitBag(uint32_t uid, uint32_t id, const Award *award);
	bool addDeserveBag(uint32_t uid, uint32_t id);
	bool addFirstCharge(uint32_t uid, const Award *award);
	bool sendMsg(uint32_t uid);
protected:
	SystemMessage();
private:
	void getMessage(uint32_t ts, vector<SystemMessageSend> &datas);
	Json::Value parseJson(const map<uint32_t, uint32_t> &msg, const vector<AwardInfo> &reward);
	void parseNewUserGift(const map<uint32_t, uint32_t> &msg, const vector<AwardInfo> &reward);
private:
	list<SystemMessageInfo> m_data;
	map<uint32_t, uint32_t> m_user_items;
};

#endif /* SYSTEMMESSAGE_H_ */
