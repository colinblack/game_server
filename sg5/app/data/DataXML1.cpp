/*
 * DataXML1.cpp
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


/****************Hammer***************/
int CDataXML::InitHammer()
{
	DataXMLHammer *pdata = (DataXMLHammer *)m_shHammer.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	//cout <<"pdata ok" << endl;

	CAutoLock lock(&(m_shHammer), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("sgonlinehammer.xml");
	//cout << "datapath: " << dataPath << endl;
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
	while(xmlConf.FindElem("hammer"))
	{
		string type = xmlConf.GetAttrib("type");
		//cout << "tpye: " << type << endl;
		uint32_t hammer;
		if (type == "h1") {
			hammer = 1;
		} else if (type == "h2") {
			hammer = 2;
		} else if (type == "h3") {
			hammer = 3;
		} else if (type == "h4") {
			hammer = 4;
		} else {
			cout<<("hammer id wrong: ")<<type<<endl;
			return 1;
		}
		xmlConf.IntoElem();
		uint32_t pos = 0;
		while (xmlConf.FindElem("item")) {
			string id = xmlConf.GetAttrib("id");
			string rate = xmlConf.GetAttrib("rate");
			//cout << "\t id:" << id << " rate: " << rate << endl;
			if(id.empty() || rate.empty())
			{
				cout<<("hammer config wrong 1")<<id<<endl;
				return 1;
			}
			pdata->hammers[hammer-1].type = hammer;
			pdata->hammers[hammer-1].items[pos].id = CTrans::STOI(id);
			pdata->hammers[hammer-1].items[pos].rate = CTrans::STOI(rate);
			++pos;
		}
		xmlConf.OutOfElem();
	}

	while(xmlConf.FindElem("hammer_allserver"))
	{
		string type = xmlConf.GetAttrib("type");
		//cout << "tpye: " << type << endl;
		uint32_t hammer;
		if (type == "h1") {
			hammer = 1;
		} else if (type == "h2") {
			hammer = 2;
		} else if (type == "h3") {
			hammer = 3;
		} else if (type == "h4") {
			hammer = 4;
		} else {
			cout<<("hammerAllServer id wrong: ")<<type<<endl;
			return 1;
		}
		xmlConf.IntoElem();
		uint32_t pos = 0;
		while (xmlConf.FindElem("item")) {
			string id = xmlConf.GetAttrib("id");
			string rate = xmlConf.GetAttrib("rate");
			//cout << "\t id:" << id << " rate: " << rate << endl;
			if(id.empty() || rate.empty())
			{
				cout<<("hammerAllServer config wrong 1")<<id<<endl;
				return 1;
			}
			pdata->hammersAllServer[hammer-1].type = hammer;
			pdata->hammersAllServer[hammer-1].items[pos].id = CTrans::STOI(id);
			pdata->hammersAllServer[hammer-1].items[pos].rate = CTrans::STOI(rate);
			++pos;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.OutOfElem();
	m_shHammer.SetInitDone();
	return 0;
}

int CDataXML::TestHammerData(){
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shHammer)), true);
	DataXMLHammer *pdata = (DataXMLHammer *)m_shHammer.GetAddress();
	for(size_t i = 0; i < XML_HAMMER_COUNT; ++i) {
		cout << "hammer: " << CTrans::ITOS(i) << endl;
		uint32_t hammerId = pdata->hammers[i].type;
		Hammer hammer;
		for(size_t idx = 0; idx < HAMMER_ITEM_NUM; ++idx){
			uint32_t id = pdata->hammers[i].items[idx].id;
			int rate = pdata->hammers[i].items[idx].rate;
			if(id == 0) {
				break;
			}
			cout << "\t id=" << CTrans::ITOS(id) << " rate=" << CTrans::ITOS(rate) << endl;
			hammer.items.push_back(HammerItem(id, rate));
		}
		m_mapHammer[hammerId] = hammer;
	}
	return 0;
}

int CDataXML::GetHammer(map<uint32_t, Hammer> &mapHammer) {
	if(m_mapHammer.empty())
		return R_ERR_PARAM;
	mapHammer = m_mapHammer;
	return 0;
}

int CDataXML::GetHammerAllServer(map<uint32_t, Hammer> &mapHammer)
{
	if(m_mapHammerAllServer.empty())
		return R_ERR_PARAM;
	mapHammer = m_mapHammerAllServer;
	return 0;
}

/*************************************/


/**************TreasureHunt***********************/
int CDataXML::InitTreasureHunt()
{
	DataXMLTreasureHunt *pdata = (DataXMLTreasureHunt *)m_shTreasureHunt.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shTreasureHunt), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("treasurehuntconfig.xml");
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

	if(!xmlConf.FindElem("step"))
	{
		cout<<("step node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("type");
		string point = xmlConf.GetAttrib("point");
		string jade = xmlConf.GetAttrib("jade");
		string rate = xmlConf.GetAttrib("rate");
		string equip,count;
		if(xmlConf.FindChildElem("equip"))
		{
			equip = xmlConf.GetChildAttrib("id");
			count = xmlConf.GetChildAttrib("count");
		}
		if(id.empty() || type.empty())
		{
			cout<<("item config wrong 1 ")<<id<<endl;
			return 1;
		}
		unsigned id1 = CTrans::STOI(id.c_str());
		unsigned type1 = CTrans::STOI(type.c_str());
		if(id1 >= XML_TREASURE_HUNT || type1 >= TreasureHuntItemType_Max)
		{
			cout<<("item config wrong 2 ")<<id<<endl;
			return 1;
		}

		pdata->item[id1].id = CTrans::STOI(id.c_str());
		pdata->item[id1].type = CTrans::STOI(type.c_str());
		if(!point.empty())
			pdata->item[id1].point = CTrans::STOI(point.c_str());
		if(!jade.empty())
			pdata->item[id1].jade = CTrans::STOI(jade.c_str());
		if(!equip.empty())
			pdata->item[id1].equip = CTrans::STOI(equip.c_str());
		if(!count.empty())
			pdata->item[id1].count = CTrans::STOI(count.c_str());
		if(!rate.empty())
			pdata->item[id1].rate = CTrans::STOI(rate.c_str());
	}

	unsigned k = 0, j = 0, l = 0;
	map<unsigned,TreasureHuntItem> temp;
	m_mapTreasureHunt.clear();
	for(k=0;k<XML_TREASURE_HUNT;++k)
	{
		if(pdata->item[k].id)
			temp[k] = pdata->item[k];
	}
	for(map<unsigned,TreasureHuntItem>::iterator it=temp.begin();it!=temp.end();++it)
	{
		unsigned sum = 0, zero = 0, temprate = 0, sumrate = 0;
		vector<pair<unsigned,unsigned> > rate;
		map<unsigned,TreasureHuntItem>::iterator iter = it;
		for(j=0;j<XML_TREASURE_RAND;++j)
		{
			++iter;
			if(iter == temp.end())
				iter = temp.begin();
			sum += iter->second.rate;
			rate.push_back(pair<unsigned,unsigned>(iter->first, iter->second.rate));
			if(iter->second.rate == 0)
				++zero;
		}
		if(zero)
			temprate = (XML_TREASURE_RATE - sum) / zero;
		for(j=0;j<XML_TREASURE_RAND;++j)
		{
			if(rate[j].second == 0)
				rate[j].second  = temprate;
			for(l=0;l<rate[j].second;++l)
			{
				m_mapTreasureHunt[it->first][sumrate] = rate[j].first;
				++sumrate;
			}
		}
	}

	m_shTreasureHunt.SetInitDone();
	return 0;
}

int CDataXML::GetTreasureHunt(unsigned id, unsigned times, vector<TreasureHuntItem> &result)
{
	DataXMLTreasureHunt *pdata = (DataXMLTreasureHunt *)m_shTreasureHunt.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shTreasureHunt), true);

	if(!m_mapTreasureHunt.count(id))
		return R_ERR_PARAM;
	if(times > 1000)
		return R_ERR_PARAM;
	for(unsigned i=0;i<times;++i)
	{
		id = m_mapTreasureHunt[id][Math::GetRandomInt(m_mapTreasureHunt[id].rbegin()->first + 1)];
		if(!m_mapTreasureHunt.count(id) || id > XML_TREASURE_HUNT)
			return R_ERR_DATA;
		result.push_back(pdata->item[id]);
	}
	return 0;
}
/*************************************/

/***************EquipIntensifys**********************/
int CDataXML::InitEquipIntensifys()
{
	DataXMLequipintensifys *pdata = (DataXMLequipintensifys *)m_shequipintensifys.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}

	CAutoLock lock(&(m_shequipintensifys), true, LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("equipintensifys.xml");

	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("equipintensifys.xml path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("equipintensifys.xml content node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	if(!xmlConf.FindElem("equips"))
	{
		cout<<("equipintensifys.xml equips node wrong")<<endl;
		return 1;
	}

	Json::FastWriter writer;
	Json::Reader reader;
	int number = 0;

	xmlConf.IntoElem();
	while(xmlConf.FindElem("equip"))
	{
		string id = xmlConf.GetAttrib("id");
		pdata->IntensifysItem[number].id = CTrans::STOI(id.c_str());
		xmlConf.IntoElem();
		if(!xmlConf.FindElem("costs"))
		{
			cout<<("equipintensifys.xml costs node wrong")<<endl;
			return 1;
		}

		xmlConf.IntoElem();
		if(!xmlConf.FindElem("rate"))
		{
			cout<<("equipintensifys.xml rate node wrong")<<endl;
			return 1;
		}
		string basicrate = xmlConf.GetAttrib("basicrate");
		basicrate.erase(0,basicrate.find_first_not_of("["));
		basicrate.erase(basicrate.find_last_not_of("]") + 1);
		vector<string> intem_basicrates;
		String::Split(basicrate, ',', intem_basicrates);
		cout << "rate:" << endl;
		for(int i =0;i < intem_basicrates.size();i++)
		{
			pdata->IntensifysItem[number].rate[i] = CTrans::STOI(intem_basicrates[i].c_str());
			cout << pdata->IntensifysItem[number].rate[i] << ",";
		}
		cout << endl;
		xmlConf.IntoElem();
		if(!xmlConf.FindElem("addrate"))
		{
			cout<<("equipintensifys.xml addrate node wrong")<<endl;
			return 1;
		}

		xmlConf.IntoElem();
		if(!xmlConf.FindElem("data"))
		{
			cout<<("equipintensifys.xml data node wrong")<<endl;
			return 1;
		}
		string addrate = xmlConf.GetData();
		addrate.erase(0,addrate.find_first_not_of("["));
		addrate.erase(addrate.find_last_not_of("]") + 1);
		vector<string> item_addrates;
		String::Split(addrate, ',', item_addrates);
		cout << "addrate:" << endl;
		for(int i =0;i < item_addrates.size();i++)
		{
			pdata->IntensifysItem[number].addrate[i] = CTrans::STOI(item_addrates[i].c_str());
			cout << pdata->IntensifysItem[number].addrate[i] << ",";
		}
		cout << endl;
		cout << "yijian:" << endl;
		for(int i =0;i < item_addrates.size();i++)
		{
			pdata->IntensifysItem[number].yijian[i] = ceil((10000 - pdata->IntensifysItem[number].rate[i]) * 1.0 / pdata->IntensifysItem[number].addrate[i]);
			cout << pdata->IntensifysItem[number].yijian[i] << ",";

		}
		cout << endl;

		++number;
		xmlConf.OutOfElem();
		xmlConf.OutOfElem();
		xmlConf.OutOfElem();
		xmlConf.OutOfElem();
	}

	m_shequipintensifys.SetInitDone();
	return 0;
}


int CDataXML::GetEquipIntensifys(unsigned id, unsigned q_level, unsigned xingyunshi_count, Json::Value &result)
{
	DataXMLequipintensifys *pdata = (DataXMLequipintensifys *)m_shequipintensifys.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}

	CAutoLock lock(const_cast<CShareMemory *>(&(m_shequipintensifys)), true);

	result = "fail";
	for(int i=0; i<XML_EQUIPINTENSIFYS_COUNT; i++)
	{
		if(id == pdata->IntensifysItem[i].id)
		{
			if(xingyunshi_count >= pdata->IntensifysItem[i].yijian[q_level - 1])	//一键搞定
			{
				result = "success";
			}
			else
			{
				int rate_num = Math::GetRandomInt(10000);
				int max_rate = pdata->IntensifysItem[i].rate[q_level - 1] + xingyunshi_count * pdata->IntensifysItem[i].addrate[q_level - 1];
				if(rate_num < max_rate)
				{
					result = "success";
				}
				else
				{
					result = "fail";
				}
			}
			break;
		}
	}

	return 0;
}

int CDataXML::GetEquipIntensifysRate(unsigned id, unsigned q_level, unsigned xingyunshi_num, unsigned &result)
{
	DataXMLequipintensifys *pdata = (DataXMLequipintensifys *)m_shequipintensifys.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shequipintensifys)), true);

	for(int i=0; i<XML_EQUIPINTENSIFYS_COUNT; i++)
	{
		if(id == pdata->IntensifysItem[i].id)
		{
			if(xingyunshi_num * pdata->IntensifysItem[i].addrate[q_level - 1] + pdata->IntensifysItem[i].rate[q_level - 1]  >= 5000)
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			break;
		}
	}

	return 0;
}

/*************************************/



