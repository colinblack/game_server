#include "MapObject.h"
#include "BuildingConfig.h"

MapObject::MapObject(): m_appear(0), m_turn(0), m_fresh(0), m_camp(0), m_tick(0), m_uid(0), m_race(0), m_battleId(0), m_mapId(0), m_lastAttackTime(0), m_oriType(0), m_automatic(false),m_isSkillNeedSyncToBattle(false)
{
}

void MapObject::propsCalc()
{
}

void MapObject::unLoadBuffProps()
{
}

void MapObject::loadBuffProps()
{
}

void MapObject::getRateProps(PropertySets & props)
{
	//interface for get more props for sub-class to implement
}

void MapObject::getAddProps(PropertySets & props)
{
	//interface for get more props for sub-class to implement
}

void MapObject::updateProps(const Property &prop,byte type)
{
	int dataType = PropertyConfig::getDataType(type);
	switch(dataType)
	{
	case DT_INT:
	case DT_UNSIGNED_INT:
		m_data[type].pi += prop.pi;
		 break;
	case DT_FLOAT:
		m_data[type].pf += prop.pf;
		 break;
	}
}


bool MapObject::isValid()
{
	return getCdTime() <= Time::GetGlobalTime();
}
bool MapObject::allowToFight()
{
	return getBattleId() == 0 && getEnergy() >= 15;
}
uint32_t MapObject::getDistance(MapObject * pMo1, MapObject * pMo2)
{
	if(pMo1 == NULL)
	{
		error_log("pMo1 is NULL");
		return 9999999;
	}
	if(pMo2 == NULL)
	{
		error_log("pMo2 is NULL");
		return 9999999;
	}
	uint32_t x1 = 0;
	uint32_t y1 = 0;
	uint32_t x2 = 0;
	uint32_t y2 = 0;
	if(pMo1->m_battleId != pMo2->m_battleId)
	{
		return 9999999;
	}
	else
	{
		if(pMo1->getRace() == RACE_TYPE_BUILDING)
		{
			uint32_t tx = 0;
			uint32_t ty = 0;
			if(!BuildingConfig::getInstance()->getFootprint(pMo1->getType(),tx,ty))
			{
				error_log("can not find building config:%d",pMo1->getType());
				return 9999999;
			}
			else
			{
				x1 = pMo1->getX() + tx;
				y1 = pMo1->getY() + ty;
			}

		}
		else
		{
			x1 = pMo1->getX();
			y1 = pMo1->getY();
		}
		if(pMo2->getRace() == RACE_TYPE_BUILDING)
		{
			uint32_t tx = 0;
			uint32_t ty = 0;
			if(!BuildingConfig::getInstance()->getFootprint(pMo2->getType(),tx,ty))
			{
				error_log("can not find building config:%d",pMo2->getType());
				return 9999999;
			}
			else
			{
				x2 = pMo2->getX() + tx;
				y2 = pMo2->getY() + ty;
				return getDistanceRect(Point(pMo1->getX(), pMo1->getY()), Point(pMo2->getX(), pMo2->getY()), tx, ty);
			}
		}
		else
		{
			x2 = pMo2->getX();
			y2 = pMo2->getY();
		}
		int x = x1 - x2;
		int y = y1 - y2;
		return sqrt(x*x+y*y);
	}
}

uint32_t MapObject::getDistanceRect(const Point &src, const Point &des, uint32_t width, uint32_t heigth)
{
	Point a(des.x, des.y);
	Point b(des.x + 2 * width, des.y);
	Point c(des.x + 2 * width, des.y + 2 * heigth);
	Point d(des.x, des.y + 2 * heigth);

	int x = src.x;;
	int y = 0;

	if (src.x < a.x)
	{
		if (src.y < a.y){
			x = a.x;
			y = a.y;
		}else if (src.y >= a.y && src.y <= d.y){
			x = a.x;
			y = src.y;
		}else if (src.y > d.y){
			x = d.x;
			y = d.y;
		}
	}
	else if (src.x >= a.x && src.x <= b.x)
	{
		if (src.y < a.y){
			x = src.x;
			y = a.y;
		}else if (src.y >= a.y && src.y <= d.y){
			x = src.x;
			y = src.y;
		}else if (src.y > d.y){
			x = src.x;
			y = d.y;
		}
	}
	else if (src.x > b.x)
	{
		if (src.y < a.y){
			x = b.x;
			y = b.y;
		}else if (src.y >= a.y && src.y <= d.y){
			x = b.x;
			y = src.y;
		}else if (src.y >d.y){
			x = c.x;
			y = c.y;
		}
	}

	int dx = src.x - x;
	int dy = src.y - y;

	return sqrt(dx*dx+dy*dy);
}

