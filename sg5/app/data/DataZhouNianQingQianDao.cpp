#include "DataZhouNianQingQianDao.h"
#include "LogicInc.h"

CDataZhouNianQingQianDao::CDataZhouNianQingQianDao() {
	m_init = false;
}
CDataZhouNianQingQianDao:: ~CDataZhouNianQingQianDao(){

}

int CDataZhouNianQingQianDao::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(DataZhouNianQingQianDao),
			SEM_ID(sem,semgroup,semserver))) {
		error_log("[init_zhounianqing_qiandao_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if (!m_sh.HasInit()) {
		DataZhouNianQingQianDao *pTable = (DataZhouNianQingQianDao *) m_sh.GetAddress();
		memset(pTable, 0, sizeof(*pTable));
		pTable->version = -1;
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataZhouNianQingQianDao::Add(int version, int count)
{
	DataZhouNianQingQianDao *pTable = (DataZhouNianQingQianDao *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	if (pTable->version != version)
	{
		pTable->version = version;
		pTable->total = 0;
	}

	pTable->total += count;
	return 0;
}

int CDataZhouNianQingQianDao::GetInfo(Json::Value & result)
{
	DataZhouNianQingQianDao *pTable = (DataZhouNianQingQianDao *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[GetInfo_fail]");
		return R_ERR_DB;
	}
	result["total"] = pTable->total;
	result["version"] = pTable->version;
	return 0;
}

void CDataZhouNianQingQianDao::Show()
{
	DataZhouNianQingQianDao *pTable = (DataZhouNianQingQianDao *) m_sh.GetAddress();
	cout << "total=" << pTable->total << " version=" << pTable->version << endl;
}
