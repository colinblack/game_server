// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CdKey.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace CdKey {

namespace {

const ::google::protobuf::Descriptor* RewardInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RewardInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* CdKeyCfg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CdKeyCfg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CdKey_2eproto() {
  protobuf_AddDesc_CdKey_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CdKey.proto");
  GOOGLE_CHECK(file != NULL);
  RewardInfo_descriptor_ = file->message_type(0);
  static const int RewardInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RewardInfo, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RewardInfo, prize_),
  };
  RewardInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RewardInfo_descriptor_,
      RewardInfo::default_instance_,
      RewardInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RewardInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RewardInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RewardInfo));
  CdKeyCfg_descriptor_ = file->message_type(1);
  static const int CdKeyCfg_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CdKeyCfg, rewards_),
  };
  CdKeyCfg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CdKeyCfg_descriptor_,
      CdKeyCfg::default_instance_,
      CdKeyCfg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CdKeyCfg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CdKeyCfg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CdKeyCfg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CdKey_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RewardInfo_descriptor_, &RewardInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CdKeyCfg_descriptor_, &CdKeyCfg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CdKey_2eproto() {
  delete RewardInfo::default_instance_;
  delete RewardInfo_reflection_;
  delete CdKeyCfg::default_instance_;
  delete CdKeyCfg_reflection_;
}

void protobuf_AddDesc_CdKey_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CommonGiftConfig::protobuf_AddDesc_CommonGiftConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013CdKey.proto\022\005CdKey\032\026CommonGiftConfig.p"
    "roto\"M\n\nRewardInfo\022\014\n\004type\030\001 \002(\r\0221\n\005priz"
    "e\030\002 \003(\0132\".CommonGiftConfig.CommonModifyI"
    "tem\".\n\010CdKeyCfg\022\"\n\007rewards\030\001 \003(\0132\021.CdKey"
    ".RewardInfo", 171);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CdKey.proto", &protobuf_RegisterTypes);
  RewardInfo::default_instance_ = new RewardInfo();
  CdKeyCfg::default_instance_ = new CdKeyCfg();
  RewardInfo::default_instance_->InitAsDefaultInstance();
  CdKeyCfg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CdKey_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CdKey_2eproto {
  StaticDescriptorInitializer_CdKey_2eproto() {
    protobuf_AddDesc_CdKey_2eproto();
  }
} static_descriptor_initializer_CdKey_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int RewardInfo::kTypeFieldNumber;
const int RewardInfo::kPrizeFieldNumber;
#endif  // !_MSC_VER

RewardInfo::RewardInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RewardInfo::InitAsDefaultInstance() {
}

RewardInfo::RewardInfo(const RewardInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RewardInfo::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RewardInfo::~RewardInfo() {
  SharedDtor();
}

void RewardInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void RewardInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RewardInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RewardInfo_descriptor_;
}

const RewardInfo& RewardInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CdKey_2eproto();  return *default_instance_;
}

RewardInfo* RewardInfo::default_instance_ = NULL;

RewardInfo* RewardInfo::New() const {
  return new RewardInfo;
}

void RewardInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0u;
  }
  prize_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RewardInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_prize;
        break;
      }
      
      // repeated .CommonGiftConfig.CommonModifyItem prize = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_prize:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_prize()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_prize;
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

void RewardInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->type(), output);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItem prize = 2;
  for (int i = 0; i < this->prize_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->prize(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RewardInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->type(), target);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItem prize = 2;
  for (int i = 0; i < this->prize_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->prize(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RewardInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }
    
  }
  // repeated .CommonGiftConfig.CommonModifyItem prize = 2;
  total_size += 1 * this->prize_size();
  for (int i = 0; i < this->prize_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->prize(i));
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

void RewardInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RewardInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RewardInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RewardInfo::MergeFrom(const RewardInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  prize_.MergeFrom(from.prize_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RewardInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RewardInfo::CopyFrom(const RewardInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RewardInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  for (int i = 0; i < prize_size(); i++) {
    if (!this->prize(i).IsInitialized()) return false;
  }
  return true;
}

void RewardInfo::Swap(RewardInfo* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    prize_.Swap(&other->prize_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RewardInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RewardInfo_descriptor_;
  metadata.reflection = RewardInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int CdKeyCfg::kRewardsFieldNumber;
#endif  // !_MSC_VER

CdKeyCfg::CdKeyCfg()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CdKeyCfg::InitAsDefaultInstance() {
}

CdKeyCfg::CdKeyCfg(const CdKeyCfg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CdKeyCfg::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CdKeyCfg::~CdKeyCfg() {
  SharedDtor();
}

void CdKeyCfg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void CdKeyCfg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CdKeyCfg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CdKeyCfg_descriptor_;
}

const CdKeyCfg& CdKeyCfg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CdKey_2eproto();  return *default_instance_;
}

CdKeyCfg* CdKeyCfg::default_instance_ = NULL;

CdKeyCfg* CdKeyCfg::New() const {
  return new CdKeyCfg;
}

void CdKeyCfg::Clear() {
  rewards_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CdKeyCfg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CdKey.RewardInfo rewards = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_rewards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_rewards()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_rewards;
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

void CdKeyCfg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .CdKey.RewardInfo rewards = 1;
  for (int i = 0; i < this->rewards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->rewards(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CdKeyCfg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .CdKey.RewardInfo rewards = 1;
  for (int i = 0; i < this->rewards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->rewards(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CdKeyCfg::ByteSize() const {
  int total_size = 0;
  
  // repeated .CdKey.RewardInfo rewards = 1;
  total_size += 1 * this->rewards_size();
  for (int i = 0; i < this->rewards_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->rewards(i));
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

void CdKeyCfg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CdKeyCfg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CdKeyCfg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CdKeyCfg::MergeFrom(const CdKeyCfg& from) {
  GOOGLE_CHECK_NE(&from, this);
  rewards_.MergeFrom(from.rewards_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CdKeyCfg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CdKeyCfg::CopyFrom(const CdKeyCfg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CdKeyCfg::IsInitialized() const {
  
  for (int i = 0; i < rewards_size(); i++) {
    if (!this->rewards(i).IsInitialized()) return false;
  }
  return true;
}

void CdKeyCfg::Swap(CdKeyCfg* other) {
  if (other != this) {
    rewards_.Swap(&other->rewards_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CdKeyCfg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CdKeyCfg_descriptor_;
  metadata.reflection = CdKeyCfg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CdKey

// @@protoc_insertion_point(global_scope)
