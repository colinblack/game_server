// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoNotify.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProtoNotify.pb.h"

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

namespace ProtoNotify {

namespace {

const ::google::protobuf::Descriptor* NotifyItemCPP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NotifyItemCPP_reflection_ = NULL;
const ::google::protobuf::Descriptor* GetNotifyReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GetNotifyReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* GetNotifyResp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GetNotifyResp_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProtoNotify_2eproto() {
  protobuf_AddDesc_ProtoNotify_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProtoNotify.proto");
  GOOGLE_CHECK(file != NULL);
  NotifyItemCPP_descriptor_ = file->message_type(0);
  static const int NotifyItemCPP_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NotifyItemCPP, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NotifyItemCPP, ts_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NotifyItemCPP, content_),
  };
  NotifyItemCPP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NotifyItemCPP_descriptor_,
      NotifyItemCPP::default_instance_,
      NotifyItemCPP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NotifyItemCPP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NotifyItemCPP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NotifyItemCPP));
  GetNotifyReq_descriptor_ = file->message_type(1);
  static const int GetNotifyReq_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyReq, id_),
  };
  GetNotifyReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GetNotifyReq_descriptor_,
      GetNotifyReq::default_instance_,
      GetNotifyReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GetNotifyReq));
  GetNotifyResp_descriptor_ = file->message_type(2);
  static const int GetNotifyResp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyResp, notify_),
  };
  GetNotifyResp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GetNotifyResp_descriptor_,
      GetNotifyResp::default_instance_,
      GetNotifyResp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyResp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetNotifyResp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GetNotifyResp));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProtoNotify_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NotifyItemCPP_descriptor_, &NotifyItemCPP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GetNotifyReq_descriptor_, &GetNotifyReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GetNotifyResp_descriptor_, &GetNotifyResp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProtoNotify_2eproto() {
  delete NotifyItemCPP::default_instance_;
  delete NotifyItemCPP_reflection_;
  delete GetNotifyReq::default_instance_;
  delete GetNotifyReq_reflection_;
  delete GetNotifyResp::default_instance_;
  delete GetNotifyResp_reflection_;
}

void protobuf_AddDesc_ProtoNotify_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021ProtoNotify.proto\022\013ProtoNotify\"8\n\rNoti"
    "fyItemCPP\022\n\n\002id\030\001 \002(\r\022\n\n\002ts\030\002 \002(\r\022\017\n\007con"
    "tent\030\003 \002(\014\"\032\n\014GetNotifyReq\022\n\n\002id\030\001 \002(\r\";"
    "\n\rGetNotifyResp\022*\n\006notify\030\001 \002(\0132\032.ProtoN"
    "otify.NotifyItemCPP", 179);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProtoNotify.proto", &protobuf_RegisterTypes);
  NotifyItemCPP::default_instance_ = new NotifyItemCPP();
  GetNotifyReq::default_instance_ = new GetNotifyReq();
  GetNotifyResp::default_instance_ = new GetNotifyResp();
  NotifyItemCPP::default_instance_->InitAsDefaultInstance();
  GetNotifyReq::default_instance_->InitAsDefaultInstance();
  GetNotifyResp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProtoNotify_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProtoNotify_2eproto {
  StaticDescriptorInitializer_ProtoNotify_2eproto() {
    protobuf_AddDesc_ProtoNotify_2eproto();
  }
} static_descriptor_initializer_ProtoNotify_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int NotifyItemCPP::kIdFieldNumber;
const int NotifyItemCPP::kTsFieldNumber;
const int NotifyItemCPP::kContentFieldNumber;
#endif  // !_MSC_VER

NotifyItemCPP::NotifyItemCPP()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoNotify.NotifyItemCPP)
}

void NotifyItemCPP::InitAsDefaultInstance() {
}

NotifyItemCPP::NotifyItemCPP(const NotifyItemCPP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoNotify.NotifyItemCPP)
}

