// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DailyMissionConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "DailyMissionConfig.pb.h"

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

namespace DailyMissionConfig {

namespace {

const ::google::protobuf::Descriptor* DailyMission_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DailyMission_reflection_ = NULL;
const ::google::protobuf::Descriptor* DailyMissionsItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DailyMissionsItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* DailyMissonItemList_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DailyMissonItemList_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_DailyMissionConfig_2eproto() {
  protobuf_AddDesc_DailyMissionConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "DailyMissionConfig.proto");
  GOOGLE_CHECK(file != NULL);
  DailyMission_descriptor_ = file->message_type(0);
  static const int DailyMission_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, rate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, subtype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, count_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, starrate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, starcoefficient_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, exp_),
  };
  DailyMission_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DailyMission_descriptor_,
      DailyMission::default_instance_,
      DailyMission_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMission, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DailyMission));
  DailyMissionsItem_descriptor_ = file->message_type(1);
  static const int DailyMissionsItem_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissionsItem, tech_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissionsItem, missions_),
  };
  DailyMissionsItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DailyMissionsItem_descriptor_,
      DailyMissionsItem::default_instance_,
      DailyMissionsItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissionsItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissionsItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DailyMissionsItem));
  DailyMissonItemList_descriptor_ = file->message_type(2);
  static const int DailyMissonItemList_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissonItemList, daily_missions_),
  };
  DailyMissonItemList_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DailyMissonItemList_descriptor_,
      DailyMissonItemList::default_instance_,
      DailyMissonItemList_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissonItemList, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyMissonItemList, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DailyMissonItemList));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_DailyMissionConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DailyMission_descriptor_, &DailyMission::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DailyMissionsItem_descriptor_, &DailyMissionsItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DailyMissonItemList_descriptor_, &DailyMissonItemList::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_DailyMissionConfig_2eproto() {
  delete DailyMission::default_instance_;
  delete DailyMission_reflection_;
  delete DailyMissionsItem::default_instance_;
  delete DailyMissionsItem_reflection_;
  delete DailyMissonItemList::default_instance_;
  delete DailyMissonItemList_reflection_;
}

void protobuf_AddDesc_DailyMissionConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030DailyMissionConfig.proto\022\022DailyMission"
    "Config\"\216\001\n\014DailyMission\022\n\n\002id\030\001 \002(\r\022\014\n\004r"
    "ate\030\002 \002(\r\022\014\n\004type\030\003 \002(\r\022\017\n\007subtype\030\004 \002(\r"
    "\022\r\n\005count\030\005 \002(\r\022\020\n\010starrate\030\006 \003(\r\022\027\n\017sta"
    "rcoefficient\030\007 \003(\001\022\013\n\003exp\030\010 \002(\r\"U\n\021Daily"
    "MissionsItem\022\014\n\004tech\030\001 \002(\r\0222\n\010missions\030\002"
    " \003(\0132 .DailyMissionConfig.DailyMission\"T"
    "\n\023DailyMissonItemList\022=\n\016daily_missions\030"
    "\001 \003(\0132%.DailyMissionConfig.DailyMissions"
    "Item", 364);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "DailyMissionConfig.proto", &protobuf_RegisterTypes);
  DailyMission::default_instance_ = new DailyMission();
  DailyMissionsItem::default_instance_ = new DailyMissionsItem();
  DailyMissonItemList::default_instance_ = new DailyMissonItemList();
  DailyMission::default_instance_->InitAsDefaultInstance();
  DailyMissionsItem::default_instance_->InitAsDefaultInstance();
  DailyMissonItemList::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_DailyMissionConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_DailyMissionConfig_2eproto {
  StaticDescriptorInitializer_DailyMissionConfig_2eproto() {
    protobuf_AddDesc_DailyMissionConfig_2eproto();
  }
} static_descriptor_initializer_DailyMissionConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DailyMission::kIdFieldNumber;
const int DailyMission::kRateFieldNumber;
const int DailyMission::kTypeFieldNumber;
const int DailyMission::kSubtypeFieldNumber;
const int DailyMission::kCountFieldNumber;
const int DailyMission::kStarrateFieldNumber;
const int DailyMission::kStarcoefficientFieldNumber;
const int DailyMission::kExpFieldNumber;
#endif  // !_MSC_VER

