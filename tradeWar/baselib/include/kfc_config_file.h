#ifndef __KFC_CONFIG_FILE_H__
#define __KFC_CONFIG_FILE_H__

#include "kfc_config.h"
#include "kfc_version.h"

#include <deque>

namespace kfc
{

/**
 * 配置类: CConfig的File实现版本<br>
 * 配置中\n表示回车符
 */
class CFileConfig : public CConfig
{
	/**
	 * no implementation
	 */
	CFileConfig(const CFileConfig&);

	CFileConfig& operator=(const CFileConfig&);
public:
	CFileConfig();
	virtual ~CFileConfig();

public:
	/**
	 * 初始化,设置配置文件名&Load
	 * @throw conf_load_error when Load fail
	 * @param filename 配置文件名
	 */
	void Init(const std::string& filename) throw(conf_load_error);

	/**
	 * 加载配置
	 * @throw conf_load_error when Load fail
	 */
	virtual void Load() throw(conf_load_error);

	/**
	 * 取配置,支持层次结构,以'\'划分,如conf["Main\\ListenPort"]
	 * @throw conf_not_find when Load fail
	 */
	virtual const std::string& operator [](const std::string& name) const throw(conf_not_find);
	virtual const std::string& getvalue(const std::string& name, const std::string& defaultvalue = "") const;
	/**
	 * 取path下所有name-value对
	 */
	virtual const std::map<std::string, std::string>& GetPairs(const std::string& path) const;
	/**
	 * 取path下所有name-value或single配置
	 */
	virtual const std::vector<std::string>& GetDomains(const std::string& path) const;
	/**
	 * 取path下所有subpath名(只取一层)
	 */
	virtual const std::vector<std::string>& GetSubPath(const std::string& path) const;

protected:

	enum EntryType
	{
		T_STARTPATH = 0,
		T_STOPPATH = 1,
		T_NULL = 2,
		T_PAIR = 3,
		T_DOMAIN = 4,
		T_ERROR = 5
	};

	std::string start_path(const std::string& s);
	std::string stop_path(const std::string& s);
	void decode_pair(const std::string& s, std::string& name, std::string& value);
	std::string trim_comment(const std::string& s); //trim注释和\n符号
	std::string path(const std::deque<std::string>& path);
	std::string parent_path(const std::deque<std::string>& path);
	std::string sub_path(const std::deque<std::string>& path);
	std::string replace_esc(const std::string& s, const std::string& esc, const std::string& repl);
	std::string get_includefile(const std::string& s);
	void LoadSubFile(const std::string& subfile)throw(conf_load_error);

	EntryType entry_type(const std::string& s);
protected:
	std::string _filename;

	std::map<std::string, std::map<std::string, std::string> > _pairs;
	std::map<std::string, std::vector<std::string> > _paths;
	std::map<std::string, std::vector<std::string> > _domains;

	std::map<std::string, std::string> _null_map;
	std::vector<std::string> _null_vector;
};

}
#endif