void NotifyItemCPP::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  id_ = 0u;
  ts_ = 0u;
  content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NotifyItemCPP::~NotifyItemCPP() {
  // @@protoc_insertion_point(destructor:ProtoNotify.NotifyItemCPP)
  SharedDtor();
}

void NotifyItemCPP::SharedDtor() {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete content_;
  }
  if (this != default_instance_) {
  }
}

void NotifyItemCPP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NotifyItemCPP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NotifyItemCPP_descriptor_;
}

const NotifyItemCPP& NotifyItemCPP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoNotify_2eproto();
  return *default_instance_;
}

NotifyItemCPP* NotifyItemCPP::default_instance_ = NULL;

NotifyItemCPP* NotifyItemCPP::New() const {
  return new NotifyItemCPP;
}

void NotifyItemCPP::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<NotifyItemCPP*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(id_, ts_);
    if (has_content()) {
      if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        content_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NotifyItemCPP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoNotify.NotifyItemCPP)
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
        if (input->ExpectTag(16)) goto parse_ts;
        break;
      }

      // required uint32 ts = 2;
      case 2: {
        if (tag == 16) {
         parse_ts:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ts_)));
          set_has_ts();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_content;
        break;
      }

      // required bytes content = 3;
      case 3: {
        if (tag == 26) {
         parse_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_content()));
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
  // @@protoc_insertion_point(parse_success:ProtoNotify.NotifyItemCPP)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoNotify.NotifyItemCPP)
  return false;
#undef DO_
}

void NotifyItemCPP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoNotify.NotifyItemCPP)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 ts = 2;
  if (has_ts()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->ts(), output);
  }

  // required bytes content = 3;
  if (has_content()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->content(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoNotify.NotifyItemCPP)
}

::google::protobuf::uint8* NotifyItemCPP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoNotify.NotifyItemCPP)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 ts = 2;
  if (has_ts()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->ts(), target);
  }

  // required bytes content = 3;
  if (has_content()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->content(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoNotify.NotifyItemCPP)
  return target;
}

int NotifyItemCPP::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 ts = 2;
    if (has_ts()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ts());
    }

    // required bytes content = 3;
    if (has_content()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->content());
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

void NotifyItemCPP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NotifyItemCPP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NotifyItemCPP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NotifyItemCPP::MergeFrom(const NotifyItemCPP& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_ts()) {
      set_ts(from.ts());
    }
    if (from.has_content()) {
      set_content(from.content());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NotifyItemCPP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NotifyItemCPP::CopyFrom(const NotifyItemCPP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NotifyItemCPP::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void NotifyItemCPP::Swap(NotifyItemCPP* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(ts_, other->ts_);
    std::swap(content_, other->content_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NotifyItemCPP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NotifyItemCPP_descriptor_;
  metadata.reflection = NotifyItemCPP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GetNotifyReq::kIdFieldNumber;
#endif  // !_MSC_VER

GetNotifyReq::GetNotifyReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoNotify.GetNotifyReq)
}

void GetNotifyReq::InitAsDefaultInstance() {
}

GetNotifyReq::GetNotifyReq(const GetNotifyReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoNotify.GetNotifyReq)
}

void GetNotifyReq::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GetNotifyReq::~GetNotifyReq() {
  // @@protoc_insertion_point(destructor:ProtoNotify.GetNotifyReq)
  SharedDtor();
}

void GetNotifyReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GetNotifyReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GetNotifyReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GetNotifyReq_descriptor_;
}

const GetNotifyReq& GetNotifyReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoNotify_2eproto();
  return *default_instance_;
}

GetNotifyReq* GetNotifyReq::default_instance_ = NULL;

GetNotifyReq* GetNotifyReq::New() const {
  return new GetNotifyReq;
}

void GetNotifyReq::Clear() {
  id_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GetNotifyReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoNotify.GetNotifyReq)
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
  // @@protoc_insertion_point(parse_success:ProtoNotify.GetNotifyReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoNotify.GetNotifyReq)
  return false;
