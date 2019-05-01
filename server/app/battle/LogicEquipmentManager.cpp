#include "LogicEquipmentManager.h"


const int LogicEquipmentManager::Wing_Man_Eqids[MAX_WINGMAN_KIND] = {e_WingManID_1,e_WingManID_2,e_WingManID_3,e_WingManID_4,e_WingManID_5,e_WingManID_6,e_WingManID_7,e_WingManID_8,e_WingManID_9};

DBCEquipmentWrap::DBCEquipmentWrap(unsigned uid, unsigned equd)
	: container_(EquipmentManager::Instance())
	, data_(EquipmentManager::Instance()->GetEquipment(uid, equd, index_))
{
	if (data_.issold)
	{
		error_log("equip is already sold. uid=%u,equd=%u", uid, equd);
		throw std::runtime_error("equip_already_sold");
	}

	if (IsDressed())   //正在战斗的英雄，不能进行洗练的操作
	{
		//验证英雄
		LogicHeroManager::Instance()->VerifyHeroRecruit(uid, data_.heroid);
	}
}

bool DBCEquipmentWrap::IsDressed() const
{
	return data_.heroid > 0;
}

void DBCEquipmentWrap::UpgradeAttr()
{
	int _m = std::min((uint8_t)3, data_.star);
	for (int i = 0; i < _m; i++)
	{
		if (! IsFullLevel(i) && data_.GetAttrLvL(i) < 5)
		{
			uint8_t* lvl = data_.AttrLvL(i);
			(*lvl) += 1;
		}
	}

	//更新激活属性，包括新增激活属性
	LogicEquipmentManager::Instance()->UpdateExtraSubProperty(data_, false);

	Save();
}

bool DBCEquipmentWrap::IsFullLevel(int index) const
{
	int maxlevel = EquipCfgWrap().GetSubMaxLevel(data_.eqid);
	return  (data_.GetAttrLvL(index) >= maxlevel);
}

bool DBCEquipmentWrap::IsReachLevel(int lvl) const
{
	int _m = std::min((uint8_t)3, data_.star);
	for (int i = 0; i < _m; i++)
	{
		if (data_.GetAttrLvL(i) < lvl)
		{
			return false;
		}
	}
	return true;
}

bool DBCEquipmentWrap::IsFullLevel() const
{
	int _m = std::min((uint8_t)3, data_.star);
	for (int i = 0; i < _m; i++)
	{
		if (! IsFullLevel(i))
		{
			return false;
		}
	}

	return true;
}

void DBCEquipmentWrap::AssignAttr(int type)
{
	if (data_.star < 4)
	{
		throw std::runtime_error("star_level_not_enough");
	}

	if (type < 1 || type > 7)
	{
		throw std::runtime_error("not_valid_equip_type");
	}

	//modify @20170207 4条洗练且达到当前最高等级才可使用指定属性洗练卡
	for (int i = 0; i < 4; i++)
	{
		if (! IsFullLevel(i))
		{
			throw std::runtime_error("need_full_level");
		}
	}


	//@end modify

	for (int i = 0; i < 4; i++)
	{
		uint8_t* val = data_.AttrVal(i);
		(*val) = type;
	}
}

void DBCEquipmentWrap::Smelt(EquipSmeltType type)
{
	//获取装备信息
	if (0 == data_.star)
	{
		return ;
	}

	 //洗练已有星级下的属性
	const EquipmentConfig::Equip & equipconfig = EquipCfgWrap().GetEquip(data_.eqid);
	uint8_t configStar = equipconfig.star();   //配置的星级
	LogicEquipmentManager::Instance()->SmeltProperty(data_, configStar);   //不刷新已激活的新属性，除非属性再次相同

	//升级洗练属性
	LogicEquipmentManager::Instance()->UpgradeSubProperty(data_, type);

	//更新激活属性，包括新增激活属性
	LogicEquipmentManager::Instance()->UpdateExtraSubProperty(data_);

	//更新装备数据
	Save();

	//todo 装备洗练外部接口
	LogicEquipmentManager::Instance()->SmeltExternalInterface(data_.uid, data_.ud);
}

///////////////////////////////////////////////////////////////////
LogicEquipmentManager::LogicEquipmentManager()
{
}

int LogicEquipmentManager::EquipLoginInit(unsigned uid)
{
	//删除回购中的装备
	DelEquipmentCheck(uid);

	//获得当前uid的最大ud，然后一直增长
	EquipmentManager::Instance()->InitUserEquip(uid);

	return 0;
}

int LogicEquipmentManager::AddEquipment(unsigned uid, const VipGiftConfig::EquipReward& equip, const string& reason)
{
	return AddEquipment(uid, (unsigned)equip.eqid(), (unsigned)equip.count(), reason);
}

int LogicEquipmentManager::AddEquipment(unsigned uid, unsigned eqid, unsigned count, const string& reason)
{
	DataCommon::EquipmentAllCPP msg;
	return AddEquipment(uid, eqid, count, reason, &msg);
}

int LogicEquipmentManager::AddEquipment(unsigned uid, unsigned eqid, unsigned count, string reason, DataCommon::EquipmentAllCPP * msg)
{
	int type = EquipCfgWrap().GetEquip(eqid).type();

	DataEquipment equipment;
	equipment.uid = uid;
	equipment.eqid = eqid;

	//判断是否定制装备
	bool isSpecail = SpecialEquipConfigWrap().IsSpecialEquip(eqid);

	if (isSpecail)   //定制装备处理
	{
		ProduceSpecialEquipment(equipment);
	}
	else
	{
		switch(type)
		{
			case equip_type_normal: ProduceEquipment(equipment); break;
			case equip_type_medal:  ProduceMedal(equipment); break;
			default: break;
		}
	}

	//判断装备是否可叠加
	bool isOverlay = EquipmentManager::Instance()->IsAllowOverlay(eqid);

	try
	{
		if (isOverlay)   //处理可叠加装备
		{
			equipment.num = count;
			AddEqupmentUnderlying(equipment, reason, msg->add_equips());
		}
		else  //不可叠加
		{
			equipment.num = 1;

			for(int i = 0; i < count; ++i)
			{
				AddEqupmentUnderlying(equipment, reason, msg->add_equips());
			}
		}
	}
	catch (std::runtime_error & e)
	{
		error_log(" exception:%s", e.what());
		throw e;
	}

	return 0;
}

