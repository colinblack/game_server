
#include "GameLogic.h"
#include <map>
#include <algorithm>
#include <iostream>
#include "log.h"
extern Log log;
//扑克数据
#if 0
_uint16 const CGameLogic::m_cbCardDataArray[MAX_CARDS] =
{
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
};

#elif 1
_uint16 const CGameLogic::m_cbCardDataArray[MAX_CARDS] =
{
	 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x109, 0x205, 0x207, 0x218, 0x303, 0x306, 0x004, 0x014, 0x016, 0x004, 0x014, 0x016, 0x01A, 0x026, 0x027,
	 0x02A, 0x02B, 0x105, 0x109, 0x205, 0x207, 0x218, 0x00C, 0x00C, 0x00C, 0x00C, 0x209, 0x209, 0x209, 0x209, 0x002, 0x002, 0x002, 0x002, 0x208, 0x208, 
	 0x208, 0x208, 0x008, 0x008, 0x008, 0x008, 0x107, 0x107, 0x107, 0x107, 0x303, 0x306, 0x004, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105,
	 0x109, 0x205, 0x207, 0x218, 0x303, 0x306, 0x004, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x109, 0x205, 0x207, 0x218, 0x303, 0x306,
};

#endif


//构造函数
CGameLogic::CGameLogic()
{
	m_bYWS = false;
	m_bHHD = false;
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//混乱扑克
void CGameLogic::RandCardData(_uint16 cbCardData[], _uint8 bMaxCount)
{
	//混乱准备
	_uint16 cbCardDataTemp[MAX_CARDS] = {0};
	memcpy(cbCardData, m_cbCardDataArray, sizeof(m_cbCardDataArray));

#if 0
	memcpy(cbCardDataTemp, m_cbCardDataArray, sizeof(m_cbCardDataArray));

	srand(time(NULL));

	//混乱扑克

	_uint8 bRandCount = 0, bPosition = 0;
	do
	{
		bPosition = rand() % (bMaxCount - bRandCount);
		cbCardData[bRandCount++] = cbCardDataTemp[bPosition];
		cbCardDataTemp[bPosition] = cbCardDataTemp[bMaxCount - bRandCount];
	} while (bRandCount < bMaxCount);
#endif
	return;
}

void  CGameLogic::SwitchToCardIndex(_uint16 cbCardData[], _uint8 bCardCount, tagCardIndex& CardIndex)
{
	for (_uint8 i = 0; i < bCardCount; ++i)
	{
		_uint8 cbCardType_1 = (cbCardData[i] & 0xF00) >> 8;
		_uint8 cbCardType_2 = (cbCardData[i] & 0x0F0) >> 4;
		_uint8 cbCardIndex = cbCardData[i] & 0x00F;
		CardIndex.cbCards[cbCardType_1][cbCardType_2][cbCardIndex]++;
	}
}

_uint16 CGameLogic::SwitchToCard(_uint8 cbFirstType, _uint8 cbSecondType, _uint8 cbIndex)
{
	return (cbFirstType << 8) |(cbSecondType << 4) | (cbIndex);
}


//删除扑克
bool CGameLogic::RemoveCard(tagCardIndex& CardIndex, vector<stCardInfo>& cbRemoveCards)
{
	//效验扑克
	//assert(IsValidCard(cbRemoveCard));
	//assert(cbCardIndex[SwitchToCardIndex(cbRemoveCard)]>0);
	_uint8 cbRemoveCardCount = 0;
	//删除扑克
	for (_uint8 i = 0; i< cbRemoveCards.size(); ++i)
	{
		_uint8 cbCardType_1 = (cbRemoveCards[i].cbCard & 0xF00) >> 8;
		_uint8 cbCardType_2 = (cbRemoveCards[i].cbCard & 0x0F0) >> 4;
		_uint8 cbCardIndex = cbRemoveCards[i].cbCard & 0x00F;

		log.info("cbCardType_1: 0x%x, cbCardType_2: 0x%x, cbCardIndex: 0x%x\n", cbCardType_1, cbCardType_2, cbCardIndex);
		log.info("RemoveCard count:  0x%x\n", CardIndex.cbCards[cbCardType_1][cbCardType_2][cbCardIndex]);

		if (CardIndex.cbCards[cbCardType_1][cbCardType_2][cbCardIndex] > 0)
		{
			CardIndex.cbCards[cbCardType_1][cbCardType_2][cbCardIndex]--;
			++cbRemoveCardCount;
		}
	}
	

	if (cbRemoveCardCount == cbRemoveCards.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}


//获取胡息
_uint8 CGameLogic::GetWeaveHuXi(const tagWeaveItem &WeaveItem)
{
	return 0;
}

//打印牌信息
void CGameLogic::DebugCards(_uint8 cbCardIndex[], _uint8 count)
{
	char s[300];
	int slen = 0;
	for (_uint8 i = 0; i < count; i++)
	{
		//slen += sprintf_s(s + slen, 300 - slen, "%d  ", cbCardIndex[i]);//windows才有
		slen += snprintf(s + slen, 300 - slen, "%.2X ", cbCardIndex[i]);
		if ((i + 1) % 10 == 0)
		{
			//slen += sprintf_s(s + slen, 300 - slen, "\n");
			slen += snprintf(s + slen, 300 - slen, "\n");
		}
	}
	printf("cards print. cards:\n%s\n", s);
}

//分析扑克
bool CGameLogic::AnalyseCard(_uint8 cbCardIndex[MAX_INDEX], CAnalyseItemArray &AnalyseItemArray, _uint8 cbCurrentCard)
{
	return true;
}




_uint8 CGameLogic::GetCardsWeaveHuXi(tagCardsWeave CardsWeave[MAX_INDEX], _uint8 cbCardsWeaveCount)
{

	return 1;
}

_uint8 CGameLogic::GetOrgCardsWeaveHuXi(tagCardsWeave CardsWeave[MAX_INDEX], _uint8 cbCardsWeaveCount)
{
	
	return 1;
}

bool CGameLogic::UpdateCardsWeave(tagCardsWeave CardsWeave[MAX_INDEX], _uint8 &cbCardsWeaveCount, const vector<stCardInfo>& cbRemoveCards)
{
	const _uint8 maxNum = 12;
	for (_uint8 i = 0; i < cbRemoveCards.size(); ++i)
	{
		_uint16 wIndex = cbRemoveCards[i].cbCard;
		_uint8 cbRow = cbRemoveCards[i].cbRow;
		_uint8 cbCol = cbRemoveCards[i].cbCol;

		log.info("UpdateCardsWeave, wIndex 0x%x , card 0x%x  cbCardsWeaveCount: %d, cbCardCount: %d,  cbRow %d, cbCol %d \n", wIndex, CardsWeave[cbCol].cbCardList[cbRow], cbCardsWeaveCount, CardsWeave[cbCol].cbCardCount, cbRow, cbCol);
		if (cbCol >= 0 && cbCol < cbCardsWeaveCount && cbRow >= 0 && cbRow < CardsWeave[cbCol].cbCardCount)
		{
			if (CardsWeave[cbCol].cbCardList[cbRow] == wIndex)
			{
				CardsWeave[cbCol].cbCardList[cbRow] = 0;
			}
		}
	}
	log.info("UpdateCardsWeave A A A \n");
	for (_uint8 i = 0; i < cbCardsWeaveCount; ++i)
	{
		for (_uint8 j = 0; j < CardsWeave[i].cbCardCount; ++j)
		{
			log.info("UpdateCardsWeave, card 0x%x \n", CardsWeave[i].cbCardList[j]);
		}
		log.info("\n");
	}


	_uint16 wCardListTemp[maxNum] = { 0 };
	for (_uint8 i = 0; i < cbCardsWeaveCount; ++i)
	{
		memset(wCardListTemp, 0, sizeof(wCardListTemp));
		_uint8 cnt = 0;
		for (_uint8 j = 0; j < CardsWeave[i].cbCardCount; ++j)
		{
			if (CardsWeave[i].cbCardList[j] == 0)
			{
				continue;
			}
			wCardListTemp[cnt++] = CardsWeave[i].cbCardList[j];
		}
		for (_uint8 j = 0; j < cnt; ++j)
		{
			log.info("wCardListTemp, card 0x%x \n", wCardListTemp[j]);
		}

		log.info("cnt  %d \n", cnt);
		memcpy(CardsWeave[i].cbCardList, wCardListTemp, sizeof(CardsWeave[i].cbCardList));
		CardsWeave[i].cbCardCount = cnt;
	}


	for (_uint8 i = 0; i < cbCardsWeaveCount; ++i)
	{
	
		if (CardsWeave[i].cbCardCount == 0)
		{
			for (_uint8 m = i + 1, n = i; m < cbCardsWeaveCount; ++m)
			{
				CardsWeave[n].cbCardCount = CardsWeave[m].cbCardCount;
				memcpy(CardsWeave[n].cbCardList, CardsWeave[m].cbCardList, sizeof(CardsWeave[n].cbCardList));
				n++;
			}
			cbCardsWeaveCount--;
		}
	}
	for (_uint8 i = 0; i < cbCardsWeaveCount; ++i)
	{
		log.info("UpdateCardsWeave after copy  %d \n", CardsWeave[i].cbCardCount);
	}

	for (_uint8 i = 0; i < cbCardsWeaveCount; ++i)
	{
		log.info("UpdateCardsWeave, card count final 0x%x \n", CardsWeave[i].cbCardCount);
		for (_uint8 j = 0; j < CardsWeave[i].cbCardCount; ++j)
		{
			log.info("UpdateCardsWeave, card final 0x%x \n", CardsWeave[i].cbCardList[j]);
		}
		log.info("\n");
	}

	return true;
}

//整理普通模式牌
bool CGameLogic::SettleCommonWeaves(const tagCardIndex& cbCardIndex, tagCardsWeave WeaveItem[MAX_INDEX], _uint8 &cbWeaveCount)
{
	tagCardIndex cbCardIndexTemp = const_cast<tagCardIndex&>(cbCardIndex);
   cbWeaveCount = 0;
	memset(WeaveItem, 0, sizeof(tagCardsWeave) * MAX_INDEX);

	for (_uint8 i = 0; i < CARD_TYPE_1; ++i)   
	{
		for (_uint8 j = 0; j < CARD_TYPE_2; ++j)
		{
			for (_uint8 k = 0; k < CARD_INDEX; ++k)
			{
				if (cbCardIndexTemp.cbCards[i][j][k] == 4)   //提取四牌
				{
					_uint16 wCards = SwitchToCard(i, j, k);
					WeaveItem[cbWeaveCount].cbCardCount = 4;
					WeaveItem[cbWeaveCount].cbCardList[0] = wCards;
					WeaveItem[cbWeaveCount].cbCardList[1] = wCards;
					WeaveItem[cbWeaveCount].cbCardList[2] = wCards;
					WeaveItem[cbWeaveCount++].cbCardList[3] = wCards;
					cbCardIndexTemp.cbCards[i][j][k] = 0;
				}
				if (cbCardIndexTemp.cbCards[i][j][k] == 3)   //提取三牌
				{
					_uint16 wCards = SwitchToCard(i, j, k);
					WeaveItem[cbWeaveCount].cbCardCount = 3;
					WeaveItem[cbWeaveCount].cbCardList[0] = wCards;
					WeaveItem[cbWeaveCount].cbCardList[1] = wCards;
					WeaveItem[cbWeaveCount++].cbCardList[2] = wCards;
					cbCardIndexTemp.cbCards[i][j][k] = 0;
				}
				if (cbCardIndexTemp.cbCards[i][j][k] == 2)   //提取二牌
				{
					_uint16 wCards = SwitchToCard(i, j, k);
					WeaveItem[cbWeaveCount].cbCardCount = 2;
					WeaveItem[cbWeaveCount].cbCardList[0] = wCards;
					WeaveItem[cbWeaveCount++].cbCardList[1] = wCards;
					cbCardIndexTemp.cbCards[i][j][k] = 0;

				}
			}
		}
	}

	//同一类型的牌放在一起
	if (cbCardIndexTemp.cbCards[0][0][12] > 0 || cbCardIndexTemp.cbCards[0][0][2] > 0
			|| cbCardIndexTemp.cbCards[0][0][8] > 0 || cbCardIndexTemp.cbCards[0][0][4] > 0)
	{
		if (cbCardIndexTemp.cbCards[0][0][12] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x00C;
			cbCardIndexTemp.cbCards[0][0][12]--;
		}
		if (cbCardIndexTemp.cbCards[0][0][2] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x002;
			cbCardIndexTemp.cbCards[0][0][2]--;
		}
		if (cbCardIndexTemp.cbCards[0][0][8] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x008;
			cbCardIndexTemp.cbCards[0][0][8]--;
		}
		if (cbCardIndexTemp.cbCards[0][0][4] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x004;
			cbCardIndexTemp.cbCards[0][0][4]--;
		}
		++cbWeaveCount;
	}

	//中三
	if (cbCardIndexTemp.cbCards[0][1][4] > 0 || cbCardIndexTemp.cbCards[0][1][6] > 0
			|| cbCardIndexTemp.cbCards[0][1][10] > 0)
	{
		if (cbCardIndexTemp.cbCards[0][1][4] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x014;
			cbCardIndexTemp.cbCards[0][1][4]--;
		}
		if (cbCardIndexTemp.cbCards[0][1][6] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x016;
			cbCardIndexTemp.cbCards[0][1][6]--;
		}
		if (cbCardIndexTemp.cbCards[0][1][10] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x01A;
			cbCardIndexTemp.cbCards[0][1][10]--;
		}
		++cbWeaveCount;
	}



	//下幺
	if (cbCardIndexTemp.cbCards[0][2][6] > 0 || cbCardIndexTemp.cbCards[0][2][7] > 0
		|| cbCardIndexTemp.cbCards[0][2][10] > 0 || cbCardIndexTemp.cbCards[0][2][11] > 0)
	{
		if (cbCardIndexTemp.cbCards[0][2][6] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x026;
			cbCardIndexTemp.cbCards[0][2][6]--;
		}
		if (cbCardIndexTemp.cbCards[0][2][7] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x027;
			cbCardIndexTemp.cbCards[0][2][7]--;
		}
		if (cbCardIndexTemp.cbCards[0][2][10] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x02A;
			cbCardIndexTemp.cbCards[0][2][10]--;
		}
		if (cbCardIndexTemp.cbCards[0][2][11] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x02B;
			cbCardIndexTemp.cbCards[0][2][11]--;
		}
		++cbWeaveCount;
	}

	//0x105, 0x107, 0x109
	if (cbCardIndexTemp.cbCards[1][0][5] > 0 || cbCardIndexTemp.cbCards[1][0][7] > 0
		|| cbCardIndexTemp.cbCards[1][0][9] > 0)
	{
		if (cbCardIndexTemp.cbCards[1][0][5] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x105;
			cbCardIndexTemp.cbCards[1][0][5]--;
		}
		if (cbCardIndexTemp.cbCards[1][0][7] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x107;
			cbCardIndexTemp.cbCards[1][0][7]--;
		}
		if (cbCardIndexTemp.cbCards[1][0][9] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x109;
			cbCardIndexTemp.cbCards[1][0][9]--;
		}
		++cbWeaveCount;
	}


	//0x205, 0x207, 0x208, 0x209, 0x218,

	if (cbCardIndexTemp.cbCards[2][0][5] > 0 || cbCardIndexTemp.cbCards[2][0][7] > 0 || cbCardIndexTemp.cbCards[2][0][8] > 0 
			|| cbCardIndexTemp.cbCards[2][0][9] > 0 || cbCardIndexTemp.cbCards[2][1][8] > 0)
	{
		if (cbCardIndexTemp.cbCards[2][0][5] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x205;
			cbCardIndexTemp.cbCards[2][0][5]--;
		}
		if (cbCardIndexTemp.cbCards[2][0][7] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x207;
			cbCardIndexTemp.cbCards[2][0][7]--;
		}
		if (cbCardIndexTemp.cbCards[2][0][8] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x208;
			cbCardIndexTemp.cbCards[2][0][8]--;
		}
		if (cbCardIndexTemp.cbCards[2][0][9] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x209;
			cbCardIndexTemp.cbCards[2][0][9]--;
		}
		if (WeaveItem[cbWeaveCount].cbCardCount <= 4 && cbCardIndexTemp.cbCards[2][1][8] > 0)
		{
			WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = 0x218;
			cbCardIndexTemp.cbCards[2][1][8]--;
		}

		++cbWeaveCount;
	}


	//if (cbCardIndexTemp.cbCards[0][0][2] > 0)   //地八
	//{
	//	if (cbCardIndexTemp.cbCards[2][0][8] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x208;
	//		cbCardIndexTemp.cbCards[2][0][8]--;
	//	}

	//	if (cbCardIndexTemp.cbCards[2][1][8] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x218;
	//		cbCardIndexTemp.cbCards[2][1][8]--;
	//	}

	//	if (WeaveItem[cbWeaveCount].cbCardCount >= 1)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[0] = 0x002;
	//		WeaveItem[cbWeaveCount++].cbCardCount++;
	//	}
	//}

	//if (cbCardIndexTemp.cbCards[0][0][8] > 0)   //人七
	//{
	//	if (cbCardIndexTemp.cbCards[1][0][7] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x107;
	//		cbCardIndexTemp.cbCards[1][0][7]--;
	//	}

	//	if (cbCardIndexTemp.cbCards[2][0][7] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x207;
	//		cbCardIndexTemp.cbCards[2][0][7]--;
	//	}

	//	if (WeaveItem[cbWeaveCount].cbCardCount >= 1)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[0] = 0x008;
	//		WeaveItem[cbWeaveCount++].cbCardCount++;
	//	}
	//}


	//if (cbCardIndexTemp.cbCards[0][0][4] > 0)  //和五
	//{
	//	if (cbCardIndexTemp.cbCards[1][0][5] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x105;
	//		cbCardIndexTemp.cbCards[1][0][5]--;
	//	}

	//	if (cbCardIndexTemp.cbCards[2][0][5] > 0)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[++WeaveItem[cbWeaveCount].cbCardCount] = 0x205;
	//		cbCardIndexTemp.cbCards[2][0][5]--;
	//	}

	//	if (WeaveItem[cbWeaveCount].cbCardCount >= 1)
	//	{
	//		WeaveItem[cbWeaveCount].cbCardList[0] = 0x004;
	//		WeaveItem[cbWeaveCount++].cbCardCount++;
	//	}
	//}

	////凑四张
	//for (_uint8 i = 0; i < cbWeaveCount; ++i)
	//{
	//	if (WeaveItem[i].cbCardCount < 4)
	//	{
	//		_uint8 u8Type = (WeaveItem[i].cbCardList[0] >> 8 & 0xF);

	//		if (u8Type ^ (WeaveItem[i].cbCardList[1] >> 8 & 0xF))
	//		{
	//			continue;
	//		}

	//		for (_uint8 i = 0; i < CARD_TYPE_2; ++i)
	//		{
	//			for (_uint8 j = 0; j < CARD_INDEX; ++j)
	//			{
	//				if (cbCardIndexTemp.cbCards[u8Type][i][j] > 0)
	//				{
	//					WeaveItem[i].cbCardList[WeaveItem[i].cbCardCount++] = cbCardIndexTemp.cbCards[u8Type][i][j];
	//					cbCardIndexTemp.cbCards[u8Type][i][j]--;
	//				}
	//			}
	//		}
	//	}
	// }
		//其他的牌


	for (_uint8 i = 0; i < CARD_TYPE_1; ++i)
	{
		for (_uint8 j = 0; j < CARD_TYPE_2; ++j)
		{
			for (_uint8 k = 0; k < CARD_INDEX; ++k)
			{
				if (cbCardIndexTemp.cbCards[i][j][k] > 0 && WeaveItem[cbWeaveCount].cbCardCount <= 4)
				{
					if (WeaveItem[cbWeaveCount].cbCardCount == 4)
					{
						++cbWeaveCount;
					}
					WeaveItem[cbWeaveCount].cbCardList[WeaveItem[cbWeaveCount].cbCardCount++] = SwitchToCard(i, j, k);
					cbCardIndexTemp.cbCards[i][j][k]--;
				}
			}
		}
	}
		return true;
}

	//整理最优模式牌
	//bool CGameLogic::SettleBestWeaves(_uint8 cbCardIndex[MAX_INDEX], tagCardsWeave WeaveItem[MAX_INDEX], _uint8 &cbWeaveCount)
	//{
	//	return true;
	//}


//胡牌最优结果
void CGameLogic::GetHuCardInfoFinal(_uint8 cbTotalCards, _uint8 cbWeaveItemCount, _uint8 cbUserID, _tint32 wUserHuXi[GAME_PLAYER], _tint32 wUserFanShu[GAME_PLAYER], _tint32  wUserScore[GAME_PLAYER],  tagWeaveItem WeaveItemArray[MAX_WEAVE], _uint8 cbBaseScore, _uint8 cbGamePlay, _uint8 wBaseHuCards)
{
	_uint8 cbSecondUsr = (cbUserID + 1) % GAME_PLAYER;
	_uint8 cbThirdUsr = (cbSecondUsr + 1) % GAME_PLAYER;
	

	wUserFanShu[cbUserID] = GetTotalFan(cbWeaveItemCount, WeaveItemArray, cbGamePlay);
	if (cbGamePlay == YEZI)
	{
		wUserScore[cbUserID] = wUserFanShu[cbUserID] * cbBaseScore * (cbTotalCards - wBaseHuCards -1) * 2;		
	}
	else
	{
		wUserScore[cbUserID] = wUserFanShu[cbUserID] * cbBaseScore * 2;
	}
	wUserScore[cbSecondUsr] = (wUserScore[cbUserID] / 2)*(-1);
	wUserScore[cbThirdUsr] = wUserScore[cbSecondUsr];
}

_tint32 CGameLogic::isHuOrHeCards(_uint8 cbTotalCards, _uint32 wBaseHe, _uint32 wBaseHuCards)
{
	//16张起胡

	//胡牌算番
	log.info("isHuOrHeCards cbTotalCards: %d wBaseHuCards %d \n", cbTotalCards, wBaseHuCards);

	if (cbTotalCards == wBaseHe)
	{
		return ACK_HUANG;
	}

	if (cbTotalCards >= wBaseHuCards)
	{
		return ACK_CHIHU;
	}

	return -1;
}

void  CGameLogic::GetNoBankerHuBestWeaves(_uint8& cbWeaveItemCount, tagWeaveItem WeaveItemArray[MAX_WEAVE], tagCardsWeave m_CardsWeaveInfo[GAME_PLAYER], _uint8& m_cbCardsWeaveCount, vector<_uint16>& wcbCenterCards, tagCardIndex	m_cbCardIndex[GAME_PLAYER], _tint32 wUserID)
{	
		std::map<_uint16, _uint32> stCardsMap;
		std::map<_uint16, _uint32> stWinMap;
		vector<_uint16> wcbOutCards;
		std::sort(wcbCenterCards.begin(), wcbCenterCards.end());

		if (wcbCenterCards.size() >= 1)
		{
			for (_uint8 i = 0; i < wcbCenterCards.size(); ++i)
			{
				stCardsMap[wcbCenterCards[i]]++;
			}
			_uint16 wFirstCardKey = stCardsMap.begin()->first;
			_uint16 wSeconCardKey = (++stCardsMap.begin())->first;
			_uint8 cbCardsSize = wcbCenterCards.size();
			_uint8 cbUserType_1 = (wcbCenterCards[0] >> 8) & 0xF;
			_uint8 cbUserType_2 = (wcbCenterCards[0] >> 4) & 0xF;
			_uint8 cbUserIndex = wcbCenterCards[0] & 0xF;

			if (stCardsMap.size() == 2 || stCardsMap.size() == 3)
			{
				if (m_cbCardIndex[wUserID].cbCards[0][0][12] + m_cbCardIndex[wUserID].cbCards[1][0][9]
					+ m_cbCardIndex[wUserID].cbCards[2][0][9] >= cbCardsSize)
				{
					_uint8& cbIndex_1 = m_cbCardIndex[wUserID].cbCards[0][0][12];
					_uint8& cbIndex_2 = m_cbCardIndex[wUserID].cbCards[1][0][9];
					_uint8& cbIndex_3 = m_cbCardIndex[wUserID].cbCards[2][0][9];

					while (cbCardsSize - 1 && cbIndex_1)
					{
						wcbOutCards.push_back(0x00C);
						--cbCardsSize;
						--cbIndex_1;
					}
					if (cbCardsSize > 0)
					{
						if (cbIndex_2 >= cbIndex_3)
						{
							while (cbCardsSize && cbIndex_2)
							{
								wcbOutCards.push_back(0x109);
								--cbCardsSize;
								--cbIndex_2;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_3)
								{
									wcbOutCards.push_back(0x209);
									--cbCardsSize;
									--cbIndex_3;
								}
							}

						}
						else
						{
							while (cbCardsSize && cbIndex_3)
							{
								wcbOutCards.push_back(0x209);
								--cbCardsSize;
								--cbIndex_3;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_2)
								{
									wcbOutCards.push_back(0x109);
									--cbCardsSize;
									--cbIndex_2;
								}
							}
						}
					}
				}

				else if (m_cbCardIndex[wUserID].cbCards[0][0][2] + m_cbCardIndex[wUserID].cbCards[2][0][8]
					+ m_cbCardIndex[wUserID].cbCards[2][1][8] >= cbCardsSize)

				{
					_uint8& cbIndex_1 = m_cbCardIndex[wUserID].cbCards[0][0][2];
					_uint8& cbIndex_2 = m_cbCardIndex[wUserID].cbCards[2][0][8];
					_uint8& cbIndex_3 = m_cbCardIndex[wUserID].cbCards[2][1][8];

					while (cbCardsSize - 1&& cbIndex_1)
					{
						wcbOutCards.push_back(0x002);
						--cbCardsSize;
						--cbIndex_1;
					}

					if (cbCardsSize > 0)
					{
						if (cbIndex_2 >= cbIndex_3)
						{
							while (cbCardsSize && cbIndex_2)
							{
								wcbOutCards.push_back(0x208);
								--cbCardsSize;
								--cbIndex_2;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_3)
								{
									wcbOutCards.push_back(0x218);
									--cbCardsSize;
									--cbIndex_3;
								}
							}

						}
						else
						{
							while (cbCardsSize && cbIndex_3)
							{
								wcbOutCards.push_back(0x218);
								--cbCardsSize;
								--cbIndex_3;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_2)
								{
									wcbOutCards.push_back(0x208);
									--cbCardsSize;
									--cbIndex_2;
								}
							}
						}

					}
				}
				else if (m_cbCardIndex[wUserID].cbCards[0][0][8] + m_cbCardIndex[wUserID].cbCards[1][0][7]
					+ m_cbCardIndex[wUserID].cbCards[2][0][7] >= cbCardsSize)
				{
					_uint8& cbIndex_1 = m_cbCardIndex[wUserID].cbCards[0][0][8];
					_uint8& cbIndex_2 = m_cbCardIndex[wUserID].cbCards[1][0][7];
					_uint8& cbIndex_3 = m_cbCardIndex[wUserID].cbCards[2][0][7];

					while (cbCardsSize - 1 && cbIndex_1)
					{
						wcbOutCards.push_back(0x008);
						--cbCardsSize;
						--cbIndex_1;

					}

					if (cbCardsSize > 0)
					{
						if (cbIndex_2 >= cbIndex_3)
						{
							while (cbCardsSize && cbIndex_2)
							{
								wcbOutCards.push_back(0x107);
								--cbCardsSize;
								--cbIndex_2;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_3)
								{
									wcbOutCards.push_back(0x207);
									--cbCardsSize;
									--cbIndex_3;
								}
							}

						}
						else
						{
							while (cbCardsSize && cbIndex_3)
							{
								wcbOutCards.push_back(0x207);
								--cbCardsSize;
								--cbIndex_3;
							}
							if (cbCardsSize > 0)
							{
								while (cbCardsSize && cbIndex_2)
								{
									wcbOutCards.push_back(0x107);
									--cbCardsSize;
									--cbIndex_2;
								}
							}
						}

					}
				}
			}

			if (stCardsMap.size() == 1)
			{
				if (cbUserType_1 == 0)
				{
					if (cbUserType_2 == 0)
					{
						if (cbUserIndex == 0x2 && m_cbCardIndex[wUserID].cbCards[0][0][12] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][12]--;
								wcbOutCards.push_back(0x00C);
							}
						}
						if (cbUserIndex == 0x8)
						{
							if (m_cbCardIndex[wUserID].cbCards[0][0][12] >= cbCardsSize)
							{
								while (cbCardsSize--)
								{
									m_cbCardIndex[wUserID].cbCards[0][0][12]--;
									wcbOutCards.push_back(0x00C);
								}
							}
							else if (m_cbCardIndex[wUserID].cbCards[0][0][2] >= cbCardsSize)
							{
								while (cbCardsSize--)
								{
									m_cbCardIndex[wUserID].cbCards[0][0][2]--;
									wcbOutCards.push_back(0x002);
								}
							}
						}
						if (cbUserIndex == 0x04)
						{
							if (m_cbCardIndex[wUserID].cbCards[0][0][12] >= cbCardsSize)
							{
								while (cbCardsSize--)
								{
									m_cbCardIndex[wUserID].cbCards[0][0][12]--;
									wcbOutCards.push_back(0x00C);
								}
							}
							else if (m_cbCardIndex[wUserID].cbCards[0][0][2] >= cbCardsSize)
							{
								while (cbCardsSize--)
								{
									m_cbCardIndex[wUserID].cbCards[0][0][2]--;
									wcbOutCards.push_back(0x002);
								}
							}
							else if (m_cbCardIndex[wUserID].cbCards[0][0][8] >= cbCardsSize)
							{
								while (cbCardsSize--)
								{
									m_cbCardIndex[wUserID].cbCards[0][0][8]--;
									wcbOutCards.push_back(0x008);
								}
							}
						}
					}
					else if (cbUserType_2 == 1)
					{
						if (m_cbCardIndex[wUserID].cbCards[0][0][12] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][12]--;
								wcbOutCards.push_back(0x00C);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][2] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][2]--;
								wcbOutCards.push_back(0x002);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][8]--;
								wcbOutCards.push_back(0x008);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][4] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][4]--;
								wcbOutCards.push_back(0x004);
							}
						}
					}
					else if (cbUserType_2 == 2)
					{
						if (m_cbCardIndex[wUserID].cbCards[0][0][12] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][12]--;
								wcbOutCards.push_back(0x00C);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][2] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][2]--;
								wcbOutCards.push_back(0x002);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][8]--;
								wcbOutCards.push_back(0x008);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][0][4] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][0][4]--;
								wcbOutCards.push_back(0x004);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][1][4] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][1][4]--;
								wcbOutCards.push_back(0x014);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][1][6] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][1][6]--;
								wcbOutCards.push_back(0x016);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[0][1][10] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[0][1][10]--;
								wcbOutCards.push_back(0x01A);
							}
						}
					}
				}
				if (cbUserType_1 == 1)
				{
					if (cbUserIndex == 0x7)
					{
						if (m_cbCardIndex[wUserID].cbCards[1][0][9] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[1][0][9]--;
								wcbOutCards.push_back(0x109);
							}
						}
					}
					if (cbUserIndex == 0x5)
					{
						if (m_cbCardIndex[wUserID].cbCards[1][0][9] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[1][0][9]--;
								wcbOutCards.push_back(0x109);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[1][0][7] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[1][0][7]--;
								wcbOutCards.push_back(0x107);
							}
						}	
					}
				}
				if (cbUserType_1 == 2)
				{
					if (cbUserIndex == 0x8 || cbUserIndex == 0x8)
					{
						if (m_cbCardIndex[wUserID].cbCards[2][0][9] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][9]--;
								wcbOutCards.push_back(0x209);
							}
						}
					}
					if (cbUserIndex == 0x7)
					{
						if (m_cbCardIndex[wUserID].cbCards[2][0][9] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][9]--;
								wcbOutCards.push_back(0x209);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[2][0][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][8]--;
								wcbOutCards.push_back(0x208);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[2][1][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][1][8]--;
								wcbOutCards.push_back(0x218);
							}
						}
					}
					if (cbUserIndex == 0x5)
					{
						if (m_cbCardIndex[wUserID].cbCards[2][0][9] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][9]--;
								wcbOutCards.push_back(0x209);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[2][0][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][8]--;
								wcbOutCards.push_back(0x208);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[2][1][8] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][1][8]--;
								wcbOutCards.push_back(0x218);
							}
						}
						else if (m_cbCardIndex[wUserID].cbCards[2][0][7] >= cbCardsSize)
						{
							while (cbCardsSize--)
							{
								m_cbCardIndex[wUserID].cbCards[2][0][7]--;
								wcbOutCards.push_back(0x207);
							}
						}
					}
				}
			}

		}


		if (wcbOutCards.size() == wcbCenterCards.size())
		{
			wcbCenterCards = wcbOutCards;
			for (_uint8 i = 0; i < wcbCenterCards.size(); ++i)
			{
				WeaveItemArray[cbWeaveItemCount].cbCardList[i] = wcbCenterCards[i];
				WeaveItemArray[cbWeaveItemCount].cbCardCount++;
				log.info("GetNoBankerHuBestWeaves, wcbCenterCards: %d \n", wcbCenterCards[i]);
			}
			cbWeaveItemCount++;
		}
}


