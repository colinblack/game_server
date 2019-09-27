#ifndef DATACHONGBANGWANGZHE_H_
#define DATACHONGBANGWANGZHE_H_
#include "Kernel.h"

#define MAX_CHONGBANG_NUM 10
#define MAX_PERSON_ONE_CHONGBANG 10
#define NOW_PERSON_DISPLAY 5

struct ChongBangPerson
{
	unsigned uid,id,dehp,mobai,level,icon,ts;
	char name[1000];
	ChongBangPerson() {
		uid = mobai = id = level = dehp = icon = ts = 0;
		memset(name,0,sizeof(name));
	}
};
struct OneChongBang
{
	ChongBangPerson person[MAX_PERSON_ONE_CHONGBANG];
};
struct DataChongBangWangZhe
{
	OneChongBang chongbang[MAX_CHONGBANG_NUM];
};


class CDataChongBangWangZhe
{
public:
	CDataChongBangWangZhe();
	virtual ~CDataChongBangWangZhe();
	int Init(const std::string &path, semdat sem=sem_chongbangwangzhe);
	int SetUser(unsigned chongbangid, unsigned uid, unsigned id, unsigned level, unsigned dehp, unsigned icon, string name);
	int MoBai(unsigned chongbangid, unsigned uid);
	int GetInfo(unsigned chongbangid, Json::Value & result);

	void Show();

protected:
	bool m_init;
	CShareMemory m_sh;
};




#endif /* DATACHONGBANGWANGZHE_H_ */
