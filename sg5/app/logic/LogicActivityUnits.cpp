/*
 * LogicActivityUnits.cpp
 *
 *  Created on: 2016-8-24
 *      Author: Administrator
 */

#include "LogicActivityUnits.h"
#include "LogicCmdUnits.h"

CActUnit::CActUnit(){
	_new_act.clear();
	_act_time_name.clear();
}
CActUnit::~CActUnit(){
}
int CActUnit::Init(unsigned uid, const string &act_time_name, unsigned lasttime, unsigned seqid){
	if (_init){
		return 0;
	}
	_uid = uid;
	_lasttime = lasttime;
	_seqid = seqid;
	_act_time_name = act_time_name;  //活动名称
	int domain = 0;
	Config::GetDB(domain);
	_serverid = MainConfig::GetMergedDomain(domain);
	CLogicUser logicUser;
	int ret = 0;
	ret = logicUser.GetUser(_uid, _user);  //获得玩家(user)信息,从数据库里获得
	if (ret){
		return ret;
	}
	_act_time.init(_act_time_name);  //配置活动名称
	_init = true;  //标志已初始化
	return 0;
}
unsigned CActUnit::GetTotalCharge(void)
{
	unsigned total_charge = 0;
	Json::Value user_flag;
	Json::FromString(user_flag, _user.user_flag);
	if (user_flag.isMember("chgs") && user_flag["chgs"].isArray()){
		for(unsigned i=0; i<user_flag["chgs"].size(); ++i){
			unsigned charge_ts = 0;
			Json::GetUInt(user_flag["chgs"][i], 0u, charge_ts);
			if (charge_ts>=_act_time.StartTS() && _act_time.EndTS()>=charge_ts){
				total_charge += user_flag["chgs"][i][1u].asUInt();
			}
		}
	}
	return total_charge;
}
unsigned CActUnit::GetDailyCharge(void)
{
	Json::Value user_flag;
	Json::FromString(user_flag, _user.user_flag);
	if (user_flag.isMember("chgs") && user_flag["chgs"].isArray()){
		for(unsigned i=0; i<user_flag["chgs"].size(); ++i){
			unsigned charge_ts = 0;
			Json::GetUInt(user_flag["chgs"][i], 0u, charge_ts);
			if (!CTime::IsDiffDay(charge_ts, Time::GetGlobalTime())){
				return user_flag["chgs"][i][1u].asUInt();
			}
		}
	}
	return 0;
}
unsigned CActUnit::GetTotalConsume(void)
{
	unsigned total_consume = 0;
	Json::Value user_flag;
	Json::FromString(user_flag, _user.user_flag);
	if (user_flag.isMember("user_pay") && user_flag["user_pay"].isArray()){
		for(unsigned i=0; i<user_flag["user_pay"].size(); ++i){
			unsigned consume_ts = 0;
			Json::GetUInt(user_flag["user_pay"][i], 0u, consume_ts);
			if (consume_ts>=_act_time.StartTS() && _act_time.EndTS()>=consume_ts){
				total_consume += user_flag["user_pay"][i][1u].asUInt();
			}
		}
	}
	return total_consume;
}
unsigned CActUnit::GetDailyConsume(void)
{
	Json::Value user_flag;
	Json::FromString(user_flag, _user.user_flag);
	if (user_flag.isMember("user_pay") && user_flag["user_pay"].isArray()){
		for(unsigned i=0; i<user_flag["user_pay"].size(); ++i){
			unsigned consume_ts = 0;
			Json::GetUInt(user_flag["user_pay"][i], 0u, consume_ts);
			if (!CTime::IsDiffDay(consume_ts, Time::GetGlobalTime())){
				return user_flag["user_pay"][i][1u].asUInt();
			}
		}
	}
	return 0;
}
bool CActUnit::CheckActTime(void){
	//unsigned now_ts = Time::GetGlobalTime();
	//return (_act_time.end_ts + _act_time.veiw_delay >= now_ts && now_ts >= _act_time.start_ts);
	ActInfoConfig actconfig(_act_time_name);
	return _act_time.IsActive();
}
bool CActUnit::CheckVersion(void) {
	ActInfoConfig actconfig(_act_time_name);
	if (_new_act.isMember("v") && _new_act["v"].isInt()){
		return actconfig.Version() == _new_act["v"].asUInt();
	}
	return false;
}

int CActTouZiDaFanLi::Process(const Json::Value &data, unsigned type)
{
	int ret = GetNewAct();
	if (ret)
		return ret;
	switch (type) {
		case ACT_TOUZI_DAFALI_PROCESS_TOUZI:
			ret = touzi(data["id"].asUInt(),data["money"].asUInt());
			break;
		case ACT_TOUZI_DAFALI_PROCESS_LINGQU:
			ret = lingqu(data["id"].asUInt());
			break;
		case ACT_TOUZI_DAFALI_PROCESS_DUIHUAN:
			ret = duihuan(data["id"].asUInt());
			break;
		case ACT_TOUZI_DAFALI_PROCESS_YIJIANLINGQU:
			ret = yijianlingqu();
			break;
		default:
			return R_ERR_PARAM;
	}
	if (ret)
		return ret;
	ret = SaveNewAct();
	if (ret)
		return ret;
	return 0;
}

int CActTouZiDaFanLi::touzi(unsigned id, unsigned money)
{
	if (!id || id>=XML_TOUZIFANLI_POOL_NUM )
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	int tot_point = GetChongZhiPoint();
	int now_point = GetNowPoint();
	if (now_point + money > tot_point)
	{
		LOGIC_ERROR_RETURN_MSG("money_limit");
	}
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLTouZiDaFanLi config;
	int ret = dataXML->GetTouZiDaFanLiReward(config);
	if (ret)
	{
		return ret;
	}

	unsigned limit = config.touzi[id-1].integral[2];
	Json::Value * tmp = NULL;
	GetNewActIndex(id,tmp);

	if (tmp->asUInt() + money > limit)
	{
		LOGIC_ERROR_RETURN_MSG("point_limit");
	}
	*tmp = tmp->asUInt() + money;

	return 0;
}

