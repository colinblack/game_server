/*
 * DataBase.cpp
 *
 *  Created on: 2015-11-20
 *      Author: Ralf
 */

#include "DataBase.h"
#include <iostream>
#include <fstream>


string ProtoElement::PrintMember()
{
	string m_cpp;

	if(isRepeat)
	{
		if(type == e_ProtoType_msg)
			m_cpp = "map<unsigned int, "+tname+"> "+name+"; ";
		else
			m_cpp = "vector<"+tname+"> "+name+"; ";
	}
	else
		m_cpp = tname+" "+name+"; ";

	return m_cpp;
}
string ProtoElement::PrintConstruct()
{
	string m_cpp;

	if(!isRepeat)
	{
		switch(type)
		{
		case e_ProtoType_int:
		case e_ProtoType_uint:
		case e_ProtoType_long:
		case e_ProtoType_ulong:
			m_cpp = name+" = 0; ";
			break;
		case e_ProtoType_float:
		case e_ProtoType_double:
			m_cpp = name+" = 0.0f; ";
			break;
		case e_ProtoType_bool:
			m_cpp = name+" = false; ";
			break;
		default:
			break;
		}
	}

	return m_cpp;
}
string ProtoElement::PrintSerialize()
{
	string m_cpp;

	switch(type)
	{
	case e_ProtoType_int:
	case e_ProtoType_uint:
	case e_ProtoType_long:
	case e_ProtoType_ulong:
	case e_ProtoType_float:
	case e_ProtoType_double:
	case e_ProtoType_bool:
	case e_ProtoType_string:
	{
		if(isRepeat)
			m_cpp = "for(vector<"+tname+">::iterator it="+name+".begin();it!="+name+".end();++it) p->add_"+name+"(*it); ";
		else
			m_cpp = "p->set_"+name+"("+name+"); ";
	}
	break;
	case e_ProtoType_msg:
	{
		if(isRepeat)
			m_cpp = "for(map<unsigned int, "+tname+">::iterator it="+name+".begin();it!="+name+".end();++it) it->second.Serialize(p->add_"+name+"()); ";
		else
			m_cpp = name+".Serialize(p->mutable_"+name+"()); ";
	}
	break;
	default:
		break;
	}

	return m_cpp;
}
string ProtoElement::PrintParse()
{
	string m_cpp;

	switch(type)
	{
	case e_ProtoType_int:
	case e_ProtoType_uint:
	case e_ProtoType_long:
	case e_ProtoType_ulong:
	case e_ProtoType_float:
	case e_ProtoType_double:
	case e_ProtoType_bool:
	case e_ProtoType_string:
	{
		if(isRepeat)
			m_cpp = "for(int i=0;i<p."+name+"_size();++i) "+name+".push_back(p."+name+"(i)); ";
		else
			m_cpp = name+" = p."+name+"(); ";
	}
	break;
	case e_ProtoType_msg:
	{
		if(isRepeat)
			m_cpp = "for(int i=0;i<p."+name+"_size();++i) "+name+"[p."+name+"(i)."+(*StructNames)[tname]+"()].Parse(p."+name+"(i)); ";
		else
			m_cpp = name+".Parse(p."+name+"()); ";
	}
	break;
	default:
		break;
	}

	return m_cpp;
}

Message* ProtoBase::CreateMessage(const string& typeName)
{
	Message* message = NULL;
	const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
	if (descriptor)
	{
		const Message* prototype = MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype)
			message = prototype->New();
	}
	return message;
}
ProtoBase::ProtoBase(const string& typeName)
{
	vector<string> rlt;
	String::Split(typeName, '.', rlt);

	if(rlt.size() != 2)
	{
		m_msg = NULL;
		return;
	}

	SpaceName = rlt[0];
	MsgName = rlt[1];
	m_msg = CreateMessage(typeName);
}
ProtoBase::~ProtoBase()
{
	if(m_msg)
	{
		m_msg->Clear();
		delete m_msg;
	}
}
int ProtoBase::Parse(const string& path)
{
	if(!m_msg || path.empty())
		return R_ERR_PARAM;

	fstream input(path.c_str(), ios::in | ios::binary);
	if(!input)
		return R_ERR_PARAM;

	if(!m_msg->ParseFromIstream(&input))
		return R_ERR_DATA;

	return 0;
}
int ProtoBase::Serialize(const string& path)
{
	if(path.empty() || !m_msg)
		return R_ERR_PARAM;

	fstream output(path.c_str(), ios::out | ios::trunc | ios::binary);
	if(!m_msg->SerializeToOstream(&output))
		return R_ERR_DATA;

	return 0;
}
string ProtoBase::DebugString()
{
	if(m_msg)
		return m_msg->DebugString();
	else
		return string("msg null!");
}

