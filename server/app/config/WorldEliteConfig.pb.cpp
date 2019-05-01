// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WorldEliteConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "WorldEliteConfig.pb.h"

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

namespace WorldEliteConfig {

namespace {

const ::google::protobuf::Descriptor* NPCInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NPCInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* TypeNPC_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TypeNPC_reflection_ = NULL;
const ::google::protobuf::Descriptor* OpenPlatformNPC_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  OpenPlatformNPC_reflection_ = NULL;
const ::google::protobuf::Descriptor* EliteNPC_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  EliteNPC_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_WorldEliteConfig_2eproto() {
  protobuf_AddDesc_WorldEliteConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "WorldEliteConfig.proto");
  GOOGLE_CHECK(file != NULL);
  NPCInfo_descriptor_ = file->message_type(0);
  static const int NPCInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCInfo, npcid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCInfo, count_),
  };
  NPCInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NPCInfo_descriptor_,
      NPCInfo::default_instance_,
      NPCInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NPCInfo));
  TypeNPC_descriptor_ = file->message_type(1);
  static const int TypeNPC_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TypeNPC, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TypeNPC, npcs_),
  };
  TypeNPC_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TypeNPC_descriptor_,
      TypeNPC::default_instance_,
      TypeNPC_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TypeNPC, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TypeNPC, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TypeNPC));
  OpenPlatformNPC_descriptor_ = file->message_type(2);
  static const int OpenPlatformNPC_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OpenPlatformNPC, startday_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OpenPlatformNPC, npcall_),
  };
  OpenPlatformNPC_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      OpenPlatformNPC_descriptor_,
      OpenPlatformNPC::default_instance_,
      OpenPlatformNPC_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OpenPlatformNPC, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OpenPlatformNPC, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(OpenPlatformNPC));
  EliteNPC_descriptor_ = file->message_type(3);
  static const int EliteNPC_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EliteNPC, open_platform_npc_),
  };
  EliteNPC_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      EliteNPC_descriptor_,
      EliteNPC::default_instance_,
      EliteNPC_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EliteNPC, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EliteNPC, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(EliteNPC));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_WorldEliteConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NPCInfo_descriptor_, &NPCInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TypeNPC_descriptor_, &TypeNPC::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    OpenPlatformNPC_descriptor_, &OpenPlatformNPC::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    EliteNPC_descriptor_, &EliteNPC::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_WorldEliteConfig_2eproto() {
  delete NPCInfo::default_instance_;
  delete NPCInfo_reflection_;
  delete TypeNPC::default_instance_;
  delete TypeNPC_reflection_;
  delete OpenPlatformNPC::default_instance_;
  delete OpenPlatformNPC_reflection_;
  delete EliteNPC::default_instance_;
  delete EliteNPC_reflection_;
}

void protobuf_AddDesc_WorldEliteConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026WorldEliteConfig.proto\022\020WorldEliteConf"
    "ig\"\'\n\007NPCInfo\022\r\n\005npcid\030\001 \002(\r\022\r\n\005count\030\002 "
    "\002(\r\"@\n\007TypeNPC\022\014\n\004type\030\001 \002(\r\022\'\n\004npcs\030\002 \003"
    "(\0132\031.WorldEliteConfig.NPCInfo\"N\n\017OpenPla"
    "tformNPC\022\020\n\010startday\030\001 \002(\r\022)\n\006npcall\030\002 \003"
    "(\0132\031.WorldEliteConfig.TypeNPC\"H\n\010EliteNP"
    "C\022<\n\021open_platform_npc\030\001 \003(\0132!.WorldElit"
    "eConfig.OpenPlatformNPC", 303);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "WorldEliteConfig.proto", &protobuf_RegisterTypes);
  NPCInfo::default_instance_ = new NPCInfo();
  TypeNPC::default_instance_ = new TypeNPC();
  OpenPlatformNPC::default_instance_ = new OpenPlatformNPC();
  EliteNPC::default_instance_ = new EliteNPC();
  NPCInfo::default_instance_->InitAsDefaultInstance();
  TypeNPC::default_instance_->InitAsDefaultInstance();
  OpenPlatformNPC::default_instance_->InitAsDefaultInstance();
  EliteNPC::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_WorldEliteConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_WorldEliteConfig_2eproto {
  StaticDescriptorInitializer_WorldEliteConfig_2eproto() {
    protobuf_AddDesc_WorldEliteConfig_2eproto();
  }
} static_descriptor_initializer_WorldEliteConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int NPCInfo::kNpcidFieldNumber;
const int NPCInfo::kCountFieldNumber;
#endif  // !_MSC_VER

