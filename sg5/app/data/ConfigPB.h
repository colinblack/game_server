/*
 * ConfigPB.h
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#ifndef CONFIGPB_H_
#define CONFIGPB_H_

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


/*
 *  把json解析成pb的基类
 */
class ConfigPBBase
{
public:
	ConfigPBBase(){}
	virtual ~ConfigPBBase(){}
	static bool _j2p(Message* msg, Json::Value &json);
	static void Fail();
};

/*
 *  类模版参数显示定义pb message的类型，构造函数传入json文件名，构造函数中自动解析
 */
template<class T>
class ConfigPB : public ConfigPBBase
{
public:
	ConfigPB(string path, bool allserver=true)
	{
		string buf;
		Json::Value json;
		if(allserver)
			path = MainConfig::GetAllServerPath(CONFIG_XML_PATH + path);
		else
			path = Config::GetPath("conf/" + path);
		int ret = File::Read(path, buf);
		if(ret)
		{
			Fail();
			error_log("read json file %s error!", path.c_str());
			return;
		}

		Json::Reader reader;
		if(!reader.parse(buf, json))
		{
			Fail();
			error_log("parse json %s error! reason=%s", path.c_str(),  reader.getFormatedErrorMessages().c_str());
			return;
		}

		if(!_j2p(&m_config, json))
		{
			Fail();
			error_log("config %s error!", path.c_str());
		}
	}
	~ConfigPB(){}
	T m_config;
};


#endif /* CONFIGPB_H_ */
