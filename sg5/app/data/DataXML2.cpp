/*
 * DataXML2.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */


#include "DataInc.h"
#include <math.h>
#include "OpenPlatform.h"
#include "IOpenPlatform.h"
#include "DataXmlUnit.h"
#include <stdexcept>


int CDataXML::GetSignInReward(int index, XMLSignInReward& reward)
{
	if (index < 0 || index >= SIGNIN_REWARDS_NUM)
	{
		return R_ERR_PARAM;
	}

	//reward = m_vXMLSignInReward[index];
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shsgsigninnewconfig)), true);

	DataXMLsgsigninnewconfig *pdata = (DataXMLsgsigninnewconfig *)m_shsgsigninnewconfig.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	reward = pdata->rewards[index];

	return R_SUCCESS;
}

int CDataXML::GetInviteLevelItem(unsigned id, XMLInviteLevelGiftItem& item)
{
    std::map<unsigned, unsigned>::iterator it = m_mapXMLInvite.find(id);
    if (it == m_mapXMLInvite.end())
    {
        return R_ERR_PARAM;
    }

    CAutoLock lock(const_cast<CShareMemory*>(&(m_shsginvitegiftconfig)), true);
    DataXMLsginvitegiftconfig *pdata = (DataXMLsginvitegiftconfig *)m_shsginvitegiftconfig.GetAddress();
    if(NULL == pdata)
    {
        return R_ERR_DB;
    }

    if (it->second < XML_INVITE_LEVEL_ITEMS_MAX)
    {
        item = pdata->levelItems[it->second];
    }

	return R_SUCCESS;
}

int CDataXML::InitBarbarKing()
{
	int ret = 0;

	DataXMLBarbar *pdata = (DataXMLBarbar *)m_shBarbar.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shBarbar), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("barbarianconfig.xml", dataPath);
	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("conten node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("barbarian_king"))
	{
		cout << ("barbarian_king node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	unsigned eqid = 0;
	unsigned c = 0;

	while (xmlConf.FindElem("level"))
	{
		xmlConf.IntoElem();

		if (!xmlConf.FindElem("rewards"))
		{
			cout << ("rewards node wrong") << endl;
			return R_ERROR;
		}
		xmlConf.IntoElem();

		unsigned j = 0;
		while (xmlConf.FindElem("reward"))
		{
			string context = xmlConf.GetData();
			Json::Value reward;
			Json::FromString(reward, context);
			eqid = reward["reward"]["equip1"]["id"].asUInt();
			c = reward["reward"]["equip1"]["c"].asUInt();

			pdata->reward[i][j].eqid = eqid;
			pdata->reward[i][j].c = c;
			++j;
		}
		xmlConf.OutOfElem();
		xmlConf.OutOfElem();

		/*
		j = 0;
		while (xmlConf.FindElem("king"))
		{
			string cost = xmlConf.GetAttrib("cost");
			string score = xmlConf.GetAttrib("score");

			pdata->reward[i][j].cost = CTrans::STOI(cost);
			pdata->reward[i][j].score = CTrans::STOI(score);
			++j;
		}
		xmlConf.OutOfElem();
		*/

		++i;
	}

	m_shBarbar.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::InitFiveTiger()
{
	int ret = 0;

	DataXMLFiveTiger *pdata = (DataXMLFiveTiger *)m_shFiveTiger.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shFiveTiger), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("fivetigerconfig.xml", dataPath);
	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("conten node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("fivetiger"))
	{
		cout << ("fivetiger node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	unsigned i = 0;

	while (xmlConf.FindElem("zhang"))
	{
		xmlConf.IntoElem();

		unsigned j = 0;
		while (xmlConf.FindElem("gate"))
		{
			string reward = xmlConf.GetAttrib("rewardId");
			unsigned yl = CTrans::STOI(reward.substr(7));
			pdata->addyl[i][j] = yl / 2;
			++j;
		}

		xmlConf.OutOfElem();

		++i;
	}

	m_shFiveTiger.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetFiveTigerItem(unsigned chapter, unsigned sgate, unsigned egate, unsigned &yl, Json::Value &result)
{
	if (chapter >= XMLFIVETIGER_CHAPTER_NUM || sgate >= XMLFIVETIGER_GATE_NUM
			|| (egate >= XMLFIVETIGER_GATE_NUM))
	{
		error_log("chapter = %u, sgate = %u, egate = %u", chapter, sgate, egate);
		return R_ERR_DATA;
	}

	DataXMLFiveTiger *pdata = (DataXMLFiveTiger *)m_shFiveTiger.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory *>(&(m_shFiveTiger)), true);

	yl = 0;

	for (unsigned i = sgate, j = 0; i <= egate; ++i, ++j)
	{
		result[j] = pdata->addyl[chapter][i];
		yl += pdata->addyl[chapter][i];
	}


	return R_SUCCESS;
}


int CDataXML::GetBarbarKingItem(unsigned index, unsigned gate, XMLBarbarItem &item)
{
	if ((index >= XMLBARBARKING_NUM) || (gate >= XMLBARBARKING_GATE_NUM))
	{
		error_log("index: %u, gate: %u", index, gate);
		return R_ERR_DATA;
	}

	DataXMLBarbar *pdata = (DataXMLBarbar *)m_shBarbar.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory *>(&(m_shBarbar)), true);

	item = pdata->reward[index][gate];

	return R_SUCCESS;
}


int CDataXML::GetDouble11AllData(DataXMLDouble11 &dataDouble)
{
	DataXMLDouble11 *pdata = (DataXMLDouble11 *)m_shDouble11.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory *>(&(m_shDouble11)), true);

	dataDouble = *pdata;
	return R_SUCCESS;
}



int CDataXML::GetFile(const string &fname, string &path)
{
	if (fname.empty())
	{
		cout << ("fname is empty") << endl;
		return R_ERROR;
	}

	path = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (path.empty())
	{
		cout << ("data path is empty") << endl;
		return R_ERROR;
	}

	if ('/' != path[path.length() - 1])
	{
		path.append("/");
	}

	path.append(fname);

	return R_SUCCESS;
}


int CDataXML::readJsonConfFile(const string &fname, Json::Value &jdata)
{
	int ret = 0;

	string path;

	ret = GetFile(fname, path);
	if (ret)
	{
		return ret;
	}

	string data;

	ret = File::Read(path, data);
	if (ret)
	{
		error_log("File Read failed. ret = %u", ret);
		return ret;
	}

	Json::Reader reader;

	if (!reader.parse(data, jdata))
	{
		string reason = reader.getFormatedErrorMessages();
		error_log("reader parse failed. reason = %s", reason.c_str());
		return R_ERR_DATA;
	}

	return R_SUCCESS;
}


int CDataXML::InitEggReward()
{
	int ret = 0;
	Json::Value data;

	ret = readJsonConfFile("goldenEggconfig.json", data);
	if (ret)
	{
		return ret;
	}

	if (!data.isArray())
	{
		error_log("goldenEggconfig.json is error");
		return R_ERR_DATA;
	}


	for (unsigned i = 0; i < data.size(); ++i)
	{
		EggRewardItem eri;
		EggReward er;

		er.weight = data[i]["weight"].asUInt();

		for (unsigned j = 0; j < data[i]["item"].size(); ++j)
		{
			eri.eqid = data[i]["item"][j]["id"].asString();
			eri.count = data[i]["item"][j]["count"].asUInt();
			eri.rate = data[i]["item"][j]["rate"].asUInt();
			eri.warn = data[i]["item"][j]["warn"].asUInt();
			er.items.push_back(eri);
		}

		m_eggrwd.push_back(er);
	}

	return R_SUCCESS;
}


int CDataXML::addforbidPool(unsigned forbid, set<unsigned> &quforbid)
{
	static const unsigned queuenum = 6;
	static const unsigned que[queuenum][2] =
	{
			{2, 3},
			{2, 4},
			{3, 4},
			{3, 2},
			{4, 2},
			{4, 3},
	};

	if (!quforbid.count(forbid))
	{
		for (unsigned i = 0; i < queuenum; ++i)
		{
			if (que[i][0] == forbid)
			{
				quforbid.insert(que[i][1]);
			}
		}

		quforbid.insert(forbid);
	}


	return R_SUCCESS;
}


int CDataXML::genUsePool(unsigned opool, set<unsigned> &quforbid, unsigned &upool)
{
	// 当没有选到合适的 pool 时使用以前的 pool
	upool = opool;

	unsigned limit = 100;
	unsigned rnum = 0;
	unsigned i = 0;
	unsigned len = m_eggrwd.size();
	unsigned weight = m_eggrwd[len - 1].weight;

	do
	{
		rnum = Math::GetRandomInt(weight);

		for (i = 0; i < len; ++i)
		{
			if (rnum < m_eggrwd[i].weight)
			{
				break;
			}
		}

		if (!quforbid.count(i))
		{
			upool = i;
			break;
		}
	}while(limit--);

	return R_SUCCESS;
}


int CDataXML::GetEggItems(unsigned lock, Json::Value &newAct, vector<EggRewardItem> &getitem)
{
	set<unsigned> quforbid;
	set<string> eqidforbid;
	vector<unsigned> aupool;

	unsigned limit = 0;
	string eqid;
	unsigned ique = 0;

	if (lock < 2)
	{
		eqid = newAct["eq"][lock].asString();
		ique = newAct["d"][lock].asUInt();

		if (!eqid.empty())
		{
			eqidforbid.insert(eqid);
			aupool.push_back(ique);
		}

		eqid = newAct["eq"][1 - lock].asString();
		ique = newAct["d"][1 - lock].asUInt();

		if (!eqid.empty())
		{
			eqidforbid.insert(eqid);
			addforbidPool(ique, quforbid);
		}

		limit = 1;
	}
	else if (2 == lock)
	{
		for (unsigned i = 0; i < lock; ++i)
		{
			eqid = newAct["eq"][i].asString();
			ique = newAct["d"][i].asUInt();

			if (!eqid.empty())
			{
				eqidforbid.insert(eqid);
			}
		}
		limit = 2;
	}

	unsigned cpool = 0;
	unsigned fpool = 0;

	for (unsigned i = 0; i < limit; ++i)
	{
		if (i < aupool.size())
		{
			fpool = aupool[i];
		}

		genUsePool(fpool, quforbid, cpool);

		vector<EggRewardItem> &items = m_eggrwd[cpool].items;

		unsigned itemlen = items.size();

		unsigned rate = items[itemlen - 1].rate;

		unsigned rnum = Math::GetRandomInt(rate);

		unsigned j = 0;
		for (j = 0; j < itemlen; ++j)
		{
			if (rnum < items[j].rate)
			{
				break;
			}
		}

		unsigned ri = j;
		if (eqidforbid.count(items[j].eqid))
		{
			// 使用下一个
			ri = (j + 1) % itemlen;
		}

		getitem.push_back(items[ri]);
		eqidforbid.insert(items[ri].eqid);

		if (2 == lock)
		{
			newAct["d"][i] = cpool;
		}
		else if (lock < 2)
		{
			newAct["d"][lock] = cpool;
		}

		// 两个框不能出现在同一个 pool 中
		addforbidPool(cpool, quforbid);
		fpool = (0 == cpool) ? 1 : 0;
	}

	return R_SUCCESS;
}

int CDataXML::InitNewJueShiWS()
{
	int ret = 0;

	DataXMLNewJueshiWS *pdata = (DataXMLNewJueshiWS *)m_shNewJueshiWS.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shNewJueshiWS), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("mystichero.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("conten node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("exange"))
	{
		cout << ("exange node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int index = 0;

	while (xmlConf.FindElem("item") && index < MAX_HERO_NUM)
	{
		string id = xmlConf.GetAttrib("id");
		string heroid = xmlConf.GetAttrib("hid");
		string price = xmlConf.GetAttrib("price");

		if (id.empty() || heroid.empty() || price.empty())
		{
			cerr<<"[mystichero.xml] content->exchange->item["<<index<<"] attribute id or hid or price have no value"<<endl;
			return R_ERROR;
		}

		pdata->heroitems[index].id =  CTrans::STOI(id.c_str());
		if (heroid[0] == 'H')
		{
			pdata->heroitems[index].heroid = CTrans::STOI(heroid.substr(1).c_str());
			pdata->heroitems[index].isHero = true;
		}
		else
		{
			pdata->heroitems[index].heroid = CTrans::STOI(heroid.c_str());
			pdata->heroitems[index].isHero = false;
		}

		pdata->heroitems[index].point = CTrans::STOI(price.c_str());

		++index;
	}

	m_shNewJueshiWS.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetNewJueShiWSItem(unsigned id, XMLNewJueShiWS & item, unsigned & index)
{
	map<unsigned, unsigned>::iterator uiter;

	if (m_mapJueshiWS.end() == (uiter = m_mapJueshiWS.find(id)))
	{
		return R_ERR_PARAM;
	}

	index = uiter->second;

	DataXMLNewJueshiWS *pdata = (DataXMLNewJueshiWS *)m_shNewJueshiWS.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shNewJueshiWS)), true);

	item = pdata->heroitems[index];

	return R_SUCCESS;
}

int CDataXML::InitOpporKnockReward()
{
	int ret = 0;

	DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shOpporknock), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("opporknock.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("[opporknock.xml] data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("[opporknock.xml] conten node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	//读取概率
	if (!xmlConf.FindElem("rate"))
	{
		cout << ("[opporknock.xml] rate node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	Json::Value value;

	//加载钻石和积分的概率
	if (!xmlConf.FindElem("cash"))
	{
		cout << ("[opporknock.xml] rate->cash node wrong") << endl;
		return R_ERROR;
	}

	if (! Json::FromString(value, xmlConf.GetAttrib("rate")) || !value.isArray())
	{
		cout << "[opporknock.xml] => content->rate->cash's attribute rate is null, or not array."<< endl;
		return R_ERROR;
	}

	for (unsigned i = 0; i < value.size() && i < TURN_TABLE_ITEMS_MAX; ++i)
	{
		pdata->cashrate[i] = value[i].asInt();
	}

	if (!xmlConf.FindElem("point"))
	{
		cout << ("[opporknock.xml] rate->point node wrong") << endl;
		return R_ERROR;
	}

	if (! Json::FromString(value, xmlConf.GetAttrib("rate")) || !value.isArray())
	{
		cout << "[opporknock.xml] => content->rate->point's attribute rate is null, or not array."<< endl;
		return R_ERROR;
	}

	for (unsigned i = 0; i < value.size() && i < TURN_TABLE_ITEMS_MAX; ++i)
	{
		pdata->pointrate[i] = value[i].asInt();
	}

	//循环读取刷新奖池的数据
	int index = 0;
	xmlConf.OutOfElem();

	if (!xmlConf.FindElem("refresh"))
	{
		cout << ("content->refresh node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	while (xmlConf.FindElem("reward") && index < REFRESH_ITEMS_MAX)
	{
		string id = xmlConf.GetAttrib("id");

		string num = xmlConf.GetAttrib("num");
		string rate = xmlConf.GetAttrib("rate");

		string eqid = xmlConf.GetAttrib("eqid");
		string heroid = xmlConf.GetAttrib("heroid");


		if (id.empty() || num.empty() || rate.empty() ||(eqid.empty() && heroid.empty()) )
		{
			cerr<<"[opporknock.xml] content->refresh->reward["<<index<<"] attribute id or num or rate or eqid and heroid have no value"<<endl;
			return R_ERROR;
		}

		if (!eqid.empty())   //装备
		{
			pdata->refreshpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->refreshpools.allitems[index].eqid = CTrans::STOI(eqid.c_str());
			pdata->refreshpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->refreshpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->refreshpools.allitems[index].isHero = 0;
		}
		else if (!heroid.empty())  //英雄
		{
			pdata->refreshpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->refreshpools.allitems[index].eqid = CTrans::STOI(heroid.substr(1).c_str());
			pdata->refreshpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->refreshpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->refreshpools.allitems[index].isHero = 1;
		}

		++pdata->refreshpools.itemcount;

		++index;
	}

	xmlConf.OutOfElem();

	if (!xmlConf.FindElem("left"))
	{
		cout << ("content->left node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	index = 0;

	while (xmlConf.FindElem("reward") && index < EXTRA_ITEMS_MAX)
	{
		string id = xmlConf.GetAttrib("id");

		string num = xmlConf.GetAttrib("num");
		string rate = xmlConf.GetAttrib("rate");

		string eqid = xmlConf.GetAttrib("eqid");
		string heroid = xmlConf.GetAttrib("heroid");


		if (id.empty() || num.empty() || rate.empty() ||(eqid.empty() && heroid.empty()) )
		{
			cerr<<"[opporknock.xml] content->left->reward["<<index<<"] attribute id or num or rate or eqid and heroid have no value"<<endl;
			return R_ERROR;
		}

		if (!eqid.empty())
		{
			pdata->leftpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->leftpools.allitems[index].eqid = CTrans::STOI(eqid.c_str());
			pdata->leftpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->leftpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->leftpools.allitems[index].isHero = 0;
		}
		else if (!heroid.empty())
		{
			pdata->leftpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->leftpools.allitems[index].eqid = CTrans::STOI(heroid.substr(1).c_str());
			pdata->leftpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->leftpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->leftpools.allitems[index].isHero = 1;
		}

		++pdata->leftpools.itemcount;

		++index;
	}

	xmlConf.OutOfElem();

	if (!xmlConf.FindElem("right"))
	{
		cout << ("content->right node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	index = 0;

	while (xmlConf.FindElem("reward") && index < EXTRA_ITEMS_MAX)
	{
		string id = xmlConf.GetAttrib("id");

		string num = xmlConf.GetAttrib("num");
		string rate = xmlConf.GetAttrib("rate");

		string eqid = xmlConf.GetAttrib("eqid");
		string heroid = xmlConf.GetAttrib("heroid");


		if (id.empty() || num.empty() || rate.empty() ||(eqid.empty() && heroid.empty()) )
		{
			cerr<<"[opporknock.xml] content->right->reward["<<index<<"] attribute id or num or rate or eqid and heroid have no value"<<endl;
			return R_ERROR;
		}

		if (!eqid.empty())
		{
			pdata->rightpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->rightpools.allitems[index].eqid = CTrans::STOI(eqid.c_str());
			pdata->rightpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->rightpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->rightpools.allitems[index].isHero = 0;
		}
		else if (!heroid.empty())
		{
			pdata->rightpools.allitems[index].id = CTrans::STOI(id.c_str());
			pdata->rightpools.allitems[index].eqid = CTrans::STOI(heroid.substr(1).c_str());
			pdata->rightpools.allitems[index].count = CTrans::STOI(num.c_str());
			pdata->rightpools.allitems[index].rate = CTrans::STOI(rate.c_str());
			pdata->rightpools.allitems[index].isHero = 1;
		}

		++pdata->rightpools.itemcount;

		++index;
	}

	xmlConf.OutOfElem();

	m_shOpporknock.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetTurnRate(unsigned type, int * & prates)
{
	DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shOpporknock)), true);

	if (TURN_BY_CASH == type)
	{
		prates = pdata->cashrate;
	}
	else if (TURN_BY_POINT == type)
	{
		prates = pdata->pointrate;
	}
	else
	{
		return R_ERR_PARAM;
	}

	return R_SUCCESS;
}

int CDataXML::GetOpporKnockRewardById(unsigned id, EquipmentRateInfo & equipitem)
{
	map<unsigned, unsigned>::iterator uiter;

	if (m_mapRefresh.end() == (uiter = m_mapRefresh.find(id)))
	{
		return R_ERR_PARAM;
	}

	DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shOpporknock)), true);

	equipitem = pdata->refreshpools.allitems[uiter->second];

	return R_SUCCESS;
}

int CDataXML::GetRefreshPoolItem(XMLRefreshPoolItem & item)
{
	DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shOpporknock)), true);

	item = pdata->refreshpools;

	return R_SUCCESS;
}

int CDataXML::GetSecondPoolItem(unsigned type, XMLSecondPoolItem & items)
{
	DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shOpporknock)), true);

	if (POOL_TO_LEFT == type)
	{
		items = pdata->leftpools;
	}
	else if (POOL_TO_RIGHT == type)
	{
		items = pdata->rightpools;
	}
	else
	{
		return R_ERR_PARAM;
	}

	return R_SUCCESS;
}

