/*
 * DataXMLPraseWrap.h
 *
 *  Created on: 2016-8-4
 *      Author: dawx62fac
 */

#ifndef DATAXMLPRASEWRAP_H_
#define DATAXMLPRASEWRAP_H_

#include <stdexcept>
#include "Kernel.h"
#include "DataXML.h"

template<class T>
class DataXmlParseWrap
{
public:
	DataXmlParseWrap(CShareMemory& sh, const std::string& cfg)
		: m_sh(sh)
	{
		m_fullCfg = GetFullPath(cfg);
	}

	virtual ~DataXmlParseWrap() {}

	int Initialize()
	{
		T* pData = reinterpret_cast<T*>(m_sh.GetAddress());
		if (pData == NULL)
		{
			throw std::runtime_error("Get_data_ptr_error");
		}

		CAutoLock lock(&(m_sh), true, LOCK_MAX);

		memset(pData, 0, sizeof(*pData));

		int ret = Parse(m_fullCfg, pData);
		if (R_SUCCESS == ret)
		{
			m_sh.SetInitDone();
		}

		return ret;
	}

protected:
	//
	virtual int Parse(const std::string& fullCfg, T* pData) = 0;


	//加载文件 并Into 字段content
	void PreHandleXmlCfg(CMarkupSTL& xmlConf, const std::string& fullCfg)
	{
		if(!xmlConf.Load(fullCfg.c_str()))
		{
			error_log("load cfg.xml failed. path: %s", fullCfg.c_str());
			throw std::runtime_error("[DataXmlNewRechargeBag]load_cfg_failed.");
		}

		if (! xmlConf.FindElem("content"))
		{
			error_log("content_node_error");
			throw std::runtime_error("content_node_error");
		}
		xmlConf.IntoElem();
	}

	void IntoXmlNode(CMarkupSTL& xmlConf, const char* node)
	{
		if (node == NULL)
		{
			throw std::runtime_error("node_isnull_error");
		}

		if (! xmlConf.FindElem(node))
		{
			error_log("node_error: %s", node);
			throw std::runtime_error("node_error");
		}

		xmlConf.IntoElem();
	}

	void FindXmlNode(CMarkupSTL& xmlConf, const char* node)
	{
		if (node == NULL)
		{
			throw std::runtime_error("node_isnull_error");
		}

		if (! xmlConf.FindElem(node))
		{
			error_log("node_error: %s", node);
			throw std::runtime_error("node_error");
		}
	}

	Json::Value XmlDataToJson(const CMarkupSTL& xmlConf)
	{
		std::string data = xmlConf.GetData();
		Json::Value jsonData;
		Json::Reader reader;
		if (!reader.parse(data, jsonData))
		{
			error_log("parse json error data=%s msg=%s", data.c_str(), reader.getFormatedErrorMessages().c_str());
			throw std::runtime_error("prayconfig.xml => data error.1");
		}

		return jsonData;
	}

	int _parse_activity_simple_reward(const Json::Value &reward, XMLActSimpleReward *data, int len)
	{
		Json::Value::Members members(reward.getMemberNames());
		int index = 0;
		for (Json::Value::Members::iterator it=members.begin(); it!=members.end(); ++it)
		{
			string type = *it;
			if (type.find("equip") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_EQUIP;
				if (!Json::GetUInt(reward[type], "id", data[index].id)){
					return R_ERR_DATA;
				}
				Json::GetUInt(reward[type], "c", data[index].count);
				unsigned q,ch;
				q=ch=0;
				Json::GetUInt(reward[type], "ch", ch);
				Json::GetUInt(reward[type], "q", q);
				data[index].q = q;
				data[index].ch = ch;
				unsigned xs = 0;
				Json::GetUInt(reward[type], "xs", xs);
				if (xs)
					data[index].xs = true;
			}else if (type.find("hero") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_HERO;
				if (!Json::GetUInt(reward[type], "id", data[index].id)){
					return R_ERR_DATA;
				}
				Json::GetUInt(reward[type], "c", data[index].count);
			}else if (type.find("gold") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_GOLD;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("explevel") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_EXP_LV;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("exp") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_EXP;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_1") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT1;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_2") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT2;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_3") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT3;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_4") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT4;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_5") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT5;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_6") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT6;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("mt_7") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_MT7;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("rs1") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_RES1;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("rs2") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_RES2;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("rs3") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_RES3;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("prosper") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_PROSPER;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else if (type.find("cash") != string::npos){
				data[index].type = XML_ACT_SIMPLE_REWARD_TYPE_CASH;
				Json::GetUInt(reward, type.c_str(), data[index].count);
			}else{
				continue;
			}
			if (++index >= len){
				break;
			}
		}
		return 0;
	}

private:
	std::string GetFullPath(const std::string& cfg)
	{
		string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
		if (dataPath.empty())
		{
			throw std::runtime_error("Get_all_server_path_config_error");
		}

		if (dataPath[dataPath.length() - 1] != '/')
		{
			dataPath.append("/");
		}

		dataPath.append(cfg);

		return dataPath;
	}
private:
	CShareMemory& 	m_sh;
	std::string 	m_fullCfg;
};



#endif /* DATAXMLPRASEWRAP_H_ */
