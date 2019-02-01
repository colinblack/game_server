#include "qosinfo_wt.h"

#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

CQosInfoWt* CQosInfoWt::_ins = NULL;
CQosInfoWt::CQosInfoWt()
{
	_qos_type = QOS_TYPE_NULL;
	_gcd_wt = 0;			//权重的最大公约数
	_max_wt = 0;			//最大的权重
	_cur_svr_id = 0;		//当前机器序号
	_cur_wt = 0;			//当前权重
	_qos_extend_rate = 0.1;	//按10%比例扩充权重
	
	_req_max = 0;
	_req_min = 5;
}

CQosInfoWt::~CQosInfoWt()
{
	int _vec_size = _vec_host.size();
	for( int i=0;i<_vec_size;i++ )
	{
		if ( _vec_host[i]._host_info._sock_fd > 0 )
		{
			close(_vec_host[i]._host_info._sock_fd);
			_vec_host[i]._host_info._sock_fd = 0;
		}
	}
	_vec_host.clear();
	_map_vec_idx.clear();
}

CQosInfoWt* CQosInfoWt::Instance()
{
	if ( !_ins )
		_ins = new CQosInfoWt();
	
	return _ins;
}

//重算时间和扩展率
int CQosInfoWt::Init(int qos_rebuild_sec, float qos_extend_rate,int req_min,ENUM_QOS_TYPE qos_type)
{
	_qos_type = qos_type;
	_req_min = req_min;	
	_qos_rebuild_internal = qos_rebuild_sec;
	_qos_extend_rate = qos_extend_rate;
	gettimeofday(&_qos_active_tm, NULL);
	_qos_build_tm = _qos_active_tm;
	
	return 0;
}

int CQosInfoWt::HostQos(char* host_ip,short host_port,float& host_wt)
{
	hash_map<string,int,str_hash>::iterator	_map_vec_idx_it;
	string _host_str;
	HOSTINFO::Host2Str((unsigned)inet_addr(host_ip),host_port,_host_str);
	
	_map_vec_idx_it = _map_vec_idx.find(_host_str);
	if ( _map_vec_idx_it != _map_vec_idx.end() )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]can't find ip:%s port:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						host_ip,host_port);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';	
		
		return -1;
	}
	int	_vec_idx = _map_vec_idx_it->second;
	host_wt = _vec_host[_vec_idx]._cur_wt;
	
	return 0;
}

int CQosInfoWt::AddHost(HOSTINFO host_info,float wt)
{
	hash_map<string,int,str_hash>::iterator	_map_vec_idx_it;
	string _host_str;
	HOSTINFO::Host2Str(host_info._host_ip,host_info._host_port,_host_str);
	
	_map_vec_idx_it = _map_vec_idx.find(_host_str);
	if ( _map_vec_idx_it != _map_vec_idx.end() )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]add dup ip:%s port:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(host_info._host_ip),host_info._host_port);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';
		
		return 0;
	}
	
	if ( wt > _max_wt )	_max_wt = wt;
	QOSHOSTINFO _qos_host;
	_qos_host._host_info = host_info;
	_qos_host._cfg_wt = wt;
	_qos_host._cur_wt = wt;
	_vec_host.push_back(_qos_host);
	_gcd_wt = Gcd_n();
	_map_vec_idx[_host_str] = _vec_host.size()-1;
	
	return 0;
}

