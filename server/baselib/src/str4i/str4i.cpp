#include "str4i.h"

CStr4I::CStr4I()
{
	m_vsId2Mark.clear();
	m_nConfTypeMax = 0;
	m_bConfInitSucc = false;

	if (m_bConfInitSucc == false)
	{
		int nRet =  ConfInit(PATH_XML_FARMCONF4I);
		if (nRet == 0)
		{
			m_bConfInitSucc = true;
		}
	}
}

CStr4I::~CStr4I()
{

}

int CStr4I::m_defaultType = LANG_CN_SIMPLE;
vector<string> CStr4I::m_vsId2Mark;
int CStr4I::m_nConfTypeMax;
bool CStr4I::m_bConfInitSucc;

hash_map < int, vector < int > > CStr4I::m_mapModuleId;
int CStr4I::m_nModuleTypeMax;
bool CStr4I::m_bModuleInitSucc;

void CStr4I::NeedKey(const char * pszKey)
{
	if (pszKey == NULL || *pszKey == '\0' )
	{
		return;
	}

	m_setKeys.insert(pszKey);
}

int CStr4I::InitKeyValues(const char * pszConfFile)
{
	if (pszConfFile == NULL)
	{
		m_strErrMsg = "pszConfFile is NULL";

		return -1;
	}

	CMarkupSTL xml;
	if (!xml.Load(pszConfFile))
	{
		m_strErrMsg = "load file:" + string(pszConfFile) + " failed, err msg:" + xml.GetError();

		return -2;
	}
	if (!xml.FindElem("str4i"))
	{
		m_strErrMsg = "find element str4i in file:" + string(pszConfFile) + ", err msg:" + xml.GetError();

		return -3;
	}
	m_nTypeMax = atoi(xml.GetAttrib("type_max").c_str());
	if ( m_nTypeMax < 0)
	{
		m_strErrMsg = "bad type_max:" + string(xml.GetAttrib("type_max").c_str());
		return -4;
	}

	if (!xml.IntoElem())
	{
		m_strErrMsg = "can't get into the str4i element, err msg:" + xml.GetError();

		return -5;
	}
	
	while (xml.FindElem())
	{
		string key = xml.GetAttrib("key");
		if(m_setKeys.find(key)==m_setKeys.end())
		{
			continue;
		}
		vector<string> vs;
		vs.resize(m_nTypeMax + 1);
		while (xml.FindChildElem("text"))
		{
			xml.IntoElem();
			int type = atoi(xml.GetAttrib("lang").c_str());
			if(type<0 || type>m_nTypeMax)
			{
				m_strErrMsg = xml.GetAttrib("lang") + " bad type";
				return -6;
			}
			vs[type] = xml.GetData();
			xml.OutOfElem();
		}
		m_mapKeyValues[key] = vs;
		m_setKeys.erase(key);
		if(m_setKeys.empty())
		{
			return 0;
		}
	}

	m_strErrMsg = *(m_setKeys.begin()) + " no found";
	return -7;
}

const char * CStr4I::GetValue(const char * pszKey, int nType)
{
	static const char *emptyStr = "key or lang no found";
	hash_map<string, vector<string>, str_hash_str4i>::iterator hit;
	hit = m_mapKeyValues.find(pszKey);
	if (hit == m_mapKeyValues.end())
	{
		return emptyStr;
	}

	if ( nType > m_nTypeMax)
	{
		return emptyStr;
	}
	return hit->second.at(nType).c_str();
}

const char * CStr4I::GetErrMsg()
{
	return m_strErrMsg.c_str();
}

int  CStr4I::GetConfFilePath(const string & sBaseConfFilePath, int nLang, string & sConfFilePath)
{
	if (!m_bConfInitSucc)
	{
		return -1;
	}
	
	sConfFilePath.clear();
	if (nLang > m_nConfTypeMax)
	{
		m_strErrMsg = "bad conf lang id";

		return -2;
	}
	
	if (sBaseConfFilePath.find_last_of('/') == string::npos)
	{
		sConfFilePath =  sBaseConfFilePath + m_vsId2Mark.at(nLang);
	}
	else
	{
		sConfFilePath =  sBaseConfFilePath.substr(0, sBaseConfFilePath.find_last_of('/')) + "/" +    
			m_vsId2Mark.at(nLang) + sBaseConfFilePath.substr(sBaseConfFilePath.find_last_of('/'));
	}

	return 0;
}