void LogicEquipmentManager::GetFightAttr(unsigned uid, unsigned heroid, HeroFightAttr& result)
{
	result.Clear();

	std::vector<DataEquipment> vEquips;
	EquipmentManager::Instance()->GetHeroEquips(uid, heroid, vEquips);

	for (size_t i = 0; i < vEquips.size(); ++i)
	{
		HeroFightAttr  equipFightAttr;
		GetFightAttr(vEquips[i], equipFightAttr);

		result += equipFightAttr;
	}
}

void LogicEquipmentManager::GetFightAttr(const DataEquipment& equip, HeroFightAttr& result)
{
	//统
	result.SetAttr(DemoHeroProperty_int, equip.born1);
	//勇
	result.SetAttr(DemoHeroProperty_int, equip.born2);

	//todo 获取装备基本属性
	EquipCfgWrap equipCfg;
	HeroFightAttr baseAttr;
	equipCfg.GetEquipBaseFightAttr(equip.eqid, baseAttr);

	int types[4] = {equip.subt1, equip.subt2, equip.subt3, equip.subt4};
	int levels[4] = {equip.sublv1, equip.sublv2, equip.sublv3, equip.sublv4};
	HeroFightAttr addiAttr;
	//todo 装备洗练属性
	equipCfg.GetFightAttr(types, levels, 4, addiAttr);

	result += baseAttr + addiAttr;
}

void LogicEquipmentManager::GetEquipSuitAttr(unsigned uid, unsigned heroid, HeroFightAttr& attr)
{
	attr.Clear();

	vector<unsigned> equipindexs;
	EquipmentManager::Instance()->GetHeroEquipment(uid, heroid, equipindexs);

	map<unsigned, unsigned> suittypeNum;
	EquipCfgWrap equipcfgWrap;

	for (size_t i = 0; i < equipindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(equipindexs[i]);

		//获取装备的配置
		const EquipmentConfig::Equip & equipcfg = equipcfgWrap.GetEquip(equip.eqid);

		suittypeNum[equipcfg.type()] += 1;
	}

	EquipSuitConfigWrap equipsuitconfig;

	for(map<unsigned, unsigned>::iterator uiter = suittypeNum.begin(); uiter != suittypeNum.end(); ++uiter)
	{
		//排除非套装的装备
		int type = uiter->first;

		if (equipcfgWrap.IsEquipSuitByType(type))
		{
			//套装类型
			HeroFightAttr  equipSuitAttr;
			equipsuitconfig.GetFightAttr(type, uiter->second, equipSuitAttr);
			attr += equipSuitAttr;
		}
	}
}

int LogicEquipmentManager::DressEquipment(unsigned uid, unsigned equd, unsigned oldequd, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg)
{
	bool isExist = EquipmentManager::Instance()->IsEquipmentExists(uid, equd);

	if (!isExist)
	{
		error_log(" equd is not exists. uid=%u, equd=%u", uid, equd);
		return R_ERROR;
	}

	unsigned index = 0;

	try
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

		if (equip.heroid && equip.heroid != heroid)
		{
			error_log(" equd already have heroid. uid=%u, equd=%u, eqheroid=%u,heroid=%u", uid, equd, equip.heroid, heroid);
			return R_ERROR;
		}

		int pid = EquipmentManager::Instance()->GetEquipmentPid(equip.eqid);

        //勋章35级等级限制
        if (meal_position_code == pid)
        {
            DBCHeroWrap heroWrap(uid, heroid);
            
            if (heroWrap.Obj().level < medal_level_limit)
            {
                error_log(" hero level not match. uid=%u,heroid=%u,equd=%u", uid, heroid, equd);
                return R_ERROR;
            }
        }
        
		if (oldequd != 0)
		{
			unsigned oldindex = 0;
			DataEquipment & oldequip = EquipmentManager::Instance()->GetEquipment(uid, oldequd, oldindex);
			int oldpid = EquipmentManager::Instance()->GetEquipmentPid(oldequip.eqid);

			if (oldequip.heroid && oldequip.heroid != heroid)
			{
				error_log(" oldequd 's heroid not same. uid=%u, equd=%u, eqheroid=%u,heroid=%u", uid, oldequd, oldequip.heroid, heroid);
				return R_ERROR;
			}

			if (pid != oldpid)
			{
				error_log(" pid not same. uid=%u, equd=%u, oldequd=%u", uid, equd, oldequd);
				return R_ERROR;
			}

			oldequip.heroid = 0;

			int ret = EquipmentManager::Instance()->UpdateEquipment(oldindex);

			if (!ret)
			{
				error_log(" update equipment error. uid=%u,equd=%u,heroid=%u", uid, oldequd, heroid);
				return R_ERROR;
			}

			oldequip.SetMessage(msg->add_equips());
		}

		equip.heroid = heroid;

		int ret = EquipmentManager::Instance()->UpdateEquipment(index);

		if (!ret)
		{
			error_log(" update equipment error. uid=%u,equd=%u,heroid=%u", uid, equd, heroid);
			return R_ERROR;
		}

		equip.SetMessage(msg->add_equips());
	}
	catch (std::runtime_error & e)
	{
		error_log(" exception:%s", e.what());
		throw e;
	}

	return 0;
}

int LogicEquipmentManager::UnDressEquipment(unsigned uid, unsigned equd, unsigned heroid, DataCommon::EquipmentCPP * msg)
{
	bool isExist = EquipmentManager::Instance()->IsEquipmentExists(uid, equd);

	if (!isExist)
	{
		error_log(" equd is not exists. uid=%u, equd=%u", uid, equd);
		return R_ERROR;
	}

	unsigned index = 0;
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

	if (equip.heroid != heroid)
	{
		error_log(" equd 's owner not same. uid=%u, equd=%u, eqheroid=%u,heroid=%u", uid, equd, equip.heroid, heroid);
		return R_ERROR;
	}

	equip.heroid = 0;
	EquipmentManager::Instance()->UpdateEquipment(index);

	equip.SetMessage(msg);

	return 0;
}