DailyMission::DailyMission()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:DailyMissionConfig.DailyMission)
}

void DailyMission::InitAsDefaultInstance() {
}

DailyMission::DailyMission(const DailyMission& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:DailyMissionConfig.DailyMission)
}

void DailyMission::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  rate_ = 0u;
  type_ = 0u;
  subtype_ = 0u;
  count_ = 0u;
  exp_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyMission::~DailyMission() {
  // @@protoc_insertion_point(destructor:DailyMissionConfig.DailyMission)
  SharedDtor();
}

void DailyMission::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DailyMission::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DailyMission::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DailyMission_descriptor_;
}

const DailyMission& DailyMission::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DailyMissionConfig_2eproto();
  return *default_instance_;
}

DailyMission* DailyMission::default_instance_ = NULL;

DailyMission* DailyMission::New() const {
  return new DailyMission;
}

void DailyMission::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<DailyMission*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 159) {
    ZR_(id_, subtype_);
    ZR_(count_, exp_);
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  starrate_.Clear();
  starcoefficient_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DailyMission::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:DailyMissionConfig.DailyMission)
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
        if (input->ExpectTag(16)) goto parse_rate;
        break;
      }

      // required uint32 rate = 2;
      case 2: {
        if (tag == 16) {
         parse_rate:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rate_)));
          set_has_rate();
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

      // required uint32 subtype = 4;
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
        if (input->ExpectTag(40)) goto parse_count;
        break;
      }

      // required uint32 count = 5;
      case 5: {
        if (tag == 40) {
         parse_count:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &count_)));
          set_has_count();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_starrate;
        break;
      }

      // repeated uint32 starrate = 6;
      case 6: {
        if (tag == 48) {
         parse_starrate:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 48, input, this->mutable_starrate())));
        } else if (tag == 50) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_starrate())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_starrate;
        if (input->ExpectTag(57)) goto parse_starcoefficient;
        break;
      }

      // repeated double starcoefficient = 7;
      case 7: {
        if (tag == 57) {
         parse_starcoefficient:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 1, 57, input, this->mutable_starcoefficient())));
        } else if (tag == 58) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, this->mutable_starcoefficient())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_starcoefficient;
        if (input->ExpectTag(64)) goto parse_exp;
        break;
      }

      // required uint32 exp = 8;
      case 8: {
        if (tag == 64) {
         parse_exp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &exp_)));
          set_has_exp();
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
  // @@protoc_insertion_point(parse_success:DailyMissionConfig.DailyMission)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:DailyMissionConfig.DailyMission)
  return false;
#undef DO_
}

void DailyMission::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:DailyMissionConfig.DailyMission)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 rate = 2;
  if (has_rate()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->rate(), output);
  }

  // required uint32 type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->type(), output);
  }

  // required uint32 subtype = 4;
  if (has_subtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->subtype(), output);
  }

  // required uint32 count = 5;
  if (has_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->count(), output);
  }

  // repeated uint32 starrate = 6;
  for (int i = 0; i < this->starrate_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      6, this->starrate(i), output);
  }

  // repeated double starcoefficient = 7;
  for (int i = 0; i < this->starcoefficient_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(
      7, this->starcoefficient(i), output);
  }

  // required uint32 exp = 8;
  if (has_exp()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->exp(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:DailyMissionConfig.DailyMission)
}

::google::protobuf::uint8* DailyMission::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:DailyMissionConfig.DailyMission)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 rate = 2;
  if (has_rate()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->rate(), target);
  }

  // required uint32 type = 3;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->type(), target);
  }

  // required uint32 subtype = 4;
  if (has_subtype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->subtype(), target);
  }

  // required uint32 count = 5;
  if (has_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->count(), target);
  }

  // repeated uint32 starrate = 6;
  for (int i = 0; i < this->starrate_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(6, this->starrate(i), target);
  }

  // repeated double starcoefficient = 7;
  for (int i = 0; i < this->starcoefficient_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteDoubleToArray(7, this->starcoefficient(i), target);
  }

  // required uint32 exp = 8;
  if (has_exp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->exp(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DailyMissionConfig.DailyMission)
  return target;
}