int CStr4I::InitModuleId(const char * pszModuleIdFile)
{
	if (m_bModuleInitSucc)
	{
		return 0;
	}
	
	if (pszModuleIdFile == NULL)
	{
		m_strErrMsg = "pszModuleIdFile is NULL";

		return -1;
	}

	CMarkupSTL xml;
	if (!xml.Load(pszModuleIdFile))
	{
		m_strErrMsg = "load file:" + string(pszModuleIdFile) + " failed, err msg:" + xml.GetError();

		return -2;
	}
	if (!xml.FindElem("moduleid4i"))
	{
		m_strErrMsg = "find element str4i in file:" + string(pszModuleIdFile) + ", err msg:" + xml.GetError();

		return -3;
	}
	m_nModuleTypeMax = atoi(xml.GetAttrib("type_max").c_str());
	if (m_nModuleTypeMax < 0)
	{
		m_strErrMsg = "bad type_max:" + string(xml.GetAttrib("type_max").c_str());
		
		return -4;
	}

	if (!xml.IntoElem())
	{
		m_strErrMsg = "can't get into the moduleid4i element, err msg:" + xml.GetError();

		return -5;
	}

	int key;
	int type;
	m_mapModuleId.clear();
	while (xml.FindElem())
	{
		key = atoi(xml.GetAttrib("value").c_str());
		vector<int> vn;
		vn.resize(m_nModuleTypeMax + 1);
		while (xml.FindChildElem("id"))
		{
			xml.IntoElem();
			type = atoi(xml.GetAttrib("lang").c_str());
			if(type<0 || type>m_nModuleTypeMax)
			{
				m_strErrMsg = xml.GetAttrib("lang") + " bad type";
				
				return -6;
			}
			vn[type] = atoi(xml.GetData().c_str());
			xml.OutOfElem();
		}
		m_mapModuleId[key] = vn;
	}
	m_bModuleInitSucc = true;

	return 0;
}

int CStr4I::GetModuleId(const int nBaseId, int & nModuleId)
{
	if (!m_bModuleInitSucc)
	{
		m_strErrMsg = "module id init failed";
		
		return -1;
	}
	if (m_defaultType > m_nModuleTypeMax)
	{
		m_strErrMsg = "default type is illegal";

		return -2;
	}
	
	hash_map < int, vector < int > >::iterator hit;
	hit = m_mapModuleId.find(nBaseId);
	if (hit == m_mapModuleId.end())
	{
		m_strErrMsg = "can't find base id";
			
		return -3;
	}
	nModuleId =  hit->second.at(m_defaultType);

	return 0;
}


int CStr4I::ConfInit(const char * pszConfFile)
{
	if (pszConfFile == NULL)
	{
		m_strErrMsg = "ConfInit pszConfFile is NULL";

		return -1;
	}

	CMarkupSTL xml;
	if (!xml.Load(pszConfFile))
	{
		m_strErrMsg = "load file:" + string(pszConfFile) + " failed, err msg:" + xml.GetError();

		return -2;
	}
	if (!xml.FindElem("conf4i"))
	{
		m_strErrMsg = "find element conf4i in file:" + string(pszConfFile) + ", err msg:" + xml.GetError();

		return -3;
	}
	m_nConfTypeMax = atoi(xml.GetAttrib("type_max").c_str());
	if (m_nConfTypeMax < 0)
	{
		m_strErrMsg = "bad type_max:" + xml.GetAttrib("type_max");
		
		return -4;
	}
	if (!xml.IntoElem())
	{
		m_strErrMsg = "can't get into the conf4i element, err msg:" + xml.GetError();

		return -5;
	}

	m_vsId2Mark.resize(m_nConfTypeMax + 1);
	string sLang;
	int nLang;
	string sMark;
	while (xml.FindElem())
	{
		sLang = xml.GetAttrib("id");
		nLang = atoi(sLang.c_str());
		sMark = xml.GetData();
		
		if (nLang > m_nConfTypeMax || nLang < 0)
		{
			m_strErrMsg = "bad conf lang id:" + xml.GetAttrib("id");
			
			return -6;
		}
		m_vsId2Mark[nLang] = xml.GetData();
	}

	return 0;
}


