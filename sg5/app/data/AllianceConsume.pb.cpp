// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AllianceConsume.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "AllianceConsume.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace AllianceConsume {

namespace {

const ::google::protobuf::Descriptor* AllianceConsumeUser_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AllianceConsumeUser_reflection_ = NULL;
const ::google::protobuf::Descriptor* AllianceConsumeAlliance_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AllianceConsumeAlliance_reflection_ = NULL;
const ::google::protobuf::Descriptor* AllianceConsume_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AllianceConsume_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_AllianceConsume_2eproto() {
  protobuf_AddDesc_AllianceConsume_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "AllianceConsume.proto");
  GOOGLE_CHECK(file != NULL);
  AllianceConsumeUser_descriptor_ = file->message_type(0);
  static const int AllianceConsumeUser_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeUser, uid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeUser, consume_),
  };
  AllianceConsumeUser_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AllianceConsumeUser_descriptor_,
      AllianceConsumeUser::default_instance_,
      AllianceConsumeUser_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeUser, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeUser, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AllianceConsumeUser));
  AllianceConsumeAlliance_descriptor_ = file->message_type(1);
  static const int AllianceConsumeAlliance_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeAlliance, aid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeAlliance, user_),
  };
  AllianceConsumeAlliance_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AllianceConsumeAlliance_descriptor_,
      AllianceConsumeAlliance::default_instance_,
      AllianceConsumeAlliance_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeAlliance, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsumeAlliance, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AllianceConsumeAlliance));
  AllianceConsume_descriptor_ = file->message_type(2);
  static const int AllianceConsume_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsume, ver_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsume, alliance_),
  };
  AllianceConsume_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AllianceConsume_descriptor_,
      AllianceConsume::default_instance_,
      AllianceConsume_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsume, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllianceConsume, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AllianceConsume));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_AllianceConsume_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AllianceConsumeUser_descriptor_, &AllianceConsumeUser::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AllianceConsumeAlliance_descriptor_, &AllianceConsumeAlliance::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AllianceConsume_descriptor_, &AllianceConsume::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_AllianceConsume_2eproto() {
  delete AllianceConsumeUser::default_instance_;
  delete AllianceConsumeUser_reflection_;
  delete AllianceConsumeAlliance::default_instance_;
  delete AllianceConsumeAlliance_reflection_;
  delete AllianceConsume::default_instance_;
  delete AllianceConsume_reflection_;
}

void protobuf_AddDesc_AllianceConsume_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025AllianceConsume.proto\022\017AllianceConsume"
    "\"3\n\023AllianceConsumeUser\022\013\n\003uid\030\001 \002(\r\022\017\n\007"
    "consume\030\002 \002(\r\"Z\n\027AllianceConsumeAlliance"
    "\022\013\n\003aid\030\001 \002(\r\0222\n\004user\030\002 \003(\0132$.AllianceCo"
    "nsume.AllianceConsumeUser\"Z\n\017AllianceCon"
    "sume\022\013\n\003ver\030\001 \002(\r\022:\n\010alliance\030\002 \003(\0132(.Al"
    "lianceConsume.AllianceConsumeAlliance", 277);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "AllianceConsume.proto", &protobuf_RegisterTypes);
  AllianceConsumeUser::default_instance_ = new AllianceConsumeUser();
  AllianceConsumeAlliance::default_instance_ = new AllianceConsumeAlliance();
  AllianceConsume::default_instance_ = new AllianceConsume();
  AllianceConsumeUser::default_instance_->InitAsDefaultInstance();
  AllianceConsumeAlliance::default_instance_->InitAsDefaultInstance();
  AllianceConsume::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_AllianceConsume_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_AllianceConsume_2eproto {
  StaticDescriptorInitializer_AllianceConsume_2eproto() {
    protobuf_AddDesc_AllianceConsume_2eproto();
  }
} static_descriptor_initializer_AllianceConsume_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int AllianceConsumeUser::kUidFieldNumber;
const int AllianceConsumeUser::kConsumeFieldNumber;
#endif  // !_MSC_VER

AllianceConsumeUser::AllianceConsumeUser()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AllianceConsume.AllianceConsumeUser)
}

void AllianceConsumeUser::InitAsDefaultInstance() {
}

AllianceConsumeUser::AllianceConsumeUser(const AllianceConsumeUser& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AllianceConsume.AllianceConsumeUser)
}

void AllianceConsumeUser::SharedCtor() {
  _cached_size_ = 0;
  uid_ = 0u;
  consume_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AllianceConsumeUser::~AllianceConsumeUser() {
  // @@protoc_insertion_point(destructor:AllianceConsume.AllianceConsumeUser)
  SharedDtor();
}

void AllianceConsumeUser::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AllianceConsumeUser::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AllianceConsumeUser::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AllianceConsumeUser_descriptor_;
}

