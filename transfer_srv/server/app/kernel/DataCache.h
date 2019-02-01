/*
 * DataCache.h
 *
 *  Created on: 2012-3-5
 *      Author: dada
 */

#ifndef DATACACHE_H_
#define DATACACHE_H_

#include "Kernel.h"

template<typename DbClass, typename KeyType, typename DataType>
class CDataCache
{
public:

	int AddData(KeyType key, const DataType &data);
	int SetData(KeyType key, const DataType &data);
	int GetData(KeyType key, DataType &data);
	int RemoveData(KeyType key);

	int Commit();	//提交修改
	int Reset();	//提交并清空缓存

private:
	DbClass m_db;
	map<KeyType, DataType> m_cache;
	vector<KeyType> m_modifyList;
};

#endif /* DATACACHE_H_ */