int CDataXML::InitFortunatelyAgain()
{
	int ret = 0;

	DataXMLFortunatelyAgain *pdata = (DataXMLFortunatelyAgain *)m_shFortunatelyAgain.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shFortunatelyAgain), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("luckylink.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("[luckylink.xml] data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("[luckylink.xml] content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int index = 0;

	while(xmlConf.FindElem("pool") && index < MAX_POOL_ITEMS)
	{
		int weight_index = pdata->poolitems[index].weightcount;

		xmlConf.IntoElem();

		while(xmlConf.FindElem("weight") && weight_index < MAX_WEIGHT_ITEMS)
		{
			weight_index = pdata->poolitems[index].weightcount;

			string id = xmlConf.GetAttrib("id");

			if (id.empty())
			{
				cerr<<"[luckylink.xml] content->pool["<<index<<"]->weight["<<weight_index<<"] attribute id have no value"<<endl;
				return R_ERROR;
			}

			pdata->poolitems[index].weightrate[weight_index] = CTrans::STOI(id.c_str());

			xmlConf.IntoElem();

			int equip_index = 0;

			while(xmlConf.FindElem("equip") && equip_index < MAX_EQUIPMENT_ITEMS)
			{
				string eqid = xmlConf.GetAttrib("id");
				string count = xmlConf.GetAttrib("count");
				string strindex = xmlConf.GetAttrib("index");

				if (eqid.empty() || count.empty() || strindex.empty())
				{
					cerr<<"[luckylink.xml] content->pool["<<index<<"]->weight["<<weight_index<<"]->equip["<<equip_index <<"] attribute id or count or index have no value"<<endl;
					return R_ERROR;
				}

				//判断是装备还是英雄
				if (string::npos == eqid.find('H'))   //装备
				{
					pdata->poolitems[index].weightItems[weight_index][equip_index].id = CTrans::STOI(eqid.c_str());
				}
				else
				{
					pdata->poolitems[index].weightItems[weight_index][equip_index].id = CTrans::STOI(eqid.substr(1).c_str());
					pdata->poolitems[index].weightItems[weight_index][equip_index].isHero = 1;
				}

				pdata->poolitems[index].weightItems[weight_index][equip_index].count = CTrans::STOI(count.c_str());
				pdata->poolitems[index].weightItems[weight_index][equip_index].index = CTrans::STOI(strindex.c_str());

				++equip_index;
			}

			++pdata->poolitems[index].weightcount;
			xmlConf.OutOfElem();
		}

		++index;

		xmlConf.OutOfElem();
	}

	xmlConf.OutOfElem();

	m_shFortunatelyAgain.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetFortunatelyRewardItem(int type, XMLFortunatelyRewardItems & item)
{
	if (type < POOL_SEQUENCE_ONE || type > POOL_SEQUENCE_THREE)
	{
		return R_ERR_PARAM;
	}

	DataXMLFortunatelyAgain *pdata = (DataXMLFortunatelyAgain *)m_shFortunatelyAgain.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFortunatelyAgain)), true);

	item = pdata->poolitems[type];

	return R_SUCCESS;
}

int CDataXML::GetSingleEquipItem(unsigned index, EquipmentInfo & iteminfo)
{
	map<unsigned, EquipIndex>::iterator eiter;

	if (m_mapEquipIndex.end() == (eiter = m_mapEquipIndex.find(index)) )
	{
		return R_ERR_PARAM;
	}

	DataXMLFortunatelyAgain *pdata = (DataXMLFortunatelyAgain *)m_shFortunatelyAgain.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFortunatelyAgain)), true);

	int pindex = eiter->second.poolindex;
	int windex = eiter->second.weightindex;
	int eindex = eiter->second.equipindex;

	iteminfo = pdata->poolitems[pindex].weightItems[windex][eindex];

	return R_SUCCESS;
}

int CDataXML::InitTurnPlate()
{
	int ret = 0;

	DataXMLTurnPlate *pdata = (DataXMLTurnPlate *)m_shTurnPlate.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shTurnPlate), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("turnplateconfig.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("[turnplateconfig.xml] data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int index = 0;

	while(xmlConf.FindElem("pool") && index < MAX_TURLPLATE_POOL_ITEMS)
	{
		int weight_index = 0;

		xmlConf.IntoElem();

		while(xmlConf.FindElem("weight") && weight_index < MAX_WEIGHT_ITEMS)
		{
			weight_index = pdata->poolitems[index].weightcount;

			string id = xmlConf.GetAttrib("id");

			if (id.empty())
			{
				cerr<<"content->pool["<<index<<"]->weight["<<weight_index<<"] attribute id have no value"<<endl;
				return R_ERROR;
			}

			pdata->poolitems[index].weightrate[weight_index] = CTrans::STOI(id.c_str());   //id就代表出席的概率

			xmlConf.IntoElem();

			int equip_index = 0;

			while(xmlConf.FindElem("equip") && equip_index < MAX_EQUIPMENT_ITEMS)
			{
				string eqid = xmlConf.GetAttrib("id");
				string count = xmlConf.GetAttrib("count");
				string strindex = xmlConf.GetAttrib("index");

				if (eqid.empty() || count.empty() || strindex.empty())
				{
					cerr<<"content->pool["<<index<<"]->weight["<<weight_index<<"]->equip["<<equip_index <<"] attribute id or count or index have no value"<<endl;
					return R_ERROR;
				}

				//判断是装备还是英雄
				if (string::npos == eqid.find('H'))   //装备
				{
					pdata->poolitems[index].weightItems[weight_index][equip_index].id = CTrans::STOI(eqid.c_str());
				}
				else
				{
					pdata->poolitems[index].weightItems[weight_index][equip_index].id = CTrans::STOI(eqid.substr(1).c_str());
					pdata->poolitems[index].weightItems[weight_index][equip_index].isHero = 1;
				}

				pdata->poolitems[index].weightItems[weight_index][equip_index].count = CTrans::STOI(count.c_str());
				pdata->poolitems[index].weightItems[weight_index][equip_index].index = CTrans::STOI(strindex.c_str());

				++equip_index;
			}

			++pdata->poolitems[index].weightcount;
			xmlConf.OutOfElem();
		}

		++index;

		xmlConf.OutOfElem();
	}

	xmlConf.OutOfElem();

	m_shTurnPlate.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetTurnPlateRewardItem(int type, XMLFortunatelyRewardItems & item)
{
	if (type < POOL_TURN_SEQUENCE_ONE || type >= POOL_TURN_SEQUENCE_MAX)
	{
		return R_ERR_PARAM;
	}

	DataXMLTurnPlate *pdata = (DataXMLTurnPlate *)m_shTurnPlate.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTurnPlate)), true);

	item = pdata->poolitems[type];

	return R_SUCCESS;
}

int CDataXML::GetTurnPlateSingleEquipItem(unsigned index, EquipmentInfo & iteminfo)
{
	map<unsigned, EquipIndex>::iterator eiter;

	if (m_mapTurnEquipIndex.end() == (eiter = m_mapTurnEquipIndex.find(index)) )
	{
		return R_ERR_PARAM;
	}

	DataXMLTurnPlate *pdata = (DataXMLTurnPlate *)m_shTurnPlate.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTurnPlate)), true);

	int pindex = eiter->second.poolindex;
	int windex = eiter->second.weightindex;
	int eindex = eiter->second.equipindex;

	iteminfo = pdata->poolitems[pindex].weightItems[windex][eindex];

	return R_SUCCESS;
}

int CDataXML::InitRechargeOptional()
{
	int ret = 0;

	DataXMLRechargeOptional *pdata = (DataXMLRechargeOptional *)m_shRechargeOptional.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shRechargeOptional), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("newActivity.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("[newActivity.xml] data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("[newActivity.xml] content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	if (!xmlConf.FindElem("qixirecharge"))
	{
		cout << ("[newActivity.xml] content->qixirecharge node wrong") << endl;
		return R_ERROR;
	}

	//获取per属性
	string strper = xmlConf.GetAttrib("per");

	if (strper.empty())
	{
		cout << ("[newActivity.xml] content->qixirecharge's attribute per have no value") << endl;
		return R_ERROR;
	}

	pdata->per = CTrans::STOI(strper.c_str());

	int index = 0;

	xmlConf.IntoElem();

	while(xmlConf.FindElem("item") && index < OPTIONAL_ITEMS_MAX)
	{
		string id = xmlConf.GetAttrib("id");

		if (id.empty())
		{
			cout <<"[newActivity.xml] content->qixirecharge->item["<<index<<"]'s attribute id have no value"<< endl;
			return R_ERROR;
		}

		Json::Value rewardValue;

		if (! Json::FromString(rewardValue, xmlConf.GetData()))
		{
			cout << "[newActivity.xml] content->qixirecharge->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		unsigned eqid = 0, count = 0;

		if (!rewardValue.isMember("reward") || ! rewardValue["reward"].isMember("equip1") || !rewardValue["reward"]["equip1"].isMember("id") || !rewardValue["reward"]["equip1"].isMember("c"))
		{
			cout << "[newActivity.xml] content->qixirecharge->item["<<index<<"]'s value format error.have no equip1 or id or c keys"<< endl;
			return R_ERROR;
		}

		Json::GetUInt(rewardValue["reward"]["equip1"], "id", eqid);
		Json::GetUInt(rewardValue["reward"]["equip1"], "c", count);

		pdata->items[index].id = CTrans::STOI(id.c_str());
		pdata->items[index].eqid = eqid;
		pdata->items[index].count = count;

		++index;
	}

	xmlConf.OutOfElem();

	pdata->itemcount = index;

	m_shRechargeOptional.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetOptionalRewardItem(vector<unsigned> vctid, vector<XMLOptionalItems> & vctitem, unsigned & per)
{
	map<unsigned, unsigned>::iterator uiter;

	DataXMLRechargeOptional *pdata = (DataXMLRechargeOptional *)m_shRechargeOptional.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shRechargeOptional)), true);

	for(unsigned i = 0; i < vctid.size(); ++i)
	{
		if (m_mapOptional.end() == (uiter = m_mapOptional.find(vctid[i])) )
		{
			return R_ERR_PARAM;
		}

		vctitem.push_back(pdata->items[uiter->second]);
	}

	per = pdata->per;

	return R_SUCCESS;
}

int CDataXML::InitSoldierTrainAndUp()
{
	int ret = 0;

	DataXMLSoldierTrainAndUp *pdata = (DataXMLSoldierTrainAndUp *)m_shSoldierTrainAndUp.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shSoldierTrainAndUp), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("soldier_new.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int kind = 0;

	while(xmlConf.FindElem("soldier") && kind < MAX_SOLDIER_KIND)
	{
		string id, grade;
		id = xmlConf.GetAttrib("id");
		grade = xmlConf.GetAttrib("grade");

		if (id.empty() || grade.empty())
		{
			cout<<"content->soldier["<<kind<<"] 's attribute id or grade is empty"<<endl;
			return R_ERROR;
		}

		xmlConf.IntoElem();

		if (!xmlConf.FindElem("produce_time"))
		{
			cout<<"content->soldier["<<kind<<"]->produce_time error."<<endl;
			return R_ERROR;
		}

		Json::Value ptimeval;
		Json::FromString(ptimeval, xmlConf.GetData());

		//start
		if (!xmlConf.FindElem("research_time"))
		{
			cout<<"content->soldier["<<kind<<"]->research_time error."<<endl;
			return R_ERROR;
		}

		Json::Value rtimeval;
		Json::FromString(rtimeval, xmlConf.GetData());
		//end
		if (!xmlConf.FindElem("cost"))
		{
			cout<<"content->soldier["<<kind<<"]->cost error."<<endl;
			return R_ERROR;
		}

		Json::Value costval;
		Json::FromString(costval, xmlConf.GetData());

		//end
		if (!xmlConf.FindElem("silver"))
		{
			cout<<"content->soldier["<<kind<<"]->silver error."<<endl;
			return R_ERROR;
		}

		Json::Value silverval;
		Json::FromString(silverval, xmlConf.GetData());
		//end
		if (!xmlConf.FindElem("silver_type"))
		{
			cout<<"content->soldier["<<kind<<"]->silver_type error."<<endl;
			return R_ERROR;
		}

		Json::Value typeval;
		Json::FromString(typeval, xmlConf.GetData());
		//end
		if (!xmlConf.FindElem("locklevel"))
		{
			cout<<"content->soldier["<<kind<<"]->locklevel error."<<endl;
			return R_ERROR;
		}

		Json::Value locklevelval;
		Json::FromString(locklevelval, xmlConf.GetData());
		//end

		if (ptimeval.size() != rtimeval.size() || rtimeval.size() != costval.size() || costval.size() != silverval.size() ||
				silverval.size() != typeval.size() || typeval.size() != locklevelval.size())
		{
			cout<<"every array's length must be same"<<endl;
			return R_ERROR;
		}

		pdata->soldieritems[kind].sid =  CTrans::STOI(id.substr(1).c_str());
		pdata->soldieritems[kind].grade =  CTrans::STOI(grade.c_str());

		for (unsigned i = 0; i < ptimeval.size() && i <= MAX_SOLDIER_LEVEL ; ++i)
		{
			pdata->soldieritems[kind].levelitems[i].locklevel = locklevelval[i].asUInt();
			pdata->soldieritems[kind].levelitems[i].silvertype = typeval[i].asUInt();
			pdata->soldieritems[kind].levelitems[i].rtime = rtimeval[i].asUInt();
			pdata->soldieritems[kind].levelitems[i].ptime = ptimeval[i].asUInt();
			pdata->soldieritems[kind].levelitems[i].cost = costval[i].asUInt();
			pdata->soldieritems[kind].levelitems[i].silver = silverval[i].asUInt();
		}

		xmlConf.OutOfElem();

		++kind;
	}

	m_shSoldierTrainAndUp.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetSoldierLevelItem(unsigned sid, unsigned level, XMLSoldierLevelItems & levelitem, unsigned char & grade)
{
	if (level > MAX_SOLDIER_LEVEL)
	{
		return R_ERR_PARAM;
	}

	map<unsigned, unsigned>::iterator uiter;

	if (m_mapSoldier.end() == (uiter = m_mapSoldier.find(sid)))
	{
		return R_ERR_PARAM;
	}

	DataXMLSoldierTrainAndUp *pdata = (DataXMLSoldierTrainAndUp *)m_shSoldierTrainAndUp.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shSoldierTrainAndUp)), true);

	levelitem = pdata->soldieritems[uiter->second].levelitems[level];
	grade = pdata->soldieritems[uiter->second].grade;

	return R_SUCCESS;
}

int CDataXML::InitHeavenDAOSkill()
{
	int ret = 0;

	DataXMLHeavenDaoSkill *pdata = (DataXMLHeavenDaoSkill *)m_shHeavenDaoSkill.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shHeavenDaoSkill), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("heavenConfig.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	if (!xmlConf.FindElem("buildingskill"))
	{
		cout << ("content->buildingskill node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int kind = 0;

	while(xmlConf.FindElem("skill") && kind < MAX_DAO_SKILL_ITEMS)
	{
		string id, stage, book, bookid;

		id = xmlConf.GetAttrib("id");
		stage = xmlConf.GetAttrib("stage");
		book = xmlConf.GetAttrib("book");
		bookid = xmlConf.GetAttrib("bookid");

		if (id.empty() || stage.empty() || book.empty() || bookid.empty())
		{
			cout<<"content->buildingskill->skill["<<kind<<"] 's attribute id or stage or book or bookid is empty"<<endl;
			return R_ERROR;
		}

		pdata->daoitem[kind].id =  CTrans::STOI(id.c_str());
		pdata->daoitem[kind].stage =  CTrans::STOI(stage.c_str());
		pdata->daoitem[kind].bookid =  CTrans::STOI(bookid.c_str());

		vector<string> vecbook;

		String::Split(book, ',', vecbook);

		for(size_t i = 0; i < vecbook.size() && i < MAX_SKILL_LEVEL; ++i)
		{
			pdata->daoitem[kind].booknum[i] = CTrans::STOI(vecbook[i].c_str());
		}

		++kind;
	}

	xmlConf.OutOfElem();

	//加载兵书相关配置

	if (!xmlConf.FindElem("heroskill"))
	{
		cout << ("content->heroskill node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int hkind = 0;

	while(xmlConf.FindElem("skill") && hkind < MAX_HEAVEN_SKILL_ITEMS)
	{
		string id, stage, book, bookid;

		id = xmlConf.GetAttrib("id");
		stage = xmlConf.GetAttrib("stage");
		book = xmlConf.GetAttrib("book");
		bookid = xmlConf.GetAttrib("bookid");

		if (id.empty() || stage.empty() || book.empty() || bookid.empty())
		{
			cout<<"content->heroskill->skill["<<kind<<"] 's attribute id or stage or book or bookid is empty"<<endl;
			return R_ERROR;
		}

		pdata->heavenitem[hkind].id =  CTrans::STOI(id.c_str());
		pdata->heavenitem[hkind].stage =  CTrans::STOI(stage.c_str());
		pdata->heavenitem[hkind].bookid =  CTrans::STOI(bookid.c_str());

		vector<string> vecbook;

		String::Split(book, ',', vecbook);

		for(size_t i = 0; i < vecbook.size() && i < MAX_SKILL_LEVEL; ++i)
		{
			pdata->heavenitem[hkind].booknum[i] = CTrans::STOI(vecbook[i].c_str());

			//cout<<"\n num:"<<(int)pdata->heavenitem[hkind].booknum[i]<<",";
		}

		++hkind;
	}

	xmlConf.OutOfElem();

	m_shHeavenDaoSkill.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetHeavenSkillItem(unsigned id, XMLHeavenDaoSkillItem & skillitem)
{
	map<unsigned, unsigned>::iterator uiter;

	if (m_mapHeaven.end() == (uiter = m_mapHeaven.find(id)))
	{
		return R_ERR_PARAM;
	}

	DataXMLHeavenDaoSkill *pdata = (DataXMLHeavenDaoSkill *)m_shHeavenDaoSkill.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeavenDaoSkill)), true);

	skillitem = pdata->heavenitem[uiter->second];

	return R_SUCCESS;
}

int CDataXML::GetDAOSkillItem(unsigned id, XMLHeavenDaoSkillItem & skillitem)
{
	map<unsigned, unsigned>::iterator uiter;

	if (m_mapDAO.end() == (uiter = m_mapDAO.find(id)))
	{
		return R_ERR_PARAM;
	}

	DataXMLHeavenDaoSkill *pdata = (DataXMLHeavenDaoSkill *)m_shHeavenDaoSkill.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeavenDaoSkill)), true);

	skillitem = pdata->daoitem[uiter->second];

	return R_SUCCESS;
}


