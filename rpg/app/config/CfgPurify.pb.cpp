// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgPurify.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CfgPurify.pb.h"

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

namespace CfgPurify {

namespace {

const ::google::protobuf::Descriptor* Purify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Purify_reflection_ = NULL;
const ::google::protobuf::Descriptor* Purifys_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Purifys_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CfgPurify_2eproto() {
  protobuf_AddDesc_CfgPurify_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CfgPurify.proto");
  GOOGLE_CHECK(file != NULL);
  Purify_descriptor_ = file->message_type(0);
  static const int Purify_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purify, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purify, useprops_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purify, attr_),
  };
  Purify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Purify_descriptor_,
      Purify::default_instance_,
      Purify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Purify));
  Purifys_descriptor_ = file->message_type(1);
  static const int Purifys_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purifys, purifys_),
  };
  Purifys_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Purifys_descriptor_,
      Purifys::default_instance_,
      Purifys_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purifys, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Purifys, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Purifys));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CfgPurify_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Purify_descriptor_, &Purify::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Purifys_descriptor_, &Purifys::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CfgPurify_2eproto() {
  delete Purify::default_instance_;
  delete Purify_reflection_;
  delete Purifys::default_instance_;
  delete Purifys_reflection_;
}

void protobuf_AddDesc_CfgPurify_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CfgCommon::protobuf_AddDesc_CfgCommon_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017CfgPurify.proto\022\tCfgPurify\032\017CfgCommon."
    "proto\"`\n\006Purify\022\r\n\005level\030\001 \002(\r\022#\n\010usePro"
    "ps\030\002 \003(\0132\021.CfgCommon.Reward\022\"\n\004attr\030\003 \003("
    "\0132\024.CfgCommon.Attribute\"-\n\007Purifys\022\"\n\007pu"
    "rifys\030\001 \003(\0132\021.CfgPurify.Purify", 190);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CfgPurify.proto", &protobuf_RegisterTypes);
  Purify::default_instance_ = new Purify();
  Purifys::default_instance_ = new Purifys();
  Purify::default_instance_->InitAsDefaultInstance();
  Purifys::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CfgPurify_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CfgPurify_2eproto {
  StaticDescriptorInitializer_CfgPurify_2eproto() {
    protobuf_AddDesc_CfgPurify_2eproto();
  }
} static_descriptor_initializer_CfgPurify_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Purify::kLevelFieldNumber;
const int Purify::kUsePropsFieldNumber;
const int Purify::kAttrFieldNumber;
#endif  // !_MSC_VER

Purify::Purify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgPurify.Purify)
}

void Purify::InitAsDefaultInstance() {
}

Purify::Purify(const Purify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgPurify.Purify)
}

void Purify::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Purify::~Purify() {
  // @@protoc_insertion_point(destructor:CfgPurify.Purify)
  SharedDtor();
}

void Purify::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Purify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Purify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Purify_descriptor_;
}

const Purify& Purify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgPurify_2eproto();
  return *default_instance_;
}

Purify* Purify::default_instance_ = NULL;

Purify* Purify::New() const {
  return new Purify;
}

void Purify::Clear() {
  level_ = 0u;
  useprops_.Clear();
  attr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Purify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgPurify.Purify)
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
        if (input->ExpectTag(18)) goto parse_useProps;
        break;
      }

      // repeated .CfgCommon.Reward useProps = 2;
      case 2: {
        if (tag == 18) {
         parse_useProps:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_useprops()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_useProps;
        if (input->ExpectTag(26)) goto parse_attr;
        break;
      }

      // repeated .CfgCommon.Attribute attr = 3;
      case 3: {
        if (tag == 26) {
         parse_attr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_attr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_attr;
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
  // @@protoc_insertion_point(parse_success:CfgPurify.Purify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgPurify.Purify)
  return false;
#undef DO_
}

void Purify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgPurify.Purify)
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
  }

  // repeated .CfgCommon.Reward useProps = 2;
  for (int i = 0; i < this->useprops_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->useprops(i), output);
  }

  // repeated .CfgCommon.Attribute attr = 3;
  for (int i = 0; i < this->attr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->attr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgPurify.Purify)
}

::google::protobuf::uint8* Purify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgPurify.Purify)
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
  }

  // repeated .CfgCommon.Reward useProps = 2;
  for (int i = 0; i < this->useprops_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->useprops(i), target);
  }

  // repeated .CfgCommon.Attribute attr = 3;
  for (int i = 0; i < this->attr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->attr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgPurify.Purify)
  return target;
}

int Purify::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

  }
  // repeated .CfgCommon.Reward useProps = 2;
  total_size += 1 * this->useprops_size();
  for (int i = 0; i < this->useprops_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->useprops(i));
  }

  // repeated .CfgCommon.Attribute attr = 3;
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

void Purify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Purify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Purify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Purify::MergeFrom(const Purify& from) {
  GOOGLE_CHECK_NE(&from, this);
  useprops_.MergeFrom(from.useprops_);
  attr_.MergeFrom(from.attr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Purify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Purify::CopyFrom(const Purify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Purify::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->useprops())) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->attr())) return false;
  return true;
}

void Purify::Swap(Purify* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    useprops_.Swap(&other->useprops_);
    attr_.Swap(&other->attr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Purify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Purify_descriptor_;
  metadata.reflection = Purify_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Purifys::kPurifysFieldNumber;
#endif  // !_MSC_VER

Purifys::Purifys()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgPurify.Purifys)
}

void Purifys::InitAsDefaultInstance() {
}

Purifys::Purifys(const Purifys& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgPurify.Purifys)
}

void Purifys::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Purifys::~Purifys() {
  // @@protoc_insertion_point(destructor:CfgPurify.Purifys)
  SharedDtor();
}

void Purifys::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Purifys::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Purifys::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Purifys_descriptor_;
}

const Purifys& Purifys::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgPurify_2eproto();
  return *default_instance_;
}

Purifys* Purifys::default_instance_ = NULL;

Purifys* Purifys::New() const {
  return new Purifys;
}

void Purifys::Clear() {
  purifys_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Purifys::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgPurify.Purifys)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CfgPurify.Purify purifys = 1;
      case 1: {
        if (tag == 10) {
         parse_purifys:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_purifys()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_purifys;
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
  // @@protoc_insertion_point(parse_success:CfgPurify.Purifys)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgPurify.Purifys)
  return false;
#undef DO_
}

void Purifys::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgPurify.Purifys)
  // repeated .CfgPurify.Purify purifys = 1;
  for (int i = 0; i < this->purifys_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->purifys(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgPurify.Purifys)
}

::google::protobuf::uint8* Purifys::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgPurify.Purifys)
  // repeated .CfgPurify.Purify purifys = 1;
  for (int i = 0; i < this->purifys_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->purifys(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgPurify.Purifys)
  return target;
}

int Purifys::ByteSize() const {
  int total_size = 0;

  // repeated .CfgPurify.Purify purifys = 1;
  total_size += 1 * this->purifys_size();
  for (int i = 0; i < this->purifys_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->purifys(i));
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

void Purifys::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Purifys* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Purifys*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Purifys::MergeFrom(const Purifys& from) {
  GOOGLE_CHECK_NE(&from, this);
  purifys_.MergeFrom(from.purifys_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Purifys::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Purifys::CopyFrom(const Purifys& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Purifys::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->purifys())) return false;
  return true;
}

void Purifys::Swap(Purifys* other) {
  if (other != this) {
    purifys_.Swap(&other->purifys_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Purifys::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Purifys_descriptor_;
  metadata.reflection = Purifys_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgPurify

// @@protoc_insertion_point(global_scope)