int CActTouZiDaFanLi::lingqu(unsigned id)
{
	if (!id || id>(XML_TOUZIFANLI_POOL_NUM-1)*3 )
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLTouZiDaFanLi config;
	int ret = dataXML->GetTouZiDaFanLiReward(config);
	if (ret)
	{
		return ret;
	}

	string s;
	s = _new_act["a"].asString();

	ret = CheckLingQu(s, config, id);
	if (ret)
		return ret;

	s[id-1] = '1';
	debug_log("s=%s",s.c_str());
	_new_act["a"] = s;
	string code = "TouZiDaFanLi_lingqu_"+CTrans::ITOS(id);
	ret = ParseSimpleReward(&(config.touzi[(id-1)/3].reward[(id-1)%3]), 1, code);
	if (ret){
		return ret;
	}
	return 0;
}

int CActTouZiDaFanLi::yijianlingqu()
{
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLTouZiDaFanLi config;
	int ret = dataXML->GetTouZiDaFanLiReward(config);
	if (ret)
	{
		return ret;
	}

	string s;
	s = _new_act["a"].asString();
	XMLActSimpleReward reward[100];
	int num = 0;
	for (unsigned id = 1; id<=(XML_TOUZIFANLI_POOL_NUM-1)*3; id++)
	{
		ret = CheckLingQu(s, config, id);
		if (ret)
			continue;
		memcpy(&(reward[num++]),&(config.touzi[(id-1)/3].reward[(id-1)%3]),sizeof(XMLActSimpleReward));
		s[id-1] = '1';
	}

	_new_act["a"] = s;
	string code = "TouZiDaFanLi_yijianlingqu";
	ret = ParseSimpleReward(reward, num, code);
	if (ret){
		return ret;
	}
	return 0;
}

int CActTouZiDaFanLi::CheckLingQu(const string & s,const DataXMLTouZiDaFanLi & config, unsigned id)
{
	if (s[id-1] > '0')
	{
		LOGIC_ERROR_RETURN_MSG("has_got");
	}
	unsigned limit = config.touzi[(id-1)/3].integral[(id-1)%3];
	Json::Value * tmp = NULL;
	GetNewActIndex((id-1)/3+1,tmp);
	if (tmp->asUInt() < limit)
	{
		LOGIC_ERROR_RETURN_MSG("lack_point");
	}
	return 0;
}

int CActTouZiDaFanLi::duihuan(unsigned id)
{
	if (!id || id >XML_TOUZIFANLI_DUIHUAN_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	int tot_point = GetChongZhiPoint();
	int now_point = GetNowPoint();
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLTouZiDaFanLi config;
	int ret = dataXML->GetTouZiDaFanLiReward(config);
	if (ret)
	{
		return ret;
	}
	if (now_point + config.duihuan[id-1].sum > tot_point)
	{
		LOGIC_ERROR_RETURN_MSG("point_limit");
	}
	_new_act_3["c"] = _new_act_3["c"].asUInt() + config.duihuan[id-1].sum;
	string code = "TouZiDaFanLi_duihuan_"+CTrans::ITOS(id);
	ret = ParseSimpleReward(config.duihuan[id-1].reward, 1, code);
	if (ret){
		return ret;
	}
	return 0;
}

int CActTouZiDaFanLi::GetNowPoint()
{
	int now_point = 0;
	for (unsigned i=0;i<_new_act_2["b"].size();i++)
		now_point += _new_act_2["b"][i].asUInt();
	for (unsigned i=0;i<_new_act_3["b"].size();i++)
		now_point += _new_act_3["b"][i].asUInt();
	now_point += _new_act_3["c"].asUInt();
	return now_point;
}

void CActTouZiDaFanLi::GetNewActIndex(unsigned id, Json::Value *& wh)
{
	if (id <= XML_TOUZIFANLI_POOL_NUM/2)
		wh = &(_new_act_2["b"][id-1]);
	else
		wh = &(_new_act_3["b"][id-XML_TOUZIFANLI_POOL_NUM/2-1]);
}

int CActTouZiDaFanLi::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_TOUZIDAFANLI_ACT_NUM_1, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_TOUZIDAFANLI_ACT_NUM_2, _new_act_2);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_TOUZIDAFANLI_ACT_NUM_3, _new_act_3);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (!CheckVersion())
	{
		_new_act["v"] = _act_time.Version();
		_new_act["id"] = ACTIVITY_TOUZIDAFANLI_ACT_NUM_1;
		string a;
		for (unsigned i=0;i<(XML_TOUZIFANLI_POOL_NUM-1)*3;i++)
			a.push_back('0');
		_new_act["a"] = a;
		_new_act_2["id"] = ACTIVITY_TOUZIDAFANLI_ACT_NUM_2;
		_new_act_2["b"] = Json::Value(Json::arrayValue);
		for (unsigned i=0;i<XML_TOUZIFANLI_POOL_NUM/2;i++)
			_new_act_2["b"].append(0);
		_new_act_3["id"] = ACTIVITY_TOUZIDAFANLI_ACT_NUM_3;
		_new_act_3["b"] = Json::Value(Json::arrayValue);
		for (unsigned i=XML_TOUZIFANLI_POOL_NUM/2;i<XML_TOUZIFANLI_POOL_NUM-1;i++)
			_new_act_3["b"].append(0);
		_new_act_3["c"] = 0;
	}
	return 0;
}

int CActTouZiDaFanLi::GetResult(Json::Value &result){
	result["newAct"] = _new_act;
	result["newAct2"] = _new_act_2;
	result["newAct3"] = _new_act_3;
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	if (!_hero.empty()){
		result["hero"] = _hero;
	}
	return 0;
}

int CActTouZiDaFanLi::SaveNewAct(void)
{
	if (_new_act.empty() || _new_act_2.empty() || _new_act_3.empty()){
		return R_ERR_LOGIC;
	}
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(_uid, _new_act);
	if (ret){
		return ret;
	}
	ret = logicSecinc.SetOneSecinc(_uid, _new_act_2);
	if (ret){
		return ret;
	}
	ret = logicSecinc.SetOneSecinc(_uid, _new_act_3);
	if (ret){
		return ret;
	}
	return ret;
}

int CActTouZiDaFanLi:: GetChongZhiPoint()
{
	int tot = GetTotalCharge();
	if (tot > 180000)
		tot = 180000;
	return tot;
}

int CActGuYu::Process(const Json::Value &data, unsigned type)
{
	int ret = GetNewAct();
	if (ret)
		return ret;
	switch (type) {
		case ACT_GUYU_PROCESS_ONLINE:
			ret = online();
			break;
		case ACT_GUYU_PROCESS_JIFEN:
			ret = jifen(data["id"].asUInt());
			break;
		case ACT_GUYU_PROCESS_MEIRI:
			ret = meiri(data["id"].asUInt());
			break;
		case ACT_GUYU_PROCESS_JINJIE_DIAMOND:
			ret = diamond();
			break;
		case ACT_GUYU_PROCESS_JINJIE_HUANYU:
			ret = huanyu();
			break;
		default:
			return R_ERR_PARAM;
	}
	if (ret)
		return ret;
	return 0;
}

