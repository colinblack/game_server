#ifndef __DATA_SECINC_H__
#define __DATA_SECINC_H__

#include "Kernel.h"

struct DataSecinc
{
	unsigned uid;
	unsigned sid;
	string   data;
};

class CDataSecinc : public CDataBaseDBC
{
public:
	CDataSecinc(int table = DB_SECINC) : CDataBaseDBC(table) {}

	/* 2014901 Ralf change to save activity
	int AddSecinc(unsigned uid, unsigned sid, const string &data);
	int SetSecinc(unsigned uid, unsigned sid, const string &data);
	int RemoveSecinc(unsigned uid, unsigned sid);
	*/

	int GetSecinc(unsigned uid, vector<DataSecinc> &datas);
	int ReplaceSecinc(unsigned uid, unsigned sid, const string &data);

	int GetSecinc(unsigned uid, unsigned sid, string &data);
	int RemoveSecinc(unsigned uid);
};

#endif