/***************Olequipset**********************/
int CDataXML::InitOlequipset()
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(&(m_sholequipset), true,LOCK_MAX);
	memset(pdata,0,sizeof(*pdata));

	Json::FastWriter writer;
	Json::Reader reader;
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("olequipset.xml");

	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("olequipset.xml path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("olequipset.xml content node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	if(!xmlConf.FindElem("builds"))
	{
		cout<<("olequipset.xml builds node wrong")<<endl;
		return 1;
	}

	int number1 = 0;
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("lv");
		string part = xmlConf.GetAttrib("part");
		string item_data = xmlConf.GetData();
		if(level.empty() || part.empty() || item_data.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->BulidOrUp[number1].level = CTrans::STOI(level.c_str());
		pdata->BulidOrUp[number1].part = CTrans::STOI(part.c_str());
		memcpy(pdata->BulidOrUp[number1].data,item_data.c_str(),sizeof(pdata->BulidOrUp[number1].data) - 1);

		++number1;
	}


	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("upgrade"))
	{
		cout<<("olequipset.xml upgrade node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("lv");
		string part = xmlConf.GetAttrib("part");
		string item_data = xmlConf.GetData();
		if(level.empty() || part.empty() || item_data.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->BulidOrUp[number1].level = CTrans::STOI(level.c_str());
		pdata->BulidOrUp[number1].part = CTrans::STOI(part.c_str());
		memcpy(pdata->BulidOrUp[number1].data,item_data.c_str(),sizeof(pdata->BulidOrUp[number1].data) - 1);
		++number1;
	}


	int wuxing = 0;
	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("xilian"))
	{
		cout<<("olequipset.xml xilian node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("level");
		string rate = xmlConf.GetAttrib("rate");
		string count = xmlConf.GetAttrib("count");
		string bs = xmlConf.GetAttrib("bs");
		if(level.empty() || rate.empty() || count.empty() || bs.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->Wuxing[wuxing].level = CTrans::STOI(level.c_str());
		pdata->Wuxing[wuxing].rate = CTrans::STOF(rate.c_str());
		pdata->Wuxing[wuxing].count = CTrans::STOI(count.c_str());
		pdata->Wuxing[wuxing].bs = CTrans::STOI(bs.c_str());
		++wuxing;
	}


	int number2 = 0;
	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("qianghua"))
	{
		cout<<("olequipset.xml qianghua node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string q_level = xmlConf.GetAttrib("qa");
		string item_data = xmlConf.GetData();
		if(q_level.empty() || item_data.empty())
		{
			cout<<("olequipset.xml q_level wrong:")<<endl;
			return 1;
		}

		Json::Value json_item;
		reader.parse(item_data,json_item);

		pdata->StoneItem[number2].q_level = CTrans::STOI(q_level.c_str());
		pdata->StoneItem[number2].q_id = json_item["material"]["equip1"]["id"].asUInt();
		pdata->StoneItem[number2].q_number = json_item["material"]["equip1"]["c"].asUInt();
		++number2;
	}


	int number3 = 0;
	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("suits"))
	{
		cout<<("olequipset.xml suits node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("lv");
		string part = xmlConf.GetAttrib("part");
		string item_data = xmlConf.GetData();
		if(level.empty() || part.empty() || item_data.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}
		pdata->Setitem[number3].level = CTrans::STOI(level.c_str());
		pdata->Setitem[number3].part = CTrans::STOI(part.c_str());

		Json::Value json_item;
		reader.parse(item_data,json_item);
		Json::Value::Members members(json_item["material"].getMemberNames());

		unsigned MaterialsNum = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			MaterialsNum += floor(json_item["material"][*it]["c"].asUInt() * 0.1);
		}

		pdata->Setitem[number3].MaterialsNum = MaterialsNum;
		++number3;
	}


	xmlConf.OutOfElem();
	if(xmlConf.FindElem("refine"))
	{
		string item_data = xmlConf.GetData();
		if(item_data.empty())
		{
			cout<<("olequipset.xml refine id wrong:")<<endl;
			return 1;
		}
		memcpy(pdata->Jinglian.data,item_data.c_str(),sizeof(pdata->Jinglian.data) - 1);
	}

	unsigned bless_num = 0;
	if(!xmlConf.FindElem("bless"))
	{
		cout<<("olequipset.xml bless node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("level");
		string exp = xmlConf.GetAttrib("exp");
		string eqid = xmlConf.GetAttrib("eqid");
		string needeq = xmlConf.GetAttrib("needeq");
		string needsoul = xmlConf.GetAttrib("needsoul");
		string per = xmlConf.GetAttrib("per");
		if(level.empty() || exp.empty() || eqid.empty() || needeq.empty() || needsoul.empty() || per.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->Bless[bless_num].level = CTrans::STOI(level.c_str());
		pdata->Bless[bless_num].exp = CTrans::STOI(exp.c_str());
		pdata->Bless[bless_num].eqid = CTrans::STOI(eqid.c_str());
		pdata->Bless[bless_num].needeqcount = CTrans::STOI(needeq.c_str());
		pdata->Bless[bless_num].bs = CTrans::STOI(needsoul.c_str());

		vector<string> item_per;
		String::Split(per, ',', item_per);
		pdata->Bless[bless_num].minrate = CTrans::STOI(item_per[0].c_str());
		pdata->Bless[bless_num].maxrate = CTrans::STOI(item_per[1].c_str());
		++bless_num;
	}
	xmlConf.OutOfElem();

	if(xmlConf.FindElem("shenzhu"))
	{
		string item_data = xmlConf.GetData();
		if(item_data.empty())
		{
			cout<<("olequipset.xml shenzhu id wrong:")<<endl;
			return 1;
		}
		memcpy(pdata->ShenZhu.data,item_data.c_str(),sizeof(pdata->ShenZhu.data) - 1);
	}

	unsigned shenwen_num = 0;
	if(!xmlConf.FindElem("shenwen"))
	{
		cout<<("olequipset.xml shenwen node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("level");
		string exp = xmlConf.GetAttrib("exp");
		string eqid = xmlConf.GetAttrib("eqid");
		string needeq = xmlConf.GetAttrib("needeq");
		string needsoul = xmlConf.GetAttrib("needsoul");
		string per = xmlConf.GetAttrib("per");
		if(level.empty() || exp.empty() || eqid.empty() || needeq.empty() || needsoul.empty() || per.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->ShenWen[shenwen_num].level = CTrans::STOI(level.c_str());
		pdata->ShenWen[shenwen_num].exp = CTrans::STOI(exp.c_str());
		pdata->ShenWen[shenwen_num].eqid = CTrans::STOI(eqid.c_str());
		pdata->ShenWen[shenwen_num].needeqcount = CTrans::STOI(needeq.c_str());
		pdata->ShenWen[shenwen_num].bs = CTrans::STOI(needsoul.c_str());

		vector<string> item_per;
		String::Split(per, ',', item_per);
		pdata->ShenWen[shenwen_num].minrate = CTrans::STOI(item_per[0].c_str());
		pdata->ShenWen[shenwen_num].maxrate = CTrans::STOI(item_per[1].c_str());
		++shenwen_num;
	}
	xmlConf.OutOfElem();
	if(xmlConf.FindElem("shenqi"))
	{
		string item_data = xmlConf.GetData();
		if(item_data.empty())
		{
			cout<<("olequipset.xml refine id wrong:")<<endl;
			return 1;
		}
		memcpy(pdata->ShenQi.data,item_data.c_str(),sizeof(pdata->ShenQi.data) - 1);
	}
	unsigned shenge_num = 0;
	if(!xmlConf.FindElem("shenge"))
	{
		cout<<("olequipset.xml shenge node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string level = xmlConf.GetAttrib("level");
		string exp = xmlConf.GetAttrib("exp");
		string eqid1 = xmlConf.GetAttrib("eqid1");
		string needeq1 = xmlConf.GetAttrib("needeq1");
		string eqid2 = xmlConf.GetAttrib("eqid2");
		string needeq2 = xmlConf.GetAttrib("needeq2");
		string eqid3 = xmlConf.GetAttrib("eqid3");
		string needeq3 = xmlConf.GetAttrib("needeq3");
		string needsoul = xmlConf.GetAttrib("needsoul");
		string per = xmlConf.GetAttrib("per");
		if(level.empty() || exp.empty() || eqid1.empty() || eqid2.empty() || eqid3.empty() ||
				needeq1.empty() || needeq2.empty() || needeq3.empty() ||needsoul.empty() || per.empty())
		{
			cout<<("olequipset.xml item id wrong:")<<endl;
			return 1;
		}

		pdata->ShenGe[shenge_num].level = CTrans::STOI(level.c_str());
		pdata->ShenGe[shenge_num].exp = CTrans::STOI(exp.c_str());
		pdata->ShenGe[shenge_num].eqid[0] = CTrans::STOI(eqid1.c_str());
		pdata->ShenGe[shenge_num].eqid[1] = CTrans::STOI(eqid2.c_str());
		pdata->ShenGe[shenge_num].eqid[2] = CTrans::STOI(eqid3.c_str());
		pdata->ShenGe[shenge_num].needeqcount[0] = CTrans::STOI(needeq1.c_str());
		pdata->ShenGe[shenge_num].needeqcount[1] = CTrans::STOI(needeq2.c_str());
		pdata->ShenGe[shenge_num].needeqcount[2] = CTrans::STOI(needeq3.c_str());
		pdata->ShenGe[shenge_num].bs = CTrans::STOI(needsoul.c_str());

		vector<string> item_per;
		String::Split(per, ',', item_per);
		pdata->ShenGe[shenge_num].minrate = CTrans::STOI(item_per[0].c_str());
		pdata->ShenGe[shenge_num].maxrate = CTrans::STOI(item_per[1].c_str());
		++shenge_num;
	}
	m_sholequipset.SetInitDone();
	return 0;
}

int CDataXML::GetBuildOrUpSetCailiao(unsigned level, unsigned part, Json::Value &data)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	Json::Reader reader;

	data["result"] = "fail";
	for(int i=0; i<XML_EQUIPSET_COUNT; ++i)
	{
		if(pdata->BulidOrUp[i].part == part && pdata->BulidOrUp[i].level == level)
		{
			Json::Value json_data;
			json_data.clear();
			string str_data = pdata->BulidOrUp[i].data;
			reader.parse(str_data, json_data);
			data["json_data"] = json_data;
			data["result"] = "success";
			break;
		}
	}

	return 0;
}

int CDataXML::GetRefineCailiao(Json::Value &data, unsigned kind)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	Json::Reader reader;
	Json::Value json_data;
	string str_data;
	string str_data2;
	if (kind == 0)
		str_data = pdata->Jinglian.data;
	else if(kind == 1)
	{
		str_data = pdata->ShenZhu.data;
		str_data2 = pdata->ShenQi.data;
	}
	else if(kind == 2)
		str_data = pdata->ShenQi.data;

	//error_log("kind: %d, str_data: %s", kind, str_data.c_str());
	//error_log("kind: %d, str_data2: %s", kind, str_data2.c_str());

	reader.parse(str_data, json_data);
	data = json_data;
	return 0;
}

int CDataXML::EquipSetWuxing(unsigned level, unsigned &count, unsigned &bs, bool &wuxingresult)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	for(int i=0; i<XML_EQUIPSET_WUXING; ++i)
	{
		if(level == pdata->Wuxing[i].level)
		{
			count = pdata->Wuxing[i].count;
			bs = pdata->Wuxing[i].bs;
			unsigned rate =  Math::GetRandomInt(WUXING_RATE_MAX);
			unsigned fail_rate = unsigned(WUXING_RATE_MAX * pdata->Wuxing[i].rate);
			if(rate < fail_rate)
			{
				wuxingresult = false;
				return 0;
			}
			else
			{
				wuxingresult = true;
				return 0;
			}

		}
	}

	return 0;
}


int CDataXML::EquipSetBless(unsigned level, unsigned exp, unsigned &eqid, unsigned &count, unsigned &bs, unsigned &n_bless_level, unsigned &n_exp)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	if(exp > pdata->Bless[level].exp)
	{
		PARAM_ERROR_RETURN_MSG("equip_bless_level_or_exp_error");
	}

	eqid = pdata->Bless[level].eqid;
	count = pdata->Bless[level].needeqcount;
	bs = pdata->Bless[level].bs;
	unsigned minrate = pdata->Bless[level].minrate;
	unsigned interval_rate = pdata->Bless[level].maxrate - minrate + 1;
	unsigned add_bless = Math::GetRandomInt(interval_rate) + minrate;

	n_exp = exp + add_bless;
	n_bless_level = level;
	if(n_exp > pdata->Bless[level].exp)
	{
		n_bless_level += 1;
	}

	return 0;
}

int CDataXML::EquipSetShenWen(unsigned level, unsigned exp, unsigned &eqid, unsigned &count, unsigned &bs, unsigned &n_bless_level, unsigned &n_exp)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	if(exp > pdata->ShenWen[level].exp)
	{
		PARAM_ERROR_RETURN_MSG("equip_bless_level_or_exp_error");
	}

	eqid = pdata->ShenWen[level].eqid;
	count = pdata->ShenWen[level].needeqcount;
	bs = pdata->ShenWen[level].bs;
	unsigned minrate = pdata->ShenWen[level].minrate;
	unsigned interval_rate = pdata->ShenWen[level].maxrate - minrate + 1;
	unsigned add_bless = Math::GetRandomInt(interval_rate) + minrate;

	n_exp = exp + add_bless;
	n_bless_level = level;
	if(n_exp > pdata->ShenWen[level].exp)
	{
		n_bless_level += 1;
	}

	return 0;
}
/*************************************/

int CDataXML::EquipSetShenGe(unsigned level, unsigned exp, unsigned eqid[3], unsigned count[3], unsigned &bs, unsigned &n_bless_level, unsigned &n_exp)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	if(exp > pdata->ShenGe[level].exp)
	{
		PARAM_ERROR_RETURN_MSG("equip_bless_level_or_exp_error");
	}

	eqid[0] = pdata->ShenGe[level].eqid[0];
	eqid[1] = pdata->ShenGe[level].eqid[1];
	eqid[2] = pdata->ShenGe[level].eqid[2];

	count[0] = pdata->ShenGe[level].needeqcount[0];
	count[1] = pdata->ShenGe[level].needeqcount[1];
	count[2] = pdata->ShenGe[level].needeqcount[2];

	bs = pdata->ShenGe[level].bs;
	unsigned minrate = pdata->ShenGe[level].minrate;
	unsigned interval_rate = pdata->ShenGe[level].maxrate - minrate + 1;
	unsigned add_bless = Math::GetRandomInt(interval_rate) + minrate;

	n_exp = exp + add_bless;
	n_bless_level = level;
	if(n_exp > pdata->ShenGe[level].exp)
	{
		n_bless_level += 1;
	}

	return 0;
}


/***************Payrank**********************/
int CDataXML::GetPayrank(unsigned uid ,unsigned lottery_number,unsigned point,vector<unsigned> &id,vector<unsigned> &count,vector<string> &type)
{
	unsigned sumrate[PAYRANK_LEVEL] = {0};

	for(int i=0; i< lottery_number; i++)
	{
		int rate_num = Math::GetRandomInt(10000);

		if(OpenPlatform::GetType() == PT_4399)
		{
			if(800 == point && (3207 == level_4_3[m_map4Payrank[2][rate_num]].id))
			{
				type.push_back("hero");
			}
			else
				type.push_back("equip");

			if(50 == point)
			{
				id.push_back(level_4_1[m_map4Payrank[0][rate_num]].id);
				count.push_back(level_4_1[m_map4Payrank[0][rate_num]].count);
			}
			else if(250 == point)
			{
				id.push_back(level_4_2[m_map4Payrank[1][rate_num]].id);
				count.push_back(level_4_2[m_map4Payrank[1][rate_num]].count);
			}
			else if(800 == point)
			{
				id.push_back(level_4_3[m_map4Payrank[2][rate_num]].id);
				count.push_back(level_4_3[m_map4Payrank[2][rate_num]].count);
			}
		}
		else
		{
			if(1000 == point && (3207 == level_3[m_mapPayrank[2][rate_num]].id))
			{
				type.push_back("hero");
			}
			else
				type.push_back("equip");

			if(100 == point)
			{
				id.push_back(level_1[m_mapPayrank[0][rate_num]].id);
				count.push_back(level_1[m_mapPayrank[0][rate_num]].count);
			}
			else if(300 == point)
			{
				id.push_back(level_2[m_mapPayrank[1][rate_num]].id);
				count.push_back(level_2[m_mapPayrank[1][rate_num]].count);
			}
			else if(1000 == point)
			{
				id.push_back(level_3[m_mapPayrank[2][rate_num]].id);
				count.push_back(level_3[m_mapPayrank[2][rate_num]].count);
			}
		}
	}

	return 0;
}

/*************************************/


/**************shop**********************/
int CDataXML::InitShop()
{
	DataXMLShop *pdata = (DataXMLShop *)m_shShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shShop), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("storeitem.xml");
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

	unsigned i = 0;
	while(xmlConf.FindElem("item"))
	{
		string id 	= xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("costType");
		string cost = xmlConf.GetAttrib("cost");
		string ch 	= xmlConf.GetAttrib("character");
		if(id.empty() || type.empty() || cost.empty())
		{
			cout<<("item config wrong 1 ")<<id<<endl;
			return 1;
		}
		pdata->shop[i].id 	 = CTrans::STOI(id.c_str());
		pdata->shop[i].type  = CTrans::STOI(type.c_str());
		pdata->shop[i].price = CTrans::STOI(cost.c_str());
		if(!ch.empty())
			pdata->shop[i].ch    = CTrans::STOI(ch.c_str());

		++i;
	}
	while(xmlConf.FindElem("vipitem"))
	{
		string id 	= xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("costType");
		string cost = xmlConf.GetAttrib("cost");
		string ch 	= xmlConf.GetAttrib("character");
		if(id.empty() || type.empty() || cost.empty())
		{
			cout<<("vipitem config wrong 1 ")<<id<<endl;
			return 1;
		}
		pdata->shop[i].id 	 = CTrans::STOI(id.c_str());
		pdata->shop[i].type  = CTrans::STOI(type.c_str());
		pdata->shop[i].vip = CTrans::STOI(cost.c_str());
		if(!ch.empty())
			pdata->shop[i].ch    = CTrans::STOI(ch.c_str());

		++i;
	}

	m_mapXMLShop.clear();
	for(unsigned j=0;j<XML_SHOP_ALL_ITEM;++j)
	{
		if(pdata->shop[j].id)
		{
			if(m_mapXMLShop.count(pdata->shop[j].id))
			{
				if(m_mapXMLShop[pdata->shop[j].id].vip)
					m_mapXMLShop[pdata->shop[j].id].price = pdata->shop[j].price;
				else if(m_mapXMLShop[pdata->shop[j].id].price)
					m_mapXMLShop[pdata->shop[j].id].vip = pdata->shop[j].vip;
			}
			else
			{
				m_mapXMLShop[pdata->shop[j].id] = pdata->shop[j];
			}
		}
		else
			break;
	}

	m_shShop.SetInitDone();
	return 0;
}
int CDataXML::GetShopItem(unsigned id, XMLShop &item)
{
	if(m_mapXMLShop.count(id))
		item = m_mapXMLShop[id];
	else
		return R_ERR_DATA;
	return 0;
}
/****************************************/

