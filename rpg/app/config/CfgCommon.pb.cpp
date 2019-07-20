// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgCommon.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CfgCommon.pb.h"

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

namespace CfgCommon {

namespace {

const ::google::protobuf::Descriptor* Reward_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Reward_reflection_ = NULL;
const ::google::protobuf::Descriptor* Attribute_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Attribute_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CfgCommon_2eproto() {
  protobuf_AddDesc_CfgCommon_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CfgCommon.proto");
  GOOGLE_CHECK(file != NULL);
  Reward_descriptor_ = file->message_type(0);
  static const int Reward_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reward, item_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reward, num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reward, rate_),
  };
  Reward_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Reward_descriptor_,
      Reward::default_instance_,
      Reward_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reward, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reward, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Reward));
  Attribute_descriptor_ = file->message_type(1);
  static const int Attribute_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Attribute, group_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Attribute, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Attribute, num_),
  };
  Attribute_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Attribute_descriptor_,
      Attribute::default_instance_,
      Attribute_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Attribute, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Attribute, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Attribute));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CfgCommon_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Reward_descriptor_, &Reward::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Attribute_descriptor_, &Attribute::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CfgCommon_2eproto() {
  delete Reward::default_instance_;
  delete Reward_reflection_;
  delete Attribute::default_instance_;
  delete Attribute_reflection_;
}

void protobuf_AddDesc_CfgCommon_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017CfgCommon.proto\022\tCfgCommon\"1\n\006Reward\022\014"
    "\n\004item\030\001 \002(\r\022\013\n\003num\030\002 \002(\r\022\014\n\004rate\030\003 \001(\r\""
    "5\n\tAttribute\022\r\n\005group\030\001 \002(\005\022\014\n\004type\030\002 \002("
    "\005\022\013\n\003num\030\003 \002(\003", 134);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CfgCommon.proto", &protobuf_RegisterTypes);
  Reward::default_instance_ = new Reward();
  Attribute::default_instance_ = new Attribute();
  Reward::default_instance_->InitAsDefaultInstance();
  Attribute::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CfgCommon_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CfgCommon_2eproto {
  StaticDescriptorInitializer_CfgCommon_2eproto() {
    protobuf_AddDesc_CfgCommon_2eproto();
  }
} static_descriptor_initializer_CfgCommon_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Reward::kItemFieldNumber;
const int Reward::kNumFieldNumber;
const int Reward::kRateFieldNumber;
#endif  // !_MSC_VER

Reward::Reward()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgCommon.Reward)
}

void Reward::InitAsDefaultInstance() {
}

Reward::Reward(const Reward& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgCommon.Reward)
}

void Reward::SharedCtor() {
  _cached_size_ = 0;
  item_ = 0u;
  num_ = 0u;
  rate_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Reward::~Reward() {
  // @@protoc_insertion_point(destructor:CfgCommon.Reward)
  SharedDtor();
}

void Reward::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Reward::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Reward::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Reward_descriptor_;
}

const Reward& Reward::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgCommon_2eproto();
  return *default_instance_;
}

Reward* Reward::default_instance_ = NULL;

Reward* Reward::New() const {
  return new Reward;
}

void Reward::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Reward*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(item_, rate_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Reward::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgCommon.Reward)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 item = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &item_)));
          set_has_item();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_num;
        break;
      }

      // required uint32 num = 2;
      case 2: {
        if (tag == 16) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &num_)));
          set_has_num();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_rate;
        break;
      }

      // optional uint32 rate = 3;
      case 3: {
        if (tag == 24) {
         parse_rate:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rate_)));
          set_has_rate();
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
  // @@protoc_insertion_point(parse_success:CfgCommon.Reward)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgCommon.Reward)
  return false;
#undef DO_
}

void Reward::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgCommon.Reward)
  // required uint32 item = 1;
  if (has_item()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->item(), output);
  }

  // required uint32 num = 2;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->num(), output);
  }

  // optional uint32 rate = 3;
  if (has_rate()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->rate(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgCommon.Reward)
}

