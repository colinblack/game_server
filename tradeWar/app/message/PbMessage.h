/*
 * PbMessage.h
 *
 *  Created on: 2018年1月24日
 *      Author: Administrator
 */

#ifndef PB_MESSAGE_H_
#define PB_MESSAGE_H_

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>

using google::protobuf::Message;
using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::MessageFactory;
using google::protobuf::Reflection;

#include "RankList.pb.h"
#include "SystemMsg.pb.h"
#include "AutoTransport.pb.h"
#include "WorldBattle.pb.h"
#include "WanBaGift.pb.h"

#endif /* PB_MESSAGE_H_ */
