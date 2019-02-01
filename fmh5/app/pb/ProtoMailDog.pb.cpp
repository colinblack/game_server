// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProtoMailDog.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ProtoMailDog {

namespace {

const ::google::protobuf::Descriptor* MaidDogCPP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MaidDogCPP_reflection_ = NULL;
const ::google::protobuf::Descriptor* ProsperityValueCPP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ProsperityValueCPP_reflection_ = NULL;
const ::google::protobuf::Descriptor* GetMailDogInfoReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GetMailDogInfoReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* GetMailDogInfoResp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GetMailDogInfoResp_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProtoMailDog_2eproto() {
  protobuf_AddDesc_ProtoMailDog_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProtoMailDog.proto");
  GOOGLE_CHECK(file != NULL);
  MaidDogCPP_descriptor_ = file->message_type(0);
  static const int MaidDogCPP_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MaidDogCPP, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MaidDogCPP, value_),
  };
  MaidDogCPP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MaidDogCPP_descriptor_,
      MaidDogCPP::default_instance_,
      MaidDogCPP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MaidDogCPP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MaidDogCPP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MaidDogCPP));
  ProsperityValueCPP_descriptor_ = file->message_type(1);
  static const int ProsperityValueCPP_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProsperityValueCPP, prosperity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProsperityValueCPP, rewardts_),
  };
  ProsperityValueCPP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ProsperityValueCPP_descriptor_,
      ProsperityValueCPP::default_instance_,
      ProsperityValueCPP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProsperityValueCPP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProsperityValueCPP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ProsperityValueCPP));
  GetMailDogInfoReq_descriptor_ = file->message_type(2);
  static const int GetMailDogInfoReq_offsets_[1] = {
  };
  GetMailDogInfoReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GetMailDogInfoReq_descriptor_,
      GetMailDogInfoReq::default_instance_,
      GetMailDogInfoReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GetMailDogInfoReq));
  GetMailDogInfoResp_descriptor_ = file->message_type(3);
  static const int GetMailDogInfoResp_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoResp, dog_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoResp, prosperity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoResp, commons_),
  };
  GetMailDogInfoResp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GetMailDogInfoResp_descriptor_,
      GetMailDogInfoResp::default_instance_,
      GetMailDogInfoResp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoResp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetMailDogInfoResp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GetMailDogInfoResp));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProtoMailDog_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MaidDogCPP_descriptor_, &MaidDogCPP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ProsperityValueCPP_descriptor_, &ProsperityValueCPP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GetMailDogInfoReq_descriptor_, &GetMailDogInfoReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GetMailDogInfoResp_descriptor_, &GetMailDogInfoResp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProtoMailDog_2eproto() {
  delete MaidDogCPP::default_instance_;
  delete MaidDogCPP_reflection_;
  delete ProsperityValueCPP::default_instance_;
  delete ProsperityValueCPP_reflection_;
  delete GetMailDogInfoReq::default_instance_;
  delete GetMailDogInfoReq_reflection_;
  delete GetMailDogInfoResp::default_instance_;
  delete GetMailDogInfoResp_reflection_;
}

