// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgReinCarn.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CfgReinCarn.pb.h"

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

namespace CfgReinCarn {

namespace {

const ::google::protobuf::Descriptor* ReinCarn_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReinCarn_reflection_ = NULL;
const ::google::protobuf::Descriptor* ReinCarns_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReinCarns_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CfgReinCarn_2eproto() {
  protobuf_AddDesc_CfgReinCarn_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CfgReinCarn.proto");
  GOOGLE_CHECK(file != NULL);
  ReinCarn_descriptor_ = file->message_type(0);
  static const int ReinCarn_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, value_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, skillid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, attr_),
  };
  ReinCarn_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReinCarn_descriptor_,
      ReinCarn::default_instance_,
      ReinCarn_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarn, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReinCarn));
  ReinCarns_descriptor_ = file->message_type(1);
  static const int ReinCarns_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarns, reincarn_),
  };
  ReinCarns_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReinCarns_descriptor_,
      ReinCarns::default_instance_,
      ReinCarns_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarns, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReinCarns, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReinCarns));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CfgReinCarn_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReinCarn_descriptor_, &ReinCarn::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReinCarns_descriptor_, &ReinCarns::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CfgReinCarn_2eproto() {
  delete ReinCarn::default_instance_;
  delete ReinCarn_reflection_;
  delete ReinCarns::default_instance_;
  delete ReinCarns_reflection_;
}

void protobuf_AddDesc_CfgReinCarn_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CfgCommon::protobuf_AddDesc_CfgCommon_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021CfgReinCarn.proto\022\013CfgReinCarn\032\017CfgCom"
    "mon.proto\"]\n\010ReinCarn\022\r\n\005level\030\001 \002(\r\022\r\n\005"
    "value\030\002 \002(\r\022\017\n\007skillId\030\003 \002(\r\022\"\n\004attr\030\004 \003"
    "(\0132\024.CfgCommon.Attribute\"4\n\tReinCarns\022\'\n"
    "\010reincarn\030\001 \003(\0132\025.CfgReinCarn.ReinCarn", 198);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CfgReinCarn.proto", &protobuf_RegisterTypes);
  ReinCarn::default_instance_ = new ReinCarn();
  ReinCarns::default_instance_ = new ReinCarns();
  ReinCarn::default_instance_->InitAsDefaultInstance();
  ReinCarns::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CfgReinCarn_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CfgReinCarn_2eproto {
  StaticDescriptorInitializer_CfgReinCarn_2eproto() {
    protobuf_AddDesc_CfgReinCarn_2eproto();
  }
} static_descriptor_initializer_CfgReinCarn_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ReinCarn::kLevelFieldNumber;
const int ReinCarn::kValueFieldNumber;
const int ReinCarn::kSkillIdFieldNumber;
const int ReinCarn::kAttrFieldNumber;
#endif  // !_MSC_VER

ReinCarn::ReinCarn()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgReinCarn.ReinCarn)
}

void ReinCarn::InitAsDefaultInstance() {
}

ReinCarn::ReinCarn(const ReinCarn& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgReinCarn.ReinCarn)
}

void ReinCarn::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  value_ = 0u;
  skillid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReinCarn::~ReinCarn() {
  // @@protoc_insertion_point(destructor:CfgReinCarn.ReinCarn)
  SharedDtor();
}

void ReinCarn::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ReinCarn::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReinCarn::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReinCarn_descriptor_;
}

const ReinCarn& ReinCarn::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgReinCarn_2eproto();
  return *default_instance_;
}

ReinCarn* ReinCarn::default_instance_ = NULL;

ReinCarn* ReinCarn::New() const {
  return new ReinCarn;
}

void ReinCarn::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ReinCarn*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(level_, value_);
    skillid_ = 0u;
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  attr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReinCarn::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgReinCarn.ReinCarn)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 level = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
          set_has_level();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_value;
        break;
      }

      // required uint32 value = 2;
      case 2: {
        if (tag == 16) {
         parse_value:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &value_)));
          set_has_value();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_skillId;
        break;
      }

      // required uint32 skillId = 3;
      case 3: {
        if (tag == 24) {
         parse_skillId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &skillid_)));
          set_has_skillid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_attr;
        break;
      }

      // repeated .CfgCommon.Attribute attr = 4;
      case 4: {
        if (tag == 34) {
         parse_attr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_attr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_attr;
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
  // @@protoc_insertion_point(parse_success:CfgReinCarn.ReinCarn)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgReinCarn.ReinCarn)
  return false;
#undef DO_
}

void ReinCarn::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgReinCarn.ReinCarn)
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
  }

  // required uint32 value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->value(), output);
  }

  // required uint32 skillId = 3;
  if (has_skillid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->skillid(), output);
  }

  // repeated .CfgCommon.Attribute attr = 4;
  for (int i = 0; i < this->attr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->attr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgReinCarn.ReinCarn)
}