uint32_t MapObject::getDistance(const Point &src,const Point &des)
{
	int x = src.x - des.x;
	int y = src.y - des.y;
	return sqrt(x*x+y*y);

}

void MapObject::setPath(const PathRlt & rlt)
{
}

void MapObject::onTimer()
{
}

bool MapObject::getTargetPoint(const Point & srcPoint,int & dx,int & dy)
{
	dx = getX();
	dy = getY();
	return true;
}

bool MapObject::encodePropsChange(IBuffer* buffer)
{
	static const int changes[] = {AP_HP,AP_HA,AP_MAX_HP,AP_LEVEL,AP_CAPACITY,AP_HERO_BUNKER,AP_MAX_CAPACITY,AP_COMBAT,AP_EXP,AP_EFFECT,AP_CU,AP_CP,AP_UPTS};
	static CStaticBuffer<MAX_ITEM_PACKET> tmpBuff;
	tmpBuff.Clear();
	PACK_PROPS(changes,tmpBuff);
	CBufferWriter writer(buffer);
	writer.AppendUInt16(tmpBuff.GetSize());
	buffer->AppendBuffer(&tmpBuff);
	return true;
}

bool MapObject::encodePropsChange(IBuffer* buffer,const vector<byte> &propsChange)
{
	CBufferWriter writer(buffer);
	writer.AppendUInt16((sizeof(uint32_t) + sizeof(byte)) * propsChange.size() + sizeof(byte));
	writer.AppendByte(propsChange.size());
	for(size_t index = 0; index < propsChange.size(); ++index)
	{
		writer.AppendByte(propsChange[index]);
		writer.AppendUInt32(m_data[propsChange[index]].pui);
	}

	return true;
}

void MapObject::updateHp(int32_t hp)
{
	if(hp < 0 && getHp() < (uint32_t)abs(hp))
	{
		setHp(0);
	}else{
		setHp(getHp() + hp);
	}

	vector<byte> vecProps;
	vecProps.push_back(AP_HP);
//	Map *pMap = MapManager::getInstance()->getMap(getBattleId());
//	pMap->sendPropChange(this,vecProps);
}

bool MapObject::onMapObjectHurt(MapObject *pAttacker, uint32_t hurt)
{
	if (pAttacker->getRace() == RACE_TYPE_CANNON)
	{
		return true;
	}
	HurtInfoKey key;
	key.uid = pAttacker->getUid();
	key.ud = pAttacker->getUD();
	key.race = pAttacker->getRace();
	HurtInfoValue& attackerHurt = m_hurtMap[key];
	if(Time::GetGlobalTime() > FIRST_ATTACKER_INTERVAL + attackerHurt.lastTime)
	{
		attackerHurt.hurt = 0;
	}
	attackerHurt.hurt += hurt;
	attackerHurt.lastTime = Time::GetGlobalTime();
	if(m_firstAttacker.hurtInfoKey == key
	|| m_firstAttacker.hurtInfoKey.uid == 0
	|| Time::GetGlobalTime() > FIRST_ATTACKER_INTERVAL + m_firstAttacker.hurtInfoValue.lastTime
	|| attackerHurt.hurt > m_firstAttacker.hurtInfoValue.hurt * 1.2)
	{
		m_firstAttacker.hurtInfoKey = key;
		m_firstAttacker.hurtInfoValue = attackerHurt;
		setTarget(pAttacker);
	}
	return true;
}

void MapObject::setTarget(MapObject* pMo)
{
	m_target.uid = pMo->getUid();
	m_target.battleId = pMo->getBattleId();
	m_target.race = pMo->getRace();
	m_target.ud = pMo->getUD();
}

bool MapObject::isTrap()
{
	return false;
}
bool MapObject::isResourceBuilding()
{
	if (!isBuilding())
	{
		return false;
	}
	uint32_t type = getType();
	return (type == BUILDING_ID_RESOURCE_R1 || type == BUILDING_ID_RESOURCE_R2);
}
bool MapObject::isStorageBuilding()
{
	if (!isBuilding())
	{
		return false;
	}
	uint32_t type = getType();
	return (type == BUILDING_ID_STORAGE_R1 || type == BUILDING_ID_STORAGE_R2);
}
bool MapObject::inAttackSpeedLimit(uint32_t now)
{
	if(getAttackSpeed() == 0)
	{
		return false;
	}
	const float speedMult = 83.0f;
	const float fps = 30.0f;
	return now >= m_lastAttackTime + static_cast<float>(100000) / static_cast<float>(getAttackSpeed()) / speedMult * fps;
}
