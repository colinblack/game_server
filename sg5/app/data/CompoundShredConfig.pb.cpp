// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CompoundShredConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CompoundShredConfig.pb.h"

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

namespace CompoundShredConfig {

namespace {

const ::google::protobuf::Descriptor* ShredItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ShredItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* ShredCompounds_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ShredCompounds_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CompoundShredConfig_2eproto() {
  protobuf_AddDesc_CompoundShredConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CompoundShredConfig.proto");
  GOOGLE_CHECK(file != NULL);
  ShredItem_descriptor_ = file->message_type(0);
  static const int ShredItem_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, shredid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, count_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, compoundid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, ishero_),
  };
  ShredItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ShredItem_descriptor_,
      ShredItem::default_instance_,
      ShredItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ShredItem));
  ShredCompounds_descriptor_ = file->message_type(1);
  static const int ShredCompounds_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredCompounds, shred_compounds_),
  };
  ShredCompounds_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ShredCompounds_descriptor_,
      ShredCompounds::default_instance_,
      ShredCompounds_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredCompounds, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShredCompounds, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ShredCompounds));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CompoundShredConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ShredItem_descriptor_, &ShredItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ShredCompounds_descriptor_, &ShredCompounds::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CompoundShredConfig_2eproto() {
  delete ShredItem::default_instance_;
  delete ShredItem_reflection_;
  delete ShredCompounds::default_instance_;
  delete ShredCompounds_reflection_;
}

void protobuf_AddDesc_CompoundShredConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031CompoundShredConfig.proto\022\023CompoundShr"
    "edConfig\"O\n\tShredItem\022\017\n\007shredId\030\001 \002(\r\022\r"
    "\n\005count\030\002 \002(\r\022\022\n\ncompoundId\030\003 \002(\r\022\016\n\006ish"
    "ero\030\004 \002(\r\"I\n\016ShredCompounds\0227\n\017shred_com"
    "pounds\030\001 \003(\0132\036.CompoundShredConfig.Shred"
    "Item", 204);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CompoundShredConfig.proto", &protobuf_RegisterTypes);
  ShredItem::default_instance_ = new ShredItem();
  ShredCompounds::default_instance_ = new ShredCompounds();
  ShredItem::default_instance_->InitAsDefaultInstance();
  ShredCompounds::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CompoundShredConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CompoundShredConfig_2eproto {
  StaticDescriptorInitializer_CompoundShredConfig_2eproto() {
    protobuf_AddDesc_CompoundShredConfig_2eproto();
  }
} static_descriptor_initializer_CompoundShredConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ShredItem::kShredIdFieldNumber;
const int ShredItem::kCountFieldNumber;
const int ShredItem::kCompoundIdFieldNumber;
const int ShredItem::kIsheroFieldNumber;
#endif  // !_MSC_VER

ShredItem::ShredItem()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CompoundShredConfig.ShredItem)
}

void ShredItem::InitAsDefaultInstance() {
}

ShredItem::ShredItem(const ShredItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CompoundShredConfig.ShredItem)
}

void ShredItem::SharedCtor() {
  _cached_size_ = 0;
  shredid_ = 0u;
  count_ = 0u;
  compoundid_ = 0u;
  ishero_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ShredItem::~ShredItem() {
  // @@protoc_insertion_point(destructor:CompoundShredConfig.ShredItem)
  SharedDtor();
}

void ShredItem::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ShredItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ShredItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ShredItem_descriptor_;
}

const ShredItem& ShredItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CompoundShredConfig_2eproto();
  return *default_instance_;
}

ShredItem* ShredItem::default_instance_ = NULL;

ShredItem* ShredItem::New() const {
  return new ShredItem;
}

void ShredItem::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ShredItem*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(shredid_, ishero_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ShredItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CompoundShredConfig.ShredItem)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 shredId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &shredid_)));
          set_has_shredid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_count;
        break;
      }

      // required uint32 count = 2;
      case 2: {
        if (tag == 16) {
         parse_count:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &count_)));
          set_has_count();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_compoundId;
        break;
      }

      // required uint32 compoundId = 3;
      case 3: {
        if (tag == 24) {
         parse_compoundId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &compoundid_)));
          set_has_compoundid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_ishero;
        break;
      }

      // required uint32 ishero = 4;
      case 4: {
        if (tag == 32) {
         parse_ishero:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ishero_)));
          set_has_ishero();
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
  // @@protoc_insertion_point(parse_success:CompoundShredConfig.ShredItem)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CompoundShredConfig.ShredItem)
  return false;
#undef DO_
}

void ShredItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CompoundShredConfig.ShredItem)
  // required uint32 shredId = 1;
  if (has_shredid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->shredid(), output);
  }

  // required uint32 count = 2;
  if (has_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->count(), output);
  }

  // required uint32 compoundId = 3;
  if (has_compoundid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->compoundid(), output);
  }

  // required uint32 ishero = 4;
  if (has_ishero()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->ishero(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CompoundShredConfig.ShredItem)
}

