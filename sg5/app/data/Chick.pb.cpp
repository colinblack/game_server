// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Chick.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Chick.pb.h"

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

namespace Chick {

namespace {

const ::google::protobuf::Descriptor* ChickHero_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ChickHero_reflection_ = NULL;
const ::google::protobuf::Descriptor* ChickUser_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ChickUser_reflection_ = NULL;
const ::google::protobuf::Descriptor* Chick_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Chick_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Chick_2eproto() {
  protobuf_AddDesc_Chick_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Chick.proto");
  GOOGLE_CHECK(file != NULL);
  ChickHero_descriptor_ = file->message_type(0);
  static const int ChickHero_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickHero, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickHero, property_),
  };
  ChickHero_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ChickHero_descriptor_,
      ChickHero::default_instance_,
      ChickHero_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickHero, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickHero, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ChickHero));
  ChickUser_descriptor_ = file->message_type(1);
  static const int ChickUser_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, uid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, fig_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, hero_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, zone_),
  };
  ChickUser_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ChickUser_descriptor_,
      ChickUser::default_instance_,
      ChickUser_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChickUser, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ChickUser));
  Chick_descriptor_ = file->message_type(2);
  static const int Chick_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chick, user_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chick, reg_),
  };
  Chick_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Chick_descriptor_,
      Chick::default_instance_,
      Chick_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chick, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chick, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Chick));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Chick_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ChickHero_descriptor_, &ChickHero::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ChickUser_descriptor_, &ChickUser::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Chick_descriptor_, &Chick::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Chick_2eproto() {
  delete ChickHero::default_instance_;
  delete ChickHero_reflection_;
  delete ChickUser::default_instance_;
  delete ChickUser_reflection_;
  delete Chick::default_instance_;
  delete Chick_reflection_;
}

void protobuf_AddDesc_Chick_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013Chick.proto\022\005Chick\",\n\tChickHero\022\r\n\005lev"
    "el\030\001 \002(\r\022\020\n\010property\030\002 \003(\r\"p\n\tChickUser\022"
    "\013\n\003uid\030\001 \002(\r\022\014\n\004name\030\002 \002(\014\022\013\n\003fig\030\003 \002(\014\022"
    "\r\n\005level\030\004 \002(\r\022\036\n\004hero\030\005 \002(\0132\020.Chick.Chi"
    "ckHero\022\014\n\004zone\030\006 \002(\r\"4\n\005Chick\022\036\n\004user\030\001 "
    "\003(\0132\020.Chick.ChickUser\022\013\n\003reg\030\002 \002(\010", 234);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Chick.proto", &protobuf_RegisterTypes);
  ChickHero::default_instance_ = new ChickHero();
  ChickUser::default_instance_ = new ChickUser();
  Chick::default_instance_ = new Chick();
  ChickHero::default_instance_->InitAsDefaultInstance();
  ChickUser::default_instance_->InitAsDefaultInstance();
  Chick::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Chick_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Chick_2eproto {
  StaticDescriptorInitializer_Chick_2eproto() {
    protobuf_AddDesc_Chick_2eproto();
  }
} static_descriptor_initializer_Chick_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ChickHero::kLevelFieldNumber;
const int ChickHero::kPropertyFieldNumber;
#endif  // !_MSC_VER

ChickHero::ChickHero()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Chick.ChickHero)
}

void ChickHero::InitAsDefaultInstance() {
}

ChickHero::ChickHero(const ChickHero& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Chick.ChickHero)
}

void ChickHero::SharedCtor() {
  _cached_size_ = 0;
  level_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ChickHero::~ChickHero() {
  // @@protoc_insertion_point(destructor:Chick.ChickHero)
  SharedDtor();
}

void ChickHero::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ChickHero::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChickHero::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ChickHero_descriptor_;
}

const ChickHero& ChickHero::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Chick_2eproto();
  return *default_instance_;
}

ChickHero* ChickHero::default_instance_ = NULL;

ChickHero* ChickHero::New() const {
  return new ChickHero;
}

void ChickHero::Clear() {
  level_ = 0u;
  property_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ChickHero::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Chick.ChickHero)
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
        if (input->ExpectTag(16)) goto parse_property;
        break;
      }

      // repeated uint32 property = 2;
      case 2: {
        if (tag == 16) {
         parse_property:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16, input, this->mutable_property())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_property())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_property;
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
  // @@protoc_insertion_point(parse_success:Chick.ChickHero)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Chick.ChickHero)
  return false;