/**************worldBattleShop**********************/
int CDataXML::InitWorldBattleShop()
{
	//把商店里的所的商品放进共享内存
	DataXMLWorldBattleShop *pdata = (DataXMLWorldBattleShop *)m_shWorldBattleShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shWorldBattleShop), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty world battle")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("worldRes.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str())) //把worldRes.xml的所的信息读进CMarkupSTL类中
	{
		cout<<("worldRes.xml path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("world battle content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("shop"))
	{
		cout<<("world battle shop node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	while(xmlConf.FindElem("reward"))
	{
		string id		= xmlConf.GetAttrib("id");
		string getItem	= xmlConf.GetAttrib("gItem");
		string getCount	= xmlConf.GetAttrib("gCount");
		string type		= xmlConf.GetAttrib("type");
		string costCount= xmlConf.GetAttrib("nCount");
		string costItem	= xmlConf.GetAttrib("nItem");
		string times 	= xmlConf.GetAttrib("times");
		if(id.empty() || getItem.empty() || getCount.empty() ||
				type.empty() || costCount.empty() || costItem.empty() || times.empty())
		{
			cout<<("world battle reward config wrong")<<id<<endl;
			return 1;
		}
		pdata->shop[i].id		= CTrans::STOI(id.c_str());
		pdata->shop[i].getItem	= CTrans::STOI(getItem.c_str());
		pdata->shop[i].getCount	= CTrans::STOI(getCount.c_str());
		pdata->shop[i].type  	= CTrans::STOI(type.c_str());
		pdata->shop[i].costCount= CTrans::STOI(costCount.c_str());
		pdata->shop[i].costItem	= CTrans::STOI(costItem.c_str());
		pdata->shop[i].times	= CTrans::STOI(times.c_str());

		++i;
	}
	xmlConf.OutOfElem();
	m_mapXMLWorldBattleShop.clear();
	for(unsigned j=0;j<XML_WORLD_BATTLE_SHOP_ALL_ITEM;++j)
	{//从共享内存里拿出商品并用id用键值放入map中一一对应方便读取
		if(pdata->shop[j].id)
		{
			m_mapXMLWorldBattleShop[pdata->shop[j].id] = pdata->shop[j];
		}
		else
			break;
	}
	if(!xmlConf.FindElem("kill"))
	{
		cout<<("world battle kill node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	i = 0;
	Json::Reader reader;
	while(xmlConf.FindElem("item"))
	{
		Json::Value t;
		string id = xmlConf.GetAttrib("id");
		string kills = xmlConf.GetAttrib("recharge");
		string item_data = xmlConf.GetData();
		if(item_data.empty() || !reader.parse(item_data, t))
		{
			cout<<"worldRes.xml kill "<<id<<" wrong"<<endl;
			return 1;
		}
		memcpy(pdata->kill[i].data, item_data.c_str(), item_data.length());
		pdata->kill[i].kill = CTrans::STOI(kills);
		++i;
	}

	m_shWorldBattleShop.SetInitDone();
	return 0;
}
int CDataXML::GetWorldBattleShopItem(unsigned id, XMLWorldBattleShopItem &item, unsigned &count)
{
	if(m_mapXMLWorldBattleShop.count(id))
		item = m_mapXMLWorldBattleShop[id];
	else
		return R_ERR_DATA;

	count = m_mapXMLWorldBattleShop.size();  //商店总共有多少个商品
	return 0;
}

int CDataXML::GetWorldBattleKillRewards(Json::Value &data, const unsigned& index)
{
	DataXMLWorldBattleShop *pdata = (DataXMLWorldBattleShop *)m_shWorldBattleShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shWorldBattleShop)), true);

	Json::Reader reader;
	Json::Value json_data;
	string str_data;
	str_data = pdata->kill[index].data;
	reader.parse(str_data, json_data);
	data = json_data;
	return 0;
}
int CDataXML::GetWorldBattleKillRewards(Json::Value &data)
{
	DataXMLWorldBattleShop *pdata = (DataXMLWorldBattleShop *)m_shWorldBattleShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shWorldBattleShop)), true);

	Json::Reader reader;
	data.resize(0);
	for(int i=0;i<XML_WORLD_BATTLE_KILL_ITEM_NUM;++i)
	{
		if(pdata->kill[i].kill == 0)
			break;
		Json::Value json_data;
		string str_data(pdata->kill[i].data);
		reader.parse(str_data, json_data);
		json_data["kill"] = pdata->kill[i].kill;
		data.append(json_data);
	}
	return 0;
}
/****************************************/

/**************rankBattleShop**************************/
int CDataXML::InitRankBattleShop()
{
	DataXMLRankBattleShop *pdata = (DataXMLRankBattleShop *)m_shRankBattleShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shRankBattleShop), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty rank battle")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("rankbattle.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("rankbattle.xml path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("rank battle content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("shop"))
	{
		cout<<("rank battle shop node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	while(xmlConf.FindElem("reward"))
	{
		string id		= xmlConf.GetAttrib("id");
		string getItem	= xmlConf.GetAttrib("gItem");
		string getCount	= xmlConf.GetAttrib("gCount");
		string type		= xmlConf.GetAttrib("type");
		string costCount= xmlConf.GetAttrib("nCount");
		string costItem	= xmlConf.GetAttrib("nItem");
		string times 	= xmlConf.GetAttrib("times");
		if(id.empty() || getItem.empty() || getCount.empty() ||
				type.empty() || costCount.empty() || costItem.empty() || times.empty())
		{
			cout<<("rank battle reward config wrong")<<id<<endl;
			return 1;
		}
		pdata->shop[i].id		= CTrans::STOI(id.c_str());
		pdata->shop[i].getItem	= CTrans::STOI(getItem.c_str());
		pdata->shop[i].getCount	= CTrans::STOI(getCount.c_str());
		pdata->shop[i].type  	= CTrans::STOI(type.c_str());
		pdata->shop[i].costCount= CTrans::STOI(costCount.c_str());
		pdata->shop[i].costItem	= CTrans::STOI(costItem.c_str());
		pdata->shop[i].times	= CTrans::STOI(times.c_str());

		++i;
	}

	m_mapXMLRankBattleShop.clear();
	for(unsigned j=0;j<XML_RANK_BATTLE_SHOP_ALL_ITEM;++j)
	{
		if(pdata->shop[j].id)
		{
			m_mapXMLRankBattleShop[pdata->shop[j].id] = pdata->shop[j];
		}
		else
			break;
	}

	m_shRankBattleShop.SetInitDone();
	return 0;
}
int CDataXML::GetRankBattleShopItem(unsigned id, XMLRankBattleShopItem &item, unsigned &count)
{
	if(m_mapXMLRankBattleShop.count(id))
		item = m_mapXMLRankBattleShop[id];
	else
		return R_ERR_DATA;

	count = m_mapXMLRankBattleShop.size();
	return 0;
}
/****************************************/

/**************hufuShop**************************/
int CDataXML::InitHufuShop()
{
	DataXMLHufuShop *pdata = (DataXMLHufuShop *)m_shHufuShop.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	Json::FastWriter writer;
	Json::Reader reader;
	CAutoLock lock(&(m_shHufuShop), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty hufu")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("activityconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("activityconfig.xml path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("hufu content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("chibi"))
	{
		cout<<("hufu shop node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	while(xmlConf.FindElem("reward"))
	{
		string id		= xmlConf.GetAttrib("id");
		string tab		= xmlConf.GetAttrib("tab");
		string costCount= xmlConf.GetAttrib("cost");
		string times 	= xmlConf.GetAttrib("times");
		string reward_data 	= xmlConf.GetData();
		if(id.empty() || costCount.empty() || tab.empty() || times.empty() ||
				reward_data.empty())
		{
			cout<<("hufu reward config wrong")<<id<<endl;
			return 1;
		}
		Json::Value json_reward;
		json_reward.clear();
		reader.parse(reward_data,json_reward);
		Json::Value reward = json_reward["reward"];

		Json::Value::Members members(reward.getMemberNames());

		int index = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			Json::Value item = reward[*it];
			if (item.isObject() && item.isMember("id") && item.isMember("c"))
			{
				pdata->shop[i].getItem = item["id"].asUInt();
				pdata->shop[i].getCount = item["c"].asUInt();
			}
			else
			{
				// gold
				pdata->shop[i].getItem = 0;
				pdata->shop[i].getCount = item.asUInt();
			}
		}

		pdata->shop[i].id		= CTrans::STOI(id.c_str());
		pdata->shop[i].tab  	= CTrans::STOI(tab.c_str());
		pdata->shop[i].costCount= CTrans::STOI(costCount.c_str());
		pdata->shop[i].times	= CTrans::STOI(times.c_str());

		++i;
	}

	m_mapXMLHufuShop.clear();
	for(unsigned j=0;j<XML_HUFU_SHOP_ALL_ITEM;++j)
	{
		if(pdata->shop[j].id)
		{
			m_mapXMLHufuShop[pdata->shop[j].id] = pdata->shop[j];
		}
		else
			break;
	}

	m_shHufuShop.SetInitDone();
	return 0;
}
int CDataXML::GetHufuShopItem(unsigned id, XMLHufuShopItem &item, unsigned &count)
{
	if(m_mapXMLHufuShop.count(id))
		item = m_mapXMLHufuShop[id];
	else
		return R_ERR_DATA;

	count = m_mapXMLHufuShop.size();
	return 0;
}
/****************************************/


/*************equipment****************/
int CDataXML::InitEquipment()
{
	DataXMLEquipment *pdata = (DataXMLEquipment *)m_shEquipment.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shEquipment), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("olequipment.xml");
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

	unsigned i = 0;
	while(xmlConf.FindElem("equipment"))
	{
		string id 	= xmlConf.GetAttrib("id");
		if(id.empty())
		{
			cout<<("equipment config wrong 1 ")<<id<<endl;
			return 1;
		}
		pdata->equip[i] = CTrans::STOI(id.c_str());
		++i;
	}

	m_setXMLEquipment.clear();
	for(unsigned j=0;j<XML_EQUIPMENT_ALL_ITEM;++j)
	{
		if(pdata->equip[j])
			m_setXMLEquipment.insert(pdata->equip[j]);
		else
			break;
	}

	m_shEquipment.SetInitDone();
	return 0;
}
int CDataXML::CheckEquipment(unsigned id)
{
	if(m_setXMLEquipment.count(id))
		return 0;
	return R_ERR_DATA;
}
/****************************************/

/*************EquipDismantling*******************/
int CDataXML::GetEquipDismantling_xingyunshi(unsigned id, unsigned q_level, unsigned &xingyunshi_count)
{
	DataXMLequipintensifys *pdata = (DataXMLequipintensifys *)m_shequipintensifys.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}

	CAutoLock lock(const_cast<CShareMemory *>(&(m_shequipintensifys)), true);

	for(int i=0; i<XML_EQUIPINTENSIFYS_COUNT; i++)
	{
		if(id == pdata->IntensifysItem[i].id)
		{
			int count_all = 0;
			for(int j=0; j<q_level; j++)
			{
				int temp = floor(float(10000 - pdata->IntensifysItem[i].rate[j]) / pdata->IntensifysItem[i].addrate[j]);
				count_all += temp;
			}
			xingyunshi_count = floor(count_all * 0.3);
			break;
		}
	}

	return 0;
}

int CDataXML::GetEquipDismantling_qianghuashi(unsigned q_level, unsigned &q_id,  unsigned &q_number)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	for(int i=0; i<XML_EQUIPQIANGHUA_COUNT; ++i)
	{
		if(pdata->StoneItem[i].q_level == q_level)
		{
			q_id = pdata->StoneItem[i].q_id;
			q_number = pdata->StoneItem[i].q_number;
			return 0;
		}
	}

	return 0;
}

int CDataXML::GetEquipDismantling_taozhuang(unsigned level, unsigned part, unsigned &num)
{
	DataXMLolequipset *pdata = (DataXMLolequipset *)m_sholequipset.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_sholequipset)), true);

	for(int i=0; i<XML_EQUIPSET_COUNT; ++i)
	{
		if(pdata->Setitem[i].level == level && pdata->Setitem[i].part == part)
		{
			num = pdata->Setitem[i].MaterialsNum;
			return 0;
		}
	}
	return 0;
}

/*************************************/