void protobuf_AddDesc_ProtoMailDog_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::DataCommon::protobuf_AddDesc_DataCommon_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022ProtoMailDog.proto\022\014ProtoMailDog\032\020Data"
    "Common.proto\"\'\n\nMaidDogCPP\022\n\n\002id\030\001 \002(\r\022\r"
    "\n\005value\030\002 \002(\r\":\n\022ProsperityValueCPP\022\022\n\np"
    "rosperity\030\001 \002(\r\022\020\n\010rewardts\030\002 \001(\r\"\023\n\021Get"
    "MailDogInfoReq\"\236\001\n\022GetMailDogInfoResp\022%\n"
    "\003dog\030\001 \003(\0132\030.ProtoMailDog.MaidDogCPP\0224\n\n"
    "prosperity\030\002 \002(\0132 .ProtoMailDog.Prosperi"
    "tyValueCPP\022+\n\007commons\030\003 \001(\0132\032.DataCommon"
    ".CommonItemsCPP", 335);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProtoMailDog.proto", &protobuf_RegisterTypes);
  MaidDogCPP::default_instance_ = new MaidDogCPP();
  ProsperityValueCPP::default_instance_ = new ProsperityValueCPP();
  GetMailDogInfoReq::default_instance_ = new GetMailDogInfoReq();
  GetMailDogInfoResp::default_instance_ = new GetMailDogInfoResp();
  MaidDogCPP::default_instance_->InitAsDefaultInstance();
  ProsperityValueCPP::default_instance_->InitAsDefaultInstance();
  GetMailDogInfoReq::default_instance_->InitAsDefaultInstance();
  GetMailDogInfoResp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProtoMailDog_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProtoMailDog_2eproto {
  StaticDescriptorInitializer_ProtoMailDog_2eproto() {
    protobuf_AddDesc_ProtoMailDog_2eproto();
  }
} static_descriptor_initializer_ProtoMailDog_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int MaidDogCPP::kIdFieldNumber;
const int MaidDogCPP::kValueFieldNumber;
#endif  // !_MSC_VER

MaidDogCPP::MaidDogCPP()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MaidDogCPP::InitAsDefaultInstance() {
}

MaidDogCPP::MaidDogCPP(const MaidDogCPP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MaidDogCPP::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  value_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MaidDogCPP::~MaidDogCPP() {
  SharedDtor();
}

void MaidDogCPP::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MaidDogCPP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MaidDogCPP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MaidDogCPP_descriptor_;
}

const MaidDogCPP& MaidDogCPP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoMailDog_2eproto();  return *default_instance_;
}

MaidDogCPP* MaidDogCPP::default_instance_ = NULL;

MaidDogCPP* MaidDogCPP::New() const {
  return new MaidDogCPP;
}

void MaidDogCPP::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0u;
    value_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MaidDogCPP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_value;
        break;
      }
      
      // required uint32 value = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_value:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &value_)));
          set_has_value();
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