#undef DO_
}

void ChickHero::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Chick.ChickHero)
  // required uint32 level = 1;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->level(), output);
  }

  // repeated uint32 property = 2;
  for (int i = 0; i < this->property_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->property(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Chick.ChickHero)
}

::google::protobuf::uint8* ChickHero::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Chick.ChickHero)
  // required uint32 level = 1;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->level(), target);
  }

  // repeated uint32 property = 2;
  for (int i = 0; i < this->property_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(2, this->property(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Chick.ChickHero)
  return target;
}

int ChickHero::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 level = 1;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

  }
  // repeated uint32 property = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->property_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->property(i));
    }
    total_size += 1 * this->property_size() + data_size;
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

void ChickHero::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ChickHero* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ChickHero*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ChickHero::MergeFrom(const ChickHero& from) {
  GOOGLE_CHECK_NE(&from, this);
  property_.MergeFrom(from.property_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_level()) {
      set_level(from.level());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ChickHero::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChickHero::CopyFrom(const ChickHero& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChickHero::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ChickHero::Swap(ChickHero* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    property_.Swap(&other->property_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ChickHero::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ChickHero_descriptor_;
  metadata.reflection = ChickHero_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ChickUser::kUidFieldNumber;
const int ChickUser::kNameFieldNumber;
const int ChickUser::kFigFieldNumber;
const int ChickUser::kLevelFieldNumber;
const int ChickUser::kHeroFieldNumber;
const int ChickUser::kZoneFieldNumber;
#endif  // !_MSC_VER

ChickUser::ChickUser()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Chick.ChickUser)
}

void ChickUser::InitAsDefaultInstance() {
  hero_ = const_cast< ::Chick::ChickHero*>(&::Chick::ChickHero::default_instance());
}

ChickUser::ChickUser(const ChickUser& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Chick.ChickUser)
}

void ChickUser::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  uid_ = 0u;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  fig_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  level_ = 0u;
  hero_ = NULL;
  zone_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ChickUser::~ChickUser() {
  // @@protoc_insertion_point(destructor:Chick.ChickUser)
  SharedDtor();
}

void ChickUser::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (fig_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete fig_;
  }
  if (this != default_instance_) {
    delete hero_;
  }
}

void ChickUser::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChickUser::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ChickUser_descriptor_;
}

const ChickUser& ChickUser::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Chick_2eproto();
  return *default_instance_;
}

ChickUser* ChickUser::default_instance_ = NULL;

ChickUser* ChickUser::New() const {
  return new ChickUser;
}

void ChickUser::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ChickUser*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 63) {
    ZR_(uid_, level_);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
    if (has_fig()) {
      if (fig_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        fig_->clear();
      }
    }
    if (has_hero()) {
      if (hero_ != NULL) hero_->::Chick::ChickHero::Clear();
    }
    zone_ = 0u;
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ChickUser::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Chick.ChickUser)
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
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // required bytes name = 2;
      case 2: {
        if (tag == 18) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_name()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_fig;
        break;
      }

      // required bytes fig = 3;
      case 3: {
        if (tag == 26) {
         parse_fig:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_fig()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_level;
        break;
      }

      // required uint32 level = 4;
      case 4: {
        if (tag == 32) {
         parse_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
          set_has_level();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_hero;
        break;
      }

      // required .Chick.ChickHero hero = 5;
      case 5: {
        if (tag == 42) {
         parse_hero:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_hero()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_zone;
        break;
      }

      // required uint32 zone = 6;
      case 6: {
        if (tag == 48) {
         parse_zone:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &zone_)));
          set_has_zone();
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
  // @@protoc_insertion_point(parse_success:Chick.ChickUser)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Chick.ChickUser)
  return false;
#undef DO_
}

void ChickUser::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Chick.ChickUser)
  // required uint32 uid = 1;
  if (has_uid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->uid(), output);
  }

  // required bytes name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->name(), output);
  }

  // required bytes fig = 3;
  if (has_fig()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->fig(), output);
  }

  // required uint32 level = 4;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->level(), output);
  }

  // required .Chick.ChickHero hero = 5;
  if (has_hero()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->hero(), output);
  }

  // required uint32 zone = 6;
  if (has_zone()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->zone(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Chick.ChickUser)
}

