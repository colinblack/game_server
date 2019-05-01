// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WorldRewardConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "WorldRewardConfig.pb.h"

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

namespace WorldRewardConfig {

namespace {

const ::google::protobuf::Descriptor* TimeMultiple_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TimeMultiple_reflection_ = NULL;
const ::google::protobuf::Descriptor* StrongHoldResource_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StrongHoldResource_reflection_ = NULL;
const ::google::protobuf::Descriptor* WorldReward_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  WorldReward_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_WorldRewardConfig_2eproto() {
  protobuf_AddDesc_WorldRewardConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "WorldRewardConfig.proto");
  GOOGLE_CHECK(file != NULL);
  TimeMultiple_descriptor_ = file->message_type(0);
  static const int TimeMultiple_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TimeMultiple, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TimeMultiple, multiple_),
  };
  TimeMultiple_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TimeMultiple_descriptor_,
      TimeMultiple::default_instance_,
      TimeMultiple_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TimeMultiple, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TimeMultiple, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TimeMultiple));
  StrongHoldResource_descriptor_ = file->message_type(1);
  static const int StrongHoldResource_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, ironbase_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, coinbase_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, timemultiple_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, tech_coefficient_),
  };
  StrongHoldResource_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StrongHoldResource_descriptor_,
      StrongHoldResource::default_instance_,
      StrongHoldResource_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StrongHoldResource, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StrongHoldResource));
  WorldReward_descriptor_ = file->message_type(2);
  static const int WorldReward_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WorldReward, stronghold_),
  };
  WorldReward_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      WorldReward_descriptor_,
      WorldReward::default_instance_,
      WorldReward_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WorldReward, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WorldReward, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(WorldReward));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_WorldRewardConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TimeMultiple_descriptor_, &TimeMultiple::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StrongHoldResource_descriptor_, &StrongHoldResource::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    WorldReward_descriptor_, &WorldReward::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_WorldRewardConfig_2eproto() {
  delete TimeMultiple::default_instance_;
  delete TimeMultiple_reflection_;
  delete StrongHoldResource::default_instance_;
  delete StrongHoldResource_reflection_;
  delete WorldReward::default_instance_;
  delete WorldReward_reflection_;
}

void protobuf_AddDesc_WorldRewardConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027WorldRewardConfig.proto\022\021WorldRewardCo"
    "nfig\".\n\014TimeMultiple\022\014\n\004time\030\001 \002(\r\022\020\n\010mu"
    "ltiple\030\002 \002(\r\"\211\001\n\022StrongHoldResource\022\020\n\010i"
    "ronbase\030\001 \002(\r\022\020\n\010coinbase\030\002 \002(\r\0225\n\014timem"
    "ultiple\030\003 \003(\0132\037.WorldRewardConfig.TimeMu"
    "ltiple\022\030\n\020tech_coefficient\030\004 \003(\r\"H\n\013Worl"
    "dReward\0229\n\nstronghold\030\001 \002(\0132%.WorldRewar"
    "dConfig.StrongHoldResource", 306);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "WorldRewardConfig.proto", &protobuf_RegisterTypes);
  TimeMultiple::default_instance_ = new TimeMultiple();
  StrongHoldResource::default_instance_ = new StrongHoldResource();
  WorldReward::default_instance_ = new WorldReward();
  TimeMultiple::default_instance_->InitAsDefaultInstance();
  StrongHoldResource::default_instance_->InitAsDefaultInstance();
  WorldReward::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_WorldRewardConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_WorldRewardConfig_2eproto {
  StaticDescriptorInitializer_WorldRewardConfig_2eproto() {
    protobuf_AddDesc_WorldRewardConfig_2eproto();
  }
} static_descriptor_initializer_WorldRewardConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TimeMultiple::kTimeFieldNumber;
const int TimeMultiple::kMultipleFieldNumber;
#endif  // !_MSC_VER

TimeMultiple::TimeMultiple()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldRewardConfig.TimeMultiple)
}

void TimeMultiple::InitAsDefaultInstance() {
}

TimeMultiple::TimeMultiple(const TimeMultiple& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldRewardConfig.TimeMultiple)
}

void TimeMultiple::SharedCtor() {
  _cached_size_ = 0;
  time_ = 0u;
  multiple_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TimeMultiple::~TimeMultiple() {
  // @@protoc_insertion_point(destructor:WorldRewardConfig.TimeMultiple)
  SharedDtor();
}

void TimeMultiple::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TimeMultiple::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TimeMultiple::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TimeMultiple_descriptor_;
}

const TimeMultiple& TimeMultiple::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldRewardConfig_2eproto();
  return *default_instance_;
}

TimeMultiple* TimeMultiple::default_instance_ = NULL;

TimeMultiple* TimeMultiple::New() const {
  return new TimeMultiple;
}

void TimeMultiple::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TimeMultiple*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(time_, multiple_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TimeMultiple::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldRewardConfig.TimeMultiple)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 time = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &time_)));
          set_has_time();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_multiple;
        break;
      }

      // required uint32 multiple = 2;
      case 2: {
        if (tag == 16) {
         parse_multiple:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &multiple_)));
          set_has_multiple();
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
  // @@protoc_insertion_point(parse_success:WorldRewardConfig.TimeMultiple)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldRewardConfig.TimeMultiple)
  return false;