/**************FashionShop**********************/
int CDataXML::InitFashionShop()
{
	DataXMLFashionShop *pdata = (DataXMLFashionShop *)m_shFashionShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shFashionShop), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	if (!xmlConf.FindElem("fashionshop"))
	{
		cout << ("fashionshop node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	m_mapFashionShopIndex.clear();
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string cost = xmlConf.GetAttrib("cost");
		string isCash = xmlConf.GetAttrib("isCash");
		string die = xmlConf.GetAttrib("die");
		string days = xmlConf.GetAttrib("days");
		string vip = xmlConf.GetAttrib("vip");
		if (id.empty() || cost.empty() || isCash.empty() || die.empty() || days.empty() || vip.empty())
		{
			cout << ("FashionShop conf wrong") << endl;
			return R_ERROR;
		}

		pdata->fashion_shop_items[i].id_ = CTrans::STOI(id.c_str());
		pdata->fashion_shop_items[i].cost_ = CTrans::STOI(cost.c_str());
		pdata->fashion_shop_items[i].is_cash_ = (bool)(CTrans::STOI(isCash.c_str()));
		pdata->fashion_shop_items[i].die_ = (bool)(CTrans::STOI(die.c_str()));
		pdata->fashion_shop_items[i].days_ = CTrans::STOI(days.c_str());
		pdata->fashion_shop_items[i].vip_ = CTrans::STOI(vip.c_str());
		m_mapFashionShopIndex[pdata->fashion_shop_items[i].id_] = i;
		++i;
	}
	m_shFashionShop.SetInitDone();

	return 0;
}


int CDataXML::GetFashionShopItem(unsigned id, XMLFashionShopItem &item)
{
	if(!m_mapFashionShopIndex.count(id))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLFashionShop *pdata = (DataXMLFashionShop *)m_shFashionShop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFashionShop)), true);
	item = pdata->fashion_shop_items[m_mapFashionShopIndex[id]];

	return R_SUCCESS;
}
/****************************************/