::google::protobuf::uint8* ReinCarn::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgReinCarn.ReinCarn)
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
  }

  // required uint32 value = 2;
  if (has_value()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->value(), target);
  }

  // required uint32 skillId = 3;
  if (has_skillid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->skillid(), target);
  }

  // repeated .CfgCommon.Attribute attr = 4;
  for (int i = 0; i < this->attr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->attr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgReinCarn.ReinCarn)
  return target;
}

int ReinCarn::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

    // required uint32 value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->value());
    }

    // required uint32 skillId = 3;
    if (has_skillid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->skillid());
    }

  }
  // repeated .CfgCommon.Attribute attr = 4;
  total_size += 1 * this->attr_size();
  for (int i = 0; i < this->attr_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->attr(i));
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

void ReinCarn::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReinCarn* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReinCarn*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReinCarn::MergeFrom(const ReinCarn& from) {
  GOOGLE_CHECK_NE(&from, this);
  attr_.MergeFrom(from.attr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
    if (from.has_skillid()) {
      set_skillid(from.skillid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReinCarn::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReinCarn::CopyFrom(const ReinCarn& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReinCarn::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->attr())) return false;
  return true;
}

void ReinCarn::Swap(ReinCarn* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    std::swap(value_, other->value_);
    std::swap(skillid_, other->skillid_);
    attr_.Swap(&other->attr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReinCarn::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReinCarn_descriptor_;
  metadata.reflection = ReinCarn_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ReinCarns::kReincarnFieldNumber;
#endif  // !_MSC_VER

ReinCarns::ReinCarns()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgReinCarn.ReinCarns)
}

void ReinCarns::InitAsDefaultInstance() {
}

ReinCarns::ReinCarns(const ReinCarns& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgReinCarn.ReinCarns)
}

void ReinCarns::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReinCarns::~ReinCarns() {
  // @@protoc_insertion_point(destructor:CfgReinCarn.ReinCarns)
  SharedDtor();
}

void ReinCarns::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ReinCarns::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReinCarns::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReinCarns_descriptor_;
}

const ReinCarns& ReinCarns::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgReinCarn_2eproto();
  return *default_instance_;
}

ReinCarns* ReinCarns::default_instance_ = NULL;

ReinCarns* ReinCarns::New() const {
  return new ReinCarns;
}

void ReinCarns::Clear() {
  reincarn_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReinCarns::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgReinCarn.ReinCarns)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CfgReinCarn.ReinCarn reincarn = 1;
      case 1: {
        if (tag == 10) {
         parse_reincarn:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_reincarn()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_reincarn;
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
  // @@protoc_insertion_point(parse_success:CfgReinCarn.ReinCarns)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgReinCarn.ReinCarns)
  return false;
#undef DO_
}

void ReinCarns::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgReinCarn.ReinCarns)
  // repeated .CfgReinCarn.ReinCarn reincarn = 1;
  for (int i = 0; i < this->reincarn_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->reincarn(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgReinCarn.ReinCarns)
}

::google::protobuf::uint8* ReinCarns::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgReinCarn.ReinCarns)
  // repeated .CfgReinCarn.ReinCarn reincarn = 1;
  for (int i = 0; i < this->reincarn_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->reincarn(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgReinCarn.ReinCarns)
  return target;
}

int ReinCarns::ByteSize() const {
  int total_size = 0;

  // repeated .CfgReinCarn.ReinCarn reincarn = 1;
  total_size += 1 * this->reincarn_size();
  for (int i = 0; i < this->reincarn_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->reincarn(i));
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

void ReinCarns::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReinCarns* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReinCarns*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReinCarns::MergeFrom(const ReinCarns& from) {
  GOOGLE_CHECK_NE(&from, this);
  reincarn_.MergeFrom(from.reincarn_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReinCarns::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReinCarns::CopyFrom(const ReinCarns& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReinCarns::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->reincarn())) return false;
  return true;
}

void ReinCarns::Swap(ReinCarns* other) {
  if (other != this) {
    reincarn_.Swap(&other->reincarn_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReinCarns::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReinCarns_descriptor_;
  metadata.reflection = ReinCarns_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgReinCarn

// @@protoc_insertion_point(global_scope)