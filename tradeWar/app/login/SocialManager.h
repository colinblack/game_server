/*
 * SocialManager.h
 *
 *  Created on: 2016-5-26
 *      Author: Administrator
 */

#ifndef SOCIAL_MANAGER_H_
#define SOCIAL_MANAGER_H_

#include "DataSocial.h"
#include "IManager.h"

class SocialManager: public IManager
{
public:
	SocialManager();
	~SocialManager();
	bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool onAccept(uint32_t uid, const string &pic);
	bool updatePic(uint32_t uid, const string &pic);
	const vector<DataSocial>& getData();
private:
	vector<DataSocial> m_data;
};

#endif /* SOCIAL_MANAGER_H_ */