/**************厚惠有期begin**********************/
int CDataXML::InitHouHuiYouQi()
{
	DataXMLHouHuiYouQi *pdata = (DataXMLHouHuiYouQi *)m_shHouHuiYouQi.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shHouHuiYouQi), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned zone_section_index = 0;
	m_mapMinZoneHouHuiYouQi.clear();
	m_mapMaxZoneHouHuiYouQi.clear();
	m_mapChargeHouHuiYouQi.clear();
	while (xmlConf.FindElem("youhui"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("houhuiyouqi config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_mapMinZoneHouHuiYouQi[zone_section_index] = min_zone;
		m_mapMaxZoneHouHuiYouQi[zone_section_index] = max_zone;
		(pdata->houhuiyouqi_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->houhuiyouqi_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned big_table_index = 0;
		while(xmlConf.FindElem("type"))
		{
			string big_id_str = xmlConf.GetAttrib("id");
			string cash_limit_str = xmlConf.GetAttrib("limit");
			if(big_id_str.empty() || cash_limit_str.empty())
			{
				cout<<("houhuiyouqi config wrong 2")<<endl;
				return R_ERROR;
			}
			int cash_limit = CTrans::STOI(cash_limit_str.c_str());
			(pdata->houhuiyouqi_items[zone_section_index]).big_table_charge_need_[big_table_index] = cash_limit;
			m_mapChargeHouHuiYouQi[zone_section_index][big_table_index] = cash_limit;
			xmlConf.IntoElem();
			unsigned small_table_index = 0;
			while (xmlConf.FindElem("item"))
			{
				string id = xmlConf.GetAttrib("id");
				string amount = xmlConf.GetAttrib("amount");
				string price = xmlConf.GetAttrib("price");
				string pay = xmlConf.GetAttrib("pay");
				if (id.empty() || amount.empty() || price.empty() || pay.empty())
				{
					cout << ("houhuiyouqi config wrong 3") << endl;
					return R_ERROR;
				}
				(pdata->houhuiyouqi_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->houhuiyouqi_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].count_ = CTrans::STOI(amount.c_str());
				(pdata->houhuiyouqi_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].cost_ = CTrans::STOI(price.c_str());
				(pdata->houhuiyouqi_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].is_cash_ = ((CTrans::STOI(pay.c_str()))==2) ? true : false;
				++small_table_index;
			}
			xmlConf.OutOfElem();
			++big_table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}

	//后面又添加了4399的
	zone_section_index = 0;
	m_map4399MinZoneHouHuiYouQi.clear();
	m_map4399MaxZoneHouHuiYouQi.clear();
	m_map4399ChargeHouHuiYouQi.clear();
	while (xmlConf.FindElem("youhui_4399"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("houhuiyouqi 4399 config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_map4399MinZoneHouHuiYouQi[zone_section_index] = min_zone;
		m_map4399MaxZoneHouHuiYouQi[zone_section_index] = max_zone;
		(pdata->houhuiyouqi_4399_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->houhuiyouqi_4399_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned big_table_index = 0;
		while(xmlConf.FindElem("type"))
		{
			string big_id_str = xmlConf.GetAttrib("id");
			string cash_limit_str = xmlConf.GetAttrib("limit");
			if(big_id_str.empty() || cash_limit_str.empty())
			{
				cout<<("houhuiyouqi 4399 config wrong 2")<<endl;
				return R_ERROR;
			}
			int cash_limit = CTrans::STOI(cash_limit_str.c_str());
			(pdata->houhuiyouqi_4399_items[zone_section_index]).big_table_charge_need_[big_table_index] = cash_limit;
			m_map4399ChargeHouHuiYouQi[zone_section_index][big_table_index] = cash_limit;
			xmlConf.IntoElem();
			unsigned small_table_index = 0;
			while (xmlConf.FindElem("item"))
			{
				string id = xmlConf.GetAttrib("id");
				string amount = xmlConf.GetAttrib("amount");
				string price = xmlConf.GetAttrib("price");
				string pay = xmlConf.GetAttrib("pay");
				if (id.empty() || amount.empty() || price.empty() || pay.empty())
				{
					cout << ("houhuiyouqi  4399 config wrong 3") << endl;
					return R_ERROR;
				}
				(pdata->houhuiyouqi_4399_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->houhuiyouqi_4399_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].count_ = CTrans::STOI(amount.c_str());
				(pdata->houhuiyouqi_4399_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].cost_ = CTrans::STOI(price.c_str());
				(pdata->houhuiyouqi_4399_items[zone_section_index]).section_houhuiyouqi_[big_table_index][small_table_index].is_cash_ = ((CTrans::STOI(pay.c_str()))==2) ? true : false;
				++small_table_index;
			}
			xmlConf.OutOfElem();
			++big_table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();

	m_shHouHuiYouQi.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetHouHuiYouQiSection(unsigned sid, unsigned & section)
{
	if (OpenPlatform::IsLYPlatform())
	{
		section = HOUHUIYOUQI_ZONE_SECTION - 1;
	} else if (OpenPlatform::GetType() == PT_4399)
	{
		if (sid < m_map4399MinZoneHouHuiYouQi[0] || sid > m_map4399MaxZoneHouHuiYouQi[HOUHUIYOUQI_4399_ZONE_SECTION - 1])
		{
			PARAM_ERROR_RETURN_MSG("houhuiyouqi 4399 sid illegal");
		}

		int ix = 0;
		for(; ix < HOUHUIYOUQI_4399_ZONE_SECTION; ++ix)
		{
			if (sid >= m_map4399MinZoneHouHuiYouQi[ix] && sid <= m_map4399MaxZoneHouHuiYouQi[ix])
			{
				section = ix;
				break;
			}
		}

		if (ix == HOUHUIYOUQI_4399_ZONE_SECTION)
		{
			DATA_ERROR_RETURN_MSG("houhuiyouqi_4399_search_section_error");
		}
	} else //qq
	{
		if (sid < m_mapMinZoneHouHuiYouQi[0] || sid > m_mapMaxZoneHouHuiYouQi[HOUHUIYOUQI_ZONE_SECTION - 1])
		{
			PARAM_ERROR_RETURN_MSG("houhuiyouqi sid illegal");
		}

		int ix = 0;
		for(; ix < HOUHUIYOUQI_ZONE_SECTION; ++ix)
		{
			if (sid >= m_mapMinZoneHouHuiYouQi[ix] && sid <= m_mapMaxZoneHouHuiYouQi[ix])
			{
				section = ix;
				break;
			}
		}

		if (ix == HOUHUIYOUQI_ZONE_SECTION)
		{
			DATA_ERROR_RETURN_MSG("houhuiyouqi_search_section_error");
		}
	}

	return R_SUCCESS;
}


int CDataXML::GetHouHuiYouQiItem(unsigned sid, unsigned b_index, unsigned s_index, XMLHouHuiYouQiItem &item)
{
	DataXMLHouHuiYouQi *pdata = (DataXMLHouHuiYouQi *)m_shHouHuiYouQi.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHouHuiYouQi)), true);

	unsigned section = 0;
	int ret = GetHouHuiYouQiSection(sid, section);
	if (ret)
		return ret;

	if (OpenPlatform::GetType() == PT_4399)
	{
		item = (pdata->houhuiyouqi_4399_items[section]).section_houhuiyouqi_[b_index-1][s_index-1];
	} else
	{
		item = (pdata->houhuiyouqi_items[section]).section_houhuiyouqi_[b_index-1][s_index-1];
	}

	return R_SUCCESS;
}


int CDataXML::GetHouHuiYouQiBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right)
{
	unsigned section = 0;
	int ret = GetHouHuiYouQiSection(sid, section);
	if (ret)
		return ret;

	big_table_right = 0;
	if (OpenPlatform::GetType() == PT_4399) //4399
	{
		if (charge < m_map4399ChargeHouHuiYouQi[section][0])  //左
		{
			PARAM_ERROR_RETURN_MSG("charge is too little to have right");
		}
		for(int ix = 0; ix < HOUHUIYOUQI_BIG_TALBE_NUM - 1; ++ix)   //中
		{
			if (charge >= m_map4399ChargeHouHuiYouQi[section][ix] && charge < m_map4399ChargeHouHuiYouQi[section][ix + 1])
			{
				big_table_right = ix+1;
				break;
			}
		}
		if (charge >= m_map4399ChargeHouHuiYouQi[section][HOUHUIYOUQI_BIG_TALBE_NUM-1])  //右
		{
			big_table_right = HOUHUIYOUQI_BIG_TALBE_NUM;
		}
		if (!big_table_right || big_table_right > HOUHUIYOUQI_BIG_TALBE_NUM)
		{
			LOGIC_ERROR_RETURN_MSG("big table right 4399 is illegal");
		}

	} else //qq ly
	{
		if (charge < m_mapChargeHouHuiYouQi[section][0])  //左
		{
			PARAM_ERROR_RETURN_MSG("charge is too little to have right");
		}
		for(int ix = 0; ix < HOUHUIYOUQI_BIG_TALBE_NUM - 1; ++ix)   //中
		{
			if (charge >= m_mapChargeHouHuiYouQi[section][ix] && charge < m_mapChargeHouHuiYouQi[section][ix + 1])
			{
				big_table_right = ix+1;
				break;
			}
		}
		if (charge >= m_mapChargeHouHuiYouQi[section][HOUHUIYOUQI_BIG_TALBE_NUM-1])  //右
		{
			big_table_right = HOUHUIYOUQI_BIG_TALBE_NUM;
		}
		if (!big_table_right || big_table_right > HOUHUIYOUQI_BIG_TALBE_NUM)
		{
			LOGIC_ERROR_RETURN_MSG("big table right is illegal");
		}
	}

	return R_SUCCESS;
}
/**************厚惠有期end**********************/



/**************超值折扣begin**********************/
int CDataXML::InitChaoZhiZheKou()
{
	DataXMLChaoZhiZheKou *pdata = (DataXMLChaoZhiZheKou *)m_shChaoZhiZheKou.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shChaoZhiZheKou), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("yuandan.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned zone_section_index = 0;
	m_mapMinZoneChaoZhiZheKou.clear();
	m_mapMaxZoneChaoZhiZheKou.clear();
	m_mapChargeChaoZhiZheKou.clear();
	while (xmlConf.FindElem("discount"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("chaozhizhekou config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_mapMinZoneChaoZhiZheKou[zone_section_index] = min_zone;
		m_mapMaxZoneChaoZhiZheKou[zone_section_index] = max_zone;
		(pdata->chaozhizhekou_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->chaozhizhekou_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned big_table_index = 0;
		while(xmlConf.FindElem("type"))
		{
			string big_id_str = xmlConf.GetAttrib("id");
			string cash_limit_str = xmlConf.GetAttrib("limit");
			if(big_id_str.empty() || cash_limit_str.empty())
			{
				cout<<("chaozhizhekou config wrong 2")<<endl;
				return R_ERROR;
			}
			int cash_limit = CTrans::STOI(cash_limit_str.c_str());
			(pdata->chaozhizhekou_items[zone_section_index]).big_table_charge_need_[big_table_index] = cash_limit;
			m_mapChargeChaoZhiZheKou[zone_section_index][big_table_index] = cash_limit;
			xmlConf.IntoElem();
			unsigned small_table_index = 0;
			while (xmlConf.FindElem("item"))
			{
				string id = xmlConf.GetAttrib("id");
				string amount = xmlConf.GetAttrib("amount");
				string price = xmlConf.GetAttrib("price");
				string pay = xmlConf.GetAttrib("pay");
				string limit = xmlConf.GetAttrib("total");
				if (id.empty() || amount.empty() || price.empty() || pay.empty() || limit.empty())
				{
					cout << ("chaozhizhekou config wrong 3") << endl;
					return R_ERROR;
				}
				(pdata->chaozhizhekou_items[zone_section_index]).section_chaozhizhekou_[big_table_index][small_table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->chaozhizhekou_items[zone_section_index]).section_chaozhizhekou_[big_table_index][small_table_index].count_ = CTrans::STOI(amount.c_str());
				(pdata->chaozhizhekou_items[zone_section_index]).section_chaozhizhekou_[big_table_index][small_table_index].cost_ = CTrans::STOI(price.c_str());
				(pdata->chaozhizhekou_items[zone_section_index]).section_chaozhizhekou_[big_table_index][small_table_index].is_cash_ = ((CTrans::STOI(pay.c_str()))==2) ? true : false;
				(pdata->chaozhizhekou_items[zone_section_index]).section_chaozhizhekou_[big_table_index][small_table_index].limit_ = CTrans::STOI(limit.c_str());
				++small_table_index;
			}
			xmlConf.OutOfElem();
			++big_table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();
	m_shChaoZhiZheKou.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetChaoZhiZheKouSection(unsigned sid, unsigned & section)
{
	if (OpenPlatform::IsLYPlatform())
	{
		section = CHAOZHIZHEKOU_ZONE_SECTION - 1;
	} else
	{
		if (sid < m_mapMinZoneChaoZhiZheKou[0] || sid > m_mapMaxZoneChaoZhiZheKou[CHAOZHIZHEKOU_ZONE_SECTION - 1])
		{
			PARAM_ERROR_RETURN_MSG("chaozhizhekou_sid_illegal");
		}

		int ix = 0;
		for(; ix < CHAOZHIZHEKOU_ZONE_SECTION; ++ix)
		{
			if (sid >= m_mapMinZoneChaoZhiZheKou[ix] && sid <= m_mapMaxZoneChaoZhiZheKou[ix])
			{
				section = ix;
				break;
			}
		}

		if (ix == CHAOZHIZHEKOU_ZONE_SECTION)
		{
			DATA_ERROR_RETURN_MSG("chaozhizhekou_search_section_error");
		}
	}

	return R_SUCCESS;
}


int CDataXML::GetChaoZhiZheKouItem(unsigned sid, unsigned b_index, unsigned s_index, XMLChaoZhiZheKouItem &item)
{
	DataXMLChaoZhiZheKou *pdata = (DataXMLChaoZhiZheKou *)m_shChaoZhiZheKou.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChaoZhiZheKou)), true);

	unsigned section = 0;
	int ret = GetChaoZhiZheKouSection(sid, section);
	if (ret)
		return ret;

	item = (pdata->chaozhizhekou_items[section]).section_chaozhizhekou_[b_index-1][s_index-1];
	return R_SUCCESS;
}


int CDataXML::GetChaoZhiZheKouBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right)
{
	unsigned section = 0;
	int ret = GetChaoZhiZheKouSection(sid, section);
	if (ret)
		return ret;

	big_table_right = 0;
	if (charge < m_mapChargeChaoZhiZheKou[section][0])  //左
	{
		PARAM_ERROR_RETURN_MSG("charge is too little to have right");
	}
	for(int ix = 0; ix < CHAOZHIZHEKOU_BIG_TALBE_NUM - 1; ++ix)   //中
	{
		if (charge >= m_mapChargeChaoZhiZheKou[section][ix] && charge < m_mapChargeChaoZhiZheKou[section][ix + 1])
		{
			big_table_right = ix+1;
			break;
		}
	}
	if (charge >= m_mapChargeChaoZhiZheKou[section][CHAOZHIZHEKOU_BIG_TALBE_NUM-1])  //右
	{
		big_table_right = CHAOZHIZHEKOU_BIG_TALBE_NUM;
	}
	if (!big_table_right || big_table_right > CHAOZHIZHEKOU_BIG_TALBE_NUM)
	{
		LOGIC_ERROR_RETURN_MSG("big table right is illegal");
	}

	return R_SUCCESS;
}
/**************超值折扣end**********************/



/**************约惠巨献begin**********************/
int CDataXML::InitYueHuiJuXian()
{
	DataXMLYueHuiJuXian *pdata = (DataXMLYueHuiJuXian *)m_shYueHuiJuXian.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shYueHuiJuXian), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("yuandan.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned zone_section_index = 0;
	m_mapMinZoneYueHuiJuXian.clear();
	m_mapMaxZoneYueHuiJuXian.clear();
	m_mapChargeYueHuiJuXian.clear();
	while (xmlConf.FindElem("allItem"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("yuehuijuxian config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_mapMinZoneYueHuiJuXian[zone_section_index] = min_zone;
		m_mapMaxZoneYueHuiJuXian[zone_section_index] = max_zone;
		(pdata->yuehuijuxian_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->yuehuijuxian_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned big_table_index = 0;
		while(xmlConf.FindElem("type"))
		{
			string big_id_str = xmlConf.GetAttrib("id");
			string cash_limit_str = xmlConf.GetAttrib("limit");
			if(big_id_str.empty() || cash_limit_str.empty())
			{
				cout<<("yuehuijuxian config wrong 2")<<endl;
				return R_ERROR;
			}
			int cash_limit = CTrans::STOI(cash_limit_str.c_str());
			(pdata->yuehuijuxian_items[zone_section_index]).big_table_charge_need_[big_table_index] = cash_limit;
			m_mapChargeYueHuiJuXian[zone_section_index][big_table_index] = cash_limit;
			xmlConf.IntoElem();
			unsigned small_table_index = 0;
			while (xmlConf.FindElem("item"))
			{
				string id = xmlConf.GetAttrib("id");
				string amount = xmlConf.GetAttrib("amount");
				string price = xmlConf.GetAttrib("price");
				string pay = xmlConf.GetAttrib("pay");
				if (id.empty() || amount.empty() || price.empty() || pay.empty())
				{
					cout << ("yuehuijuxian config wrong 3") << endl;
					return R_ERROR;
				}
				(pdata->yuehuijuxian_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->yuehuijuxian_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].count_ = CTrans::STOI(amount.c_str());
				(pdata->yuehuijuxian_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].cost_ = CTrans::STOI(price.c_str());
				(pdata->yuehuijuxian_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].is_cash_ = ((CTrans::STOI(pay.c_str()))==2) ? true : false;
				++small_table_index;
			}
			xmlConf.OutOfElem();
			++big_table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}

	//因为配置改变，新增加了4399
	zone_section_index = 0;
	m_map4399MinZoneYueHuiJuXian.clear();
	m_map4399MaxZoneYueHuiJuXian.clear();
	m_map4399ChargeYueHuiJuXian.clear();
	while (xmlConf.FindElem("allItem_4399"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("yuehuijuxian 4399 config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_map4399MinZoneYueHuiJuXian[zone_section_index] = min_zone;
		m_map4399MaxZoneYueHuiJuXian[zone_section_index] = max_zone;
		(pdata->yuehuijuxian_4399_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->yuehuijuxian_4399_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned big_table_index = 0;
		while(xmlConf.FindElem("type"))
		{
			string big_id_str = xmlConf.GetAttrib("id");
			string cash_limit_str = xmlConf.GetAttrib("limit");
			if(big_id_str.empty() || cash_limit_str.empty())
			{
				cout<<("yuehuijuxian 4399 config wrong 2")<<endl;
				return R_ERROR;
			}
			int cash_limit = CTrans::STOI(cash_limit_str.c_str());
			(pdata->yuehuijuxian_4399_items[zone_section_index]).big_table_charge_need_[big_table_index] = cash_limit;
			m_map4399ChargeYueHuiJuXian[zone_section_index][big_table_index] = cash_limit;
			xmlConf.IntoElem();
			unsigned small_table_index = 0;
			while (xmlConf.FindElem("item"))
			{
				string id = xmlConf.GetAttrib("id");
				string amount = xmlConf.GetAttrib("amount");
				string price = xmlConf.GetAttrib("price");
				string pay = xmlConf.GetAttrib("pay");
				if (id.empty() || amount.empty() || price.empty() || pay.empty())
				{
					cout << ("yuehuijuxian 4399  config wrong 3") << endl;
					return R_ERROR;
				}
				(pdata->yuehuijuxian_4399_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->yuehuijuxian_4399_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].count_ = CTrans::STOI(amount.c_str());
				(pdata->yuehuijuxian_4399_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].cost_ = CTrans::STOI(price.c_str());
				(pdata->yuehuijuxian_4399_items[zone_section_index]).section_yuehuijuxian_[big_table_index][small_table_index].is_cash_ = ((CTrans::STOI(pay.c_str()))==2) ? true : false;
				++small_table_index;
			}
			xmlConf.OutOfElem();
			++big_table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();

	m_shYueHuiJuXian.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetYueHuiJuXianSection(unsigned sid, unsigned & section)
{
	if (OpenPlatform::IsLYPlatform())
	{
		section = YUEHUIJUXIAN_ZONE_SECTION - 1;
	} else if (OpenPlatform::GetType() == PT_4399) //4399
	{
		if (sid < m_map4399MinZoneYueHuiJuXian[0] || sid > m_map4399MaxZoneYueHuiJuXian[YUEHUIJUXIAN_4399_ZONE_SECTION - 1])
		{
			PARAM_ERROR_RETURN_MSG("yuehuijuxian4399_sid_illegal");
		}

		int ix = 0;
		for(; ix < YUEHUIJUXIAN_4399_ZONE_SECTION; ++ix)
		{
			if (sid >= m_map4399MinZoneYueHuiJuXian[ix] && sid <= m_map4399MaxZoneYueHuiJuXian[ix])
			{
				section = ix;
				break;
			}
		}

		if (ix == YUEHUIJUXIAN_4399_ZONE_SECTION)
		{
			DATA_ERROR_RETURN_MSG("yuehuijuxian_search_section_error");
		}

	} else  //qq
	{
		if (sid < m_mapMinZoneYueHuiJuXian[0] || sid > m_mapMaxZoneYueHuiJuXian[YUEHUIJUXIAN_ZONE_SECTION - 1])
		{
			PARAM_ERROR_RETURN_MSG("yuehuijuxian_sid_illegal");
		}

		int ix = 0;
		for(; ix < YUEHUIJUXIAN_ZONE_SECTION; ++ix)
		{
			if (sid >= m_mapMinZoneYueHuiJuXian[ix] && sid <= m_mapMaxZoneYueHuiJuXian[ix])
			{
				section = ix;
				break;
			}
		}

		if (ix == YUEHUIJUXIAN_ZONE_SECTION)
		{
			DATA_ERROR_RETURN_MSG("yuehuijuxian_search_section_error");
		}
	}

	return R_SUCCESS;
}


int CDataXML::GetYueHuiJuXianItem(unsigned sid, unsigned b_index, unsigned s_index, XMLYueHuiJuXianItem &item)
{
	DataXMLYueHuiJuXian *pdata = (DataXMLYueHuiJuXian *)m_shYueHuiJuXian.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shYueHuiJuXian)), true);

	unsigned section = 0;
	int ret = GetYueHuiJuXianSection(sid, section);
	if (ret)
		return ret;

	if (OpenPlatform::GetType() == PT_4399)
	{
		if (sid < (pdata->yuehuijuxian_4399_items[section]).zone_start_ || sid > (pdata->yuehuijuxian_4399_items[section]).zone_end_)
		{
			DATA_ERROR_RETURN_MSG("yuehuijuxian_4399_index_create_error");
		}
		item = (pdata->yuehuijuxian_4399_items[section]).section_yuehuijuxian_[b_index-1][s_index-1];
	}  else //ly and qq
	{
		item = (pdata->yuehuijuxian_items[section]).section_yuehuijuxian_[b_index-1][s_index-1];
	}

	return R_SUCCESS;
}


int CDataXML::GetYueHuiJuXianBigTableRight(unsigned sid, unsigned charge, unsigned & big_table_right)
{
	unsigned section = 0;
	int ret = GetYueHuiJuXianSection(sid, section);
	if (ret)
		return ret;

	if (OpenPlatform::GetType() == PT_4399)
	{
		big_table_right = 0;
		if (charge < m_map4399ChargeYueHuiJuXian[section][0])  //左
		{
			PARAM_ERROR_RETURN_MSG("charge is too little to have right");
		}
		for(int ix = 0; ix < YUEHUIJUXIAN_BIG_TALBE_NUM - 1; ++ix)   //中
		{
			if (charge >= m_map4399ChargeYueHuiJuXian[section][ix] && charge < m_map4399ChargeYueHuiJuXian[section][ix + 1])
			{
				big_table_right = ix+1;
				break;
			}
		}
		if (charge >= m_map4399ChargeYueHuiJuXian[section][YUEHUIJUXIAN_BIG_TALBE_NUM-1])  //右
		{
			big_table_right = YUEHUIJUXIAN_BIG_TALBE_NUM;
		}
		if (!big_table_right || big_table_right > YUEHUIJUXIAN_BIG_TALBE_NUM)
		{
			LOGIC_ERROR_RETURN_MSG("big table right is illegal");
		}
	} else  //qq ly
	{
		big_table_right = 0;
		if (charge < m_mapChargeYueHuiJuXian[section][0])  //左
		{
			PARAM_ERROR_RETURN_MSG("charge is too little to have right");
		}
		for(int ix = 0; ix < YUEHUIJUXIAN_BIG_TALBE_NUM - 1; ++ix)   //中
		{
			if (charge >= m_mapChargeYueHuiJuXian[section][ix] && charge < m_mapChargeYueHuiJuXian[section][ix + 1])
			{
				big_table_right = ix+1;
				break;
			}
		}
		if (charge >= m_mapChargeYueHuiJuXian[section][YUEHUIJUXIAN_BIG_TALBE_NUM-1])  //右
		{
			big_table_right = YUEHUIJUXIAN_BIG_TALBE_NUM;
		}
		if (!big_table_right || big_table_right > YUEHUIJUXIAN_BIG_TALBE_NUM)
		{
			LOGIC_ERROR_RETURN_MSG("big table right is illegal");
		}
	}

	return R_SUCCESS;
}
/**************约惠巨献end**********************/


/**************全服限购 begin**********************/
int CDataXML::InitLimitBuyOfZone()
{
	DataXMLLimitBuyOfZone *pdata = (DataXMLLimitBuyOfZone *)m_shLimitBuyOfZone.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shLimitBuyOfZone), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("activityconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("limitbuy"))
	{
		cout << ("limitbuy node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	Json::Reader reader;
	unsigned zone_section_index = 0;
	m_mapMinZoneLimitBuy.clear();
	m_mapMaxZoneLimitBuy.clear();
	m_mapConsumeLimitBuy.clear();
	while (xmlConf.FindElem("allItem"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("limitbuyofzone config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_mapMinZoneLimitBuy[0][zone_section_index] = min_zone;  //0:qq, 1:ly, 2:4399
		m_mapMaxZoneLimitBuy[0][zone_section_index] = max_zone;
		(pdata->limitbuyofzone_qq_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->limitbuyofzone_qq_items[zone_section_index]).zone_end_ = max_zone;
		if (zone_section_index == (LIMITBUYOFZONE_ZONE_QQ_SECTION-1))  //联运
		{
			m_mapMinZoneLimitBuy[1][0] = 1;
			m_mapMaxZoneLimitBuy[1][0] = 9999;
			(pdata->limitbuyofzone_ly_items[0]).zone_start_ = 1;
			(pdata->limitbuyofzone_ly_items[0]).zone_end_ = 9999;
		}
		xmlConf.IntoElem();
		unsigned table_index = 0;
		Json::Value json_item_data;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string cash = xmlConf.GetAttrib("diamond");
			string cash_limit_str = xmlConf.GetAttrib("condition");
			string item_data = xmlConf.GetData();
			if (id.empty() || cash.empty() || cash_limit_str.empty() || item_data.empty())
			{
				cout << ("limitbuyofzone config wrong 3") << endl;
				return R_ERROR;
			}

			json_item_data.clear();
			reader.parse(item_data,json_item_data);
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].id_ = CTrans::STOI(id.c_str());
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].cash_ = CTrans::STOI(cash.c_str());
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].cond_ = CTrans::STOI(cash_limit_str.c_str());
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_q_ = json_item_data["reward"]["equip"]["q"].asUInt();
			(pdata->limitbuyofzone_qq_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_ch_ = json_item_data["reward"]["equip"]["ch"].asUInt();
			m_mapConsumeLimitBuy[0][zone_section_index][table_index] = CTrans::STOI(cash_limit_str.c_str());

			if (zone_section_index == (LIMITBUYOFZONE_ZONE_QQ_SECTION-1))  //联运
			{
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].id_ = CTrans::STOI(id.c_str());
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].cash_ = CTrans::STOI(cash.c_str());
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].cond_ = CTrans::STOI(cash_limit_str.c_str());
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].eq_cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].eq_q_ = json_item_data["reward"]["equip"]["q"].asUInt();
				(pdata->limitbuyofzone_ly_items[0]).section_limitbuyofzone_[table_index].eq_ch_ = json_item_data["reward"]["equip"]["ch"].asUInt();
				m_mapConsumeLimitBuy[1][0][table_index] = CTrans::STOI(cash_limit_str.c_str());
			}

			++table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();

	//4399
	if(!xmlConf.FindElem("limitbuy"))
	{
		cout << ("content node2 wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	zone_section_index = 0;
	while (xmlConf.FindElem("allItem_4399"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("limitbuyofzone config2 wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		m_mapMinZoneLimitBuy[2][zone_section_index] = min_zone;
		m_mapMaxZoneLimitBuy[2][zone_section_index] = max_zone;
		(pdata->limitbuyofzone_4399_items[zone_section_index]).zone_start_ = min_zone;
		(pdata->limitbuyofzone_4399_items[zone_section_index]).zone_end_ = max_zone;
		xmlConf.IntoElem();
		unsigned table_index = 0;
		Json::Value json_item_data;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string cash = xmlConf.GetAttrib("diamond");
			string cash_limit_str = xmlConf.GetAttrib("condition");
			string item_data = xmlConf.GetData();
			if (id.empty() || cash.empty() || cash_limit_str.empty() || item_data.empty())
			{
				cout << ("limitbuyofzone config2 wrong 3") << endl;
				return R_ERROR;
			}

			json_item_data.clear();
			reader.parse(item_data,json_item_data);
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].id_ = CTrans::STOI(id.c_str());
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].cash_ = CTrans::STOI(cash.c_str());
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].cond_ = CTrans::STOI(cash_limit_str.c_str());
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_q_ = json_item_data["reward"]["equip"]["q"].asUInt();
			(pdata->limitbuyofzone_4399_items[zone_section_index]).section_limitbuyofzone_[table_index].eq_ch_ = json_item_data["reward"]["equip"]["ch"].asUInt();
			m_mapConsumeLimitBuy[2][zone_section_index][table_index] = CTrans::STOI(cash_limit_str.c_str());

			++table_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();

	m_shLimitBuyOfZone.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetLimitBuyOfZoneSection(const unsigned & index_platform, unsigned sid, unsigned & section, const unsigned & total_zone_section)
{
	if (sid < m_mapMinZoneLimitBuy[index_platform][0] || sid > m_mapMaxZoneLimitBuy[index_platform][total_zone_section - 1])
	{
		PARAM_ERROR_RETURN_MSG("limitbuyofzone_sid_illegal");
	}

	int ix = 0;
	for(; ix < total_zone_section; ++ix)
	{
		if (sid >= m_mapMinZoneLimitBuy[index_platform][ix] && sid <= m_mapMaxZoneLimitBuy[index_platform][ix])
		{
			section = ix;
			break;
		}
	}

	if (ix == total_zone_section)
	{
		DATA_ERROR_RETURN_MSG("limitbuyofzone_search_section_error");
	}
	return R_SUCCESS;
}


int CDataXML::GetLimitBuyOfZoneItem(unsigned sid, unsigned index, XMLLimitBuyOfZoneItem &item)
{
	DataXMLLimitBuyOfZone *pdata = (DataXMLLimitBuyOfZone *)m_shLimitBuyOfZone.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shLimitBuyOfZone)), true);

	unsigned index_platform = 0;
	unsigned total_zone_section = LIMITBUYOFZONE_ZONE_QQ_SECTION;
	if(OpenPlatform::IsLYPlatform())
	{
		index_platform = 1;
		total_zone_section = LIMITBUYOFZONE_ZONE_LY_SECTION;
	} else if (OpenPlatform::GetType() == PT_4399)
	{
		index_platform = 2;
		total_zone_section = LIMITBUYOFZONE_ZONE_4399_SECTION;
	}

	unsigned section = 0;
	int ret = GetLimitBuyOfZoneSection(index_platform, sid, section, total_zone_section);
	if (ret)
		return ret;

	if (OpenPlatform::IsLYPlatform())
	{
		if (sid < (pdata->limitbuyofzone_ly_items[section]).zone_start_ || sid > (pdata->limitbuyofzone_ly_items[section]).zone_end_)
		{
			DATA_ERROR_RETURN_MSG("limitbuyofzone_index_create_error");
		}
		item = (pdata->limitbuyofzone_ly_items[section]).section_limitbuyofzone_[index-1];
	}else if (OpenPlatform::GetType() == PT_4399)
	{
		if (sid < (pdata->limitbuyofzone_4399_items[section]).zone_start_ || sid > (pdata->limitbuyofzone_4399_items[section]).zone_end_)
		{
			DATA_ERROR_RETURN_MSG("limitbuyofzone_index_create_error");
		}
		item = (pdata->limitbuyofzone_4399_items[section]).section_limitbuyofzone_[index-1];
	} else
	{
		if (sid < (pdata->limitbuyofzone_qq_items[section]).zone_start_ || sid > (pdata->limitbuyofzone_qq_items[section]).zone_end_)
		{
			DATA_ERROR_RETURN_MSG("limitbuyofzone_index_create_error");
		}
		item = (pdata->limitbuyofzone_qq_items[section]).section_limitbuyofzone_[index-1];
	}

	return R_SUCCESS;
}


int CDataXML::GetLimitBuyOfZoneTableRight(unsigned sid, unsigned consume, unsigned & table_right)
{
	unsigned index_platform = 0;
	unsigned total_zone_section = LIMITBUYOFZONE_ZONE_QQ_SECTION;
	if(OpenPlatform::IsLYPlatform())
	{
		index_platform = 1;
		total_zone_section = LIMITBUYOFZONE_ZONE_LY_SECTION;
	} else if (OpenPlatform::GetType() == PT_4399)
	{
		index_platform = 2;
		total_zone_section = LIMITBUYOFZONE_ZONE_4399_SECTION;
	}

	unsigned section = 0;
	int ret = GetLimitBuyOfZoneSection(index_platform, sid, section, total_zone_section);
	if (ret)
		return ret;

	table_right = 0;
	if (consume < m_mapConsumeLimitBuy[index_platform][section][0])  //左
	{
		PARAM_ERROR_RETURN_MSG("charge is too little to have right");
	}
	for(int ix = 0; ix < LIMITBUYOFZONE_TALBE_NUM - 1; ++ix)   //中
	{
		if (consume >= m_mapConsumeLimitBuy[index_platform][section][ix] && consume < m_mapConsumeLimitBuy[index_platform][section][ix + 1])
		{
			table_right = ix+1;
			break;
		}
	}
	if (consume >= m_mapConsumeLimitBuy[index_platform][section][LIMITBUYOFZONE_TALBE_NUM-1])  //右
	{
		table_right = LIMITBUYOFZONE_TALBE_NUM;
	}
	if (!table_right || table_right > LIMITBUYOFZONE_TALBE_NUM)
	{
		LOGIC_ERROR_RETURN_MSG("table right is illegal");
	}

	return R_SUCCESS;
}
/**************全服限购 end**********************/


/**************五行防御成长 begin**********************/
int CDataXML::InitFiveDefendGrow()
{
	DataXMLFiveDefendGrow *pdata = (DataXMLFiveDefendGrow *)m_shFiveDefendGrow.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shFiveDefendGrow), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("awakenConfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("wuxing"))
	{
		cout<<("wuxing node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	unsigned index_defence = 0;
	while (xmlConf.FindElem("defence"))
	{
		string level = xmlConf.GetAttrib("level");
		string value = xmlConf.GetAttrib("value");
		string cost = xmlConf.GetAttrib("cost");
		if (level.empty() || value.empty() || cost.empty())
		{
			cout << ("fivedefendgrow config wrong 3") << endl;
			return R_ERROR;
		}

		(pdata->fivedefendgrow_items_)[index_defence].level_ = CTrans::STOI(level.c_str());
		(pdata->fivedefendgrow_items_)[index_defence].value_ = CTrans::STOI(value.c_str());
		(pdata->fivedefendgrow_items_)[index_defence].cost_ = CTrans::STOI(cost.c_str());
		++index_defence;
	}
	m_shFiveDefendGrow.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetFiveDefendGrowItem(unsigned level, XMLFiveDefendGrowItem & item)
{
	DataXMLFiveDefendGrow *pdata = (DataXMLFiveDefendGrow *)m_shFiveDefendGrow.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFiveDefendGrow)), true);
	if (level <= FIVEDEFENDGROW_LEVEL-1)
	{
		item = pdata->fivedefendgrow_items_[level];
	} else
	{
		PARAM_ERROR_RETURN_MSG("five_defend_index_error");
	}

	return R_SUCCESS;
}
/**************五行防御成长 end**********************/


/**************国庆盛典 begin**********************/
int CDataXML::InitCountryDay()
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCountryDay), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("guoqing"))
	{
		cout<<("guoqing node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();  //进入国庆

	//进入国庆登录  初始化
	if(!xmlConf.FindElem("login"))
	{
		cout<<("login node wrong")<<endl;
		return 1;
	}
	string begin_ts = xmlConf.GetAttrib("start");
	string end_ts = xmlConf.GetAttrib("end");
	if (begin_ts.empty() || end_ts.empty())
	{
		cout << ("login time node wrong") << endl;
		return R_ERROR;
	}
	(pdata->login_).begin_ts_ = CTrans::STOI(begin_ts.c_str());
	(pdata->login_).end_ts_ = CTrans::STOI(end_ts.c_str());

	xmlConf.IntoElem(); //进入login
	if(!xmlConf.FindElem("daily_login"))
	{
		cout << ("daily_login node wrong") << endl;
		return 1;
	}
	unsigned index_login_items = 0;
	(pdata->login_).login_items_[index_login_items].id_ = 0;
	(pdata->login_).login_items_[index_login_items].days_ = 1;

	string item_data = xmlConf.GetData();
	Json::Value json_item_data;
	Json::Reader reader;
	reader.parse(item_data, json_item_data);
	Json::Value  & json_login_reward = json_item_data["reward"];
	Json::Value::Members members(json_login_reward.getMemberNames());
	unsigned index_equip_items = 0;
	for (Json::Value::Members::iterator iter = members.begin(); iter != members.end(); ++iter)
	{

		((pdata->login_).login_items_[index_login_items].equip_items_[index_equip_items]).eqid_ = json_login_reward[*iter]["id"].asUInt();
		((pdata->login_).login_items_[index_login_items].equip_items_[index_equip_items]).cnt_ = json_login_reward[*iter]["c"].asUInt();
		++index_equip_items;
	}
	++index_login_items;

	if(!xmlConf.FindElem("total_login"))
	{
		cout<<("total_login node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();  //进入total_login
	while (xmlConf.FindElem("item"))
	{
		string id_str = xmlConf.GetAttrib("id");
		string day_str = xmlConf.GetAttrib("day");
		if (id_str.empty() || day_str.empty())
		{
			cout << ("total_login item node wrong") << endl;
			return R_ERROR;
		}
		(pdata->login_).login_items_[index_login_items].id_ = CTrans::STOI(id_str.c_str());
		(pdata->login_).login_items_[index_login_items].days_ = CTrans::STOI(day_str.c_str());

		item_data = xmlConf.GetData();
		Json::Value json_item_data;
		reader.parse(item_data, json_item_data);
		json_login_reward = json_item_data["reward"];
		index_equip_items = 0;
		Json::Value::Members members_aid(json_login_reward.getMemberNames());
		for (Json::Value::Members::iterator iter = members_aid.begin(); iter != members_aid.end(); ++iter)
		{

			((pdata->login_).login_items_[index_login_items].equip_items_[index_equip_items]).eqid_ = json_login_reward[*iter]["id"].asUInt();
			((pdata->login_).login_items_[index_login_items].equip_items_[index_equip_items]).cnt_ = json_login_reward[*iter]["c"].asUInt();
			++index_equip_items;
		}
		++index_login_items;
	}
	xmlConf.OutOfElem(); //跳出 total_login
	xmlConf.OutOfElem(); //跳出 login

	//进入国庆商店  初始化
	if(!xmlConf.FindElem("shop"))
	{
		cout<<("shop node wrong")<<endl;
		return 1;
	}
	begin_ts = xmlConf.GetAttrib("start");
	end_ts = xmlConf.GetAttrib("end");
	if (begin_ts.empty() || end_ts.empty())
	{
		cout << ("shop time node wrong") << endl;
		return R_ERROR;
	}
	(pdata->shop_).begin_ts_ = CTrans::STOI(begin_ts.c_str());
	(pdata->shop_).end_ts_ = CTrans::STOI(end_ts.c_str());
	xmlConf.IntoElem(); //进入shop
	unsigned index_shop_item = 0;
	while (xmlConf.FindElem("item"))
	{
		string id_str = xmlConf.GetAttrib("id");
		string limitcount_str = xmlConf.GetAttrib("limitcount");
		string eqid_str = xmlConf.GetAttrib("eqid");
		string eqcount_str = xmlConf.GetAttrib("eqcount");
		string time_str = xmlConf.GetAttrib("time");
		string cash_str = xmlConf.GetAttrib("price");
		if (id_str.empty() || limitcount_str.empty() || eqid_str.empty() || eqcount_str.empty() || time_str.empty() || cash_str.empty())
		{
			cout << ("shop item node wrong") << endl;
			return R_ERROR;
		}
		(pdata->shop_).shop_items_[index_shop_item].id_ = CTrans::STOI(id_str.c_str());
		(pdata->shop_).shop_items_[index_shop_item].limit_ = CTrans::STOI(limitcount_str.c_str());
		(pdata->shop_).shop_items_[index_shop_item].eqid_ = CTrans::STOI(eqid_str.c_str());
		(pdata->shop_).shop_items_[index_shop_item].eq_cnt_ = CTrans::STOI(eqcount_str.c_str());
		(pdata->shop_).shop_items_[index_shop_item].ts_ = CTrans::STOI(time_str.c_str());
		(pdata->shop_).shop_items_[index_shop_item].cash_ = CTrans::STOI(cash_str.c_str());
		++index_shop_item;
	}
	xmlConf.OutOfElem(); //跳出 shop

	//进入国庆福袋  初始化
	if(!xmlConf.FindElem("fudai"))
	{
		cout<<("fudai node wrong")<<endl;
		return 1;
	}
	begin_ts = xmlConf.GetAttrib("start");
	end_ts = xmlConf.GetAttrib("end");
	if (begin_ts.empty() || end_ts.empty())
	{
		cout << ("fudai time node wrong") << endl;
		return R_ERROR;
	}
	(pdata->bag_).begin_ts_ = CTrans::STOI(begin_ts.c_str());
	(pdata->bag_).end_ts_ = CTrans::STOI(end_ts.c_str());
	xmlConf.IntoElem(); //进入fudai
	unsigned index_bag_item = 0;
	while (xmlConf.FindElem("item"))
	{
		string id_str = xmlConf.GetAttrib("id");
		string dailypay_str = xmlConf.GetAttrib("dailypay");
		string eqid_str = xmlConf.GetAttrib("eqid");
		string eqcount_str = xmlConf.GetAttrib("eqcount");
		if (id_str.empty() || dailypay_str.empty() || eqid_str.empty() || eqcount_str.empty())
		{
			cout << ("fudai item node wrong") << endl;
			return R_ERROR;
		}
		(pdata->bag_).bag_items_[index_bag_item].id_ = CTrans::STOI(id_str.c_str());
		(pdata->bag_).bag_items_[index_bag_item].daily_pay_ = CTrans::STOI(dailypay_str.c_str());
		(pdata->bag_).bag_items_[index_bag_item].eqid_ = CTrans::STOI(eqid_str.c_str());
		(pdata->bag_).bag_items_[index_bag_item].eq_cnt_ = CTrans::STOI(eqcount_str.c_str());
		++index_bag_item;
	}
	xmlConf.OutOfElem(); //跳出 fudai
	xmlConf.OutOfElem(); //跳出 guoqing
	xmlConf.OutOfElem(); //跳出 content


	m_shCountryDay.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetCountryDayLoginItem(unsigned index, XMLCountryDayLoginItem & item)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	item = (pdata->login_).login_items_[index];
	if (index != item.id_)
	{
		error_log("GetCountryDayLoginItem fail: index=%u, id=%u", index, item.id_);
		return R_ERR_DB;
	}

	return R_SUCCESS;
}

int CDataXML::GetCountryDayShopItem(unsigned index, XMLCountryDayShopItem & item)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	item = (pdata->shop_).shop_items_[index];
	if ((index+1) != item.id_)
	{
		error_log("GetCountryDayShopItem fail: index=%u, id=%u", index, item.id_);
		return R_ERR_DB;
	}

	return R_SUCCESS;
}
int CDataXML::GetCountryDayBagItem(unsigned index, XMLCountryDayBagItem & item)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	item = (pdata->bag_).bag_items_[index];
	if ((index+1) != item.id_)
	{
		error_log("GetCountryDayBagItem fail: index=%u, id=%u", index, item.id_);
		return R_ERR_DB;
	}

	return R_SUCCESS;
}

int CDataXML::GetCountryDayLoginOpenTime(unsigned & begin_ts, unsigned & end_ts)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	begin_ts = (pdata->login_).begin_ts_;
	end_ts = (pdata->login_).end_ts_;

	return R_SUCCESS;
}

int CDataXML::GetCountryDayShopOpenTime(unsigned & begin_ts, unsigned & end_ts)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	begin_ts = (pdata->shop_).begin_ts_;
	end_ts = (pdata->shop_).end_ts_;

	return R_SUCCESS;
}

int CDataXML::GetCountryDayBagOpenTime(unsigned & begin_ts, unsigned & end_ts)
{
	DataXMLCountryDay *pdata = (DataXMLCountryDay *)m_shCountryDay.GetAddress();
	if (NULL == pdata)
	{
		error_log("Init xml country day fail!");
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCountryDay)), true);

	begin_ts = (pdata->bag_).begin_ts_;
	end_ts = (pdata->bag_).end_ts_;

	return R_SUCCESS;
}
/**************国庆盛典 end**********************/


/**************五行灵珠 begin**********************/
int CDataXML::InitWuxingPearl()
{
	DataXMLWuxingPearl *pdata = (DataXMLWuxingPearl *)m_shWuxingPearl.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shWuxingPearl), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("awakenConfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("wuxing_activity"))
	{
		cout<<("wuxing_activity node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	unsigned index_defence = 0;
	while (xmlConf.FindElem("reward"))
	{
		string cond_str = xmlConf.GetAttrib("cond");
		string eqid_str = xmlConf.GetAttrib("eqid");
		string count_str = xmlConf.GetAttrib("count");
		if (cond_str.empty() || eqid_str.empty() ||  count_str.empty())
		{
			cout << ("wuxing_activity config wrong 3") << endl;
			return R_ERROR;
		}

		(pdata->wuxing_perl_items_)[index_defence].cond_ = CTrans::STOI(cond_str.c_str());
		(pdata->wuxing_perl_items_)[index_defence].eqid_ = CTrans::STOI(eqid_str.c_str());
		(pdata->wuxing_perl_items_)[index_defence].count_ = CTrans::STOI(count_str.c_str());
		++index_defence;
	}
	m_shWuxingPearl.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetWuxingPearlData(unsigned index, unsigned &cond, unsigned &eqid, unsigned &count)
{
	DataXMLWuxingPearl *pdata = (DataXMLWuxingPearl *)m_shWuxingPearl.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shWuxingPearl)), true);
	if ((!index) || index > WUXING_PERAL_ITEM_COUNT)
	{
		PARAM_ERROR_RETURN_MSG("wuxing_pearl_index_error");
	}
	cond = (pdata->wuxing_perl_items_)[index-1].cond_;
	eqid = (pdata->wuxing_perl_items_)[index-1].eqid_;
	count = (pdata->wuxing_perl_items_)[index-1].count_;

	return R_SUCCESS;
}
/**************五行灵珠 end**********************/


/**************心动特卖**********************/
int CDataXML::InitHeartbeatBigSale()
{
	DataXMLHeartbeatBigSale *pdata = (DataXMLHeartbeatBigSale *)m_shHeartbeatBigSale.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shHeartbeatBigSale), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("zaohuage.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("temai"))
	{
		cout << ("temai node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned zone_section_index = 0;
	while (xmlConf.FindElem("allItem"))
	{
		string zone = xmlConf.GetAttrib("zone");
		if(zone.empty())
		{
			cout << ("zaohuage config wrong 1") << endl;
			return R_ERROR;
		}
		string min_zone_str = zone.substr(0, zone.find("-"));
		string max_zone_str = zone.substr(zone.find("-")+1);
		int min_zone = CTrans::STOI(min_zone_str.c_str());
		int max_zone = CTrans::STOI(max_zone_str.c_str());
		(pdata->all_items_)[zone_section_index].start_zone_ = min_zone;
		(pdata->all_items_)[zone_section_index].end_zone_ = max_zone;

		xmlConf.IntoElem();
		unsigned item_index = 0;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string cash = xmlConf.GetAttrib("diamond");
			string limit_count = xmlConf.GetAttrib("limitcount");
			string item_data = xmlConf.GetData();
			if (id.empty() || cash.empty() || limit_count.empty() || item_data.empty())
			{
				cout << ("temai config wrong 3") << endl;
				return R_ERROR;
			}
			Json::Reader reader;
			Json::Value json_item_data;
			reader.parse(item_data, json_item_data);
			(pdata->all_items_)[zone_section_index].section_items_[item_index].id_ = CTrans::STOI(id.c_str());
			(pdata->all_items_)[zone_section_index].section_items_[item_index].cash_ = CTrans::STOI(cash.c_str());
			(pdata->all_items_)[zone_section_index].section_items_[item_index].limit_ = CTrans::STOI(limit_count.c_str());
			(pdata->all_items_)[zone_section_index].section_items_[item_index].reward_.eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
			(pdata->all_items_)[zone_section_index].section_items_[item_index].reward_.cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
			(pdata->all_items_)[zone_section_index].section_items_[item_index].reward_.q_ = json_item_data["reward"]["equip"]["q"].asUInt();
			(pdata->all_items_)[zone_section_index].section_items_[item_index].reward_.ch_ = json_item_data["reward"]["equip"]["ch"].asUInt();
			++item_index;
		}
		xmlConf.OutOfElem();
		++zone_section_index;
	}
	xmlConf.OutOfElem();

	m_shHeartbeatBigSale.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetHeartbeatBigSaleItem(unsigned sid, unsigned index, XMLHeartbeatBigSaleItem & item)
{
	DataXMLHeartbeatBigSale *pdata = (DataXMLHeartbeatBigSale *)m_shHeartbeatBigSale.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeartbeatBigSale)), true);

	unsigned section_index = 0;
	if (OpenPlatform::IsLYPlatform())
	{
		section_index = HEART_BEAT_BIG_SALE_SECTION_NUM - 1;
	}else
	{
		if (sid >= (pdata->all_items_)[0].start_zone_ &&
			sid <= (pdata->all_items_)[0].end_zone_)
		{
			section_index = 0;
		} else
		{
			section_index = HEART_BEAT_BIG_SALE_SECTION_NUM - 1;
		}
	}

	item = (pdata->all_items_)[section_index].section_items_[index];

	return R_SUCCESS;
}
/****************************************/


/**************五行商铺  begin**********************/
int CDataXML::InitFiveShop()
{
	DataXMLFiveShop *pdata = (DataXMLFiveShop *)m_shFiveShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shFiveShop), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("wuxing_shop"))
	{
		cout << ("wuxing_shop node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("special_shop"))
	{
		cout << ("special_shop node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned item_index = 0;
	while (xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string eqid = xmlConf.GetAttrib("eqid");
		string eqcount = xmlConf.GetAttrib("eqcount");
		string price = xmlConf.GetAttrib("price");
		string limit = xmlConf.GetAttrib("limit");
		if (id.empty() || eqid.empty() || eqcount.empty() || price.empty() || limit.empty())
		{
			cout << ("special_shop config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->five_special_shop_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->five_special_shop_items_)[item_index].eqid_ = CTrans::STOI(eqid.c_str());
		(pdata->five_special_shop_items_)[item_index].eq_cnt_ = CTrans::STOI(eqcount.c_str());
		(pdata->five_special_shop_items_)[item_index].price_ = CTrans::STOI(price.c_str());
		(pdata->five_special_shop_items_)[item_index].limit_ = CTrans::STOI(limit.c_str());
		++item_index;
	}
	xmlConf.OutOfElem();

	if(!xmlConf.FindElem("discount_shop"))
	{
		cout << ("discount_shop node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();
	item_index = 0;
	while (xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string eqid = xmlConf.GetAttrib("eqid");
		string eqcount = xmlConf.GetAttrib("eqcount");
		string price = xmlConf.GetAttrib("price");
		string quan = xmlConf.GetAttrib("quan");
		string limit = xmlConf.GetAttrib("limit");
		if (id.empty() || eqid.empty() || eqcount.empty() || price.empty() || quan.empty() || limit.empty())
		{
			cout << ("special_shop config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->five_discount_shop_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->five_discount_shop_items_)[item_index].eqid_ = CTrans::STOI(eqid.c_str());
		(pdata->five_discount_shop_items_)[item_index].eq_cnt_ = CTrans::STOI(eqcount.c_str());
		(pdata->five_discount_shop_items_)[item_index].price_ = CTrans::STOI(price.c_str());
		(pdata->five_discount_shop_items_)[item_index].quan_ = CTrans::STOI(quan.c_str());
		(pdata->five_discount_shop_items_)[item_index].limit_ = CTrans::STOI(limit.c_str());
		++item_index;
	}
	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("quan"))
	{
		cout << ("quan node wrong") << endl;
		return 1;
	}
	string pay = xmlConf.GetAttrib("pay");
	string count = xmlConf.GetAttrib("count");
	string limit = xmlConf.GetAttrib("limit");
	if (pay.empty() || count.empty() || limit.empty())
	{
		cout << ("quan config wrong 3") << endl;
		return R_ERROR;
	}
	pdata->quan_pay_ = CTrans::STOI(pay.c_str());
	pdata->quan_count_ = CTrans::STOI(count.c_str());
	pdata->quan_limit_ = CTrans::STOI(limit.c_str());

	m_shFiveShop.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetFiveSpecialShopItem(unsigned index, XMLFiveSpecialShopItem & item)
{
	DataXMLFiveShop *pdata = (DataXMLFiveShop *)m_shFiveShop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFiveShop)), true);


	if (index >= MAX_FIVE_SPECIAL_SHOP_ITEMS)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->five_special_shop_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetFiveDiscountShopItem(unsigned index, XMLFiveDiscountShopItem & item)
{
	DataXMLFiveShop *pdata = (DataXMLFiveShop *)m_shFiveShop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFiveShop)), true);

	if (index >= MAX_FIVE_DISCOUNT_SHOP_ITEMS)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->five_discount_shop_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetFiveShopQuan(unsigned & pay, unsigned & count, unsigned & limit)
{
	DataXMLFiveShop *pdata = (DataXMLFiveShop *)m_shFiveShop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFiveShop)), true);

	pay = pdata->quan_pay_;
	count = pdata->quan_count_;
	limit = pdata->quan_limit_;

	return R_SUCCESS;
}
/****************五行商铺  end************************/

int CDataXML::InitJinqiushiyueChongzhihuikui()
{
	int ret = 0;
	Json::Value data;

	ret = readJsonConfFile("chongzhihuikui.json", data);
	if (ret)
		return ret;

	if(!data.isMember("chongzhihuikui") || !data["chongzhihuikui"].isArray() || data["chongzhihuikui"].size() != CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX
	|| !data.isMember("jinqiushiyue") || !data["jinqiushiyue"].isArray() || data["jinqiushiyue"].size() != CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX)
	{
		error_log("chongzhihuikui.json is error");
		return R_ERR_DATA;
	}

	{
		Json::Value& temp = data["chongzhihuikui"];
		for(unsigned i=0;i<temp.size();++i)
			m_chongzhihuikui[i] = make_pair(temp[i]["need"].asUInt(), make_pair(make_pair(temp[i]["id1"].asUInt(),temp[i]["count1"].asUInt()), make_pair(temp[i]["id2"].asUInt(),temp[i]["count2"].asUInt())));
	}
	{
		Json::Value& temp = data["jinqiushiyue"];
		for(unsigned i=0;i<temp.size();++i)
			m_jinqiushiyue[i] = make_pair(temp[i]["need"].asUInt(), make_pair(make_pair(temp[i]["id1"].asUInt(),temp[i]["count1"].asUInt()), make_pair(temp[i]["id2"].asUInt(),temp[i]["count2"].asUInt())));
	}

	return R_SUCCESS;
}
int CDataXML::GetJinqiushiyue(unsigned index, unsigned type, unsigned& need, pair<unsigned, unsigned> &item)
{
	if(!m_jinqiushiyue.count(index))
		return R_ERR_PARAM;
	need = m_jinqiushiyue[index].first;
	if(type)
		item = m_jinqiushiyue[index].second.second;
	else
		item = m_jinqiushiyue[index].second.first;
	return 0;
}
int CDataXML::GetChongzhihuikui(unsigned index, unsigned type, unsigned& need, pair<unsigned, unsigned> &item)
{
	if(!m_chongzhihuikui.count(index))
		return R_ERR_PARAM;
	need = m_chongzhihuikui[index].first;
	if(type)
		item = m_chongzhihuikui[index].second.second;
	else
		item = m_chongzhihuikui[index].second.first;
	return 0;
}

int CDataXML::InitZhiZunBaoXiang()
{
	int ret = 0;
	Json::Value data;

	ret = readJsonConfFile("zhizunbaoxiang.json", data);
	if (ret)
		return ret;

	if(!data.isMember("kapai") || !data["kapai"].isArray()
	|| !data.isMember("baoxiang") || !data["baoxiang"].isArray())
	{
		error_log("zhizunbaoxiang.json is error");
		return R_ERR_DATA;
	}

	{
		Json::Value& temp = data["kapai"];
		unsigned s = 0;
		for(unsigned i=0;i<temp.size();++i)
		{
			s += temp[i]["rate"].asUInt();
			m_zhizunbaoxiang_kapai.push_back(make_pair(s, make_pair(temp[i]["id"].asUInt(),temp[i]["count"].asUInt())));
		}
	}
	{
		Json::Value& temp = data["baoxiang"];
		for(unsigned i=0;i<temp.size();++i)
			m_zhizunbaoxiang_baoxiang.push_back(make_pair(temp[i]["need"].asUInt(), temp[i]["id"].asUInt()));
	}

	return R_SUCCESS;
}
int CDataXML::GetZhiZunBaoXiangK(pair<unsigned, unsigned> &item)
{
	unsigned r = Math::GetRandomInt(100);
	for(vector<pair<unsigned, pair<unsigned, unsigned> > >::iterator it=m_zhizunbaoxiang_kapai.begin();it!=m_zhizunbaoxiang_kapai.end();++it)
	{
		if(r < it->first)
		{
			item = it->second;
			return 0;
		}
	}
	item = m_zhizunbaoxiang_kapai.begin()->second;
	return 0;
}
int CDataXML::GetZhiZunBaoXiangB(unsigned index, pair<unsigned, unsigned> &item)
{
	if(index >= m_zhizunbaoxiang_baoxiang.size())
		return R_ERR_PARAM;
	item = m_zhizunbaoxiang_baoxiang[index];
	return 0;
}


/**************觉醒特惠  begin**********************/
int CDataXML::InitJueXingTeHui()
{
	DataXMLJueXingTeHui *pdata = (DataXMLJueXingTeHui *)m_shJueXingTeHui.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shJueXingTeHui), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("activityconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("juexinghuikui"))
	{
		cout << ("juexinghuikui node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned item_index = 0;
	while (xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string eqid = xmlConf.GetAttrib("eqid");
		string price = xmlConf.GetAttrib("cost");
		string limit = xmlConf.GetAttrib("limit");
		string wj_cnt = xmlConf.GetAttrib("needwj");
		string wj_jie = xmlConf.GetAttrib("needjie");
		if (id.empty() || eqid.empty() || price.empty() || limit.empty() || wj_cnt.empty() || wj_jie.empty())
		{
			cout << ("juexingtehui item config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->juexingtehui_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->juexingtehui_items_)[item_index].eqid_ = CTrans::STOI(eqid.c_str());
		(pdata->juexingtehui_items_)[item_index].price_ = CTrans::STOI(price.c_str());
		(pdata->juexingtehui_items_)[item_index].limit_ = CTrans::STOI(limit.c_str());
		(pdata->juexingtehui_items_)[item_index].wj_cnt_ = CTrans::STOI(wj_cnt.c_str());
		(pdata->juexingtehui_items_)[item_index].wj_jie_ = CTrans::STOI(wj_jie.c_str());
		++item_index;
	}
	pdata->item_real_cnt_ = item_index;
	xmlConf.OutOfElem();

	m_shJueXingTeHui.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetJueXingTeHuiItem(unsigned index, XMLJueXingTeHuiItem & item)
{
	DataXMLJueXingTeHui *pdata = (DataXMLJueXingTeHui *)m_shJueXingTeHui.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJueXingTeHui)), true);

	if (index >= pdata->item_real_cnt_)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->juexingtehui_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetJueXingTeHuiItemsCnt(unsigned & cnt)
{
	DataXMLJueXingTeHui *pdata = (DataXMLJueXingTeHui *)m_shJueXingTeHui.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJueXingTeHui)), true);

	cnt = pdata->item_real_cnt_;
	return R_SUCCESS;
}
/**************觉醒特惠  end**********************/


/**************免费兑换 begin**********************/
int CDataXML::InitFreeExchange()
{
	DataXMLFreeExchange *pdata = (DataXMLFreeExchange *)m_shFreeExchange.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shFreeExchange), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("activityconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("xianshiduihuan"))
	{
		cout << ("xianshiduihuan node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	Json::Reader reader;
	Json::Value json_item_data;
	unsigned item_index = 0;
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("type");
		string eqid1;
		if (CTrans::STOI(type.c_str()) == 1)
		{
			eqid1 = xmlConf.GetAttrib("eqid1");
		} else
		{
			eqid1 = xmlConf.GetAttrib("qh1");
		}
		string need1 = xmlConf.GetAttrib("need1");
		string eqid2 = xmlConf.GetAttrib("eqid2");
		string need2 = xmlConf.GetAttrib("need2");
		string limit = xmlConf.GetAttrib("count");
		string item_data = xmlConf.GetData();
		if (id.empty() || type.empty() || eqid1.empty() || need1.empty() || eqid2.empty() || need2.empty() || limit.empty())
		{
			cout << ("xianshiduihuan config wrong 3") << endl;
			return R_ERROR;
		}

		json_item_data.clear();
		reader.parse(item_data,json_item_data);
		(pdata->free_exchange_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->free_exchange_items_)[item_index].type_ = CTrans::STOI(type.c_str());
		(pdata->free_exchange_items_)[item_index].eqid1_ = CTrans::STOI(eqid1.c_str());
		(pdata->free_exchange_items_)[item_index].need1_ = CTrans::STOI(need1.c_str());
		(pdata->free_exchange_items_)[item_index].eqid2_ = CTrans::STOI(eqid2.c_str());
		(pdata->free_exchange_items_)[item_index].need2_ = CTrans::STOI(need2.c_str());
		(pdata->free_exchange_items_)[item_index].limit_ = CTrans::STOI(limit.c_str());
		(pdata->free_exchange_items_)[item_index].reward_.eqid_ = json_item_data["reward"]["equip1"]["id"].asUInt();
		(pdata->free_exchange_items_)[item_index].reward_.cnt_ = json_item_data["reward"]["equip1"]["c"].asUInt();
		++item_index;
	}
	xmlConf.OutOfElem();
	pdata->item_real_cnt_ = item_index;

	m_shFreeExchange.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetFreeExchangeItem(unsigned index, XMLFreeExchangeItem & item)
{
	DataXMLFreeExchange *pdata = (DataXMLFreeExchange *)m_shFreeExchange.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFreeExchange)), true);

	if (index >= pdata->item_real_cnt_)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->free_exchange_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetFreeExchangeItemsCnt(unsigned & cnt)
{
	DataXMLFreeExchange *pdata = (DataXMLFreeExchange *)m_shFreeExchange.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shFreeExchange)), true);

	cnt = pdata->item_real_cnt_;
	return R_SUCCESS;
}

/**************免费兑换 end**********************/


/**************双11 begin**********************/
int CDataXML::InitDoubleEleven()
{
	DataXMLDoubleEleven *pdata = (DataXMLDoubleEleven *)m_shDoubleEleven.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shDoubleEleven), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("shuang11"))
	{
		cout << ("shuang11 node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	Json::Reader reader;
	Json::Value json_item_data;
	unsigned item_index = 0;
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string limitbuy = xmlConf.GetAttrib("limitbuy");
		string recharge = xmlConf.GetAttrib("recharge");
		string rewardid = xmlConf.GetAttrib("rewardid");
		string rewardcnt = xmlConf.GetAttrib("rewardcount");
		string item_data = xmlConf.GetData();
		if (id.empty() || limitbuy.empty() || recharge.empty() || rewardid.empty() || rewardcnt.empty())
		{
			cout << ("double eleven config wrong 3") << endl;
			return R_ERROR;
		}

		json_item_data.clear();
		reader.parse(item_data,json_item_data);
		(pdata->doubleeleven_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->doubleeleven_items_)[item_index].limitbuy_ = CTrans::STOI(limitbuy.c_str());
		(pdata->doubleeleven_items_)[item_index].recharge_ = CTrans::STOI(recharge.c_str());
		(pdata->doubleeleven_items_)[item_index].rewardid_ = CTrans::STOI(rewardid.c_str());
		(pdata->doubleeleven_items_)[item_index].rewardcnt_ = CTrans::STOI(rewardcnt.c_str());
		for(unsigned inx = 0; inx != DOUBLE_ELEVEN_SMALL_ITEMS_CNT; ++inx)
		{
			(pdata->doubleeleven_items_)[item_index].small_items_[inx].id_ = (inx + 1);
			(pdata->doubleeleven_items_)[item_index].small_items_[inx].eqid_ = json_item_data["shop"][inx]["eqid"].asUInt();
			(pdata->doubleeleven_items_)[item_index].small_items_[inx].cnt_ = json_item_data["shop"][inx]["c"].asUInt();
			(pdata->doubleeleven_items_)[item_index].small_items_[inx].cash_ = json_item_data["shop"][inx]["cost"].asUInt();
		}
		++item_index;
	}
	xmlConf.OutOfElem();
	pdata->big_item_cnt_ = item_index;

	m_shDoubleEleven.SetInitDone();
	return R_SUCCESS;
}


int CDataXML::GetDoubleElevenBigItem(unsigned big_index, XMLDoubleElevenBigItem & item)
{
	DataXMLDoubleEleven *pdata = (DataXMLDoubleEleven *)m_shDoubleEleven.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shDoubleEleven)), true);

	if (big_index >= pdata->big_item_cnt_)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->doubleeleven_items_)[big_index];

	return R_SUCCESS;
}


