// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WanBaGift.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "WanBaGift.pb.h"

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

namespace WanBaGift {

namespace {

const ::google::protobuf::Descriptor* User_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  User_reflection_ = NULL;
const ::google::protobuf::Descriptor* Daily_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Daily_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_WanBaGift_2eproto() {
  protobuf_AddDesc_WanBaGift_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "WanBaGift.proto");
  GOOGLE_CHECK(file != NULL);
  User_descriptor_ = file->message_type(0);
  static const int User_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User, openid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User, gift_),
  };
  User_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      User_descriptor_,
      User::default_instance_,
      User_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(User));
  Daily_descriptor_ = file->message_type(1);
  static const int Daily_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Daily, ts_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Daily, ids_),
  };
  Daily_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Daily_descriptor_,
      Daily::default_instance_,
      Daily_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Daily, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Daily, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Daily));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_WanBaGift_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    User_descriptor_, &User::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Daily_descriptor_, &Daily::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_WanBaGift_2eproto() {
  delete User::default_instance_;
  delete User_reflection_;
  delete Daily::default_instance_;
  delete Daily_reflection_;
}

void protobuf_AddDesc_WanBaGift_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017WanBaGift.proto\022\tWanBaGift\"$\n\004User\022\016\n\006"
    "openid\030\001 \002(\t\022\014\n\004gift\030\002 \003(\r\"1\n\005Daily\022\n\n\002t"
    "s\030\001 \002(\r\022\034\n\003ids\030\002 \003(\0132\017.WanBaGift.User", 117);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "WanBaGift.proto", &protobuf_RegisterTypes);
  User::default_instance_ = new User();
  Daily::default_instance_ = new Daily();
  User::default_instance_->InitAsDefaultInstance();
  Daily::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_WanBaGift_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_WanBaGift_2eproto {
  StaticDescriptorInitializer_WanBaGift_2eproto() {
    protobuf_AddDesc_WanBaGift_2eproto();
  }
} static_descriptor_initializer_WanBaGift_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int User::kOpenidFieldNumber;
const int User::kGiftFieldNumber;
#endif  // !_MSC_VER

User::User()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WanBaGift.User)
}

void User::InitAsDefaultInstance() {
}

User::User(const User& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WanBaGift.User)
}

void User::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  openid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

User::~User() {
  // @@protoc_insertion_point(destructor:WanBaGift.User)
  SharedDtor();
}

void User::SharedDtor() {
  if (openid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete openid_;
  }
  if (this != default_instance_) {
  }
}

void User::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* User::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return User_descriptor_;
}

const User& User::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WanBaGift_2eproto();
  return *default_instance_;
}

User* User::default_instance_ = NULL;

User* User::New() const {
  return new User;
}

void User::Clear() {
  if (has_openid()) {
    if (openid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      openid_->clear();
    }
  }
  gift_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool User::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WanBaGift.User)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string openid = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_openid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->openid().data(), this->openid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "openid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_gift;
        break;
      }

      // repeated uint32 gift = 2;
      case 2: {
        if (tag == 16) {
         parse_gift:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16, input, this->mutable_gift())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_gift())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_gift;
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
  // @@protoc_insertion_point(parse_success:WanBaGift.User)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WanBaGift.User)
  return false;
#undef DO_
}

void User::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WanBaGift.User)
  // required string openid = 1;
  if (has_openid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->openid().data(), this->openid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "openid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->openid(), output);
  }

  // repeated uint32 gift = 2;
  for (int i = 0; i < this->gift_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->gift(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WanBaGift.User)
}

::google::protobuf::uint8* User::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WanBaGift.User)
  // required string openid = 1;
  if (has_openid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->openid().data(), this->openid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "openid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->openid(), target);
  }

  // repeated uint32 gift = 2;
  for (int i = 0; i < this->gift_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(2, this->gift(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WanBaGift.User)
  return target;
}

int User::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string openid = 1;
    if (has_openid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->openid());
    }

  }
  // repeated uint32 gift = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->gift_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->gift(i));
    }
    total_size += 1 * this->gift_size() + data_size;
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

void User::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const User* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const User*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void User::MergeFrom(const User& from) {
  GOOGLE_CHECK_NE(&from, this);
  gift_.MergeFrom(from.gift_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_openid()) {
      set_openid(from.openid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void User::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void User::CopyFrom(const User& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool User::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void User::Swap(User* other) {
  if (other != this) {
    std::swap(openid_, other->openid_);
    gift_.Swap(&other->gift_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata User::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = User_descriptor_;
  metadata.reflection = User_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Daily::kTsFieldNumber;
const int Daily::kIdsFieldNumber;
#endif  // !_MSC_VER

Daily::Daily()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WanBaGift.Daily)
}

void Daily::InitAsDefaultInstance() {
}

Daily::Daily(const Daily& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WanBaGift.Daily)
}

void Daily::SharedCtor() {
  _cached_size_ = 0;
  ts_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Daily::~Daily() {
  // @@protoc_insertion_point(destructor:WanBaGift.Daily)
  SharedDtor();
}

void Daily::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Daily::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Daily::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Daily_descriptor_;
}

const Daily& Daily::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WanBaGift_2eproto();
  return *default_instance_;
}

Daily* Daily::default_instance_ = NULL;

Daily* Daily::New() const {
  return new Daily;
}

void Daily::Clear() {
  ts_ = 0u;
  ids_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Daily::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WanBaGift.Daily)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 ts = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ts_)));
          set_has_ts();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ids;
        break;
      }

      // repeated .WanBaGift.User ids = 2;
      case 2: {
        if (tag == 18) {
         parse_ids:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_ids()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ids;
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
  // @@protoc_insertion_point(parse_success:WanBaGift.Daily)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WanBaGift.Daily)
  return false;
#undef DO_
}

void Daily::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WanBaGift.Daily)
  // required uint32 ts = 1;
  if (has_ts()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->ts(), output);
  }

  // repeated .WanBaGift.User ids = 2;
  for (int i = 0; i < this->ids_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->ids(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WanBaGift.Daily)
}

::google::protobuf::uint8* Daily::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WanBaGift.Daily)
  // required uint32 ts = 1;
  if (has_ts()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->ts(), target);
  }

  // repeated .WanBaGift.User ids = 2;
  for (int i = 0; i < this->ids_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->ids(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WanBaGift.Daily)
  return target;
}

int Daily::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 ts = 1;
    if (has_ts()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ts());
    }

  }
  // repeated .WanBaGift.User ids = 2;
  total_size += 1 * this->ids_size();
  for (int i = 0; i < this->ids_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->ids(i));
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

void Daily::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Daily* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Daily*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Daily::MergeFrom(const Daily& from) {
  GOOGLE_CHECK_NE(&from, this);
  ids_.MergeFrom(from.ids_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ts()) {
      set_ts(from.ts());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Daily::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Daily::CopyFrom(const Daily& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Daily::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->ids())) return false;
  return true;
}

void Daily::Swap(Daily* other) {
  if (other != this) {
    std::swap(ts_, other->ts_);
    ids_.Swap(&other->ids_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Daily::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Daily_descriptor_;
  metadata.reflection = Daily_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace WanBaGift

// @@protoc_insertion_point(global_scope)