const char* Proto2CPP::TYPE_NAME[e_ProtoType_max] = {
		"int",
		"unsigned int",
		"long",
		"unsigned long",
		"float",
		"double",
		"bool",
		"string",
		" ",
};
string Proto2CPP::_proto(const Descriptor *des)
{
	string name, id;
	name = "Data" + des->name();
	if(StructNames.count(name))
		return name;

	vector<ProtoElement> mbs;
	for (int i = 0; i != des->field_count(); i++)
	{
		const FieldDescriptor *field = des->field(i);

		ProtoElement ele(field->is_repeated(), field->name(), &StructNames);

		if(i == 0)
			id = ele.name;

		switch (field->cpp_type())
		{
		case FieldDescriptor::CPPTYPE_DOUBLE:
			ele.type = e_ProtoType_double;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_FLOAT:
			ele.type = e_ProtoType_float;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_INT64:
			ele.type = e_ProtoType_long;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_UINT64:
			ele.type = e_ProtoType_ulong;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_INT32:
			ele.type = e_ProtoType_int;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_UINT32:
			ele.type = e_ProtoType_uint;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_BOOL:
			ele.type = e_ProtoType_bool;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_STRING:
			ele.type = e_ProtoType_string;
			ele.tname = TYPE_NAME[ele.type];
			break;
		case FieldDescriptor::CPPTYPE_MESSAGE:
			ele.type = e_ProtoType_msg;
			ele.tname = _proto(field->message_type());
			break;
		default:
			break;
		}
		mbs.push_back(ele);
	}

	m_cpp += "class "+name+" { public: ";
	for(vector<ProtoElement>::iterator it=mbs.begin();it!=mbs.end();++it)
		m_cpp += (*it).PrintMember();
	m_cpp += name+"(){";
	for(vector<ProtoElement>::iterator it=mbs.begin();it!=mbs.end();++it)
		m_cpp += (*it).PrintConstruct();
	m_cpp += "} ~";
	m_cpp += name+"(){} void Serialize("+SpaceName+"::"+des->name()+" *p){";
	for(vector<ProtoElement>::iterator it=mbs.begin();it!=mbs.end();++it)
		m_cpp += (*it).PrintSerialize();
	m_cpp += "} void Parse(const "+SpaceName+"::"+des->name()+" &p){";
	for(vector<ProtoElement>::iterator it=mbs.begin();it!=mbs.end();++it)
		m_cpp += (*it).PrintParse();
	m_cpp += "} };";

	StructNames[name] = id;
	return name;
}
Proto2CPP::Proto2CPP(const string& typeName)
	:ProtoBase(typeName)
{
	if(m_msg)
		_proto(m_msg->GetDescriptor());
	else
		m_cpp = "msg null!";
}