_uint32 CGameLogic::GetTotalFan(_uint8 cbWeaveItemCount, tagWeaveItem WeaveItemArray[MAX_WEAVE], _uint8 cbGameplay)
{
	_uint8  cbFan = 1;
	log.info("GetTotalFan: cbGameplay: %d \n ", cbGameplay);
	for (_uint8 i = 0; i < cbWeaveItemCount; ++i)
	{
		//排序
		for (_uint8 j = 0; j < WeaveItemArray[i].cbCardCount - 1; ++j)
		{
			for (_uint8 k = i; k< WeaveItemArray[i].cbCardCount - i; ++k)
			{
				if (WeaveItemArray[i].cbCardList[k] > WeaveItemArray[i].cbCardList[k + 1])
				{
					std::swap(WeaveItemArray[i].cbCardList[k], WeaveItemArray[i].cbCardList[k + 1]);
				}
			}
		}

		for (_uint8 j = 0; j < WeaveItemArray[i].cbCardCount; ++j)
		{
			log.info("GetTotalFan: cards : 0x%x \n ", WeaveItemArray[i].cbCardList[j]);
		}
		if (WeaveItemArray[i].cbCardCount == 3)
		{
			if ((WeaveItemArray[i].cbCardList[0] == 0x00C && WeaveItemArray[i].cbCardList[1] == 0x00C && WeaveItemArray[i].cbCardList[2] == 0x00C)
				|| (WeaveItemArray[i].cbCardList[0] == 0x002 && WeaveItemArray[i].cbCardList[1] == 0x002 && WeaveItemArray[i].cbCardList[2] == 0x002)
				|| (WeaveItemArray[i].cbCardList[0] == 0x008 && WeaveItemArray[i].cbCardList[1] == 0x008 && WeaveItemArray[i].cbCardList[2] == 0x008)
				|| (WeaveItemArray[i].cbCardList[0] == 0x004 && WeaveItemArray[i].cbCardList[1] == 0x004 && WeaveItemArray[i].cbCardList[2] == 0x004))
			{
				cbFan *= 2;
			}
		}

		if (WeaveItemArray[i].cbCardCount > 3)
		{
			if (WeaveItemArray[i].cbCardList[0] == 0x00C && WeaveItemArray[i].cbCardList[1] == 0x00C && WeaveItemArray[i].cbCardList[2] == 0x00C && WeaveItemArray[i].cbCardList[3] == 0x00C)
			{
				cbFan *= 4;
			}
			if (WeaveItemArray[i].cbCardList[0] == 0x002 && WeaveItemArray[i].cbCardList[1] == 0x002 && WeaveItemArray[i].cbCardList[2] == 0x002)
			{
				cbFan *= 2;
			}
			if (WeaveItemArray[i].cbCardList[0] == 0x008 && WeaveItemArray[i].cbCardList[1] == 0x008 && WeaveItemArray[i].cbCardList[2] == 0x008 )
			{
				cbFan *= 2;
			}
			if (WeaveItemArray[i].cbCardList[0] == 0x004 && WeaveItemArray[i].cbCardList[1] == 0x004 && WeaveItemArray[i].cbCardList[2] == 0x004 )
			{
				cbFan *= 2;
			}
			//棍子番
			if (cbGameplay == STICK)
			{
				bool bFind = false;
				if (WeaveItemArray[i].cbCardList[0] == 0x00C)
				{
					_uint8 j = 1;
					for (; j < WeaveItemArray[i].cbCardCount; ++j)											//可能是天九
					{
						if (WeaveItemArray[i].cbCardList[j] == 0x109 || WeaveItemArray[i].cbCardList[j] == 0x209)
						{
							bFind = true;
							break;
						}
					}
					if (bFind == true &&j + 3 < WeaveItemArray[i].cbCardCount)
					{
						if ((WeaveItemArray[i].cbCardList[j] == 0x209 && WeaveItemArray[i].cbCardList[j + 1] == 0x209
							&& WeaveItemArray[i].cbCardList[j + 2] == 0x209 && WeaveItemArray[i].cbCardList[j + 3] == 0x209)
							|| (WeaveItemArray[i].cbCardList[j] == 0x109 && WeaveItemArray[i].cbCardList[j + 1] == 0x109
								&& WeaveItemArray[i].cbCardList[j + 2] == 0x109 && WeaveItemArray[i].cbCardList[j + 3] == 0x109))
						{
							cbFan *= 2;
						}
					}
				}
				else if (WeaveItemArray[i].cbCardList[0] == 0x002)
				{
					_uint8 j = 1;
					for (; j < WeaveItemArray[i].cbCardCount; ++j)											//可能是地八
					{
						if (WeaveItemArray[i].cbCardList[j] == 0x208 || WeaveItemArray[i].cbCardList[j] == 0x218)
						{
							bFind = true;
							break;
						}
					}
					if (bFind == true && j + 3 < WeaveItemArray[i].cbCardCount)
					{
						if ((WeaveItemArray[i].cbCardList[j] == 0x208 && WeaveItemArray[i].cbCardList[j + 1] == 0x208
							&& WeaveItemArray[i].cbCardList[j + 2] == 0x208 && WeaveItemArray[i].cbCardList[j + 3] == 0x208)
							|| (WeaveItemArray[i].cbCardList[j] == 0x218 && WeaveItemArray[i].cbCardList[j + 1] == 0x218
							&& WeaveItemArray[i].cbCardList[j + 2] == 0x218 && WeaveItemArray[i].cbCardList[j + 3] == 0x218))
						{
							cbFan *= 2;
						}
					}
				}
				else if (WeaveItemArray[i].cbCardList[0] == 0x008)
				{
					_uint8 j = 1;
					for (; j < WeaveItemArray[i].cbCardCount; ++j)											//可能是人七
					{
						if (WeaveItemArray[i].cbCardList[j] == 0x107 || WeaveItemArray[i].cbCardList[j] == 0x207)
						{
							bFind = true;
							break;
						}
					}
					if (bFind == true && j + 3 < WeaveItemArray[i].cbCardCount)
					{
						if ((WeaveItemArray[i].cbCardList[j] == 0x107 && WeaveItemArray[i].cbCardList[j + 1] == 0x107
							&& WeaveItemArray[i].cbCardList[j + 2] == 0x107 && WeaveItemArray[i].cbCardList[j + 3] == 0x107)
							|| (WeaveItemArray[i].cbCardList[j] == 0x207 && WeaveItemArray[i].cbCardList[j + 1] == 0x207
								&& WeaveItemArray[i].cbCardList[j + 2] == 0x207 && WeaveItemArray[i].cbCardList[j + 3] == 0x207))
						{
							cbFan *= 2;
						}
					}
				}
				else if (WeaveItemArray[i].cbCardList[0] == 0x004)										//可能和五
				{
					_uint8 j = 1;
					for (; j < WeaveItemArray[i].cbCardCount; ++j)											
					{
						if (WeaveItemArray[i].cbCardList[j] == 0x105 || WeaveItemArray[i].cbCardList[j] == 0x205)
						{
							bFind = true;
							break;
						}
					}
					if (bFind == true && j + 3 < WeaveItemArray[i].cbCardCount)
					{
						if ((WeaveItemArray[i].cbCardList[j] == 0x105 && WeaveItemArray[i].cbCardList[j + 1] == 0x105
							&& WeaveItemArray[i].cbCardList[j + 2] == 0x105 && WeaveItemArray[i].cbCardList[j + 3] == 0x105)
							|| (WeaveItemArray[i].cbCardList[j] == 0x205 && WeaveItemArray[i].cbCardList[j + 1] == 0x205
								&& WeaveItemArray[i].cbCardList[j + 2] == 0x205 && WeaveItemArray[i].cbCardList[j + 3] == 0x205))
						{
							cbFan *= 2;
						}
					}
				}
				else
				{
					if (WeaveItemArray[i].cbCardCount >= 4)
					{
						if (WeaveItemArray[i].cbCardList[0] == WeaveItemArray[i].cbCardList[1] 
							&& WeaveItemArray[i].cbCardList[0] == WeaveItemArray[i].cbCardList[2]
							&& WeaveItemArray[i].cbCardList[0] == WeaveItemArray[i].cbCardList[3])
						{
							cbFan *= 2;                                    //其他的牌
						}
					
					}				
				}
			}
		}
	}

	return  cbFan;
}

