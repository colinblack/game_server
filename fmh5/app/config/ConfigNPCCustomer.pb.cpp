// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigNPCCustomer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ConfigNPCCustomer {

namespace {

const ::google::protobuf::Descriptor* LevleTs_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LevleTs_reflection_ = NULL;
const ::google::protobuf::Descriptor* NPCCustomerCPP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NPCCustomerCPP_reflection_ = NULL;
const ::google::protobuf::Descriptor* NPCCustomerInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NPCCustomerInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigNPCCustomer_2eproto() {
  protobuf_AddDesc_ConfigNPCCustomer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigNPCCustomer.proto");
  GOOGLE_CHECK(file != NULL);
  LevleTs_descriptor_ = file->message_type(0);
  static const int LevleTs_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevleTs, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevleTs, ts_),
  };
  LevleTs_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LevleTs_descriptor_,
      LevleTs::default_instance_,
      LevleTs_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevleTs, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevleTs, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LevleTs));
  NPCCustomerCPP_descriptor_ = file->message_type(1);
  static const int NPCCustomerCPP_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, unlocklevel_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, npcmaxcnt_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, npccomemaxcnt_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, npcitemcntpercnt_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, pricebase_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, exp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, notincludeitem_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, levelts_),
  };
  NPCCustomerCPP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NPCCustomerCPP_descriptor_,
      NPCCustomerCPP::default_instance_,
      NPCCustomerCPP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerCPP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NPCCustomerCPP));
  NPCCustomerInfo_descriptor_ = file->message_type(2);
  static const int NPCCustomerInfo_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerInfo, npccustomer_),
  };
  NPCCustomerInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NPCCustomerInfo_descriptor_,
      NPCCustomerInfo::default_instance_,
      NPCCustomerInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCCustomerInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NPCCustomerInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigNPCCustomer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LevleTs_descriptor_, &LevleTs::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NPCCustomerCPP_descriptor_, &NPCCustomerCPP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NPCCustomerInfo_descriptor_, &NPCCustomerInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigNPCCustomer_2eproto() {
  delete LevleTs::default_instance_;
  delete LevleTs_reflection_;
  delete NPCCustomerCPP::default_instance_;
  delete NPCCustomerCPP_reflection_;
  delete NPCCustomerInfo::default_instance_;
  delete NPCCustomerInfo_reflection_;
}

void protobuf_AddDesc_ConfigNPCCustomer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027ConfigNPCCustomer.proto\022\021ConfigNPCCust"
    "omer\"$\n\007LevleTs\022\r\n\005level\030\001 \003(\r\022\n\n\002ts\030\002 \002"
    "(\r\"\316\001\n\016NPCCustomerCPP\022\023\n\013unlocklevel\030\001 \002"
    "(\r\022\021\n\tnpcMaxCnt\030\002 \002(\r\022\025\n\rnpcComeMaxCnt\030\003"
    " \002(\r\022\030\n\020npcItemCntPercnt\030\004 \003(\r\022\021\n\tpriceB"
    "ase\030\005 \002(\002\022\013\n\003exp\030\006 \002(\r\022\026\n\016notIncludeItem"
    "\030\007 \003(\r\022+\n\007levelts\030\010 \003(\0132\032.ConfigNPCCusto"
    "mer.LevleTs\"I\n\017NPCCustomerInfo\0226\n\013npccus"
    "tomer\030\001 \002(\0132!.ConfigNPCCustomer.NPCCusto"
    "merCPP", 366);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigNPCCustomer.proto", &protobuf_RegisterTypes);
  LevleTs::default_instance_ = new LevleTs();
  NPCCustomerCPP::default_instance_ = new NPCCustomerCPP();
  NPCCustomerInfo::default_instance_ = new NPCCustomerInfo();
  LevleTs::default_instance_->InitAsDefaultInstance();
  NPCCustomerCPP::default_instance_->InitAsDefaultInstance();
  NPCCustomerInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigNPCCustomer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigNPCCustomer_2eproto {
  StaticDescriptorInitializer_ConfigNPCCustomer_2eproto() {
    protobuf_AddDesc_ConfigNPCCustomer_2eproto();
  }
} static_descriptor_initializer_ConfigNPCCustomer_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int LevleTs::kLevelFieldNumber;
const int LevleTs::kTsFieldNumber;
#endif  // !_MSC_VER

LevleTs::LevleTs()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LevleTs::InitAsDefaultInstance() {
}