::google::protobuf::uint8* Reward::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgCommon.Reward)
  // required uint32 item = 1;
  if (has_item()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->item(), target);
  }

  // required uint32 num = 2;
  if (has_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->num(), target);
  }

  // optional uint32 rate = 3;
  if (has_rate()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->rate(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgCommon.Reward)
  return target;
}

int Reward::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 item = 1;
    if (has_item()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->item());
    }

    // required uint32 num = 2;
    if (has_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->num());
    }

    // optional uint32 rate = 3;
    if (has_rate()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->rate());
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

void Reward::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Reward* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Reward*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Reward::MergeFrom(const Reward& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_item()) {
      set_item(from.item());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
    if (from.has_rate()) {
      set_rate(from.rate());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Reward::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Reward::CopyFrom(const Reward& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Reward::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Reward::Swap(Reward* other) {
  if (other != this) {
    std::swap(item_, other->item_);
    std::swap(num_, other->num_);
    std::swap(rate_, other->rate_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Reward::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Reward_descriptor_;
  metadata.reflection = Reward_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Attribute::kGroupFieldNumber;
const int Attribute::kTypeFieldNumber;
const int Attribute::kNumFieldNumber;
#endif  // !_MSC_VER

Attribute::Attribute()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CfgCommon.Attribute)
}

void Attribute::InitAsDefaultInstance() {
}

Attribute::Attribute(const Attribute& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CfgCommon.Attribute)
}

void Attribute::SharedCtor() {
  _cached_size_ = 0;
  group_ = 0;
  type_ = 0;
  num_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Attribute::~Attribute() {
  // @@protoc_insertion_point(destructor:CfgCommon.Attribute)
  SharedDtor();
}

void Attribute::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Attribute::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Attribute::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Attribute_descriptor_;
}

const Attribute& Attribute::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CfgCommon_2eproto();
  return *default_instance_;
}

Attribute* Attribute::default_instance_ = NULL;

Attribute* Attribute::New() const {
  return new Attribute;
}

void Attribute::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Attribute*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(group_, num_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Attribute::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CfgCommon.Attribute)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 group = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &group_)));
          set_has_group();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }

      // required int32 type = 2;
      case 2: {
        if (tag == 16) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_num;
        break;
      }

      // required int64 num = 3;
      case 3: {
        if (tag == 24) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &num_)));
          set_has_num();
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
  // @@protoc_insertion_point(parse_success:CfgCommon.Attribute)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CfgCommon.Attribute)
  return false;
#undef DO_
}

void Attribute::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CfgCommon.Attribute)
  // required int32 group = 1;
  if (has_group()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->group(), output);
  }

  // required int32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->type(), output);
  }

  // required int64 num = 3;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->num(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CfgCommon.Attribute)
}

::google::protobuf::uint8* Attribute::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CfgCommon.Attribute)
  // required int32 group = 1;
  if (has_group()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->group(), target);
  }

  // required int32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->type(), target);
  }

  // required int64 num = 3;
  if (has_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->num(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CfgCommon.Attribute)
  return target;
}

int Attribute::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 group = 1;
    if (has_group()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->group());
    }

    // required int32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }

    // required int64 num = 3;
    if (has_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->num());
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

void Attribute::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Attribute* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Attribute*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Attribute::MergeFrom(const Attribute& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_group()) {
      set_group(from.group());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Attribute::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Attribute::CopyFrom(const Attribute& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Attribute::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void Attribute::Swap(Attribute* other) {
  if (other != this) {
    std::swap(group_, other->group_);
    std::swap(type_, other->type_);
    std::swap(num_, other->num_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Attribute::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Attribute_descriptor_;
  metadata.reflection = Attribute_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgCommon

// @@protoc_insertion_point(global_scope)