/*************powerup*****************/
float CDataXML::GetRandomGradePoint(int type, int grade, int level)
{
	float point = 0;
	int n = Math::GetRandomInt(100) + 1;
	switch (type)
	{//武将星级
		//白将
		case 1:
			switch (grade)
			{//阶数
				case 0:
					//1阶
					switch (level)
					{
						//初级成长丹
						case 0:
							if (n <= 85)
								point = 0.3001f;
							else if (n > 85 && n <= 95)
								point = 0.4001f;
							else if (n > 95)
								point = 0.5001f;
							break;
						//中级成长丹
						case 1:
							if (n <= 40)
								point = 1.0001f;
							else if (n > 40 && n <= 90)
								point = 1.4001f;
							else if (n > 90)
								point = 1.8001f;
							break;
						//高级成长丹
						case 2:
							if (n <= 45)
								point = 2.8001f;
							else if (n > 45 && n <= 75)
								point = 3.2001f;
							else if (n > 75 && n <= 85)
								point = 3.6001f;
							else if (n > 85 && n <= 95)
								point = 4.0001f;
							else if (n > 95)
								point = 4.4001f;
							break;
					}
					break;
				case 1:
					//二阶
					switch (level)
					{
						case 0:
							if (n <= 85)
								point = 0.3001f;
							else if (n > 85 && n <= 95)
								point = 0.4001f;
							else if (n > 95)
								point = 0.5001f;
							break;
						case 1:
							if (n <= 50)
								point = 1.0001f;
							else if (n > 50 && n <= 80)
								point = 1.4001f;
							else if (n > 80)
								point = 1.8001f;
							break;
						case 2:
							if (n <= 40)
								point = 2.8001f;
							else if (n > 40 && n <= 80)
								point = 3.2001f;
							else if (n > 80 && n <= 90)
								point = 3.6001f;
							else if (n > 90 && n <= 95)
								point = 4.0001f;
							else if (n > 95)
								point = 4.4001f;
							break;
					}
					break;
				case 2:
					//三阶
					switch (level)
					{
						case 0:
							if (n <= 20)
								point = 0.3001f;
							else if (n > 20 && n <= 80)
								point = 0.4001f;
							else if (n > 80)
								point = 0.5001f;
							break;
						case 1:
							if (n <= 10)
								point = 1.0001f;
							else if (n > 10 && n <= 40)
								point = 1.4001f;
							else if (n > 40)
								point = 1.8001f;
							break;
						case 2:
							if (n <= 10)
								point = 2.8001f;
							else if (n > 10 && n <= 20)
								point = 3.2001f;
							else if (n > 20 && n <= 30)
								point = 3.6001f;
							else if (n > 30 && n <= 50)
								point = 4.0001f;
							else if (n > 50)
								point = 4.4001f;
							break;
					}
					break;
				case 3:
					//四阶
					switch (level)
					{
						case 0:
							if (n <= 36)
								point = 0.3001f;
							else if (n > 36 && n <= 80)
								point = 0.4001f;
							else if (n > 80)
								point = 0.5001f;
							break;
						case 1:
							if (n <= 6)
								point = 1.0001f;
							else if (n > 6 && n <= 60)
								point = 1.4001f;
							else if (n > 60)
								point = 1.8001f;
							break;
						case 2:
							if (n <= 10)
								point = 2.8001f;
							else if (n > 10 && n <= 20)
								point = 3.2001f;
							else if (n > 20 && n <= 40)
								point = 3.6001f;
							else if (n > 40 && n <= 70)
								point = 4.0001f;
							else if (n > 70)
								point = 4.4001f;
							break;
					}
					break;
				case 4:
					//五阶
					switch (level)
					{
						case 0:
							if (n <= 50)
								point = 0.1001f;
							else if (n > 50 && n <= 90)
								point = 0.2001f;
							else if (n > 90)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 45)
								point = 0.3001f;
							else if (n > 45 && n <= 85)
								point = 0.4001f;
							else if (n > 85)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 20)
								point = 1.0001f;
							else if (n > 20 && n <= 45)
								point = 1.2001f;
							else if (n > 45 && n <= 65)
								point = 1.4001f;
							else if (n > 65 && n <= 85)
								point = 1.6001f;
							else if (n > 85)
								point = 1.8001f;
							break;
					}
					break;
				case 5:
					switch (level)
					{
						case 0:
							if (n <= 62)
								point = 0.0001f;
							else if (n > 62 && n <= 98)
								point = 0.1001f;
							else if (n > 98)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 95)
								point = 0.1001f;
							else if (n > 95 && n <= 99)
								point = 0.2001f;
							else if (n > 99)
								point = 0.3001f;
							break;
						case 2:
							if (n <= 30)
								point = 0.2001f;
							else if (n > 30 && n <= 63)
								point = 0.3001f;
							else if (n > 63 && n <= 97)
								point = 0.4001f;
							else if (n > 97)
								point = 0.5001f;
							break;
					}
					break;
			}
			break;
		//绿将
		case 2:
			switch (grade)
			{
				case 0:
					switch (level)
					{
						case 0:
							if (n <= 70)
								point = 0.2001f;
							else if (n > 70 && n <= 90)
								point = 0.3001f;
							else if (n > 90)
								point = 0.4001f;
							break;
						case 1:
							if (n <= 75)
								point = 0.9001f;
							else if (n > 75 && n <= 95)
								point = 1.1001f;
							else if (n > 95)
								point = 1.3001f;
							break;
						case 2:
							if (n <= 60)
								point = 2.2001f;
							else if (n > 60 && n <= 70)
								point = 2.4001f;
							else if (n > 70 && n <= 80)
								point = 2.6001f;
							else if (n > 80 && n <= 90)
								point = 2.8001f;
							else if (n > 90)
								point = 3.0001f;
							break;
					}
					break;
				case 1:
					switch (level)
					{
						case 0:
							if (n <= 75)
								point = 0.2001f;
							else if (n > 75 && n <= 85)
								point = 0.3001f;
							else if (n > 85)
								point = 0.4001f;
							break;
						case 1:
							if (n <= 78)
								point = 0.9001f;
							else if (n > 78 && n <= 92)
								point = 1.1001f;
							else if (n > 92)
								point = 1.3001f;
							break;
						case 2:
							if (n <= 40)
								point = 2.2001f;
							else if (n > 40 && n <= 80)
								point = 2.4001f;
							else if (n > 80 && n <= 90)
								point = 2.6001f;
							else if (n > 90 && n <= 95)
								point = 2.8001f;
							else if (n > 95)
								point = 3.0001f;
							break;
					}
					break;
				case 2:
					switch (level)
					{
						case 0:
							if (n <= 20)
								point = 0.2001f;
							else if (n > 20 && n <= 80)
								point = 0.3001f;
							else if (n > 80)
								point = 0.4001f;
							break;
						case 1:
							if (n <= 10)
								point = 0.9001f;
							else if (n > 10 && n <= 40)
								point = 1.1001f;
							else if (n > 40)
								point = 1.3001f;
							break;
						case 2:
							if (n <= 10)
								point = 2.2001f;
							else if (n > 10 && n <= 20)
								point = 2.4001f;
							else if (n > 20 && n <= 30)
								point = 2.6001f;
							else if (n > 30 && n <= 40)
								point = 2.8001f;
							else if (n > 40)
								point = 3.0001f;
							break;
					}
					break;
				case 3:
					switch (level)
					{
						case 0:
							if (n <= 24)
								point = 0.2001f;
							else if (n > 24 && n <= 80)
								point = 0.3001f;
							else if (n > 80)
								point = 0.4001f;
							break;
						case 1:
							if (n <= 24)
								point = 0.9001f;
							else if (n > 24 && n <= 50)
								point = 1.1001f;
							else if (n > 50)
								point = 1.3001f;
							break;
						case 2:
							if (n <= 10)
								point = 2.2001f;
							else if (n > 10 && n <= 20)
								point = 2.4001f;
							else if (n > 20 && n <= 30)
								point = 2.6001f;
							else if (n > 30 && n <= 40)
								point = 2.8001f;
							else if (n > 40)
								point = 3.0001f;
							break;
					}
					break;
				case 4:
					switch (level)
					{
						case 0:
							if (n <= 65)
								point = 0.1001f;
							else if (n > 65 && n <= 95)
								point = 0.2001f;
							else if (n > 95)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 50)
								point = 0.3001f;
							else if (n > 50 && n <= 80)
								point = 0.4001f;
							else if (n > 80)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 10)
								point = 0.8001f;
							else if (n > 10 && n <= 30)
								point = 0.9001f;
							else if (n > 30 && n <= 50)
								point = 1.0001f;
							else if (n > 50 && n <= 70)
								point = 1.2001f;
							else if (n > 70)
								point = 1.4001f;
							break;
					}
					break;
				case 5:
					switch (level)
					{
						case 0:
							if (n <= 62)
								point = 0.0001f;
							else if (n > 62 && n <= 98)
								point = 0.1001f;
							else if (n > 98)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 95)
								point = 0.1001f;
							else if (n > 95 && n <= 99)
								point = 0.2001f;
							else if (n > 99)
								point = 0.3001f;
							break;
						case 2:
							if (n <= 30)
								point = 0.2001f;
							else if (n > 30 && n <= 63)
								point = 0.3001f;
							else if (n > 63 && n <= 97)
								point = 0.4001f;
							else if (n > 97)
								point = 0.5001f;
							break;
					}
					break;
			}
			break;
		//蓝将
		case 3:
			switch (grade)
			{
				case 0:
					switch (level)
					{
						case 0:
							if (n <= 50)
								point = 0.1001f;
							else if (n > 50 && n <= 90)
								point = 0.2001f;
							else if (n > 90)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 85)
								point = 0.6001f;
							else if (n > 85 && n <= 95)
								point = 0.8001f;
							else if (n > 95)
								point = 1.0001f;
							break;
						case 2:
							if (n <= 60)
								point = 1.4001f;
							else if (n > 60 && n <= 70)
								point = 1.6001f;
							else if (n > 70 && n <= 80)
								point = 1.8001f;
							else if (n > 80 && n <= 90)
								point = 2.0001f;
							else if (n > 90)
								point = 2.2001f;
							break;
					}
					break;
				case 1:
					switch (level)
					{
						case 0:
							if (n <= 60)
								point = 0.1001f;
							else if (n > 60 && n <= 80)
								point = 0.2001f;
							else if (n > 80)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 85)
								point = 0.6001f;
							else if (n > 85 && n <= 95)
								point = 0.8001f;
							else if (n > 95)
								point = 1.0001f;
							break;
						case 2:
							if (n <= 40)
								point = 1.4001f;
							else if (n > 40 && n <= 75)
								point = 1.6001f;
							else if (n > 75 && n <= 90)
								point = 1.8001f;
							else if (n > 90 && n <= 95)
								point = 2.0001f;
							else if (n > 95)
								point = 2.2001f;
							break;
					}
					break;
				case 2:
					switch (level)
					{
						case 0:
							if (n <= 20)
								point = 0.1001f;
							else if (n > 20 && n <= 80)
								point = 0.2001f;
							else if (n > 80)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 30)
								point = 0.6001f;
							else if (n > 30 && n <= 70)
								point = 0.8001f;
							else if (n > 70)
								point = 1.0001f;
							break;
						case 2:
							if (n <= 10)
								point = 1.4001f;
							else if (n > 10 && n <= 20)
								point = 1.6001f;
							else if (n > 20 && n <= 30)
								point = 1.8001f;
							else if (n > 30 && n <= 40)
								point = 2.0001f;
							else if (n > 40)
								point = 2.2001f;
							break;
					}
					break;
				case 3:
					switch (level)
					{
						case 0:
							if (n <= 22)
								point = 0.1001f;
							else if (n > 22 && n <= 78)
								point = 0.2001f;
							else if (n > 78)
								point = 0.3001f;
							break;
						case 1:
							if (n <= 36)
								point = 0.6001f;
							else if (n > 36 && n <= 80)
								point = 0.8001f;
							else if (n > 80)
								point = 1.0001f;
							break;
						case 2:
							if (n <= 10)
								point = 1.4001f;
							else if (n > 10 && n <= 30)
								point = 1.6001f;
							else if (n > 30 && n <= 40)
								point = 1.8001f;
							else if (n > 40 && n <= 60)
								point = 2.0001f;
							else if (n > 60)
								point = 2.2001f;
							break;
					}
					break;
				case 4:
					switch (level)
					{
						case 0:
							if (n <= 40)
								point = 0.0001f;
							else if (n > 40 && n <= 80)
								point = 0.1001f;
							else if (n > 80)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 60)
								point = 0.2001f;
							else if (n > 60 && n <= 95)
								point = 0.3001f;
							else if (n > 95)
								point = 0.4001f;
							break;
						case 2:
							if (n <= 5)
								point = 0.5001f;
							else if (n > 5 && n <= 15)
								point = 0.6001f;
							else if (n > 15 && n <= 45)
								point = 0.7001f;
							else if (n > 45 && n <= 80)
								point = 0.8001f;
							else if (n > 80)
								point = 0.9001f;
							break;
					}
					break;
				case 5:
					switch (level)
					{
						case 0:
							if (n <= 62)
								point = 0.0001f;
							else if (n > 62 && n <= 98)
								point = 0.1001f;
							else if (n > 98)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 95)
								point = 0.1001f;
							else if (n > 95 && n <= 99)
								point = 0.2001f;
							else if (n > 99)
								point = 0.3001f;
							break;
						case 2:
							if (n <= 30)
								point = 0.2001f;
							else if (n > 30 && n <= 63)
								point = 0.3001f;
							else if (n > 63 && n <= 97)
								point = 0.4001f;
							else if (n > 97)
								point = 0.5001f;
							break;
					}
					break;
			}
			break;
		//紫将
		case 4:
		case 5:
		case 6:
			switch (grade)
			{
				case 0:
					switch (level)
					{
						case 0:
							if (n <= 30)
								point = 0.0001f;
							else if (n > 30 && n <= 90)
								point = 0.1001f;
							else if (n > 90)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 85)
								point = 0.3001f;
							else if (n > 85 && n <= 95)
								point = 0.4001f;
							else if (n > 95)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 60)
								point = 0.7001f;
							else if (n > 60 && n <= 70)
								point = 0.8001f;
							else if (n > 70 && n <= 80)
								point = 0.9001f;
							else if (n > 80 && n <= 90)
								point = 1.0001f;
							else if (n > 90)
								point = 1.2001f;
							break;
					}
					break;
				case 1:
					switch (level)
					{
						case 0:
							if (n <= 40)
								point = 0.0001f;
							else if (n > 40 && n <= 80)
								point = 0.1001f;
							else if (n > 80)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 88)
								point = 0.3001f;
							else if (n > 88 && n <= 92)
								point = 0.4001f;
							else if (n > 92)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 40)
								point = 0.7001f;
							else if (n > 40 && n <= 80)
								point = 0.8001f;
							else if (n > 80 && n <= 90)
								point = 0.9001f;
							else if (n > 90 && n <= 95)
								point = 1.0001f;
							else if (n > 95)
								point = 1.2001f;
							break;
					}
					break;
				case 2:
					switch (level)
					{
						case 0:
							if (n <= 20)
								point = 0.0001f;
							else if (n > 20 && n <= 80)
								point = 0.1001f;
							else if (n > 80)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 30)
								point = 0.3001f;
							else if (n > 30 && n <= 70)
								point = 0.4001f;
							else if (n > 70)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 10)
								point = 0.7001f;
							else if (n > 10 && n <= 20)
								point = 0.8001f;
							else if (n > 20 && n <= 30)
								point = 0.9001f;
							else if (n > 30 && n <= 70)
								point = 1.0001f;
							else if (n > 70)
								point = 1.2001f;
							break;
					}
					break;
				case 3:
					switch (level)
					{
						case 0:
							if (n <= 24)
								point = 0.0001f;
							else if (n > 24 && n <= 80)
								point = 0.1001f;
							else if (n > 80)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 36)
								point = 0.3001f;
							else if (n > 36 && n <= 80)
								point = 0.4001f;
							else if (n > 80)
								point = 0.5001f;
							break;
						case 2:
							if (n <= 10)
								point = 0.7001f;
							else if (n > 10 && n <= 30)
								point = 0.8001f;
							else if (n > 30 && n <= 60)
								point = 0.9001f;
							else if (n > 60 && n <= 70)
								point = 1.0001f;
							else if (n > 70)
								point = 1.2001f;
							break;
					}
					break;
				case 4:
					switch (level)
					{
						case 0:
							if (n <= 65)
								point = 0.0001f;
							else if (n > 65 && n <= 98)
								point = 0.1001f;
							else if (n > 98)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 85)
								point = 0.1001f;
							else if (n > 85 && n <= 98)
								point = 0.2001f;
							else if (n > 98)
								point = 0.3001f;
							break;
						case 2:
							if (n <= 40)
								point = 0.3001f;
							else if (n > 40 && n <= 75)
								point = 0.4001f;
							else if (n > 75 && n <= 95)
								point = 0.5001f;
							else if (n > 95)
								point = 0.6001f;
							break;
					}
					break;
				case 5:
					switch (level)
					{
						case 0:
							if (n <= 62)
								point = 0.0001f;
							else if (n > 62 && n <= 98)
								point = 0.1001f;
							else if (n > 98)
								point = 0.2001f;
							break;
						case 1:
							if (n <= 95)
								point = 0.1001f;
							else if (n > 95 && n <= 99)
								point = 0.2001f;
							else if (n > 99)
								point = 0.3001f;
							break;
						case 2:
							if (n <= 30)
								point = 0.2001f;
							else if (n > 30 && n <= 63)
								point = 0.3001f;
							else if (n > 63 && n <= 97)
								point = 0.4001f;
							else if (n > 97)
								point = 0.5001f;
							break;
					}
					break;
			}
			break;
	}

	return point;
}
float CDataXML::GetMaxGradePoint(int grade, float point)
{
	switch(grade)
	{
	case 0:
		return point * 1.2f;
	case 1:
		return point * 1.4f;
	case 2:
		return point * 1.7f;
	case 3:
		return point * 2.0f;
	case 4:
		return point * 2.3f;
	case 5:
		return point * 2.7f;
	}
	return 0.0001f;
}

