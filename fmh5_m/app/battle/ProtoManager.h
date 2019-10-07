/*
 * ProtoManager.h
 *
 *  Created on: 2016-8-20
 *      Author: Ralf
 */

#ifndef PROTOMANAGER_H_
#define PROTOMANAGER_H_

#include "Kernel.h"
#include "DataInc.h"
#include "LogicManager.h"

/*
 * 回调管理器
 * 必须是static函数才可以注册回调
 * 这里实现具体的回调逻辑
 */
class ProtoManager
{
public:
	static int DisCardMessage(Message* message);
	static CurCMD m_CurCMD;
	static int ProcessLogin(Common::Login* msg);

	/**************通用模版**********/
	//new出回包，自动删除
	template<class T, class G, class H>
	static int Process(T* msg)
	{
		int ret = 0;
		G* resp = new G;
		try
		{
			ret = H::Instance()->Process(LogicManager::Instance()->Getuid(), msg, resp);
			if (ret != 0)
				delete resp;
			else
				LogicManager::Instance()->SetReplyProtocol(resp);

		}
		catch(const std::exception& e)
		{
			delete resp;
			LogicManager::Instance()->SetErrMsg(e.what());
			return R_ERROR;
		}

		return ret;
	}

	//不new回包，不删除
	template<class T, class G, class H>
	static int ProcessNoNew(T* msg)
	{
		int ret = 0;
		G* resp = NULL;
		try
		{
			ret = H::Instance()->Process(LogicManager::Instance()->Getuid(), msg, resp);
			if(ret == 0)
			{
				LogicManager::Instance()->SetReplyProtocol(resp);
				LogicManager::Instance()->SetNeedDelReply();
			}

		}
		catch(const std::exception& e)
		{
			LogicManager::Instance()->SetErrMsg(e.what());
			return R_ERROR;
		}

		return ret;
	}

	//无回包
	template<class T, class H>
	static int ProcessNoReply(T* msg)
	{
		int ret = 0;
		try
		{
			ret = H::Instance()->Process(LogicManager::Instance()->Getuid(), msg);
		}
		catch(const std::exception& e)
		{
			LogicManager::Instance()->SetErrMsg(e.what());
			return R_ERROR;
		}

		return ret;
	}

	//new出回包，自动删除，支付或者gm发来的无uid的包
	template<class T, class G, class H>
	static int ProcessNoUID(T* msg)
	{
		int ret = 0;
		G* resp = new G;
		try
		{
			ret = H::Instance()->Process(msg, resp);
			if (ret != 0)
				delete resp;
			else
				LogicManager::Instance()->SetReplyProtocol(resp);

		}
		catch(const std::exception& e)
		{
			delete resp;
			LogicManager::Instance()->SetErrMsg(e.what());
			return R_ERROR;
		}

		return ret;
	}

	//无回包，支付或者gm发来的无uid的包
	template<class T, class H>
	static int ProcessNoReplyNoUID(T* msg)
	{
		int ret = 0;
		try
		{
			ret = H::Instance()->Process(msg);
		}
		catch(const std::exception& e)
		{
			LogicManager::Instance()->SetErrMsg(e.what());
			return R_ERROR;
		}

		return ret;
	}

	/*禁用同步接口
	//指定serverid的battle之间的有回复跨服请求，对方的消息注册应该使用 ProcessNoUID
	static int BattleConnect(unsigned serverid, Message& msg, Message& resp)
	{
		int ret = 0;
		try
		{
			CFirePacket packet(PROTOCOL_EVENT_BATTLE_CONNECT, false);
			packet.m_msg = &msg;
			ret = BattleConnect::Send(serverid, &packet);
			if(ret)
			{
				error_log("send to server:%u error!", serverid);
				return ret;
			}

			CFirePacket reply;
			ret = BattleConnect::Receive(serverid, &reply);
			if(ret)
			{
				error_log("receive from server:%u error!", serverid);
				return ret;
			}

			if(reply.m_msg->GetTypeName() == "ErrorRet.ErrorRet")
			{
				ErrorRet::ErrorRet* t = dynamic_cast<ErrorRet::ErrorRet*>(reply.m_msg);
				ret = t->errorret();
				error_log("reply %s error, ret=%u, msg=%s", t->requestmsg().c_str(), ret, t->errormsg().c_str());
				return ret;
			}

			resp.MergeFrom(*reply.m_msg);
		}
		catch(const std::exception& e)
		{
			error_log("BattleConnect error %s", e.what());
			return R_ERROR;
		}

		return ret;
	}
	*/

	//指定serverid的battle之间的无回复跨服请求，对方的消息注册应该使用 ProcessNoReplyNoUID
	static int BattleConnectNoReply(unsigned serverid, Message* msg, bool d = true)
	{
		try
		{
			CFirePacket* packet = new CFirePacket(PROTOCOL_EVENT_BATTLE_CONNECT, d);
			packet->m_msg = msg;
			BattleConnect::AddSend(serverid, packet);
		}
		catch(const std::exception& e)
		{
			error_log("BattleConnect error %s", e.what());
			return R_ERROR;
		}

		return 0;
	}

	/*禁用同步接口
	//指定uid的battle之间的有回复跨服请求，对方的消息注册应该使用 ProcessNoUID
	static int BattleConnectByUID(unsigned uid, Message& msg, Message& resp)
	{
		return BattleConnect(Config::GetZoneByUID(uid), msg, resp);
	}
	//指定aid的battle之间的有回复跨服请求，对方的消息注册应该使用 ProcessNoUID
	static int BattleConnectByAID(unsigned aid, Message& msg, Message& resp)
	{
		return BattleConnect(Config::GetZoneByAID(aid), msg, resp);
	}
	*/
	//指定uid的battle之间的无回复跨服请求，对方的消息注册应该使用 ProcessNoReplyNoUID
	static int BattleConnectNoReplyByUID(unsigned uid, Message* msg, bool d = true)
	{
		return BattleConnectNoReply(Config::GetZoneByUID(uid), msg, d);
	}
	//指定aid的battle之间的无回复跨服请求，对方的消息注册应该使用 ProcessNoReplyNoUID
	static int BattleConnectNoReplyByAID(unsigned aid, Message* msg, bool d = true)
	{
		return BattleConnectNoReply(Config::GetZoneByAID(aid), msg, d);
	}
	//指定zoneId的battle之间的无回复跨服请求，对方的消息注册应该使用 ProcessNoReplyNoUID
	static int BattleConnectNoReplyByZoneID(unsigned zoneId, Message* msg, bool d = true)
	{
		return BattleConnectNoReply(zoneId, msg, d);
	}
};


#endif /* PROTOMANAGER_H_ */