int DailyMission::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 rate = 2;
    if (has_rate()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->rate());
    }

    // required uint32 type = 3;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

    // required uint32 subtype = 4;
    if (has_subtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->subtype());
    }

    // required uint32 count = 5;
    if (has_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->count());
    }

    // required uint32 exp = 8;
    if (has_exp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->exp());
    }

  }
  // repeated uint32 starrate = 6;
  {
    int data_size = 0;
    for (int i = 0; i < this->starrate_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->starrate(i));
    }
    total_size += 1 * this->starrate_size() + data_size;
  }

  // repeated double starcoefficient = 7;
  {
    int data_size = 0;
    data_size = 8 * this->starcoefficient_size();
    total_size += 1 * this->starcoefficient_size() + data_size;
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

void DailyMission::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DailyMission* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DailyMission*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DailyMission::MergeFrom(const DailyMission& from) {
  GOOGLE_CHECK_NE(&from, this);
  starrate_.MergeFrom(from.starrate_);
  starcoefficient_.MergeFrom(from.starcoefficient_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_rate()) {
      set_rate(from.rate());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_subtype()) {
      set_subtype(from.subtype());
    }
    if (from.has_count()) {
      set_count(from.count());
    }
    if (from.has_exp()) {
      set_exp(from.exp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DailyMission::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DailyMission::CopyFrom(const DailyMission& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyMission::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000009f) != 0x0000009f) return false;

  return true;
}

void DailyMission::Swap(DailyMission* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(rate_, other->rate_);
    std::swap(type_, other->type_);
    std::swap(subtype_, other->subtype_);
    std::swap(count_, other->count_);
    starrate_.Swap(&other->starrate_);
    starcoefficient_.Swap(&other->starcoefficient_);
    std::swap(exp_, other->exp_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DailyMission::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DailyMission_descriptor_;
  metadata.reflection = DailyMission_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int DailyMissionsItem::kTechFieldNumber;
const int DailyMissionsItem::kMissionsFieldNumber;
#endif  // !_MSC_VER

DailyMissionsItem::DailyMissionsItem()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:DailyMissionConfig.DailyMissionsItem)
}

void DailyMissionsItem::InitAsDefaultInstance() {
}

DailyMissionsItem::DailyMissionsItem(const DailyMissionsItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:DailyMissionConfig.DailyMissionsItem)
}

void DailyMissionsItem::SharedCtor() {
  _cached_size_ = 0;
  tech_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyMissionsItem::~DailyMissionsItem() {
  // @@protoc_insertion_point(destructor:DailyMissionConfig.DailyMissionsItem)
  SharedDtor();
}

void DailyMissionsItem::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DailyMissionsItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DailyMissionsItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DailyMissionsItem_descriptor_;
}

const DailyMissionsItem& DailyMissionsItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DailyMissionConfig_2eproto();
  return *default_instance_;
}

DailyMissionsItem* DailyMissionsItem::default_instance_ = NULL;

DailyMissionsItem* DailyMissionsItem::New() const {
  return new DailyMissionsItem;
}

void DailyMissionsItem::Clear() {
  tech_ = 0u;
  missions_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DailyMissionsItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:DailyMissionConfig.DailyMissionsItem)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 tech = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &tech_)));
          set_has_tech();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_missions;
        break;
      }

      // repeated .DailyMissionConfig.DailyMission missions = 2;
      case 2: {
        if (tag == 18) {
         parse_missions:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_missions()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_missions;
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
  // @@protoc_insertion_point(parse_success:DailyMissionConfig.DailyMissionsItem)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:DailyMissionConfig.DailyMissionsItem)
  return false;
#undef DO_
}

void DailyMissionsItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:DailyMissionConfig.DailyMissionsItem)
  // required uint32 tech = 1;
  if (has_tech()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tech(), output);
  }

  // repeated .DailyMissionConfig.DailyMission missions = 2;
  for (int i = 0; i < this->missions_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->missions(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:DailyMissionConfig.DailyMissionsItem)
}

::google::protobuf::uint8* DailyMissionsItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:DailyMissionConfig.DailyMissionsItem)
  // required uint32 tech = 1;
  if (has_tech()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tech(), target);
  }

  // repeated .DailyMissionConfig.DailyMission missions = 2;
  for (int i = 0; i < this->missions_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->missions(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DailyMissionConfig.DailyMissionsItem)
  return target;
}

int DailyMissionsItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 tech = 1;
    if (has_tech()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->tech());
    }

  }
  // repeated .DailyMissionConfig.DailyMission missions = 2;
  total_size += 1 * this->missions_size();
  for (int i = 0; i < this->missions_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->missions(i));
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

void DailyMissionsItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DailyMissionsItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DailyMissionsItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DailyMissionsItem::MergeFrom(const DailyMissionsItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  missions_.MergeFrom(from.missions_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tech()) {
      set_tech(from.tech());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DailyMissionsItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DailyMissionsItem::CopyFrom(const DailyMissionsItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyMissionsItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->missions())) return false;
  return true;
}

void DailyMissionsItem::Swap(DailyMissionsItem* other) {
  if (other != this) {
    std::swap(tech_, other->tech_);
    missions_.Swap(&other->missions_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DailyMissionsItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DailyMissionsItem_descriptor_;
  metadata.reflection = DailyMissionsItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int DailyMissonItemList::kDailyMissionsFieldNumber;
#endif  // !_MSC_VER

DailyMissonItemList::DailyMissonItemList()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:DailyMissionConfig.DailyMissonItemList)
}

void DailyMissonItemList::InitAsDefaultInstance() {
}

DailyMissonItemList::DailyMissonItemList(const DailyMissonItemList& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:DailyMissionConfig.DailyMissonItemList)
}

void DailyMissonItemList::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyMissonItemList::~DailyMissonItemList() {
  // @@protoc_insertion_point(destructor:DailyMissionConfig.DailyMissonItemList)
  SharedDtor();
}

void DailyMissonItemList::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DailyMissonItemList::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DailyMissonItemList::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DailyMissonItemList_descriptor_;
}

const DailyMissonItemList& DailyMissonItemList::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DailyMissionConfig_2eproto();
  return *default_instance_;
}

DailyMissonItemList* DailyMissonItemList::default_instance_ = NULL;

DailyMissonItemList* DailyMissonItemList::New() const {
  return new DailyMissonItemList;
}

void DailyMissonItemList::Clear() {
  daily_missions_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DailyMissonItemList::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:DailyMissionConfig.DailyMissonItemList)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
      case 1: {
        if (tag == 10) {
         parse_daily_missions:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_daily_missions()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_daily_missions;
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
  // @@protoc_insertion_point(parse_success:DailyMissionConfig.DailyMissonItemList)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:DailyMissionConfig.DailyMissonItemList)
  return false;
#undef DO_
}

void DailyMissonItemList::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:DailyMissionConfig.DailyMissonItemList)
  // repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
  for (int i = 0; i < this->daily_missions_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->daily_missions(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:DailyMissionConfig.DailyMissonItemList)
}

::google::protobuf::uint8* DailyMissonItemList::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:DailyMissionConfig.DailyMissonItemList)
  // repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
  for (int i = 0; i < this->daily_missions_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->daily_missions(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DailyMissionConfig.DailyMissonItemList)
  return target;
}

int DailyMissonItemList::ByteSize() const {
  int total_size = 0;

  // repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
  total_size += 1 * this->daily_missions_size();
  for (int i = 0; i < this->daily_missions_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->daily_missions(i));
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

void DailyMissonItemList::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DailyMissonItemList* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DailyMissonItemList*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DailyMissonItemList::MergeFrom(const DailyMissonItemList& from) {
  GOOGLE_CHECK_NE(&from, this);
  daily_missions_.MergeFrom(from.daily_missions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DailyMissonItemList::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DailyMissonItemList::CopyFrom(const DailyMissonItemList& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyMissonItemList::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->daily_missions())) return false;
  return true;
}

void DailyMissonItemList::Swap(DailyMissonItemList* other) {
  if (other != this) {
    daily_missions_.Swap(&other->daily_missions_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DailyMissonItemList::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DailyMissonItemList_descriptor_;
  metadata.reflection = DailyMissonItemList_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace DailyMissionConfig

// @@protoc_insertion_point(global_scope)