int CActGuYu::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_GUYU_JIFEN, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (ret==R_ERR_NO_DATA || !Time::IsToday(_new_act["ts"].asUInt()))
	{
		_new_act["ts"] = Time::GetGlobalTime();
		_new_act["id"] = ACTIVITY_GUYU_JIFEN;

		_new_act["a"] = Json::Value(Json::arrayValue);
		for (unsigned i=0;i<MAX_GUYU_JIFEN_ITEM_NUM;i++)
			_new_act["a"].append(0);

		_new_act["j"] = 0;
	}

	ret = logicSecinc.GetSecinc(_uid, NAT_CONFIG_guyv_meiri, _new_act_2);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (ret==R_ERR_NO_DATA || !Time::IsToday(_new_act_2["ts"].asUInt()))
	{
		_new_act_2["id"] = NAT_CONFIG_guyv_meiri;
		_new_act_2["ts"] = Time::GetGlobalTime();
		DataXMLGuYu config;
		CDataXML *pDataXML = CDataXML::GetCDataXML();
		if(!pDataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}
		ret = pDataXML->GetGuYuReward(config);
		if (ret)
		{
			return ret;
		}
		unsigned pass_day = (Time::GetGlobalTime() -  _act_time.StartTS())/86400+1;
		int num = 0;
		for (unsigned i=0;i<MAX_GUYU_MEIRI_ITEM_NUM;i++)
			if (config.meiri[i].id / 10 == pass_day)
				num++;
		_new_act_2["a"] = Json::Value(Json::arrayValue);
		for (unsigned i=0;i<num;i++)
			_new_act_2["a"].append(0);
	}

	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_GUYU_JINJIE, _new_act_3);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (ret == R_ERR_NO_DATA || !Time::IsToday(_new_act_3["ts"].asUInt()))
	{
		_new_act_3["id"] = ACTIVITY_GUYU_JINJIE;
		_new_act_3["ts"] = Time::GetGlobalTime();
		_new_act_3["a"] = Json::Value(Json::arrayValue);
		_new_act_3["b"] = Json::Value(Json::arrayValue);
		_new_act_3["c"] = 0;

		for (unsigned i = 0; i < MAX_GUYU_JINJIE_DIAMOND;++i)
			_new_act_3["a"].append(0);

		for(unsigned i = 0;i < MAX_GUYU_JINJIE_HUANYU;++i)
			_new_act_3["b"].append(0);
	}
	return 0;
}

int CActGuYu::GetResult(Json::Value &result){
	result["newAct"] = _new_act;
	result["newAct2"] = _new_act_2;
	result["newAct3"] = _new_act_3;
	result["onlinets"] = _user.ext;
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	if (!_hero.empty()){
		result["hero"] = _hero;
	}
	return 0;
}

