#ifndef DATAZHOUNIANQINGQIANDAO_H_
#define DATAZHOUNIANQINGQIANDAO_H_
#include "Kernel.h"

struct DataZhouNianQingQianDao
{
	unsigned total;
	int version;
	DataZhouNianQingQianDao() : total(0), version(0) {
	}
};


class CDataZhouNianQingQianDao
{
public:
	CDataZhouNianQingQianDao();
	virtual ~CDataZhouNianQingQianDao();
	int Init(const std::string &path, semdat sem=sem_zhounianqing_qiandao);
	int Add(int version, int point);
	int GetInfo(Json::Value & result);

	void Show();

protected:
	bool m_init;
	CShareMemory m_sh;
};




#endif /* DATAZHOUNIANQINGQIANDAO_H_ */