int CQosInfoWt::UpdateHost(HOSTINFO host_info,int rsp_code,int rsp_time_usec)
{
	hash_map<string,int,str_hash>::iterator	_map_vec_idx_it;
	string _host_str;
	HOSTINFO::Host2Str(host_info._host_ip,host_info._host_port,_host_str);
	
	_map_vec_idx_it = _map_vec_idx.find(_host_str);
	if ( _map_vec_idx_it == _map_vec_idx.end() )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]can't find host-ip:%s host-port:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(host_info._host_ip),host_info._host_port);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	int	_vec_idx = _map_vec_idx_it->second;
	if ( _vec_host[_vec_idx]._host_info._host_ip != host_info._host_ip ||
			_vec_host[_vec_idx]._host_info._host_port != host_info._host_port )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]map-vec-idx:%d host-ip:%s  host-port:%d invalid\n",
					__FILE__,__LINE__,__FUNCTION__,
						_vec_idx,HOSTINFO::HostInt2Str(host_info._host_ip),host_info._host_port);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	_vec_host[_vec_idx]._host_info = host_info;
	if ( _qos_type == QOS_TYPE_NULL )
		return 0;
	
	gettimeofday(&_qos_active_tm, NULL);
	_vec_host[_vec_idx]._req_count++;
	if ( rsp_code < 0 )	_vec_host[_vec_idx]._rsp_error++;
	_vec_host[_vec_idx]._rsp_time += rsp_time_usec;
	if ( _req_max < _vec_host[_vec_idx]._req_count )
		_req_max = _vec_host[_vec_idx]._req_count;
	
	if((_qos_active_tm.tv_sec - _qos_build_tm.tv_sec) >= _qos_rebuild_internal)
	{
		return RebuildQos();
	}
	return 0;
}

int CQosInfoWt::RebuildQos()
{
	_max_wt = 0;
	vector<QOSHOSTINFO*>::iterator _vec_it;
	int _vec_size = _vec_host.size();
	if ( _req_max <= 0 ) return 0;	
	
	if ( _qos_type == QOS_TYPE_RSP_CODE )
	{
		float _err_rate;
		float _req_min_rate = (float)_req_min / (float)_req_max;
		for ( int i=0;i<_vec_size;i++ )
		{
			float _wt_min = _vec_host[i]._cfg_wt * _req_min_rate;
			if ( _wt_min < 1 ) _wt_min = 1;
			
			if ( _vec_host[i]._req_count == 0 )
			{
				if ( _vec_host[i]._cur_wt < _wt_min ) _vec_host[i]._cur_wt = _wt_min;
				if ( _vec_host[i]._cur_wt > _max_wt )	_max_wt = _vec_host[i]._cur_wt;
				/*
				printf("qos ip:%s port:%d req:%d err:%d old-wt:%f new-wt:%f req-min-rate:%f wt-min:%f\n",
					HOSTINFO::HostInt2Str(_vec_host[i]._host_info._host_ip),
						_vec_host[i]._host_info._host_port,
						_vec_host[i]._req_count,
						_vec_host[i]._rsp_error,
						_old_wt,
						_vec_host[i]._cur_wt,
						_req_min_rate,
						_wt_min);	
				*/
				continue;
			}
			
			_err_rate = ((float)_vec_host[i]._rsp_error/(float)_vec_host[i]._req_count);
			if ( _err_rate > 0 )
			{
				_vec_host[i]._cur_wt -= _vec_host[i]._cur_wt*_err_rate;
			}
			else if ( _vec_host[i]._cur_wt < _vec_host[i]._cfg_wt )
			{
				float _add_wt = _vec_host[i]._cfg_wt*_qos_extend_rate;
				if ( _add_wt < 1 ) _add_wt = 1;
				_vec_host[i]._cur_wt += _add_wt;
			}
			
			if ( _vec_host[i]._cur_wt < _wt_min ) _vec_host[i]._cur_wt = _wt_min;
			if ( _vec_host[i]._cur_wt > _vec_host[i]._cfg_wt ) _vec_host[i]._cur_wt = 
						_vec_host[i]._cfg_wt;
			if ( _vec_host[i]._cur_wt > _max_wt )	_max_wt = _vec_host[i]._cur_wt;
			
			/*
			printf("qos ip:%s port:%d req:%d err:%d old-wt:%f new-wt:%f req-min-rate:%f wt-min:%f\n",
					HOSTINFO::HostInt2Str(_vec_host[i]._host_info._host_ip),
						_vec_host[i]._host_info._host_port,
						_vec_host[i]._req_count,
						_vec_host[i]._rsp_error,
						_old_wt,
						_vec_host[i]._cur_wt,
						_req_min_rate,
						_wt_min);
			*/
			_vec_host[i]._req_count = 0;
			_vec_host[i]._rsp_error = 0;
			_vec_host[i]._rsp_time = 0;
		}
	}
	else if ( _qos_type == QOS_TYPE_RSP_TIME )
	{
		float _rsp_avg_time;
		for ( int i=0;i<_vec_size;i++ )
		{
			float _req_min_rate = (float)_req_min / (float)_req_max;
			float _wt_min = _vec_host[i]._cfg_wt * _req_min_rate;
			
			_rsp_avg_time = (float)_vec_host[i]._rsp_time/(float)_vec_host[i]._req_count;
			_vec_host[i]._cur_wt = (1/_rsp_avg_time)*1000;
			
			if ( _vec_host[i]._cur_wt < _wt_min ) _vec_host[i]._cur_wt = _wt_min;
			if ( _vec_host[i]._cur_wt > _vec_host[i]._cfg_wt ) _vec_host[i]._cur_wt = 
						_vec_host[i]._cfg_wt;
			
			_vec_host[i]._req_count = 0;
			_vec_host[i]._rsp_error = 0;
			_vec_host[i]._rsp_time = 0;
		}
	}
	else
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]invalid qos-type:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						_qos_type);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';	
		
		return -1;
	};
	
	_gcd_wt = 0;
	_cur_svr_id = 0;
	_cur_wt = 0;
	_req_max = 0;
	_gcd_wt = Gcd_n();
	_qos_build_tm = _qos_active_tm;	
	
	return 0;
}