int LogicEquipmentManager::OneKeyDressEquipment(unsigned uid, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg)
{
	//首先，获取该英雄身上的装备，判断还有那些部位的装备未穿戴
	vector<unsigned> vctindexs;

	EquipmentManager::Instance()->GetHeroEquipment(uid, heroid, vctindexs);

	//按照pid进行筛选
	map<uint8_t, uint32_t> map_bestequip;  //部位对应的当前最佳装备,pid为key, index为值
	map<uint8_t, pair<uint8_t, uint32_t> > map_oldequip;  //已穿戴部位信息. pid-><flag,index>. flag-是否被替换的标志.0-未被替换，1-被替换

	for(int i = 0; i < vctindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctindexs[i]);  //可能会抛出异常
		int pid = EquipmentManager::Instance()->GetEquipmentPid(equip.eqid);
		map_bestequip[pid] = vctindexs[i];

		map_oldequip[pid].first = 0;
		map_oldequip[pid].second = vctindexs[i];
	}

	//获取用户可选的装备
	vector<unsigned> vctoptionindexs;
	EquipmentManager::Instance()->GetOptionalEquipment(uid, vctoptionindexs);

	EquipmentManager::EquipConfInfo equipinfo;
	EquipCfgWrap equipwrap;   //装备配置封装对象


	for(int i = 0; i < vctoptionindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctoptionindexs[i]);
		EquipmentManager::Instance()->GetEquipmentConfig(uid, equip.eqid, equipinfo);

		int pid = equipinfo.pid;
        
        //勋章35级等级限制,在35级前，过滤掉勋章
        if (meal_position_code == pid)
        {
            DBCHeroWrap heroWrap(uid, heroid);
            
            if (heroWrap.Obj().level < medal_level_limit)
            {
                continue;
            }
        }
        
		if (!equipwrap.IsEquipment(equip.eqid))  //排除普通道具
		{
			continue;
		}

		if (map_bestequip.count(pid))   //已有装备，与当前装备进行对比
		{
			//先比较品质
			EquipmentManager::EquipConfInfo best_equipinfo;    //最佳所对象的装备信息,获取这个，是为了比较品质
			DataEquipment & best_equip = EquipmentManager::Instance()->GetEquipmentByIndex(map_bestequip[pid]);

			//EquipmentManager::Instance()->GetEquipmentConfig(uid, best_equip.eqid, best_equipinfo);
			int subval = equipwrap.GetPropertySubValue(equip.eqid, best_equip.eqid);

			bool isBetter = false;

			if (subval > 0)  //比较装备的配置的大小，包括品质和基础属性值
			{
				isBetter = true;
			}
			else if(0 == subval && equip > best_equip)  //配置的属性相同，进一步比较星级和洗练等级和，如果是勋章，则是比较统和勇的值
			{
				isBetter = true;
			}

			if (isBetter)
			{
				map_bestequip[pid] = vctoptionindexs[i];

				if (map_oldequip.count(pid) && 0 == map_oldequip[pid].first)  //已穿戴装备被替换
				{
					map_oldequip[pid].first = 1;
				}
			}

		}
		else
		{
			map_bestequip.insert(make_pair(pid, vctoptionindexs[i]));
		}
	}

	//将最佳选项的装备设置英雄所有
	map<uint8_t, uint32_t>::iterator uiter;

	for(uiter = map_bestequip.begin(); uiter != map_bestequip.end(); ++uiter)
	{
		DataEquipment & bestequip = EquipmentManager::Instance()->GetEquipmentByIndex(uiter->second);
		bestequip.heroid = heroid;

		EquipmentManager::Instance()->UpdateEquipment(uiter->second);
		bestequip.SetMessage(msg->add_equips());
	}

	map<uint8_t, pair<uint8_t, uint32_t> >::iterator piter;

	//处理被替换的装备
	for(piter = map_oldequip.begin(); piter != map_oldequip.end(); ++piter)
	{
		if (0 == piter->second.first)  //该部位的装备未被替换，则不做处理
		{
			continue;
		}

		DataEquipment & replaceequip = EquipmentManager::Instance()->GetEquipmentByIndex(piter->second.second);
		replaceequip.heroid = 0;

		EquipmentManager::Instance()->UpdateEquipment(piter->second.second);
		replaceequip.SetMessage(msg->add_equips());
	}

	return 0;
}


int LogicEquipmentManager::SwitchDress(unsigned uid, unsigned heroid, unsigned othheroid, ProtoHero::EquipmentWrapCPP * msg)
{
	//获取第一个英雄身上的装备
	vector<unsigned> vctindexs;
	EquipmentManager::Instance()->GetHeroEquipment(uid, heroid, vctindexs);
    DBCHeroWrap heroWrapThis(uid, heroid);

    //获取第二个英雄身上的装备
	vector<unsigned> vctOthindexs;
	EquipmentManager::Instance()->GetHeroEquipment(uid, othheroid, vctOthindexs);
    DBCHeroWrap heroWrapOth(uid, othheroid);
     
    EquipCfgWrap equpcfgwrap;   //装备配置的封装类
    
	//更换第一个英雄身上的装备
	for(int i = 0; i < vctindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctindexs[i]);   //可能会抛出异常

        //勋章要进行判断对方英雄是否达到35级
        if (equpcfgwrap.IsMedal(equip.eqid))
        {
            if (heroWrapOth.Obj().level < medal_level_limit)  //对方英雄不足等级，则不做处理
            {
                continue;
            }
        }
        
		equip.heroid = othheroid;

		EquipmentManager::Instance()->UpdateEquipment(vctindexs[i]);
		equip.SetMessage(msg->add_equips());
	}

    //更换第二个英雄身上的装备
	for(int i = 0; i < vctOthindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctOthindexs[i]);  //可能会抛出异常

        //勋章要进行判断对方英雄是否达到35级
        if (equpcfgwrap.IsMedal(equip.eqid))
        {
            if (heroWrapThis.Obj().level < medal_level_limit)  //对方英雄不足等级，则不做处理
            {
                continue;
            }
        }
        
		equip.heroid = heroid;
        
		EquipmentManager::Instance()->UpdateEquipment(vctOthindexs[i]);
		equip.SetMessage(msg->add_equips());
	}

	return 0;
}