const AllianceConsumeUser& AllianceConsumeUser::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_AllianceConsume_2eproto();
  return *default_instance_;
}

AllianceConsumeUser* AllianceConsumeUser::default_instance_ = NULL;

AllianceConsumeUser* AllianceConsumeUser::New() const {
  return new AllianceConsumeUser;
}

void AllianceConsumeUser::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<AllianceConsumeUser*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(uid_, consume_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AllianceConsumeUser::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AllianceConsume.AllianceConsumeUser)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 uid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &uid_)));
          set_has_uid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_consume;
        break;
      }

      // required uint32 consume = 2;
      case 2: {
        if (tag == 16) {
         parse_consume:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &consume_)));
          set_has_consume();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AllianceConsume.AllianceConsumeUser)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AllianceConsume.AllianceConsumeUser)
  return false;
#undef DO_
}

void AllianceConsumeUser::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AllianceConsume.AllianceConsumeUser)
  // required uint32 uid = 1;
  if (has_uid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->uid(), output);
  }

  // required uint32 consume = 2;
  if (has_consume()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->consume(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AllianceConsume.AllianceConsumeUser)
}

::google::protobuf::uint8* AllianceConsumeUser::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AllianceConsume.AllianceConsumeUser)
  // required uint32 uid = 1;
  if (has_uid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->uid(), target);
  }

  // required uint32 consume = 2;
  if (has_consume()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->consume(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AllianceConsume.AllianceConsumeUser)
  return target;
}

int AllianceConsumeUser::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 uid = 1;
    if (has_uid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->uid());
    }

    // required uint32 consume = 2;
    if (has_consume()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->consume());
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

void AllianceConsumeUser::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AllianceConsumeUser* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AllianceConsumeUser*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AllianceConsumeUser::MergeFrom(const AllianceConsumeUser& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uid()) {
      set_uid(from.uid());
    }
    if (from.has_consume()) {
      set_consume(from.consume());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AllianceConsumeUser::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AllianceConsumeUser::CopyFrom(const AllianceConsumeUser& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AllianceConsumeUser::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void AllianceConsumeUser::Swap(AllianceConsumeUser* other) {
  if (other != this) {
    std::swap(uid_, other->uid_);
    std::swap(consume_, other->consume_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AllianceConsumeUser::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AllianceConsumeUser_descriptor_;
  metadata.reflection = AllianceConsumeUser_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AllianceConsumeAlliance::kAidFieldNumber;
const int AllianceConsumeAlliance::kUserFieldNumber;
#endif  // !_MSC_VER

AllianceConsumeAlliance::AllianceConsumeAlliance()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AllianceConsume.AllianceConsumeAlliance)
}

void AllianceConsumeAlliance::InitAsDefaultInstance() {
}

AllianceConsumeAlliance::AllianceConsumeAlliance(const AllianceConsumeAlliance& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AllianceConsume.AllianceConsumeAlliance)
}

void AllianceConsumeAlliance::SharedCtor() {
  _cached_size_ = 0;
  aid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AllianceConsumeAlliance::~AllianceConsumeAlliance() {
  // @@protoc_insertion_point(destructor:AllianceConsume.AllianceConsumeAlliance)
  SharedDtor();
}

void AllianceConsumeAlliance::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AllianceConsumeAlliance::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AllianceConsumeAlliance::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AllianceConsumeAlliance_descriptor_;
}

const AllianceConsumeAlliance& AllianceConsumeAlliance::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_AllianceConsume_2eproto();
  return *default_instance_;
}

AllianceConsumeAlliance* AllianceConsumeAlliance::default_instance_ = NULL;

AllianceConsumeAlliance* AllianceConsumeAlliance::New() const {
  return new AllianceConsumeAlliance;
}

void AllianceConsumeAlliance::Clear() {
  aid_ = 0u;
  user_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AllianceConsumeAlliance::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AllianceConsume.AllianceConsumeAlliance)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 aid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &aid_)));
          set_has_aid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_user;
        break;
      }

      // repeated .AllianceConsume.AllianceConsumeUser user = 2;
      case 2: {
        if (tag == 18) {
         parse_user:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_user()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_user;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AllianceConsume.AllianceConsumeAlliance)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AllianceConsume.AllianceConsumeAlliance)
  return false;
#undef DO_
}

void AllianceConsumeAlliance::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AllianceConsume.AllianceConsumeAlliance)
  // required uint32 aid = 1;
  if (has_aid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->aid(), output);
  }

  // repeated .AllianceConsume.AllianceConsumeUser user = 2;
  for (int i = 0; i < this->user_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->user(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AllianceConsume.AllianceConsumeAlliance)
}