#undef DO_
}

void TimeMultiple::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldRewardConfig.TimeMultiple)
  // required uint32 time = 1;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->time(), output);
  }

  // required uint32 multiple = 2;
  if (has_multiple()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->multiple(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldRewardConfig.TimeMultiple)
}

::google::protobuf::uint8* TimeMultiple::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldRewardConfig.TimeMultiple)
  // required uint32 time = 1;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->time(), target);
  }

  // required uint32 multiple = 2;
  if (has_multiple()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->multiple(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldRewardConfig.TimeMultiple)
  return target;
}

int TimeMultiple::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 time = 1;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->time());
    }

    // required uint32 multiple = 2;
    if (has_multiple()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->multiple());
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

void TimeMultiple::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TimeMultiple* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TimeMultiple*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TimeMultiple::MergeFrom(const TimeMultiple& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_time()) {
      set_time(from.time());
    }
    if (from.has_multiple()) {
      set_multiple(from.multiple());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TimeMultiple::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TimeMultiple::CopyFrom(const TimeMultiple& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TimeMultiple::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void TimeMultiple::Swap(TimeMultiple* other) {
  if (other != this) {
    std::swap(time_, other->time_);
    std::swap(multiple_, other->multiple_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TimeMultiple::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TimeMultiple_descriptor_;
  metadata.reflection = TimeMultiple_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int StrongHoldResource::kIronbaseFieldNumber;
const int StrongHoldResource::kCoinbaseFieldNumber;
const int StrongHoldResource::kTimemultipleFieldNumber;
const int StrongHoldResource::kTechCoefficientFieldNumber;
#endif  // !_MSC_VER

StrongHoldResource::StrongHoldResource()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldRewardConfig.StrongHoldResource)
}

void StrongHoldResource::InitAsDefaultInstance() {
}

StrongHoldResource::StrongHoldResource(const StrongHoldResource& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldRewardConfig.StrongHoldResource)
}

void StrongHoldResource::SharedCtor() {
  _cached_size_ = 0;
  ironbase_ = 0u;
  coinbase_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StrongHoldResource::~StrongHoldResource() {
  // @@protoc_insertion_point(destructor:WorldRewardConfig.StrongHoldResource)
  SharedDtor();
}

void StrongHoldResource::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StrongHoldResource::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StrongHoldResource::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StrongHoldResource_descriptor_;
}

const StrongHoldResource& StrongHoldResource::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldRewardConfig_2eproto();
  return *default_instance_;
}

StrongHoldResource* StrongHoldResource::default_instance_ = NULL;

StrongHoldResource* StrongHoldResource::New() const {
  return new StrongHoldResource;
}

void StrongHoldResource::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<StrongHoldResource*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(ironbase_, coinbase_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  timemultiple_.Clear();
  tech_coefficient_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StrongHoldResource::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldRewardConfig.StrongHoldResource)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 ironbase = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ironbase_)));
          set_has_ironbase();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_coinbase;
        break;
      }

      // required uint32 coinbase = 2;
      case 2: {
        if (tag == 16) {
         parse_coinbase:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &coinbase_)));
          set_has_coinbase();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_timemultiple;
        break;
      }

      // repeated .WorldRewardConfig.TimeMultiple timemultiple = 3;
      case 3: {
        if (tag == 26) {
         parse_timemultiple:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_timemultiple()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_timemultiple;
        if (input->ExpectTag(32)) goto parse_tech_coefficient;
        break;
      }

      // repeated uint32 tech_coefficient = 4;
      case 4: {
        if (tag == 32) {
         parse_tech_coefficient:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 32, input, this->mutable_tech_coefficient())));
        } else if (tag == 34) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_tech_coefficient())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_tech_coefficient;
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
  // @@protoc_insertion_point(parse_success:WorldRewardConfig.StrongHoldResource)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldRewardConfig.StrongHoldResource)
  return false;
#undef DO_
}

void StrongHoldResource::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldRewardConfig.StrongHoldResource)
  // required uint32 ironbase = 1;
  if (has_ironbase()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->ironbase(), output);
  }

  // required uint32 coinbase = 2;
  if (has_coinbase()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->coinbase(), output);
  }

  // repeated .WorldRewardConfig.TimeMultiple timemultiple = 3;
  for (int i = 0; i < this->timemultiple_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->timemultiple(i), output);
  }

  // repeated uint32 tech_coefficient = 4;
  for (int i = 0; i < this->tech_coefficient_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      4, this->tech_coefficient(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldRewardConfig.StrongHoldResource)
}