int CActGuYu::online()
{
	DataXMLGuYu config;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int ret = pDataXML->GetGuYuReward(config);
	if (ret)
	{
		return ret;
	}

	if(Time::IsToday(_new_act["ts2"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("today_has_got");
	}

	if (CTime::GetDayInterval(_user.last_active_time, Time::GetGlobalTime()) == 0)
	{
		//如果在线时长达标并且未领取
		if(_user.ext >= 30)
		{
			_new_act["ts2"] = Time::GetGlobalTime();  //将状态置1
			ret = SaveNewAct();
			if (ret)
				return ret;
			string code = "guyu_online";
			ret = ParseSimpleReward(config.online, MAX_GUYU_ONLINE_REWARD_NUM, code);
			if (ret){
				return ret;
			}
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("have recv or not enough time");
		}
	}
	else
	{
		PARAM_ERROR_RETURN_MSG("today not active");
	}
	return 0;
}

int CActGuYu::jifen(unsigned id)
{
	if (!id || id > MAX_GUYU_JIFEN_ITEM_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	unsigned jifen = GetTotalCharge() * 2;
	if (jifen > 20000)
		jifen = 20000;

	DataXMLGuYu config;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int ret = pDataXML->GetGuYuReward(config);
	if (ret)
	{
		return ret;
	}

	if (_new_act["j"].asUInt() + config.jifen[id-1].require > jifen)
	{
		LOGIC_ERROR_RETURN_MSG("jifen_lack");
	}

	_new_act["j"] = _new_act["j"].asUInt() + config.jifen[id-1].require;

	if (_new_act["a"][id-1].asUInt() + 1 > config.jifen[id-1].limit)
	{
		LOGIC_ERROR_RETURN_MSG("cishu_limit");
	}

	_new_act["a"][id-1] = _new_act["a"][id-1].asUInt() + 1;

	ret = SaveNewAct();
	if (ret)
		return ret;

	string code = "guyu_jifen_"+CTrans::ITOS(id);
	ret = ParseSimpleReward(config.jifen[id-1].reward, MAX_GUYU_JIFEN_REWARD_NUM, code);
	if (ret){
		return ret;
	}

	return 0;
}

int CActGuYu::meiri(unsigned id)
{
	unsigned pass_day = (Time::GetGlobalTime() -  _act_time.StartTS())/86400+1;
	if (id / 10 != pass_day)
	{
		PARAM_ERROR_RETURN_MSG("error_day_id");
	}
	DataXMLGuYu config;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int ret = pDataXML->GetGuYuReward(config);
	if (ret)
	{
		return ret;
	}
	int idx = 0;
	for (idx = 0;idx < MAX_GUYU_MEIRI_ITEM_NUM;idx++)
		if (config.meiri[idx].id == id)
			break;
	if (idx == MAX_GUYU_MEIRI_ITEM_NUM) {
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (config.meiri[idx].id != id) {
		PARAM_ERROR_RETURN_MSG("id");
	}

	if (_new_act_2["a"][id%10].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("reward_has_got");
	}

	if (GetDailyCharge() < config.meiri[idx].require)
	{
		LOGIC_ERROR_RETURN_MSG("lack_charge");
	}

	_new_act_2["a"][id%10] = 1;

	ret = SaveNewAct();
	if (ret)
		return ret;

	string code = "guyu_meiri_"+CTrans::ITOS(id);
	ret = ParseSimpleReward(config.meiri[idx].reward, MAX_GUYU_MEIRI_REWARD_NUM, code);
	if (ret){
		return ret;
	}

	return 0;
}

int CActGuYu::diamond()
{
	DataXMLGuYuJinJie config;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML of diamond fail");
		return R_ERR_DB;
	}

	int ret = pDataXML->GetGuYuJinJieReward(config);
	if (ret)
	{
		return ret;
	}

	unsigned daily = GetDailyConsume();  
	unsigned flag = 0;
	XMLActSimpleReward rewardArray[MAX_GUYU_JINJIE_DIAMOND];

	for(unsigned i = 0,j = 0; i < MAX_GUYU_JINJIE_DIAMOND && j < MAX_GUYU_JINJIE_DIAMOND;++i)
	{
		if(daily >= config.diamond[i].require && _new_act_3["a"][i].asUInt() == 0)
		{
			_new_act_3["a"][i] = 1;  //领取标志
			rewardArray[j].id = config.diamond[i].reward[0].id;
			rewardArray[j].count = config.diamond[i].reward[0].count;
			++j;
			flag = 1;
		}
	}

	ret = SaveNewAct();
	if (ret)
	{
		return ret;
	}
	
	if(flag == 1)
	{
		string code = "618jinjie";
		ret = ParseSimpleReward(rewardArray, MAX_GUYU_JINJIE_DIAMOND, code);
		if(ret)
		{
			return ret;
		}
	}

	return 0;
}

int CActGuYu::sumHuanyu(int num)
{
	//_act_time.init(ACTIVITY_TIME_GUYU);
	if(CheckActTime() == false)
	{
		return 1;
	}
	int ret = GetNewAct();
	if(ret)
	{
		return ret;
	}
	_new_act_3["c"] = _new_act_3["c"].asUInt() + num;
	ret = SaveNewAct();
	if(ret)
	{
		return ret;
	}

	return 0;
}

int CActGuYu::huanyu()
{	
	DataXMLGuYuJinJie config;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML of huanyu failed");
		return R_ERR_DB;
	}

	int ret = pDataXML->GetGuYuJinJieReward(config);
	if (ret)
	{
		return ret;
	}

	unsigned daily = _new_act_3["c"].asUInt();
	unsigned flag = 0;
	XMLActSimpleReward rewardArray[MAX_GUYU_JINJIE_HUANYU];

	for(unsigned i = 0,j = 0; i < MAX_GUYU_JINJIE_HUANYU && j < MAX_GUYU_JINJIE_HUANYU;++i)
	{
		if(daily >= config.huanyu[i].require && _new_act_3["b"][i].asUInt() == 0)
		{
			_new_act_3["b"][i] = 1;  //领取标志
			rewardArray[j].id = config.huanyu[i].reward[0].id;
			rewardArray[j].count = config.huanyu[i].reward[0].count;
			++j;

			flag = 1;
		}
	}

	ret = SaveNewAct();
	if (ret)
	{
		return ret;
	}

	if(flag == 1)
	{
		string code = "618jinjie";
		ret = ParseSimpleReward(rewardArray, MAX_GUYU_JINJIE_HUANYU, code);
		if(ret)
		{
			return ret;
		}
	
	}

	return 0;
}

//存档
int CActGuYu::SaveNewAct(void)
{
	if (_new_act.empty() || _new_act_2.empty() || _new_act_3.empty()){
		return R_ERR_LOGIC;
	}
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(_uid, _new_act);
	if (ret){
		return ret;
	}
	ret = logicSecinc.SetOneSecinc(_uid, _new_act_2);
	if (ret){
		return ret;
	}
	ret = logicSecinc.SetOneSecinc(_uid,_new_act_3);
	if(ret)
	{
		return ret;
	}
	return ret;
}

int CActchildrenDaysActivity::initconfig()
{
	CDataXML *dataXML = CDataXML::GetCDataXML();  //用于调用下面的Getchildren
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int ret = dataXML->GetchildrenDaysActivityReward(_config);  //从共享内存中获取XML中的商品信息赋值给_config
	if (ret)
	{
		return ret;
	}
	return 0;
}

int CActchildrenDaysActivity::Process(const Json::Value &data, unsigned type)
{
	int ret = initconfig();
	if (ret)
		return ret;
	ret = GetNewAct();
	if (ret)
		return ret;
	switch (type) {
		case ACT_CHILDRENDAT_PROCESS_GET:
			SaveNewAct();
			break;
		case ACT_CHILDRENDAT_PROCESS_LINGQU:
			ret = lingqu(data["count"].asUInt());
			break;
		case ACT_CHILDRENDAT_PROCESS_DUIHUAN:
			ret = duihuan(data["id"].asUInt());
			break;
		default:
			return R_ERR_PARAM;
	}
	if (ret)
		return ret;
	return 0;
}

int CActchildrenDaysActivity::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, NAT_CONFIG_childrenDaysActivity, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (!CheckVersion())
	{
		_new_act["id"] = NAT_CONFIG_childrenDaysActivity;
		_new_act["v"] = _act_time.Version();
		_new_act["a"] = 0;
		int len = 0;
		for (int i=0;i<XML_ERTONGJIEHUODONG_MAX_NUM;i++)
			if (_config.item[i].id)
				len++;  //物品个数
		_new_act["b"] = Json::Value(Json::arrayValue); //每个物品的times赋为0
		for (int i=0;i<len;i++)
			_new_act["b"].append(0);
	}

	return 0;
}

unsigned CActchildrenDaysActivity::GetTotalCharge(void)
{
	unsigned totalPay = 0;
	CLogicPay logicPay;
	logicPay.GetPayHistory(_uid, _act_time.StartTS(), _act_time.EndTS(), totalPay);
	return totalPay;
}

int CActchildrenDaysActivity::lingqu(unsigned count)
{
	unsigned target_count = _new_act["a"].asUInt() + count;
	if (target_count > 2000 || target_count > GetTotalCharge() / 100)
	{
		LOGIC_ERROR_RETURN_MSG("领取次数超过限制");
	}
	_new_act["a"] = _new_act["a"].asUInt() + count;
	int ret = SaveNewAct();
	if (ret)
		return ret;

	string code = "childrenDaysActivity_lingqu";
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(_uid,10327,count,code,_equip,true,0,0,_act_time.EndTS()-Time::GetGlobalTime());
	if (ret){
		return ret;
	}

	return 0;
}

int CActchildrenDaysActivity::duihuan(unsigned id)
{
	if (!id || id > XML_ERTONGJIEHUODONG_MAX_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	CLogicEquipment logicEquipment;
	Json::Value all_equipment;
	int ret = logicEquipment.GetEquipment(_uid, 0, all_equipment); //从数据库获取该玩家的装备信息（个数、什么装备）
	//all_equipment是从一个vector中一个一个的赋值的,见CLogicEquipment::GetEquipment
	if (ret){
		return ret;
	}

	if (_config.item[id-1].times && _new_act["b"][id-1].asUInt()>=_config.item[id-1].times)
	{
		LOGIC_ERROR_RETURN_MSG("超过兑换次数限制");
	}

	map<int,pair<unsigned, unsigned> > ud_map;
	ud_map.clear();
	for (int j=0; j<XML_ERTONGJIEHUODONG_DUIHUAN_NUM; ++j){
		if (_config.item[id-1].needNum[j] == 0){
			continue;
		}
		bool find = false;
		for (unsigned i=0; i<all_equipment.size(); ++i){
			int eqid = 0;
			Json::GetInt(all_equipment[i], "id", eqid);
			unsigned ud = 0;
			Json::GetUInt(all_equipment[i], "ud", ud);
			unsigned count = 0;  //玩家有该字帖的个数
			Json::GetUInt(all_equipment[i], "count", count);
			if (_config.item[id-1].need[j] == eqid && count >= _config.item[id-1].needNum[j]){
				ud_map[eqid].first = ud;
				ud_map[eqid].second = _config.item[id-1].needNum[j];
				find = true;
				break;
			}
		}
		if (!find){
			error_log("[need error][uid=%u,eqid=%d]", _uid, _config.item[id-1].need[j]);
			LOGIC_ERROR_RETURN_MSG("need_error");
		}
	}

	_new_act["b"][id-1] = _new_act["b"][id-1].asUInt() + 1;  //兑换次数加1
	ret = SaveNewAct();  // 修改后的信息存入数据库
	if (ret)
		return ret;

	string code = "childrenDaysActivity_duihuan";
	for (map<int,pair<unsigned, unsigned> >::iterator itr=ud_map.begin(); itr!=ud_map.end(); ++itr){
		int count = 0;
		ret = logicEquipment.UseEquipmentEx(_uid, itr->first, (itr->second).first, (itr->second).second, code, count);
		if (ret){
			return ret;
		}

		Json::Value temp;
		temp["id"] = itr->first;
		temp["c"] = count;
		jsoncount.append(temp);

	}

	ret = ParseSimpleReward(_config.item[id-1].reward, XML_ERTONGJIEHUODONG_REWARD_NUM, code);
	if (ret){
		return ret;
	}
	return 0;
}

int CActchildrenDaysActivity::GetResult(Json::Value &result){
	result["newAct"] = _new_act;
	result["chargeCount"] = GetTotalCharge();
	result["rewardCount"] = _new_act["a"].asUInt();
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	result["count"] = jsoncount;
	return 0;
}


int CActXingshiPoints::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_STONE_JIFEN, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	
	if (ret == R_ERR_NO_DATA || !Time::IsToday(_new_act["ts"].asUInt()))
	{
		_new_act["ts"] = Time::GetGlobalTime();
		_new_act["id"] = ACTIVITY_STONE_JIFEN;

		_new_act["a"] = Json::Value(Json::arrayValue);
		for (unsigned i = 0;i < MAX_XINGSHI_ITEM_NUM;i++)
			_new_act["a"].append(0);

		_new_act["b"] = 0;  //当日使用积分数
	}
	return 0;
}

int CActXingshiPoints::GetResult(Json::Value &result)
{
	result["newAct"] = _new_act;
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	return 0;
}

int CActXingshiPoints::GetStoneGrade()
{
	int ret = 0;
	Json::Value tech;
	Json::Reader reader;
	reader.parse(_user.user_tech,tech);
	if(!tech.isMember("godS"))
	{
		LOGIC_ERROR_RETURN_MSG("godS lose");
	}

	unsigned row = tech["godS"].size();
	unsigned con = tech["godS"][0u].size();
	unsigned totalGrade = 0;
	CLogicEquipment logicEquipment;
	for(unsigned i = 0; i < row; ++i)   //根据ud获取id来计算星石等级
	{
		for(unsigned j = 0; j < con;++j)
		{
			if(tech["godS"][i][j].asInt() > 0)
			{
				Json::Value data;
				ret = logicEquipment.Get(_uid,tech["godS"][i][j].asUInt(),data);
				if(ret)
				{
					LOGIC_ERROR_RETURN_MSG("Get equipment failed");
				}
				
				if(data["id"].asUInt() >= 6601 && data["id"].asUInt() <= 6612) //星石id范围
				{
					totalGrade += data["id"].asUInt() % 100;
				}
			}
		}
	}
	return totalGrade;
}

int CActXingshiPoints::Process(const Json::Value &data, unsigned type)
{
	int ret = GetNewAct();
	if(ret)
	{
		error_log("GetNewAct error");
		return ret;
	}

	unsigned id = data["id"].asUInt() - 1; 
	if(id < 0 || id >= MAX_XINGSHI_ITEM_NUM)
	{
		LOGIC_ERROR_RETURN_MSG("index error");
	}
	unsigned chge_count = data["count"].asUInt();  //一次兑换个数
	if(chge_count < 1)
	{
		LOGIC_ERROR_RETURN_MSG("count error");
	}

	DataXMLXingshiPoints config;
	CDataXML *pdataXML = CDataXML::GetCDataXML();
	if(pdataXML == NULL)
	{
		error_log("GetInitXML Process error");
		return R_ERR_DB;
	}
	ret = pdataXML->GetXingshiPointsReward(config);
	if(ret)
	{
		return ret;
	}

	CLogicEquipment logicEquipment;
	unsigned dailyCharge = GetDailyCharge() - _new_act["b"].asUInt();  //充一钻石一积分
	string reason = "";
	XMLActSimpleReward rewardArray;
	bool flag = false;
	if(dailyCharge >= config.stone[id].points * chge_count && _new_act["a"][id].asUInt() < config.stone[id].times)
	{
		unsigned grade = config.stone[id].grade == 0 ? 0 : GetStoneGrade(); //星石等级要求为0的不用再计算
		if(grade >= config.stone[id].grade)
		{
			//XMLActSimpleReward rewardArray;
			rewardArray.id = config.stone[id].reward[0].id;
			rewardArray.count = chge_count;
			reason = "xingshijifen_" + CTrans::UTOS(id);
			_new_act["a"][id] = _new_act["a"][id].asUInt() + chge_count; //相应位置兑换的次数
			_new_act["b"] = _new_act["b"].asUInt() + config.stone[id].points * chge_count;
			flag = true;
		}
	}

	ret = SaveNewAct();
	if(ret)
	{
		error_log("SaveNewAct error");
		return ret;
	}

	if(flag)
	{
		ret = ParseSimpleReward(&rewardArray, MAX_XINGSHI_REWARD_NUM, reason);
		if (ret)
		{
			return ret;
		}
	}

	return 0;
}

int CActWuYiQingDian::Process(const Json::Value &data, unsigned type)
{
	int ret = initconfig();
	if (ret)
		return ret;
	ret = GetNewAct();
	if (ret)
		return ret;
	switch (type) {
		case ACT_WUYIQINGDIAN_PROCESS_MEIRI:
			ret = meiri(data["id"].asUInt());
			break;
		case ACT_WUYIQINGDIAN_PROCESS_JIFEN:
			ret = jifen(data["id"].asUInt());
			break;
		default:
			return R_ERR_PARAM;
	}
	if (ret)
		return ret;
	return 0;
}

int CActWuYiQingDian::initconfig()
{
	CDataXML *pdataXML = CDataXML::GetCDataXML();
	if(pdataXML == NULL)
	{
		error_log("GetInitXML Process error");
		return R_ERR_DB;
	}
	int ret = pdataXML->GetWuYiQingDianReward(_config);
	if (ret)
	{
		return ret;
	}

	return 0;
}

int CActWuYiQingDian::get_pass_day()
{
	return  (Time::GetGlobalTime() -  _act_time.StartTS())/86400;
}

unsigned CActWuYiQingDian::get_meiri_item_num(unsigned idx)
{
	unsigned num = 0;
	for (int i=0;i<MAX_WUYIQINGDIAN_MEIRI_ITEM_NUM;i++)
		if (_config.meiri[idx][i].id)
			num++;
	return num;
}

int CActWuYiQingDian::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_WUYIQINGDIAN_MEIRI, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (ret==R_ERR_NO_DATA || !Time::IsToday(_new_act["ts"].asUInt()))
	{
		_new_act["ts"] = Time::GetGlobalTime();
		_new_act["id"] = ACTIVITY_WUYIQINGDIAN_MEIRI;

		_new_act["a"] = Json::Value(Json::arrayValue);
		unsigned item_num = get_meiri_item_num(get_pass_day());
		for (unsigned i=0;i<item_num;i++)
			_new_act["a"].append(0);
	}

	if (!CheckVersion())
	{
		_new_act["v"] = _act_time.Version();
		_new_act["id"] = ACTIVITY_WUYIQINGDIAN_MEIRI;
		_new_act["b"] = Json::Value(Json::arrayValue);
		for (unsigned i=0;i<MAX_WUYIQINGDIAN_JIFEN_ITEM_NUM;i++)
			_new_act["b"].append(0);
	}
	return 0;
}

