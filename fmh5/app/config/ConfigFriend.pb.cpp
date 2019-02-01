// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigFriend.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ConfigFriend {

namespace {

const ::google::protobuf::Descriptor* LevelNums_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LevelNums_reflection_ = NULL;
const ::google::protobuf::Descriptor* Friend_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Friend_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigFriend_2eproto() {
  protobuf_AddDesc_ConfigFriend_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigFriend.proto");
  GOOGLE_CHECK(file != NULL);
  LevelNums_descriptor_ = file->message_type(0);
  static const int LevelNums_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelNums, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelNums, concern_nums_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelNums, fans_num_),
  };
  LevelNums_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LevelNums_descriptor_,
      LevelNums::default_instance_,
      LevelNums_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelNums, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LevelNums, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LevelNums));
  Friend_descriptor_ = file->message_type(1);
  static const int Friend_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Friend, nums_),
  };
  Friend_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Friend_descriptor_,
      Friend::default_instance_,
      Friend_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Friend, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Friend, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Friend));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigFriend_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LevelNums_descriptor_, &LevelNums::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Friend_descriptor_, &Friend::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigFriend_2eproto() {
  delete LevelNums::default_instance_;
  delete LevelNums_reflection_;
  delete Friend::default_instance_;
  delete Friend_reflection_;
}

void protobuf_AddDesc_ConfigFriend_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022ConfigFriend.proto\022\014ConfigFriend\"B\n\tLe"
    "velNums\022\r\n\005level\030\001 \002(\r\022\024\n\014concern_nums\030\002"
    " \002(\r\022\020\n\010fans_num\030\003 \002(\r\"/\n\006Friend\022%\n\004nums"
    "\030\001 \003(\0132\027.ConfigFriend.LevelNums", 151);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigFriend.proto", &protobuf_RegisterTypes);
  LevelNums::default_instance_ = new LevelNums();
  Friend::default_instance_ = new Friend();
  LevelNums::default_instance_->InitAsDefaultInstance();
  Friend::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigFriend_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigFriend_2eproto {
  StaticDescriptorInitializer_ConfigFriend_2eproto() {
    protobuf_AddDesc_ConfigFriend_2eproto();
  }
} static_descriptor_initializer_ConfigFriend_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int LevelNums::kLevelFieldNumber;
const int LevelNums::kConcernNumsFieldNumber;
const int LevelNums::kFansNumFieldNumber;
#endif  // !_MSC_VER

LevelNums::LevelNums()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LevelNums::InitAsDefaultInstance() {
}

LevelNums::LevelNums(const LevelNums& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LevelNums::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  concern_nums_ = 0u;
  fans_num_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LevelNums::~LevelNums() {
  SharedDtor();
}

void LevelNums::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LevelNums::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LevelNums::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LevelNums_descriptor_;
}

const LevelNums& LevelNums::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigFriend_2eproto();  return *default_instance_;
}

LevelNums* LevelNums::default_instance_ = NULL;

LevelNums* LevelNums::New() const {
  return new LevelNums;
}

void LevelNums::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    level_ = 0u;
    concern_nums_ = 0u;
    fans_num_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LevelNums::MergePartialFromCodedStream(
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
        if (input->ExpectTag(16)) goto parse_concern_nums;
        break;
      }
      
      // required uint32 concern_nums = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_concern_nums:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &concern_nums_)));
          set_has_concern_nums();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_fans_num;
        break;
      }
      
      // required uint32 fans_num = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_fans_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &fans_num_)));
          set_has_fans_num();
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

void LevelNums::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
  }
  
  // required uint32 concern_nums = 2;
  if (has_concern_nums()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->concern_nums(), output);
  }
  
  // required uint32 fans_num = 3;
  if (has_fans_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->fans_num(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LevelNums::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
  }
  
  // required uint32 concern_nums = 2;
  if (has_concern_nums()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->concern_nums(), target);
  }
  
  // required uint32 fans_num = 3;
  if (has_fans_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->fans_num(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LevelNums::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }
    
    // required uint32 concern_nums = 2;
    if (has_concern_nums()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->concern_nums());
    }
    
    // required uint32 fans_num = 3;
    if (has_fans_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->fans_num());
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

void LevelNums::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LevelNums* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LevelNums*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LevelNums::MergeFrom(const LevelNums& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_concern_nums()) {
      set_concern_nums(from.concern_nums());
    }
    if (from.has_fans_num()) {
      set_fans_num(from.fans_num());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LevelNums::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LevelNums::CopyFrom(const LevelNums& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LevelNums::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  return true;
}

void LevelNums::Swap(LevelNums* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    std::swap(concern_nums_, other->concern_nums_);
    std::swap(fans_num_, other->fans_num_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LevelNums::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LevelNums_descriptor_;
  metadata.reflection = LevelNums_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Friend::kNumsFieldNumber;
#endif  // !_MSC_VER

Friend::Friend()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Friend::InitAsDefaultInstance() {
}

Friend::Friend(const Friend& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Friend::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Friend::~Friend() {
  SharedDtor();
}

void Friend::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Friend::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Friend::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Friend_descriptor_;
}

const Friend& Friend::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigFriend_2eproto();  return *default_instance_;
}

Friend* Friend::default_instance_ = NULL;

Friend* Friend::New() const {
  return new Friend;
}

void Friend::Clear() {
  nums_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Friend::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ConfigFriend.LevelNums nums = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_nums:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_nums()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_nums;
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

void Friend::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ConfigFriend.LevelNums nums = 1;
  for (int i = 0; i < this->nums_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->nums(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Friend::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ConfigFriend.LevelNums nums = 1;
  for (int i = 0; i < this->nums_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->nums(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Friend::ByteSize() const {
  int total_size = 0;
  
  // repeated .ConfigFriend.LevelNums nums = 1;
  total_size += 1 * this->nums_size();
  for (int i = 0; i < this->nums_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->nums(i));
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

void Friend::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Friend* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Friend*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Friend::MergeFrom(const Friend& from) {
  GOOGLE_CHECK_NE(&from, this);
  nums_.MergeFrom(from.nums_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Friend::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Friend::CopyFrom(const Friend& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Friend::IsInitialized() const {
  
  for (int i = 0; i < nums_size(); i++) {
    if (!this->nums(i).IsInitialized()) return false;
  }
  return true;
}

void Friend::Swap(Friend* other) {
  if (other != this) {
    nums_.Swap(&other->nums_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Friend::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Friend_descriptor_;
  metadata.reflection = Friend_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigFriend

// @@protoc_insertion_point(global_scope)