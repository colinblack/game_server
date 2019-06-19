#include "Common.h"
#include "GameLogic.h"
#include <iostream>
#include <cstdio>

tagCardIndex                    m_cbCardIndex[GAME_PLAYER];
tagCardsWeave					m_CardsWeaveInfo[GAME_PLAYER][MAX_INDEX];//手牌组合
_uint8							m_cbCardsWeaveCount[GAME_PLAYER];


/*  0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,
	0x002, 0x004, 0x008, 0x00C, 0x014, 0x016, 0x01A, 0x026, 0x027, 0x02A, 0x02B, 0x105, 0x107, 0x109, 0x205, 0x207, 0x208, 0x209, 0x218, 0x303, 0x306,

*/


_uint8 A[CARD_TYPE_1][CARD_TYPE_2][CARD_INDEX] =
{
	{ { 0,0,1,0,1,0,0,0,1,0,0,0,0 },{ 0,0,0,0,2,0,1,0,0,0,1,0,0 },{ 0,0,0,0,0,0,4,0,0,0,2,1,0 } },
	{ { 0,0,0,0,0,1,0,1,0,2,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,1,0,0,1,1,0,0,0 },{ 0,0,0,0,0,0,0,0,1,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } }
};

_uint8 B[CARD_TYPE_1][CARD_TYPE_2][CARD_INDEX] =
{
	{ { 0,0,2,0,2,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,2,2,0,0,0,0,2 } },
	{ { 0,0,0,0,0,2,0,0,1,2,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,2,2,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } }
};
_uint8 C[CARD_TYPE_1][CARD_TYPE_2][CARD_INDEX] =
{
	{ { 0,0,2,0,2,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,2,2,0,0,0,0,2 } },
	{ { 0,0,0,0,0,2,0,0,1,2,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,2,2,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0,0,0,0 } }
};

_uint8 m_UserOutCardIndex = 0;
bool m_UserCanOutCard[3] = { 1,1,1 };
bool m_Is_is_begin_per_circle = true;
void sendNodtifyTest(int is, int user)
{
	_uint8 cbSecondUser = (user + 1) % 3;
	_uint8 cbTempUser = 0;
	for (_uint8 i = cbSecondUser; (m_UserOutCardIndex % 3) != 0; ++i)
	{
		if (!is)				//和下家比较，如果下家不能打，就直接过
		{
			++m_UserOutCardIndex;
			m_UserCanOutCard[i] = false;
			cbTempUser = i;
			printf("SendOutCardNotify: %d \n", cbTempUser);
		}
		else
		{
			break;
		}
	}
	if (m_UserOutCardIndex % 3 == 0)
	{
		for (_uint8 i = 0; i < 3; ++i)
		{
			m_UserCanOutCard[i] = true;
		}
		m_Is_is_begin_per_circle = true;
	}
	else
	{
		m_Is_is_begin_per_circle = false;
	}
	printf("SendOutCardNotify: %d \n", cbTempUser);


}

int main(int argc, char *argv[])
{
	//memcpy(m_cbCardIndex[0].cbCards, A, sizeof(A));
	//memcpy(m_cbCardIndex[1].cbCards, B, sizeof(B));
	//memcpy(m_cbCardIndex[2].cbCards, C, sizeof(C));
	//
	CGameLogic logic;
	
	_uint8    m_bLeftCardCount = MAX_CARDS;
	_uint16	  m_cbRepertoryCard[MAX_CARDS];			//库存扑克
	logic.RandCardData(m_cbRepertoryCard, MAX_CARDS);
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		m_bLeftCardCount -= (MAX_COUNT);
		logic.SwitchToCardIndex(&m_cbRepertoryCard[m_bLeftCardCount], MAX_COUNT, m_cbCardIndex[i]);
	}

	logic.SettleCommonWeaves(m_cbCardIndex[0], m_CardsWeaveInfo[0], m_cbCardsWeaveCount[0]);

	//logic.SettleCommonWeaves(m_cbCardIndex[0], m_CardsWeaveInfo[0], m_cbCardsWeaveCount[0]);

	//for (_uint8 i = 0; i < m_cbCardsWeaveCount[0]; ++i)
	//{
	//	for (_uint8 j =0; j < m_CardsWeaveInfo[0][i].cbCardCount; ++j)
	//	{
	//		printf("0x%-4x    ", m_CardsWeaveInfo[0][i].cbCardList[j]);
	//	}
	//	printf("\n");
	//}

	/*vector<_uint16> win;
	win.push_back(0x026);
	win.push_back(0x105);*/
//	win.push_back(0x002);

	vector<_uint16> car;


	car.push_back(0x002);
	car.push_back(0x002);
	car.push_back(0x002);

	logic.getNoBankerHuBestWeaves(0, NULL, m_CardsWeaveInfo[1], &m_cbCardsWeaveCount[1], car, &m_cbCardIndex[1], 0);
	//std::cout << logic.FisrstCardIsValid(win, 0) << std::endl;
	
	for (_uint8 i = 0; i < m_cbCardsWeaveCount[1]; ++i)
	{
		for (_uint8 j = 0; j <  m_CardsWeaveInfo[1][i].cbCardCount; ++j)
		{
			std::cout << m_CardsWeaveInfo[1][i].cbCardList[j];
		}
		std::cout << std::endl;
	}

	for (_uint8 i = 0; i < car.size(); ++i)
	{
		std::cout << car[i] << std::endl;
	}

	return 0;
}
