/*
 * DataManager.h
 *
 *  Created on: 2019年4月19日
 *      Author: Administrator
 */

#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "AsyncDBInterface.h"
#include "AsyncDBManager.h"
#include "DataInc.h"

template<class _HANDLE, class _DBC, int _ID>
class DataManagerBase: public AsyncDBInterfaceBase {
private:
	int m_tableId;
	_HANDLE m_handle;
public:
	virtual ~DataManagerBase() {
	}
	DataManagerBase() {
		m_tableId = _ID;
	}
	virtual int RealAdd(DataPacket* packet) {
		_DBC data;
		if (!data.Decode(&packet->body)) {
			return R_ERR_DATA;
		}
		return m_handle.AddData(data);
	}
	virtual int RealSet(DataPacket* packet) {
		_DBC data;
		if (!data.Decode(&packet->body)) {
			return R_ERR_DATA;
		}
		return m_handle.SetData(data);
	}
	virtual int RealRep(DataPacket* packet) {
		_DBC data;
		if (!data.Decode(&packet->body)) {
			return R_ERR_DATA;
		}
		return m_handle.RepData(data);
	}
	virtual int RealDel(DataPacket* packet) {
		_DBC data;
		if (!data.Decode(&packet->body)) {
			return R_ERR_DATA;
		}
		return m_handle.DelData(data);
	}
	virtual int Add(const _DBC &data) {
		DataPacket sp;
		sp.m_tableId = m_tableId;
		sp.m_opId = AsyncDbAdd;
		if (!data.Encode(&sp.body)) {
			return R_ERROR;
		}
		AsyncDBManager::getInstance()->send(sp);
		return 0;
	}
	virtual int Set(const _DBC &data) {
		DataPacket sp;
		sp.m_tableId = m_tableId;
		sp.m_opId = AsyncDbSet;
		if (!data.Encode(&sp.body)) {
			return R_ERROR;
		}
		AsyncDBManager::getInstance()->send(sp);
		return 0;
	}
	virtual int Rep(const _DBC &data) {
		DataPacket sp;
		sp.m_tableId = m_tableId;
		sp.m_opId = AsyncDbRep;
		if (!data.Encode(&sp.body)) {
			return R_ERROR;
		}
		AsyncDBManager::getInstance()->send(sp);
		return 0;
	}
	virtual int Del(const _DBC &data) {
		DataPacket sp;
		sp.m_tableId = m_tableId;
		sp.m_opId = AsyncDbDel;
		if (!data.Encode(&sp.body)) {
			return R_ERROR;
		}
		AsyncDBManager::getInstance()->send(sp);
		return 0;
	}
	virtual int Get(uint32_t uid, _DBC &data) {
		return m_handle.GetData(uid, data);
	}
	virtual int Get(uint32_t uid, vector<_DBC> &datas) {
		return m_handle.GetData(uid, datas);
	}
	virtual void doRequest(DataPacket* packet) {
		int ret = 0;
		switch (packet->m_opId) {
		case AsyncDbAdd:
			ret = RealAdd(packet);
			break;
		case AsyncDbSet:
			ret = RealSet(packet);
			break;
		case AsyncDbRep:
			ret = RealRep(packet);
			break;
		case AsyncDbDel:
			ret = RealDel(packet);
			break;
		default:
			ret = R_ERR_PARAM;
			break;
		}
		if (0 != ret) {
			error_log("tid=%u,op=%u,ret=%d", packet->m_tableId, packet->m_opId, ret);
		}
	}
};

class DataBaseManager: public DataManagerBase<CDataBase, DataBase, DB_BASE>, public CSingleton<DataBaseManager> {
private:
	friend class CSingleton<DataBaseManager>;
	DataBaseManager(){}
};

class DataPosManager: public DataManagerBase<CDataPos, DataPos, DB_POS>, public CSingleton<DataPosManager> {
private:
	friend class CSingleton<DataPosManager>;
	DataPosManager(){}
};

class DataSkillManager: public DataManagerBase<CDataSkill, DataSkill, DB_SKILL>, public CSingleton<DataSkillManager> {
private:
	friend class CSingleton<DataSkillManager>;
	DataSkillManager(){}
};

class DataPayManager: public DataManagerBase<CDataPay, DataPay, DB_PAY>, public CSingleton<DataPayManager> {
private:
	friend class CSingleton<DataPayManager>;
	DataPayManager(){}
};

class DataRoleManager: public DataManagerBase<CDataRole, DataRole, DB_ROLE>, public CSingleton<DataRoleManager> {
private:
	friend class CSingleton<DataRoleManager>;
	DataRoleManager(){}
};

class DataMissionManager: public DataManagerBase<CDataMission, DataMission, DB_MISSION>, public CSingleton<DataMissionManager> {
private:
	friend class CSingleton<DataMissionManager>;
	DataMissionManager(){}
};

class DataAdvanceManager: public DataManagerBase<CDataAdvance, DataAdvance, DB_ADVANCE>, public CSingleton<DataAdvanceManager> {
private:
	friend class CSingleton<DataAdvanceManager>;
	DataAdvanceManager(){}
};

class DataEquipManager: public DataManagerBase<CDataEquip, DataEquip, DB_EQUIP>, public CSingleton<DataEquipManager> {
private:
	friend class CSingleton<DataEquipManager>;
	DataEquipManager(){}
};

class DataShenQiManager: public DataManagerBase<CDataShenQi, DataShenQi, DB_SHENQI>, public CSingleton<DataShenQiManager> {
private:
	friend class CSingleton<DataShenQiManager>;
	DataShenQiManager(){}
};

class DataBagExtendManager: public DataManagerBase<CDataBagExtend, DataBagExtend, DB_BAG_EXTEND>, public CSingleton<DataBagExtendManager> {
private:
	friend class CSingleton<DataBagExtendManager>;
	DataBagExtendManager(){}
};

class DataTreasureManager: public DataManagerBase<CDataTreasure, DataTreasure, DB_TREASURE>, public CSingleton<DataTreasureManager> {
private:
	friend class CSingleton<DataTreasureManager>;
	DataTreasureManager(){}
};

class DataForgeManager: public DataManagerBase<CDataForge, DataForge, DB_FORGE>, public CSingleton<DataForgeManager> {
private:
	friend class CSingleton<DataForgeManager>;
	DataForgeManager(){}
};

class DataAttrManager: public DataManagerBase<CDataAttr, DataAttr, DB_ATTR>, public CSingleton<DataAttrManager> {
private:
	friend class CSingleton<DataAttrManager>;
	DataAttrManager(){}
};
class DataRoleAttrManager: public DataManagerBase<CDataRoleAttr, DataRoleAttr, DB_ROLE_ATTR>, public CSingleton<DataRoleAttrManager> {
private:
	friend class CSingleton<DataRoleAttrManager>;
	DataRoleAttrManager(){}
};
class DataActiveManager: public DataManagerBase<CDataActive, DataActive, DB_ACTIVE>, public CSingleton<DataActiveManager> {
private:
	friend class CSingleton<DataActiveManager>;
	DataActiveManager() {}
};
#endif /* DATA_MANAGER_H_ */