::google::protobuf::uint8* ShredItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CompoundShredConfig.ShredItem)
  // required uint32 shredId = 1;
  if (has_shredid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->shredid(), target);
  }

  // required uint32 count = 2;
  if (has_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->count(), target);
  }

  // required uint32 compoundId = 3;
  if (has_compoundid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->compoundid(), target);
  }

  // required uint32 ishero = 4;
  if (has_ishero()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->ishero(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CompoundShredConfig.ShredItem)
  return target;
}

int ShredItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 shredId = 1;
    if (has_shredid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->shredid());
    }

    // required uint32 count = 2;
    if (has_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->count());
    }

    // required uint32 compoundId = 3;
    if (has_compoundid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->compoundid());
    }

    // required uint32 ishero = 4;
    if (has_ishero()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ishero());
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

void ShredItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ShredItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ShredItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ShredItem::MergeFrom(const ShredItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_shredid()) {
      set_shredid(from.shredid());
    }
    if (from.has_count()) {
      set_count(from.count());
    }
    if (from.has_compoundid()) {
      set_compoundid(from.compoundid());
    }
    if (from.has_ishero()) {
      set_ishero(from.ishero());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ShredItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ShredItem::CopyFrom(const ShredItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ShredItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void ShredItem::Swap(ShredItem* other) {
  if (other != this) {
    std::swap(shredid_, other->shredid_);
    std::swap(count_, other->count_);
    std::swap(compoundid_, other->compoundid_);
    std::swap(ishero_, other->ishero_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ShredItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ShredItem_descriptor_;
  metadata.reflection = ShredItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ShredCompounds::kShredCompoundsFieldNumber;
#endif  // !_MSC_VER

ShredCompounds::ShredCompounds()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CompoundShredConfig.ShredCompounds)
}

void ShredCompounds::InitAsDefaultInstance() {
}

ShredCompounds::ShredCompounds(const ShredCompounds& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CompoundShredConfig.ShredCompounds)
}

void ShredCompounds::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ShredCompounds::~ShredCompounds() {
  // @@protoc_insertion_point(destructor:CompoundShredConfig.ShredCompounds)
  SharedDtor();
}

void ShredCompounds::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ShredCompounds::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ShredCompounds::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ShredCompounds_descriptor_;
}

const ShredCompounds& ShredCompounds::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CompoundShredConfig_2eproto();
  return *default_instance_;
}

ShredCompounds* ShredCompounds::default_instance_ = NULL;

ShredCompounds* ShredCompounds::New() const {
  return new ShredCompounds;
}

void ShredCompounds::Clear() {
  shred_compounds_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ShredCompounds::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CompoundShredConfig.ShredCompounds)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CompoundShredConfig.ShredItem shred_compounds = 1;
      case 1: {
        if (tag == 10) {
         parse_shred_compounds:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_shred_compounds()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_shred_compounds;
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
  // @@protoc_insertion_point(parse_success:CompoundShredConfig.ShredCompounds)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CompoundShredConfig.ShredCompounds)
  return false;
#undef DO_
}

void ShredCompounds::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CompoundShredConfig.ShredCompounds)
  // repeated .CompoundShredConfig.ShredItem shred_compounds = 1;
  for (int i = 0; i < this->shred_compounds_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->shred_compounds(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CompoundShredConfig.ShredCompounds)
}

::google::protobuf::uint8* ShredCompounds::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CompoundShredConfig.ShredCompounds)
  // repeated .CompoundShredConfig.ShredItem shred_compounds = 1;
  for (int i = 0; i < this->shred_compounds_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->shred_compounds(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CompoundShredConfig.ShredCompounds)
  return target;
}

int ShredCompounds::ByteSize() const {
  int total_size = 0;

  // repeated .CompoundShredConfig.ShredItem shred_compounds = 1;
  total_size += 1 * this->shred_compounds_size();
  for (int i = 0; i < this->shred_compounds_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->shred_compounds(i));
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

void ShredCompounds::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ShredCompounds* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ShredCompounds*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ShredCompounds::MergeFrom(const ShredCompounds& from) {
  GOOGLE_CHECK_NE(&from, this);
  shred_compounds_.MergeFrom(from.shred_compounds_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ShredCompounds::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ShredCompounds::CopyFrom(const ShredCompounds& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ShredCompounds::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->shred_compounds())) return false;
  return true;
}

void ShredCompounds::Swap(ShredCompounds* other) {
  if (other != this) {
    shred_compounds_.Swap(&other->shred_compounds_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ShredCompounds::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ShredCompounds_descriptor_;
  metadata.reflection = ShredCompounds_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CompoundShredConfig

// @@protoc_insertion_point(global_scope)