// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoPass.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProtoPass.pb.h"

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

namespace ProtoPass {

namespace {

const ::google::protobuf::Descriptor* NPCPassRecord_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NPCPassRecord_reflection_ = NULL;
const ::google::protobuf::Descriptor* EnterFightReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  EnterFightReq_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProtoPass_2eproto() {
  protobuf_AddDesc_ProtoPass_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProtoPass.proto");
  GOOGLE_CHECK(file != NULL);
  NPCPassRecord_descriptor_ = file->message_type(0);
  static const int NPCPassRecord_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCPassRecord, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCPassRecord, cnt_),
  };
  NPCPassRecord_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NPCPassRecord_descriptor_,
      NPCPassRecord::default_instance_,
      NPCPassRecord_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCPassRecord, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NPCPassRecord, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NPCPassRecord));
  EnterFightReq_descriptor_ = file->message_type(1);
  static const int EnterFightReq_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EnterFightReq, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EnterFightReq, hero_ids_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EnterFightReq, diff_),
  };
  EnterFightReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      EnterFightReq_descriptor_,
      EnterFightReq::default_instance_,
      EnterFightReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EnterFightReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EnterFightReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(EnterFightReq));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProtoPass_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NPCPassRecord_descriptor_, &NPCPassRecord::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    EnterFightReq_descriptor_, &EnterFightReq::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProtoPass_2eproto() {
  delete NPCPassRecord::default_instance_;
  delete NPCPassRecord_reflection_;
  delete EnterFightReq::default_instance_;
  delete EnterFightReq_reflection_;
}

void protobuf_AddDesc_ProtoPass_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017ProtoPass.proto\022\tProtoPass\"(\n\rNPCPassR"
    "ecord\022\n\n\002id\030\001 \002(\r\022\013\n\003cnt\030\002 \002(\r\";\n\rEnterF"
    "ightReq\022\n\n\002id\030\001 \002(\r\022\020\n\010hero_ids\030\002 \003(\r\022\014\n"
    "\004diff\030\003 \001(\005", 131);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProtoPass.proto", &protobuf_RegisterTypes);
  NPCPassRecord::default_instance_ = new NPCPassRecord();
  EnterFightReq::default_instance_ = new EnterFightReq();
  NPCPassRecord::default_instance_->InitAsDefaultInstance();
  EnterFightReq::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProtoPass_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProtoPass_2eproto {
  StaticDescriptorInitializer_ProtoPass_2eproto() {
    protobuf_AddDesc_ProtoPass_2eproto();
  }
} static_descriptor_initializer_ProtoPass_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int NPCPassRecord::kIdFieldNumber;
const int NPCPassRecord::kCntFieldNumber;
#endif  // !_MSC_VER

NPCPassRecord::NPCPassRecord()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoPass.NPCPassRecord)
}

void NPCPassRecord::InitAsDefaultInstance() {
}

NPCPassRecord::NPCPassRecord(const NPCPassRecord& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoPass.NPCPassRecord)
}

void NPCPassRecord::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  cnt_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NPCPassRecord::~NPCPassRecord() {
  // @@protoc_insertion_point(destructor:ProtoPass.NPCPassRecord)
  SharedDtor();
}

void NPCPassRecord::SharedDtor() {
  if (this != default_instance_) {
  }
}

void NPCPassRecord::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NPCPassRecord::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NPCPassRecord_descriptor_;
}

const NPCPassRecord& NPCPassRecord::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoPass_2eproto();
  return *default_instance_;
}

NPCPassRecord* NPCPassRecord::default_instance_ = NULL;

NPCPassRecord* NPCPassRecord::New() const {
  return new NPCPassRecord;
}

void NPCPassRecord::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<NPCPassRecord*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, cnt_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NPCPassRecord::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoPass.NPCPassRecord)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_cnt;
        break;
      }

      // required uint32 cnt = 2;
      case 2: {
        if (tag == 16) {
         parse_cnt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cnt_)));
          set_has_cnt();
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
  // @@protoc_insertion_point(parse_success:ProtoPass.NPCPassRecord)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoPass.NPCPassRecord)
  return false;
#undef DO_
}

void NPCPassRecord::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoPass.NPCPassRecord)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 cnt = 2;
  if (has_cnt()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->cnt(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoPass.NPCPassRecord)
}

