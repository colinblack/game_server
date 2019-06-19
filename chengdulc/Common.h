#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>
#include <vector>
#include <set>
using  std::vector;


//数据类型定义
typedef          char        _tint8;     //有符号 1 字节
typedef unsigned char        _uint8;     //无符号 1 字节
typedef short                _tint16;    //有符号 2 字节
typedef unsigned short       _uint16;    //无符号 2 字节
typedef int                  _tint32;    //有符号 4 字节
typedef unsigned int         _uint32;    //无符号 4 字节
typedef			 long long   _tint64;    //有符号 8 字节
typedef unsigned long long   _uint64;    //无符号 8 字节

//数值定义
#define GAME_PLAYER					3									//游戏人数
#define MAX_WEAVE					21									//最大组合
#define MAX_INDEX					21									//最大索引
#define MAX_INDEX_EX                28                                
#define MAX_COUNT					28									//最大数目
#define MAX_COUNT_4					15									//4人玩最大数目
#define	MASK_TYPE					0xF00								//类型掩码
#define MASK_TYPE_1                 0x0F0                               //次类型掩码
#define	MASK_VALUE					0x00F								//数值掩码
#define MAX_CARDS					84									//最大牌数
#define INVALID_CHAIR  				-1	 								//无效座位号
#define INVALID_CARD				0xFF								//无效牌
#define HU_BASE_CARD_NUM            16									//16张牌起胡

//动作定义
#define ACK_NULL					0x00								//空
#define ACK_CHIHU					0x01								//胡
#define ACK_HUANG                   0x02								//黄


//显示定义
#define ACK_KAN						0x50								//坎
#define ACK_JIANG					0x60								//将

#define ACK_ORGWV					0x80								//是不是原手的组合
#define ACK_ORGWV_MASK				0x7F								//
#define ACK_ORG_WV(ACK)				((ACK)|(ACK_ORGWV))
#define ACK_IS_ORG_WV(ACK)			((ACK)&(ACK_ORGWV))
#define ACK_KIND(ACK)				((ACK)&(ACK_ORGWV_MASK))

//吃牌类型
#define CK_NULL						0x00								//无效类型
#define CK_XXD						0x01								//小小大搭
#define CK_XDD						0x02								//小大大搭
#define CK_EQS						0x04								//二七十吃
#define CK_YWS						0x08								//一五十吃
//#define CK_YES						0x06								//一二三吃
#define CK_LEFT						0x10								//靠左对齐
#define CK_CENTER					0x20								//居中对齐
#define CK_RIGHT					0x40								//靠右对齐

#define CardNum(c) ((c) & MASK_VALUE)
#define CardType(c) (((c) & MASK_COLOR)>>4)
#define CardValue(t,n) ( (t<<4) | n )

#define CARD_TYPE_1    4
#define CARD_TYPE_2    3
#define CARD_INDEX     13


//交换两个整形数，不能传表达式，同一个变量 ns=not same
#define ns_swap(a,b) ((a)^=(b),(b)^=(a),(a)^=(b))

//三个整型数排序
#define sort3n(a)	do{	\
	((a)[0] > (a)[1]) && (ns_swap((a)[0], (a)[1]));\
	((a)[0] > (a)[2]) && (ns_swap((a)[0], (a)[2]));\
	((a)[1] > (a)[2]) && (ns_swap((a)[1], (a)[2]));}while(0)

//////////////////////////////////////////////////////////////////////////



//胡番类型
enum HuFanType
{
	MT_NULL = 0,								//空
	MT_HONG_HU = 1,								//红胡,清一色
	MT_HEI_HU = 2,								//黑胡，清一色
	MT_TIAN_HU = 3,								//天胡
	MT_DI_HU = 4,								//地胡
	MT_SINGLE_CYCLE = 5,						//圈胡
	MT_DOUBLE_CYCLE = 6,						//双圈
	MT_DA_KA_HU = 7,							//大卡胡
	MT_DIAN_HU = 8,								//点胡
	MT_JU_SHOU = 9,								//举手
	MT_ZI_MO = 10,								//自摸
	MT_XIAO_HONG_HU = 11,						//小红胡
	MT_KUN_HU = 12,								//坤胡
	MT_PIAOPIAO_HU = 13,						//瞟瞟
};

//组合子项
struct tagWeaveItem
{
	_uint8							cbWeaveKind;						//组合类型
	_uint8							cbCardCount;						//扑克数目
	_uint8							cbCenterCard;						//中心扑克
	_uint8							cbOutCard;							//打出的牌
	_uint16							cbCardList[12];						    //扑克列表
	tagWeaveItem()
	{
		cbWeaveKind = 0;
		cbCardCount = 0;
		cbCenterCard = 0;
		cbOutCard = 0;
		memset(cbCardList, 0 , sizeof(cbCardList));
	}
};

struct tagCardIndex 
{
	_uint8 cbCards[CARD_TYPE_1][CARD_TYPE_2][CARD_INDEX];

	tagCardIndex()
	{
		memset(cbCards,0, sizeof(cbCards));
	}
};



//吃牌信息
struct tagChiCardInfo
{
	_uint8							cbChiKind;							//吃牌类型
	_uint8							cbCenterCard;						//中心扑克
	_uint8							cbResultCount;						//结果数目
	_uint8							cbCardData[3][3];					//吃牌组合
	tagChiCardInfo()
	{
		cbChiKind = 0;
		cbCenterCard = 0;
		cbResultCount = 0;
		memset(cbCardData, 0, sizeof(cbCardData));
	}
};

