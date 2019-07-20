/*
 * Convert.cpp
 *
 *  Created on: 2011-6-23
 *      Author: dada
 */

#include "Convert.h"

bool StringIsInt(const string &s)
{
	const char *pc = s.c_str();
	bool hasNumber = false;
	bool hasSign = false;
	while(*pc != '\0')
	{
		if(*pc < '0' || *pc > '9')
		{
			if(hasNumber || hasSign)
			{
				return false;
			}
			else
			{
				if(*pc == '+' || *pc == '-')
				{
					hasSign = true;
				}
				else if(*pc != ' ' && *pc != '\t')
				{
					return false;
				}
			}
		}
		else
		{
			hasNumber = true;
		}
		pc++;
	}
	return hasNumber;
}

bool StringIsUInt(const string &s)
{
	const char *pc = s.c_str();
	bool hasNumber = false;
	while(*pc != '\0')
	{
		if(*pc < '0' || *pc > '9')
		{
			if(hasNumber || (*pc != ' ' && *pc != '\t' && *pc != '.'))
			{
				return false;
			}
		}
		else
		{
			hasNumber = true;
		}
		pc++;
	}
	return hasNumber;
}

bool Convert::StringToInt(int &n, const string &s)
{
	if(!StringIsInt(s))
	{
		return false;
	}
	errno = 0;
	n = strtol(s.c_str(), NULL, 10);
	return errno == 0;
}

int Convert::StringToInt(const string &s, int defaultValue)
{
	if(!StringIsInt(s))
	{
		return defaultValue;
	}
	errno = 0;
	int n = strtol(s.c_str(), NULL, 10);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

bool Convert::StringToUInt(unsigned int &n, const string &s)
{
	if(!StringIsUInt(s))
	{
		return false;
	}
	errno = 0;
	n = strtoul(s.c_str(), NULL, 10);
	return errno == 0;
}

unsigned int Convert::StringToUInt(const string &s, unsigned int defaultValue)
{
	if(!StringIsUInt(s))
	{
		return defaultValue;
	}
	errno = 0;
	unsigned int n = strtoul(s.c_str(), NULL, 10);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

bool Convert::StringToInt64(int64_t &n, const string &s)
{
	if(!StringIsInt(s))
	{
		return false;
	}
	errno = 0;
	n = strtoll(s.c_str(), NULL, 10);
	return errno == 0;
}

int64_t Convert::StringToInt64(const string &s, int64_t defaultValue)
{
	if(!StringIsInt(s))
	{
		return defaultValue;
	}
	errno = 0;
	int64_t n = strtoll(s.c_str(), NULL, 10);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

bool Convert::StringToUInt64(uint64_t &n, const string &s)
{
	if(!StringIsUInt(s))
	{
		return false;
	}
	errno = 0;
	n = strtoull(s.c_str(), NULL, 10);
	return errno == 0;
}

uint64_t Convert::StringToUInt64(const string &s, uint64_t defaultValue)
{
	if(!StringIsUInt(s))
	{
		return defaultValue;
	}
	errno = 0;
	uint64_t n = strtoull(s.c_str(), NULL, 10);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

float Convert::StringToFloat(const string &s, float defaultValue) {
	if (!StringIsUInt(s)){
		return defaultValue;
	}
	errno = 0;
	float n = strtof(s.c_str(), NULL);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

double Convert::StringToDouble(const string &s, double defaultValue) {
	if (!StringIsUInt(s)){
		return defaultValue;
	}
	errno = 0;
	double n = strtod(s.c_str(), NULL);
	if(errno != 0)
	{
		return defaultValue;
	}
	return n;
}

bool Convert::StringToBool(const string &s, double defaultValue) {
	string ss = s;
	String::ToLower(ss);
	if (ss.find("true") != string::npos) {
		return true;
	}
	if (StringIsUInt(s) && strtol(s.c_str(), NULL, 10) != 0) {
		return true;
	}
	return defaultValue;
}

string Convert::IntToString(int n)
{
	string s;
	String::Format(s, "%d", n);
	return s;
}

string Convert::UIntToString(unsigned int n)
{
	string s;
	String::Format(s, "%u", n);
	return s;
}

string Convert::Int64ToString(int64_t n)
{
	string s;
	String::Format(s, "%lld", n);
	return s;
}

string Convert::UInt64ToString(uint64_t n)
{
	string s;
	String::Format(s, "%llu", n);
	return s;
}

Message* Convert::CreateMessage(const string& typeName)
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

bool Convert::JsonToMsg(Message *msg, const Json::Value &json) {
	const Descriptor* des = msg->GetDescriptor();
	const Reflection* ref = msg->GetReflection();
	for (int i = 0; i < des->field_count(); ++i) {
		const FieldDescriptor* field = des->field(i);
		const string& key = field->name();
		if (field->is_required()) {
			if (!json.isMember(key)) {
				error_log("[ConfigPBBase] key is not exists. key=%s", key.c_str());
				return false;
			}
		}
		if (!json.isObject()) {
			error_log("name=%s, key=%s, value=%s", msg->GetTypeName().c_str(), key.c_str(), Json::ToString(json).c_str());
			return false;
		}
		if (field->is_repeated() && json.isMember(key)) {
			if (!json[key].isArray()) {
				error_log("key is not array. key=%s name=%s", key.c_str(), msg->GetTypeName().c_str());
				return false;
			}
			for (unsigned j = 0; j < json[key].size(); ++j) {
				switch (field->cpp_type()) {
				case FieldDescriptor::CPPTYPE_DOUBLE:
					ref->AddDouble(msg, field, StringToDouble(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_FLOAT:
					ref->AddFloat(msg, field, StringToFloat(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_INT64:
					ref->AddInt64(msg, field, StringToInt64(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_UINT64:
					ref->AddUInt64(msg, field, StringToUInt64(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_INT32:
					ref->AddInt32(msg, field, StringToInt(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_UINT32:
					ref->AddUInt32(msg, field, StringToUInt(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_BOOL:
					ref->AddBool(msg, field, StringToBool(json[key][j].asString()));
					break;
				case FieldDescriptor::CPPTYPE_STRING:
					ref->AddString(msg, field, json[key][j].asString());
					break;
				case FieldDescriptor::CPPTYPE_MESSAGE:
					if (!JsonToMsg(ref->AddMessage(msg, field), json[key][j]))
						return false;
					break;
				default:
					break;
				}
			}
		} else if (json.isMember(key)) {
			switch (field->cpp_type()) {
			case FieldDescriptor::CPPTYPE_DOUBLE:
				ref->SetDouble(msg, field, StringToDouble(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_FLOAT:
				ref->SetFloat(msg, field, StringToFloat(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_INT64:
				ref->SetInt64(msg, field, StringToInt64(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_UINT64:
				ref->SetUInt64(msg, field, StringToUInt64(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_INT32:
				ref->SetInt32(msg, field, StringToInt(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_UINT32:
				ref->SetUInt32(msg, field, StringToUInt(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_BOOL:
				ref->SetBool(msg, field, StringToBool(json[key].asString()));
				break;
			case FieldDescriptor::CPPTYPE_STRING:
				ref->SetString(msg, field, json[key].asString());
				break;
			case FieldDescriptor::CPPTYPE_MESSAGE:
				if (!JsonToMsg(ref->MutableMessage(msg, field), json[key]))
					return false;
				break;
			default:
				break;
			}
		}
	}
	return true;
}
