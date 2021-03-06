// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AchievementConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "AchievementConfig.pb.h"

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

namespace AchievementConfig {

namespace {

const ::google::protobuf::Descriptor* Achievement_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Achievement_reflection_ = NULL;
const ::google::protobuf::Descriptor* AchievementList_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AchievementList_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_AchievementConfig_2eproto() {
  protobuf_AddDesc_AchievementConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "AchievementConfig.proto");
  GOOGLE_CHECK(file != NULL);
  Achievement_descriptor_ = file->message_type(0);
  static const int Achievement_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, achitype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, subtype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, condition_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, reward_),
  };
  Achievement_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Achievement_descriptor_,
      Achievement::default_instance_,
      Achievement_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Achievement, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Achievement));
  AchievementList_descriptor_ = file->message_type(1);
  static const int AchievementList_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AchievementList, achievements_),
  };
  AchievementList_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AchievementList_descriptor_,
      AchievementList::default_instance_,
      AchievementList_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AchievementList, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AchievementList, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AchievementList));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_AchievementConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Achievement_descriptor_, &Achievement::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AchievementList_descriptor_, &AchievementList::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_AchievementConfig_2eproto() {
  delete Achievement::default_instance_;
  delete Achievement_reflection_;
  delete AchievementList::default_instance_;
  delete AchievementList_reflection_;
}

void protobuf_AddDesc_AchievementConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::RewardConfig::protobuf_AddDesc_RewardConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027AchievementConfig.proto\022\021AchievementCo"
    "nfig\032\022RewardConfig.proto\"\203\001\n\013Achievement"
    "\022\n\n\002id\030\001 \002(\r\022\020\n\010achitype\030\002 \002(\r\022\014\n\004type\030\003"
    " \002(\r\022\017\n\007subtype\030\004 \001(\r\022\021\n\tcondition\030\005 \003(\r"
    "\022$\n\006reward\030\006 \003(\0132\024.RewardConfig.Reward\"G"
    "\n\017AchievementList\0224\n\014achievements\030\001 \003(\0132"
    "\036.AchievementConfig.Achievement", 271);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "AchievementConfig.proto", &protobuf_RegisterTypes);
  Achievement::default_instance_ = new Achievement();
  AchievementList::default_instance_ = new AchievementList();
  Achievement::default_instance_->InitAsDefaultInstance();
  AchievementList::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_AchievementConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_AchievementConfig_2eproto {
  StaticDescriptorInitializer_AchievementConfig_2eproto() {
    protobuf_AddDesc_AchievementConfig_2eproto();
  }
} static_descriptor_initializer_AchievementConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Achievement::kIdFieldNumber;
const int Achievement::kAchitypeFieldNumber;
const int Achievement::kTypeFieldNumber;
const int Achievement::kSubtypeFieldNumber;
const int Achievement::kConditionFieldNumber;
const int Achievement::kRewardFieldNumber;
#endif  // !_MSC_VER

Achievement::Achievement()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AchievementConfig.Achievement)
}

void Achievement::InitAsDefaultInstance() {
}

Achievement::Achievement(const Achievement& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AchievementConfig.Achievement)
}

void Achievement::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  achitype_ = 0u;
  type_ = 0u;
  subtype_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Achievement::~Achievement() {
  // @@protoc_insertion_point(destructor:AchievementConfig.Achievement)
  SharedDtor();
}

void Achievement::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Achievement::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Achievement::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Achievement_descriptor_;
}

const Achievement& Achievement::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_AchievementConfig_2eproto();
  return *default_instance_;
}

Achievement* Achievement::default_instance_ = NULL;

Achievement* Achievement::New() const {
  return new Achievement;
}

void Achievement::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Achievement*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, subtype_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  condition_.Clear();
  reward_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Achievement::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AchievementConfig.Achievement)
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
        if (input->ExpectTag(16)) goto parse_achitype;
        break;
      }

      // required uint32 achitype = 2;
      case 2: {
        if (tag == 16) {
         parse_achitype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &achitype_)));
          set_has_achitype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_type;
        break;
      }

      // required uint32 type = 3;
      case 3: {
        if (tag == 24) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_subtype;
        break;
      }

      // optional uint32 subtype = 4;
      case 4: {
        if (tag == 32) {
         parse_subtype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &subtype_)));
          set_has_subtype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_condition;
        break;
      }

      // repeated uint32 condition = 5;
      case 5: {
        if (tag == 40) {
         parse_condition:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 40, input, this->mutable_condition())));
        } else if (tag == 42) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_condition())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_condition;
        if (input->ExpectTag(50)) goto parse_reward;
        break;
      }

      // repeated .RewardConfig.Reward reward = 6;
      case 6: {
        if (tag == 50) {
         parse_reward:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_reward()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_reward;
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
  // @@protoc_insertion_point(parse_success:AchievementConfig.Achievement)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AchievementConfig.Achievement)
  return false;
#undef DO_
}

void Achievement::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AchievementConfig.Achievement)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 achitype = 2;
  if (has_achitype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->achitype(), output);
  }

  // required uint32 type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->type(), output);
  }

  // optional uint32 subtype = 4;
  if (has_subtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->subtype(), output);
  }

  // repeated uint32 condition = 5;
  for (int i = 0; i < this->condition_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      5, this->condition(i), output);
  }

  // repeated .RewardConfig.Reward reward = 6;
  for (int i = 0; i < this->reward_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->reward(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AchievementConfig.Achievement)
}

