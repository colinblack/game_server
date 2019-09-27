/*
 * BattleDefine.h
 *
 *  Created on: 2016年2月24日
 *      Author: Administrator
 */

#ifndef BATTLEDEFINE_H_
#define BATTLEDEFINE_H_
#include "AutoAttribute.h"
// BUFF状态
class BuffBattleState
{
public:
    BuffBattleState()
    {}
    ~BuffBattleState() {}

    map<byte,AutoAttribute> m_props;
    // 概率性吸血 buff
//    struct RandDamageTurnHp
//    {
//        int rand; // 吸血的概率
//        double scale; // 吸收伤害的比例转换为生命
//        RandDamageTurnHp()
//            : rand( 0 ), scale( 0 ) {}
//
//        // 是否吸血
//        bool IsDamageTurnHp();
//
//        // 吸血数量
//        int GetHp( int damage );
//    };
//    RandDamageTurnHp randDamageTurnHp;
};




#endif /* BATTLEDEFINE_H_ */
