#include "DataChongBangWangZhe.h"
#include "LogicInc.h"
#include "DataUserBasic.h"

CDataChongBangWangZhe::CDataChongBangWangZhe() {
	m_init = false;
}
CDataChongBangWangZhe:: ~CDataChongBangWangZhe(){

}

int CDataChongBangWangZhe::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(DataChongBangWangZhe),
			SEM_ID(sem,semgroup,semserver))) {
		error_log("[init_chongbang_wangzhe_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if (!m_sh.HasInit()) {
		DataChongBangWangZhe *pTable = (DataChongBangWangZhe *) m_sh.GetAddress();
		memset(pTable, 0, sizeof(*pTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataChongBangWangZhe::SetUser(unsigned chongbangid, unsigned uid, unsigned id, unsigned level, unsigned dehp, unsigned icon, string name)
{
	DataChongBangWangZhe *pTable = (DataChongBangWangZhe *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	OneChongBang & bang = pTable->chongbang[chongbangid-1];
	for (int i=0;i<NOW_PERSON_DISPLAY;i++)
	{
		if (bang.person[i].uid == uid)
		{
			ChongBangPerson temp;
			memcpy(&temp,&(bang.person[i]),sizeof(ChongBangPerson));
			temp.ts = Time::GetGlobalTime();
			for (int j=i;j>0;j--)
			{
				memcpy(&(bang.person[j]),&(bang.person[j-1]),sizeof(ChongBangPerson));
			}
			memcpy(&(bang.person[0]),&temp,sizeof(ChongBangPerson));
			return 0;
		}
	}
	//玩家未出现在近5期榜
	for (int j=NOW_PERSON_DISPLAY;j>0;j--)
	{
		memcpy(&(bang.person[j]),&(bang.person[j-1]),sizeof(ChongBangPerson));
	}
	bang.person[0].ts = Time::GetGlobalTime();
	bang.person[0].mobai = 0;
	bang.person[0].uid = uid;
	bang.person[0].id = id;
	bang.person[0].dehp = dehp;
	bang.person[0].level = level;
	bang.person[0].icon = icon;
	strcpy(bang.person[0].name,name.c_str());
	return 0;
}

int CDataChongBangWangZhe::MoBai(unsigned chongbangid, unsigned uid)
{
	DataChongBangWangZhe *pTable = (DataChongBangWangZhe *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[MoBai_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	OneChongBang & bang = pTable->chongbang[chongbangid-1];
	for (int i=0;i<NOW_PERSON_DISPLAY;i++)
		if (bang.person[i].uid == uid)
		{
			bang.person[i].mobai++;
			return 0;
		}
	return R_ERR_NO_DATA;
}

int CDataChongBangWangZhe::GetInfo(unsigned chongbangid, Json::Value & result)
{
	DataChongBangWangZhe *pTable = (DataChongBangWangZhe *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[GetInfo_fail]");
		return R_ERR_DB;
	}
	OneChongBang & bang = pTable->chongbang[chongbangid-1];
	CDataUserBasic dbUser;
	for (int i=0;i<NOW_PERSON_DISPLAY;i++)
	{
		if (bang.person[i].uid)
		{
			Json::Value temp;
			temp["uid"] = bang.person[i].uid;
			temp["id"] = bang.person[i].id;
			temp["dehp"] = bang.person[i].dehp;
			temp["mobai"] = bang.person[i].mobai;
			temp["ts"] = bang.person[i].ts;
			temp["level"] = bang.person[i].level;
			string userName;
			dbUser.GetUserName(bang.person[i].uid, OpenPlatform::GetType(), userName);
			temp["name"] = userName;
			temp["icon"] = bang.person[i].icon;
			temp["heroname"] = string(bang.person[i].name);
			result.append(temp);
		}
		else return 0;
	}
	return 0;
}

void CDataChongBangWangZhe::Show()
{
	DataChongBangWangZhe *pTable = (DataChongBangWangZhe *) m_sh.GetAddress();
	for (unsigned chongbangid = 0;chongbangid <=5;chongbangid++)
	{
		cout << "chongbangid" << chongbangid << endl;
		for (unsigned i=0;i<MAX_PERSON_ONE_CHONGBANG;i++)
		{
			cout << pTable->chongbang[chongbangid].person[i].uid << " " << pTable->chongbang[chongbangid].person[i].mobai << " "
					<< pTable->chongbang[chongbangid].person[i].ts << endl;

		}
	}
}