int CActWuYiQingDian::meiri(unsigned id)
{
	unsigned daily_charge = GetDailyCharge();
	unsigned pass_day = get_pass_day();
	unsigned item_num = get_meiri_item_num(pass_day);
	if (!id || id>item_num)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (daily_charge < _config.meiri[pass_day][id-1].require)
	{
		LOGIC_ERROR_RETURN_MSG("charge_not_enough");
	}
	if (_new_act["a"][id-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("today_has_got");
	}
	_new_act["a"][id-1] = 1;
	int ret = SaveNewAct();
	if (ret)
		return ret;
	string code = "wuyiqingdian_meiri_"+CTrans::ITOS(id);
	ret = ParseSimpleReward(_config.meiri[pass_day][id-1].reward, MAX_WUYIQINGDIAN_MEIRI_REWARD_NUM, code);
	if (ret){
		return ret;
	}
	return 0;
}

int CActWuYiQingDian::jifen(unsigned id)
{
	if (!id || id > MAX_WUYIQINGDIAN_JIFEN_ITEM_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	unsigned total_charge = GetTotalCharge();
	string code = "wuyiqingdian_shop_"+CTrans::ITOS(id);
	int limitmax = 0;
	limitmax = total_charge / _config.limit[0].require * _config.limit[0].id;
	if (limitmax > _config.limit[0].limitmax)
		limitmax = _config.limit[0].limitmax;
	if (_new_act["b"][id-1].asUInt() >= limitmax)
	{
		LOGIC_ERROR_RETURN_MSG("limitmax");
	}
	int ret = ChangePay(-_config.jifen[id-1].require,0,code);
	if (ret)
		return ret;
	ret = ParseSimpleReward(_config.jifen[id-1].reward, MAX_WUYIQINGDIAN_JIFEN_REWARD_NUM, code);
	if (ret){
		return ret;
	}
	_new_act["b"][id-1] = _new_act["b"][id-1].asUInt() + 1;
	ret = SaveNewAct();
	if (ret)
		return ret;
	return 0;
}

int CActWuYiQingDian::GetResult(Json::Value &result){
	result["newAct"] = _new_act;
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	if (!_hero.empty()){
		result["hero"] = _hero;
	}
	if (_coins > 0){
		result["coins"] = _coins;
	}
	if (_cash > 0){
		result["coins2"] = _cash;
	}
	return 0;
}

int CActyongguansanjun::initconfig()
{
	CDataXML *pdataXML = CDataXML::GetCDataXML();
	if(pdataXML == NULL)
	{
		error_log("GetInitXML Process error");
		return R_ERR_DB;
	}
	int ret = pdataXML->Getyongguansanjun_goumaiReward(_config);
	if (ret)
	{
		return ret;
	}
	_non_zero = 0;
	for (int i=0;i<XML_KUANGHUAN618_ITEM_NUM;i++)
		if (_config.item[i].id)
			_non_zero++;
	return 0;
}

int CActyongguansanjun::Process(const Json::Value &data, unsigned type)
{
	int ret = initconfig();
	if (ret)
		return ret;
	ret = GetNewAct();
	if (ret)
		return ret;

	unsigned id = data["id"].asUInt();
	if (!id || id > _non_zero) {
		PARAM_ERROR_RETURN_MSG("id");
	}

	if (_new_act["b"][id-1].asUInt()) {
		LOGIC_ERROR_RETURN_MSG("reward_has_got");
	}

	if (GetTotalCharge() < _config.item[id-1].require) {
		LOGIC_ERROR_RETURN_MSG("charge_not_enough");
	}

	_new_act["b"][id-1] = 1;

	string code = "yongguansanjun";
	ret = ChangePay(-_config.item[id-1].price, 0, code);
	if (ret){
		return ret;
	}

	ret = ParseSimpleReward(_config.item[id-1].reward, XML_KUANGHUAN618_REWARD_NUM, code);
	if (ret){
		return ret;
	}

	ret = SaveNewAct();
	if (ret)
		return ret;
	return 0;
}

bool CActyongguansanjun::CheckVersion(void) {
	if (_new_act.isMember("v2") && _new_act["v2"].isInt()){
		//debug_log("version=%d,v=%d",_act_time.version,_new_act["v"].asUInt());
		return _act_time.Version() == _new_act["v2"].asUInt();
	}
	return false;
}

int CActyongguansanjun::GetNewAct()
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, NAT_CONFIG_yongguansanjun, _new_act);
	if(ret!=0&&ret!=R_ERR_NO_DATA){
		return ret;
	}
	if (!CheckVersion())
	{
		_new_act["id"] = NAT_CONFIG_yongguansanjun;
		_new_act["v2"] = _act_time.Version();
		_new_act["b"] = Json::Value(Json::arrayValue);
		for (int i=0;i<_non_zero;i++)
			_new_act["b"].append(0);

	}

	return 0;
}