int LogicEquipmentManager::UnDressAllEquipment(unsigned uid, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg)
{
	//获取该英雄身上的装备
	vector<unsigned> vctindexs;
	EquipmentManager::Instance()->GetHeroEquipment(uid, heroid, vctindexs);

	try
	{
		for(int i = 0; i < vctindexs.size(); ++i)
		{
			DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctindexs[i]);  //这里可能会抛出异常
			equip.heroid = 0;   //脱装备

			EquipmentManager::Instance()->UpdateEquipment(vctindexs[i]);

			equip.SetMessage(msg->add_equips());
		}
	}
	catch (std::runtime_error & e)
	{
		error_log(" exception:%s", e.what());
		throw e;
	}

	return 0;
}

unsigned LogicEquipmentManager::ComposeEquipSuit(unsigned uid, unsigned equd, vector<unsigned> & material, DataCommon::EquipmentAllCPP * msg)
{
	//先验证条件
	vector<unsigned> counts;
	VerifyComposeCondition(uid, equd, material, counts);

	//产生套装，赋予新属性
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);
	DataEquipment suitEquip;

	const EquipSuitConfig::SuitEquip & suitequipcfg = EquipSuitConfigWrap().GetEquipSuit(equip.eqid);

	//不处理装备的born1和bor2，因为这是统和勇，六个部位中没有这个属性
	suitEquip.uid = uid;
	suitEquip.eqid = suitequipcfg.suiteqid();

	const EquipmentConfig::Equip & equipcfg = EquipCfgWrap().GetEquip(suitEquip.eqid);
	suitEquip.star = equip.star;  //套装的星级与前置装备的星级相同
	suitEquip.num = 1;

	//产生的套装，继承前置装备的洗练属性以及英雄
	suitEquip.heroid = equip.heroid;
	InheritSubProperty(suitEquip, equip);

	//消耗前置装备
	int precount = 1;
	UseEquipment(uid, equip.eqid, equd, precount, "Compose_Equipsuit", msg->add_equips());

	//消耗材料
	for(int i = 0; i < material.size(); ++i)
	{
		DataEquipment & equip_material = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, material[i]);
		UseEquipment(uid, equip_material.eqid, material[i], counts[i], "Compose_Equipsuit", msg->add_equips());
	}

	//开始进行套装合成,将套装写入内存
	AddEqupmentUnderlying(suitEquip, "Compose_Equipsuit", msg->add_equips());

	//todo 接入套装合成成就
	EquipExternalInterface(uid, achievement_type_composesuit);

	return suitEquip.ud;
}

int LogicEquipmentManager::VerifyComposeCondition(unsigned uid, unsigned equd, vector<unsigned> & material, vector<unsigned> & counts)
{
	//先验证equd是否可用，有效
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);

	if (equip.issold)
	{
		error_log(" equip is already sold. uid=%u,equd=%u", uid, equd);
		throw std::runtime_error("equip_already_sold");
	}

	EquipCfgWrap equipcfgwrap;   //装备配置封装类对象
	const EquipmentConfig::Equip & equipcfg = equipcfgwrap.GetEquip(equip.eqid);

	int maxlevel = equipcfgwrap.GetSubMaxLevel(equip.eqid);

	if (equipcfg.character() != charater_type_purple)
	{
		error_log(" pre equipment's character not enough. uid=%u,equd=%u,character=%u", uid, equd);
		throw std::runtime_error("preequip_character_not_enough");
	}

	int maxstar = equipcfg.character() - 3 + 1;  //紫色能够达到的最大星级

	//判断前置装备是否满足套装的要求:紫色，四星,属性满级
	bool isFull = IsEquipSubFull(equip, maxlevel, maxstar);

	if (!isFull)
	{
		error_log(" pre equipment's subproperty not maxlevel. uid=%u,equd=%u", uid, equd);
		throw std::runtime_error("preequip_sublevel_not_enough");
	}

	const EquipSuitConfig::SuitEquip & suitequip = EquipSuitConfigWrap().GetEquipSuit(equip.eqid);

	if (material.size() != suitequip.material_size())
	{
		error_log(" material size not same. uid=%u,conditon_size=%d,really_size=%u", uid, suitequip.material_size(), material.size());
		throw std::runtime_error("param error");
	}

	for(int i = 0; i < material.size(); ++i)
	{
		DataEquipment & equip_material = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, material[i]);
		bool isHave = false;
		unsigned count = 0;

		for(int j = 0; j < suitequip.material_size(); ++j)
		{
			if (equip_material.eqid == suitequip.material(j).eqid())
			{
				isHave = true;
				count = suitequip.material(j).count();
				counts.push_back(count);
				break;
			}
		}

		if (!isHave)
		{
			error_log(" eqid is not condition. uid=%u,equd=%u,eqid=%u", uid, equip_material.ud, equip_material.eqid);
			throw std::runtime_error("param error");
		}

		if (equip_material.num < count)
		{
			error_log(" equd's num is not enough. uid=%u,equd=%u,condition_num=%u,num=%u", uid, equip_material.ud, count, equip_material.num);
			throw std::runtime_error("param error");
		}
	}

	if (counts.size() != material.size())
	{
		error_log(" count's size should equal to material size. uid=%u", uid);
		throw std::runtime_error("logic_error");
	}

	return 0;
}

int LogicEquipmentManager::InheritSubProperty(DataEquipment& equip, DataEquipment& oldequip)
{
	for(int i = 1; i < sub_type_max; ++i)
	{
		switch(i)
		{
			case 1: equip.subt1 = oldequip.subt1; equip.sublv1 = oldequip.sublv1; break;
			case 2: equip.subt2 = oldequip.subt2; equip.sublv2 = oldequip.sublv2; break;
			case 3: equip.subt3 = oldequip.subt3; equip.sublv3 = oldequip.sublv3; break;
			case 4: equip.subt4 = oldequip.subt4; equip.sublv4 = oldequip.sublv4; break;

			default: break;
		}
	}

	return 0;
}

