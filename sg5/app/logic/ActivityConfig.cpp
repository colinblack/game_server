/*
 * ActivityConfig.cpp
 *
 *  Created on: 2017-5-15
 *      Author: dawx62fac
 */

#include "ActivityConfig.h"

const char* all_activity_table[] = {
       "treasures_around",  	//金玉满堂
       "spirit_foster",  		//将灵培养
       "allserver_groupbuy",  //百服团购
       CONFIG_SCROLL_ACTIVITY,  //古卷专项活动
       CONFIG_KING_TREASURE, //天帝宝库活动
       CONFIG_SCROLL_FEEDBACK, //古卷回馈活动
       CONFIG_SEVENDAYS_AWAKEN, //七日觉醒活动
       CONFIG_TOKEN_UPGRADE, //令牌提升活动
       CONFIG_BUILD_SUIT,  //打造套装
       CONFIG_BLESS_POINT, //祝福积分
       CONFIG_DOUBLE_WELFARE, //双倍福利
       CONFIG_PEARL_ADVANCE,  //灵珠进阶
       CONFIG_UNIQUE_DIAL,  //绝学转盘
       CONFIG_CHARGE_HORSE, //的卢凝魂
       CONFIG_SPIRIT_VITALITY,  //精元礼包
       CONFIG_FORGE_SMELT,  //熔炉
       CONFIG_HERO_DIAL, //紫将转盘
       CONFIG_KINGDOM_WAR, //三国争霸
       CONFIG_ONEDIAMOND, //一钻瑞兽
       CONFIG_QIXI_FEEDBACK, //七夕回馈
       CONFIG_FORTUNE_PACKS, //好运礼包
       CONFIG_SEVENDAYS_PACKS, //7天好礼
       CONFIG_ICEPHOENIX,
       CONFIG_AUTUMN_FEEDBACK,
       CONFIG_PROTECT_FLAG,
       CONFIG_TWOHOLIDAY_ENJOY, //国庆中秋双节活动
       CONFIG_KEY_LUXURYGIFT, //密钥豪礼
       CONFIG_ENJOY_SMALLGIFT,  //畅享小礼
       CONFIG_LUCKY_GIFT,  //幸运好礼
       CONFIG_YEAREND_GIFT,  //年末好礼
       CONFIG_NEWYEAR_GIFT, //元旦庆典
       //CONFIG_BLACK_ENHANCE, //黑金强化
       CONFIG_STAR_STONE_CHG, //星石置换
       CONFIG_VICKY_ACC_X, //vicky的充值活动x
	   CONFIG_NEWYEAR_ACTIVE, //红人榜
       CONFIG_VICKY_ACC_X1, //vicky的充值活动x1
       CONFIG_VICKY_ACC_X2, //vicky的充值活动x2
       CONFIG_VICKY_ACC_X3, //vicky的充值活动x3
       CONFIG_VICKY_ACC_X4, //vicky的充值活动x4
       CONFIG_VICKY_ACC_X5, //vicky的充值活动x5
	   CONFIG_TASK_GIFT, //任务好礼
	   CONFIG_huangzhong, //机甲黄忠
	   CONFIG_ROTARYTABLE_GIFT, //转盘狂惠
	   CONFIG_VICKY_NEW_OPEN, //vicky的开服活动
	   CONFIG_VICKY_NO_NAME, //vicky没想好名字的活动
	   CONFIG_VICKY_BINGSHU, //兵书突破
	   CONFIG_VICKY_QIANFU, //千服同庆
	   CONFIG_BATMANTREASURE_GIFT,//小兵宝物
	   CONFIG_SUMMERCHAEGE_GIFT,//暑假精选
	   CONFIG_SUMMERREWARD_GIFT,//暑假回馈
   	   CONFIG_CHONGZHI_ZIXUAN, //新充值自选
	   CONFIG_BEAUTY, //美人献计
	   CONFIG_INVESTMENT, //充值投资
	   CONFIG_VICKY_NNA, //vicky懒得给我说名字的活动
	   CONFIG_BIRDBRIDGE, //七夕相会
//autolable2
CONFIG_hanjiajingxuan,
CONFIG_fuzhuhesui,
CONFIG_zhuniandaji,
CONFIG_vicky_qingrenjie,
CONFIG_yuandan2018,
CONFIG_yearend2018,
CONFIG_winter2018,
CONFIG_double11_2018,
	   CONFIG_mid_aug_hao,
	   CONFIG_mid_aug_reu,
	   CONFIG_water_taotie,
	   CONFIG_water_qilin,
	   CONFIG_water_pheonix,
	   CONFIG_vicky_nnom,
	   CONFIG_CHINADAY_WELCOME,
	   CONFIG_GUO_QING_KUANG_HUAN,
	   CONFIG_OPTIONAL_PAY,
	   CONFIG_FREE_EXCHG,//兑换自选
	   CONFIG_SHENGDAN_2018,
	   CONFIG_XIAONIAN_2018,
	   CONFIG_QINGRENJIE_MEIGUI,
	   CONFIG_NIANSHOU_BOSS,
       NULL
};

void ActInfoConfig::full_act_info(Json::Value& result) const
{
	result.clear();

	result[0u] = StartTS();
	result[1u] = EndTS();
	result[2u] = Version();
	result[3u] = Platform();
}
/////////////////////////////////////////////////////////////////////////////////
void full_all_act_info(Json::Value& result)
{
	for (int i = 0; all_activity_table[i] != NULL ;i++)
	{
		try
		{
			Json::Value info = Json::arrayValue;
			ActInfoConfig(all_activity_table[i]).full_act_info(info);
			result[all_activity_table[i]] = info;
		}
		catch (const std::exception& e) {
			//error_log("activity name: %s, error: %s", all_activity_table[i], e.what());
		}
	}
}