::google::protobuf::uint8* AllianceConsumeAlliance::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AllianceConsume.AllianceConsumeAlliance)
  // required uint32 aid = 1;
  if (has_aid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->aid(), target);
  }

  // repeated .AllianceConsume.AllianceConsumeUser user = 2;
  for (int i = 0; i < this->user_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->user(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AllianceConsume.AllianceConsumeAlliance)
  return target;
}

int AllianceConsumeAlliance::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 aid = 1;
    if (has_aid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->aid());
    }

  }
  // repeated .AllianceConsume.AllianceConsumeUser user = 2;
  total_size += 1 * this->user_size();
  for (int i = 0; i < this->user_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->user(i));
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

void AllianceConsumeAlliance::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AllianceConsumeAlliance* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AllianceConsumeAlliance*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AllianceConsumeAlliance::MergeFrom(const AllianceConsumeAlliance& from) {
  GOOGLE_CHECK_NE(&from, this);
  user_.MergeFrom(from.user_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_aid()) {
      set_aid(from.aid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AllianceConsumeAlliance::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AllianceConsumeAlliance::CopyFrom(const AllianceConsumeAlliance& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AllianceConsumeAlliance::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->user())) return false;
  return true;
}

void AllianceConsumeAlliance::Swap(AllianceConsumeAlliance* other) {
  if (other != this) {
    std::swap(aid_, other->aid_);
    user_.Swap(&other->user_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AllianceConsumeAlliance::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AllianceConsumeAlliance_descriptor_;
  metadata.reflection = AllianceConsumeAlliance_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AllianceConsume::kVerFieldNumber;
const int AllianceConsume::kAllianceFieldNumber;
#endif  // !_MSC_VER

AllianceConsume::AllianceConsume()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AllianceConsume.AllianceConsume)
}

void AllianceConsume::InitAsDefaultInstance() {
}

AllianceConsume::AllianceConsume(const AllianceConsume& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AllianceConsume.AllianceConsume)
}

void AllianceConsume::SharedCtor() {
  _cached_size_ = 0;
  ver_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AllianceConsume::~AllianceConsume() {
  // @@protoc_insertion_point(destructor:AllianceConsume.AllianceConsume)
  SharedDtor();
}

void AllianceConsume::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AllianceConsume::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AllianceConsume::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AllianceConsume_descriptor_;
}

const AllianceConsume& AllianceConsume::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_AllianceConsume_2eproto();
  return *default_instance_;
}

AllianceConsume* AllianceConsume::default_instance_ = NULL;

AllianceConsume* AllianceConsume::New() const {
  return new AllianceConsume;
}

void AllianceConsume::Clear() {
  ver_ = 0u;
  alliance_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AllianceConsume::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AllianceConsume.AllianceConsume)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 ver = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ver_)));
          set_has_ver();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_alliance;
        break;
      }

      // repeated .AllianceConsume.AllianceConsumeAlliance alliance = 2;
      case 2: {
        if (tag == 18) {
         parse_alliance:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_alliance()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_alliance;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AllianceConsume.AllianceConsume)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AllianceConsume.AllianceConsume)
  return false;
#undef DO_
}

void AllianceConsume::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AllianceConsume.AllianceConsume)
  // required uint32 ver = 1;
  if (has_ver()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->ver(), output);
  }

  // repeated .AllianceConsume.AllianceConsumeAlliance alliance = 2;
  for (int i = 0; i < this->alliance_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->alliance(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AllianceConsume.AllianceConsume)
}

::google::protobuf::uint8* AllianceConsume::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AllianceConsume.AllianceConsume)
  // required uint32 ver = 1;
  if (has_ver()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->ver(), target);
  }

  // repeated .AllianceConsume.AllianceConsumeAlliance alliance = 2;
  for (int i = 0; i < this->alliance_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->alliance(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AllianceConsume.AllianceConsume)
  return target;
}

int AllianceConsume::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 ver = 1;
    if (has_ver()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ver());
    }

  }
  // repeated .AllianceConsume.AllianceConsumeAlliance alliance = 2;
  total_size += 1 * this->alliance_size();
  for (int i = 0; i < this->alliance_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->alliance(i));
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

void AllianceConsume::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AllianceConsume* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AllianceConsume*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AllianceConsume::MergeFrom(const AllianceConsume& from) {
  GOOGLE_CHECK_NE(&from, this);
  alliance_.MergeFrom(from.alliance_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ver()) {
      set_ver(from.ver());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AllianceConsume::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AllianceConsume::CopyFrom(const AllianceConsume& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AllianceConsume::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->alliance())) return false;
  return true;
}

void AllianceConsume::Swap(AllianceConsume* other) {
  if (other != this) {
    std::swap(ver_, other->ver_);
    alliance_.Swap(&other->alliance_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AllianceConsume::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AllianceConsume_descriptor_;
  metadata.reflection = AllianceConsume_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AllianceConsume

// @@protoc_insertion_point(global_scope)