int LogicEquipmentManager::AddEqupmentUnderlying(DataEquipment& equip, string  reason, DataCommon::EquipmentCPP * msg)
{
	int ret = R_SUCCESS;

	unsigned uid = equip.uid;
	unsigned eqid = equip.eqid;

	unsigned equd = 0;

	equd = EquipmentManager::Instance()->GetUserNextUd(uid, eqid, equip.num);

	bool isExist = EquipmentManager::Instance()->IsEquipmentExists(uid, equd);

	if (!isExist)   //新增的装备信息
	{
		equip.ud = equd;
		ret = EquipmentManager::Instance()->AddBuff(equip);

		if (ret)
		{
			error_log(" add dbc error. uid=%u", uid);
			throw std::runtime_error("add_equipment_eror");
		}

		DataEquipment & dataequip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);
		dataequip.SetMessage(msg);
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s.",
				uid, equd, eqid, "Add", dataequip.num, dataequip.num, reason.c_str());
	}
	else
	{
		//如果物品存在的话，就更新数量即可
		unsigned index = 0;
		DataEquipment & dataequip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

		dataequip.num += equip.num;

		ret = EquipmentManager::Instance()->UpdateEquipment(index);

		if (!ret)
		{
			error_log(" update equipment error. uid=%u,eqid=%u,ud=%u", uid, eqid, equd);
			throw std::runtime_error("update_equipment_error");
		}

		dataequip.SetMessage(msg);

		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s.",
				uid, equd, eqid, "Add", equip.num, dataequip.num, reason.c_str());
	}

	//todo 接入装备接口，只针对装备和勋章，排除普通物品
	bool isEquip = EquipCfgWrap().IsEquipment(equip.eqid);

	if (isEquip)
	{
		//接入指定品质装备成就
		EquipExternalInterface(uid, achievement_type_character_equip);

		//接入四星装备成就
		EquipExternalInterface(uid, achievement_type_star_equip);

		//接入秘籍属性成就
		EquipExternalInterface(uid, achievement_type_extraproperty);
	}

	return 0;
}

int LogicEquipmentManager::EquipExternalInterface(unsigned uid, unsigned type)
{
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = type;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

unsigned LogicEquipmentManager::GetWingmanByHeroid(unsigned uid, unsigned heroid)
{
	//首先遍历英雄的所有数据
	vector<unsigned>  indexs;
	EquipmentManager::Instance()->GetHeroEquipment(uid, heroid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(indexs[i]);
		bool iswing = IsWingMan(uid, equip.ud);

		if (iswing)
		{
			return equip.eqid;
		}
	}

	return 0;
}

bool LogicEquipmentManager::IsHaveTheWingman(unsigned uid, unsigned eqid)
{
	vector<unsigned> indexs;
	EquipmentManager::Instance()->GetEquipments(uid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(indexs[i]);

		if (equip.eqid == eqid)
		{
			return true;
		}
	}

	return false;
}

bool LogicEquipmentManager::IsWingMan(unsigned uid, unsigned equd)
{
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);

	for(int i = 0; i < MAX_WINGMAN_KIND; ++i)
	{
		if (equip.eqid == Wing_Man_Eqids[i])
		{
			return true;
		}
	}

	return false;
}

int LogicEquipmentManager::ProduceSpecialEquipment(DataEquipment & equip)
{
	unsigned eqid = equip.eqid;
	unsigned uid = equip.uid;

	const EquipmentConfig::Equip & equipcfg = EquipCfgWrap().GetEquip(eqid);
	const SpecialEquipConfig::SpecialEquipItem & specialcfg = SpecialEquipConfigWrap().GetSpecialEquipItem(eqid);

	if (equip_type_medal == equipcfg.type())  //勋章
	{
		if (2 == specialcfg.born_size())
		{
			equip.born1 = specialcfg.born(0u);
			equip.born2 = specialcfg.born(1u);
		}
		else if (1 == specialcfg.born_size())
		{
			equip.born1 = specialcfg.born(0u);
		}
	}
	else  //装备
	{
		unsigned star = equipcfg.star();
		unsigned special_star = specialcfg.star();

		if (star > special_star)  //定制的装备星级不正确
		{
			error_log(" special star not right. uid=%u,eqid=%u,special_star=%u,star=%u", uid, eqid, special_star, star);

			//定制化无效，调用随机生成
			ProduceEquipment(equip);
		}
		else  //定制星级
		{
			equip.star = special_star;

			for(int i = 0; i < special_star && i < specialcfg.subs_size() && i < specialcfg.sublevel_size(); ++i)
			{
				switch(i)
				{
					case 0: equip.subt1 = specialcfg.subs(i);  equip.sublv1 = specialcfg.sublevel(i); break;
					case 1: equip.subt2 = specialcfg.subs(i);  equip.sublv2 = specialcfg.sublevel(i); break;
					case 2: equip.subt3 = specialcfg.subs(i);  equip.sublv3 = specialcfg.sublevel(i); break;
					case 3: equip.subt4 = specialcfg.subs(i);  equip.sublv4 = specialcfg.sublevel(i); break;
					default: break;
				}
			}
		}
	}

	return 0;
}

int LogicEquipmentManager::ProduceEquipment(DataEquipment & equip)
{
	unsigned eqid = equip.eqid;
	//获取星级
	equip.star = EquipCfgWrap().GetEquip(eqid).star();

	//初始化洗练属性类型
	SmeltProperty(equip);

	//初始化洗练等级
	InitEquipSubLv(equip);

	return 0;
}

int LogicEquipmentManager::InitEquipSubLv(DataEquipment & equip)
{
	int lv = 1;

	for(int i = 0; i < equip.star; ++i)
	{
		switch(i)
		{
			case 0: equip.sublv1 = lv; break;
			case 1: equip.sublv2 = lv; break;
			case 2: equip.sublv3 = lv; break;
			case 3: equip.sublv4 = lv; break;
			default: break;
		}
	}

	return 0;
}

