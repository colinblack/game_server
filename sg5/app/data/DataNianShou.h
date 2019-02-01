#ifndef _DATA_NIAN_SHOU_H_
#define _DATA_NIAN_SHOU_H_

#include "Kernel.h"

#define NIANSHOU_CHALLENGERS_MAX 1000
struct NianShouChallenger
{
	unsigned uid;
	unsigned damage;	//伤害
	unsigned kingdom;   //国家
	unsigned level;		//等级
	char     name[56];	//攻击者名字
};
struct NianShouData
{
	unsigned fullBlood;
	unsigned blood;
	unsigned ts;
	unsigned standts;
	unsigned challNum;
	unsigned showNum;
	bool rewarded;
	NianShouChallenger challengers[NIANSHOU_CHALLENGERS_MAX];
};

class CDataNianShou
{
public:
	CDataNianShou();
	int Init(const string &path, semdat sem=sem_nianshou);
	int LoadNianShou(unsigned uid, unsigned bossId, unsigned &blood, unsigned &number, int &selfRank, NianShouChallenger &self,
			vector<NianShouChallenger> &top, NianShouChallenger &last,unsigned &fullBlood);
	int AttackNianShou(unsigned uid, unsigned bossId, unsigned damage, const string &name, const unsigned level, const unsigned kingdom,
			bool &dying, unsigned &blood, unsigned &number, int &selfRank, NianShouChallenger &self,
			vector<NianShouChallenger> &top, NianShouChallenger &last, vector<NianShouChallenger> &lucks
			, vector<NianShouChallenger> &dam, bool bAll, vector<NianShouChallenger> &all);
	int ViewNianShou(unsigned uid, unsigned bossId, unsigned &blood, unsigned &fullBlood,unsigned &number, int &selfRank, NianShouChallenger &self,
			vector<NianShouChallenger> &top, NianShouChallenger &last);
	int ViewNianShou( unsigned bossId, unsigned &blood, unsigned &fullblood, unsigned &standts, unsigned ts);
	int SetNianShou( unsigned bossId, unsigned blood, unsigned fullblood, unsigned standts, unsigned ts);
	int SetRewarded(unsigned bossId);

//	unsigned GetNianShouTotalBlood(unsigned bossId)
//	{
//		if (!IsValidNianShouId(bossId))
//			return R_ERR_NO_DATA;
//		return m_nianshouBlood[bossId - NIAN_SHOU_ID_MIN];
//	}

protected:
	CShareMemory m_sh[NIAN_SHOU_ID_MAX - NIAN_SHOU_ID_MIN + 1];
	bool m_init;
	//unsigned m_nianshouBlood[NIAN_SHOU_ID_MAX - NIAN_SHOU_ID_MIN + 1];
	//unsigned m_minNianshouBlood[NIAN_SHOU_ID_MAX - NIAN_SHOU_ID_MIN + 1];
	//unsigned m_maxNianshouBlood[NIAN_SHOU_ID_MAX - NIAN_SHOU_ID_MIN + 1];
};

#endif