int CDataXML::GetGradeLevel(unsigned id, int &grade, int &level)
{
	switch(id)
	{
	case 40121:
		grade = 0;
		level = 0;
		return 0;
	case 40122:
		grade = 0;
		level = 1;
		return 0;
	case 40123:
		grade = 0;
		level = 2;
		return 0;
	case 40131:
		grade = 1;
		level = 0;
		return 0;
	case 40132:
		grade = 1;
		level = 1;
		return 0;
	case 40133:
		grade = 1;
		level = 2;
		return 0;
	case 40141:
		grade = 2;
		level = 0;
		return 0;
	case 40142:
		grade = 2;
		level = 1;
		return 0;
	case 40143:
		grade = 2;
		level = 2;
		return 0;
	case 40151:
		grade = 3;
		level = 0;
		return 0;
	case 40152:
		grade = 3;
		level = 1;
		return 0;
	case 40153:
		grade = 3;
		level = 2;
		return 0;
	case 40161:
		grade = 4;
		level = 0;
		return 0;
	case 40162:
		grade = 4;
		level = 1;
		return 0;
	case 40163:
		grade = 4;
		level = 2;
		return 0;
	case 40171:
		grade = 5;
		level = 0;
		return 0;
	case 40172:
		grade = 5;
		level = 1;
		return 0;
	case 40173:
		grade = 5;
		level = 2;
		return 0;
	}

	return R_ERR_PARAM;
}

int CDataXML::GetHeroStepNeedHeroLevel(const int grade, int & level)
{
	switch(grade)
	{
	case 0:
		level = 1;
		return R_SUCCESS;
	case 1:
		level = 30;
		return R_SUCCESS;
	case 2:
		level = 60;
		return R_SUCCESS;
	case 3:
		level = 80;
		return R_SUCCESS;
	case 4:
		level = 100;
		return R_SUCCESS;
	case 5:
		level = 120;
		return R_SUCCESS;
	}

	return R_ERR_PARAM;
}

int CDataXML::GetHeroStepNeedBuildingLevel(const int grade, int & level)
{
	switch(grade)
	{
	case 0:
		level = 1;
		return R_SUCCESS;
	case 1:
		level = 5;
		return R_SUCCESS;
	case 2:
		level = 10;
		return R_SUCCESS;
	case 3:
		level = 20;
		return R_SUCCESS;
	case 4:
		level = 80;
		return R_SUCCESS;
	case 5:
		level = 90;
		return R_SUCCESS;
	}

	return R_ERR_PARAM;
}

int CDataXML::GetHeroStepNeedGoldCost(const int grade, int & coins)
{
	switch(grade)
	{
	case 0:
		coins = 1;
		return R_SUCCESS;
	case 1:
		coins = 10;
		return R_SUCCESS;
	case 2:
		coins = 20;
		return R_SUCCESS;
	case 3:
		coins = 30;
		return R_SUCCESS;
	case 4:
		coins = 50;
		return R_SUCCESS;
	case 5:
		coins = 80;
		return R_SUCCESS;
	}

	return R_ERR_PARAM;
}

int CDataXML::GetHeroStepNeedBSCost(const int grade, int & bs)
{
	switch(grade)
	{
	case 0:
		bs = 1;
		return R_SUCCESS;
	case 1:
		bs = 1000;
		return R_SUCCESS;
	case 2:
		bs = 2000;
		return R_SUCCESS;
	case 3:
		bs = 3000;
		return R_SUCCESS;
	case 4:
		bs = 50000;
		return R_SUCCESS;
	case 5:
		bs = 100000;
		return R_SUCCESS;
	}

	return R_ERR_PARAM;
}
/****************************************/


/*************newlottery_start****************/
int CDataXML::InitNewLottery()
{
	DataXMLnewlottery *pdata = (DataXMLnewlottery *)m_shnewlottery.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shnewlottery), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("newturntablelottery.xml");
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

	for(int i=0; i<XML_PARTITION_NUM; ++i)
	{
		if(xmlConf.FindElem("turntable"))
		{
			string start = xmlConf.GetAttrib("start");
			string end = xmlConf.GetAttrib("end");
			if(start.empty() || end.empty())
			{
				cout<<("turntable item id wrong")<<endl;
				return 1;
			}
			pdata->part_zone[i].start_id = CTrans::STOI(start.c_str());
			pdata->part_zone[i].end_id = CTrans::STOI(end.c_str());
		}
		xmlConf.IntoElem();

		if(xmlConf.FindElem("firstlayer"))
		{
			string gold = xmlConf.GetAttrib("gold");
			pdata->part_zone[i].first_cash = CTrans::STOI(gold.c_str());
		}
		xmlConf.IntoElem();
		unsigned first_rate = 0;
		unsigned first = 0;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string type_id = xmlConf.GetAttrib("typeid");
			string rate = xmlConf.GetAttrib("rate");
			string eqid = xmlConf.GetAttrib("eqid");
			string num = xmlConf.GetAttrib("num");
			if(id.empty() || type_id.empty() || rate.empty() || eqid.empty() || num.empty())
			{
				cout<<("firstlayer item id wrong")<<endl;
				return 1;
			}
			pdata->part_zone[i].FirstLayer[first].id = CTrans::STOI(id.c_str());
			pdata->part_zone[i].FirstLayer[first].type_id = CTrans::STOI(type_id.c_str());
			pdata->part_zone[i].FirstLayer[first].rate = CTrans::STOI(rate.c_str());
			pdata->part_zone[i].FirstLayer[first].prize_id = CTrans::STOI(eqid.c_str());
			pdata->part_zone[i].FirstLayer[first].prize_num = CTrans::STOI(num.c_str());

			for(unsigned j=0; j<pdata->part_zone[i].FirstLayer[first].rate; ++j)
			{
				m_mapXMLfirstlottery[i][first_rate] = pdata->part_zone[i].FirstLayer[first].id;
				++first_rate;
			}
			++first;
		}


		xmlConf.OutOfElem();
		if(xmlConf.FindElem("secondlayer"))
		{
			string gold = xmlConf.GetAttrib("gold");
			pdata->part_zone[i].second_cash = CTrans::STOI(gold.c_str());
		}
		xmlConf.IntoElem();
		unsigned second_rate = 0;
		unsigned second = 0;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string type_id = xmlConf.GetAttrib("typeid");
			string rate = xmlConf.GetAttrib("rate");
			string eqid = xmlConf.GetAttrib("eqid");
			string num = xmlConf.GetAttrib("num");
			string total = xmlConf.GetAttrib("total");
			if(id.empty() || type_id.empty() || rate.empty() || eqid.empty() || num.empty() || total.empty())
			{
				cout<<("secondlayer item id wrong")<<endl;
				return 1;
			}
			pdata->part_zone[i].SecondLayer[second].id = CTrans::STOI(id.c_str());
			pdata->part_zone[i].SecondLayer[second].type_id = CTrans::STOI(type_id.c_str());
			pdata->part_zone[i].SecondLayer[second].rate = CTrans::STOI(rate.c_str());
			pdata->part_zone[i].SecondLayer[second].prize_id = CTrans::STOI(eqid.c_str());
			pdata->part_zone[i].SecondLayer[second].prize_num = CTrans::STOI(num.c_str());
			pdata->part_zone[i].SecondLayer[second].total = CTrans::STOI(total.c_str());

			for(unsigned j=0; j<pdata->part_zone[i].SecondLayer[second].rate; ++j)
			{
				m_mapXMLsecondlottery[i][second_rate] = pdata->part_zone[i].SecondLayer[second].id;
				++second_rate;
			}
			++second;
		}

		xmlConf.OutOfElem();
		if(xmlConf.FindElem("openfloor"))
		{
			string openfloor = xmlConf.GetData();
			pdata->part_zone[i].openfloor = CTrans::STOI(openfloor.c_str());
		}
		xmlConf.OutOfElem();
	}

	m_shnewlottery.SetInitDone();
	return 0;
}

int CDataXML::GetNewLottery(unsigned uid, unsigned level, vector <unsigned> &id, vector <unsigned> &type_id, vector <unsigned> &rate, vector <unsigned> &eqid, vector <unsigned> &num, vector <unsigned> &total, unsigned &openfloor, unsigned &cash)
{
	DataXMLnewlottery *pdata = (DataXMLnewlottery *)m_shnewlottery.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shnewlottery)), true);

	unsigned zone_id =Config::GetZoneByUID(uid);
	if (OpenPlatform::IsLYPlatform())
	{
		zone_id = 1000;
	}

	unsigned interval = 0;
	for(int i=0; i <XML_PARTITION_NUM; ++i)
	{
		if(zone_id>=pdata->part_zone[i].start_id && zone_id<=pdata->part_zone[i].end_id)
		{
			interval = i;
			break;
		}
	}

	openfloor = pdata->part_zone[interval].openfloor;
	if(level == 1)
	{
		cash = pdata->part_zone[interval].first_cash;
		for(int j=0; j<XML_FIRST_LAYER_NUM; ++j)
		{
			id.push_back(pdata->part_zone[interval].FirstLayer[j].id);
			type_id.push_back(pdata->part_zone[interval].FirstLayer[j].type_id);
			rate.push_back(pdata->part_zone[interval].FirstLayer[j].rate);
			eqid.push_back(pdata->part_zone[interval].FirstLayer[j].prize_id);
			num.push_back(pdata->part_zone[interval].FirstLayer[j].prize_num);
		}
	}
	else if(level == 2)
	{
		cash = pdata->part_zone[interval].second_cash;
		for(int j=0; j<XML_SECOND_LAYER_NUM; ++j)
		{
			id.push_back(pdata->part_zone[interval].SecondLayer[j].id);
			type_id.push_back(pdata->part_zone[interval].SecondLayer[j].type_id);
			rate.push_back(pdata->part_zone[interval].SecondLayer[j].rate);
			eqid.push_back(pdata->part_zone[interval].SecondLayer[j].prize_id);
			num.push_back(pdata->part_zone[interval].SecondLayer[j].prize_num);
			total.push_back(pdata->part_zone[interval].SecondLayer[j].total);
		}
	}


	return 0;
}
/*************newlottery_end****************/

/*************juexue*****************/
int CDataXML::GetJuexue(unsigned npc, bool zhaohuan, unsigned level, unsigned &cost, unsigned &id, unsigned &next)
{
	if(npc >= XML_JUEXUE_NPC_NUM)
		return R_ERR_PARAM;

	cost = juexue_cost[npc];

	if(npc == XML_JUEXUE_NPC_NUM - 1)
		next = 0;
	else if(npc == XML_JUEXUE_NPC_NUM - 2 && zhaohuan)
		next = XML_JUEXUE_NPC_NUM - 1;
	else if(Math::GetRandomInt(juexue_chance[XML_JUEXUE_NPC_NUM - 1]) < juexue_chance[npc])
		next = npc + 1;
	else
		next = 0;

	unsigned fall = (npc == (XML_JUEXUE_NPC_NUM - 1) && zhaohuan) ? XML_JUEXUE_NPC_NUM : npc;
	unsigned type = m_mapXMLJuexueFall[fall][Math::GetRandomInt(m_mapXMLJuexueFall[fall].rbegin()->first + 1)];

	if(type == e_juexue_type_rubbish)
	{
		id = XML_JUEXUE_RUBBISH_ID;
		return 0;
	}
	else if(type == e_juexue_type_exp)
	{
		id = XML_JUEXUE_EXP_ID;
		return 0;
	}

	unsigned level_r = XML_JUEXUE_LEVEL_NUM - 1;
	for(unsigned i=0;i<XML_JUEXUE_LEVEL_NUM;++i)
	{
		if(level < juexue_level[i])
		{
			level_r = i;
			break;
		}
	}

	unsigned juexue = m_mapXMLJuexueType[level_r][type][Math::GetRandomInt(m_mapXMLJuexueType[level_r][type].rbegin()->first + 1)];
	id = juexue_id[type][juexue];

	return 0;
}
/****************************************/


/*************choujiang_start****************/
int CDataXML::InitChoujiang()
{
	DataXMLchoujiang *pdata = (DataXMLchoujiang *)m_shchoujiang.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shchoujiang), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("choujiangconfig.xml");
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

	if(xmlConf.FindElem("rate"))
	{
		string basicrate = xmlConf.GetData();
		basicrate.erase(0,basicrate.find_first_not_of("["));
		basicrate.erase(basicrate.find_last_not_of("]") + 1);
		vector<string> intem_basicrates;
		String::Split(basicrate, ',', intem_basicrates);
		for(int i =0;i < intem_basicrates.size();i++)
		{
			pdata->rate1[i] = CTrans::STOI(intem_basicrates[i].c_str());
		}
	}

	if(xmlConf.FindElem("rate"))
	{
		string basicrate = xmlConf.GetData();
		basicrate.erase(0,basicrate.find_first_not_of("["));
		basicrate.erase(basicrate.find_last_not_of("]") + 1);
		vector<string> intem_basicrates;
		String::Split(basicrate, ',', intem_basicrates);
		for(int i =0;i < intem_basicrates.size();i++)
		{
			pdata->rate2[i] = CTrans::STOI(intem_basicrates[i].c_str());
		}
	}

	unsigned index_num = 0;
	while(xmlConf.FindElem("item"))
	{
		string index = xmlConf.GetAttrib("index");
		string type_id = xmlConf.GetAttrib("typeid");
		string id = xmlConf.GetAttrib("id");
		string num;
		xmlConf.IntoElem();
		if(xmlConf.FindElem("num"))
		{
			num = xmlConf.GetData();
		}
		xmlConf.OutOfElem();
		if(id.empty() || type_id.empty() || index.empty() || num.empty())
		{
			cout<<("firstlayer item id wrong")<<endl;
			return 1;
		}

		if(CTrans::STOI(type_id.c_str()) == 2)
		{
			id = id.erase(0,1);
		}

		pdata->goods[index_num].id = CTrans::STOI(id.c_str());
		pdata->goods[index_num].type_id = CTrans::STOI(type_id.c_str());
		pdata->goods[index_num].index = CTrans::STOI(index.c_str());
		pdata->goods[index_num].num = CTrans::STOI(num.c_str());

		++index_num;
	}


	unsigned rate = 0;
	m_mapFloor_1.clear();
	for(int i=0; i<XML_CHOUJIANG_RATE_FIRST; ++i)
	{
		for(int j=0; j<pdata->rate1[i]; ++j)
		{
			m_mapFloor_1[rate] = pdata->goods[i].index;
			++rate;
		}
	}

	rate = 0;
	m_mapFloor_2.clear();
	for(int i=0; i<XML_CHOUJIANG_RATE_SECOND; ++i)
	{
		for(int j=0; j<pdata->rate2[i]; ++j)
		{
			m_mapFloor_2[rate] = pdata->goods[i].index;
			++rate;
		}
	}

	m_shchoujiang.SetInitDone();
	return 0;
}

int CDataXML::GetChoujiangWupin(unsigned uid, unsigned floors, unsigned count, vector <unsigned> &awards_index_id, vector <unsigned> &awards_type_id,
		vector <unsigned> &awards_eqid, vector <unsigned> &awards_num, vector <unsigned> &limit_items)
{
	DataXMLchoujiang *pdata = (DataXMLchoujiang *)m_shchoujiang.GetAddress();
	if(pdata == NULL)
	{
		return R_ERROR;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shchoujiang)), true);

	for(int i=0; i<count; ++i)
	{
		if(floors == 1)
		{
			unsigned rate_num = Math::GetRandomInt(m_mapFloor_1.rbegin()->first + 1);
			awards_index_id.push_back(pdata->goods[m_mapFloor_1[rate_num]].index);
			awards_type_id.push_back(pdata->goods[m_mapFloor_1[rate_num]].type_id);
			awards_eqid.push_back(pdata->goods[m_mapFloor_1[rate_num]].id);
			awards_num.push_back(pdata->goods[m_mapFloor_1[rate_num]].num);
		}
		else if(floors == 2)
		{
			unsigned rate_num = Math::GetRandomInt(m_mapFloor_2.rbegin()->first + 1);
			unsigned item_index = m_mapFloor_2[rate_num];
			if(m_mapFloor_2[rate_num] == 10 )
			{
				limit_items[0] += 1;
				if(limit_items[0] > 5)
				{
					limit_items[0] = 5;
					item_index += 1;
				}
			}
			else if(m_mapFloor_2[rate_num] == 13 )
			{
				limit_items[1] += 1;
				if(limit_items[1] > 5)
				{
					limit_items[1] = 5;
					item_index += 1;
				}
			}
			else if(m_mapFloor_2[rate_num] == 17 )
			{
				limit_items[2] += 1;
				if(limit_items[2] > 5)
				{
					limit_items[2] = 5;
					item_index += 1;
				}
			}
			else if(m_mapFloor_2[rate_num] == 20 )
			{
				limit_items[3] += 1;
				if(limit_items[3] > 5)
				{
					limit_items[3] = 5;
					item_index += 1;
				}
			}
			awards_index_id.push_back(pdata->goods[item_index].index);
			awards_type_id.push_back(pdata->goods[item_index].type_id);
			awards_eqid.push_back(pdata->goods[item_index].id);
			awards_num.push_back(pdata->goods[item_index].num);
		}
	}

	return 0;
}

