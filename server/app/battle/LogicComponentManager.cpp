#include "LogicComponentManager.h"

int LogicComponentManager::LoginCheck(unsigned uid)
{
	//检查部件数据是否加载进内存
	int ret = DataComponentManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataComponentManager::Instance()->LoadBuff(uid);
	}

	//初始化部件ud值
	DataComponentManager::Instance()->InitUserComponent(uid);

	return ret;
}

int LogicComponentManager::AddComponent(unsigned uid, unsigned compid, unsigned count, const string & reason, ProtoComponent::ComponentAllCPP* msg)
{
	for(int i = 0; i < count; ++i)
	{
		AddSingleComponent(uid, compid, reason, msg->add_components());
	}

	return 0;
}

int LogicComponentManager::AddSingleComponent(unsigned uid, unsigned compid, const string & reason, ProtoComponent::ComponentCPP* msg)
{
	DataComponent component;

	component.uid = uid;
	component.compid = compid;
	component.level = 1;  //初始等级为1

	//加工部件
	ProcessComponent(component);

	//调用底层的添加部件方法
	AddComponentUnderlying(component, reason, msg);
}

int LogicComponentManager::AddComponentUnderlying(DataComponent& component, const string & reason, ProtoComponent::ComponentCPP * msg)
{
	int ret = R_SUCCESS;

	unsigned uid = component.uid;
	unsigned compid = component.compid;
	unsigned compud = 0;

	//获得下一个可用的ud
	compud = DataComponentManager::Instance()->GetUserNextUd(uid);

	component.ud = compud;
	ret = DataComponentManager::Instance()->AddBuff(component);

	if (ret)
	{
		error_log("[AddComponentUnderlying] add buff error. uid=%u", uid);
		throw std::runtime_error("add_component_eror");
	}

	component.SetMessage(msg);
	COMPONENT_LOG("uid=%u,compud=%u,compid=%d,act=%s,level=%d,exp=%d,code=%s.", uid, compud, compid, "Add", component.level, component.exp, reason.c_str());

	return 0;
}

int LogicComponentManager::ProcessComponent(DataComponent& component)
{
	unsigned compid = component.compid;

	const ComponentConfig::ComponentBase & compobase = ComponentConfigWrap().GetComponentBaseConfig(compid);

	//排除非普通部件
	if (component_type_normal != compobase.type())
	{
		return 0;
	}

	//从配置中读取主属性的大小
	component.master = compobase.master();

	return 0;
}

int LogicComponentManager::LoadComponent(unsigned uid, unsigned compud, unsigned oldcompud, unsigned heroid, unsigned pos,
		ProtoComponent::ComponentAllCPP * compomsg)
{
	//根据ud获取部件数据
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	//判断当前部件是否可装备，因为部件经验道具是不可装备的
	bool isnormal = ComponentConfigWrap().IsNormalComponent(component.compid);

	if (!isnormal)
	{
		error_log("[LoadComponent] compud is exp props. uid=%u,compud=%u", uid, compud);
		throw runtime_error("component_can_not_load");
	}

	if (0 != oldcompud)
	{
		//校验旧有部件ud是否存在
		bool isExist =  DataComponentManager::Instance()->IsComponentExists(uid, oldcompud);

		if (!isExist)
		{
			error_log("[LoadComponent] compud is not exist. uid=%u,oldcompud=%u", uid, oldcompud);
			throw runtime_error("component_not_exist");
		}

		DataComponent& oldcomponent = DataComponentManager::Instance()->GetComponent(uid, oldcompud);

		if (heroid != oldcomponent.heroid)
		{
			error_log("[LoadComponent] heroid is not same, too bad.uid=%u,oldcompud=%u,heroid=%u", uid, oldcompud, heroid);
			throw runtime_error("can_not_replace_otherhero_component");
		}
	}

	//不能装载已经装载的装备
	if (component.heroid)
	{
		error_log("[LoadComponent] compud already have owner. uid=%u,compud=%u", uid, oldcompud);
		throw runtime_error("component_already_loaded");
	}

	//增加主属性冲突的限制
	vector<unsigned> indexs;
	DataComponentManager::Instance()->GetHeroComponents(uid, heroid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataComponent& othcomponent = DataComponentManager::Instance()->GetComponent(indexs[i]);

		if (othcomponent.master == component.master && othcomponent.ud != oldcompud)
		{
			error_log("[LoadComponent] master property is conflict. uid=%u,compud=%u,othcompud=%u", uid, compud, othcomponent.ud);
			throw runtime_error("master_property_conflict");
		}
	}

	//开始装载
	component.heroid = heroid;
	component.position = pos;

	if (0 != oldcompud)
	{
		DataComponent& oldcomponent = DataComponentManager::Instance()->GetComponent(uid, oldcompud);
		oldcomponent.heroid = 0;
		oldcomponent.position = 0;

		DataComponentManager::Instance()->UpdateDataComponent(oldcomponent);

		oldcomponent.SetMessage(compomsg->add_components());
	}

	DataComponentManager::Instance()->UpdateDataComponent(component);
	component.SetMessage(compomsg->add_components());

	return 0;
}