int LogicEquipmentManager::ProduceMedal(DataEquipment & equip)
{
	unsigned eqid = equip.eqid;
	//获取品质
	unsigned character = EquipCfgWrap().GetEquip(eqid).character();

	//根据品质，获取产生的统和勇的范围
	const EquipmentConfig::EquipList & equiplist = EquipCfgWrap().EquipList();
	int min = 0, max = 0;

	for(int i = 0; i < equiplist.spprop_size(); ++i)
	{
		if (equiplist.spprop(i).ch() == character)
		{
			min = equiplist.spprop(i).value(0u);
			max = equiplist.spprop(i).value(1u);
			break;
		}
	}

	//在一定范围内随机
	int rule = LogicCommonUtil::GetRandomBetweenAB(min, max);  //统
	int courage = LogicCommonUtil::GetRandomBetweenAB(min, max);  //勇

	equip.born1 = rule;
	equip.born2 = courage;

	return 0;
}


int LogicEquipmentManager::UseEquipment(unsigned uid, unsigned eqid, unsigned equd, unsigned count, string reason, DataCommon::EquipmentCPP * msg)
{
	unsigned index = 0;
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);
	equip.SetMessage(msg);

	unsigned restcount = 0;
	UseEquipment(uid, eqid, equd, count, reason, restcount);

	msg->set_num(restcount);

	return 0;
}

bool LogicEquipmentManager::IsOwnerEquipments(unsigned uid, unsigned eqid, unsigned equd, unsigned count)
{
	unsigned index = 0;
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

	if (equip.eqid != eqid)
	{
		error_log(" eqid is not same. uid=%u,ud=%u", uid, equd);
		throw std::runtime_error("equip_not_same");
	}

	if (equip.issold)
	{
		error_log(" equip is sold. uid=%u,ud=%u", uid, equd);
		throw std::runtime_error("equip_is_sold");
	}

	//判断道具数量是否足够
	return equip.num >= count;
}

int LogicEquipmentManager::UseEquipment(unsigned uid, unsigned eqid, unsigned equd, unsigned count, string reason, unsigned & restcount)
{
	try
	{
		unsigned index = 0;
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

		if (equip.eqid != eqid)
		{
			error_log(" eqid is not same. uid=%u,ud=%u", uid, equd);
			throw std::runtime_error("equip_not_same");
		}

		if (equip.issold)
		{
			error_log(" equip is sold. uid=%u,ud=%u", uid, equd);
			throw std::runtime_error("equip_is_sold");
		}

		//判断道具数量是否足够
		if (equip.num < count)
		{
			error_log(" equip not enough. uid=%u,ud=%u,count=%u", uid, equd, count);
			throw std::runtime_error("equip_not_enough");
		}

		equip.num -= count;
		restcount = equip.num;

		if (0 == equip.num)  //道具已用完，删除
		{
			EquipmentManager::Instance()->DeleteEquipment(equip);
		}
		else
		{
			EquipmentManager::Instance()->UpdateEquipment(index);
		}

		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s.",
				uid, equd, equip.eqid, "Sub", count, equip.num, reason.c_str());
	}
	catch (std::runtime_error & e)
	{
		throw e;
	}

	return 0;
}

int LogicEquipmentManager::Process(unsigned uid, ProtoEquip::SoldEquipReq *reqmsg, ProtoEquip::SoldEquipResp * respmsg)
{
	unsigned equd = reqmsg->equd();

	int ret = SoldEquipment(uid, equd, respmsg);

	if (ret)
	{
		throw std::runtime_error("sold_equip_error");
	}

	return 0;
}

int LogicEquipmentManager::Process(unsigned uid, ProtoEquip::OpenRepurchaseWindowReq *reqmsg, ProtoEquip::OpenRepurchaseWindowResp * respmsg)
{
	//先删除已到时间的回购装备
	DelEquipmentCheck(uid);

	//先获取当前用户已售出的装备
	vector<unsigned> vctindexs;

	EquipmentManager::Instance()->GetSoldEquipment(uid, vctindexs);

	for(int i = 0; i < vctindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctindexs[i]);
		equip.SetMessage(respmsg->add_equips());
	}

	return 0;
}

int LogicEquipmentManager::SmeltEquipment(unsigned uid, unsigned equd, int type, ProtoHero::EquipSmeltResp* msg)
{
	//获取装备信息
	unsigned index = 0;
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

	if (0 == equip.star)
	{
		equip.SetMessage(msg->mutable_equip());
		return 0;
	}

	//todo 消耗洗练次数或者钻石
	SmeltCostTimesOrCash(uid, type, msg);

	 //洗练已有星级下的属性
	const EquipmentConfig::Equip & equipconfig = EquipCfgWrap().GetEquip(equip.eqid);
	uint8_t configStar = equipconfig.star();   //配置的星级
	SmeltProperty(equip, configStar);   //不刷新已激活的新属性，除非属性再次相同

	//升级洗练属性
	UpgradeSubProperty(equip, type);

	//更新激活属性，包括新增激活属性
	UpdateExtraSubProperty(equip);

	//更新装备数据
	EquipmentManager::Instance()->UpdateEquipment(index);

	//返回前端装备信息
	equip.SetMessage(msg->mutable_equip());

	//todo 装备洗练外部接口
	SmeltExternalInterface(uid, equd);

	return 0;
}

int LogicEquipmentManager::SmeltExternalInterface(unsigned uid, unsigned equd)
{
	//todo 接入每日洗练任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_smelt;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	//洗练大放送
	LogicSmeltActivity::Instance()->AccumulateSmeltCnt(uid, 1);

	return 0;
}