bool CGameLogic::IsValidCard(stCardInfo& cbCardData)
{
	_uint8 cbType_1 = (cbCardData.cbCard & 0xF00) >> 8;
	_uint8 cbType_2 = (cbCardData.cbCard & 0x0F0) >> 4;
	_uint8 cbIndex = cbCardData.cbCard & 0x00F;

	if ((cbType_1 >= 0 && cbType_1 <= 3) && (cbType_2 >= 0 && cbType_2 <= 2) && (cbIndex >= 2 && cbIndex <= 12))
	{
		return true;
	}
	return false;
}


bool CGameLogic::FisrstCardIsValid(vector<_uint16>& wCurUserOutCards)
{
	if (wCurUserOutCards.size() > 12 )
	{
		return false;
	}

	std::map<_uint16, _uint32> stCardsMap;
	for (_uint8 i = 0; i < wCurUserOutCards.size(); ++i)
	{
		stCardsMap[wCurUserOutCards[i]]++;
	}
	std::cout << stCardsMap.size() << std::endl;

	if (stCardsMap.size() > 2)
	{
		return false;
	}
	if (stCardsMap.size() == 1)
	{
		return true;
	}

	if (stCardsMap.size() == 2)
	{
		_uint16 wFirstKey = stCardsMap.begin()->first;
		_uint16 wSecondKey = (++stCardsMap.begin())->first;

		if (wFirstKey == 0x00C || wFirstKey == 0x002
			|| wFirstKey == 0x008 || wFirstKey == 0x004)
		{

			if (wFirstKey == 0x00C && (wSecondKey == 0x109
				|| wSecondKey == 0x209))
			{
				return true;
			}
			if (wFirstKey == 0x002 && (wSecondKey == 0x208
				|| wSecondKey == 0x218))
			{
				return true;
			}

			if (wFirstKey == 0x008 && (wSecondKey == 0x107
				|| wSecondKey == 0x207))
			{
				return true;
			}

			if (wFirstKey == 0x004 && (wSecondKey == 0x105
				|| wSecondKey == 0x205))
			{
				return true;
			}
		}
	}

	return false;
}


