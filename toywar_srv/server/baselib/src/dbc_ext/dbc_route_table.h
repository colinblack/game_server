#ifndef _DBCROUTETAB_H_
#define _DBCROUTETAB_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "markupstl.h"
#include "dbcapi.h"

using namespace std;
typedef map<DBC::Server *, int, less<DBC::Server *> > DBCConnectMap;

//记录信息
struct UIN_DBC
{
	int iBeg_uin;
	int iEnd_uin;
	int iTableId;

	char sIP[18];
	char sPort[10];
	char sTable[30];
        char sProt[10];
	int  iTimeOut;
    int iMTimeOut;
	DBC::Server *pServer;
} ;
//内存头信息
struct HEARD_INFO
{
	int MIN_UIN;
	int MAX_UIN;
	int iMod;
	int iDiv;
	int iMaxnum;
	char sTable[30];
	int iTableId;
};
//批量接口记录信息
struct BATCH_DBC
{
	std::vector<int>  iUins;
	DBC::Server **pServer;
};

class CDBCRouteTable
{
public:




	CDBCRouteTable(char *xml );
	static CDBCRouteTable * GetInstance(char * xml);
	int init(char *xml_config);


	~CDBCRouteTable();

	static CDBCRouteTable * _pInstance;      //0 没有初始化

	int load_rout(const std::string  & sPath);
	int get_route(char *sTable,unsigned iUin,DBC::Server ** m_stServer);
	int get_route(int iTableId,unsigned iUin,DBC::Server ** m_stServer,
            bool isUseConf=false,  unsigned int  pn_MaxNum=100, char** ip = NULL);;
	//debug
	char * get_address(int iTableId,int iUin);
	//debug
	int get_route(int iTableId,unsigned iUin, char ** ip, unsigned& port);
	//批量接口
	int get_route_batch( char *sTable,std::vector<int>  iUin, std::vector<BATCH_DBC> vBatchTtc);
	string get_msg();
	int CheckConnectCount(int iTableId, int iUin, DBC::Server * mp_stServer,  unsigned int  pn_MaxNum);
	// 取 IP
	int get_ip(int iTableId,int iUin, string & ps_IP, unsigned int & pn_Port);
public:
	int MIN_UIN;
	int MAX_UIN;

	HEARD_INFO * m_pInfo;
	UIN_DBC    * m_pUinTtc ;

	vector<HEARD_INFO> m_vstHeardInfo;
	vector<UIN_DBC>    m_vstUinTtc;
	list<DBC::Server *>    mlp_DBCConList;   // DBC 连接 list
	DBCConnectMap          mc_DBCConMap;     // DBC 连接 map


	string sErrMsg;
	int iInitSuc;

};


#endif
