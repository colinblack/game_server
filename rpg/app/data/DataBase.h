#ifndef DATA_BASE_H_
#define DATA_BASE_H_

#include "Kernel.h"

struct DataBase {
	uint32_t uid;
	uint32_t register_time;
	uint32_t login_time;
	uint32_t offline_time;
	uint32_t exp;
	uint32_t guild_id;
	uint32_t login_days;
	uint16_t level;
	uint16_t hang;
	uint8_t  hang_power;
	uint8_t  role_num;
	uint8_t  main_role;
	string   open_id;

	DataBase() {
		uid = 0;
		register_time = 0;
		login_time = 0;
		offline_time = 0;
		exp = 0;
		guild_id = 0;
		login_days = 0;
		level = 0;
		hang = 0;
		hang_power = 0;
		role_num = 0;
		main_role = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, register_time);
		PACKET_ENCODE(UInt32, login_time);
		PACKET_ENCODE(UInt32, offline_time);
		PACKET_ENCODE(UInt32, exp);
		PACKET_ENCODE(UInt32, guild_id);
		PACKET_ENCODE(UInt32, login_days);
		PACKET_ENCODE(UInt16, level);
		PACKET_ENCODE(UInt16, hang);
		PACKET_ENCODE(Byte, hang_power);
		PACKET_ENCODE(Byte, role_num);
		PACKET_ENCODE(Byte, main_role);
		PACKET_ENCODE(String, open_id);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, register_time);
		PACKET_DECODE(UInt32, login_time);
		PACKET_DECODE(UInt32, offline_time);
		PACKET_DECODE(UInt32, exp);
		PACKET_DECODE(UInt32, guild_id);
		PACKET_DECODE(UInt32, login_days);
		PACKET_DECODE(UInt16, level);
		PACKET_DECODE(UInt16, hang);
		PACKET_DECODE(Byte, hang_power);
		PACKET_DECODE(Byte, role_num);
		PACKET_DECODE(Byte, main_role);
		PACKET_DECODE(String, open_id);
		return true;
	}
};

class CDataBase: public CDataBaseDBC {
public:
	CDataBase(int table = DB_BASE) : CDataBaseDBC(table) {
	}
	virtual ~CDataBase();
	int AddData(const DataBase &data);
	int SetData(const DataBase &data);
	int RepData(const DataBase &data);
	int DelData(const DataBase &data);
	int GetData(uint32_t uid, DataBase &data);
	int GetData(uint32_t uid, vector<DataBase> &datas);
};

#endif /* DATA_BASE_H_ */
