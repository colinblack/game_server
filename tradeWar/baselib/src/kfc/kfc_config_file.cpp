#include "kfc_config_file.h"
#include "kfc_comm.h"

#include <fstream>
#include <iostream>
#include <strings.h>

using namespace std;

kfc::CFileConfig::CFileConfig()
{
}

kfc::CFileConfig::~CFileConfig()
{
}

inline string kfc::CFileConfig::start_path(const string& s)
{
	return string(s.c_str(), 1, s.length() - 2);
}

inline string kfc::CFileConfig::stop_path(const string& s)
{
	return string(s.c_str(), 2, s.length() - 3);
}

inline void kfc::CFileConfig::decode_pair(const string& s, string& name, string& value)
{
	bool find = false;
	char *p = const_cast<char *> (s.c_str());
	char *p1 = p;

	while(*p1 != 0)
	{
		if(*p1 == '=' || *p1 == '\t' || *p1 == ' ')
		{
			find = true;
			break;
		}
		p1++;
	}
	if(!find || p1 == p)
	{
		throw conf_load_error(string("CFileConfig::Load:can not find name: ") + s);
	}
	name = string(p, 0, p1 - p);
	p += s.length();
	find = false;
	while(*p1 != 0)
	{
		if(*p1 != '=' && *p1 != '\t' && *p1 != ' ')
		{
			find = true;
			break;
		}
		p1++;
	}
	value = string(p1, 0, p - p1);
}

kfc::CFileConfig::EntryType kfc::CFileConfig::entry_type(const string& s)
{
	if(s.length() == 0) return T_NULL;
	if(s.c_str()[0] == '<')
	{
		if(s.c_str()[s.length() - 1] == '>')
		{
			if(s.c_str()[1] == '/') return T_STOPPATH;
			else return T_STARTPATH;
		}
		else
		{
			return T_ERROR;
		}
	}
	else
	{
		if(s.find(" ") == string::npos && s.find("\t") == string::npos && s.find("=") == string::npos)
		{
			return T_DOMAIN;
		}
		else return T_PAIR;
	}
	return T_ERROR;
}

// 替换转义符
inline string kfc::CFileConfig::replace_esc(const string& s, const string& esc, const string& repl)
{
	size_t pos = s.find(esc);
	if(pos == string::npos) return s;
	string real;
	size_t idex = 0;
	while(pos != string::npos)
	{
		if(pos > idex)
		{
			real += s.substr(idex, pos - idex);
		}
		real += repl;
		idex = pos + esc.length();
		pos = s.find(esc, idex);
	}
	real += s.substr(idex, s.length() - idex);
	return real;
}

// 去掉注释、替换转义符 ， #后为注释\# \n \\为转义符
inline string kfc::CFileConfig::trim_comment(const string& s)
{
	if(s.c_str()[0] == '#') return "";

	char *p = const_cast<char *> (s.c_str());
	char *p1 = p;
	while(*p1 != 0)
	{
		if(*p1 == '#')
		{
			if(*(p1 - 1) != '\\')
			{ //如果#前不是\，就是注释
				break;
			}
		}
		p1++;
	}
	string real = string(p, 0, p1 - p);
	real = replace_esc(real, "\\r", "\r");
	real = replace_esc(real, "\\n", "\n");
	real = replace_esc(real, "\\t", "\t");
	real = replace_esc(real, "\\#", "#");
	real = replace_esc(real, "\\\\", "\\");
	return real;
}

// 得到当前路径,调用之前判断是否为空
inline string kfc::CFileConfig::path(const deque<string>& path)
{
	deque<string>::const_iterator it;
	string s;
	if(path.size() == 0)
	{
		throw conf_load_error("CFileConfig::Load:must not into here");
	}
	for(it = path.begin(); it != path.end(); it++)
	{
		s += "\\";
		s += (*it);
	}
	return string(s.c_str(), 1, s.length() - 1);
}

// 得到parent路径，调用前判断是否为空，可能返回""
inline string kfc::CFileConfig::parent_path(const deque<string>& path)
{
	deque<string>::const_iterator it;
	string s("");
	unsigned i = 0;
	if(path.size() == 0)
	{
		throw conf_load_error("CFileConfig::Load:must not into here");
	}
	if(path.size() == 1)
	{
		return s;
	}
	for(it = path.begin(); it != path.end(); it++)
	{
		if(i + 1 == path.size()) break;
		s += "\\";
		s += (*it);
		i++;
	}
	return string(s.c_str(), 1, s.length() - 1);
}

// 得到sub路径，调用前判断是否为空
inline string kfc::CFileConfig::sub_path(const deque<string>& path)
{
	deque<string>::reverse_iterator it;
	string s;
	if(path.size() == 0)
	{
		throw conf_load_error("CFileConfig::Load:must not into here");
	}

	return(*it);
}

/*
 *   支持include 语法  #include "config filename"
 */
inline string kfc::CFileConfig::get_includefile(const string& s)
{
	int startflag = s.find_first_of("\"");
	int endflag = s.find_last_of("\"");

	if(endflag <= startflag)
		return string("");

	return s.substr(startflag + 1, endflag - startflag - 1);
}

void kfc::CFileConfig::Init(const string& filename)
throw(conf_load_error)
{
	_filename = filename;
	Load();
}

