#include "kfc_mysql.h"
#include <stdio.h>

kfc::mysql_slopover::mysql_slopover(const string & s) : logic_error(s)
{
}

kfc::mysql_execfail::mysql_execfail(const string & s) : runtime_error(s)
{
}

////////////////////////////////////////////////

kfc::MySqlRowData::MySqlRowData(const vector<string>& data, map<string, int>& s2n)
: _data(&data), _s2n(&s2n)
{
}

kfc::MySqlRowData::MySqlRowData(const MySqlRowData & right)
: _data(right._data), _s2n(right._s2n)
{
}

void kfc::MySqlRowData::operator=(const MySqlRowData & right)
{
	_data = right._data;
	_s2n = right._s2n;
}

const string& kfc::MySqlRowData::operator [](const string &s) const throw(mysql_slopover)
{
	if((*_s2n).find(s) == (*_s2n).end())
		throw mysql_slopover(s + " slopover in MySqlRowData");
	return(*_data)[(*_s2n)[s]];
}

////////////////////////////////////////////////

kfc::MySqlBasicData::MySqlBasicData()
{
	_affected_rows = 0;
	_nRefCount = 0;
	//	cerr << "new " << this << endl;
}

void kfc::MySqlBasicData::RefAdd()
{
	_nRefCount++;
}

void kfc::MySqlBasicData::RefSub()
{
	if(--_nRefCount == 0) delete this;
}

void kfc::MySqlBasicData::Fields(const vector<string>& v) throw(mysql_slopover)
{
	_col.clear();
	_s2n.clear();
	for(size_t i = 0; i < v.size(); i++)
	{
		if(_s2n.find(v[i]) != _s2n.end())
		{
			throw mysql_slopover(string("MySqlBasicData::Fields ") + v[i] + " duplicate");
		}
		_col.push_back(v[i]);
		_s2n[v[i]] = i;
	}
}

void kfc::MySqlBasicData::push_back(vector<string>& v) throw(mysql_slopover)
{
	if(v.size() == 0 || v.size() != _col.size())
	{
		throw mysql_slopover("MySqlBasicData::push_back: num is not match");
	}
	_data.push_back(v);
}

// do it after push_back over

void kfc::MySqlBasicData::genrows()
{
	_rows.clear();
	for(size_t i = 0; i < _data.size(); i++)
		_rows.push_back(MySqlRowData(_data[i], _s2n));
}

////////////////////////////////////////////////

kfc::MySqlData::MySqlData(const MySqlData & right)
: _data(right._data)
{
	_data->RefAdd();
}

void kfc::MySqlData::operator =(const MySqlData& right)
{
	if(_data) _data->RefSub();
	_data = right._data;
	_data->RefAdd();
}

kfc::MySqlData::MySqlData(MySqlBasicData * data)
: _data(data)
{
	_data->RefAdd();
}

kfc::MySqlData::~MySqlData()
{
	_data->RefSub();
}

const kfc::MySqlRowData& kfc::MySqlData::operator [](const size_t row) const throw(mysql_slopover)
{
	if(row >= (_data->_rows).size())
	{
		char sTmp[16];
		sprintf(sTmp, "%ld", row);
		throw mysql_slopover(string("MySqlRowData::[") + sTmp + "] slopover");
	}
	return(_data->_rows)[row];
}

//

size_t kfc::MySqlData::affected_rows() const
{
	return _data->_affected_rows;
}

size_t kfc::MySqlData::num_rows() const
{
	return _data->_data.size();
}

size_t kfc::MySqlData::num_fields() const
{
	return _data->_col.size();
}

string kfc::MySqlData::org_name() const
{
	return _data->_org_name;
}

const vector<string>& kfc::MySqlData::Fields() const
{
	return _data->_col;
}

////////////////////////////////////////////////

kfc::CMySql::CMySql()
{
	_Mysql = NULL;
	_bIsConn = false;
}

kfc::CMySql::~CMySql()
{
	Close();
	delete _Mysql;
	_Mysql = NULL;
}

void kfc::CMySql::Init(const string &host, const string &user, const string &pass, unsigned short port, const string& charSet) throw(mysql_execfail)
{
	Close();
	delete _Mysql;
	_Mysql = NULL;

	_host = host;
	_user = user;
	_pass = pass;
	_port = port;
	//初试时如果不为空, 则设置_charSet, 防止Init前调用了setCharSet函数
	if(!charSet.empty())
	{
		_charSet = charSet;
	}
	_Mysql = new MYSQL;
	Connect();
}

void kfc::CMySql::use(const string & db)
{
	_dbname = db;
}

void kfc::CMySql::setCharSet(const string & cs)throw(mysql_execfail)
{
	_charSet = cs;

	if(!_bIsConn) return;

	//设置字符集后, 马上生效
	if(!_charSet.empty())
	{
		string sql = "set names '" + _charSet + "'";
		if(mysql_options(_Mysql, MYSQL_INIT_COMMAND, sql.c_str()))
		{
			throw mysql_execfail(string("CMySql::Connect: mysql_options MYSQL_INIT_COMMAND ") + _charSet + ":" + mysql_error(_Mysql));
		}

		query(sql);
	}
}