NPCInfo::NPCInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldEliteConfig.NPCInfo)
}

void NPCInfo::InitAsDefaultInstance() {
}

NPCInfo::NPCInfo(const NPCInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldEliteConfig.NPCInfo)
}

void NPCInfo::SharedCtor() {
  _cached_size_ = 0;
  npcid_ = 0u;
  count_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NPCInfo::~NPCInfo() {
  // @@protoc_insertion_point(destructor:WorldEliteConfig.NPCInfo)
  SharedDtor();
}

void NPCInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void NPCInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NPCInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NPCInfo_descriptor_;
}

const NPCInfo& NPCInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldEliteConfig_2eproto();
  return *default_instance_;
}

NPCInfo* NPCInfo::default_instance_ = NULL;

NPCInfo* NPCInfo::New() const {
  return new NPCInfo;
}

void NPCInfo::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<NPCInfo*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(npcid_, count_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NPCInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldEliteConfig.NPCInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 npcid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &npcid_)));
          set_has_npcid();
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
  // @@protoc_insertion_point(parse_success:WorldEliteConfig.NPCInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldEliteConfig.NPCInfo)
  return false;
#undef DO_
}

void NPCInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldEliteConfig.NPCInfo)
  // required uint32 npcid = 1;
  if (has_npcid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->npcid(), output);
  }

  // required uint32 count = 2;
  if (has_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->count(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldEliteConfig.NPCInfo)
}

::google::protobuf::uint8* NPCInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldEliteConfig.NPCInfo)
  // required uint32 npcid = 1;
  if (has_npcid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->npcid(), target);
  }

  // required uint32 count = 2;
  if (has_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->count(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldEliteConfig.NPCInfo)
  return target;
}

int NPCInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 npcid = 1;
    if (has_npcid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->npcid());
    }

    // required uint32 count = 2;
    if (has_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->count());
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

void NPCInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NPCInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NPCInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NPCInfo::MergeFrom(const NPCInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_npcid()) {
      set_npcid(from.npcid());
    }
    if (from.has_count()) {
      set_count(from.count());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NPCInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NPCInfo::CopyFrom(const NPCInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NPCInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void NPCInfo::Swap(NPCInfo* other) {
  if (other != this) {
    std::swap(npcid_, other->npcid_);
    std::swap(count_, other->count_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NPCInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NPCInfo_descriptor_;
  metadata.reflection = NPCInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TypeNPC::kTypeFieldNumber;
const int TypeNPC::kNpcsFieldNumber;
#endif  // !_MSC_VER

TypeNPC::TypeNPC()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldEliteConfig.TypeNPC)
}

void TypeNPC::InitAsDefaultInstance() {
}

TypeNPC::TypeNPC(const TypeNPC& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldEliteConfig.TypeNPC)
}

void TypeNPC::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TypeNPC::~TypeNPC() {
  // @@protoc_insertion_point(destructor:WorldEliteConfig.TypeNPC)
  SharedDtor();
}

void TypeNPC::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TypeNPC::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TypeNPC::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TypeNPC_descriptor_;
}

const TypeNPC& TypeNPC::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldEliteConfig_2eproto();
  return *default_instance_;
}

TypeNPC* TypeNPC::default_instance_ = NULL;

TypeNPC* TypeNPC::New() const {
  return new TypeNPC;
}