int LogicEquipmentManager::UpdateExtraSubProperty(DataEquipment& equip, bool isSame)
{
	EquipCfgWrap equipcfgwrap;   //装备配置
	SmeltConfigWrap smelfconfig;  //洗练配置
	const EquipmentConfig::Equip & equipconfig = equipcfgwrap.GetEquip(equip.eqid);

	int character = equipconfig.character();
	uint8_t configStar = equipconfig.star();   //配置的星级
	uint8_t max_charcter_star = 0;

	if (character > 3)
	{
		max_charcter_star = character - 3;  //品质对应的原始最大星级
	}

	int maxlevel = equipcfgwrap.GetSubMaxLevel(equip.eqid);

	//操作已激活或待激活的洗练属性
	if (equip.star > 1)
	{
		bool isFullAndSame = IsEquipSubFullAndSame(equip, maxlevel, configStar);

		//判断是否已激活额外洗练属性
		if (isFullAndSame)
		{
			if (max_charcter_star == equip.star)   //未激活
			{
				//额外激活属性
				if (2 == equip.star)
				{
					if (isSame)
					{
						equip.subt3 = equip.subt1;
					}
					else
					{
						equip.subt3 = Math::GetRandomInt(property_type_strong_defend) + 1;
					}

					equip.sublv3 = equip.sublv1;
					equip.star += 1;
				}
				else if (3 == equip.star)
				{
					if (isSame)
					{
						equip.subt4 = equip.subt1;
					}
					else
					{
						equip.subt4 = Math::GetRandomInt(property_type_strong_defend) + 1;
					}

					equip.sublv4 = equip.sublv1;
					equip.star += 1;
				}

				//todo 接入星级成就
				EquipExternalInterface(equip.uid, achievement_type_star_equip);

			}
			else if (max_charcter_star < equip.star)
			{
				//新属性替换
				if (3 == equip.star)
				{
					if (isSame)
					{
						equip.subt3 = equip.subt1;
					}
					else
					{
						equip.subt3 = Math::GetRandomInt(property_type_strong_defend) + 1;
					}
					equip.sublv3 = equip.sublv1;
				}
				else if (4 == equip.star)
				{
					if (isSame)
					{
						equip.subt4 = equip.subt1;
					}
					else
					{
						equip.subt4 = Math::GetRandomInt(property_type_strong_defend) + 1;
					}
					equip.sublv4 = equip.sublv1;
				}
			}
		}
	}

	//接入秘籍属性成就
	EquipExternalInterface(equip.uid, achievement_type_extraproperty);

	return 0;
}

int LogicEquipmentManager::UpgradeSubProperty(DataEquipment& equip, int type)
{
	EquipCfgWrap equipcfg;   //装备配置
	SmeltConfigWrap smelfconfig;  //洗练配置

	int maxlevel = equipcfg.GetSubMaxLevel(equip.eqid);

	unsigned uid = equip.uid;
	unsigned equd = equip.ud;

	if (-1 == maxlevel)
	{
		error_log(" get equipsmelt's maxlevel error. uid=%u,equd=%u", uid, equd);
		throw std::runtime_error("get_caracter_config_error");
	}

	//2.随机产生一个升级的部位
	uint8_t configStar = equipcfg.GetEquip(equip.eqid).star();   //配置的星级
	int pos = Math::GetRandomInt(configStar) + 1;   //升级的属性位置
	int curlevel = GetPropertyLevel(equip, pos);

	if (-1 == curlevel)
	{
		error_log(" get equip property level error. uid=%u,equd=%u,pos=%d", uid, equd, pos);
		throw std::runtime_error("get_curlevell_error");
	}

	if (curlevel < maxlevel)
	{
		int rate = smelfconfig.GetUpgradeRate(type, curlevel);   //获取升级概率

		//3.随机判定技能是否升级
		int randval = Math::GetRandomInt(100);   //生成随机值

		if (rate > randval)
		{
			++curlevel;
			SetPropertyLevel(equip, pos, curlevel);
		}
	}

	return 0;
}

int LogicEquipmentManager::SmeltCostTimesOrCash(unsigned uid, int type, ProtoHero::EquipSmeltResp* msg)
{
	DBCUserBaseWrap userWrap(uid);

	//先扣次数或者资源
	if (smelt_type_of_normal == type)  //普通洗练
	{
		if (userWrap.Obj().refresh < 1)
		{
			error_log(" free refresh time not enough. uid=%u", uid);
			throw std::runtime_error("times_not_enough");
		}
		else
		{
			userWrap.Obj().refresh -= 1;
		}
	}
	else if (smelt_type_of_super == type)
	{
		if (userWrap.Obj().arefresh < 1)
		{
			//扣钻
			int cash = 10;
			userWrap.CostCash(cash, "Super_Smelt");
		}
		else
		{
			userWrap.Obj().arefresh -= 1;
		}
	}

	userWrap.Save();

	msg->set_refresh(userWrap.Obj().refresh);
	msg->set_arefresh(userWrap.Obj().arefresh);
	msg->set_cash(userWrap.Obj().cash);

	return 0;
}

bool LogicEquipmentManager::IsEquipSubFullAndSame(DataEquipment& equip, int maxlevel, int maxstar)
{
	bool isFullAndSame = true;  //相同属性，且都是满级

	int firsttype = equip.subt1;

	for(int i = 1; i <= equip.star && i <= maxstar; ++i)
	{
		//判断是否满足各星级属性全都相同，全都满级等条件
		switch(i)
		{
			case 1: if (firsttype != equip.subt1 || maxlevel != equip.sublv1) {isFullAndSame = false;} break;
			case 2: if (firsttype != equip.subt2 || maxlevel != equip.sublv2) {isFullAndSame = false;} break;
			case 3: if (firsttype != equip.subt3 || maxlevel != equip.sublv3) {isFullAndSame = false;} break;
			case 4: if (firsttype != equip.subt4 || maxlevel != equip.sublv4) {isFullAndSame = false;} break;
			default: isFullAndSame = false; break;
		}

		if (!isFullAndSame)
		{
			break;
		}
	}

	return isFullAndSame;
}