int LogicComponentManager::UnloadComponent(unsigned uid, unsigned compud, unsigned heroid, ProtoComponent::ComponentCPP * compomsg)
{
	//判断背包是否已满
	bool isfull = LogicCompProduceManager::Instance()->IsPackageFull(uid);

	if (isfull)
	{
		throw runtime_error("component_package_is_full");
	}

	//根据ud获取部件数据
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	//不能装载已经装载的装备
	if (component.heroid != heroid)
	{
		error_log("[UnDressEquipment] compud 's owner not same. uid=%u, compud=%u, compheroid=%u,heroid=%u", uid, compud, component.heroid, heroid);
		throw runtime_error("component_heroid_error");
	}

	component.heroid = 0;
	component.position = 0;

	DataComponentManager::Instance()->UpdateDataComponent(component);

	component.SetMessage(compomsg);

	return 0;
}

int LogicComponentManager::StrengthenComponent(unsigned uid, unsigned compud, unsigned othcompud, ProtoComponent::ComponentCPP * compomsg)
{
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	//调用底层强化方法
	int ret = StrengthenComponentUnderly(uid, compud, othcompud);

	switch(ret)
	{
		case 0: break;
		case ret_by_not_enough : throw runtime_error("resource_not_enough"); break;
		case ret_by_already_max : throw runtime_error("component_already_maxlevel"); break;
	}

	component.SetMessage(compomsg);

	return 0;
}

int LogicComponentManager::OneKeyStrengthenComponent(unsigned uid, unsigned compud, ProtoComponent::ComponentCPP *compomsg, vector<unsigned> & delcompo)
{
	//一键强化选择的部件条件:比自身品质低，且等级为1的直接吞噬

	//先从整体中选出符合条件的，然后再剩余的物品中进行排序
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);
	ComponentConfigWrap componentconfig;

	//配置
	const ComponentConfig::ComponentBase & baseconfig = componentconfig.GetComponentBaseConfig(component.compid);
	unsigned character = baseconfig.character();

	vector<unsigned> optionalIndexs;
	DataComponentManager::Instance()->GetOptionalComponents(uid, optionalIndexs);
	map<unsigned, vector<DataComponent> > optionalComponent;  //品质为key,部件集合为value

	//如何实现从低品质到高品质呢？来个map就行
	for(int i = 0; i < optionalIndexs.size(); ++i)
	{
		DataComponent& optionalcompo = DataComponentManager::Instance()->GetComponent(optionalIndexs[i]);

		//过滤等级非1的部件
		if (optionalcompo.level > 1)
		{
			continue;
		}

		//过滤大于等于自身品质的部件
		const ComponentConfig::ComponentBase & optionalconfig = componentconfig.GetComponentBaseConfig(optionalcompo.compid);

		unsigned optional_character = optionalconfig.character();

		if (optional_character >= character)
		{
			continue;
		}

		optionalComponent[optional_character].push_back(optionalcompo);
	}

	//对可选装备部件
	int ret = 0;
	bool isEnd = false;

	//开始强化
	for(map<unsigned, vector<DataComponent> >::iterator viter = optionalComponent.begin(); viter != optionalComponent.end(); ++viter)
	{
		vector<DataComponent> & compo = viter->second;

		//从小到大进行排序
		sort(compo.begin(), compo.end(), less<DataComponent>());

		//对排序后的集合进行强化操作
		for(int i = 0; i < compo.size(); ++i)
		{
			ret = StrengthenComponentUnderly(uid, compud, compo[i].ud);

			if (ret)  //满级或者资源不足
			{
				isEnd = true;
				break;
			}
			else   //强化成功，将当前被吞噬的ud放入集合
			{
				delcompo.push_back(compo[i].ud);
			}
		}

		if (isEnd)
		{
			break;
		}
	}

	component.SetMessage(compomsg);

	return 0;
}