void TypeNPC::Clear() {
  type_ = 0u;
  npcs_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TypeNPC::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldEliteConfig.TypeNPC)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 type = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_npcs;
        break;
      }

      // repeated .WorldEliteConfig.NPCInfo npcs = 2;
      case 2: {
        if (tag == 18) {
         parse_npcs:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_npcs()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_npcs;
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
  // @@protoc_insertion_point(parse_success:WorldEliteConfig.TypeNPC)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldEliteConfig.TypeNPC)
  return false;
#undef DO_
}

void TypeNPC::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldEliteConfig.TypeNPC)
  // required uint32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->type(), output);
  }

  // repeated .WorldEliteConfig.NPCInfo npcs = 2;
  for (int i = 0; i < this->npcs_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->npcs(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldEliteConfig.TypeNPC)
}

::google::protobuf::uint8* TypeNPC::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldEliteConfig.TypeNPC)
  // required uint32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->type(), target);
  }

  // repeated .WorldEliteConfig.NPCInfo npcs = 2;
  for (int i = 0; i < this->npcs_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->npcs(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldEliteConfig.TypeNPC)
  return target;
}

int TypeNPC::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

  }
  // repeated .WorldEliteConfig.NPCInfo npcs = 2;
  total_size += 1 * this->npcs_size();
  for (int i = 0; i < this->npcs_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->npcs(i));
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

void TypeNPC::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TypeNPC* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TypeNPC*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TypeNPC::MergeFrom(const TypeNPC& from) {
  GOOGLE_CHECK_NE(&from, this);
  npcs_.MergeFrom(from.npcs_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TypeNPC::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TypeNPC::CopyFrom(const TypeNPC& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TypeNPC::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->npcs())) return false;
  return true;
}

void TypeNPC::Swap(TypeNPC* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    npcs_.Swap(&other->npcs_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TypeNPC::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TypeNPC_descriptor_;
  metadata.reflection = TypeNPC_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int OpenPlatformNPC::kStartdayFieldNumber;
const int OpenPlatformNPC::kNpcallFieldNumber;
#endif  // !_MSC_VER

OpenPlatformNPC::OpenPlatformNPC()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldEliteConfig.OpenPlatformNPC)
}

void OpenPlatformNPC::InitAsDefaultInstance() {
}

OpenPlatformNPC::OpenPlatformNPC(const OpenPlatformNPC& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldEliteConfig.OpenPlatformNPC)
}

void OpenPlatformNPC::SharedCtor() {
  _cached_size_ = 0;
  startday_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

OpenPlatformNPC::~OpenPlatformNPC() {
  // @@protoc_insertion_point(destructor:WorldEliteConfig.OpenPlatformNPC)
  SharedDtor();
}

void OpenPlatformNPC::SharedDtor() {
  if (this != default_instance_) {
  }
}

void OpenPlatformNPC::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* OpenPlatformNPC::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OpenPlatformNPC_descriptor_;
}

const OpenPlatformNPC& OpenPlatformNPC::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldEliteConfig_2eproto();
  return *default_instance_;
}

OpenPlatformNPC* OpenPlatformNPC::default_instance_ = NULL;

OpenPlatformNPC* OpenPlatformNPC::New() const {
  return new OpenPlatformNPC;
}

void OpenPlatformNPC::Clear() {
  startday_ = 0u;
  npcall_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool OpenPlatformNPC::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldEliteConfig.OpenPlatformNPC)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 startday = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &startday_)));
          set_has_startday();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_npcall;
        break;
      }

      // repeated .WorldEliteConfig.TypeNPC npcall = 2;
      case 2: {
        if (tag == 18) {
         parse_npcall:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_npcall()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_npcall;
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
  // @@protoc_insertion_point(parse_success:WorldEliteConfig.OpenPlatformNPC)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldEliteConfig.OpenPlatformNPC)
  return false;
#undef DO_
}

void OpenPlatformNPC::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldEliteConfig.OpenPlatformNPC)
  // required uint32 startday = 1;
  if (has_startday()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->startday(), output);
  }

  // repeated .WorldEliteConfig.TypeNPC npcall = 2;
  for (int i = 0; i < this->npcall_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->npcall(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldEliteConfig.OpenPlatformNPC)
}

::google::protobuf::uint8* OpenPlatformNPC::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldEliteConfig.OpenPlatformNPC)
  // required uint32 startday = 1;
  if (has_startday()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->startday(), target);
  }

  // repeated .WorldEliteConfig.TypeNPC npcall = 2;
  for (int i = 0; i < this->npcall_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->npcall(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldEliteConfig.OpenPlatformNPC)
  return target;
}

