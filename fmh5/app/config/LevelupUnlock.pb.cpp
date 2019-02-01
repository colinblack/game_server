// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "LevelupUnlock.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace LevelupUnlock {

namespace {

const ::google::protobuf::Descriptor* LevelRewards_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LevelRewards_reflection_ = NULL;
const ::google::protobuf::Descriptor* LevelupUnlockCfg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LevelupUnlockCfg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_LevelupUnlock_2eproto() {
  protobuf_AddDesc_LevelupUnlock_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "LevelupUnlock.proto");
  GOOGLE_CHECK(file != NULL);
  LevelRewards_descriptor_ = file->message_type(0);
  static const int LevelRewards_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelRewards, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelRewards, prize_),
  };
  LevelRewards_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LevelRewards_descriptor_,
      LevelRewards::default_instance_,
      LevelRewards_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelRewards, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelRewards, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LevelRewards));
  LevelupUnlockCfg_descriptor_ = file->message_type(1);
  static const int LevelupUnlockCfg_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelupUnlockCfg, levels_),
  };
  LevelupUnlockCfg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LevelupUnlockCfg_descriptor_,
      LevelupUnlockCfg::default_instance_,
      LevelupUnlockCfg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelupUnlockCfg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelupUnlockCfg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LevelupUnlockCfg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_LevelupUnlock_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LevelRewards_descriptor_, &LevelRewards::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LevelupUnlockCfg_descriptor_, &LevelupUnlockCfg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_LevelupUnlock_2eproto() {
  delete LevelRewards::default_instance_;
  delete LevelRewards_reflection_;
  delete LevelupUnlockCfg::default_instance_;
  delete LevelupUnlockCfg_reflection_;
}

void protobuf_AddDesc_LevelupUnlock_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CommonGiftConfig::protobuf_AddDesc_CommonGiftConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023LevelupUnlock.proto\022\rLevelupUnlock\032\026Co"
    "mmonGiftConfig.proto\"P\n\014LevelRewards\022\r\n\005"
    "level\030\001 \002(\r\0221\n\005prize\030\002 \003(\0132\".CommonGiftC"
    "onfig.CommonModifyItem\"\?\n\020LevelupUnlockC"
    "fg\022+\n\006levels\030\001 \003(\0132\033.LevelupUnlock.Level"
    "Rewards", 207);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "LevelupUnlock.proto", &protobuf_RegisterTypes);
  LevelRewards::default_instance_ = new LevelRewards();
  LevelupUnlockCfg::default_instance_ = new LevelupUnlockCfg();
  LevelRewards::default_instance_->InitAsDefaultInstance();
  LevelupUnlockCfg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_LevelupUnlock_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_LevelupUnlock_2eproto {
  StaticDescriptorInitializer_LevelupUnlock_2eproto() {
    protobuf_AddDesc_LevelupUnlock_2eproto();
  }
} static_descriptor_initializer_LevelupUnlock_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int LevelRewards::kLevelFieldNumber;
const int LevelRewards::kPrizeFieldNumber;
#endif  // !_MSC_VER

LevelRewards::LevelRewards()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LevelRewards::InitAsDefaultInstance() {
}

LevelRewards::LevelRewards(const LevelRewards& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LevelRewards::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LevelRewards::~LevelRewards() {
  SharedDtor();
}

void LevelRewards::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LevelRewards::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LevelRewards::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LevelRewards_descriptor_;
}

const LevelRewards& LevelRewards::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_LevelupUnlock_2eproto();  return *default_instance_;
}

LevelRewards* LevelRewards::default_instance_ = NULL;

LevelRewards* LevelRewards::New() const {
  return new LevelRewards;
}

void LevelRewards::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    level_ = 0u;
  }
  prize_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LevelRewards::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 level = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
          set_has_level();
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

void LevelRewards::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
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

::google::protobuf::uint8* LevelRewards::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
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

int LevelRewards::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
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

void LevelRewards::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LevelRewards* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LevelRewards*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LevelRewards::MergeFrom(const LevelRewards& from) {
  GOOGLE_CHECK_NE(&from, this);
  prize_.MergeFrom(from.prize_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LevelRewards::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LevelRewards::CopyFrom(const LevelRewards& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LevelRewards::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  for (int i = 0; i < prize_size(); i++) {
    if (!this->prize(i).IsInitialized()) return false;
  }
  return true;
}

void LevelRewards::Swap(LevelRewards* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    prize_.Swap(&other->prize_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LevelRewards::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LevelRewards_descriptor_;
  metadata.reflection = LevelRewards_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LevelupUnlockCfg::kLevelsFieldNumber;
#endif  // !_MSC_VER

LevelupUnlockCfg::LevelupUnlockCfg()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LevelupUnlockCfg::InitAsDefaultInstance() {
}

LevelupUnlockCfg::LevelupUnlockCfg(const LevelupUnlockCfg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LevelupUnlockCfg::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LevelupUnlockCfg::~LevelupUnlockCfg() {
  SharedDtor();
}

void LevelupUnlockCfg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LevelupUnlockCfg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LevelupUnlockCfg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LevelupUnlockCfg_descriptor_;
}

const LevelupUnlockCfg& LevelupUnlockCfg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_LevelupUnlock_2eproto();  return *default_instance_;
}

LevelupUnlockCfg* LevelupUnlockCfg::default_instance_ = NULL;

LevelupUnlockCfg* LevelupUnlockCfg::New() const {
  return new LevelupUnlockCfg;
}

void LevelupUnlockCfg::Clear() {
  levels_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LevelupUnlockCfg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .LevelupUnlock.LevelRewards levels = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_levels:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_levels()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_levels;
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

void LevelupUnlockCfg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .LevelupUnlock.LevelRewards levels = 1;
  for (int i = 0; i < this->levels_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->levels(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LevelupUnlockCfg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .LevelupUnlock.LevelRewards levels = 1;
  for (int i = 0; i < this->levels_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->levels(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LevelupUnlockCfg::ByteSize() const {
  int total_size = 0;
  
  // repeated .LevelupUnlock.LevelRewards levels = 1;
  total_size += 1 * this->levels_size();
  for (int i = 0; i < this->levels_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->levels(i));
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

void LevelupUnlockCfg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LevelupUnlockCfg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LevelupUnlockCfg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LevelupUnlockCfg::MergeFrom(const LevelupUnlockCfg& from) {
  GOOGLE_CHECK_NE(&from, this);
  levels_.MergeFrom(from.levels_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LevelupUnlockCfg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LevelupUnlockCfg::CopyFrom(const LevelupUnlockCfg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LevelupUnlockCfg::IsInitialized() const {
  
  for (int i = 0; i < levels_size(); i++) {
    if (!this->levels(i).IsInitialized()) return false;
  }
  return true;
}

void LevelupUnlockCfg::Swap(LevelupUnlockCfg* other) {
  if (other != this) {
    levels_.Swap(&other->levels_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LevelupUnlockCfg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LevelupUnlockCfg_descriptor_;
  metadata.reflection = LevelupUnlockCfg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace LevelupUnlock

// @@protoc_insertion_point(global_scope)