::google::protobuf::uint8* StrongHoldResource::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldRewardConfig.StrongHoldResource)
  // required uint32 ironbase = 1;
  if (has_ironbase()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->ironbase(), target);
  }

  // required uint32 coinbase = 2;
  if (has_coinbase()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->coinbase(), target);
  }

  // repeated .WorldRewardConfig.TimeMultiple timemultiple = 3;
  for (int i = 0; i < this->timemultiple_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->timemultiple(i), target);
  }

  // repeated uint32 tech_coefficient = 4;
  for (int i = 0; i < this->tech_coefficient_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(4, this->tech_coefficient(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldRewardConfig.StrongHoldResource)
  return target;
}

int StrongHoldResource::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 ironbase = 1;
    if (has_ironbase()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ironbase());
    }

    // required uint32 coinbase = 2;
    if (has_coinbase()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->coinbase());
    }

  }
  // repeated .WorldRewardConfig.TimeMultiple timemultiple = 3;
  total_size += 1 * this->timemultiple_size();
  for (int i = 0; i < this->timemultiple_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->timemultiple(i));
  }

  // repeated uint32 tech_coefficient = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->tech_coefficient_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->tech_coefficient(i));
    }
    total_size += 1 * this->tech_coefficient_size() + data_size;
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

void StrongHoldResource::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StrongHoldResource* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StrongHoldResource*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StrongHoldResource::MergeFrom(const StrongHoldResource& from) {
  GOOGLE_CHECK_NE(&from, this);
  timemultiple_.MergeFrom(from.timemultiple_);
  tech_coefficient_.MergeFrom(from.tech_coefficient_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ironbase()) {
      set_ironbase(from.ironbase());
    }
    if (from.has_coinbase()) {
      set_coinbase(from.coinbase());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StrongHoldResource::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StrongHoldResource::CopyFrom(const StrongHoldResource& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StrongHoldResource::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->timemultiple())) return false;
  return true;
}

void StrongHoldResource::Swap(StrongHoldResource* other) {
  if (other != this) {
    std::swap(ironbase_, other->ironbase_);
    std::swap(coinbase_, other->coinbase_);
    timemultiple_.Swap(&other->timemultiple_);
    tech_coefficient_.Swap(&other->tech_coefficient_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata StrongHoldResource::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StrongHoldResource_descriptor_;
  metadata.reflection = StrongHoldResource_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int WorldReward::kStrongholdFieldNumber;
#endif  // !_MSC_VER

WorldReward::WorldReward()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WorldRewardConfig.WorldReward)
}

void WorldReward::InitAsDefaultInstance() {
  stronghold_ = const_cast< ::WorldRewardConfig::StrongHoldResource*>(&::WorldRewardConfig::StrongHoldResource::default_instance());
}

WorldReward::WorldReward(const WorldReward& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:WorldRewardConfig.WorldReward)
}

void WorldReward::SharedCtor() {
  _cached_size_ = 0;
  stronghold_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

WorldReward::~WorldReward() {
  // @@protoc_insertion_point(destructor:WorldRewardConfig.WorldReward)
  SharedDtor();
}

void WorldReward::SharedDtor() {
  if (this != default_instance_) {
    delete stronghold_;
  }
}

void WorldReward::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* WorldReward::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return WorldReward_descriptor_;
}

const WorldReward& WorldReward::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldRewardConfig_2eproto();
  return *default_instance_;
}

WorldReward* WorldReward::default_instance_ = NULL;

WorldReward* WorldReward::New() const {
  return new WorldReward;
}

void WorldReward::Clear() {
  if (has_stronghold()) {
    if (stronghold_ != NULL) stronghold_->::WorldRewardConfig::StrongHoldResource::Clear();
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool WorldReward::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WorldRewardConfig.WorldReward)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .WorldRewardConfig.StrongHoldResource stronghold = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_stronghold()));
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
  // @@protoc_insertion_point(parse_success:WorldRewardConfig.WorldReward)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WorldRewardConfig.WorldReward)
  return false;
#undef DO_
}

void WorldReward::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WorldRewardConfig.WorldReward)
  // required .WorldRewardConfig.StrongHoldResource stronghold = 1;
  if (has_stronghold()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->stronghold(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WorldRewardConfig.WorldReward)
}

::google::protobuf::uint8* WorldReward::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WorldRewardConfig.WorldReward)
  // required .WorldRewardConfig.StrongHoldResource stronghold = 1;
  if (has_stronghold()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->stronghold(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WorldRewardConfig.WorldReward)
  return target;
}

int WorldReward::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .WorldRewardConfig.StrongHoldResource stronghold = 1;
    if (has_stronghold()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->stronghold());
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

void WorldReward::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const WorldReward* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const WorldReward*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void WorldReward::MergeFrom(const WorldReward& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_stronghold()) {
      mutable_stronghold()->::WorldRewardConfig::StrongHoldResource::MergeFrom(from.stronghold());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void WorldReward::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WorldReward::CopyFrom(const WorldReward& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WorldReward::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (has_stronghold()) {
    if (!this->stronghold().IsInitialized()) return false;
  }
  return true;
}

void WorldReward::Swap(WorldReward* other) {
  if (other != this) {
    std::swap(stronghold_, other->stronghold_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata WorldReward::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = WorldReward_descriptor_;
  metadata.reflection = WorldReward_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace WorldRewardConfig

// @@protoc_insertion_point(global_scope)