//吃牌第三层
struct tagThirdChiInfo
{
	_uint8							cbChiKind;							//吃牌类型
	_uint8							cbCenterCard;						//中心牌
	_uint8							cbCardData[3];						//吃牌
	tagThirdChiInfo()
	{
		cbChiKind = 0;
		cbCenterCard = 0;
		memset(cbCardData, 0, sizeof(cbCardData));
	}
};

//吃牌第二层
struct tagSecondChiInfo
{
	_uint8							cbChiKind;							//吃牌类型
	_uint8							cbCenterCard;						//中心牌
	_uint8							cbCardData[3];						//吃牌
	_uint8							cbThirdCount;						//剩余组合数
	tagThirdChiInfo					ThirdData[6];
	tagSecondChiInfo()
	{
		cbChiKind = 0;
		cbCenterCard = 0;
		memset(cbCardData, 0, sizeof(cbCardData));
		cbThirdCount = 0;
		memset(ThirdData, 0, sizeof(ThirdData));
	}
};

//新吃牌信息
struct tagNewChiCardInfo
{
	_uint8							cbChiKind;							//吃牌类型
	_uint8							cbCenterCard;						//中心牌
	_uint8							cbCardData[3];						//吃牌
	_uint8							cbSecondCount;						//剩余组合数
	tagSecondChiInfo				SecondData[6];
	tagNewChiCardInfo()
	{
		cbChiKind = 0;
		cbCenterCard = 0;
		memset(cbCardData, 0, sizeof(cbCardData));
		cbSecondCount = 0;
		memset(SecondData, 0, sizeof(SecondData));
	}
};

//分析子项
struct tagAnalyseItem
{
	_uint8							cbCardEye;							//牌眼扑克
	_uint8							cbHuXiCount;						//胡息数目
	_uint8							cbWeaveCount;						//组合数目
	tagWeaveItem					WeaveItemArray[MAX_WEAVE];			//组合扑克
	tagAnalyseItem()
	{
		cbCardEye = 0;
		cbHuXiCount = 0;
		cbWeaveCount = 0;
		memset(WeaveItemArray, 0, sizeof(WeaveItemArray));
	}
};

//胡牌信息
struct tagHuCardInfo
{
	_uint8							cbCardEye;							//牌眼扑克
	_uint8							cbHuXiCount;						//胡息数目
	_uint8							cbFinalHuXiCount;					//最终胡息数目
	_uint8							cbWeaveCount;						//组合数目
	tagWeaveItem					WeaveItemArray[MAX_WEAVE];			//组合扑克
	tagHuCardInfo()
	{
		cbCardEye = 0;
		cbHuXiCount = 0;
		cbFinalHuXiCount = 0;
		cbWeaveCount = 0;
		memset(WeaveItemArray, 0, sizeof(WeaveItemArray));
	}
};

//胡番信息
struct tagHuFanInfo
{
	_uint32							wHuFanType;							//胡番类型
	_uint32							wHuFanNum;							//胡番数	
	_uint32							wHuFanXi;							//胡番息	
	tagHuFanInfo()
	{
		wHuFanType = 0;
		wHuFanNum = 0;
		wHuFanXi = 0;
	}
};

//手牌组合
/*
struct tagCardsWeave
{
	_uint8							cbCardCount;						//组合牌数
	_uint8							cbCardList[4];						//组合牌
	tagCardsWeave()
	{
		cbCardCount = 0;
		memset(cbCardList, 0, sizeof(cbCardList));
	}
};
*/


typedef  tagWeaveItem tagCardsWeave;


struct tagWeaveScore
{
	_uint8 cbLittleCount;
	_uint8 cbBigCount;
	_tint32 nScore;
	tagWeaveScore()
	{
		cbLittleCount = 0;
		cbBigCount = 0;
		nScore = 0;
	}
};

enum PlayType
{
	PLAY_TYPE					= 1000,			//玩法
	BASE_HU_XI					= 1003,			//起胡胡息
	NEI_NIAO_COUNT				= 1049,			//内围打鸟个数
	PIAO_SCORE					= 1053,			//飘的分数
	XIAO_PAI_OPTION				= 1104,			//明消暗消选项
	IS_PIAO						= 1108,			//是否能飘	
	GAME_PLAYERS				= 1109,			//游戏人数
	SPICAL_OPTIONS				= 1111,			//特殊选项
	
	HY_PT_PLAY_TYPE			= 1128,			//玩法 多选
	HY_PT_FANXING			= 1129,			//翻醒
	HY_PT_WEIPAI			= 1130,			//明暗偎
	HY_PT_FENGDING			= 1131,			//封顶

};

enum PlayerMethodID
{
	TIANHU = 0,
	STICK  = 1,
	YEZI   = 2,
};


//玩法ID
enum PlayerID
{
	//底分
	BASE_SCORE_1 = 1001001,  //1分
	BASE_SCORE_2 = 1001002,  //2分
	BASE_SCORE_3 = 1001003,  //3分
	BASE_SCORE_5 = 1001004,  //5分
	BASE_SCORE_10 = 1001005, //10分

	//玩法
	BANKER_TIANHU = 1002001,  //庄家天胡
	STICK_FAN = 1002002,		 //棍子番
	YEZI_METHOD = 1002003,       //页子算法

	//胡牌
	THREE_CARD_HE = 1003001, //三张起和
	FIVE_CARD_HE = 1003002,  //五张起和
	SEVEN_CARD_HE = 1003003, //七张起和
};


struct stCardInfo {
	_uint16 cbCard;
	_uint8 cbRow;
	_uint8 cbCol;

	stCardInfo():cbCard(0), cbRow(0), cbCol(0) {}

};

#endif