LevleTs::LevleTs(const LevleTs& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LevleTs::SharedCtor() {
  _cached_size_ = 0;
  ts_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LevleTs::~LevleTs() {
  SharedDtor();
}

void LevleTs::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LevleTs::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LevleTs::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LevleTs_descriptor_;
}

const LevleTs& LevleTs::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigNPCCustomer_2eproto();  return *default_instance_;
}

LevleTs* LevleTs::default_instance_ = NULL;

LevleTs* LevleTs::New() const {
  return new LevleTs;
}

void LevleTs::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    ts_ = 0u;
  }
  level_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LevleTs::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 level = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_level())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_level())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_level;
        if (input->ExpectTag(16)) goto parse_ts;
        break;
      }
      
      // required uint32 ts = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_ts:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ts_)));
          set_has_ts();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LevleTs::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 level = 1;
  for (int i = 0; i < this->level_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->level(i), output);
  }
  
  // required uint32 ts = 2;
  if (has_ts()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->ts(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LevleTs::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 level = 1;
  for (int i = 0; i < this->level_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->level(i), target);
  }
  
  // required uint32 ts = 2;
  if (has_ts()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->ts(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LevleTs::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required uint32 ts = 2;
    if (has_ts()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ts());
    }
    
  }
  // repeated uint32 level = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->level_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->level(i));
    }
    total_size += 1 * this->level_size() + data_size;
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LevleTs::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LevleTs* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LevleTs*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LevleTs::MergeFrom(const LevleTs& from) {
  GOOGLE_CHECK_NE(&from, this);
  level_.MergeFrom(from.level_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_ts()) {
      set_ts(from.ts());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LevleTs::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LevleTs::CopyFrom(const LevleTs& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LevleTs::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;
  
  return true;
}

void LevleTs::Swap(LevleTs* other) {
  if (other != this) {
    level_.Swap(&other->level_);
    std::swap(ts_, other->ts_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LevleTs::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LevleTs_descriptor_;
  metadata.reflection = LevleTs_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int NPCCustomerCPP::kUnlocklevelFieldNumber;
const int NPCCustomerCPP::kNpcMaxCntFieldNumber;
const int NPCCustomerCPP::kNpcComeMaxCntFieldNumber;
const int NPCCustomerCPP::kNpcItemCntPercntFieldNumber;
const int NPCCustomerCPP::kPriceBaseFieldNumber;
const int NPCCustomerCPP::kExpFieldNumber;
const int NPCCustomerCPP::kNotIncludeItemFieldNumber;
const int NPCCustomerCPP::kLeveltsFieldNumber;
#endif  // !_MSC_VER

NPCCustomerCPP::NPCCustomerCPP()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void NPCCustomerCPP::InitAsDefaultInstance() {
}

NPCCustomerCPP::NPCCustomerCPP(const NPCCustomerCPP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void NPCCustomerCPP::SharedCtor() {
  _cached_size_ = 0;
  unlocklevel_ = 0u;
  npcmaxcnt_ = 0u;
  npccomemaxcnt_ = 0u;
  pricebase_ = 0;
  exp_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NPCCustomerCPP::~NPCCustomerCPP() {
  SharedDtor();
}

void NPCCustomerCPP::SharedDtor() {
  if (this != default_instance_) {
  }
}

void NPCCustomerCPP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NPCCustomerCPP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NPCCustomerCPP_descriptor_;
}

const NPCCustomerCPP& NPCCustomerCPP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigNPCCustomer_2eproto();  return *default_instance_;
}

NPCCustomerCPP* NPCCustomerCPP::default_instance_ = NULL;

NPCCustomerCPP* NPCCustomerCPP::New() const {
  return new NPCCustomerCPP;
}

void NPCCustomerCPP::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    unlocklevel_ = 0u;
    npcmaxcnt_ = 0u;
    npccomemaxcnt_ = 0u;
    pricebase_ = 0;
    exp_ = 0u;
  }
  npcitemcntpercnt_.Clear();
  notincludeitem_.Clear();
  levelts_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NPCCustomerCPP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 unlocklevel = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &unlocklevel_)));
          set_has_unlocklevel();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_npcMaxCnt;
        break;
      }
      
      // required uint32 npcMaxCnt = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_npcMaxCnt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &npcmaxcnt_)));
          set_has_npcmaxcnt();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_npcComeMaxCnt;
        break;
      }
      
      // required uint32 npcComeMaxCnt = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_npcComeMaxCnt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &npccomemaxcnt_)));
          set_has_npccomemaxcnt();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_npcItemCntPercnt;
        break;
      }
      
      // repeated uint32 npcItemCntPercnt = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_npcItemCntPercnt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 32, input, this->mutable_npcitemcntpercnt())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_npcitemcntpercnt())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_npcItemCntPercnt;
        if (input->ExpectTag(45)) goto parse_priceBase;
        break;
      }
      
      // required float priceBase = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_priceBase:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &pricebase_)));
          set_has_pricebase();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_exp;
        break;
      }
      
      // required uint32 exp = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_exp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &exp_)));
          set_has_exp();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_notIncludeItem;
        break;
      }
      
      // repeated uint32 notIncludeItem = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_notIncludeItem:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 56, input, this->mutable_notincludeitem())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_notincludeitem())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_notIncludeItem;
        if (input->ExpectTag(66)) goto parse_levelts;
        break;
      }
      
      // repeated .ConfigNPCCustomer.LevleTs levelts = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_levelts:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_levelts()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_levelts;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void NPCCustomerCPP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 unlocklevel = 1;
  if (has_unlocklevel()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->unlocklevel(), output);
  }
  
  // required uint32 npcMaxCnt = 2;
  if (has_npcmaxcnt()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->npcmaxcnt(), output);
  }
  
  // required uint32 npcComeMaxCnt = 3;
  if (has_npccomemaxcnt()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->npccomemaxcnt(), output);
  }
  
  // repeated uint32 npcItemCntPercnt = 4;
  for (int i = 0; i < this->npcitemcntpercnt_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      4, this->npcitemcntpercnt(i), output);
  }
  
  // required float priceBase = 5;
  if (has_pricebase()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->pricebase(), output);
  }
  
  // required uint32 exp = 6;
  if (has_exp()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->exp(), output);
  }
  
  // repeated uint32 notIncludeItem = 7;
  for (int i = 0; i < this->notincludeitem_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      7, this->notincludeitem(i), output);
  }
  
  // repeated .ConfigNPCCustomer.LevleTs levelts = 8;
  for (int i = 0; i < this->levelts_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      8, this->levelts(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* NPCCustomerCPP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 unlocklevel = 1;
  if (has_unlocklevel()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->unlocklevel(), target);
  }
  
  // required uint32 npcMaxCnt = 2;
  if (has_npcmaxcnt()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->npcmaxcnt(), target);
  }
  
  // required uint32 npcComeMaxCnt = 3;
  if (has_npccomemaxcnt()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->npccomemaxcnt(), target);
  }
  
  // repeated uint32 npcItemCntPercnt = 4;
  for (int i = 0; i < this->npcitemcntpercnt_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(4, this->npcitemcntpercnt(i), target);
  }
  
  // required float priceBase = 5;
  if (has_pricebase()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->pricebase(), target);
  }
  
  // required uint32 exp = 6;
  if (has_exp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->exp(), target);
  }
  
  // repeated uint32 notIncludeItem = 7;
  for (int i = 0; i < this->notincludeitem_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(7, this->notincludeitem(i), target);
  }
  
  // repeated .ConfigNPCCustomer.LevleTs levelts = 8;
  for (int i = 0; i < this->levelts_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        8, this->levelts(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int NPCCustomerCPP::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 unlocklevel = 1;
    if (has_unlocklevel()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->unlocklevel());
    }
    
    // required uint32 npcMaxCnt = 2;
    if (has_npcmaxcnt()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->npcmaxcnt());
    }
    
    // required uint32 npcComeMaxCnt = 3;
    if (has_npccomemaxcnt()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->npccomemaxcnt());
    }
    
    // required float priceBase = 5;
    if (has_pricebase()) {
      total_size += 1 + 4;
    }
    
    // required uint32 exp = 6;
    if (has_exp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->exp());
    }
    
  }
  // repeated uint32 npcItemCntPercnt = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->npcitemcntpercnt_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->npcitemcntpercnt(i));
    }
    total_size += 1 * this->npcitemcntpercnt_size() + data_size;
  }
  
  // repeated uint32 notIncludeItem = 7;
  {
    int data_size = 0;
    for (int i = 0; i < this->notincludeitem_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->notincludeitem(i));
    }
    total_size += 1 * this->notincludeitem_size() + data_size;
  }
  
  // repeated .ConfigNPCCustomer.LevleTs levelts = 8;
  total_size += 1 * this->levelts_size();
  for (int i = 0; i < this->levelts_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->levelts(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void NPCCustomerCPP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NPCCustomerCPP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NPCCustomerCPP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NPCCustomerCPP::MergeFrom(const NPCCustomerCPP& from) {
  GOOGLE_CHECK_NE(&from, this);
  npcitemcntpercnt_.MergeFrom(from.npcitemcntpercnt_);
  notincludeitem_.MergeFrom(from.notincludeitem_);
  levelts_.MergeFrom(from.levelts_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_unlocklevel()) {
      set_unlocklevel(from.unlocklevel());
    }
    if (from.has_npcmaxcnt()) {
      set_npcmaxcnt(from.npcmaxcnt());
    }
    if (from.has_npccomemaxcnt()) {
      set_npccomemaxcnt(from.npccomemaxcnt());
    }
    if (from.has_pricebase()) {
      set_pricebase(from.pricebase());
    }
    if (from.has_exp()) {
      set_exp(from.exp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NPCCustomerCPP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NPCCustomerCPP::CopyFrom(const NPCCustomerCPP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NPCCustomerCPP::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000037) != 0x00000037) return false;
  
  for (int i = 0; i < levelts_size(); i++) {
    if (!this->levelts(i).IsInitialized()) return false;
  }
  return true;
}

void NPCCustomerCPP::Swap(NPCCustomerCPP* other) {
  if (other != this) {
    std::swap(unlocklevel_, other->unlocklevel_);
    std::swap(npcmaxcnt_, other->npcmaxcnt_);
    std::swap(npccomemaxcnt_, other->npccomemaxcnt_);
    npcitemcntpercnt_.Swap(&other->npcitemcntpercnt_);
    std::swap(pricebase_, other->pricebase_);
    std::swap(exp_, other->exp_);
    notincludeitem_.Swap(&other->notincludeitem_);
    levelts_.Swap(&other->levelts_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NPCCustomerCPP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NPCCustomerCPP_descriptor_;
  metadata.reflection = NPCCustomerCPP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int NPCCustomerInfo::kNpccustomerFieldNumber;
#endif  // !_MSC_VER

NPCCustomerInfo::NPCCustomerInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void NPCCustomerInfo::InitAsDefaultInstance() {
  npccustomer_ = const_cast< ::ConfigNPCCustomer::NPCCustomerCPP*>(&::ConfigNPCCustomer::NPCCustomerCPP::default_instance());
}

NPCCustomerInfo::NPCCustomerInfo(const NPCCustomerInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void NPCCustomerInfo::SharedCtor() {
  _cached_size_ = 0;
  npccustomer_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NPCCustomerInfo::~NPCCustomerInfo() {
  SharedDtor();
}

void NPCCustomerInfo::SharedDtor() {
  if (this != default_instance_) {
    delete npccustomer_;
  }
}

void NPCCustomerInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NPCCustomerInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NPCCustomerInfo_descriptor_;
}

const NPCCustomerInfo& NPCCustomerInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigNPCCustomer_2eproto();  return *default_instance_;
}

NPCCustomerInfo* NPCCustomerInfo::default_instance_ = NULL;

NPCCustomerInfo* NPCCustomerInfo::New() const {
  return new NPCCustomerInfo;
}

void NPCCustomerInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_npccustomer()) {
      if (npccustomer_ != NULL) npccustomer_->::ConfigNPCCustomer::NPCCustomerCPP::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NPCCustomerInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ConfigNPCCustomer.NPCCustomerCPP npccustomer = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_npccustomer()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void NPCCustomerInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .ConfigNPCCustomer.NPCCustomerCPP npccustomer = 1;
  if (has_npccustomer()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->npccustomer(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* NPCCustomerInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .ConfigNPCCustomer.NPCCustomerCPP npccustomer = 1;
  if (has_npccustomer()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->npccustomer(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int NPCCustomerInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ConfigNPCCustomer.NPCCustomerCPP npccustomer = 1;
    if (has_npccustomer()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->npccustomer());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void NPCCustomerInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NPCCustomerInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NPCCustomerInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NPCCustomerInfo::MergeFrom(const NPCCustomerInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_npccustomer()) {
      mutable_npccustomer()->::ConfigNPCCustomer::NPCCustomerCPP::MergeFrom(from.npccustomer());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NPCCustomerInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NPCCustomerInfo::CopyFrom(const NPCCustomerInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NPCCustomerInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  if (has_npccustomer()) {
    if (!this->npccustomer().IsInitialized()) return false;
  }
  return true;
}

void NPCCustomerInfo::Swap(NPCCustomerInfo* other) {
  if (other != this) {
    std::swap(npccustomer_, other->npccustomer_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NPCCustomerInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NPCCustomerInfo_descriptor_;
  metadata.reflection = NPCCustomerInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigNPCCustomer

// @@protoc_insertion_point(global_scope)