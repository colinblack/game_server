#include "dbc_route_table.h"
#include "trans.h"
#include "commlog.h"
CDBCRouteTable * CDBCRouteTable::_pInstance = 0;

CDBCRouteTable::CDBCRouteTable(char *xml)
{
	MIN_UIN=0;
	MAX_UIN=0;
	m_vstUinTtc.clear();
	m_vstHeardInfo.clear();
	mlp_DBCConList.clear();
	m_pInfo=NULL;
	m_pUinTtc=NULL;
	sErrMsg.clear();

	iInitSuc=init(xml);
}
CDBCRouteTable::~CDBCRouteTable()
{}

int CDBCRouteTable::init(char * xml_config)
{
	CMarkupSTL XMLConf;
	if( !XMLConf.Load(xml_config)) {
		sErrMsg= string(xml_config)+" not find";
		return -1;
	}
	if( !XMLConf.FindElem("content") ){
		sErrMsg="node 'content' not find";
		return -2;
	}
	XMLConf.IntoElem();

	if( !XMLConf.FindElem("system") ) {
		MIN_UIN =10;
		MAX_UIN =2000000000;
	}else{
		MIN_UIN =atoi(XMLConf.GetAttrib("minuin").c_str());
		MAX_UIN =atoi(XMLConf.GetAttrib("maxuin").c_str());
	}

	if( !XMLConf.FindElem("route_list") ){
		sErrMsg="node 'route_list' not find";
		return -3;
	}
	while(XMLConf.FindChildElem("route"))
	{
		int iRet = load_rout(XMLConf.GetChildAttrib("file"));
		if (iRet!=0) 
			error_log("CDBCRouteTable::init() err:file=%s ", XMLConf.GetChildAttrib("file").c_str());
	}
	return 0;
}

int CDBCRouteTable::load_rout(const std::string  & sPath)
{
	CMarkupSTL XMLConf;
	if( !XMLConf.Load(sPath.c_str())) {
		sErrMsg=sPath+" path err";
		return -10;
	}
	if( !XMLConf.FindElem("content")) {
		sErrMsg=sPath+" node 'content' not find";
		return -11;
	}
	XMLConf.IntoElem();

	string sTable;
	int iTableId,keyType;
	if( !XMLConf.FindElem("uin_dbc") ) {
		sErrMsg=sPath+" node 'uin_dbc' not find";
		return -12;
	}else{
		HEARD_INFO stHeardInfo;

		stHeardInfo.iMod  =atoi(XMLConf.GetAttrib("mod").c_str());
		stHeardInfo.iDiv  =atoi(XMLConf.GetAttrib("div").c_str());
		stHeardInfo.iMaxnum=atoi(XMLConf.GetAttrib("maxnum").c_str());

		sTable = XMLConf.GetAttrib("table");
		iTableId = atoi(XMLConf.GetAttrib("id").c_str());
		keyType = atoi(XMLConf.GetAttrib("key_type").c_str());

		stHeardInfo.iTableId = iTableId;
		snprintf(stHeardInfo.sTable ,sizeof(stHeardInfo.sTable), "%s",sTable.c_str());

		m_vstHeardInfo.push_back(stHeardInfo);
	}

	while(XMLConf.FindChildElem("route") )
	{
		UIN_DBC stUinTtc;
		stUinTtc.iBeg_uin =atoi(XMLConf.GetChildAttrib("begin").c_str());
		stUinTtc.iEnd_uin =atoi(XMLConf.GetChildAttrib("end").c_str());
		stUinTtc.iTableId =iTableId;

		snprintf(stUinTtc.sIP   ,sizeof(stUinTtc.sIP),   "%s",XMLConf.GetChildAttrib("ip").c_str());
		snprintf(stUinTtc.sPort ,sizeof(stUinTtc.sPort), "%s",XMLConf.GetChildAttrib("port").c_str());

		// spport udp protocol
		if(XMLConf.GetChildAttrib("prot").size() > 0)
			snprintf(stUinTtc.sProt, sizeof(stUinTtc.sProt), "%s", XMLConf.GetChildAttrib("prot").c_str());
		else
			snprintf(stUinTtc.sProt, sizeof(stUinTtc.sProt), "%s", "tcp");

		snprintf(stUinTtc.sTable,sizeof(stUinTtc.sTable),"%s",sTable.c_str());

        stUinTtc.iMTimeOut = atoi(XMLConf.GetChildAttrib("mtimeout").c_str());
        stUinTtc.iTimeOut = atoi(XMLConf.GetChildAttrib("timeout").c_str());

		DBC::Server *stServer = new DBC::Server;
		stServer->SetTableName(stUinTtc.sTable);

		char addr[128] = {0};
		snprintf(addr, sizeof(addr), "%s:%s/%s", stUinTtc.sIP, stUinTtc.sPort, stUinTtc.sProt);

		stServer->SetAddress(addr);
        if (stUinTtc.iMTimeOut != 0)
        {
            stServer->SetMTimeout(stUinTtc.iMTimeOut);
        }
        else
        {
            stServer->SetTimeout(stUinTtc.iTimeOut);
        }
        if(keyType == DBC::KeyTypeString){
        	stServer->StringKey();
        }else{
        	stServer->IntKey();
        }


		stUinTtc.pServer=stServer;
		m_vstUinTtc.push_back(stUinTtc);
	}
	return 0;
}

