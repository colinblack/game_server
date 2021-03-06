// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgRing.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CfgRing.pb.h"

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

namespace CfgRing {

namespace {

const ::google::protobuf::Descriptor* Ring_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Ring_reflection_ = NULL;
const ::google::protobuf::Descriptor* Rings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Rings_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CfgRing_2eproto() {
  protobuf_AddDesc_CfgRing_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CfgRing.proto");
  GOOGLE_CHECK(file != NULL);
  Ring_descriptor_ = file->message_type(0);
  static const int Ring_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Ring, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Ring, exp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Ring, attr_),
  };
  Ring_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Ring_descriptor_,
      Ring::default_instance_,
      Ring_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Ring, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Ring, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Ring));
  Rings_descriptor_ = file->message_type(1);
  static const int Rings_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rings, ring_),
  };
  Rings_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Rings_descriptor_,
      Rings::default_instance_,
      Rings_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rings, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rings, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Rings));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CfgRing_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Ring_descriptor_, &Ring::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Rings_descriptor_, &Rings::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CfgRing_2eproto() {
  delete Ring::default_instance_;
  delete Ring_reflection_;
  delete Rings::default_instance_;
  delete Rings_reflection_;
}

void protobuf_AddDesc_CfgRing_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CfgCommon::protobuf_AddDesc_CfgCommon_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rCfgRing.proto\022\007CfgRing\032\017CfgCommon.prot"
    "o\"F\n\004Ring\022\r\n\005level\030\001 \002(\r\022\013\n\003exp\030\002 \002(\r\022\"\n"
    "\004attr\030\003 \003(\0132\024.CfgCommon.Attribute\"$\n\005Rin"
    "gs\022\033\n\004ring\030\001 \003(\0132\r.CfgRing.Ring", 151);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CfgRing.proto", &protobuf_RegisterTypes);
  Ring::default_instance_ = new Ring();
  Rings::default_instance_ = new Rings();
  Ring::default_instance_->InitAsDefaultInstance();
  Rings::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CfgRing_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CfgRing_2eproto {
  StaticDescriptorInitializer_CfgRing_2eproto() {
    protobuf_AddDesc_CfgRing_2eproto();
  }
} static_descriptor_initializer_CfgRing_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Ring::kLevelFieldNumber;
const int Ring::kExpFieldNumber;
const int Ring::kAttrFieldNumber;
#endif  // !_MSC_VER

Ring::Ring()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgRing.Ring)
}

void Ring::InitAsDefaultInstance() {
}

Ring::Ring(const Ring& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgRing.Ring)
}

void Ring::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  exp_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Ring::~Ring() {
  // @@protoc_insertion_point(destructor:CfgRing.Ring)
  SharedDtor();
}

void Ring::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Ring::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Ring::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Ring_descriptor_;
}

const Ring& Ring::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgRing_2eproto();
  return *default_instance_;
}

Ring* Ring::default_instance_ = NULL;

Ring* Ring::New() const {
  return new Ring;
}

void Ring::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Ring*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(level_, exp_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  attr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Ring::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgRing.Ring)
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
        if (input->ExpectTag(16)) goto parse_exp;
        break;
      }

      // required uint32 exp = 2;
      case 2: {
        if (tag == 16) {
         parse_exp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &exp_)));
          set_has_exp();
        } else {
          goto handle_unusual;
        }
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
  // @@protoc_insertion_point(parse_success:CfgRing.Ring)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgRing.Ring)
  return false;
#undef DO_
}

void Ring::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgRing.Ring)
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
  }

  // required uint32 exp = 2;
  if (has_exp()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->exp(), output);
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
  // @@protoc_insertion_point(serialize_end:CfgRing.Ring)
}

::google::protobuf::uint8* Ring::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgRing.Ring)
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
  }

  // required uint32 exp = 2;
  if (has_exp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->exp(), target);
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
  // @@protoc_insertion_point(serialize_to_array_end:CfgRing.Ring)
  return target;
}

int Ring::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

    // required uint32 exp = 2;
    if (has_exp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->exp());
    }

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

void Ring::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Ring* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Ring*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Ring::MergeFrom(const Ring& from) {
  GOOGLE_CHECK_NE(&from, this);
  attr_.MergeFrom(from.attr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_exp()) {
      set_exp(from.exp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Ring::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Ring::CopyFrom(const Ring& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Ring::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->attr())) return false;
  return true;
}

void Ring::Swap(Ring* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    std::swap(exp_, other->exp_);
    attr_.Swap(&other->attr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Ring::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Ring_descriptor_;
  metadata.reflection = Ring_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Rings::kRingFieldNumber;
#endif  // !_MSC_VER

Rings::Rings()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgRing.Rings)
}

void Rings::InitAsDefaultInstance() {
}

Rings::Rings(const Rings& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgRing.Rings)
}

void Rings::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Rings::~Rings() {
  // @@protoc_insertion_point(destructor:CfgRing.Rings)
  SharedDtor();
}

void Rings::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Rings::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Rings::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Rings_descriptor_;
}

const Rings& Rings::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgRing_2eproto();
  return *default_instance_;
}

Rings* Rings::default_instance_ = NULL;

Rings* Rings::New() const {
  return new Rings;
}

void Rings::Clear() {
  ring_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Rings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgRing.Rings)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CfgRing.Ring ring = 1;
      case 1: {
        if (tag == 10) {
         parse_ring:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_ring()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ring;
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
  // @@protoc_insertion_point(parse_success:CfgRing.Rings)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgRing.Rings)
  return false;
#undef DO_
}

void Rings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgRing.Rings)
  // repeated .CfgRing.Ring ring = 1;
  for (int i = 0; i < this->ring_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->ring(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgRing.Rings)
}

::google::protobuf::uint8* Rings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgRing.Rings)
  // repeated .CfgRing.Ring ring = 1;
  for (int i = 0; i < this->ring_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->ring(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgRing.Rings)
  return target;
}

int Rings::ByteSize() const {
  int total_size = 0;

  // repeated .CfgRing.Ring ring = 1;
  total_size += 1 * this->ring_size();
  for (int i = 0; i < this->ring_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->ring(i));
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

void Rings::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Rings* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Rings*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Rings::MergeFrom(const Rings& from) {
  GOOGLE_CHECK_NE(&from, this);
  ring_.MergeFrom(from.ring_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Rings::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Rings::CopyFrom(const Rings& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Rings::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->ring())) return false;
  return true;
}

void Rings::Swap(Rings* other) {
  if (other != this) {
    ring_.Swap(&other->ring_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Rings::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Rings_descriptor_;
  metadata.reflection = Rings_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgRing

// @@protoc_insertion_point(global_scope)
