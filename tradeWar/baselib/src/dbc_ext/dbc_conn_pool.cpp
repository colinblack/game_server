/*=============================================================================
#  Author:          DanteZhu
#  Email:           dantezhu@vip.qq.com
#  FileName:        dbc_conn_pool.cpp
#  Version:         1.0
#  LastChange:      2010-01-17 10:46:46
#  Description:     DBC链接池管理
#  History:         
=============================================================================*/
#include "dbc_conn_pool.h"
#include <algorithm>
auto_ptr<CDBCConnPool> CDBCConnPool::m_auto_ptr;
CDBCConnPool * CDBCConnPool::_ins = NULL;
CDBCConnPool::CDBCConnPool()
{
	m_MaxConnNum = -1;
	m_auto_ptr = auto_ptr<CDBCConnPool>(this);
}
void CDBCConnPool::SetMaxConnNum(int num)
{
	if(num > m_MaxConnNum)
	{
		m_MaxConnNum = num;
	}
}
int CDBCConnPool::push_back(DBC::Server *pServer)
{
	int tempMaxNum = m_MaxConnNum;
	if(tempMaxNum<0)
	{
		tempMaxNum = 10;
	}

	list<DBC::Server*>::iterator findIt= find(m_pDBCConList.begin(),m_pDBCConList.end(),pServer);

	if(findIt != m_pDBCConList.end())
	{
		m_pDBCConList.erase(findIt);
	}
	m_pDBCConList.push_back(pServer);

	if(m_pDBCConList.size() > (unsigned int)tempMaxNum)
	{
		DBC::Server * p_Tmp = m_pDBCConList.front();
		p_Tmp->Close();
		m_pDBCConList.pop_front();
		return 1;
	}	
	return 0;
}