int CDataXML::GetDoubleElevenBigItemsCnt(unsigned & cnt)
{
	DataXMLDoubleEleven *pdata = (DataXMLDoubleEleven *)m_shDoubleEleven.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shDoubleEleven)), true);

	cnt = pdata->big_item_cnt_;

	return R_SUCCESS;
}

/**************双11 end**********************/


/**************聚宝匣 begin**********************/
int CDataXML::InitJuBaoXia()
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shJuBaoXia), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("mooncake.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("box"))
	{
		cout << ("box node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("normal"))
	{
		cout << ("normal node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();  //进入normal

	unsigned item_index = 0;
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string amount = xmlConf.GetAttrib("amount");
		string rate = xmlConf.GetAttrib("rate");
		if (id.empty() || amount.empty() || rate.empty())
		{
			cout << ("jubaoxia config wrong 3") << endl;
			return R_ERROR;
		}

		(pdata->common_items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->common_items_)[item_index].amount_ = CTrans::STOI(amount.c_str());
		(pdata->common_items_)[item_index].rate_ = CTrans::STOI(rate.c_str());
		++item_index;
	}
	xmlConf.OutOfElem(); //退出normal

	if(!xmlConf.FindElem("last"))
	{
		cout << ("last node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();  //进入last
	item_index = 0;
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string amount = xmlConf.GetAttrib("amount");
		string rate = xmlConf.GetAttrib("rate");
		if (id.empty() || amount.empty() || rate.empty())
		{
			cout << ("jubaoxia config wrong 3") << endl;
			return R_ERROR;
		}

		if (string::npos == id.find('H'))   //装备
		{
			(pdata->precious_items_)[item_index].id_ = CTrans::STOI(id.c_str());
			(pdata->precious_items_)[item_index].is_hero_ = false;
		}
		else
		{
			(pdata->precious_items_)[item_index].id_ = CTrans::STOI(id.substr(1).c_str());
			(pdata->precious_items_)[item_index].is_hero_ = true;
		}
		(pdata->precious_items_)[item_index].amount_ = CTrans::STOI(amount.c_str());
		vector<string> temp;
		String::Split(rate, '_', temp);
		//cout <<item_index << endl;
		//cout <<(pdata->precious_items_)[item_index].id_ << endl;
		//cout <<(pdata->precious_items_)[item_index].amount_ << endl;
		//cout <<(pdata->precious_items_)[item_index].is_hero_ << endl;
		for(unsigned inx = 0; inx != JUBAOXIA_PRECIOUS_RATE_KINDS; ++inx)
		{
			(pdata->precious_items_)[item_index].rate_[inx] = CTrans::STOI(temp[inx]);
			//cout << inx << "  " << (pdata->precious_items_)[item_index].rate_[inx] << endl;
		}

		++item_index;
	}
	xmlConf.OutOfElem();  //退出 last
	xmlConf.OutOfElem();  //退出 box

	if(!xmlConf.FindElem("exchange"))
	{
		cout << ("exchange node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();  //进入exchange

	if(!xmlConf.FindElem("dayfree"))
	{
		cout << ("dayfree node wrong") << endl;
		return 1;
	}
	string id_free = xmlConf.GetAttrib("id");
	string amount_free = xmlConf.GetAttrib("amount");
	if (id_free.empty() || amount_free.empty())
	{
		cout << ("jubaoxia config wrong 4") << endl;
		return R_ERROR;
	}
	(pdata->daily_free_item).id_ = CTrans::STOI(id_free.c_str());
	(pdata->daily_free_item).cnt_ = CTrans::STOI(amount_free.c_str());

	if(!xmlConf.FindElem("buy"))
	{
		cout << ("buy node wrong") << endl;
		return 1;
	}
	string nid = xmlConf.GetAttrib("nid");
	string namount = xmlConf.GetAttrib("namount");
	string ngold = xmlConf.GetAttrib("ngold");
	string gid = xmlConf.GetAttrib("gid");
	string gamount = xmlConf.GetAttrib("gamount");
	if (nid.empty()     ||
		namount.empty() ||
		ngold.empty()   ||
		gid.empty()     ||
		gamount.empty())
	{
		cout << ("jubaoxia config wrong 4") << endl;
		return R_ERROR;
	}
	(pdata->exchange_item).need_id_ = CTrans::STOI(nid.c_str());
	(pdata->exchange_item).need_cnt_ = CTrans::STOI(namount.c_str());
	(pdata->exchange_item).need_cash_ = CTrans::STOI(ngold.c_str());
	(pdata->exchange_item).get_id_ = CTrans::STOI(gid.c_str());
	(pdata->exchange_item).get_cnt_ = CTrans::STOI(gamount.c_str());

	item_index = 0;
	while(xmlConf.FindElem("costget"))
	{
		string ncharge = xmlConf.GetAttrib("ncharge");
		string gid = xmlConf.GetAttrib("gid");
		string gamount = xmlConf.GetAttrib("gamount");
		if (ncharge.empty() || gid.empty() || gamount.empty())
		{
			cout << ("jubaoxia config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->key_items)[item_index].need_charge_ = CTrans::STOI(ncharge.c_str());
		(pdata->key_items)[item_index].get_id_ = CTrans::STOI(gid.c_str());
		(pdata->key_items)[item_index].get_cnt_ = CTrans::STOI(gamount.c_str());
		++item_index;
	}

	m_shJuBaoXia.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaCommonRate(map<unsigned, unsigned> & rate)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	for(unsigned inx = 0; inx != JUBAOXIA_COMMON_CNT; ++inx)
	{
		rate[inx] = (pdata->common_items_)[inx].rate_;
	}

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaPreciousRate(unsigned circle, map<unsigned, unsigned> & rate)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	for(unsigned inx = 0; inx != JUBAOXIA_PRECIOUS_CNT; ++inx)
	{
		rate[inx] = (pdata->precious_items_) [inx].rate_[circle-1];
	}

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaCommonItem(unsigned index, XMLJuBaoXiaTreasureCommonItem & item)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	item = (pdata->common_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaPreciousItem(unsigned index, XMLJuBaoXiaTreasurePreciousItem & item)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	item = (pdata->precious_items_)[index];

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaDailyFreeItem(XMLJuBaoXiaDailyFreeItem & item)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	item = pdata->daily_free_item;

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaExchangeItem(XMLJuBaoXiaExchangeItem & item)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	item = pdata->exchange_item;

	return R_SUCCESS;
}


int CDataXML::GetJuBaoXiaKeyItem(unsigned index, XMLJuBaoXiaKeyItem & item)
{
	DataXMLJuBaoXia *pdata = (DataXMLJuBaoXia *)m_shJuBaoXia.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shJuBaoXia)), true);

	item = pdata->key_items[index];

	return R_SUCCESS;
}
/**************聚宝匣 end**********************/



/**************兵书进阶 begin**********************/
int CDataXML::InitHeavenStep()
{
	DataXMLHeavenStep *pdata = (DataXMLHeavenStep *)m_shHeavenStep.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shHeavenStep), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("linshibingshu.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("bingshu"))
	{
		cout << ("bingshu step node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned jie_index = 0;
	while(xmlConf.FindElem("jie"))
	{
		string id = xmlConf.GetAttrib("id");
		(pdata->reward_items_)[jie_index].jie_id_ = CTrans::STOI(id.c_str());
		xmlConf.IntoElem();

		Json::Reader reader;
		Json::Value json_item_data;
		unsigned item_index = 0;
		while(xmlConf.FindElem("reward"))
		{
			string item_data = xmlConf.GetData();
			json_item_data.clear();
			reader.parse(item_data, json_item_data);
			(pdata->reward_items_)[jie_index].eqid_[item_index] = json_item_data["reward"]["equip1"]["id"].asUInt();
			(pdata->reward_items_)[jie_index].cnt_[item_index] = json_item_data["reward"]["equip1"]["c"].asUInt();
			++item_index;
		}
		xmlConf.OutOfElem();
		++jie_index;
	}

	m_shHeavenStep.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetHeavenStepItem(unsigned jie, XMLHeavenStepRewardItem & item)
{
	DataXMLHeavenStep *pdata = (DataXMLHeavenStep *)m_shHeavenStep.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeavenStep)), true);

	if (jie != (pdata->reward_items_)[jie-1].jie_id_)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->reward_items_)[jie-1];

	return R_SUCCESS;
}
/**************兵书进阶 end**********************/



/**************遁甲进阶 begin**********************/
int CDataXML::InitDaoistStep()
{
	DataXMLDaoistStep *pdata = (DataXMLDaoistStep *)m_shDaoistStep.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shDaoistStep), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("linshibingshu.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("dunjia"))
	{
		cout << ("dunjia step node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned jie_index = 0;
	while(xmlConf.FindElem("jie"))
	{
		string id = xmlConf.GetAttrib("id");
		(pdata->reward_items_)[jie_index].jie_id_ = CTrans::STOI(id.c_str());
		xmlConf.IntoElem();

		Json::Reader reader;
		Json::Value json_item_data;
		unsigned item_index = 0;
		while(xmlConf.FindElem("reward"))
		{
			string item_data = xmlConf.GetData();
			json_item_data.clear();
			reader.parse(item_data, json_item_data);
			(pdata->reward_items_)[jie_index].eqid_[item_index] = json_item_data["reward"]["equip1"]["id"].asUInt();
			(pdata->reward_items_)[jie_index].cnt_[item_index] = json_item_data["reward"]["equip1"]["c"].asUInt();
			++item_index;
		}
		xmlConf.OutOfElem();
		++jie_index;
	}

	m_shDaoistStep.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetDaoistStepItem(unsigned jie, XMLDaoistStepRewardItem & item)
{
	DataXMLDaoistStep *pdata = (DataXMLDaoistStep *)m_shDaoistStep.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shDaoistStep)), true);

	if (jie != (pdata->reward_items_)[jie-1].jie_id_)
	{
		return R_ERR_LOGIC;
	}
	item = (pdata->reward_items_)[jie-1];

	return R_SUCCESS;
}
/**************遁甲进阶 end**********************/


/**************珍宝阁魂石 begin**********************/
int CDataXML::InitZhenBaoGeHero()
{
	DataXMLZhenBaoGeHero *pdata = (DataXMLZhenBaoGeHero *)m_shZhenBaoGeHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shZhenBaoGeHero), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("zhenbaoge.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while(xmlConf.FindElem("stone"))
	{
		string big_id = xmlConf.GetAttrib("id");
		unsigned big_index = CTrans::STOI(big_id.c_str()) - 1;
		xmlConf.IntoElem();

		unsigned item_index = 0;
		while(xmlConf.FindElem("item"))
		{
			string eqid = xmlConf.GetAttrib("id");
			string amount = xmlConf.GetAttrib("amount");
			string price = xmlConf.GetAttrib("price");
			string maxTimes = xmlConf.GetAttrib("maxTimes");
			if (eqid.empty() || amount.empty() || price.empty() || maxTimes.empty())
			{
				cout << ("zhenbaoge config wrong 3") << endl;
				return R_ERROR;
			}
			(pdata->items_)[big_index][item_index].eqid_ = CTrans::STOI(eqid.c_str());
			(pdata->items_)[big_index][item_index].eq_cnt_ = CTrans::STOI(amount.c_str());
			(pdata->items_)[big_index][item_index].cash_ = CTrans::STOI(price.c_str());
			(pdata->items_)[big_index][item_index].limit_times_ = CTrans::STOI(maxTimes.c_str());
			++item_index;
		}
		xmlConf.OutOfElem();
	}

	m_shZhenBaoGeHero.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetZhenBaoGeHeroItem(unsigned big_index, unsigned small_index, XMLZhenBaoGeHeroItem & item)
{
	DataXMLZhenBaoGeHero *pdata = (DataXMLZhenBaoGeHero *)m_shZhenBaoGeHero.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shZhenBaoGeHero)), true);

	item = (pdata->items_)[big_index][small_index];

	return R_SUCCESS;
}
/**************珍宝阁魂石 end**********************/


/**************珍宝阁宝石 begin**********************/
int CDataXML::InitZhenBaoGeBuilding()
{
	DataXMLZhenBaoGeBuilding *pdata = (DataXMLZhenBaoGeBuilding *)m_shZhenBaoGeBuilding.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shZhenBaoGeBuilding), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("zhenbaoge.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while(xmlConf.FindElem("building"))
	{
		string big_id = xmlConf.GetAttrib("id");
		unsigned big_index = CTrans::STOI(big_id.c_str()) - 1;
		xmlConf.IntoElem();

		unsigned item_index = 0;
		while(xmlConf.FindElem("item"))
		{
			string eqid = xmlConf.GetAttrib("id");
			string amount = xmlConf.GetAttrib("amount");
			string price = xmlConf.GetAttrib("price");
			string maxTimes = xmlConf.GetAttrib("maxTimes");
			if (eqid.empty() || amount.empty() || price.empty() || maxTimes.empty())
			{
				cout << ("zhenbaoge config wrong 3") << endl;
				return R_ERROR;
			}
			(pdata->items_)[big_index][item_index].eqid_ = CTrans::STOI(eqid.c_str());
			(pdata->items_)[big_index][item_index].eq_cnt_ = CTrans::STOI(amount.c_str());
			(pdata->items_)[big_index][item_index].cash_ = CTrans::STOI(price.c_str());
			(pdata->items_)[big_index][item_index].limit_times_ = CTrans::STOI(maxTimes.c_str());
			++item_index;
		}
		xmlConf.OutOfElem();
	}

	m_shZhenBaoGeBuilding.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetZhenBaoGeBuildingItem(unsigned big_index, unsigned small_index, XMLZhenBaoGeBuildingItem & item)
{
	DataXMLZhenBaoGeBuilding *pdata = (DataXMLZhenBaoGeBuilding *)m_shZhenBaoGeBuilding.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shZhenBaoGeBuilding)), true);

	item = (pdata->items_)[big_index][small_index];

	return R_SUCCESS;
}
/**************珍宝阁宝石 end**********************/


/**************魂石进阶 begin**********************/
int CDataXML::InitHeroStoneStep()
{
	DataXMLHeroStoneStep *pdata = (DataXMLHeroStoneStep *)m_shHeroStoneStep.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shHeroStoneStep), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("strengthactivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("stones"))
	{
		cout << ("stones node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned item_index = 0;
	while(xmlConf.FindElem("stone"))
	{
		string id = xmlConf.GetAttrib("id");
		string lv = xmlConf.GetAttrib("lv");
		string maxcount = xmlConf.GetAttrib("maxcount");
		Json::Reader reader;
		string item_data = xmlConf.GetData();
		Json::Value json_item_data;
		reader.parse(item_data, json_item_data);
		if (id.empty() || lv.empty() || maxcount.empty())
		{
			cout << ("HeroStoneStep config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->items_)[item_index].lv_ = CTrans::STOI(lv.c_str());
		(pdata->items_)[item_index].maxcount_ = CTrans::STOI(maxcount.c_str());
		(pdata->items_)[item_index].reward_.eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
		(pdata->items_)[item_index].reward_.eq_cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
		(pdata->items_)[item_index].reward_.q_ = json_item_data["reward"]["equip"]["q"].asUInt();
		++item_index;
	}

	m_shHeroStoneStep.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetHeroStoneStepItem(unsigned index, XMLHeroStoneStepItem & item)
{
	DataXMLHeroStoneStep *pdata = (DataXMLHeroStoneStep *)m_shHeroStoneStep.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeroStoneStep)), true);

	item = (pdata->items_)[index];

	return R_SUCCESS;
}
/**************魂石进阶 end**********************/


/**************宝石进阶 begin**********************/
int CDataXML::InitBuildingStoneStep()
{
	DataXMLBuildingStoneStep *pdata = (DataXMLBuildingStoneStep *)m_shBuildingStoneStep.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shBuildingStoneStep), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("strengthactivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("building"))
	{
		cout << ("building node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned item_index = 0;
	while(xmlConf.FindElem("stone"))
	{
		string id = xmlConf.GetAttrib("id");
		string lv = xmlConf.GetAttrib("lv");
		string maxcount = xmlConf.GetAttrib("maxcount");
		Json::Reader reader;
		string item_data = xmlConf.GetData();
		Json::Value json_item_data;
		reader.parse(item_data, json_item_data);
		if (id.empty() || lv.empty() || maxcount.empty())
		{
			cout << ("BuildingStoneStep config wrong 3") << endl;
			return R_ERROR;
		}
		(pdata->items_)[item_index].id_ = CTrans::STOI(id.c_str());
		(pdata->items_)[item_index].lv_ = CTrans::STOI(lv.c_str());
		(pdata->items_)[item_index].maxcount_ = CTrans::STOI(maxcount.c_str());
		(pdata->items_)[item_index].reward_.eqid_ = json_item_data["reward"]["equip"]["id"].asUInt();
		(pdata->items_)[item_index].reward_.eq_cnt_ = json_item_data["reward"]["equip"]["c"].asUInt();
		(pdata->items_)[item_index].reward_.q_ = json_item_data["reward"]["equip"]["q"].asUInt();
		++item_index;
	}

	m_shBuildingStoneStep.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetBuildingStoneStepItem(unsigned index, XMLBuildingStoneStepItem & item)
{
	DataXMLBuildingStoneStep *pdata = (DataXMLBuildingStoneStep *)m_shBuildingStoneStep.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shBuildingStoneStep)), true);

	item = (pdata->items_)[index];

	return R_SUCCESS;
}
/**************宝石进阶 end**********************/


/**************11月回馈 begin**********************/
int CDataXML::InitJinQiuNovember()
{
	int ret = 0;
	Json::Value data;
	ret = readJsonConfFile("jinqiunovember.json", data);
	if (ret)
		return ret;

	if(!data.isMember("jinqiunovember") || !data["jinqiunovember"].isArray() || data["jinqiunovember"].size() != JINQIUNOVEMBER_INDEX)
	{
		error_log("jinqiunovember.json is error");
		return R_ERR_DATA;
	}
	{
		Json::Value& temp = data["jinqiunovember"];
		for(unsigned i=0;i<temp.size();++i)
			m_jinqiunovember[i] = make_pair(temp[i]["need"].asUInt(), make_pair(temp[i]["id"].asUInt(), temp[i]["count"].asUInt()));
	}

	return R_SUCCESS;
}


int CDataXML::GetJinQiuNovember(unsigned index, unsigned& need, pair<unsigned, unsigned> &item)
{
	if(!m_jinqiunovember.count(index))
		return R_ERR_PARAM;
	need = m_jinqiunovember[index].first;
	item = m_jinqiunovember[index].second;

	return R_SUCCESS;
}
/**************11月回馈 end**********************/


/**************充值送神纹符 begin**********************/
int CDataXML::InitAcchargeBackShenwen()
{
	int ret = 0;
	Json::Value data;
	ret = readJsonConfFile("jinqiunovember.json", data);
	if (ret)
		return ret;

	if(!data.isMember("acchargebackshenwen") || !data["acchargebackshenwen"].isArray() || data["acchargebackshenwen"].size() != ACCHARGEBACKSHENWEN_INDEX)
	{
		error_log("jinqiunovember.json is error");
		return R_ERR_DATA;
	}
	{
		Json::Value& temp = data["acchargebackshenwen"];
		for(unsigned i=0;i<temp.size();++i)
			m_acchargebackshenwen[i] = make_pair(temp[i]["need"].asUInt(), make_pair(temp[i]["id"].asUInt(), temp[i]["count"].asUInt()));
	}

	return R_SUCCESS;
}


int CDataXML::GetAcchargeBackShenwen(unsigned index, unsigned& need, pair<unsigned, unsigned> &item)
{
	if(!m_acchargebackshenwen.count(index))
		return R_ERR_PARAM;
	need = m_acchargebackshenwen[index].first;
	item = m_acchargebackshenwen[index].second;

	return R_SUCCESS;
}
/**************充值送神纹符 end**********************/


/**************成长开发 begin**********************/
int CDataXML::InitGrowDevelop()
{
	DataXMLGrowDevelop *pdata = (DataXMLGrowDevelop *)m_shGrowDevelop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_shGrowDevelop), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("potentialconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("HeroTrain"))
	{
		cout << ("HeroTrain node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned big_index = 0;
	while(xmlConf.FindElem("conditions"))
	{
		string level = xmlConf.GetAttrib("level");
		string require = xmlConf.GetAttrib("require");
		if (level.empty() || require.empty())
		{
			cout << ("GrowDevelop config wrong") << endl;
			return R_ERROR;
		}
		(pdata->items_)[big_index].level_ = CTrans::STOI(level.c_str());
		(pdata->items_)[big_index].require_ = CTrans::STOI(require.c_str());

		xmlConf.IntoElem();
		unsigned small_index = 0;
		while(xmlConf.FindElem("reward"))
		{
			Json::Reader reader;
			string item_data = xmlConf.GetData();
			if (item_data.empty())
			{
				cout << ("GrowDevelop item_data wrong") << endl;
				return R_ERROR;
			}
			Json::Value json_item_data;
			reader.parse(item_data, json_item_data);
			(pdata->items_)[big_index].rewards_[small_index].eqid_ = json_item_data["reward"]["equip1"]["id"].asUInt();
			(pdata->items_)[big_index].rewards_[small_index].eq_cnt_ = json_item_data["reward"]["equip1"]["c"].asUInt();
			(pdata->items_)[big_index].rewards_[small_index].q_ = json_item_data["reward"]["equip1"]["q"].asUInt();
			++small_index;
		}
		xmlConf.OutOfElem();

		++big_index;
	}
	xmlConf.OutOfElem();

	m_shGrowDevelop.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetGrowDevelopRewardItem(unsigned big_index, unsigned small_index, XMLGrowDevelopRewardItem & item)
{
	DataXMLGrowDevelop *pdata = (DataXMLGrowDevelop *)m_shGrowDevelop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shGrowDevelop)), true);

	item = (pdata->items_)[big_index].rewards_[small_index];

	return R_SUCCESS;
}


int CDataXML::GetGrowDevelopCond(unsigned level, unsigned & require)
{
	if(level > HEROGROWDEVELOP_SMALL_CNT)
	{
		require = 10000;
		return R_SUCCESS;
	}

	DataXMLGrowDevelop *pdata = (DataXMLGrowDevelop *)m_shGrowDevelop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shGrowDevelop)), true);

	if ((pdata->items_)[level-1].level_ != level)
	{
		return R_ERR_LOGIC;
	}
	require = (pdata->items_)[level-1].require_;

	return R_SUCCESS;
}
/**************成长开发 end**********************/