int OpenPlatformNPC::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 startday = 1;
    if (has_startday()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->startday());
    }

  }
  // repeated .WorldEliteConfig.TypeNPC npcall = 2;
  total_size += 1 * this->npcall_size();
  for (int i = 0; i < this->npcall_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->npcall(i));
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

void OpenPlatformNPC::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const OpenPlatformNPC* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const OpenPlatformNPC*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void OpenPlatformNPC::MergeFrom(const OpenPlatformNPC& from) {
  GOOGLE_CHECK_NE(&from, this);
  npcall_.MergeFrom(from.npcall_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_startday()) {
      set_startday(from.startday());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void OpenPlatformNPC::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OpenPlatformNPC::CopyFrom(const OpenPlatformNPC& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OpenPlatformNPC::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->npcall())) return false;
  return true;
}

void OpenPlatformNPC::Swap(OpenPlatformNPC* other) {
  if (other != this) {
    std::swap(startday_, other->startday_);
    npcall_.Swap(&other->npcall_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata OpenPlatformNPC::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = OpenPlatformNPC_descriptor_;
  metadata.reflection = OpenPlatformNPC_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int EliteNPC::kOpenPlatformNpcFieldNumber;
#endif  // !_MSC_VER

EliteNPC::EliteNPC()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldEliteConfig.EliteNPC)
}

void EliteNPC::InitAsDefaultInstance() {
}

EliteNPC::EliteNPC(const EliteNPC& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldEliteConfig.EliteNPC)
}

void EliteNPC::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EliteNPC::~EliteNPC() {
  // @@protoc_insertion_point(destructor:WorldEliteConfig.EliteNPC)
  SharedDtor();
}

void EliteNPC::SharedDtor() {
  if (this != default_instance_) {
  }
}

void EliteNPC::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* EliteNPC::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EliteNPC_descriptor_;
}

const EliteNPC& EliteNPC::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldEliteConfig_2eproto();
  return *default_instance_;
}

EliteNPC* EliteNPC::default_instance_ = NULL;

EliteNPC* EliteNPC::New() const {
  return new EliteNPC;
}

void EliteNPC::Clear() {
  open_platform_npc_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool EliteNPC::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldEliteConfig.EliteNPC)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
      case 1: {
        if (tag == 10) {
         parse_open_platform_npc:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_open_platform_npc()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_open_platform_npc;
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
  // @@protoc_insertion_point(parse_success:WorldEliteConfig.EliteNPC)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldEliteConfig.EliteNPC)
  return false;
#undef DO_
}

void EliteNPC::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldEliteConfig.EliteNPC)
  // repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
  for (int i = 0; i < this->open_platform_npc_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->open_platform_npc(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldEliteConfig.EliteNPC)
}

::google::protobuf::uint8* EliteNPC::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldEliteConfig.EliteNPC)
  // repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
  for (int i = 0; i < this->open_platform_npc_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->open_platform_npc(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldEliteConfig.EliteNPC)
  return target;
}

int EliteNPC::ByteSize() const {
  int total_size = 0;

  // repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
  total_size += 1 * this->open_platform_npc_size();
  for (int i = 0; i < this->open_platform_npc_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->open_platform_npc(i));
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

void EliteNPC::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const EliteNPC* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const EliteNPC*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void EliteNPC::MergeFrom(const EliteNPC& from) {
  GOOGLE_CHECK_NE(&from, this);
  open_platform_npc_.MergeFrom(from.open_platform_npc_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void EliteNPC::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EliteNPC::CopyFrom(const EliteNPC& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EliteNPC::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->open_platform_npc())) return false;
  return true;
}

void EliteNPC::Swap(EliteNPC* other) {
  if (other != this) {
    open_platform_npc_.Swap(&other->open_platform_npc_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata EliteNPC::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = EliteNPC_descriptor_;
  metadata.reflection = EliteNPC_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace WorldEliteConfig

// @@protoc_insertion_point(global_scope)