int LogicComponentManager::StrengthenComponentUnderly(unsigned uid, unsigned compud, unsigned othcompud)
{
	//强化部件
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	ComponentConfigWrap componentconfig;
	//不能强化非一般部件
	bool isnormal = componentconfig.IsNormalComponent(component.compid);

	if (!isnormal)
	{
		error_log("[StrengthenComponentUnderly] compud is exp props. uid=%u,compud=%u", uid, compud);
		throw runtime_error("component_can_not_strengthen");
	}

	//是否已强化到顶级
	if (componentconfig.IsMaxLevel(component.compid, component.level))
	{
		error_log("[StrengthenComponentUnderly] compud is maxlevel. uid=%u,compud=%u", uid, compud);
		return ret_by_already_max;
	}

	//查看是否已被吞噬
	if (!DataComponentManager::Instance()->IsComponentExists(uid, othcompud))
	{
		error_log("[StrengthenComponentUnderly] othcompud already been eaten. uid=%u,compud=%u,othcompud=%u", uid, compud, othcompud);
		throw runtime_error("other_component_already_eaten");
	}

	//排除有主部件
	DataComponent& othcomponent = DataComponentManager::Instance()->GetComponent(uid, othcompud);

	//品质比较
	const ComponentConfig::ComponentBase &	thisconfig = componentconfig.GetComponentBaseConfig(component.compid);
	const ComponentConfig::ComponentBase & otherconfig = componentconfig.GetComponentBaseConfig(othcomponent.compid);

	if (otherconfig.character() > thisconfig.character() && otherconfig.type() == 1)  //只有同是一般部件，才有品质要求
	{
		error_log("[StrengthenComponentUnderly] can't eat higher character.uid=%u,compud=%u,othcompud=%u", uid, compud, othcompud);
		throw runtime_error("other_component_cannot_higher_character");
	}

	if (0 != othcomponent.heroid)
	{
		error_log("[StrengthenComponentUnderly] can't use loaded component. uid=%u,compud=%u,othcompud=%u", uid, compud, othcompud);
		throw runtime_error("can_not_eat_loaded_component");
	}

	//获得吞噬需要消耗的材料数量
	unsigned coin = 0;
	unsigned wood = 0;

	bool isothnormal = componentconfig.IsNormalComponent(othcomponent.compid);

	if (isothnormal)
	{
		componentconfig.GetNormalResourceCost(othcomponent.compid, othcomponent.level, coin, wood);
	}
	else
	{
		componentconfig.GetPropsResouceCost(othcomponent.compid, coin, wood);
	}

	//扣除吞噬部件需要消耗的材料
	DBCUserBaseWrap userwrap(uid);

	try
	{
		userwrap.CostUserResource(coin, wood, 0, 0, "Component_Strengthen");
	}
	catch(runtime_error &e)
	{
		return ret_by_not_enough;
	}

	//升级部件
	unsigned characterexp = componentconfig.GetExpByCompid(othcomponent.compid);  //品质对应的经验或经验道具id对应经验
	unsigned addexp = characterexp + othcomponent.exp * (double)0.8;  //原有经验损耗20%

	AddExp(uid, compud, addexp);

	//删除被吞噬的部件
	DataComponentManager::Instance()->DeleteComponent(othcomponent);

	//更新部件
	DataComponentManager::Instance()->UpdateDataComponent(component);

	return 0;
}

int LogicComponentManager::AddExp(unsigned uid, unsigned compud, unsigned exp)
{
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);
	const ComponentConfig::ComponentExp & expconfig = ComponentConfigWrap().GetExpLevelConfig(component.compid);
	int maxlevel = expconfig.exp_level_size();

	int oldlevel = component.level;
	//增加经验
	component.exp += exp;

	//当前经验已达到最高等级的经验
	if (component.exp >= expconfig.exp_level(maxlevel - 1))
	{
		component.level = maxlevel;
		component.exp = expconfig.exp_level(maxlevel - 1);

		return 0;
	}

	//等级作为下标
	int i = 0;
	for(; i < maxlevel; ++i)
	{
		if (expconfig.exp_level(i) > component.exp)
		{
			break;
		}
	}

	component.level = i;
	//todo 处理部件升级后，解锁副属性
	if (component.level > oldlevel)
	{
		UnlockSlave(component);
	}

	//更新
	DataComponentManager::Instance()->UpdateDataComponent(component);

	return 0;
}

int LogicComponentManager::UnlockSlave(DataComponent& component)
{
	const ComponentConfig::ComponentItem & item = ComponentConfigWrap().Component().component();
	int target = -1;

	//todo 处理升级的时候可能跨级的问题，比如一下子就从1级升到了3级
	for(int i = 0; i < item.component_unlock_size(); ++i)
	{
		//等级等于高于解锁条件的，都调用解锁副属性接口
		if (item.component_unlock(i) <= component.level)
		{
			UnlockSlaveProperty(component, i);
		}
		else  //这个都没通过，就不用循环下一个解锁条件了，因为后面更大
		{
			break;
		}
	}

	return 0;
}

