#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "markupstl.h"
#include "route.h"

char* CRoute::OLD_TAG[3] = { "content", "uin_dbc", "route" };
char* CRoute::NEW_TAG[3] = { "content", "route", "node" };


int CRoute::initialize( const char* path, char** tags )
{
	CMarkupSTL XMLConf;

	if ( !XMLConf.Load( path ) )
	{
		return -1;
	}

	if ( !XMLConf.FindElem( tags[0] ) )
	{
		return -2;
	}
	XMLConf.IntoElem();

	if ( !XMLConf.FindElem( tags[1] ) )
	{
		return -3;
	}

	m_head.mod = atoi( XMLConf.GetAttrib("mod").c_str() );
	m_head.div = atoi( XMLConf.GetAttrib("div").c_str() );
	m_head.tout = atoi( XMLConf.GetAttrib("timeout").c_str() );
	m_head.tout_usec = atoi( XMLConf.GetAttrib("timeout_usec").c_str() ) * 1000;

	std::string sTable= XMLConf.GetAttrib("table");

	int index = 0;
	m_info.resize( 0 );
	while( XMLConf.FindChildElem( tags[2] ) )
	{
		_INFO info;
		info.index = index++;
		info.begin = atoi( XMLConf.GetChildAttrib("begin").c_str() );
		info.end = atoi( XMLConf.GetChildAttrib("end").c_str() );
		snprintf( info.ip, sizeof(info.ip), "%s", XMLConf.GetChildAttrib("ip").c_str() );
		info.port = atoi( XMLConf.GetChildAttrib("port").c_str() );
		snprintf( info.table,sizeof(info.table),"%s", sTable.c_str() );
		snprintf( info.prot, sizeof(info.prot), "%s", XMLConf.GetChildAttrib("prot").c_str() );
		if ( 0 == info.prot[0] )
			snprintf( info.prot, sizeof(info.prot), "%s", "tcp" );
		m_info.push_back( info );
	}
	return 0;
}

int CRoute::InitLogicServer( const char* path)
{
	CMarkupSTL XMLConf;

	ms_ConfigInfo.mn_BlockNum =0;
	ms_ConfigInfo.mn_ServerTotalNum =0;
	ms_ConfigInfo.mn_ServerNum =0;
	ms_ConfigInfo.mn_LastServerNum =0;

	if ( !XMLConf.Load( path ) )
	{
		return -1;
	}

	if ( !XMLConf.FindElem("content") )
	{
		return -2;
	}
	XMLConf.IntoElem();

	if ( !XMLConf.FindElem("route_info") )
	{
		return -3;
	}
	ms_ConfigInfo.mn_BlockNum = atoi( XMLConf.GetAttrib("block_num").c_str() );
	ms_ConfigInfo.mn_ServerNum = atoi( XMLConf.GetAttrib("server_num_in_block").c_str() );


	if ( !XMLConf.FindElem("server_list") )
	{
		return -4;
	}

	m_info.clear();
	int ln_Idx = 0;
	while( XMLConf.FindChildElem("backend_server") )
	{
		_INFO info;

		info.index = ln_Idx++;
		snprintf( info.ip, sizeof(info.ip), "%s", XMLConf.GetChildAttrib("ip").c_str() );
		info.port = atoi( XMLConf.GetChildAttrib("port").c_str() );
		snprintf( info.prot, sizeof(info.prot), "%s", XMLConf.GetChildAttrib("prot").c_str() );
		if ( 0 == info.prot[0] )
			snprintf( info.prot, sizeof(info.prot), "%s", "tcp" );

		m_info.push_back( info );
	}

	ms_ConfigInfo.mn_ServerTotalNum = m_info.size();
	if( ms_ConfigInfo.mn_BlockNum * ms_ConfigInfo.mn_ServerNum > ms_ConfigInfo.mn_ServerTotalNum) {
		snprintf(m_errMsg,sizeof(m_errMsg),"server size overflow block %u total %u servernum %u",
			ms_ConfigInfo.mn_BlockNum, ms_ConfigInfo.mn_ServerTotalNum,
			ms_ConfigInfo.mn_ServerNum);
		return -5;
	}

	// 把剩余的 server 给最后一段用
	ms_ConfigInfo.mn_LastServerNum = ms_ConfigInfo.mn_ServerNum
			+ (ms_ConfigInfo.mn_ServerTotalNum - ms_ConfigInfo.mn_ServerNum * ms_ConfigInfo.mn_BlockNum);


	// error_log("GETSIZE block %u total %u servernum %u lastservernum %u",
	// 	ms_ConfigInfo.mn_BlockNum, ms_ConfigInfo.mn_ServerTotalNum,
	// 	ms_ConfigInfo.mn_ServerNum, ms_ConfigInfo.mn_LastServerNum);
    //
	// for(unsigned int ln_Index = 0; ln_Index < m_info.size(); ++ln_Index) {
	// 	error_log("id %u ip %s port %u prot %s",
	// 		m_info[ln_Index].index, m_info[ln_Index].ip, m_info[ln_Index].port,
	// 		m_info[ln_Index].prot );
	// }

	return 0;
}

CRoute::_INFO* CRoute::GetRouteInfo( int code )
{
	int route_index = int(code/m_head.div)%m_head.mod;
	for ( unsigned i=0; i<m_info.size(); i++ )
	{
		if ( route_index >= m_info[i].begin && route_index <= m_info[i].end )
		{
			return &( m_info[i] );
		}
	}
	return NULL;
}

int CRoute::RouteID(int uid)
{
	CRoute::_INFO* info = GetRouteInfo(uid);
	if(!info) return 0;

	return info->index;
}
