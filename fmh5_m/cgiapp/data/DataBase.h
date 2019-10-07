#ifndef CGIAPP_DATA_DATABASE_H_
#define CGIAPP_DATA_DATABASE_H_
#include "Kernel.h"

struct DataBase{
	uint32_t uid;
	char name[BASE_NAME_LEN];//名字
	char fig[BASE_FIG_LEN];//头像url
	uint32_t level;//等级
	uint32_t cash;//二级货币
	uint32_t blue_info; // 蓝钻信息
	uint32_t flag;	// 标志位
	uint32_t prosperity;//繁荣度
	uint32_t accthumbsup;//累积被点赞
	uint32_t viplevel;//vip等级
	uint32_t register_time;//注册时间
	uint32_t last_login_time;//上次登录时间
	DataBase(){
		uid = 0;
		level = 0;
		cash = 0;
		blue_info = 0;
		flag = 0;
		prosperity = 0;
		accthumbsup = 0;
		viplevel = 0;
		register_time = 0;
		last_login_time = 0;
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}
};

class CDataBase :public CDataBaseDBC
{
public:
	CDataBase(int table = DB_BASE) : CDataBaseDBC(table) {}
	virtual int Get(DataBase &data);
	virtual int Add(DataBase &data);
	virtual int Set(DataBase &data);
	virtual int Del(DataBase &data);
};

#endif /* CGIAPP_DATA_DATABASE_H_ */