Proto2Json::Proto2Json(const string& typeName)
	:ProtoBase(typeName)
{
}
int Proto2Json::P2J()
{
	if(!m_msg)
		return R_ERR_PARAM;

	_p2j(m_msg, m_json);

	return 0;
}
void Proto2Json::_p2j(const Message* msg, Json::Value &json)
{
	const Descriptor* des = msg->GetDescriptor();
	const Reflection* ref = msg->GetReflection();
	for (int i = 0; i < des->field_count(); ++i)
	{
		const FieldDescriptor* field = des->field(i);
		const string& key = field->name();
		if(field->is_repeated())
		{
			json[key].resize(0);
			for(int j = 0; j < ref->FieldSize(*msg, field); ++j)
			{
				Json::Value temp;
				switch (field->cpp_type())
				{
				case FieldDescriptor::CPPTYPE_DOUBLE:
					temp = ref->GetRepeatedDouble(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_FLOAT:
					temp = ref->GetRepeatedFloat(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_INT64:
					temp = double(ref->GetRepeatedInt64(*msg, field, j));
					break;
				case FieldDescriptor::CPPTYPE_UINT64:
					temp = double(ref->GetRepeatedUInt64(*msg, field, j));
					break;
				case FieldDescriptor::CPPTYPE_INT32:
					temp = ref->GetRepeatedInt32(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_UINT32:
					temp = ref->GetRepeatedUInt32(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_BOOL:
					temp = ref->GetRepeatedBool(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_STRING:
					temp = ref->GetRepeatedString(*msg, field, j);
					break;
				case FieldDescriptor::CPPTYPE_MESSAGE:
					_p2j(&ref->GetRepeatedMessage(*msg, field, j), temp);
					break;
				default:
					break;
				}
				json[key].append(temp);
			}
		}
		else
		{
			switch (field->cpp_type())
			{
			case FieldDescriptor::CPPTYPE_DOUBLE:
				json[key] = ref->GetDouble(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_FLOAT:
				json[key] = ref->GetFloat(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_INT64:
				json[key] = double(ref->GetInt64(*msg, field));
				break;
			case FieldDescriptor::CPPTYPE_UINT64:
				json[key] = double(ref->GetUInt64(*msg, field));
				break;
			case FieldDescriptor::CPPTYPE_INT32:
				json[key] = ref->GetInt32(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_UINT32:
				json[key] = ref->GetUInt32(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_BOOL:
				json[key] = ref->GetBool(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_STRING:
				json[key] = ref->GetString(*msg, field);
				break;
			case FieldDescriptor::CPPTYPE_MESSAGE:
				_p2j(&ref->GetMessage(*msg, field), json[key]);
				break;
			default:
				break;
			}
		}
	}
}
string Proto2Json::SerializeJson()
{
	Json::FastWriter writer;
	return writer.write(m_json);
}

Json2Proto::Json2Proto(const string& typeName)
	:ProtoBase(typeName)
{
}
int Json2Proto::ParseJson(const string& jpath)
{
	string buf;
	int ret = File::Read(jpath, buf);
	if(ret)
		return ret;
	Json::Reader reader;
	if(!reader.parse(buf, m_json))
		return R_ERR_DATA;
	return 0;
}
int Json2Proto::J2P()
{
	if(!m_msg)
		return R_ERR_PARAM;

	_j2p(m_msg, m_json);

	return 0;
}
int Json2Proto::_j2p(Message* msg, Json::Value &json)
{
	const Descriptor* des = msg->GetDescriptor();
	const Reflection* ref = msg->GetReflection();
	for (int i = 0; i < des->field_count(); ++i)
	{
		const FieldDescriptor* field = des->field(i);
		const string& key = field->name();
		if(!json.isMember(key))
			return R_ERR_DATA;
		if(field->is_repeated())
		{
			if(!json[key].isArray())
				return R_ERR_DATA;
			for(unsigned j = 0; j < json[key].size(); ++j)
			{
				switch (field->cpp_type())
				{
				case FieldDescriptor::CPPTYPE_DOUBLE:
					ref->AddDouble(msg, field, json[key][j].asDouble());
					break;
				case FieldDescriptor::CPPTYPE_FLOAT:
					ref->AddFloat(msg, field, (float)json[key][j].asDouble());
					break;
				case FieldDescriptor::CPPTYPE_INT64:
					ref->AddInt64(msg, field, (int64_t)json[key][j].asDouble());
					break;
				case FieldDescriptor::CPPTYPE_UINT64:
					ref->AddUInt64(msg, field, (uint64_t)json[key][j].asDouble());
					break;
				case FieldDescriptor::CPPTYPE_INT32:
					ref->AddInt32(msg, field, json[key][j].asInt());
					break;
				case FieldDescriptor::CPPTYPE_UINT32:
					ref->AddUInt32(msg, field, json[key][j].asUInt());
					break;
				case FieldDescriptor::CPPTYPE_BOOL:
					ref->AddBool(msg, field, json[key][j].asBool());
					break;
				case FieldDescriptor::CPPTYPE_STRING:
					ref->AddString(msg, field, json[key][j].asString());
					break;
				case FieldDescriptor::CPPTYPE_MESSAGE:
					_j2p(ref->AddMessage(msg, field), json[key][j]);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			switch (field->cpp_type())
			{
			case FieldDescriptor::CPPTYPE_DOUBLE:
				ref->SetDouble(msg, field, json[key].asDouble());
				break;
			case FieldDescriptor::CPPTYPE_FLOAT:
				ref->SetFloat(msg, field, (float)json[key].asDouble());
				break;
			case FieldDescriptor::CPPTYPE_INT64:
				ref->SetInt64(msg, field, (int64_t)json[key].asDouble());
				break;
			case FieldDescriptor::CPPTYPE_UINT64:
				ref->SetUInt64(msg, field, (uint64_t)json[key].asDouble());
				break;
			case FieldDescriptor::CPPTYPE_INT32:
				ref->SetInt32(msg, field, json[key].asInt());
				break;
			case FieldDescriptor::CPPTYPE_UINT32:
				ref->SetUInt32(msg, field, json[key].asUInt());
				break;
			case FieldDescriptor::CPPTYPE_BOOL:
				ref->SetBool(msg, field, json[key].asBool());
				break;
			case FieldDescriptor::CPPTYPE_STRING:
				ref->SetString(msg, field, json[key].asString());
				break;
			case FieldDescriptor::CPPTYPE_MESSAGE:
				_j2p(ref->MutableMessage(msg, field), json[key]);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

/**********************************************************************/
DataBase::DataBase(string path)
	: m_path(path)
	, m_msg(NULL)
{
}

DataBase::~DataBase()
{
	if(m_msg)
		delete m_msg;
}

int DataBase::Init()
{
	return 0;
}

int DataBase::Save()
{
	return 0;
}

int DataBase::Sig(int sig)
{
	return 0;
}

int DataBase::Parse()
{
	if(m_path.empty() || !m_msg)
    {
		error_log("not init");
		return R_ERR_PARAM;
    }
	else
	{
		fstream input(m_path.c_str(), ios::in | ios::binary);
		if(!input)
		{
			error_log("create new %s",m_path.c_str());
			return R_ERR_NO_DATA;
		}
		else if(!m_msg->ParseFromIstream(&input))
		{
			error_log("parse %s fail",m_path.c_str());
			return R_ERR_DB;
		}
	}
	return 0;
}

int DataBase::Serialize()
{
	if(m_path.empty() || !m_msg)
    {
		error_log("not init");
		return R_ERR_PARAM;
    }
	else
	{
		fstream output(m_path.c_str(), ios::out | ios::trunc | ios::binary);
		if(!m_msg->SerializeToOstream(&output))
		{
			error_log("serialize %s fail",m_path.c_str());
			return R_ERR_DB;
		}
	}
	return 0;
}