void MaidDogCPP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }
  
  // required uint32 value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->value(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MaidDogCPP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }
  
  // required uint32 value = 2;
  if (has_value()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->value(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MaidDogCPP::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }
    
    // required uint32 value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->value());
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

void MaidDogCPP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MaidDogCPP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MaidDogCPP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MaidDogCPP::MergeFrom(const MaidDogCPP& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MaidDogCPP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MaidDogCPP::CopyFrom(const MaidDogCPP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MaidDogCPP::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void MaidDogCPP::Swap(MaidDogCPP* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(value_, other->value_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MaidDogCPP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MaidDogCPP_descriptor_;
  metadata.reflection = MaidDogCPP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ProsperityValueCPP::kProsperityFieldNumber;
const int ProsperityValueCPP::kRewardtsFieldNumber;
#endif  // !_MSC_VER

ProsperityValueCPP::ProsperityValueCPP()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ProsperityValueCPP::InitAsDefaultInstance() {
}

ProsperityValueCPP::ProsperityValueCPP(const ProsperityValueCPP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ProsperityValueCPP::SharedCtor() {
  _cached_size_ = 0;
  prosperity_ = 0u;
  rewardts_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ProsperityValueCPP::~ProsperityValueCPP() {
  SharedDtor();
}

void ProsperityValueCPP::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ProsperityValueCPP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProsperityValueCPP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ProsperityValueCPP_descriptor_;
}

const ProsperityValueCPP& ProsperityValueCPP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoMailDog_2eproto();  return *default_instance_;
}

ProsperityValueCPP* ProsperityValueCPP::default_instance_ = NULL;

ProsperityValueCPP* ProsperityValueCPP::New() const {
  return new ProsperityValueCPP;
}

void ProsperityValueCPP::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    prosperity_ = 0u;
    rewardts_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ProsperityValueCPP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 prosperity = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &prosperity_)));
          set_has_prosperity();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_rewardts;
        break;
      }
      
      // optional uint32 rewardts = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_rewardts:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rewardts_)));
          set_has_rewardts();
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

void ProsperityValueCPP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 prosperity = 1;
  if (has_prosperity()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->prosperity(), output);
  }
  
  // optional uint32 rewardts = 2;
  if (has_rewardts()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->rewardts(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ProsperityValueCPP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 prosperity = 1;
  if (has_prosperity()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->prosperity(), target);
  }
  
  // optional uint32 rewardts = 2;
  if (has_rewardts()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->rewardts(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ProsperityValueCPP::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 prosperity = 1;
    if (has_prosperity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->prosperity());
    }
    
    // optional uint32 rewardts = 2;
    if (has_rewardts()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->rewardts());
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

void ProsperityValueCPP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ProsperityValueCPP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ProsperityValueCPP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ProsperityValueCPP::MergeFrom(const ProsperityValueCPP& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_prosperity()) {
      set_prosperity(from.prosperity());
    }
    if (from.has_rewardts()) {
      set_rewardts(from.rewardts());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ProsperityValueCPP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProsperityValueCPP::CopyFrom(const ProsperityValueCPP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProsperityValueCPP::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void ProsperityValueCPP::Swap(ProsperityValueCPP* other) {
  if (other != this) {
    std::swap(prosperity_, other->prosperity_);
    std::swap(rewardts_, other->rewardts_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ProsperityValueCPP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ProsperityValueCPP_descriptor_;
  metadata.reflection = ProsperityValueCPP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

GetMailDogInfoReq::GetMailDogInfoReq()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GetMailDogInfoReq::InitAsDefaultInstance() {
}

GetMailDogInfoReq::GetMailDogInfoReq(const GetMailDogInfoReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GetMailDogInfoReq::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GetMailDogInfoReq::~GetMailDogInfoReq() {
  SharedDtor();
}

void GetMailDogInfoReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GetMailDogInfoReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GetMailDogInfoReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GetMailDogInfoReq_descriptor_;
}

const GetMailDogInfoReq& GetMailDogInfoReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoMailDog_2eproto();  return *default_instance_;
}

GetMailDogInfoReq* GetMailDogInfoReq::default_instance_ = NULL;

GetMailDogInfoReq* GetMailDogInfoReq::New() const {
  return new GetMailDogInfoReq;
}

void GetMailDogInfoReq::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GetMailDogInfoReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void GetMailDogInfoReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GetMailDogInfoReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GetMailDogInfoReq::ByteSize() const {
  int total_size = 0;
  
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

void GetMailDogInfoReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GetMailDogInfoReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GetMailDogInfoReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GetMailDogInfoReq::MergeFrom(const GetMailDogInfoReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GetMailDogInfoReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetMailDogInfoReq::CopyFrom(const GetMailDogInfoReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetMailDogInfoReq::IsInitialized() const {
  
  return true;
}

void GetMailDogInfoReq::Swap(GetMailDogInfoReq* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GetMailDogInfoReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GetMailDogInfoReq_descriptor_;
  metadata.reflection = GetMailDogInfoReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GetMailDogInfoResp::kDogFieldNumber;
const int GetMailDogInfoResp::kProsperityFieldNumber;
const int GetMailDogInfoResp::kCommonsFieldNumber;
#endif  // !_MSC_VER

GetMailDogInfoResp::GetMailDogInfoResp()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GetMailDogInfoResp::InitAsDefaultInstance() {
  prosperity_ = const_cast< ::ProtoMailDog::ProsperityValueCPP*>(&::ProtoMailDog::ProsperityValueCPP::default_instance());
  commons_ = const_cast< ::DataCommon::CommonItemsCPP*>(&::DataCommon::CommonItemsCPP::default_instance());
}

GetMailDogInfoResp::GetMailDogInfoResp(const GetMailDogInfoResp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GetMailDogInfoResp::SharedCtor() {
  _cached_size_ = 0;
  prosperity_ = NULL;
  commons_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GetMailDogInfoResp::~GetMailDogInfoResp() {
  SharedDtor();
}

void GetMailDogInfoResp::SharedDtor() {
  if (this != default_instance_) {
    delete prosperity_;
    delete commons_;
  }
}

void GetMailDogInfoResp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GetMailDogInfoResp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GetMailDogInfoResp_descriptor_;
}

const GetMailDogInfoResp& GetMailDogInfoResp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoMailDog_2eproto();  return *default_instance_;
}

GetMailDogInfoResp* GetMailDogInfoResp::default_instance_ = NULL;

GetMailDogInfoResp* GetMailDogInfoResp::New() const {
  return new GetMailDogInfoResp;
}

void GetMailDogInfoResp::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (has_prosperity()) {
      if (prosperity_ != NULL) prosperity_->::ProtoMailDog::ProsperityValueCPP::Clear();
    }
    if (has_commons()) {
      if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
    }
  }
  dog_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GetMailDogInfoResp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ProtoMailDog.MaidDogCPP dog = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dog:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_dog()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_dog;
        if (input->ExpectTag(18)) goto parse_prosperity;
        break;
      }
      
      // required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_prosperity:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_prosperity()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_commons;
        break;
      }
      
      // optional .DataCommon.CommonItemsCPP commons = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_commons:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_commons()));
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

void GetMailDogInfoResp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ProtoMailDog.MaidDogCPP dog = 1;
  for (int i = 0; i < this->dog_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->dog(i), output);
  }
  
  // required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
  if (has_prosperity()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->prosperity(), output);
  }
  
  // optional .DataCommon.CommonItemsCPP commons = 3;
  if (has_commons()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->commons(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GetMailDogInfoResp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ProtoMailDog.MaidDogCPP dog = 1;
  for (int i = 0; i < this->dog_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->dog(i), target);
  }
  
  // required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
  if (has_prosperity()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->prosperity(), target);
  }
  
  // optional .DataCommon.CommonItemsCPP commons = 3;
  if (has_commons()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->commons(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GetMailDogInfoResp::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
    if (has_prosperity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->prosperity());
    }
    
    // optional .DataCommon.CommonItemsCPP commons = 3;
    if (has_commons()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->commons());
    }
    
  }
  // repeated .ProtoMailDog.MaidDogCPP dog = 1;
  total_size += 1 * this->dog_size();
  for (int i = 0; i < this->dog_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->dog(i));
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

void GetMailDogInfoResp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GetMailDogInfoResp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GetMailDogInfoResp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GetMailDogInfoResp::MergeFrom(const GetMailDogInfoResp& from) {
  GOOGLE_CHECK_NE(&from, this);
  dog_.MergeFrom(from.dog_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_prosperity()) {
      mutable_prosperity()->::ProtoMailDog::ProsperityValueCPP::MergeFrom(from.prosperity());
    }
    if (from.has_commons()) {
      mutable_commons()->::DataCommon::CommonItemsCPP::MergeFrom(from.commons());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GetMailDogInfoResp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetMailDogInfoResp::CopyFrom(const GetMailDogInfoResp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetMailDogInfoResp::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;
  
  for (int i = 0; i < dog_size(); i++) {
    if (!this->dog(i).IsInitialized()) return false;
  }
  if (has_prosperity()) {
    if (!this->prosperity().IsInitialized()) return false;
  }
  if (has_commons()) {
    if (!this->commons().IsInitialized()) return false;
  }
  return true;
}

void GetMailDogInfoResp::Swap(GetMailDogInfoResp* other) {
  if (other != this) {
    dog_.Swap(&other->dog_);
    std::swap(prosperity_, other->prosperity_);
    std::swap(commons_, other->commons_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GetMailDogInfoResp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GetMailDogInfoResp_descriptor_;
  metadata.reflection = GetMailDogInfoResp_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoMailDog

// @@protoc_insertion_point(global_scope)