/////////////////////////////////////////////////////////////////////////////////
//寒假狂欢
DataWinterHolidayRevelry::DataWinterHolidayRevelry(const Json::Value& jsonData)
	 : total_draw_reward_rate_(0)
{
	Json::Value jsonDrawRreward;
	if (! Json::GetArray(jsonData, "choujiang", jsonDrawRreward))
	{
		throw std::runtime_error("choujiang_member_array_error");
	}

	for (int i = 0; i < jsonDrawRreward.size(); i++)
	{
		_v_draw_reward.push_back(DataDrawRewardItem(jsonDrawRreward[i]));
		total_draw_reward_rate_ += _v_draw_reward[i].rate;
	}

	Json::Value jsonGetRreward;
	if (! Json::GetArray(jsonData, "lingqu", jsonGetRreward))
	{
		throw std::runtime_error("lingqu_member_array_error");
	}

	for (int i = 0; i < jsonGetRreward.size(); i++)
	{
		_v_get_reward.push_back(DataGetRewardItem(jsonGetRreward[i]));
	}

}

int DataWinterHolidayRevelry::RandomDrawRewardIndex() const
{
	int nRandomVal = Math::GetRandomInt(total_draw_reward_rate_);
	for (size_t i = 0; i < _v_draw_reward.size(); i++)
	{
		if (nRandomVal < _v_draw_reward[i].rate)
		{
			//return std::make_pair(_v_draw_reward[i].id, _v_draw_reward[i].count);
			return i;
		}

		nRandomVal -= _v_draw_reward[i].rate;
	}

	throw std::runtime_error("random_winter_holiday_revelry_reward_error");
}