int CActyongguansanjun::GetResult(Json::Value &result){
	result["newAct"] = _new_act;
	if (!_equip.empty()){
		result["equipment"] = _equip;
	}
	if (_coins > 0){
		result["coins"] = _coins;
	}
	if (_cash > 0){
		result["coins2"] = _cash;
	}
	return 0;
}

int CActQunXing::Process(const Json::Value &data, unsigned type) {
	unsigned id = 0;
	Json::GetUInt(data, "id", id);
	Json::GetUInt(data, "type", type);
	int ret = 0;
	switch(type) {
	case ACT_QUNXING_DAILY:
		ret = Daily(id);
		break;
	case ACT_QUNXING_TOTAL:
		ret = Total(id);
		break;
	case ACT_QUNXING_JINDU:
		ret = Jindu(id);
		break;
	default:
		ret = R_ERR_PARAM;
	}
	return ret;
}
int CActQunXing::GetNewAct(void) {
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, NAT_ACT_QUNXINGHUIJU, _new_act);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		return ret;
	}
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (!CheckVersion()) {
		_new_act["id"] = NAT_ACT_QUNXINGHUIJU;
		_new_act["ts"] = Time::GetGlobalTime();
		_new_act["v"] = _act_time.Version();
		_new_act["a"] = Json::Value(Json::arrayValue);
		_new_act["b"] = Json::Value(Json::arrayValue);
		_new_act["e"] = Json::Value(Json::arrayValue);
		for (int i = 0; i < cfg.daily_size(); ++i) {
			_new_act["a"].append(0);
		}
		for (int i = 0; i < cfg.total_size(); ++i) {
			_new_act["b"].append(0);
		}
		for (int i = 0; i < cfg.jindu_size(); ++i) {
			_new_act["e"].append(0);
		}
		_new_act["c"] = 0;
		_new_act["d"] = 0;
	} else {
		unsigned ts = 0;
		Json::GetUInt(_new_act, "ts", ts);
		if (CTime::IsDiffDay(ts, Time::GetGlobalTime())) {
			_new_act["a"] = Json::Value(Json::arrayValue);
			_new_act["ts"] = Time::GetGlobalTime();
			for (int i = 0; i < cfg.daily_size(); ++i) {
				_new_act["a"].append(0);
			}
		}
	}
	return 0;
}
int CActQunXing::GetResult(Json::Value &result) {
	result["newAct"] = _new_act;
	if (!_equip.empty()) {
		result["equipment"] = _equip;
	}
	return 0;
}
int CActQunXing::Daily(unsigned id) {
	int ret = 0;
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (id >= cfg.daily_size()) {
		error_log("id error uid=%u id=%u max=%u", _uid, id, cfg.daily_size());
		return R_ERR_PARAM;
	}
	ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	unsigned charge = GetDailyCharge();
	if (charge < cfg.daily(id).need()) {
		error_log("charge limit uid=%u id=%u need=%u hold=%u", _uid, id, cfg.daily(id).need(), charge);
		return R_ERR_LOGIC;
	}
	unsigned flag = 0;
	Json::GetUInt(_new_act["a"], id, flag);
	if (flag != 0) {
		error_log("flag error uid=%u id=%u", _uid, id);
		return R_ERR_LOGIC;
	}
	_new_act["a"][id] = 1;
	ret = SaveNewAct();
	if (0 != ret) {
		return ret;
	}
	RewardConfig::RewardItemCfg reward;
	for (int i = 0; i < cfg.daily(id).id_size(); ++i) {
		RewardConfig::EquipItem *equip = reward.add_equips();
		equip->set_eqid(cfg.daily(id).id(i));
		equip->set_c(cfg.daily(id).count(i));
	}
	string code;
	String::Format(code, "act_qunxing_daily_%u", id);
	ret = ProvideCommonReward(reward, code, _act_time.EndTS());
	if (0 != ret) {
		return ret;
	}
	return 0;
}
int CActQunXing::Total(unsigned id) {
	int ret = 0;
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (id >= cfg.total_size()) {
		error_log("id error uid=%u id=%u max=%u", _uid, id, cfg.total_size());
		return R_ERR_PARAM;
	}
	ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	unsigned charge = GetTotalCharge() + _new_act["c"].asUInt();
	if (charge < cfg.total(id).need()) {
		error_log("charge limit uid=%u id=%u need=%u hold=%u", _uid, id, cfg.total(id).need(), charge);
		return R_ERR_LOGIC;
	}
	unsigned flag = 0;
	Json::GetUInt(_new_act["b"], id, flag);
	if (flag != 0) {
		error_log("flag error uid=%u id=%u", _uid, id);
		return R_ERR_LOGIC;
	}
	_new_act["b"][id] = 1;

	ret = SaveNewAct();
	if (0 != ret) {
		return ret;
	}
	RewardConfig::RewardItemCfg reward;
	for (int i = 0; i < cfg.total(id).id_size(); ++i) {
		RewardConfig::EquipItem *equip = reward.add_equips();
		equip->set_eqid(cfg.total(id).id(i));
		equip->set_c(cfg.total(id).count(i));
	}
	string code;
	String::Format(code, "act_qunxing_total_%u", id);
	ret = ProvideCommonReward(reward, code, _act_time.EndTS());
	if (0 != ret) {
		return ret;
	}
	return 0;
}