int CQosInfoWt::AllocServer(HOSTINFO& host_info,int host_idx)
{
	int	_vec_size = _vec_host.size();
	if ( host_idx >= _vec_size )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]host-idx:%d too max:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						host_idx,_vec_size);
		if ( _ret >= 0 )	*((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	host_info = _vec_host[host_idx]._host_info;
	
	return 0;
}

int CQosInfoWt::AllocServer(HOSTINFO& host_info)
{
	int	_vec_size = _vec_host.size();
	
	for(;;)
	{
		_cur_svr_id = (_cur_svr_id + 1) % _vec_size;
		if (_cur_svr_id == 0) 
		{
			_cur_wt = _cur_wt - _gcd_wt;
			
	  		if ( _cur_wt <= 0 )
	 		{
	    	 	_cur_wt = _max_wt;
	    		if (_cur_wt == 0)	return -1;
			}
		}
		
		if ( _vec_host[_cur_svr_id]._cur_wt >= _cur_wt )
		{
			host_info = _vec_host[_cur_svr_id]._host_info;
			/*
			if ( _vec_size == 2 )
			{
				Log("alloc host:%s cfg-wt:%f cur-wt:%f size:%d cur-id:%d cur_wt:%f gcd_wt:%d\n",
						HOSTINFO::HostInt2Str(host_info._host_ip),
						_vec_host[_cur_svr_id]._cfg_wt,
						_vec_host[_cur_svr_id]._cur_wt,
						_vec_host.size(),
						_cur_svr_id,
						_cur_wt,
						_gcd_wt);	
			}
			*/
			return 0;
		}
	}
	
	return -1;
}

int CQosInfoWt::Gcd(int a, int b) 
{ 
	int r; 
	if(a<b){r=a; a=b; b=r;} 
	
	while (b!=0) 
	{
		r=a%b; 
		a=b; 
		b=r; 
	}
	return a; 
}

int CQosInfoWt::Gcd_n()
{
	int	_vec_size = _vec_host.size();
	int rtn = 0;
	
	for ( int i=0;i<_vec_size;i++ )
	{
		if ( i== 0 )
			rtn = (int)_vec_host[i]._cur_wt;
		rtn = Gcd(rtn,(int)_vec_host[i]._cur_wt);
	}
	
	return rtn;
}

int CQosInfoWt::List()
{
	/*
	ERROR_LOG("");
	ERROR_LOG("...................................");	
	int _vec_qos_size = _vec_host.size();
	for( int i=0;i<_vec_qos_size;i++ )
	{
		ERROR_LOG("ip %d qos wt:%f", _vec_host[i]->_svr_ip, _vec_host[i]->_cur_wt);
	}
	ERROR_LOG("...................................\n");	
	*/
	
	return 0;
}

int CQosInfoWt::GetHostInfo(vector<QOSHOSTINFO>& vec_host_info)
{
	vec_host_info = _vec_host;
	
	return 0;
}