bool CGameLogic::IsValidCardWeaves(vector<_uint16>& wWinCarsWeaves, vector<_uint16>& wCurUserOutCards)
{
	//如果是同一张牌点数是否相同
	if (!wWinCarsWeaves.size() && !wCurUserOutCards.size())
	{
		return false;
	}

	std::map<_uint16, _uint32> stCardsMap;
	std::map<_uint16, _uint32> stWinMap;
	
	std::sort(wCurUserOutCards.begin(), wCurUserOutCards.end());
	std::sort(wWinCarsWeaves.begin(), wWinCarsWeaves.end());
	_uint8 cbWinType_1 = (wWinCarsWeaves[0] >> 8) & 0xF;
	_uint8 cbUserType_1 = (wCurUserOutCards[0] >> 8) & 0xF;
	_uint8 cbWinType_2 = (wWinCarsWeaves[0] >> 4) & 0xF;
	_uint8 cbUserType_2 = (wCurUserOutCards[0] >> 4) & 0xF;

	_uint8 cbWinIndex = wWinCarsWeaves[0] & 0xF;
	_uint8 cbUserIndex = wCurUserOutCards[0] & 0xF;


	if (wCurUserOutCards.size() >= 1 )
	{
		for (_uint8 i = 0; i < wCurUserOutCards.size(); ++i)
		{
			stCardsMap[wCurUserOutCards[i]]++;
		}
		
		if (stCardsMap.size() >= 2)
		{
			_uint16 wFirstCardKey = stCardsMap.begin()->first;
			_uint16 wSeconCardKey = (++stCardsMap.begin())->first;
			
			if (wFirstCardKey != 0x00C && wFirstCardKey != 0x002
				&& wFirstCardKey != 0x008 && wFirstCardKey != 0x004)
			{
				return false;
			}

			 if (wFirstCardKey == 0x00C  || wFirstCardKey == 0x002
					|| wFirstCardKey == 0x008 || wFirstCardKey == 0x004)
			 {

				 if (wFirstCardKey == 0x00C && wSeconCardKey != 0x109
						&& wSeconCardKey != 0x209)
				 {
					 return false;
				 }
				 if (wFirstCardKey == 0x002 && wSeconCardKey != 0x208
						&& wSeconCardKey != 0x218)
				 {
					 return false;
				 }

				 if (wFirstCardKey == 0x008 && wSeconCardKey != 0x107
					 && wSeconCardKey != 0x207)
				 {
					 return false;
				 }
				 if (wFirstCardKey == 0x004 && wSeconCardKey != 0x105
					 && wSeconCardKey == 0x205)
				 {
					 return false;
				 }
			}
			else
			{
				return false;
			}
		}
	}
	
	if (stCardsMap.size() == 1 && cbWinType_1 == cbUserType_1)
	{
		if ((wCurUserOutCards.size() != wWinCarsWeaves.size()))
		{
			return false;
		}

		if (cbWinType_1 == 0)
		{
			if (cbWinType_2 == 0)
			{
				if (wWinCarsWeaves[0] == 0x00C)   //天牌最大
				{
					return false;
				}
				if (wWinCarsWeaves[0] == 0x002
						&& wCurUserOutCards[0] != 0x00C)  //不能同时为地牌
				{
					return false;
				}

				if (wCurUserOutCards[0] == 0x002 && wWinCarsWeaves[0] == 0x002)
				{	
					return false;
				}
				if (wCurUserOutCards[0] != 0x002
						&& cbUserIndex <= cbWinIndex)  //其他的牌按照牌序的大小比较
				{
					return false;
				}
			}
			else if (cbWinType_2 == 1)
			{
				if (cbUserType_2 != 0)
				{
					return false;
				}
			}
			else if (cbWinType_2 == 2)
			{
				if (cbUserType_2 > 1)
				{
					return false;
				}
			}
		}
		else
		{
			if (cbWinType_2 == cbUserType_2)
			{
				if (cbWinIndex >= cbUserIndex)
				{
					return false;
				}				
			}
			else if ((wWinCarsWeaves[0] == 0x208 && wCurUserOutCards[0] == 218)
						|| (wWinCarsWeaves[0] == 0x218 && wCurUserOutCards[0] == 208))
			{
				return false;	
			}
		}	

		return true;
	}

	
	for (_uint8 i = 0; i < wWinCarsWeaves.size(); ++i)
	{
		stWinMap[wWinCarsWeaves[i]]++;
	}

	if (stWinMap.size() >= 2)
	{
		_uint8 u8TotalWins  = stWinMap.begin()->second + (++stWinMap.begin())->second;
		_uint8 u8TotalCards = stCardsMap.begin()->second + (++stCardsMap.begin())->second;
		
		log.info("isValidCardWeaves: u8TotalWins: %d, u8TotalCards: %d \n", u8TotalWins, u8TotalCards);
		if (u8TotalCards != u8TotalWins)
		{
			return false;
		}

		if (cbWinIndex == 0xC)
		{
			return false;
		}
		else if (cbWinIndex == 0x2 && cbUserIndex != 0xC)
		{
			return false;
		}
		else if (cbWinIndex == 0x8 && (cbUserIndex != 0xC && cbUserIndex != 0x2))
		{
			return false;
		}
		else if (cbWinIndex == 0x4 && (cbUserIndex != 0xC && cbUserIndex != 0x2 && cbUserIndex != 0x8))
		{
			return false;
		}
		
		return true;
	}


	return false;
}

