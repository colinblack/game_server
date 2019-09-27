/*
 * IManager.h
 *
 *  Created on: 2016年1月22日
 *      Author: aaron
 *      desc  : 系统公用接口
 */

#ifndef IMANAGER_H_
#define IMANAGER_H_

#include "Kernel.h"

class Player;
class IManager
{
public:
	IManager();
	virtual ~IManager();
	virtual bool doPacket(CNetPacket * packet) = 0;
public:
	void setPlayer(Player* player)
	{
		m_player = player;
	}
	Player *getPlayer()
	{
		return m_player;
	}
protected:
	Player *m_player;
};

#endif /* IMANAGER_H_ */