int CDBCRouteTable::get_route(int iTableId, unsigned iUin, char ** ip, unsigned& port)
{
	if (iInitSuc !=0)return -1;
	if (iTableId<0)
	{
		sErrMsg = string("err: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::UTOS(iUin);
		return -2;
	}
	int iModUin =0 ;
	bool bFlag=false;
	for (vector<HEARD_INFO>::iterator it=m_vstHeardInfo.begin(); it!=m_vstHeardInfo.end();it++)
	{
		if ( (it->iTableId)==iTableId )
		{
			iModUin =(iUin/it->iDiv )%(it->iMod);
			bFlag=true;
			break;
		}
	}
	if (!bFlag)
	{
		sErrMsg = string("err table id ") + CTrans::ITOS(iTableId);
		error_log("get_route() err:table id=%d ", iTableId);
		return -3;
	}

	for (std::vector<UIN_DBC>::iterator it=m_vstUinTtc.begin(); it!=m_vstUinTtc.end();it++)
	{
		if( (it->iTableId == iTableId ) && (iModUin >= it->iBeg_uin)  && (iModUin <= it->iEnd_uin) )
		{
			*ip  = it->sIP;
			port = atoi(it->sPort);
			return 0;
		}
	}

	sErrMsg = string("not found: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::UTOS(iUin);
	return -4;
}

int CDBCRouteTable::get_route(char * sTable,unsigned iUin,DBC::Server **m_stServer)
{
	if (iInitSuc !=0)return -1;

	int iModUin =-100 ;
	for (vector<HEARD_INFO>::iterator it=m_vstHeardInfo.begin(); it!=m_vstHeardInfo.end();it++)
	{
		if ( strcmp(sTable,it->sTable)==0 )
		{
			iModUin =(iUin/it->iDiv )%(it->iMod);
			break;
		}
	}
	if (iModUin==-100 )
	{
		sErrMsg=string(sTable)+" :err table name ";
		return -2;
	}

	for (std::vector<UIN_DBC>::iterator it=m_vstUinTtc.begin(); it!=m_vstUinTtc.end();it++)
	{
		if(strcmp(sTable,it->sTable)==0 && iModUin >= it->iBeg_uin  && iModUin < it->iEnd_uin)
		{
			*m_stServer = it->pServer;
			return 0;
		}
	}

	sErrMsg = string("not found: iTable =") + string(sTable) + " iUin="+CTrans::UTOS(iUin);
	error_log("get_route() err:table id=%s ", sTable);
	return -4;
};

int CDBCRouteTable::get_route(int iTableId,unsigned iUin,DBC::Server ** m_stServer,
                             bool isUseConf,  unsigned int  pn_MaxNum, char** ip)
{
	if (iInitSuc !=0)return -1;

	#ifdef _MAKESERVER_
	/*采用配置DBC后ID全部上涨30，合并代码前临时采用这种方式测试*/
	if (iTableId < 30)
	{
		iTableId += 30;
	}
	#endif

	if (iTableId<0)
	{
		sErrMsg = string("err: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::UTOS(iUin);
		return -2;
	}
	int iModUin =0 ;
	bool bFlag=false;
	for (vector<HEARD_INFO>::iterator it=m_vstHeardInfo.begin(); it!=m_vstHeardInfo.end();it++)
	{
		if ( (it->iTableId)==iTableId )
		{
			if(isUseConf)
			{
				pn_MaxNum=it->iMaxnum;
			}
			
			iModUin =(iUin/it->iDiv )%(it->iMod);
			bFlag=true;
			break;
		}
	}
	if (!bFlag)
	{
		sErrMsg = string("err table id ") + CTrans::ITOS(iTableId);
		error_log("get_route() err:table id=%d ", iTableId);
		return -3;
	}

	for (std::vector<UIN_DBC>::iterator it=m_vstUinTtc.begin(); it!=m_vstUinTtc.end();it++)
	{
		if( (it->iTableId == iTableId ) && (iModUin >= it->iBeg_uin)  && (iModUin <= it->iEnd_uin) )
		{
			//cout<<"find port"<< it->sPort	<<" ip"<< it->sIP<<	endl;
			*m_stServer = it->pServer;
			if ( NULL != ip )
				*ip = it->sIP;
			CheckConnectCount(iTableId, iUin, it->pServer, pn_MaxNum);
			return 0;
		}
	}

	sErrMsg = string("not found: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::UTOS(iUin);
	return -4;
};

int CDBCRouteTable::get_ip(int iTableId,int iUin, string & ps_IP, unsigned int & pn_Port)
{
	ps_IP.clear();
	pn_Port = 0;

	if (iInitSuc !=0) return -1;
	if (iTableId<0 || iUin<0)
	{
		sErrMsg = string("err: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::ITOS(iUin);
		return -2;
	}
	int iModUin =0 ;
	bool bFlag=false;
	for (vector<HEARD_INFO>::iterator it=m_vstHeardInfo.begin(); it!=m_vstHeardInfo.end();it++)
	{
		if ( (it->iTableId)==iTableId )
		{
			iModUin =((int)(iUin/it->iDiv ))%(it->iMod);
			bFlag=true;
			break;
		}
	}
	if (!bFlag)
	{
		sErrMsg = string("err table id ") + CTrans::ITOS(iTableId);
		error_log("get_route() err:table id=%d ", iTableId);
		return -3;
	}

	for (std::vector<UIN_DBC>::iterator it=m_vstUinTtc.begin(); it!=m_vstUinTtc.end();it++)
	{
		if( (it->iTableId == iTableId ) && (iModUin >= it->iBeg_uin)  && (iModUin <= it->iEnd_uin) )
		{
			ps_IP = it->sIP;
			pn_Port = atoi(it->sPort);

			return 0;
		}
	}

	sErrMsg = string("not found: iTableId =")+CTrans::ITOS(iTableId)+" iUin="+CTrans::ITOS(iUin);
	return -4;
}

int CDBCRouteTable::get_route_batch(char *sTable,std::vector<int>  iUins, std::vector<BATCH_DBC> vBatchTtc)
{
	//todo
	return -1;
}

string CDBCRouteTable::get_msg()
{
	return sErrMsg;
};

int CDBCRouteTable::CheckConnectCount(int iTableId, int iUin, DBC::Server * mp_stServer,
			 unsigned int  pn_MaxNum)
{
	if( !mp_stServer) {
		return -1;
	}

	DBCConnectMap::iterator  lp_ConP = mc_DBCConMap.find(mp_stServer);
	if(lp_ConP != mc_DBCConMap.end() ) {    // 原来已经有了 返回
		return 0;
	}

	mc_DBCConMap.insert(make_pair(mp_stServer, iTableId));   // 新加入
	mlp_DBCConList.push_back(mp_stServer);

	if (pn_MaxNum<=0) 
	{//最大连接数不能为<=0，否则进来的连接直接会被关闭
		pn_MaxNum=1;
	}
	
	if(mlp_DBCConList.size() > pn_MaxNum) {     // 大于数量限制 主动关闭
		DBC::Server * lp_Tmp = mlp_DBCConList.front();
		lp_Tmp->Close();
		mlp_DBCConList.pop_front();
		mc_DBCConMap.erase(lp_Tmp);
		return 1;
	}

	return 0;
}


CDBCRouteTable * CDBCRouteTable::GetInstance(char *xml)
{
	if ( _pInstance == 0 )
	{
        _pInstance = new CDBCRouteTable(xml);
	}
    return _pInstance;
};
//int main(int argc, char *argv[])
//{
//	printf("Hello, world\n");
//	CDBCRouteTable stTtc;
//	int iRet=stTtc.init();
//
//	printf("---%d--\n",iRet);
//
//	iRet=stTtc.get_route(0 ,110);
//
//	printf("2---%d--\n",iRet);
//
//	return 0;
//}
