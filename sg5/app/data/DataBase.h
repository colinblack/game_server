/*
 * DataBase.h
 *
 *  Created on: 2015-11-20
 *      Author: Ralf
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "Kernel.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/descriptor.h>

using google::protobuf::Message;
using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::MessageFactory;
using google::protobuf::Reflection;

#include "test.pb.h"
#include "CrowdFunding.pb.h"
#include "NewWorldAllianceRoom.pb.h"
#include "NewWorldAllianceMap.pb.h"
#include "AllianceTorch.pb.h"
#include "AllServerLords.pb.h"
#include "BraveNewWorld.pb.h"
#include "AllianceConsume.pb.h"
#include "MVP.pb.h"
#include "Chick.pb.h"
#include "QingRenJie.pb.h"

enum ProtoType
{
	e_ProtoType_int 	= 0,
	e_ProtoType_uint 	= 1,
	e_ProtoType_long 	= 2,
	e_ProtoType_ulong 	= 3,
	e_ProtoType_float 	= 4,
	e_ProtoType_double 	= 5,
	e_ProtoType_bool 	= 6,
	e_ProtoType_string 	= 7,
	e_ProtoType_msg 	= 8,

	e_ProtoType_max
};
class ProtoElement
{
public:
	ProtoType type;
	bool isRepeat;
	string name, tname;
	map<string, string> *StructNames;

	ProtoElement(bool i, const string &n, map<string, string> *s)
		:isRepeat(i)
		,name(n)
		,StructNames(s)
	{
		type = e_ProtoType_max;
	}
	string PrintMember();
	string PrintConstruct();
	string PrintSerialize();
	string PrintParse();
};

class ProtoBase
{
public:
	string SpaceName, MsgName;
	Message* m_msg;

	static Message* CreateMessage(const string& typeName);
	ProtoBase(const string& typeName);
	ProtoBase() {m_msg = NULL;}
	~ProtoBase();
	int Parse(const string& path);
	int Serialize(const string& path);
	string DebugString();
};

class Proto2CPP : public ProtoBase
{
public:
	map<string, string> StructNames;
	static const char* TYPE_NAME[e_ProtoType_max];
	string m_cpp;

	string _proto(const Descriptor *des);
	Proto2CPP(const string& typeName);
	Proto2CPP(){};
};

class Proto2Json : public ProtoBase
{
public:
	Json::Value m_json;
	Proto2Json(const string& typeName);
	Proto2Json() {}
	int P2J();
	void _p2j(const Message* msg, Json::Value &json);
	string SerializeJson();
};
class Json2Proto : public ProtoBase
{
public:
	Json::Value m_json;
	Json2Proto(const string& typeName);
	Json2Proto() {}
	int ParseJson(const string& jpath);
	int J2P();
	int _j2p(Message* msg, Json::Value &json);
};
/**********************************************************************/
class DataBase
{
public:
	DataBase(string path);
	virtual ~DataBase();
	virtual int Init();
	virtual int Save();
	virtual int Sig(int sig);
protected:
	int Parse();
	int Serialize();
	string m_path;
	google::protobuf::Message* m_msg;
};
template<class T, class D>
class DataBaseT : public DataBase
{
public:
	DataBaseT(string path)
		:DataBase(path)
	{
		m_msg = new T;
	}
	virtual ~DataBaseT(){}
	virtual int OnInit(int ret)
	{
		return ret;
	}
	virtual int Init()
	{
		int ret = Parse();
		if(ret && ret != R_ERR_NO_DATA)
			return ret;

		if(ret != R_ERR_NO_DATA)
			m_data.Parse(*(T *)m_msg);

		m_msg->Clear();

		return OnInit(ret);
	}
	virtual int Save()
	{
		m_data.Serialize((T *)m_msg);

		int ret = Serialize();

		m_msg->Clear();

		return ret;
	}
	virtual int Sig(int sig)
	{
		return 0;
	}
protected:
	D m_data;
};

#endif /* DATABASE_H_ */