::google::protobuf::uint8* NPCPassRecord::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoPass.NPCPassRecord)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 cnt = 2;
  if (has_cnt()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->cnt(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoPass.NPCPassRecord)
  return target;
}

int NPCPassRecord::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 cnt = 2;
    if (has_cnt()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cnt());
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

void NPCPassRecord::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NPCPassRecord* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NPCPassRecord*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NPCPassRecord::MergeFrom(const NPCPassRecord& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_cnt()) {
      set_cnt(from.cnt());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NPCPassRecord::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NPCPassRecord::CopyFrom(const NPCPassRecord& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NPCPassRecord::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void NPCPassRecord::Swap(NPCPassRecord* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(cnt_, other->cnt_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NPCPassRecord::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NPCPassRecord_descriptor_;
  metadata.reflection = NPCPassRecord_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int EnterFightReq::kIdFieldNumber;
const int EnterFightReq::kHeroIdsFieldNumber;
const int EnterFightReq::kDiffFieldNumber;
#endif  // !_MSC_VER

EnterFightReq::EnterFightReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoPass.EnterFightReq)
}

void EnterFightReq::InitAsDefaultInstance() {
}

EnterFightReq::EnterFightReq(const EnterFightReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoPass.EnterFightReq)
}

void EnterFightReq::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  diff_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EnterFightReq::~EnterFightReq() {
  // @@protoc_insertion_point(destructor:ProtoPass.EnterFightReq)
  SharedDtor();
}

void EnterFightReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void EnterFightReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* EnterFightReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EnterFightReq_descriptor_;
}

const EnterFightReq& EnterFightReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoPass_2eproto();
  return *default_instance_;
}

EnterFightReq* EnterFightReq::default_instance_ = NULL;

EnterFightReq* EnterFightReq::New() const {
  return new EnterFightReq;
}

void EnterFightReq::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<EnterFightReq*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, diff_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  hero_ids_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool EnterFightReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoPass.EnterFightReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_hero_ids;
        break;
      }

      // repeated uint32 hero_ids = 2;
      case 2: {
        if (tag == 16) {
         parse_hero_ids:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16, input, this->mutable_hero_ids())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_hero_ids())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_hero_ids;
        if (input->ExpectTag(24)) goto parse_diff;
        break;
      }

      // optional int32 diff = 3;
      case 3: {
        if (tag == 24) {
         parse_diff:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &diff_)));
          set_has_diff();
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
  // @@protoc_insertion_point(parse_success:ProtoPass.EnterFightReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoPass.EnterFightReq)
  return false;
#undef DO_
}

void EnterFightReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoPass.EnterFightReq)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // repeated uint32 hero_ids = 2;
  for (int i = 0; i < this->hero_ids_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->hero_ids(i), output);
  }

  // optional int32 diff = 3;
  if (has_diff()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->diff(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoPass.EnterFightReq)
}

::google::protobuf::uint8* EnterFightReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoPass.EnterFightReq)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // repeated uint32 hero_ids = 2;
  for (int i = 0; i < this->hero_ids_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(2, this->hero_ids(i), target);
  }

  // optional int32 diff = 3;
  if (has_diff()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->diff(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoPass.EnterFightReq)
  return target;
}

int EnterFightReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // optional int32 diff = 3;
    if (has_diff()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->diff());
    }

  }
  // repeated uint32 hero_ids = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->hero_ids_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->hero_ids(i));
    }
    total_size += 1 * this->hero_ids_size() + data_size;
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

void EnterFightReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const EnterFightReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const EnterFightReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void EnterFightReq::MergeFrom(const EnterFightReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  hero_ids_.MergeFrom(from.hero_ids_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_diff()) {
      set_diff(from.diff());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void EnterFightReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EnterFightReq::CopyFrom(const EnterFightReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EnterFightReq::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void EnterFightReq::Swap(EnterFightReq* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    hero_ids_.Swap(&other->hero_ids_);
    std::swap(diff_, other->diff_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata EnterFightReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = EnterFightReq_descriptor_;
  metadata.reflection = EnterFightReq_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoPass

// @@protoc_insertion_point(global_scope)