int CActQunXing::Jindu(unsigned id) {
	int ret = 0;
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (id >= cfg.jindu_size()) {
		error_log("id error uid=%u id=%u max=%u", _uid, id, cfg.jindu_size());
		return R_ERR_PARAM;
	}
	ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	unsigned point = 0;
	Json::GetUInt(_new_act, "d", point);
	if (point < cfg.jindu(id).need()) {
		error_log("point limit uid=%u id=%u need=%u hold=%u", _uid, id, cfg.jindu(id).need(), point);
		return R_ERR_LOGIC;
	}
	unsigned flag = 0;
	Json::GetUInt(_new_act["e"], id, flag);
	if (flag != 0) {
		error_log("flag error uid=%u id=%u", _uid, id);
		return R_ERR_LOGIC;
	}
	_new_act["e"][id] = 1;

	ret = SaveNewAct();
	if (0 != ret) {
		return ret;
	}
	RewardConfig::RewardItemCfg reward;
	for (int i = 0; i < cfg.jindu(id).id_size(); ++i) {
		RewardConfig::EquipItem *equip = reward.add_equips();
		equip->set_eqid(cfg.jindu(id).id(i));
		equip->set_c(cfg.jindu(id).count(i));
	}
	string code;
	String::Format(code, "act_qunxing_jindu_%u", id);
	ret = ProvideCommonReward(reward, code, _act_time.EndTS());
	if (0 != ret) {
		return ret;
	}
	return 0;
}