void kfc::CFileConfig::LoadSubFile(const string& subfile)
throw(conf_load_error)
{
	if(subfile == "") throw conf_load_error("CFileConfig::Load: include filename is null");

	string sline;
	string sreal;
	ifstream in(subfile.c_str());
	if(!in)
		throw conf_load_error(string("CFileConfig::Load: can not open ") + subfile);

	deque<string> path_stack;

	string name, value;
	deque<string>::reverse_iterator it;

	while(getline(in, sline))
	{
		sreal = trim_right(trim_comment(trim_right(trim_left(sline, " \t"), " \t\r\n")), "\t ");
		switch(entry_type(sreal))
		{
		case T_STARTPATH:
			path_stack.push_back(start_path(sreal));
			//			_pairs[path(path_stack)] = _null_map;
			//			_domains[path(path_stack)] = _null_vector;
			//			if(_paths.find(parent_path(path_stack)) == _paths.end())[_paths[parent_path(path_stack)]] = _null_vector);
			_paths[parent_path(path_stack)].push_back(start_path(sreal));
			break;
		case T_STOPPATH:
			it = path_stack.rbegin();
			if(it == path_stack.rend() || (*it) != stop_path(sreal))
			{
				throw conf_load_error(string("CFileConfig::Load: path not match: ") + stop_path(sreal));
			}
			path_stack.pop_back();
			break;
		case T_NULL:
			break;
		case T_PAIR: // 同时也作为domain
			if(path_stack.size() == 0)
			{
				throw conf_load_error("CFileConfig::Load: path is null");
			}
			decode_pair(sreal, name, value);

			_pairs[path(path_stack)][name] = value;
			_domains[path(path_stack)].push_back(sreal);
			break;
		case T_DOMAIN: // 同时也作为pair
			if(path_stack.size() == 0)
			{
				throw conf_load_error("CFileConfig::Load: path is null");
			}
			_pairs[path(path_stack)][sreal] = "";
			_domains[path(path_stack)].push_back(sreal);
			break;
		default:
			throw conf_load_error(string("CFileConfig::Load: invalid:") + sreal);
		}
	}
	//文件解析完要判断path_stack是否为空
	if(path_stack.size() != 0)
	{
		throw conf_load_error("CFileConfig::Load: path havenot over");
	}
}

void kfc::CFileConfig::Load()
throw(conf_load_error)
{
	if(_filename == "") throw conf_load_error("CFileConfig::Load: filename is null");

	string sline;
	string sreal;
	ifstream in(_filename.c_str());
	if(!in)
		throw conf_load_error(string("CFileConfig::Load: can not open ") + _filename);

	_pairs.clear();
	_paths.clear();
	_domains.clear();

	while(getline(in, sline))
	{
		sreal = trim_right(trim_left(sline, " \t"), " \t\r\n");
		if(strncasecmp(sreal.c_str(), "#include", 8) == 0)
		{
			LoadSubFile(get_includefile(sreal));
		}
	}
	in.close();
	LoadSubFile(_filename);
}

const string& kfc::CFileConfig::operator [](const string& name) const throw(conf_not_find)
{
	if(name.length() == 0)
	{
		throw conf_not_find("CFileConfig::[] is not find");
	}

	char *p0 = const_cast<char *> (name.c_str());
	char *p1 = p0 + name.length() - 1;
	char *p = p1;
	while(p > p0)
	{
		if(*p == '\\') break;
		p--;
	}
	if(p == p0 || p == p1) throw conf_not_find(string("CFileConfig::[] path is null:") + name);
	string path(p0, 0, p - p0);
	string realname(p + 1, 0, p1 - p);

	map<string, map<string, string> >::const_iterator it = _pairs.find(path);
	if(it == _pairs.end()) throw conf_not_find(string("CFileConfig::[") + name + "] is not find");
	map<string, string>::const_iterator it2 = (*it).second.find(realname);
	if(it2 == (*it).second.end()) throw conf_not_find(string("CFileConfig::[") + name + "] is not find");
	return(*it2).second;

}

const string& kfc::CFileConfig::getvalue(const string& name, const std::string& defaultvalue) const
{
	if(name.length() == 0)
	{
		return defaultvalue;
	}

	char *p0 = const_cast<char *> (name.c_str());
	char *p1 = p0 + name.length() - 1;
	char *p = p1;
	while(p > p0)
	{
		if(*p == '\\') break;
		p--;
	}
	if(p == p0 || p == p1) return defaultvalue;
	string path(p0, 0, p - p0);
	string realname(p + 1, 0, p1 - p);

	map<string, map<string, string> >::const_iterator it = _pairs.find(path);
	if(it == _pairs.end()) return defaultvalue;
	map<string, string>::const_iterator it2 = (*it).second.find(realname);
	if(it2 == (*it).second.end()) return defaultvalue;
	return(*it2).second;

}

const map<string, string>& kfc::CFileConfig::GetPairs(const string& path) const
{
	map<string, map<string, string> >::const_iterator it = _pairs.find(path);
	if(it == _pairs.end()) return _null_map;
	return(*it).second;
}

const vector<string>& kfc::CFileConfig::GetDomains(const string& path) const
{
	map<string, vector<string> >::const_iterator it = _domains.find(path);
	if(it == _domains.end()) return _null_vector;
	return(*it).second;
}

const vector<string>& kfc::CFileConfig::GetSubPath(const string& path) const
{
	map<string, vector<string> >::const_iterator it = _paths.find(path);
	if(it == _paths.end()) return _null_vector;
	return(*it).second;
}