::google::protobuf::uint8* Achievement::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AchievementConfig.Achievement)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 achitype = 2;
  if (has_achitype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->achitype(), target);
  }

  // required uint32 type = 3;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->type(), target);
  }

  // optional uint32 subtype = 4;
  if (has_subtype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->subtype(), target);
  }

  // repeated uint32 condition = 5;
  for (int i = 0; i < this->condition_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(5, this->condition(i), target);
  }

  // repeated .RewardConfig.Reward reward = 6;
  for (int i = 0; i < this->reward_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->reward(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AchievementConfig.Achievement)
  return target;
}

int Achievement::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 achitype = 2;
    if (has_achitype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->achitype());
    }

    // required uint32 type = 3;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

    // optional uint32 subtype = 4;
    if (has_subtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->subtype());
    }

  }
  // repeated uint32 condition = 5;
  {
    int data_size = 0;
    for (int i = 0; i < this->condition_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->condition(i));
    }
    total_size += 1 * this->condition_size() + data_size;
  }

  // repeated .RewardConfig.Reward reward = 6;
  total_size += 1 * this->reward_size();
  for (int i = 0; i < this->reward_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->reward(i));
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

void Achievement::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Achievement* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Achievement*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Achievement::MergeFrom(const Achievement& from) {
  GOOGLE_CHECK_NE(&from, this);
  condition_.MergeFrom(from.condition_);
  reward_.MergeFrom(from.reward_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_achitype()) {
      set_achitype(from.achitype());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_subtype()) {
      set_subtype(from.subtype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Achievement::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Achievement::CopyFrom(const Achievement& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Achievement::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->reward())) return false;
  return true;
}

void Achievement::Swap(Achievement* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(achitype_, other->achitype_);
    std::swap(type_, other->type_);
    std::swap(subtype_, other->subtype_);
    condition_.Swap(&other->condition_);
    reward_.Swap(&other->reward_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Achievement::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Achievement_descriptor_;
  metadata.reflection = Achievement_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AchievementList::kAchievementsFieldNumber;
#endif  // !_MSC_VER

AchievementList::AchievementList()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AchievementConfig.AchievementList)
}

void AchievementList::InitAsDefaultInstance() {
}

AchievementList::AchievementList(const AchievementList& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AchievementConfig.AchievementList)
}

void AchievementList::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AchievementList::~AchievementList() {
  // @@protoc_insertion_point(destructor:AchievementConfig.AchievementList)
  SharedDtor();
}

void AchievementList::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AchievementList::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AchievementList::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AchievementList_descriptor_;
}

const AchievementList& AchievementList::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_AchievementConfig_2eproto();
  return *default_instance_;
}

AchievementList* AchievementList::default_instance_ = NULL;

AchievementList* AchievementList::New() const {
  return new AchievementList;
}

void AchievementList::Clear() {
  achievements_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AchievementList::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AchievementConfig.AchievementList)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .AchievementConfig.Achievement achievements = 1;
      case 1: {
        if (tag == 10) {
         parse_achievements:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_achievements()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_achievements;
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
  // @@protoc_insertion_point(parse_success:AchievementConfig.AchievementList)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AchievementConfig.AchievementList)
  return false;
#undef DO_
}

void AchievementList::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AchievementConfig.AchievementList)
  // repeated .AchievementConfig.Achievement achievements = 1;
  for (int i = 0; i < this->achievements_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->achievements(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AchievementConfig.AchievementList)
}

::google::protobuf::uint8* AchievementList::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AchievementConfig.AchievementList)
  // repeated .AchievementConfig.Achievement achievements = 1;
  for (int i = 0; i < this->achievements_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->achievements(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AchievementConfig.AchievementList)
  return target;
}

int AchievementList::ByteSize() const {
  int total_size = 0;

  // repeated .AchievementConfig.Achievement achievements = 1;
  total_size += 1 * this->achievements_size();
  for (int i = 0; i < this->achievements_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->achievements(i));
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

void AchievementList::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AchievementList* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AchievementList*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AchievementList::MergeFrom(const AchievementList& from) {
  GOOGLE_CHECK_NE(&from, this);
  achievements_.MergeFrom(from.achievements_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AchievementList::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AchievementList::CopyFrom(const AchievementList& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AchievementList::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->achievements())) return false;
  return true;
}

void AchievementList::Swap(AchievementList* other) {
  if (other != this) {
    achievements_.Swap(&other->achievements_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AchievementList::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AchievementList_descriptor_;
  metadata.reflection = AchievementList_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AchievementConfig

// @@protoc_insertion_point(global_scope)
