#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE
#include "Common.h"


//数组说明
//typedef CArrayTemplate<tagAnalyseItem,tagAnalyseItem &> CAnalyseItemArray;
typedef std::vector<tagAnalyseItem> CAnalyseItemArray;
//游戏逻辑类
class CGameLogic
{
	//变量定义
	public:
		static const _uint16	m_cbCardDataArray[MAX_CARDS];				//扑克数据
		//函数定义
	public:
		//构造函数
		CGameLogic();
		//析构函数
		virtual ~CGameLogic();
		//控制函数
	public:
		//混乱扑克
		void RandCardData(_uint16 cbCardData[], _uint8 bMaxCount);
		//删除扑克
		bool RemoveCard(tagCardIndex& CardIndex, vector<stCardInfo>& cbRemoveCards);
		//逻辑函数
	public:
		//有效判断
		bool IsValidCard(stCardInfo& cbCardData);
		bool IsValidCardWeaves(vector<_uint16>& wWinCarsWeaves, vector<_uint16>& wCurUserOutCards);
		bool FisrstCardIsValid(vector<_uint16>& wCurUserOutCards);

		//获取胡息
		_uint8 GetWeaveHuXi(const tagWeaveItem & WeaveItem);
		//打印牌信息
		void DebugCards(_uint8 cbCardIndex[], _uint8 count);
		//计算胡息
		_uint8 GetCardsWeaveHuXi( tagCardsWeave CardsWeave[MAX_INDEX], _uint8 cbCardsWeaveCount );
		//更新手牌组合
		bool UpdateCardsWeave(tagCardsWeave CardsWeave[MAX_INDEX], _uint8 &cbCardsWeaveCount, const vector<stCardInfo>& cbRemoveCards);
		//整理普通模式牌
		bool SettleCommonWeaves(const tagCardIndex& cbCardIndex, tagCardsWeave WeaveItem[MAX_INDEX], _uint8 &cbWeaveCount);
		//整理最优模式牌
	//	bool SettleBestWeaves(_uint8 cbCardIndex[MAX_INDEX], tagCardsWeave WeaveItem[MAX_INDEX], _uint8 &cbWeaveCount );
		//获取组合
		bool GetWeaves(_uint8 cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItemArray[MAX_WEAVE], _uint8 &cbWeaveCount, _uint8 cbRand );
		//转换函数
		//扑克转换
		void SwitchToCardIndex(_uint16 cbCardData[], _uint8 bCardCount, tagCardIndex& cbCardIndex);
		_uint16  SwitchToCard(_uint8 cbFirstType, _uint8 cbSecondType, _uint8 cbIndex);

		_uint8 GetOrgCardsWeaveHuXi(tagCardsWeave CardsWeave[MAX_INDEX], _uint8 cbCardsWeaveCount);
	private:
		//分析扑克
		bool AnalyseCard(_uint8 cbCardIndex[MAX_INDEX], CAnalyseItemArray & AnalyseItemArray, _uint8 cbCurrentCard);
	
	//判断函数
	public:
		//胡牌最优结果
		_tint32 isHuOrHeCards(_uint8 cbTotalCards, _uint32 wBaseHe = 15, _uint32 wBaseHuCards = 16);
		void GetHuCardInfoFinal(_uint8 cbTotalCards, _uint8 cbWeaveItemCount, _uint8 cbUserID, _tint32 wUserHuXi[GAME_PLAYER], _tint32 wUserFanShu[GAME_PLAYER], _tint32  wUserScore[GAME_PLAYER], tagWeaveItem WeaveItemArray[MAX_WEAVE], _uint8 cbBaseScore, _uint8 cbGamePlay, _uint8 wBaseHuCards = 15);
		//获取番类型和番数
		_uint32 GetTotalFan(_uint8 cbWeaveItemCount, tagWeaveItem WeaveItemArray[MAX_WEAVE], _uint8 cbGameplay);

		//设置配置信息 
		void GetNoBankerHuBestWeaves(_uint8& cbWeaveItemCount, tagWeaveItem WeaveItemArray[MAX_WEAVE], tagCardsWeave m_CardsWeaveInfo[GAME_PLAYER], _uint8& m_cbCardsWeaveCount,	vector<_uint16>& wcbCenterCards, tagCardIndex	m_cbCardIndex[GAME_PLAYER], _tint32 wUserID);
	private:
		bool							m_bYWS;										//一五十
		bool							m_bHHD;										//红黑点
	public:
		inline void set_m_bYWS(bool bYWS);
		inline void set_m_bHHD(bool bHHD);
};


void CGameLogic::set_m_bYWS(bool bYWS)
{
	m_bYWS = bYWS;
}
void CGameLogic::set_m_bHHD(bool bHHD)
{
	m_bHHD = bHHD;
}
//////////////////////////////////////////////////////////////////////////

#endif