::google::protobuf::uint8* ChickUser::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Chick.ChickUser)
  // required uint32 uid = 1;
  if (has_uid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->uid(), target);
  }

  // required bytes name = 2;
  if (has_name()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->name(), target);
  }

  // required bytes fig = 3;
  if (has_fig()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->fig(), target);
  }

  // required uint32 level = 4;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->level(), target);
  }

  // required .Chick.ChickHero hero = 5;
  if (has_hero()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->hero(), target);
  }

  // required uint32 zone = 6;
  if (has_zone()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->zone(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Chick.ChickUser)
  return target;
}

int ChickUser::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 uid = 1;
    if (has_uid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->uid());
    }

    // required bytes name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->name());
    }

    // required bytes fig = 3;
    if (has_fig()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->fig());
    }

    // required uint32 level = 4;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

    // required .Chick.ChickHero hero = 5;
    if (has_hero()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->hero());
    }

    // required uint32 zone = 6;
    if (has_zone()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->zone());
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

void ChickUser::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ChickUser* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ChickUser*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ChickUser::MergeFrom(const ChickUser& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uid()) {
      set_uid(from.uid());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_fig()) {
      set_fig(from.fig());
    }
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_hero()) {
      mutable_hero()->::Chick::ChickHero::MergeFrom(from.hero());
    }
    if (from.has_zone()) {
      set_zone(from.zone());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ChickUser::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChickUser::CopyFrom(const ChickUser& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChickUser::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;

  if (has_hero()) {
    if (!this->hero().IsInitialized()) return false;
  }
  return true;
}

void ChickUser::Swap(ChickUser* other) {
  if (other != this) {
    std::swap(uid_, other->uid_);
    std::swap(name_, other->name_);
    std::swap(fig_, other->fig_);
    std::swap(level_, other->level_);
    std::swap(hero_, other->hero_);
    std::swap(zone_, other->zone_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ChickUser::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ChickUser_descriptor_;
  metadata.reflection = ChickUser_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Chick::kUserFieldNumber;
const int Chick::kRegFieldNumber;
#endif  // !_MSC_VER

Chick::Chick()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Chick.Chick)
}

void Chick::InitAsDefaultInstance() {
}

Chick::Chick(const Chick& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Chick.Chick)
}

void Chick::SharedCtor() {
  _cached_size_ = 0;
  reg_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Chick::~Chick() {
  // @@protoc_insertion_point(destructor:Chick.Chick)
  SharedDtor();
}

void Chick::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Chick::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Chick::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Chick_descriptor_;
}

const Chick& Chick::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Chick_2eproto();
  return *default_instance_;
}

Chick* Chick::default_instance_ = NULL;

Chick* Chick::New() const {
  return new Chick;
}

void Chick::Clear() {
  reg_ = false;
  user_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Chick::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Chick.Chick)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Chick.ChickUser user = 1;
      case 1: {
        if (tag == 10) {
         parse_user:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_user()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_user;
        if (input->ExpectTag(16)) goto parse_reg;
        break;
      }

      // required bool reg = 2;
      case 2: {
        if (tag == 16) {
         parse_reg:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &reg_)));
          set_has_reg();
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
  // @@protoc_insertion_point(parse_success:Chick.Chick)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Chick.Chick)
  return false;
#undef DO_
}

void Chick::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Chick.Chick)
  // repeated .Chick.ChickUser user = 1;
  for (int i = 0; i < this->user_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->user(i), output);
  }

  // required bool reg = 2;
  if (has_reg()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->reg(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Chick.Chick)
}

::google::protobuf::uint8* Chick::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Chick.Chick)
  // repeated .Chick.ChickUser user = 1;
  for (int i = 0; i < this->user_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->user(i), target);
  }

  // required bool reg = 2;
  if (has_reg()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->reg(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Chick.Chick)
  return target;
}

int Chick::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required bool reg = 2;
    if (has_reg()) {
      total_size += 1 + 1;
    }

  }
  // repeated .Chick.ChickUser user = 1;
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

void Chick::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Chick* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Chick*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Chick::MergeFrom(const Chick& from) {
  GOOGLE_CHECK_NE(&from, this);
  user_.MergeFrom(from.user_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_reg()) {
      set_reg(from.reg());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Chick::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Chick::CopyFrom(const Chick& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Chick::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->user())) return false;
  return true;
}

void Chick::Swap(Chick* other) {
  if (other != this) {
    user_.Swap(&other->user_);
    std::swap(reg_, other->reg_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Chick::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Chick_descriptor_;
  metadata.reflection = Chick_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Chick

// @@protoc_insertion_point(global_scope)