int LogicComponentManager::UnlockSlaveProperty(DataComponent& component, int target)
{
	unsigned randomval = Math::GetRandomInt(property_type_strong_defend_percent) + 1;   //1-14中随机一类型

	//只解锁未解锁的副属性
	switch(target)
	{
		case 0: if (0 == component.slave1) component.slave1 = randomval; break; //解锁第一个副属性
		case 1:	if (0 == component.slave2) component.slave2 = randomval; break; //解锁第二个副属性
		case 2: if (0 == component.slave3) component.slave3 = randomval; break; //解锁第三个副属性
	}

	return 0;
}

int LogicComponentManager::GetBaseAttr(unsigned uid, unsigned heroid, HeroFightAttr& attr)
{
	//加载英雄装载的部件
	vector<unsigned> component_indexs;
	DataComponentManager::Instance()->GetHeroComponents(uid, heroid, component_indexs);
	attr.Clear();

	for(int i = 0; i < component_indexs.size(); ++i)
	{
		DataComponent& component = DataComponentManager::Instance()->GetComponent(component_indexs[i]);
		HeroFightAttr componentAttr;

		//部件属性大小计算
		GetComponentBaseAttr(component, componentAttr);

		attr += componentAttr;
	}

	return 0;
}

int LogicComponentManager::GetComponentBaseAttr(DataComponent& component, HeroFightAttr& attr)
{
	attr.Clear();
	vector<unsigned> types;
	ComponentConfigWrap componentcfgwrap;

	//todo 部件主属性
	if(component.master != 0 && component.master <= property_type_strong_defend)
	{
		types.push_back(component.master);
		HeroFightAttr masterAttr;
		componentcfgwrap.GetBaseAttr(component.compid, types, component.level, true, masterAttr);
		attr += masterAttr;
	}

	types.clear();

	//副属性
	HeroFightAttr slaveAttr;

	if(component.slave1 != 0 && component.slave1 <= property_type_strong_defend)
	{
		types.push_back(component.slave1);
	}

	if(component.slave2 != 0 && component.slave2 <= property_type_strong_defend)
	{
		types.push_back(component.slave2);
	}

	if(component.slave3 != 0 && component.slave3 <= property_type_strong_defend)
	{
		types.push_back(component.slave3);
	}

	//计算副属性大小
	componentcfgwrap.GetBaseAttr(component.compid, types, component.level, false, slaveAttr);
	attr += slaveAttr;

	return 0;
}

int LogicComponentManager::GetPercentAttr(unsigned uid, unsigned heroid, map<unsigned, double> & propertys)
{
	//加载英雄装载的部件
	vector<unsigned> component_indexs;
	DataComponentManager::Instance()->GetHeroComponents(uid, heroid, component_indexs);

	for(int i = 0; i < component_indexs.size(); ++i)
	{
		DataComponent& component = DataComponentManager::Instance()->GetComponent(component_indexs[i]);

		//计算每个部件的百分比属性
		GetComponentPercentAttr(component, propertys);
	}

	return 0;
}

int LogicComponentManager::GetComponentPercentAttr(DataComponent& component, map<unsigned, double> & propertys)
{
	ComponentConfigWrap componentcfgwrap;

	//todo 部件主属性
	if(component.master != 0 && component.master >= property_type_attack_percent)
	{
		map<unsigned, unsigned> masterPro;

		masterPro[component.master]  = 1;  //类型插入
		componentcfgwrap.GetPercentAttr(component.compid, component.level, true, masterPro, propertys);
	}

	//副属性
	map<unsigned, unsigned> slavePro;

	if(component.slave1 != 0 && component.slave1 >= property_type_attack_percent)
	{
		slavePro[component.slave1] += 1;  //类型次数插入
	}

	if(component.slave2 != 0 && component.slave2 >= property_type_attack_percent)
	{
		slavePro[component.slave2] += 1;  //类型次数插入
	}

	if(component.slave3 != 0 && component.slave3 >= property_type_attack_percent)
	{
		slavePro[component.slave3] += 1;  //类型次数插入
	}

	//计算部件副属性大小
	componentcfgwrap.GetPercentAttr(component.compid, component.level, false, slavePro, propertys);

	return 0;
}

int LogicComponentManager::MergePropertyFrom(map<unsigned, double> & thisPropertys, map<unsigned, double> & othPropertys)
{
	for(map<unsigned, double>::iterator diter = othPropertys.begin(); diter != othPropertys.end(); ++diter)
	{
		thisPropertys[diter->first] += diter->second;
	}

	return 0;
}

int LogicComponentManager::FullMessage(unsigned uid, ProtoComponent::ComponentAllCPP* msg)
{
	vector<unsigned> component_indexs;

	DataComponentManager::Instance()->GetComponents(uid, component_indexs);

	for(int i = 0; i < component_indexs.size(); ++i)
	{
		DataComponent& component = DataComponentManager::Instance()->GetComponent(component_indexs[i]);
		component.SetMessage(msg->add_components());
	}

	return 0;
}

