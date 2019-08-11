/*
 * MissionManager.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef MISSION_MANAGER_H_
#define MISSION_MANAGER_H_

#include "BattleBaseInc.h"

enum MISSION_STATUS {
	MISSION_UNKNOW		= 0,	//
	MISSION_DOING		= 1,	//
	MISSION_COMPLETE	= 2,	//
	MISSION_FAILED		= 3,	//
	MISSION_COMMIT		= 4		//
};

enum CONDITION_TYPE {
	MT_ROLE_LEVEL = 1,					//人物等级（前台自动）
	MT_REINCARNATION = 13,				//转生
	MT_HANG_LEVEL = 14,					//通关关卡
	MT_UNKNOW_3 = 15,
	MT_FORGE_LEVEL = 16,				//强化总等级
	MT_ACTIVATE_SHENQI_PIECES = 19,		//激活神器碎片
	MT_REACTIVE_SHENQI = 20,			//激活神器
	MT_UPGRADE_STATE = 21,				//境界提示
	MT_UNKNOW_8 = 23,
	MT_UNKNOW_9 = 24,
	MT_TREASURE_UPGRADE = 25,
	MT_UNKNOW_11 = 26,
	MT_UNKNOW_12 = 27,
	MT_UNKNOW_13 = 28,
	MT_UNKNOW_14 = 29,
	MT_MAGIC_LEARN = 31,				//符文装备
	MT_KILL_BOSS = 32,					//击杀转生BOSS
	MT_RUNE_TOWER = 33,					//符文塔闯关
	MT_UNKNOW_18 = 34,
	MT_UNKNOW_19 = 35,
	MT_EQUIP_EQUIP = 36,				//穿戴装备
	MT_UNKNOW_21 = 37,
	MT_UNKNOW_22 = 38,
	MT_UNKNOW_23 = 39,
	MT_WORLD_BOSS = 40,
	MT_UNKNOW_25 = 41,
	MT_UNKNOW_26 = 42,
	MT_UNKNOW_27 = 43,
	MT_UNKNOW_28 = 44,
	MT_UNKNOW_29 = 45,
	MT_UNKNOW_30 = 46,
	MT_TREASUREHUNT = 53,				//寻宝
	MT_UNKNOW_32 = 54,
	MT_UNKNOW_33 = 55,
	MT_UNKNOW_34 = 56,
	MT_ACHIEVEMENT = 57,				//累计获得成就
	MT_UNKNOW_36 = 58,
	MT_UNKNOW_37 = 59,
	MT_UNKNOW_38 = 60,
	MT_UNKNOW_39 = 61,
	MT_UNKNOW_40 = 63,
	MT_UNKNOW_41 = 64,
	MT_UNKNOW_42 = 70,
	MT_UNKNOW_43 = 72,
	MT_UNKNOW_44 = 73,
	MT_UNKNOW_45 = 74,
	MT_UNKNOW_46 = 75,
	MT_UNKNOW_47 = 76,
	MT_UNKNOW_48 = 77,
	MT_UNKNOW_49 = 78,
	MT_UNKNOW_50 = 79,
	MT_UNKNOW_51 = 85,
	MT_UNKNOW_52 = 92,
	MT_UNKNOW_53 = 93,
	MT_UNKNOW_54 = 94,
	MT_UNKNOW_55 = 95,
	MT_UNKNOW_56 = 96,
	MT_UNKNOW_57 = 97,
	MT_UNKNOW_58 = 98,
	MT_UNKNOW_59 = 103,
	MT_UNKNOW_60 = 104,
	MT_UNKNOW_61 = 105,
	MT_UNKNOW_62 = 106,
	MT_UNKNOW_63 = 107,
	MT_UNKNOW_64 = 108,
	MT_UNKNOW_65 = 109,
	MT_UNKNOW_66 = 110,
	MT_UNKNOW_67 = 111,
	MT_UNKNOW_68 = 114,
	MT_UNKNOW_69 = 115,
	MT_UNKNOW_70 = 116,
	MT_UNKNOW_71 = 117,
	MT_UNKNOW_72 = 118,
	MT_UNKNOW_73 = 119,
	MT_UNKNOW_74 = 120,
	MT_UNKNOW_75 = 121,
	MT_UNKNOW_76 = 124,
	MT_UNKNOW_77 = 125,
	MT_UNKNOW_78 = 126,
	MT_UNKNOW_79 = 127,
	MT_UNKNOW_80 = 128,
	MT_UNKNOW_81 = 129,
	MT_UNKNOW_82 = 130,
	MT_UNKNOW_83 = 131,
	MT_UNKNOW_84 = 132,
	MT_UNKNOW_85 = 133,
	MT_UNKNOW_86 = 134,
	MT_UNKNOW_87 = 135,
	MT_UNKNOW_88 = 136,
	MT_UPGRADE_SKILL = 137,					//升级技能
	MT_KILL_HANG_MONSTER = 1006,			//击杀关卡怪物
	MT_SMELT_EQUIP = 1007,					//熔炼装备
	MT_STRENGTH_EQUIP = 1008,				//强化装备
	MT_TASK_COPY = 1009,					//进入引导副本
	MT_ACTIVATE_TREASURE = 1010,			//激活宝物
	MT_UPGRADE = 1011,						//激活和提升进阶系统
	MT_UNKNOW_96 = 1019,
	MT_UNKNOW_97 = 1020,
	MT_UNKNOW_98 = 1021,
	MT_UNKNOW_99 = 1022,
	MT_UNKNOW_100 = 1023,
	MT_UNKNOW_101 = 1024,
	MT_UNKNOW_102 = 1025,
	MT_UNKNOW_103 = 1034,
	MT_UNKNOW_104 = 1035,
	MT_UNKNOW_105 = 1043,
	MT_UNKNOW_106 = 1044,
	MT_UNKNOW_107 = 1049,
	MT_UNKNOW_108 = 1051,
	MT_UNKNOW_109 = 1052,
	MT_UNKNOW_110 = 1053,
	MT_UNKNOW_111 = 1054,
	MT_UNKNOW_112 = 1058,
	MT_UNKNOW_113 = 1059,
	MT_UNKNOW_114 = 1060,
	MT_UNKNOW_115 = 1061,
	MT_UNKNOW_116 = 1062,
	MT_UNKNOW_117 = 1063,
	MT_ATTACH_NPC = 2000,					//寻找NPC
	MT_KILL_MONSTER = 2001					//击杀怪物
};

class MissionManager: public CSingleton<MissionManager> {
private:
	friend class CSingleton<MissionManager> ;
	MissionManager();
	~MissionManager();
	set<uint32_t> m_unknow;
public:
	bool Init();
	bool ActorLogin(uint32_t uid);
	bool InitMission(UserCache &cache);
	bool SendMsg(const DataMission &m);
	bool TestCheck(uint32_t uid);
	uint32_t AddIv(string &str, uint32_t t, uint32_t n);
	uint32_t AddMv(string &str, uint32_t t, uint32_t st, uint32_t n);
	uint32_t GetEquipCntByLimit(const UserCache &cache,uint32_t color);

public:
	bool OnKillHangMonster(uint32_t uid, uint32_t id, uint32_t num);
	bool OnHangLevel(uint32_t uid);
	bool onUpgrade(uint32_t uid,uint32_t advanceType,uint32_t num);
	bool onActivateShenqi(uint32_t uid,uint32_t itemId);
	bool onEquipEquip(uint32_t uid, uint32_t star, uint32_t reincarnLevel, uint32_t career);
	bool onColorEquip(uint32_t uid, uint32_t color, uint32_t star, uint32_t reincarnLevel, uint32_t career);
	//bool onUpgradeSkill(uint32_t uid,uint32_t num);
	bool onMission(uint32_t uid, uint32_t type,uint32_t num);
	bool onSubMission(uint32_t uid, uint32_t type,uint32_t subType, uint32_t num);
	bool onUpgradeSkill(uint32_t uid,uint32_t num);
	bool onEnterCopy(uint32_t uid,uint32_t type,uint32_t copyCode);

public:
	int Process(uint32_t uid, logins::SMissionReq *req);
	int Process(uint32_t uid, logins::SMissionCommit *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerMissionList *resp);
};

#endif /* MISSION_MANAGER_H_ */
