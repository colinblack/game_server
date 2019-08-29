#ifndef DATAEMAIL_H_
#define DATAEMAIL_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

enum EmailAttackFlag
{
	e_EmailAttackFlagNone = 0,   //无
	e_EmailAttackFlagSet = 1,    //有
	e_EmailAttackFlagGet = 2,    //已经领取
};

enum EmailPostFlag
{
	e_EmailPostFlagRecv = 1,   //接收
	e_EmailPostFlagSend = 2,   //发送
	e_EmailPostFlagRemove = 3, //删除
};

struct DataEmail {
	uint32_t uid;
	uint32_t id;
	uint32_t opposite_uid;
	string title;
	string text;
	string from_name;
	string to_name;
	uint32_t post_ts;
	uint32_t read_ts;
	string attachments;
	byte attach_flag;
	byte post_flag;

	DataEmail() {
		uid = 0;
		id = 0;
		opposite_uid = 0;
		title = "";
		text = "";
		from_name = "";
		to_name = "";
		post_ts = 0;
		read_ts = 0;
		attachments = "";
		attach_flag = 0;
		post_flag = 1;
	}

	inline bool operator==(uint32_t id) const {
		return this->id == id;
	}
};

class CDataEmail: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataEmail(int table = DB_EMAIL) : CDataBaseDBC(table) {
	}
	virtual ~CDataEmail() {
	}
	int AddEmail(const DataEmail &dataEmail);
	int GetEmail(uint32_t uid, uint32_t id, DataEmail &dataEmail);
	int GetEmails(uint32_t uid, vector<DataEmail> &dataEmail);
	int RemoveEmail(uint32_t uid, uint32_t id);
	int UpdateEmail(const DataEmail &dataEmail);
	int syncAddEmail(const DataEmail &dataEmail);
	virtual void doRequest(CNetPacket* packet);
	int RealAddEmail(CNetPacket* packet);
	int RealUpdateEmail(CNetPacket* packet);
	int RealRemoveEmail(CNetPacket* packet);
};

#endif