kfc::MySqlData kfc::CMySql::query(const string & sql) throw(mysql_execfail)
{
	Select();

	if(mysql_real_query(_Mysql, sql.c_str(), sql.length()))
	{
		string err(sql.c_str(), 0, 128);
		int ret_errno = mysql_errno(_Mysql);
		Close();
		if(ret_errno == 2013 || ret_errno == 2006)
		{ // CR_SERVER_LOST，重连一次
			Connect();
			if(mysql_select_db(_Mysql, _dbname.c_str()))
				throw mysql_execfail(string("CMySql::query: mysql_select_db ") + _dbname + ":" + mysql_error(_Mysql));
			if(mysql_real_query(_Mysql, sql.c_str(), sql.length()))
				throw mysql_execfail(string("CMySql::query: ") + mysql_error(_Mysql) + "|" + err);
		}
		else
		{
			throw mysql_execfail(string("CMySql::query: ") + mysql_error(_Mysql) + "|" + err);
		}
	}

	MySqlBasicData *data = new MySqlBasicData();
	// store
	if(mysql_field_count(_Mysql) == 0)
	{ //
		int inum = mysql_affected_rows(_Mysql);
		string err(sql.c_str(), 0, 128);
		if(inum < 0)
		{
			delete data;
			throw mysql_execfail(string("CMySql::query: ") + mysql_error(_Mysql) + "|" + err);
		}
		data->affected_rows(inum);
		return MySqlData(data);
	}
	MYSQL_RES * pstMySqlRes = mysql_store_result(_Mysql);
	if(pstMySqlRes == NULL)
	{
		string err(sql.c_str(), 0, 128);
		delete data;
		throw mysql_execfail(string("CMySql::query: mysql_store_result is null: ") + mysql_error(_Mysql) + "|" + err);
	}

	// fields
	MYSQL_FIELD *field;
	unsigned i = 0;
	vector<string> vfield;
	while((field = mysql_fetch_field(pstMySqlRes)))
	{
		//		if(i==0) {data->org_name(field->org_name); i++;}
		// 2007-01-24,mysql高版本又恢复了table字段，鉴于该功能的不稳定性，不再支持此api
		if(i == 0)
		{
			data->org_name("not support");
			i++;
		}
		/*
		// 2004-12-20,mysql 4.0以下不支持org_name
				#if MYSQL_VERSION_ID > 40027
					if(i==0) {data->org_name(field->org_name); i++;}
				#else
					if(i==0) {data->org_name(field->table); i++;}
				#endif
		 */
		vfield.push_back(field->name);
	}
	try
	{
		data->Fields(vfield);
	}
	catch(mysql_slopover& e)
	{
		delete data;
		mysql_free_result(pstMySqlRes);
		throw mysql_execfail(string("CMySql::query: catch mysql_slopover:") + e.what());
	}

	// values
	data->clear();
	MYSQL_ROW row;
	vector<string> vrow;
	try
	{
		while((row = mysql_fetch_row(pstMySqlRes)))
		{
			vrow.clear();
			for(i = 0; i < vfield.size(); i++)
				vrow.push_back(row[i] ? row[i] : "");
			data->push_back(vrow);
		}
	}
	catch(mysql_slopover& e)
	{
		delete data;
		mysql_free_result(pstMySqlRes);
		throw mysql_execfail(string("CMySql::query: catch mysql_slopover: ") + e.what());
	}
	data->genrows();
	mysql_free_result(pstMySqlRes);

	return MySqlData(data);
}

////////protected

void kfc::CMySql::Connect()
{
	mysql_init(_Mysql);

	//建立连接后, 自动调用设置字符集语句
	if(!_charSet.empty())
	{
		string sql = "set names '" + _charSet + "'";
		if(mysql_options(_Mysql, MYSQL_INIT_COMMAND, sql.c_str()))
		{
			throw mysql_execfail(string("CMySql::Connect: mysql_options MYSQL_INIT_COMMAND ") + _charSet + ":" + mysql_error(_Mysql));
		}
	}

	if(mysql_real_connect(_Mysql, _host.c_str(), _user.c_str(), _pass.c_str()
						, NULL, _port, NULL, 0) == NULL)
		throw mysql_execfail(string("CMySql::Connect: mysql_real_connect to ") + _host + ":" + mysql_error(_Mysql));

	_bIsConn = true;
}

void kfc::CMySql::Close()
{
	if(!_bIsConn) return;
	mysql_close(_Mysql);
	_bIsConn = false;
}

void kfc::CMySql::Select()
{
	if(!_bIsConn) Connect();

	if(_dbname.empty()) return;

	if(mysql_select_db(_Mysql, _dbname.c_str()))
	{
		int ret_errno = mysql_errno(_Mysql);
		Close();
		if(ret_errno == 2013 || ret_errno == 2006)
		{ // CR_SERVER_LOST，重连一次
			Connect();
		}

		if(mysql_select_db(_Mysql, _dbname.c_str()))
			throw mysql_execfail(string("CMySql::Select: mysql_select_db ") + _dbname + ":" + mysql_error(_Mysql));
	}
}

std::string kfc::CMySql::escape_string(const char * s, size_t length)
{
	char * p = new char[length * 2 + 1];
	char * pp = p;
	pp += mysql_real_escape_string(_Mysql, pp, s, length);
	std::string s1(p, pp - p);
	delete p;
	return s1;
}
