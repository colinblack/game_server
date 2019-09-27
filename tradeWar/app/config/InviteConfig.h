/*
 * InviteConfig.h
 *
 *  Created on: 2016-6-8
 *      Author: Administrator
 */

#ifndef INVITECONFIG_H_
#define INVITECONFIG_H_

#include "Kernel.h"
#include "CommData.h"

struct InviteLevelConfig
{
	uint32_t id;
	uint32_t level;
	uint32_t count;
	vector<AwardInfo> vAward;
	InviteLevelConfig()
	{
		id = 0;
		level = 0;
		count = 0;
		vAward.clear();
	}
};

class InviteConfig
{
private:
	InviteConfig();
public:
	~InviteConfig();
	static InviteConfig * getInstance()
	{
		static InviteConfig gc;
		return & gc;
	};
	bool init(const string & path);
	bool getConfig(uint32_t id, InviteLevelConfig & sConfig);
	vector<AwardInfo> & getDayAward(){return vdayAward;};
	vector<InviteLevelConfig> & getConfig(){return m_levels;};
private:
	vector<InviteLevelConfig> m_levels;
	vector<AwardInfo> vdayAward;
};

#endif /* INVITECONFIG_H_ */