/*************choujiang_end****************/

/*************jiangling_start****************/
int CDataXML::GetJianglingGrow(unsigned uid, unsigned &grow_value, unsigned &dan_growth, unsigned &prosper)
{
	unsigned rate = Math::GetRandomInt(10000);
	if(grow_value < chengzhang[1][0])
	{
		grow_value += m_mapjiangling_rate1[rate];
		dan_growth = chengzhang[0][2];
		prosper = chengzhang[0][3];
//		prosper = m_mapjiangling_rate1[rate];    //概率测试用
	}
	else if(grow_value >= chengzhang[1][0] && grow_value < chengzhang[2][0])
	{
		grow_value += m_mapjiangling_rate2[rate];
		dan_growth = chengzhang[1][2];
		prosper = chengzhang[1][3];
//		prosper = m_mapjiangling_rate2[rate];
	}
	else if(grow_value >= chengzhang[2][0])
	{
		grow_value += m_mapjiangling_rate3[rate];
		dan_growth = chengzhang[2][2];
		prosper = chengzhang[2][3];
//		prosper = m_mapjiangling_rate3[rate];
	}

	if(grow_value > chengzhang[3][0])
	{
		grow_value = chengzhang[3][0];
	}
	return 0;
}
/*************jiangling_end****************/

/*************quest reward****************/
int CDataXML::InitActivityConfig()
{
	XML_ACTIVITY_CONFIG mapXMLActivityRewad;

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	string faile_name = "activityconfig.xml";
	dataPath.append(faile_name);
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
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("blunt"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("reward"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["blunt"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("tutorLoginGate"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("reward"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["tutorLoginGate"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("tutorLogin"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("reward"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["tutorLogin"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("fchargeReward"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("fcharge"))
		{
			string id = xmlConf.GetAttrib("zoneArr");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["fchargeReward"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("tutorLoginLevel"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("reward"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["tutorLoginLevel"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("hongbao"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["hongbao"][id] = context;
		}
		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	if(xmlConf.FindElem("jifenduihuan"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			mapXMLActivityRewad["jifenduihuan"][id] = context;
		}
		xmlConf.OutOfElem();
	}

	DataXMLActReward *pdata = (DataXMLActReward *)m_shActReward.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shActReward), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	unsigned i = 0;
	for(XML_ACTIVITY_CONFIG::iterator it=mapXMLActivityRewad.begin();it!=mapXMLActivityRewad.end();++it)
	{
		for(map<string,string>::iterator it1=it->second.begin();it1!=it->second.end();++it1)
		{
			strcpy(pdata->reward[i].act,it->first.c_str());
			strcpy(pdata->reward[i].id,it1->first.c_str());
			strcpy(pdata->reward[i].reward,it1->second.c_str());
			++i;
		}
	}

	for(unsigned i=0;i<ACT_REWARD_NUM;++i)
	{
		string temp(pdata->reward[i].act);
		if(m_mapXMLActivityRewad.count(temp))
			continue;

		m_mapXMLActivityRewad[temp] = i;
	}

	m_shActReward.SetInitDone();

	return 0;
}
int CDataXML::InitOlGateConfig()
{
	XML_OLGATE_CONFIG mapXMLOlGate;

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	string faile_name = "olgateconfig.xml";
	dataPath.append(faile_name);
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
	if(!xmlConf.FindElem("gates"))
	{
		cout<<("gates node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("gate"))
	{
		int level = CTrans::STOI(xmlConf.GetAttrib("level"));
		string reward;
		string freward;
		xmlConf.IntoElem();
		if (xmlConf.FindElem("reward"))
			reward = xmlConf.GetData();
		else
			reward.clear();
		mapXMLOlGate[level]["reward"] = reward;
		if (xmlConf.FindElem("freward"))
			freward = xmlConf.GetData();
		else
			freward.clear();
		mapXMLOlGate[level]["freward"] = freward;
		while(xmlConf.FindElem("item"))
		{
			string id = xmlConf.GetAttrib("id");
			if (id.empty())
			{
				continue;
			}
			string character = xmlConf.GetAttrib("character");
			if (character.empty())
			{
				character = "0";
			}
			string quality = xmlConf.GetAttrib("quality");
			if (quality.empty())
			{
				quality = "0";
			}
			string item_id = id+"_"+character;
			string eqdata = "{\"id\":" + id + ",\"c\":" + character + ",\"q\":" + quality + "}";
			mapXMLOlGate[level][item_id] = eqdata;
		}
		xmlConf.OutOfElem();
	}

	DataXMLGateReward *pdata = (DataXMLGateReward *)m_shGateReward.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shGateReward), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	unsigned i = 0;
	for(XML_OLGATE_CONFIG::iterator it=mapXMLOlGate.begin();it!=mapXMLOlGate.end();++it)
	{
		for(map<string,string>::iterator it1=it->second.begin();it1!=it->second.end();++it1)
		{
			pdata->reward[i].level = it->first;
			strcpy(pdata->reward[i].id,it1->first.c_str());
			strcpy(pdata->reward[i].reward,it1->second.c_str());
			++i;
		}
	}

	for(unsigned i=0;i<GATE_REWARD_NUM;++i)
	{
		if(m_mapXMLOlGate.count(pdata->reward[i].level))
			continue;

		m_mapXMLOlGate[pdata->reward[i].level] = i;
	}

	m_shGateReward.SetInitDone();

	return 0;
}
int CDataXML::InitQuestConfig()
{
	XML_QUEST_CONFIG mapXMLQuest;

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	string faile_name = "questconfig.xml";
	dataPath.append(faile_name);
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
	if(xmlConf.FindElem("quests"))
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("quest"))
		{
			string id = xmlConf.GetAttrib("id");
			string context = xmlConf.GetData();
			Json::Value reward;
			Json::FromString(reward,context);
			if (reward.isMember("reward")){
				mapXMLQuest[id] = Json::ToString(reward["reward"]);
			}
		}
		xmlConf.OutOfElem();
	}

	DataXMLQuestReward *pdata = (DataXMLQuestReward *)m_shQuestReward.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shQuestReward), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	unsigned i = 0;
	for(XML_QUEST_CONFIG::iterator it=mapXMLQuest.begin();it!=mapXMLQuest.end();++it)
	{
		strcpy(pdata->reward[i].id,it->first.c_str());
		strcpy(pdata->reward[i].reward,it->second.c_str());
		++i;
	}

	for(unsigned i=0;i<QUEST_REWARD_NUM;++i)
	{
		string temp(pdata->reward[i].id);
		m_mapXMLQuest[temp] = i;
	}

	m_shQuestReward.SetInitDone();

	return 0;
}

int CDataXML::GetActivityConfig(const string &name, map<string, string> &config)
{
	if (m_mapXMLActivityRewad.count(name))
	{
		DataXMLActReward *pdata = (DataXMLActReward *)m_shActReward.GetAddress();
		if(pdata == NULL)
		{
			return R_ERROR;
		}
		CAutoLock lock(const_cast<CShareMemory *>(&(m_shActReward)), true);

		for(unsigned i=m_mapXMLActivityRewad[name];i<ACT_REWARD_NUM;++i)
		{
			string temp(pdata->reward[i].act);
			if(temp != name)
				break;

			config[string(pdata->reward[i].id)] = string(pdata->reward[i].reward);
		}

		return 0;
	}
	return R_ERR_NO_DATA;
}
int CDataXML::GetOlGateConfig(unsigned level, map<string, string> &config)
{
	if (m_mapXMLOlGate.count(level))
	{
		DataXMLGateReward *pdata = (DataXMLGateReward *)m_shGateReward.GetAddress();
		if(pdata == NULL)
		{
			return R_ERROR;
		}
		CAutoLock lock(const_cast<CShareMemory *>(&(m_shGateReward)), true);

		for(unsigned i=m_mapXMLOlGate[level];i<GATE_REWARD_NUM;++i)
		{
			if(pdata->reward[i].level != level)
				break;

			config[string(pdata->reward[i].id)] = string(pdata->reward[i].reward);
		}

		return 0;
	}
	return R_ERR_NO_DATA;
}
int CDataXML::GetQuestConfig(const string &id, Json::Value &reward)
{
	if (m_mapXMLQuest.count(id))
	{
		DataXMLQuestReward *pdata = (DataXMLQuestReward *)m_shQuestReward.GetAddress();
		if(pdata == NULL)
		{
			return R_ERROR;
		}
		CAutoLock lock(const_cast<CShareMemory *>(&(m_shQuestReward)), true);

		string temp(pdata->reward[m_mapXMLQuest[id]].reward);
		Json::FromString(reward, temp);

		return 0;
	}
	return R_ERR_NO_DATA;
}

int CDataXML::InitHeavenDaoist()
{
	DataXMLHeavenDaoist *pdata = (DataXMLHeavenDaoist *)m_shHeavenDaoist.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shHeavenDaoist), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	int ret = GetFile("heavenConfig.xml", dataPath);
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

	if (!xmlConf.FindElem("hero"))
	{
		cout << ("hero node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();


	string id;
	string exp;
	string res;
	string needeq;
	string per;
	unsigned i = 0;
	unsigned n = 0;
	m_mapXMLHeavenDaoist.clear();

	for (i = 0; i < HEAVEN_NUM; ++i)
	{
		xmlConf.FindElem("floor");
		id = xmlConf.GetAttrib("id");
		exp = xmlConf.GetAttrib("exp");
		res = xmlConf.GetAttrib("res");
		needeq = xmlConf.GetAttrib("needeq");
		per = xmlConf.GetAttrib("per");

		if (id.empty() || exp.empty() || res.empty() || needeq.empty() || per.empty())
		{
			cout << ("heavenConfig wrong") << endl;
			return R_ERROR;
		}

		n = res.find_first_of(',');

		pdata->heavenDaoist[i].id = CTrans::STOI(id.c_str());
		pdata->heavenDaoist[i].exp = CTrans::STOI(exp.c_str());
		pdata->heavenDaoist[i].res = CTrans::STOI(res.substr(0, n).c_str());
		pdata->heavenDaoist[i].needeq = CTrans::STOI(needeq.c_str());
		pdata->heavenDaoist[i].per = CTrans::STOI(per.c_str());

		m_mapXMLHeavenDaoist[pdata->heavenDaoist[i].id] = i;
	}

	xmlConf.OutOfElem();

	if (!xmlConf.FindElem("building"))
	{
		cout << ("building node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	for (i = HEAVEN_NUM; i < HEAVEN_DAOIST_NUM; ++i)
	{
		xmlConf.FindElem("floor");

		id = xmlConf.GetAttrib("id");
		exp = xmlConf.GetAttrib("exp");
		res = xmlConf.GetAttrib("res");
		needeq = xmlConf.GetAttrib("needeq");
		per = xmlConf.GetAttrib("per");

		if (id.empty() || exp.empty() || res.empty() || needeq.empty() || per.empty())
		{
			cout << ("heavenConfig wrong") << endl;
			return R_ERROR;
		}

		n = res.find_last_of(',') + 1;

		pdata->heavenDaoist[i].id = CTrans::STOI(id.c_str());
		pdata->heavenDaoist[i].exp = CTrans::STOI(exp.c_str());
		pdata->heavenDaoist[i].res = CTrans::STOI(res.substr(n).c_str());
		pdata->heavenDaoist[i].needeq = CTrans::STOI(needeq.c_str());
		pdata->heavenDaoist[i].per = CTrans::STOI(per.c_str());

		m_mapXMLHeavenDaoist[pdata->heavenDaoist[i].id] = i;
	}

	xmlConf.OutOfElem();

	if (xmlConf.FindElem("heavenuplevel"))
	{
		xmlConf.IntoElem();
		int num = 0;
		while (xmlConf.FindElem("item"))
		{
			//strcpy(pdata->heavenup[i][num].name,bingzhongname[i]);
			pdata->heavenup[num].level = Convert::StringToUInt(xmlConf.GetAttrib("level"));
			pdata->heavenup[num].exp = Convert::StringToUInt(xmlConf.GetAttrib("exp"));
			pdata->heavenup[num].eqid = Convert::StringToUInt(xmlConf.GetAttrib("eqid"));
			pdata->heavenup[num].eqid2 = Convert::StringToUInt(xmlConf.GetAttrib("eqid2"));
			pdata->heavenup[num].needeq = Convert::StringToUInt(xmlConf.GetAttrib("needeq"));
			pdata->heavenup[num].needeq2 = Convert::StringToUInt(xmlConf.GetAttrib("needeq2"));
			pdata->heavenup[num].per = Convert::StringToUInt(xmlConf.GetAttrib("per"));
			res = xmlConf.GetAttrib("res");
			n = res.find_last_of(',') - 1;
			pdata->heavenup[num].res = CTrans::STOI(res.substr(4,n-4+1).c_str());
			m_XMLHeavenUp[pdata->heavenup[num].exp] = pdata->heavenup[num];
			cout << pdata->heavenup[num].level << " "
				<< pdata->heavenup[num].exp << " "
				<< pdata->heavenup[num].eqid << " "
				<< pdata->heavenup[num].eqid2 << " "
				<< pdata->heavenup[num].needeq << " "
				<< pdata->heavenup[num].needeq2 << " "
				<< pdata->heavenup[num].per << " "
				<< pdata->heavenup[num].res << endl;
			++num;
		}
		xmlConf.OutOfElem();
	}


	m_shHeavenDaoist.SetInitDone();

	return R_SUCCESS;
}


// id must
int CDataXML::GetHeavenDaoistItem(const unsigned id, XMLHeavenDaoist &item)
{
	if (!m_mapXMLHeavenDaoist.count(id))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLHeavenDaoist *pdata = (DataXMLHeavenDaoist *)m_shHeavenDaoist.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shHeavenDaoist)), true);

	item = pdata->heavenDaoist[m_mapXMLHeavenDaoist[id]];

	return R_SUCCESS;
}


int CDataXML::GetHeavenDaoistLv(unsigned id, unsigned exp, unsigned &lv)
{
	if (!m_mapXMLHeavenDaoist.count(id))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLHeavenDaoist *pdata = (DataXMLHeavenDaoist *)m_shHeavenDaoist.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shHeavenDaoist)), true);

	lv = m_mapXMLHeavenDaoist[id];

	while (lv && (pdata->heavenDaoist[lv].exp > exp))
	{
		--lv;
	}

	return R_SUCCESS;
}

int CDataXML::GetHeavenUp( unsigned exp, XMLHeavenUp &data, int &needexp)
{
	map<unsigned,XMLHeavenUp>::iterator itr = m_XMLHeavenUp.begin();
	while (itr != m_XMLHeavenUp.end())
	{
		map<unsigned,XMLHeavenUp>::iterator olditr = itr;
		itr++;
		if (itr == m_XMLHeavenUp.end())
		{
			return R_ERR_DATA;
		}

		if (exp >= olditr->first && exp < itr->first)
		{
			data = olditr->second;
			needexp = itr->first - exp;
			return 0;
		}
	}
	return R_ERR_DATA;
}

int CDataXML::GetMaxHeavenUpExp(unsigned & exp)
{
	exp = 0;
	for (map<unsigned,XMLHeavenUp>::iterator itr = m_XMLHeavenUp.begin();itr != m_XMLHeavenUp.end();++itr)
	{
		if (exp < itr->first)
			exp = itr->first;
	}
	return 0;
}

int CDataXML::GetHeavenUpLevel(unsigned exp, unsigned &level)
{
	level = 0;
	const map<unsigned, XMLHeavenUp> *pXMLTemp = NULL;
		pXMLTemp = &(m_XMLHeavenUp);

	map<unsigned,XMLHeavenUp>::const_iterator itr = pXMLTemp->begin();
	while (itr != pXMLTemp->end())
	{
		map<unsigned,XMLHeavenUp>::const_iterator olditr = itr;
		itr++;
		if (itr == pXMLTemp->end())
		{
			return 0;
		}
		if (exp >= olditr->first && exp < itr->first)
		{
			return 0;
		}
		level++;
	}
	return 0;
}

int CDataXML::InitCostHeavenDaoist()
{
	DataXMLCostHeavenDaoist *pdata = (DataXMLCostHeavenDaoist *)m_shCostHeavenDaoist.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCostHeavenDaoist), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	int ret = GetFile("heavenConfig.xml", dataPath);
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

	if (!xmlConf.FindElem("cost"))
	{
		cout << ("cost node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string jie = "";
	string cash = "";
	m_mapCostHeavenDaoist.clear();
	for(unsigned i = 0; i < HEAVEN_JIE_NUM; ++i)
	{
		xmlConf.FindElem("bingshu");
		jie = xmlConf.GetAttrib("jie");
		cash = xmlConf.GetAttrib("cash");
		if (jie.empty() || cash.empty())
		{
			cout << ("heavenConfig cost wrong") << endl;
			return R_ERROR;
		}
		m_mapCostHeavenDaoist[i] = CTrans::STOI(cash.c_str());
		pdata->heavenDaoistCost[i].id = i;
		pdata->heavenDaoistCost[i].jie = CTrans::STOI(jie.c_str());
		pdata->heavenDaoistCost[i].cash = CTrans::STOI(cash.c_str());
	}

	for(unsigned i = HEAVEN_JIE_NUM; i < HEAVEN_JIE_NUM + DAOIST_JIE_NUM; ++i)
	{
		xmlConf.FindElem("dunjia");
		jie = xmlConf.GetAttrib("jie");
		cash = xmlConf.GetAttrib("cash");
		if (jie.empty() || cash.empty())
		{
			cout << ("heavenConfig cost wrong") << endl;
			return R_ERROR;
		}
		m_mapCostHeavenDaoist[i] = CTrans::STOI(cash.c_str());
		pdata->heavenDaoistCost[i].id = i;
		pdata->heavenDaoistCost[i].jie = CTrans::STOI(jie.c_str());
		pdata->heavenDaoistCost[i].cash = CTrans::STOI(cash.c_str());
	}

	xmlConf.OutOfElem();

	m_shCostHeavenDaoist.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::InitCostHeavenUp()
{
	DataXMLCostHeavenUp *pdata = (DataXMLCostHeavenUp *)m_shCostHeavenUp.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCostHeavenUp),true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath;
	int ret = GetFile("heavenConfig.xml",dataPath);
	if(ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if(!xmlConf.Load(dataPath.c_str()))
	{
		error_log("InitCostHeavenUp dataPath loading wrong!");
		return R_ERROR;
	}

	if(!xmlConf.FindElem("content"))
	{
		error_log("InitCostHeavenUp content node wrong!");
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("cost"))
	{
		cout << ("cost node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string jie = "";
	string cash = "";

	//钻石
	for(unsigned i = 0; i < HEAVENUP_JIE_NUM;++i)
	{
		xmlConf.FindElem("bingshuup");
		jie = xmlConf.GetAttrib("jie");
		cash = xmlConf.GetAttrib("cash");
		if(jie.empty() || cash.empty())
		{
			error_log("heavenConf cost wrong!");
			return R_ERROR;
		}

		pdata->heavenUpCost[i].id = i;
		pdata->heavenUpCost[i].jie = CTrans::STOI(jie.c_str());
		pdata->heavenUpCost[i].cash = CTrans::STOI(cash.c_str());
	}

	//兵书替换兵魂
	string bshu_num = "";
	string bhun_num = "";
	string exchange_max_times = "";

	bool flag = xmlConf.FindElem("bingshuupmax");
	if(!flag)
	{
		cout << ("bingshuupmax node wrong") << endl;
		return R_ERROR;
	}

	bshu_num = xmlConf.GetAttrib("shu");
	bhun_num = xmlConf.GetAttrib("hun");
	exchange_max_times = xmlConf.GetAttrib("huanmax");
	
	if(bshu_num.empty() || bhun_num.empty() || exchange_max_times.empty())
	{
		LOGIC_ERROR_RETURN_MSG("heavenConf cost bingshuupmax reading error");
	}
	
	pdata->exBinghun.bingshuNum = CTrans::STOI(bshu_num.c_str());
	pdata->exBinghun.binghunNum = CTrans::STOI(bhun_num.c_str());
	pdata->exBinghun.maxTimes = CTrans::STOI(exchange_max_times.c_str());

	xmlConf.OutOfElem();

	m_shCostHeavenUp.SetInitDone();
	return R_SUCCESS;
}

int CDataXML::GetCostHeavenUp(unsigned jie_index,unsigned &cash)
{
	if(!m_mapCostHeavenUp.count(jie_index))  
	{
		error_log("heavenXML to map wrong!");
		return R_ERR_NO_DATA;
	}

	cash = m_mapCostHeavenUp[jie_index];
	return R_SUCCESS;
}

int CDataXML::GetCostHeavenDaoist(bool is_heaven, unsigned jie_index, unsigned &cash)
{
	unsigned real_index = 0;
	real_index = is_heaven ? jie_index : (jie_index + HEAVEN_JIE_NUM);
	if (!m_mapCostHeavenDaoist.count(real_index))
	{
		return R_ERR_NO_DATA;
	}

	cash = m_mapCostHeavenDaoist[real_index];
	return R_SUCCESS;
}

int CDataXML::GetExchangeBinghuToBinghun(unsigned index,XMLCostHeavenUPToBinghun &data)
{
	if(m_mapCostBShuToBHun.size() == 0)
	{
		return R_ERR_NO_DATA;
	}
	memset(&data,0,sizeof(data));

	data = m_mapCostBShuToBHun[index];
	return R_SUCCESS;
}

int CDataXML::InitEightFormation()
{
	DataXMLEightFormation* pdata = (DataXMLEightFormation*)m_shEightFormation.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shEightFormation), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	int ret = GetFile("bazhentu.xml", dataPath);
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

	while(xmlConf.FindElem("bazhentu"))
	{
		string r = xmlConf.GetAttrib("r");
		unsigned r_index = CTrans::STOI(r.c_str())-1;
		string ids = xmlConf.GetAttrib("ids");
		std::size_t tail = 0;
		string str = ids;
		while(tail != string::npos)
		{
			tail = str.find_first_of(',');
			unsigned idx = CTrans::STOI(str.substr(0, tail).c_str());
			if(idx < 9)
				(pdata->r)[idx] = r_index;
			str = str.substr(tail+1);
		}

		xmlConf.IntoElem();
		unsigned floor_index = 0;
		while(xmlConf.FindElem("floor"))
		{
			string id =  xmlConf.GetAttrib("id");
			string exp = xmlConf.GetAttrib("exp");
			string res = xmlConf.GetAttrib("res");
			string needeq = xmlConf.GetAttrib("needeq");
			string per= xmlConf.GetAttrib("per");

			if (id.empty() || exp.empty() || res.empty() || needeq.empty() || per.empty())
			{
				cout << ("bazhentu wrong") << endl;
				return R_ERROR;
			}
			unsigned n = res.find_first_of(',');
			(pdata->eightFormation)[r_index][floor_index].id =  CTrans::STOI(id.c_str());
			(pdata->eightFormation)[r_index][floor_index].exp =  CTrans::STOI(exp.c_str());
			(pdata->eightFormation)[r_index][floor_index].res =  CTrans::STOI(res.substr(0, n).c_str());
			(pdata->eightFormation)[r_index][floor_index].needeq =  CTrans::STOI(needeq.c_str());
			(pdata->eightFormation)[r_index][floor_index].per =  CTrans::STOI(per.c_str());
			++floor_index;
		}
		xmlConf.OutOfElem();
	}

	m_shEightFormation.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetEightFormationItem(const unsigned id, const unsigned idx, XMLEightFormation &item)
{
	unsigned r = eight_formation[id];

	if (!m_mapXMLEightFormation[r].count(idx))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLEightFormation *pdata = (DataXMLEightFormation *)m_shEightFormation.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shEightFormation)), true);

	item = (pdata->eightFormation)[r][m_mapXMLEightFormation[r][idx]];

	return R_SUCCESS;
}

int CDataXML::GetEightFormationLv(unsigned id, unsigned idx, unsigned exp, unsigned &lv)
{
	unsigned r = eight_formation[id];

	if (!m_mapXMLEightFormation[r].count(idx))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLEightFormation *pdata = (DataXMLEightFormation *)m_shEightFormation.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shEightFormation)), true);

	lv = m_mapXMLEightFormation[r][idx];

	while (lv && ((pdata->eightFormation)[r][lv].exp > exp))
	{
		--lv;
	}

	return R_SUCCESS;
}

unsigned CDataXML::GetMaxExp(unsigned id, unsigned maxlv)
{
	DataXMLEightFormation *pdata = (DataXMLEightFormation *)m_shHeavenDaoist.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(static_cast<CShareMemory *>(&(m_shEightFormation)), true);
	unsigned r = eight_formation[id];

	return (pdata->eightFormation)[r][maxlv].exp;

}


int CDataXML::InitCostEightFormation()
{
	DataXMLCostEightFormation *pdata = (DataXMLCostEightFormation *)m_shCostEightFormation.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCostEightFormation), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	int ret = GetFile("bazhentu.xml", dataPath);
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

	if (!xmlConf.FindElem("cost"))
	{
		cout << ("cost node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string jie = "";
	string cash = "";
	m_mapCostEightFormation.clear();
	for(unsigned i = 0; i <= EIGHT_FORMATION_JIE_NUM; ++i)
	{
		xmlConf.FindElem("array");
		jie = xmlConf.GetAttrib("jie");
		cash = xmlConf.GetAttrib("cash");
		if (jie.empty() || cash.empty())
		{
			cout << ("eightFormation cost wrong") << endl;
			return R_ERROR;
		}
		m_mapCostEightFormation[i] = CTrans::STOI(cash.c_str());
		pdata->eightFormationCost[i].id = i;
		pdata->eightFormationCost[i].jie = CTrans::STOI(jie.c_str());
		pdata->eightFormationCost[i].cash = CTrans::STOI(cash.c_str());
	}

	m_shCostEightFormation.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetCostEightFormation(unsigned jie_index, unsigned &cash)
{
	if (!m_mapCostEightFormation.count(jie_index))
	{
		return R_ERR_NO_DATA;
	}

	cash = m_mapCostEightFormation[jie_index];
	return R_SUCCESS;
}


int CDataXML::InitDouble11()
{
	int ret = 0;

	DataXMLDouble11 *pdata = (DataXMLDouble11 *)m_shDouble11.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock((&(m_shDouble11)), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("yuandan.xml", dataPath);
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

	if (!xmlConf.FindElem("shuang11"))
	{
		cout << ("shuang11 node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string eqid;
	string price;
	string eqcnt;
	string total;

	unsigned i = 0;
	unsigned j = 0;

	while (xmlConf.FindElem("type"))
	{
		xmlConf.IntoElem();
		j = 0;

		while (xmlConf.FindElem("item"))
		{
			eqid = xmlConf.GetAttrib("id");
			eqcnt = xmlConf.GetAttrib("amount");
			price = xmlConf.GetAttrib("price");
			total = xmlConf.GetAttrib("total");

			pdata->prop[i][j].eqid = CTrans::STOI(eqid.c_str());
			pdata->prop[i][j].eqcnt = CTrans::STOI(eqcnt.c_str());
			pdata->prop[i][j].price = CTrans::STOI(price.c_str());
			pdata->prop[i][j].total = CTrans::STOI(total.c_str());

			++j;
		}
		xmlConf.OutOfElem();

		++i;
	}

	m_shDouble11.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::InitBetShop()
{
	int ret = 0;

	DataXMLBetShop *pdata = (DataXMLBetShop *)m_shBetShop.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shBetShop), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("qiriConfig.xml", dataPath);
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

	if (!xmlConf.FindElem("betshop"))
	{
		cout << ("betshop node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	unsigned eqid;
	string times;
	unsigned c;
	string cost;

	XMLBetShopItem item;

	unsigned i = 0;
	m_mapXMLBetShop.clear();

	while (xmlConf.FindElem("reward"))
	{
		times = xmlConf.GetAttrib("times");
		cost = xmlConf.GetAttrib("cost");
		string context = xmlConf.GetData();
		Json::Value reward;
		Json::FromString(reward, context);

		if (reward["reward"].isMember("equip1"))
		{
			eqid = reward["reward"]["equip1"]["id"].asUInt();
			c = reward["reward"]["equip1"]["c"].asUInt();
		}
		else if (reward["reward"].isMember("gold"))
		{
			// 只有一个,那么没有问题,有多个时使用eqid++
			eqid = 0;
			c = reward["reward"]["gold"].asUInt();
		}
		else
		{
			cout << ("CData node is wrong") << endl;
			return R_ERROR;
		}

		item.eqid = eqid;
		item.c = c;
		item.times = CTrans::STOI(times);
		item.cost = CTrans::STOI(cost);

		pdata->bsitem[i] = item;

		m_mapXMLBetShop[eqid] = item;
		++i;
	}

	m_shBetShop.SetInitDone();

	return R_SUCCESS;
}


int CDataXML::GetBetShopItem(unsigned eqid, XMLBetShopItem &item)
{
	if (!m_mapXMLBetShop.count(eqid))
	{
		return R_ERR_DATA;
	}

	item = m_mapXMLBetShop[eqid];

	return R_SUCCESS;
}

int CDataXML::InitPayOptional()
{
	int ret = 0;
	Json::Value data;

	ret = readJsonConfFile("vicky_pay.json", data);

	if (ret)
	{
		return ret;
	}

	//解析json
	if(!data.isMember("vicy_pay") || !data["vicy_pay"].isArray())
	{
		error_log("json format error. no vicy_pay or not array");
		return ret;
	}

	m_payoptionals.clear();
	PayOptionalItem optionalitem;

	for(unsigned i = 0; i < data["vicy_pay"].size(); ++i)
	{
		optionalitem.Clear();

		unsigned index = data["vicy_pay"][i]["index"].asUInt();
		optionalitem.index = index;
		optionalitem.equip.id = data["vicy_pay"][i]["id"].asUInt();
		optionalitem.equip.cnt = data["vicy_pay"][i]["count"].asUInt();

		m_payoptionals[index] = optionalitem;
	}

	return 0;
}

int CDataXML::GetPayOptionalItem(vector<unsigned> & indexs, vector<PayOptionalItem> & items)
{
	for(int i = 0; i < indexs.size(); ++i)
	{
		if (!m_payoptionals.count(indexs[i]))
		{
			return R_ERR_PARAM;
		}

		items.push_back(m_payoptionals[indexs[i]]) ;
	}

	return 0;
}

int CDataXML::InitHeQuActivity()
{
	DataXMLHequActivity *pdata = (DataXMLHequActivity *)m_shHequActivity.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLHequActivity),
			"hequConfig.xml", m_shHequActivity, &CDataXML::ParseXMLHeQuActivity);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetChargeRewardItem(unsigned index, HeQuChargeItem & item)
{
	DataXMLHequActivity *pdata = (DataXMLHequActivity *)m_shHequActivity.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shHequActivity getaddress error.");
		return R_ERR_DB;
	}

	if (index < 1 || index > MAX_CHARGE_ITEMS)
	{
		error_log("param error. index=%u", index);
		return R_ERR_PARAM;
	}

	item = pdata->chargeitems[index - 1];

	return 0;
}

int CDataXML::GetVIPRewardItem(unsigned vindex, unsigned sindex, HeQuVIPItem & item)
{
	DataXMLHequActivity *pdata = (DataXMLHequActivity *)m_shHequActivity.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shHequActivity getaddress error.");
		return R_ERR_DB;
	}

	if (vindex < 1 || vindex > MAX_VIP_ITEMS)
	{
		error_log("param error. vindex=%u", vindex);
		return R_ERR_PARAM;
	}

	if (sindex < 1 || sindex > MAX_VIP_SUBQUENT)
	{
		error_log("param error. sindex=%u", sindex);
		return R_ERR_PARAM;
	}

	item = pdata->vipitems[vindex - 1][sindex - 1];

	return 0;
}

int CDataXML::GetRecompenseRewardItem(unsigned index, HeQuRecompense & item)
{
	DataXMLHequActivity *pdata = (DataXMLHequActivity *)m_shHequActivity.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shHequActivity getaddress error.");
		return R_ERR_DB;
	}

	if (index < 1 || index > MAX_RECOMPENSE_ITEMS)
	{
		error_log("param error. index=%u", index);
		return R_ERR_PARAM;
	}

	item = pdata->recomitems[index - 1];

	return 0;
}

int CDataXML::ParseXMLHeQuActivity(void *data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLHequActivity * pdata = (DataXMLHequActivity *) data;

	//解析充值
	ret = ParseXMLCharge(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	//解析vip
	ret = ParseXMLVIP(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	//解析补偿
	ret = ParseXMLRecompense(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::ParseXMLCharge(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf)
{
	if(!xmlConf.FindElem("charge"))
	{
		cout<<("charge node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	int index = 0;

	//解析充值
	while(xmlConf.FindElem("item") && index < MAX_CHARGE_ITEMS)
	{
		string cash = xmlConf.GetAttrib("gold");

		//读取奖励配置
		Json::Value rewardval;
		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->charge->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (!rewardval.isMember("reward"))
		{
			cout<<"content->charge->item["<<index<<"]'s reward not exist."<< endl;
			return R_ERROR;
		}

		pdata->chargeitems[index].cash = CTrans::STOI(cash.c_str());

		for(int i = 0; i < EQUIP_ITEMS_MAX; ++i)
		{
			//equip优先
			char keys[10] = {0};
			sprintf(keys, "equip%u", i+1);

			if (!rewardval["reward"].isMember(keys))
			{
				break;
			}

			int itemindex = pdata->chargeitems[index].itemnum;

			pdata->chargeitems[index].items[itemindex].m_nId = rewardval["reward"][keys]["id"].asUInt();
			pdata->chargeitems[index].items[itemindex].m_nCnt = rewardval["reward"][keys]["c"].asUInt();

			++pdata->chargeitems[index].itemnum;
		}

		if (EQUIP_ITEMS_MAX != pdata->chargeitems[index].itemnum)
		{
			//equip配置没有填充完奖励数组，找寻英雄配置
			if (rewardval["reward"].isMember("hero"))
			{
				//英雄配置
				int itemindex = pdata->chargeitems[index].itemnum;

				pdata->chargeitems[index].items[itemindex].m_nId = rewardval["reward"]["hero"]["id"].asUInt();
				pdata->chargeitems[index].items[itemindex].m_nCnt = rewardval["reward"]["hero"]["c"].asUInt();

				pdata->chargeitems[index].items[itemindex].m_bIsHero = true;

				++pdata->chargeitems[index].itemnum;
			}
		}

		++index;
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::ParseXMLVIP(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf)
{
	if(!xmlConf.FindElem("vips"))
	{
		cout<<("vips node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	int vindex = 0;

	while(xmlConf.FindElem("vip") && vindex < MAX_VIP_ITEMS)
	{
		xmlConf.IntoElem();
		int sindex = 0;

		while(xmlConf.FindElem("item") && sindex < MAX_VIP_SUBQUENT)
		{
			string strminlv = xmlConf.GetAttrib("lv");
			int minlv = CTrans::STOI(strminlv.substr(0, 1).c_str());

			pdata->vipitems[vindex][sindex].limit_vip = minlv;

			//读取奖励配置
			Json::Value rewardval;
			if (!Json::FromString(rewardval, xmlConf.GetData()))
			{
				cout<<"content->vip->item["<<vindex<<"-"<<sindex<<"]'s value read fail."<< endl;
				return R_ERROR;
			}

			if (!rewardval.isMember("reward"))
			{
				cout<<"content->vip->item["<<vindex<<"-"<<sindex<<"]'s reward not exist."<< endl;
				return R_ERROR;
			}

			for(int i = 0; i < EQUIP_ITEMS_MAX; ++i)
			{
				//equip优先
				char keys[10] = {0};
				sprintf(keys, "equip%u", i+1);

				if (!rewardval["reward"].isMember(keys))
				{
					break;
				}

				int itemindex = pdata->vipitems[vindex][sindex].itemnum;

				pdata->vipitems[vindex][sindex].items[itemindex].m_nId = rewardval["reward"][keys]["id"].asUInt();
				pdata->vipitems[vindex][sindex].items[itemindex].m_nCnt = rewardval["reward"][keys]["c"].asUInt();

				++pdata->vipitems[vindex][sindex].itemnum;
			}

			if (EQUIP_ITEMS_MAX != pdata->vipitems[vindex][sindex].itemnum)
			{
				//equip配置没有填充完奖励数组，找寻英雄配置
				if (rewardval["reward"].isMember("hero"))
				{
					//英雄配置
					int itemindex = pdata->vipitems[vindex][sindex].itemnum;

					pdata->vipitems[vindex][sindex].items[itemindex].m_nId = rewardval["reward"]["hero"]["id"].asUInt();
					pdata->vipitems[vindex][sindex].items[itemindex].m_nCnt = rewardval["reward"]["hero"]["c"].asUInt();

					pdata->vipitems[vindex][sindex].items[itemindex].m_bIsHero = true;

					++pdata->vipitems[vindex][sindex].itemnum;
				}
			}

			++sindex;
		}

		xmlConf.OutOfElem();
		++vindex;
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::ParseXMLRecompense(DataXMLHequActivity *pdata, CMarkupSTL & xmlConf)
{
	if(!xmlConf.FindElem("buchang"))
	{
		cout<<("buchang node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	int index = 0;

	while(xmlConf.FindElem("item") && index < MAX_RECOMPENSE_ITEMS)
	{
		string minlv = xmlConf.GetAttrib("minLevel");
		string maxlv = xmlConf.GetAttrib("maxLevel");

		pdata->recomitems[index].minlevel = CTrans::STOI(minlv.c_str());
		pdata->recomitems[index].maxlevel = CTrans::STOI(maxlv.c_str());

		//读取奖励配置
		Json::Value rewardval;
		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->buchang->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (!rewardval.isMember("reward"))
		{
			cout<<"content->buchang->item["<<index<<"]'s reward not exist."<< endl;
			return R_ERROR;
		}

		for(int i = 0; i < EQUIP_ITEMS_MAX; ++i)
		{
			//equip优先
			char keys[10] = {0};
			sprintf(keys, "equip%u", i+1);

			if (!rewardval["reward"].isMember(keys))
			{
				break;
			}

			int itemindex = pdata->recomitems[index].itemnum;

			pdata->recomitems[index].items[itemindex].m_nId = rewardval["reward"][keys]["id"].asUInt();
			pdata->recomitems[index].items[itemindex].m_nCnt = rewardval["reward"][keys]["c"].asUInt();

			++pdata->recomitems[index].itemnum;
		}

		if (EQUIP_ITEMS_MAX != pdata->recomitems[index].itemnum)
		{
			//equip配置没有填充完奖励数组，找寻英雄配置
			if (rewardval["reward"].isMember("hero"))
			{
				//英雄配置
				int itemindex = pdata->recomitems[index].itemnum;

				pdata->recomitems[index].items[itemindex].m_nId = rewardval["reward"]["hero"]["id"].asUInt();
				pdata->recomitems[index].items[itemindex].m_nCnt = rewardval["reward"]["hero"]["c"].asUInt();

				pdata->recomitems[index].items[itemindex].m_bIsHero = true;

				++pdata->recomitems[index].itemnum;
			}
		}

		++index;
	}

	xmlConf.OutOfElem();
	return 0;
}

int CDataXML::InitAncientScroll()
{
	DataXMLAncientScroll *pdata = (DataXMLAncientScroll *)m_shAncientScroll.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLAncientScroll),
			"gujuanqishu.xml", m_shAncientScroll, &CDataXML::ParseXMLAncientScroll);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::ParseXMLAncientScroll(void *data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLAncientScroll * pdata = (DataXMLAncientScroll *) data;

	//直接从content的下一级目录中解析
	int index = 0;

	while(xmlConf.FindElem("gujuan") && index < ANCIENT_SCROLL_ITEMS)
	{
		xmlConf.IntoElem();
		int sindex = 0;

		while(xmlConf.FindElem("item") && sindex < MAX_SCROLL_LEVEL)
		{
			//读取属性
			string id = xmlConf.GetAttrib("id");
			string zhuzi = xmlConf.GetAttrib("zhuzi");
			string needeq = xmlConf.GetAttrib("needeq");
			string strres = xmlConf.GetAttrib("res");
			Json::Value res;

			if (!Json::FromString(res, strres))
			{
				cout<<"[gujuan-"<<index<<"-item-"<<sindex<<"]'s res attribute read fail."<< endl;
				return R_ERROR;
			}

			pdata->items[index][sindex].id = CTrans::STOI(id.c_str());
			pdata->items[index][sindex].zhuzi = CTrans::STOI(zhuzi.c_str());
			pdata->items[index][sindex].needeq = CTrans::STOI(needeq.c_str());

			for(int i = 0; i < res.size() && i < 4; ++i)
			{
				pdata->items[index][sindex].res[i] = res[i].asUInt();
			}

			++sindex;
		}

		xmlConf.OutOfElem();

		++index;
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::GetAncientItem(unsigned id, unsigned level, ScrollItem & item)
{
	DataXMLAncientScroll *pdata = (DataXMLAncientScroll *)m_shAncientScroll.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shAncientScroll getaddress error.");
		return R_ERR_DB;
	}

	if (id < 1 || id > ANCIENT_SCROLL_ITEMS)
	{
		error_log("param error. id=%u", id);
		return R_ERR_PARAM;
	}

	if (level < 1 || level >= MAX_SCROLL_LEVEL)
	{
		error_log("param error. level=%u", level);
		return R_ERR_PARAM;
	}

	item = pdata->items[id - 1][level];

	return 0;
}

int CDataXML::InitProtectFlag()
{
	DataXMLProtectFlag *pdata = (DataXMLProtectFlag *)m_shProtectFlag.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLProtectFlag),
			"buildingupgrade.xml", m_shProtectFlag, &CDataXML::ParseXMLProtectFlag);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetProtectFlagPointer(DataXMLProtectFlag ** pflag)
{
	DataXMLProtectFlag *pdata = (DataXMLProtectFlag *)m_shProtectFlag.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shProtectFlag getaddress error.");
		return R_ERR_DB;
	}

	*pflag = pdata;

	return 0;
}

int CDataXML::ParseXMLProtectFlag(void *data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLProtectFlag * pdata = (DataXMLProtectFlag *) data;

	//直接从content的下一级目录中解析
	if(!xmlConf.FindElem("exp"))
	{
		cout<<("exp node wrong")<<endl;
		return R_ERROR;
	}

	//读取节点数据
	Json::Value expval;

	if (!Json::FromString(expval, xmlConf.GetData()))
	{
		cout<<"content->exp's value read fail."<< endl;
		return R_ERROR;
	}

	for(unsigned i = 0; i < expval.size() && i < MAX_FLAG_LEVEL; ++i)
	{
		pdata->exps[i] = expval[i].asUInt();
	}

	//直接从content的下一级目录中解析
	if(!xmlConf.FindElem("eqcount"))
	{
		cout<<("eqcount node wrong")<<endl;
		return R_ERROR;
	}

	//读取节点数据
	Json::Value eqcountval;

	if (!Json::FromString(eqcountval, xmlConf.GetData()))
	{
		cout<<"content->eqcount's value read fail."<< endl;
		return R_ERROR;
	}

	for(unsigned i = 0; i < eqcountval.size() && i < MAX_FLAG_LEVEL; ++i)
	{
		pdata->eqcount[i] = eqcountval[i].asUInt();
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::InitProtectGoddess()
{
	DataXMLProtectGoddess *pdata = (DataXMLProtectGoddess *)m_shProtectGoddess.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLProtectGoddess),
			"nvshen.xml", m_shProtectGoddess, &CDataXML::ParseXMLProtectGoddess);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetProtectGoddessRewardItem(unsigned id, ProtectGoddessRewardItem ** pflag)
{
	if (!m_protectgoddess.count(id))
	{
		error_log("wrong id param. id=%u", id);
		return R_ERROR;
	}

	DataXMLProtectGoddess *pdata = (DataXMLProtectGoddess *)m_shProtectGoddess.GetAddress();

	if(pdata == NULL)
	{
		error_log("m_shProtectGoddess getaddress error.");
		return R_ERR_DB;
	}

	unsigned index = m_protectgoddess[id];

	*pflag = &pdata->reward[index];

	return 0;
}

int CDataXML::ParseXMLProtectGoddess(void *data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLProtectGoddess * pdata = (DataXMLProtectGoddess *) data;

	//直接从content的下一级目录中解析
	if(!xmlConf.FindElem("reward"))
	{
		cout<<("reward node wrong")<<endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();
	int index = 0;

	while(xmlConf.FindElem("item") && index < MAX_REWARD_ITEM)
	{
		string id = xmlConf.GetAttrib("id");
		string point = xmlConf.GetAttrib("jf");

		pdata->reward[index].id = CTrans::STOI(id.c_str());
		pdata->reward[index].point = CTrans::STOI(point.c_str());

		//读取奖励配置
		Json::Value rewardval;

		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->reward->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (!rewardval.isMember("reward"))
		{
			cout<<"content->reward->item["<<index<<"]'s reward not exist."<< endl;
			return R_ERROR;
		}

		for(int i = 0; i < MAX_REWARD_EQUIP_ITEM; ++i)
		{
			//equip优先
			char keys[10] = {0};
			sprintf(keys, "equip%u", i+1);

			if (!rewardval["reward"].isMember(keys))
			{
				break;
			}

			int itemindex = pdata->reward[index].itemnum;

			pdata->reward[index].items[itemindex].m_nId = rewardval["reward"][keys]["id"].asUInt();
			pdata->reward[index].items[itemindex].m_nCnt = rewardval["reward"][keys]["c"].asUInt();

			++pdata->reward[index].itemnum;
		}

		++index;
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::_parse_activity_simple_reward(const Json::Value &reward, XMLActSimpleReward *data, int len)
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

int CDataXML::_get_xml(CMarkupSTL &xmlConf, const string &file_name)
{
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);  //获得绝对路径
	if (dataPath.empty())
		return R_ERR_DATA;

	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append(file_name);  //加上文件名
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return R_ERR_DATA;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return R_ERR_DATA;
	}
	xmlConf.IntoElem();
	return 0;
}