const DataWinterHolidayRevelry::DataDrawRewardItem& DataWinterHolidayRevelry::DrawRewardItem(int index) const
{
	if (index < 0 || index >= (int)_v_draw_reward.size())
	{
		throw std::runtime_error("winter_holiday_revelry_draw_reward_index_error");
	}

	return _v_draw_reward[index];
}

int DataWinterHolidayRevelry::GetRewardItemsSize() const
{
	return _v_get_reward.size();
}

const DataWinterHolidayRevelry::DataGetRewardItem& DataWinterHolidayRevelry::GetRewardItem(int index) const
{
	if (index < 0 || index >= (int)_v_get_reward.size())
	{
		throw std::runtime_error("winter_holiday_revelry_get_reward_index_error");
	}

	return _v_get_reward[index];
}

int CDataXML::InitJsonWinterHolidayRevelry()
{
	int ret = 0;
	Json::Value data;

	ret = readJsonConfFile("hanjiakuanghuan.json", data);
	if (ret)
	{
		return ret;
	}

	try
	{
		m_JsonWinterHolidayRevelry = DataWinterHolidayRevelry(data);
	}
	catch(const std::exception& e)
	{
		error_log("hanjiakuanghuan.json is error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const DataWinterHolidayRevelry& CDataXML::GetWinterHolidayRevelryConfig() const
{
	return m_JsonWinterHolidayRevelry;
}

int CDataXML::InitTokenIntensify()
{
	Json::Value data;
	int ret = readJsonConfFile("xinwuqianghua.json", data);
	if (ret != 0) return ret;

	try
	{
		m_tokenIntensify = DataTokenIntensify(data);
	}
	catch(const std::exception& e)
	{
		error_log("xinwuqianghua.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const DataTokenIntensify& CDataXML::GetTokenIntensify() const
{
	return m_tokenIntensify;
}

//////////////////////////////////////////////////////////////////////////////////////////
//世间秘宝
int CDataXML::InitWorldTreasure()
{
	Json::Value data;
	int ret = readJsonConfFile("shijianmibao.json", data);
	if (ret != 0) return ret;

	try
	{
		m_worldTreasure = ConfigWorldTreasure(data);
	}
	catch(const std::exception& e)
	{
		error_log("shijianmibao.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigWorldTreasure& CDataXML::GetConfigWorldTreasure() const
{
	return m_worldTreasure;
}

ConfigWorldTreasure::GoodsItem::GoodsItem(const Json::Value& jsonData)
{
	id_ = jsonData["id"].asInt();
	cnt_ = jsonData["amount"].asInt();
	prob_ = jsonData["rate"].asInt();

	if (id_ == 0 || cnt_ == 0 || prob_ == 0)
	{
		throw std::runtime_error("config_mishi_item_errro");
	}
}

ConfigWorldTreasure::AmountItem::AmountItem(const Json::Value& jsonData)
{
	value_ = jsonData["recharge"].asInt();
	items_ = jsonData["eqcount"].asInt();

	if (value_ == 0 || items_ == 0)
	{
		throw std::runtime_error("config_mibao_item_error");
	}
}

ConfigWorldTreasure::ConfigWorldTreasure(const Json::Value& jsonData)
{
	Json::Value jsonMiShi;
	Json::Value jsonMiBao;
	Json::GetArray(jsonData, "mishi", jsonMiShi);
	Json::GetArray(jsonData, "mibao", jsonMiBao);

	for (size_t i = 0; i < jsonMiShi.size(); i++)
	{
		v_amount_items_.push_back(AmountItem(jsonMiShi[i]));
	}

	for (size_t i = 0; i < jsonMiBao.size(); i++)
	{
		int cost = jsonMiBao[i]["cost"].asInt();
		if (cost == 0)
		{
			throw std::runtime_error("config_mibao_item_cost_error");
		}

		v_cost_props_.push_back(cost);

		int type =  jsonMiBao[i]["index"].asInt();

		for (size_t k = 0; k < jsonMiBao[i]["pool"].size(); ++k)
		{
			GetGoodsLib(type).push_back(GoodsItem(jsonMiBao[i]["pool"][k]));
		}
	}

}

const ConfigWorldTreasure::AmountItem& ConfigWorldTreasure::GetAmount(int stage) const
{
	if (stage < 0 || stage >= (int)v_amount_items_.size())
	{
		throw std::runtime_error("get_amount_tb_params_error");
	}

	return v_amount_items_[stage];
}

int ConfigWorldTreasure::GetCostProps(int type) const
{
	if (type < 0 || type >= (int)v_cost_props_.size())
	{
		throw std::runtime_error("unknown_type");
	}

	return v_cost_props_[type];
}

std::vector<ConfigWorldTreasure::GoodsItem>& ConfigWorldTreasure::GetGoodsLib(int type)
{
	switch (type)
	{
	case 0: return v_primary_lib_;
	case 1: return v_middle_lib_;
	case 2: return v_high_lib_;
	case 3: return v_super_lib_;
	default: throw std::runtime_error("unknow_goods_lib_type");
	}
}

const std::vector<ConfigWorldTreasure::GoodsItem>& ConfigWorldTreasure::GetGoodsLib(int type) const
{
	switch (type)
	{
	case 0: return v_primary_lib_;
	case 1: return v_middle_lib_;
	case 2: return v_high_lib_;
	case 3: return v_super_lib_;
	default: throw std::runtime_error("unknow_goods_lib_type");
	}
}

const ConfigWorldTreasure::GoodsItem& ConfigWorldTreasure::GetGoodsItem(int index, int type) const
{
	const std::vector<ConfigWorldTreasure::GoodsItem>& vItems = GetGoodsLib(type);
	if (index < 0 || index > vItems.size())
	{
		throw std::runtime_error("out_goods_lib_index");
	}
	return vItems[index];
}

int ConfigWorldTreasure::RandomItem(const std::vector<int>& vExclude, int type) const
{
	const std::vector<ConfigWorldTreasure::GoodsItem>& vItems = GetGoodsLib(type);
	if (vExclude.size() == vItems.size())
	{
		throw std::runtime_error("item_already_get_out");
	}

	std::vector<int> vProb;
	std::vector<int> vIdxs;
	unsigned nTotal = 0;
	for(size_t i = 0; i < vItems.size(); i++)
	{
		//not find
		if (vExclude.end() == std::find(vExclude.begin(), vExclude.end(), i))
		{
			nTotal += vItems[i].Prob();
			vProb.push_back(vItems[i].Prob());
			vIdxs.push_back(i);
		}
	}

	unsigned nRandom = Math::GetRandomInt(nTotal);
	for (size_t i = 0; i < vProb.size(); i ++)
	{
		if (nRandom < vProb[i])
		{
			return vIdxs[i];
		}

		nRandom -= vProb[i];
	}

	throw std::runtime_error("random_item_error");
}

/////////////////////////////////////////////////////////////////////////
int CDataXML::InitSoulFeedback()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_soulFeedback = ConfigSoulFeedback(data);
	}
	catch(const std::exception& e)
	{
		error_log("wuhunhuikui.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigSoulFeedback& CDataXML::GetConfigSoulFeedback() const
{
	return m_soulFeedback;
}


ConfigSoulFeedback::Item::Item(const Json::Value& jsonData)
{
	amount_ = jsonData["need"].asInt();
	for (Json::UInt i = 0; i < jsonData["id"].size(); i++)
	{
		int  id = jsonData["id"][i].asInt();
		v_equips_id_.push_back(id);

		if (0 == id)
		{
			throw std::runtime_error("config_soul_feedback_id_error");
		}
	}

	for(Json::UInt i = 0; i < jsonData["count"].size(); i++)
	{
		int cnt = jsonData["count"][i].asInt();
		v_equips_cnt_.push_back(cnt);

		if (cnt == 0)
		{
			throw std::runtime_error("config_soul_feedback_cnt_error");
		}
	}

	if (v_equips_id_.size() != v_equips_cnt_.size())
	{
		throw std::runtime_error("config_soul_feedback_id_and_cnt_size_error");
	}

	/*if (amount_ == 0)
	{
		throw std::runtime_error("config_soul_feedback_need_error");
	}*/
}

int ConfigSoulFeedback::Item::EquipId(int idx) const
{
	if (idx < 0 || idx > v_equips_id_.size())
	{
		throw std::runtime_error("equps_index_error");
	}

	return v_equips_id_[idx];
}

int ConfigSoulFeedback::Item::EquipCnt(int idx) const
{
	if (idx < 0 || idx > v_equips_id_.size())
	{
		throw std::runtime_error("equps_index_error");
	}

	return v_equips_cnt_[idx];
}

ConfigSoulFeedback::ConfigSoulFeedback(const Json::Value& jsonData)
{
	Json::Value jsonRewards;
	Json::GetArray(jsonData, "reward_items", jsonRewards);

	for (Json::UInt i = 0; i < jsonRewards.size(); i++)
	{
		v_rewards_.push_back(ConfigSoulFeedback::Item(jsonRewards[i]));
	}
}

const ConfigSoulFeedback::Item& ConfigSoulFeedback::GetRewards(int index) const
{
	if (index < 0 || index > v_rewards_.size())
	{
		throw std::runtime_error("get_reward_item_index_params_error");
	}

	return v_rewards_[index];
}

//////////////////////////////////////////////////////////////////////////
ConfigAwakenFeedback::ConfigAwakenFeedback(const Json::Value& jsonData)
{
	Json::Value jsonRewards;
	Json::GetArray(jsonData, "juexing_items", jsonRewards);

	for (Json::UInt i = 0; i < jsonRewards.size(); i++)
	{
		v_rewards_.push_back(ConfigAwakenFeedback::Item(jsonRewards[i]));
	}
}

int CDataXML::InitAwakenFeedback()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_awakenFeedback = ConfigAwakenFeedback(data);
	}
	catch(const std::exception& e)
	{
		error_log("wuhunhuikui.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigAwakenFeedback& CDataXML::GetConfigAwakenFeedback() const
{
	return m_awakenFeedback;
}

//////////////////////////////////////////////////////////////////////////////////
ConfigCastSoulDiscount::ConfigCastSoulDiscount(const Json::Value& jsonData)
{
	Json::Value jsonRewards;
	Json::GetArray(jsonData, "cast_soul", jsonRewards);

	for (Json::UInt i = 0; i < jsonRewards.size(); i++)
	{
		v_rewards_.push_back(ConfigSoulFeedback::Item(jsonRewards[i]));
	}
}

int CDataXML::InitCastSoulDiscount()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_castSoulDiscount = ConfigCastSoulDiscount(data);
	}
	catch(const std::exception& e)
	{
		error_log("wuhunhuikui.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigCastSoulDiscount& CDataXML::GetConfigCastSoulDiscount() const
{
	return m_castSoulDiscount;
}

///////////////////////////////////////////////////////////////////////////////////
ConfigTreasuresAllAround::ConfigTreasuresAllAround(const Json::Value& data)
	: base(data["treasure_all_around"])
{

}

int CDataXML::InitTreasuresAllAround()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_treasuresAllAround = ConfigTreasuresAllAround(data);
	}
	catch(const std::exception& e)
	{
		error_log("InitTreasuresAllAround wuhunhuikui.json error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigTreasuresAllAround& CDataXML::GetTreasureAllAround() const
{
	return m_treasuresAllAround;
}

///////////////////////////////////////////////////////////////////////////////////
int CDataXML::InitSpiritFoster()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_spiritFoster = ConfigSpiritFoster(data);
	}
	catch(const std::exception& e)
	{
		error_log("InitSpiritFoser error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigSpiritFoster& CDataXML::GetSpiritFoster() const
{
	return m_spiritFoster;
}

///////////////////////////////////////////////////////////////////////////////////
int CDataXML::InitChargeHorse()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_chargeHorse = ConfigChargeHorse(data);
	}
	catch(const std::exception& e)
	{
		error_log("InitChargeHorse error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigChargeHorse& CDataXML::GetChargeHorse() const
{
	return m_chargeHorse;
}

///////////////////////////////////////////////////////////////////////////////////
int CDataXML::InitVickyAccX()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_vicky_acc_x = ConfigVickyAccX(data);
		m_vicky_acc_x1 = ConfigVickyAccX1(data);
		m_vicky_acc_x2 = ConfigVickyAccX2(data);
		m_vicky_acc_x3 = ConfigVickyAccX3(data);
		m_vicky_acc_x4 = ConfigVickyAccX4(data);
		m_vicky_acc_x5 = ConfigVickyAccX5(data);
		m_huangzhong = Confighuangzhong(data);
		m_VickyNewOpen = ConfigVickyNewOpen(data);
//autolable5
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_yongguansanjun)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_wuyiqingdian_leiji)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_yvre618_2)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_yvre618_1)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_toushichejineng)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_chongbang_3)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_zhuanshucanjuan)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_baihuahuikui_3)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_baihuahuikui_2)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_baihuahuikui_1)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_guyv_leiji)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_chengyuantisheng_2)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_chengyuantisheng_1)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_lueduotongqian_chongbang)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_anniversary_leiji)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_anniversary_meiri)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_zhengbashadi_chongbang)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_hanjiajingxuan)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_fuzhuhesui)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_zhuniandaji)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_qingrenjie)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_yuandan2018)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_yearend2018)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_winter2018)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_double11_2018)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_hao)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_mid_aug_reu)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_taotie)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_qilin)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_water_pheonix)
INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_vicky_nnom)
		INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NO_NAME)
		INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_BINGSHU)
		INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_QIANFU)
		INIT_CHARGE_DRAW_ACT_CONFIG(CONFIG_VICKY_NNA)
	}
	catch(const std::exception& e)
	{
		error_log("InitVickyAccX error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

const ConfigVickyAccX& CDataXML::GetVickyAccX() const
{
	return m_vicky_acc_x;
}
const ConfigVickyAccX1& CDataXML::GetVickyAccX1() const
{
	return m_vicky_acc_x1;
}
const ConfigVickyAccX2& CDataXML::GetVickyAccX2() const
{
	return m_vicky_acc_x2;
}
const ConfigVickyAccX3& CDataXML::GetVickyAccX3() const
{
	return m_vicky_acc_x3;
}
const ConfigVickyAccX4& CDataXML::GetVickyAccX4() const
{
	return m_vicky_acc_x4;
}
const ConfigVickyAccX5& CDataXML::GetVickyAccX5() const
{
	return m_vicky_acc_x5;
}
const Confighuangzhong& CDataXML::Gethuangzhong() const
{
	return m_huangzhong;
}
const ConfigVickyNewOpen& CDataXML::GetVickyNewOpen() const
{
	return m_VickyNewOpen;
}
///////////////////////////////////////////////////////////////////////////////////
int CDataXML::InitGemDiscount()
{
	Json::Value data;
	int ret = readJsonConfFile("wuhunhuikui.json", data);
	if (ret != 0) return ret;
	try
	{
		m_gemDiscount = ConfigGemDiscount(data["gem_discount"]);
	}
	catch(const std::exception& e)
	{
		error_log("wuhunhuikui.json=>gem_discount error: %s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

ConfigGemDiscount::Item::Item(const Json::Value& jsonData)
{
	eq_id_ = jsonData["id"].asInt();
	eq_cnt_ = jsonData["count"].asInt();
	limit_ = jsonData["limit"].asInt();
}

ConfigGemDiscount::ConfigGemDiscount(const Json::Value& jsonData)
{
	Json::Value jsonStages;
	Json::GetArray(jsonData, "stages", jsonStages);
	for (int i = 0; i < (int)jsonStages.size(); i++)
	{
		v_stages_.push_back(jsonStages[i].asInt());
	}

	Json::Value jsonRewards;
	Json::GetArray(jsonData, "rewards", jsonRewards);
	for (int i = 0; i < (int)jsonRewards.size(); i++)
	{
		v_items_.push_back(jsonRewards[i]);
	}
}

const ConfigGemDiscount& CDataXML::GetConfigGemDiscount() const
{
	return m_gemDiscount;
}

const ConfigGemDiscount::Item& ConfigGemDiscount::GetItem(int index) const
{
	if (index < 0 || index > v_items_.size())
	{
		throw std::runtime_error("get_item_index_params_error");
	}

	return v_items_[index];
}

int ConfigGemDiscount::GetUseCnt(int point) const
{
	for (int i = v_stages_.size() - 1; i >= 0; i--)
	{
		if (point >= v_stages_[i])
		{
			return i + 1;
		}
	}

	throw std::runtime_error("cfg_stages_point_error");
}