#undef DO_
}

void GetNotifyReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoNotify.GetNotifyReq)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoNotify.GetNotifyReq)
}

::google::protobuf::uint8* GetNotifyReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoNotify.GetNotifyReq)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoNotify.GetNotifyReq)
  return target;
}

int GetNotifyReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
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

void GetNotifyReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GetNotifyReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GetNotifyReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GetNotifyReq::MergeFrom(const GetNotifyReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GetNotifyReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetNotifyReq::CopyFrom(const GetNotifyReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetNotifyReq::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void GetNotifyReq::Swap(GetNotifyReq* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GetNotifyReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GetNotifyReq_descriptor_;
  metadata.reflection = GetNotifyReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GetNotifyResp::kNotifyFieldNumber;
#endif  // !_MSC_VER

GetNotifyResp::GetNotifyResp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoNotify.GetNotifyResp)
}

void GetNotifyResp::InitAsDefaultInstance() {
  notify_ = const_cast< ::ProtoNotify::NotifyItemCPP*>(&::ProtoNotify::NotifyItemCPP::default_instance());
}

GetNotifyResp::GetNotifyResp(const GetNotifyResp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoNotify.GetNotifyResp)
}

void GetNotifyResp::SharedCtor() {
  _cached_size_ = 0;
  notify_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GetNotifyResp::~GetNotifyResp() {
  // @@protoc_insertion_point(destructor:ProtoNotify.GetNotifyResp)
  SharedDtor();
}

void GetNotifyResp::SharedDtor() {
  if (this != default_instance_) {
    delete notify_;
  }
}

void GetNotifyResp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GetNotifyResp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GetNotifyResp_descriptor_;
}

const GetNotifyResp& GetNotifyResp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoNotify_2eproto();
  return *default_instance_;
}

GetNotifyResp* GetNotifyResp::default_instance_ = NULL;

GetNotifyResp* GetNotifyResp::New() const {
  return new GetNotifyResp;
}

void GetNotifyResp::Clear() {
  if (has_notify()) {
    if (notify_ != NULL) notify_->::ProtoNotify::NotifyItemCPP::Clear();
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GetNotifyResp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoNotify.GetNotifyResp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ProtoNotify.NotifyItemCPP notify = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_notify()));
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
  // @@protoc_insertion_point(parse_success:ProtoNotify.GetNotifyResp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoNotify.GetNotifyResp)
  return false;
#undef DO_
}

void GetNotifyResp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoNotify.GetNotifyResp)
  // required .ProtoNotify.NotifyItemCPP notify = 1;
  if (has_notify()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->notify(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoNotify.GetNotifyResp)
}

::google::protobuf::uint8* GetNotifyResp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoNotify.GetNotifyResp)
  // required .ProtoNotify.NotifyItemCPP notify = 1;
  if (has_notify()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->notify(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoNotify.GetNotifyResp)
  return target;
}

int GetNotifyResp::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ProtoNotify.NotifyItemCPP notify = 1;
    if (has_notify()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->notify());
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

void GetNotifyResp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GetNotifyResp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GetNotifyResp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GetNotifyResp::MergeFrom(const GetNotifyResp& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_notify()) {
      mutable_notify()->::ProtoNotify::NotifyItemCPP::MergeFrom(from.notify());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GetNotifyResp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetNotifyResp::CopyFrom(const GetNotifyResp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetNotifyResp::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (has_notify()) {
    if (!this->notify().IsInitialized()) return false;
  }
  return true;
}

void GetNotifyResp::Swap(GetNotifyResp* other) {
  if (other != this) {
    std::swap(notify_, other->notify_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GetNotifyResp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GetNotifyResp_descriptor_;
  metadata.reflection = GetNotifyResp_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoNotify

// @@protoc_insertion_point(global_scope)