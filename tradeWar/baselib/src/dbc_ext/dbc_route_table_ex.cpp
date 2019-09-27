/*=============================================================================
#  Author:          DanteZhu
#  Email:           dantezhu@vstrIp.qq.com
#  FileName:        dbc_route_table_ex.cpp
#  Version:         1.0
#  LastChange:      2010-01-26 10:36:23
#  DescrstrIption:     
#  History:         
=============================================================================*/
#include "dbc_route_table_ex.h"
#include <stdio.h>
using namespace std;
//=============================================================================
/*CDBCRouteInfo{{{*/
CDBCRouteInfo::CDBCRouteInfo()
{
	m_Div_Num=1;
	m_Mod_Num=100;
}
CDBCRouteInfo::~CDBCRouteInfo()
{
	FreeSelf();
}
int CDBCRouteInfo::Init(int div,int mod)
{
	m_Div_Num = div;
	m_Mod_Num = mod;
	return 0;
}
void CDBCRouteInfo::push_back(DBCRouteNode node)
{
	m_vec_host.push_back(node);
}
int CDBCRouteInfo::GetClient(unsigned int iUin,DBC::Server *&pServer)
{
	unsigned int _idx ;
	_idx = iUin/(this->m_Div_Num)%(this->m_Mod_Num);
	for(unsigned int i = 0;i<m_vec_host.size();++i)
	{
		if(_idx>=m_vec_host[i].beginUin && _idx<=m_vec_host[i].endUin)
		{
			pServer = m_vec_host[i].pServer;

			if(CDBCConnPool::Ins() == NULL)
			{
				return -2;
			}

			CDBCConnPool::Ins()->push_back(pServer);

			return 0;
		}
	}
	return -1;
}
int CDBCRouteInfo::GetHostInfo(unsigned int iUin,DBCRouteNode& node)
{
	unsigned int _idx ;
	_idx = iUin/(this->m_Div_Num)%(this->m_Mod_Num);
	for(unsigned int i = 0;i<m_vec_host.size();++i)
	{
		if(_idx>=m_vec_host[i].beginUin && _idx<=m_vec_host[i].endUin)
		{
			node = m_vec_host[i];

			DBC::Server * pServer = m_vec_host[i].pServer;

			if(CDBCConnPool::Ins() == NULL)
			{
				return -2;
			}

			CDBCConnPool::Ins()->push_back(pServer);
			return 0;
		}
	}
	return -1;
}
void CDBCRouteInfo::FreeSelf()
{
	for(vector<DBCRouteNode>::iterator it=m_vec_host.begin();it!=m_vec_host.end();++it)
	{
		if(it->pServer)
		{
			it->pServer->Close();
			delete it->pServer;
		}
	}
}
/*}}}*/
//=============================================================================
/*CDBCRouteMng{{{*/
auto_ptr<CDBCRouteMng> CDBCRouteMng::m_auto_ptr;
CDBCRouteMng * CDBCRouteMng::_ins = NULL;
CDBCRouteMng* CDBCRouteMng::Ins()
{
	if ( !_ins )
	{
		try
		{
			_ins = new CDBCRouteMng();
		}
		catch(...)
		{
			return NULL;
		}
	}
	return _ins;
}
CDBCRouteMng::CDBCRouteMng()
{
	m_auto_ptr = auto_ptr<CDBCRouteMng>(this);
	m_StrErrMsg[0]='\0';
}
CDBCRouteMng::~CDBCRouteMng()
{/*{{{*/
	for(map<string,CDBCRouteInfo*>::iterator it = m_MapDBCRoute.begin();it!=m_MapDBCRoute.end();++it)
	{
		if(it->second)
		{
			delete it->second;
		}
	}
}/*}}}*/
int CDBCRouteMng::GetClient(string strFilePath,unsigned int iUin,DBC::Server *&pServer)
{/*{{{*/
	if(m_MapDBCRoute.find(strFilePath)==m_MapDBCRoute.end())
	{
		return -1;
	}
	CDBCRouteInfo * routeInfo = m_MapDBCRoute[strFilePath];
	return routeInfo->GetClient(iUin,pServer);
}/*}}}*/
int CDBCRouteMng::GetHostInfo(string strFilePath,unsigned int iUin,DBCRouteNode& node)
{/*{{{*/
	if(m_MapDBCRoute.find(strFilePath)==m_MapDBCRoute.end())
	{
		return -1;
	}
	CDBCRouteInfo * routeInfo = m_MapDBCRoute[strFilePath];
	return routeInfo->GetHostInfo(iUin,node);
}/*}}}*/
int CDBCRouteMng::AddNewRoute(string strFilePath)
{/*{{{*/
	if(m_MapDBCRoute.find(strFilePath)!=m_MapDBCRoute.end())
	{
		return 0;
	}
	CMarkupSTL XMLConf;
	if( !XMLConf.Load(strFilePath.c_str())) {
		snprintf(m_StrErrMsg,DBCROUTETABLEEX_MAXERRLEN,"%s path err",strFilePath.c_str());
		return -1;
	}
	if( !XMLConf.FindElem("content")) {
		snprintf(m_StrErrMsg,DBCROUTETABLEEX_MAXERRLEN,"%s node 'content' not find",strFilePath.c_str());
		return -2;
	}
	XMLConf.IntoElem();

	string strTable;

	CDBCRouteInfo *routeInfo = NULL;
	try
	{
		routeInfo = new CDBCRouteInfo();
	}
	catch(...)
	{
		snprintf(m_StrErrMsg,DBCROUTETABLEEX_MAXERRLEN,"CDBCRouteInfo new error");
		return -3;
	}
	m_MapDBCRoute[strFilePath]=routeInfo;//导入

	if( !XMLConf.FindElem("uin_dbc") ) {
		snprintf(m_StrErrMsg,DBCROUTETABLEEX_MAXERRLEN,"%s node 'uin_dbc' not find",strFilePath.c_str());
		delete routeInfo;
		return -4;
	}else{
		strTable = XMLConf.GetAttrib("table");
		routeInfo->Init(atoi(XMLConf.GetAttrib("div").c_str()),atoi(XMLConf.GetAttrib("mod").c_str()));

		CDBCConnPool::Ins()->SetMaxConnNum(atoi(XMLConf.GetAttrib("maxnum").c_str()));
	}

	while(XMLConf.FindChildElem("route") )
	{
		DBCRouteNode routeNode;
		routeNode.beginUin = atoi(XMLConf.GetChildAttrib("begin").c_str());
		routeNode.endUin = atoi(XMLConf.GetChildAttrib("end").c_str());

		routeNode.strIp = XMLConf.GetChildAttrib("ip");
		routeNode.strPort = XMLConf.GetChildAttrib("port");

		// spport udp protocol
		if(XMLConf.GetChildAttrib("prot").size() > 0)
			routeNode.strProtocol = XMLConf.GetChildAttrib("prot");
		else
			routeNode.strProtocol = XMLConf.GetChildAttrib("tcp");

		routeNode.strTable = strTable;

		routeNode.iMTimeOut = atoi(XMLConf.GetChildAttrib("mtimeout").c_str());
		routeNode.iTimeOut = atoi(XMLConf.GetChildAttrib("timeout").c_str());

		DBC::Server *stServer = NULL;
		try
		{
			stServer = new DBC::Server;
		}
		catch(...)
		{
			snprintf(m_StrErrMsg,DBCROUTETABLEEX_MAXERRLEN,"DBC new error");
			//只要return 就要删除之前new的
			delete routeInfo;
			return -5;
		}
		stServer->SetTableName(routeNode.strTable.c_str());

		char addr[128] = {0};
		snprintf(addr, sizeof(addr), "%s:%s/%s", routeNode.strIp.c_str(), routeNode.strPort.c_str(), routeNode.strProtocol.c_str());

		stServer->SetAddress(addr);
		if (routeNode.iMTimeOut != 0)
		{
			stServer->SetMTimeout(routeNode.iMTimeOut);
		}
		else
		{
			stServer->SetTimeout(routeNode.iTimeOut);
		}
		stServer->IntKey();

		routeNode.pServer=stServer;
		routeInfo->push_back(routeNode);
	}
	return 0;

}/*}}}*/
/*}}}*/
//=============================================================================