int CActQunXing::SetPoint(unsigned point) {
	int ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	unsigned curr_point = 0;
	Json::GetUInt(_new_act, "c", curr_point);
	if (curr_point >= point) {
		return 0;
	}
	_new_act["c"] = point;
	ret = SaveNewAct();
	if (0 != ret) {
		return ret;
	}
	return 0;
}

int CActQunXing::AddJinDu() {
	int ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	unsigned curr_count = 0;
	Json::GetUInt(_new_act, "d", curr_count);
	_new_act["d"] = curr_count + 1;
	ret = SaveNewAct();
	if (0 != ret) {
		return ret;
	}
	return 0;
}

int CActQunXing::GetInfo(Json::Value &result) {
	int ret = GetNewAct();
	if (0 != ret) {
		return ret;
	}
	result["newAct"] = _new_act;
	return 0;
}

int CActQiTianJinJie::Process(const Json::Value &data, unsigned type) {
	int ret = initconfig();
	if (ret) {
		return ret;
	}
	_idx_zone = -1;
	for (int i = 0; i < MAX_QITIANJINJIE_MEIRI_ZONE_NUM; ++i) {
		if (_config.zone[i].start <= _serverid && _serverid <= _config.zone[i].end) {
			_idx_zone = i;
			break;
		}
	}
	if (_idx_zone == -1) {
		error_log("_serverid=%u", _serverid);
		LOGIC_ERROR_RETURN_MSG("config_error");
	}
	ret = GetNewAct();
	if (ret) {
		return ret;
	}
	ret = meiri(data["id"].asUInt());
	if (ret) {
		return ret;
	}
	return 0;
}
int CActQiTianJinJie::initconfig()
{
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML) {
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int ret = dataXML->GetQiTianJinJieReward(_config);
	if (ret) {
		return ret;
	}
	return 0;
}
int CActQiTianJinJie::get_pass_day() {
	return Math::Abs(CTime::GetDayInterval(Time::GetGlobalTime(), _act_time.StartTS()));
}
unsigned CActQiTianJinJie::get_meiri_item_num(unsigned idx) {
	if (idx >= MAX_QITIANJINJIE_MEIRI_DAY_NUM) {
		idx = MAX_QITIANJINJIE_MEIRI_DAY_NUM - 1;
	}
	unsigned num = 0;
	for (int i = 0; i < MAX_QITIANJINJIE_MEIRI_ITEM_NUM; ++i) {
		if (_config.zone[_idx_zone].meiri[idx][i].id) {
			++num;
		}
	}
	return num;
}
int CActQiTianJinJie::GetNewAct() {
	int ret = 0;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(_uid, ACTIVITY_QITIANJINJIE_MEIRI, _new_act);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		return ret;
	}
	unsigned ts = 0;
	Json::GetUInt(_new_act, "ts", ts);
	if (CTime::IsDiffDay(Time::GetGlobalTime(), ts)) {
		_new_act["ts"] = Time::GetGlobalTime();
		_new_act["id"] = ACTIVITY_QITIANJINJIE_MEIRI;
		_new_act["a"] = Json::Value(Json::arrayValue);
		unsigned item_num = get_meiri_item_num(get_pass_day());
		for (unsigned i = 0; i < item_num; ++i) {
			_new_act["a"].append(0);
		}
	}
	return 0;
}
int CActQiTianJinJie::meiri(unsigned id) {
	unsigned daily_charge = GetDailyCharge();
	unsigned pass_day = get_pass_day();
	if (pass_day >= MAX_QITIANJINJIE_MEIRI_DAY_NUM) {
		pass_day = MAX_QITIANJINJIE_MEIRI_DAY_NUM - 1;
	}
	unsigned item_num = get_meiri_item_num(pass_day);
	if (!id || id > item_num) {
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (daily_charge < _config.zone[_idx_zone].meiri[pass_day][id - 1].require) {
		LOGIC_ERROR_RETURN_MSG("charge_not_enough");
	}
	if (_new_act["a"][id - 1].asUInt()) {
		LOGIC_ERROR_RETURN_MSG("today_has_got");
	}
	_new_act["a"][id - 1] = 1;
	int ret = SaveNewAct();
	if (ret) {
		return ret;
	}
	string code;
	String::Format(code, "qitianjinjie_%u_%u", pass_day, id);
	ret = ParseSimpleReward(_config.zone[_idx_zone].meiri[pass_day][id - 1].reward, MAX_QITIANJINJIE_MEIRI_REWARD_NUM, code);
	if (ret) {
		return ret;
	}
	return 0;
}
int CActQiTianJinJie::GetResult(Json::Value &result) {
	result["newAct"] = _new_act;
	if (!_equip.empty()) {
		result["equipment"] = _equip;
	}
	if (!_hero.empty()) {
		result["hero"] = _hero;
	}
	if (_coins > 0) {
		result["coins"] = _coins;
	}
	if (_cash > 0) {
		result["coins2"] = _cash;
	}
	return 0;
}
