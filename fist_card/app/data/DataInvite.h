/*
 * DataInvite.h
 *
 *  Created on: 2018年9月25日
 *      Author: colin
 */

#ifndef APP_DATA_DATAINVITE_H_
#define APP_DATA_DATAINVITE_H_

#include "Kernel.h"

struct DataInvite
{
	uint32_t  uid;
	uint32_t id;
	char name[BASE_NAME_LEN];//名字
	char fig[BASE_FIG_LEN];//头像ur

	DataInvite()
	{
		uid = 0;
		id  = 0;
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	void SetMessage(User::InivteUserInfoCPP* msg) const
	{
		msg->set_uid(id);
		msg->set_name(name);
		msg->set_fig(fig);

	}
};


class CDataInvite :public DBCBase<DataInvite, DB_INVITE>
{
public:
	virtual int Get(DataInvite &data);
	virtual int Get(vector<DataInvite> &data);
	virtual int Add(DataInvite &data);
	virtual int Set(DataInvite &data);
	virtual int Del(DataInvite &data);
};



#endif /* APP_DATA_DATAINVITE_H_ */