bool LogicEquipmentManager::IsEquipSubFull(DataEquipment& equip, int maxlevel, int maxstar)
{
	bool isFull = true;  //默认满级

	for(int i = 1; i <= equip.star && i <= maxstar; ++i)
	{
		//判断是否满足各星级属性全都满级
		switch(i)
		{
			case 1: if (maxlevel != equip.sublv1) {isFull = false;} break;
			case 2: if (maxlevel != equip.sublv2) {isFull = false;} break;
			case 3: if (maxlevel != equip.sublv3) {isFull = false;} break;
			case 4: if (maxlevel != equip.sublv4) {isFull = false;} break;
			default: isFull = false; break;
		}

		if (!isFull)
		{
			break;
		}
	}

	return isFull;
}

int LogicEquipmentManager::SoldEquipment(unsigned uid, unsigned equd, ProtoEquip::SoldEquipResp * msg)
{
	//获得装备信息
	bool isExist = EquipmentManager::Instance()->IsEquipmentExists(uid, equd);

	if (!isExist)
	{
		error_log(" equd is not exists. uid=%u, equd=%u", uid, equd);
		return R_ERROR;
	}

	unsigned index = 0;
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipment(uid, equd, index);

	//卖出装备得银币
	EquipmentManager::EquipConfInfo equipinfo;
	EquipmentManager::Instance()->GetEquipmentConfig(uid, equip.eqid, equipinfo);

	//没有配置价格的道具不允许卖出 @add oulong 20161027
	if (equipinfo.price <= 0)
	{
		throw std::runtime_error("this_equip_can_not_sell");
		return R_ERROR;
	}

	if (equip.heroid != 0)
	{
		error_log(" equd have owner. uid=%u, equd=%u", uid, equd);
		return R_ERROR;
	}

	if (equip.issold)
	{
		error_log(" equd already sold. uid=%u, equd=%u", uid, equd);
		return R_ERROR;
	}

	equip.issold = 1;

	unsigned now = Time::GetGlobalTime();
	equip.deltime = now;   //装备的待清除时间

	int ret = EquipmentManager::Instance()->UpdateEquipment(index);

	if (!ret)
	{
		error_log(" update equipment error. uid=%u,equd=%u", uid, equip.ud);
		return R_ERROR;
	}

	//记录装备出售日志
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d", uid, equd, equip.eqid, "Sold", equip.num, equip.num);

	//todo 返回数据给前端，填写msg
	equip.SetMessage(msg->mutable_soldequip());

	Json::Value result;
	LogicUserManager::Instance()->AddUserResource(uid, equipinfo.price, 0, 0, 0, "Sold_Equipment", result);

	msg->set_coin(result["coin"].asUInt());

	return 0;
}

int LogicEquipmentManager::CalculateRefreshTimes(unsigned uid, unsigned last_offtime)
{
	unsigned now = Time::GetGlobalTime();

	if (now < last_offtime)   //当前时间小于上次离线时间，暂不做处理
	{
		return 0;
	}

	DataBase& base = BaseManager::Instance()->Get(uid);

	if(base.refresh >=  MAX_REFRESH_TIME)
	{
		return 0;
	}

	//计算当前时间与上次离线时间，间隔了多少个整点
	int times = LogicCommonUtil::GetHourTimes(last_offtime, now);

	base.refresh += times;

	if (base.refresh > MAX_REFRESH_TIME)
	{
		base.refresh = MAX_REFRESH_TIME;
	}

	BaseManager::Instance()->UpdateDatabase(base);

	return 0;
}

int LogicEquipmentManager::GetRefreshTimes(unsigned uid)
{
	int times = 0;

	DataBase& base = BaseManager::Instance()->Get(uid);

	times = base.refresh;

	return times;
}

int LogicEquipmentManager::DelEquipmentCheck(unsigned uid)
{
	//先获取当前用户已售出的装备
	vector<unsigned> vctindexs;

	EquipmentManager::Instance()->GetSoldEquipment(uid, vctindexs);

	unsigned now =  Time::GetGlobalTime();
	for(int i = 0; i < vctindexs.size(); ++i)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctindexs[i]);

		if (now < equip.deltime)
		{
			continue;
		}

		EquipmentManager::Instance()->DeleteEquipment(equip);
	}

	return 0;
}

int LogicEquipmentManager::SmeltProperty(DataEquipment & equip, unsigned star)
{
	unsigned uid = equip.uid;
	unsigned equd = equip.ud;

	if (0 == star)
	{
		star = equip.star;
	}

	for(int i = 0; i < equip.star && i < star; ++i)
	{
		//随机属性类型
		unsigned randomval = Math::GetRandomInt(property_type_strong_defend) + 1;

		switch(i)
		{
			case 0: equip.subt1 = randomval; break;
			case 1: equip.subt2 = randomval; break;
			case 2: equip.subt3 = randomval; break;
			case 3: equip.subt4 = randomval; break;
			default: break;
		}
	}

	return 0;
}

int LogicEquipmentManager::GetPropertyLevel(DataEquipment & equip, int pos)
{
	int level = -1;

	switch(pos)
	{
		case 1: level = equip.sublv1; break;
		case 2: level = equip.sublv2; break;
		case 3: level = equip.sublv3; break;
		case 4: level = equip.sublv4; break;
		default: break;
	}

	return level;
}

int LogicEquipmentManager::SetPropertyLevel(DataEquipment & equip, int pos, int val)
{
	switch(pos)
	{
		case 1: equip.sublv1 = val; break;
		case 2: equip.sublv2 = val; break;
		case 3: equip.sublv3 = val; break;
		case 4: equip.sublv4 = val; break;
		default: break;
	}

	return 0;
}

int LogicEquipmentManager::AdminClear(unsigned uid, bool isAdmin)
{
	if (!isAdmin)  //非管理标志，不得执行此操作
	{
		return 0;
	}

	//清除装备表
	//获取物品表的所有物品，不管是否被英雄穿戴着
	vector<unsigned> equipIndexs;
	EquipmentManager::Instance()->GetEquipments(uid, equipIndexs);

	for(int i = 0; i < equipIndexs.size(); ++i)
	{
		DataEquipment & equip =  EquipmentManager::Instance()->GetEquipmentByIndex(equipIndexs[i]);
		//删除装备
		EquipmentManager::Instance()->DeleteEquipment(equip);
	}

	return 0;
}
