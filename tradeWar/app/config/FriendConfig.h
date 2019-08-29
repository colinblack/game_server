/*
 * FriendConfig.h
 *
 *  Created on: 2017年11月15日
 *      Author: Administrator
 */

#ifndef FRIEND_CONFIG_H_
#define FRIEND_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

class FriendConfig
{
public:
	static FriendConfig * getInstance(){
		static FriendConfig ins;
		return &ins;
	}
	virtual ~FriendConfig();
	bool init(const string &path);
	uint32_t getMaxSendHelp() const
	{
		return max_send_help;
	}
	uint32_t getMaxRecvHelp() const
	{
		return max_recv_help;
	}
	uint32_t getMaxSendGift() const
	{
		return max_send_gift;
	}
	uint32_t getMaxRecvGift() const
	{
		return max_recv_gift;
	}
	const Award* getReward(uint32_t id) const
	{
		map<uint16_t, Award>::const_iterator itr = m_reward.find(id);
		if (itr == m_reward.end())
		{
			return NULL;
		}
		return &(itr->second);
	}
protected:
	FriendConfig();
private:
	uint16_t max_send_help;
	uint16_t max_recv_help;
	uint16_t max_send_gift;
	uint16_t max_recv_gift;
	map<uint16_t, Award> m_reward;
};

#endif /* FRIEND_CONFIG_H_ */
