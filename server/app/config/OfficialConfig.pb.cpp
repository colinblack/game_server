// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: OfficialConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "OfficialConfig.pb.h"

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

namespace OfficialConfig {

namespace {

const ::google::protobuf::Descriptor* OfficialJob_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  OfficialJob_reflection_ = NULL;
const ::google::protobuf::Descriptor* OfficialDepartment_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  OfficialDepartment_reflection_ = NULL;
const ::google::protobuf::Descriptor* Official_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Official_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_OfficialConfig_2eproto() {
  protobuf_AddDesc_OfficialConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "OfficialConfig.proto");
  GOOGLE_CHECK(file != NULL);
  OfficialJob_descriptor_ = file->message_type(0);
  static const int OfficialJob_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, coin_yield_add_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, wood_yield_add_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, food_yield_add_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, iron_yield_add_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, pay_),
  };
  OfficialJob_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      OfficialJob_descriptor_,
      OfficialJob::default_instance_,
      OfficialJob_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialJob, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(OfficialJob));
  OfficialDepartment_descriptor_ = file->message_type(1);
  static const int OfficialDepartment_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialDepartment, department_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialDepartment, job_),
  };
  OfficialDepartment_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      OfficialDepartment_descriptor_,
      OfficialDepartment::default_instance_,
      OfficialDepartment_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialDepartment, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfficialDepartment, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(OfficialDepartment));
  Official_descriptor_ = file->message_type(2);
  static const int Official_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Official, official_),
  };
  Official_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Official_descriptor_,
      Official::default_instance_,
      Official_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Official, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Official, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Official));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_OfficialConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    OfficialJob_descriptor_, &OfficialJob::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    OfficialDepartment_descriptor_, &OfficialDepartment::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Official_descriptor_, &Official::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_OfficialConfig_2eproto() {
  delete OfficialJob::default_instance_;
  delete OfficialJob_reflection_;
  delete OfficialDepartment::default_instance_;
  delete OfficialDepartment_reflection_;
  delete Official::default_instance_;
  delete Official_reflection_;
}

void protobuf_AddDesc_OfficialConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024OfficialConfig.proto\022\016OfficialConfig\"\206"
    "\001\n\013OfficialJob\022\n\n\002id\030\001 \002(\r\022\026\n\016coin_yield"
    "_add\030\002 \002(\r\022\026\n\016wood_yield_add\030\003 \002(\r\022\026\n\016fo"
    "od_yield_add\030\004 \002(\r\022\026\n\016iron_yield_add\030\005 \002"
    "(\r\022\013\n\003pay\030\006 \002(\r\"R\n\022OfficialDepartment\022\022\n"
    "\ndepartment\030\001 \002(\r\022(\n\003job\030\002 \003(\0132\033.Officia"
    "lConfig.OfficialJob\"@\n\010Official\0224\n\010offic"
    "ial\030\001 \003(\0132\".OfficialConfig.OfficialDepar"
    "tment", 325);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "OfficialConfig.proto", &protobuf_RegisterTypes);
  OfficialJob::default_instance_ = new OfficialJob();
  OfficialDepartment::default_instance_ = new OfficialDepartment();
  Official::default_instance_ = new Official();
  OfficialJob::default_instance_->InitAsDefaultInstance();
  OfficialDepartment::default_instance_->InitAsDefaultInstance();
  Official::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_OfficialConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_OfficialConfig_2eproto {
  StaticDescriptorInitializer_OfficialConfig_2eproto() {
    protobuf_AddDesc_OfficialConfig_2eproto();
  }
} static_descriptor_initializer_OfficialConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int OfficialJob::kIdFieldNumber;
const int OfficialJob::kCoinYieldAddFieldNumber;
const int OfficialJob::kWoodYieldAddFieldNumber;
const int OfficialJob::kFoodYieldAddFieldNumber;
const int OfficialJob::kIronYieldAddFieldNumber;
const int OfficialJob::kPayFieldNumber;
#endif  // !_MSC_VER

OfficialJob::OfficialJob()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:OfficialConfig.OfficialJob)
}

void OfficialJob::InitAsDefaultInstance() {
}

OfficialJob::OfficialJob(const OfficialJob& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:OfficialConfig.OfficialJob)
}

void OfficialJob::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  coin_yield_add_ = 0u;
  wood_yield_add_ = 0u;
  food_yield_add_ = 0u;
  iron_yield_add_ = 0u;
  pay_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

OfficialJob::~OfficialJob() {
  // @@protoc_insertion_point(destructor:OfficialConfig.OfficialJob)
  SharedDtor();
}

void OfficialJob::SharedDtor() {
  if (this != default_instance_) {
  }
}

void OfficialJob::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* OfficialJob::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OfficialJob_descriptor_;
}

const OfficialJob& OfficialJob::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_OfficialConfig_2eproto();
  return *default_instance_;
}

OfficialJob* OfficialJob::default_instance_ = NULL;

OfficialJob* OfficialJob::New() const {
  return new OfficialJob;
}

void OfficialJob::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<OfficialJob*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 63) {
    ZR_(id_, pay_);
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool OfficialJob::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:OfficialConfig.OfficialJob)
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
        if (input->ExpectTag(16)) goto parse_coin_yield_add;
        break;
      }

      // required uint32 coin_yield_add = 2;
      case 2: {
        if (tag == 16) {
         parse_coin_yield_add:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &coin_yield_add_)));
          set_has_coin_yield_add();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_wood_yield_add;
        break;
      }

      // required uint32 wood_yield_add = 3;
      case 3: {
        if (tag == 24) {
         parse_wood_yield_add:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &wood_yield_add_)));
          set_has_wood_yield_add();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_food_yield_add;
        break;
      }

      // required uint32 food_yield_add = 4;
      case 4: {
        if (tag == 32) {
         parse_food_yield_add:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &food_yield_add_)));
          set_has_food_yield_add();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_iron_yield_add;
        break;
      }

      // required uint32 iron_yield_add = 5;
      case 5: {
        if (tag == 40) {
         parse_iron_yield_add:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &iron_yield_add_)));
          set_has_iron_yield_add();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_pay;
        break;
      }

      // required uint32 pay = 6;
      case 6: {
        if (tag == 48) {
         parse_pay:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &pay_)));
          set_has_pay();
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
  // @@protoc_insertion_point(parse_success:OfficialConfig.OfficialJob)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:OfficialConfig.OfficialJob)
  return false;
#undef DO_
}

void OfficialJob::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:OfficialConfig.OfficialJob)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 coin_yield_add = 2;
  if (has_coin_yield_add()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->coin_yield_add(), output);
  }

  // required uint32 wood_yield_add = 3;
  if (has_wood_yield_add()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->wood_yield_add(), output);
  }

  // required uint32 food_yield_add = 4;
  if (has_food_yield_add()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->food_yield_add(), output);
  }

  // required uint32 iron_yield_add = 5;
  if (has_iron_yield_add()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->iron_yield_add(), output);
  }

  // required uint32 pay = 6;
  if (has_pay()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->pay(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:OfficialConfig.OfficialJob)
}

::google::protobuf::uint8* OfficialJob::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:OfficialConfig.OfficialJob)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 coin_yield_add = 2;
  if (has_coin_yield_add()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->coin_yield_add(), target);
  }

  // required uint32 wood_yield_add = 3;
  if (has_wood_yield_add()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->wood_yield_add(), target);
  }

  // required uint32 food_yield_add = 4;
  if (has_food_yield_add()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->food_yield_add(), target);
  }

  // required uint32 iron_yield_add = 5;
  if (has_iron_yield_add()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->iron_yield_add(), target);
  }

  // required uint32 pay = 6;
  if (has_pay()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->pay(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:OfficialConfig.OfficialJob)
  return target;
}

int OfficialJob::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 coin_yield_add = 2;
    if (has_coin_yield_add()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->coin_yield_add());
    }

    // required uint32 wood_yield_add = 3;
    if (has_wood_yield_add()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->wood_yield_add());
    }

    // required uint32 food_yield_add = 4;
    if (has_food_yield_add()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->food_yield_add());
    }

    // required uint32 iron_yield_add = 5;
    if (has_iron_yield_add()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->iron_yield_add());
    }

    // required uint32 pay = 6;
    if (has_pay()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->pay());
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

void OfficialJob::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const OfficialJob* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const OfficialJob*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void OfficialJob::MergeFrom(const OfficialJob& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_coin_yield_add()) {
      set_coin_yield_add(from.coin_yield_add());
    }
    if (from.has_wood_yield_add()) {
      set_wood_yield_add(from.wood_yield_add());
    }
    if (from.has_food_yield_add()) {
      set_food_yield_add(from.food_yield_add());
    }
    if (from.has_iron_yield_add()) {
      set_iron_yield_add(from.iron_yield_add());
    }
    if (from.has_pay()) {
      set_pay(from.pay());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void OfficialJob::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OfficialJob::CopyFrom(const OfficialJob& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OfficialJob::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;

  return true;
}

void OfficialJob::Swap(OfficialJob* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(coin_yield_add_, other->coin_yield_add_);
    std::swap(wood_yield_add_, other->wood_yield_add_);
    std::swap(food_yield_add_, other->food_yield_add_);
    std::swap(iron_yield_add_, other->iron_yield_add_);
    std::swap(pay_, other->pay_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata OfficialJob::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = OfficialJob_descriptor_;
  metadata.reflection = OfficialJob_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int OfficialDepartment::kDepartmentFieldNumber;
const int OfficialDepartment::kJobFieldNumber;
#endif  // !_MSC_VER

OfficialDepartment::OfficialDepartment()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:OfficialConfig.OfficialDepartment)
}

void OfficialDepartment::InitAsDefaultInstance() {
}

OfficialDepartment::OfficialDepartment(const OfficialDepartment& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:OfficialConfig.OfficialDepartment)
}

void OfficialDepartment::SharedCtor() {
  _cached_size_ = 0;
  department_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

OfficialDepartment::~OfficialDepartment() {
  // @@protoc_insertion_point(destructor:OfficialConfig.OfficialDepartment)
  SharedDtor();
}

void OfficialDepartment::SharedDtor() {
  if (this != default_instance_) {
  }
}

void OfficialDepartment::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* OfficialDepartment::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OfficialDepartment_descriptor_;
}

const OfficialDepartment& OfficialDepartment::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_OfficialConfig_2eproto();
  return *default_instance_;
}

OfficialDepartment* OfficialDepartment::default_instance_ = NULL;

OfficialDepartment* OfficialDepartment::New() const {
  return new OfficialDepartment;
}

void OfficialDepartment::Clear() {
  department_ = 0u;
  job_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool OfficialDepartment::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:OfficialConfig.OfficialDepartment)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 department = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &department_)));
          set_has_department();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_job;
        break;
      }

      // repeated .OfficialConfig.OfficialJob job = 2;
      case 2: {
        if (tag == 18) {
         parse_job:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_job()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_job;
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
  // @@protoc_insertion_point(parse_success:OfficialConfig.OfficialDepartment)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:OfficialConfig.OfficialDepartment)
  return false;
#undef DO_
}

void OfficialDepartment::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:OfficialConfig.OfficialDepartment)
  // required uint32 department = 1;
  if (has_department()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->department(), output);
  }

  // repeated .OfficialConfig.OfficialJob job = 2;
  for (int i = 0; i < this->job_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->job(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:OfficialConfig.OfficialDepartment)
}

::google::protobuf::uint8* OfficialDepartment::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:OfficialConfig.OfficialDepartment)
  // required uint32 department = 1;
  if (has_department()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->department(), target);
  }

  // repeated .OfficialConfig.OfficialJob job = 2;
  for (int i = 0; i < this->job_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->job(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:OfficialConfig.OfficialDepartment)
  return target;
}

int OfficialDepartment::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 department = 1;
    if (has_department()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->department());
    }

  }
  // repeated .OfficialConfig.OfficialJob job = 2;
  total_size += 1 * this->job_size();
  for (int i = 0; i < this->job_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->job(i));
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

void OfficialDepartment::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const OfficialDepartment* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const OfficialDepartment*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void OfficialDepartment::MergeFrom(const OfficialDepartment& from) {
  GOOGLE_CHECK_NE(&from, this);
  job_.MergeFrom(from.job_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_department()) {
      set_department(from.department());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void OfficialDepartment::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OfficialDepartment::CopyFrom(const OfficialDepartment& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OfficialDepartment::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->job())) return false;
  return true;
}

void OfficialDepartment::Swap(OfficialDepartment* other) {
  if (other != this) {
    std::swap(department_, other->department_);
    job_.Swap(&other->job_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata OfficialDepartment::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = OfficialDepartment_descriptor_;
  metadata.reflection = OfficialDepartment_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Official::kOfficialFieldNumber;
#endif  // !_MSC_VER

Official::Official()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:OfficialConfig.Official)
}

void Official::InitAsDefaultInstance() {
}

Official::Official(const Official& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:OfficialConfig.Official)
}

void Official::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Official::~Official() {
  // @@protoc_insertion_point(destructor:OfficialConfig.Official)
  SharedDtor();
}

void Official::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Official::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Official::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Official_descriptor_;
}

const Official& Official::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_OfficialConfig_2eproto();
  return *default_instance_;
}

Official* Official::default_instance_ = NULL;

Official* Official::New() const {
  return new Official;
}

void Official::Clear() {
  official_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Official::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:OfficialConfig.Official)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .OfficialConfig.OfficialDepartment official = 1;
      case 1: {
        if (tag == 10) {
         parse_official:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_official()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_official;
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
  // @@protoc_insertion_point(parse_success:OfficialConfig.Official)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:OfficialConfig.Official)
  return false;
#undef DO_
}

void Official::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:OfficialConfig.Official)
  // repeated .OfficialConfig.OfficialDepartment official = 1;
  for (int i = 0; i < this->official_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->official(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:OfficialConfig.Official)
}

::google::protobuf::uint8* Official::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:OfficialConfig.Official)
  // repeated .OfficialConfig.OfficialDepartment official = 1;
  for (int i = 0; i < this->official_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->official(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:OfficialConfig.Official)
  return target;
}

int Official::ByteSize() const {
  int total_size = 0;

  // repeated .OfficialConfig.OfficialDepartment official = 1;
  total_size += 1 * this->official_size();
  for (int i = 0; i < this->official_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->official(i));
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

void Official::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Official* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Official*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Official::MergeFrom(const Official& from) {
  GOOGLE_CHECK_NE(&from, this);
  official_.MergeFrom(from.official_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Official::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Official::CopyFrom(const Official& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Official::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->official())) return false;
  return true;
}

void Official::Swap(Official* other) {
  if (other != this) {
    official_.Swap(&other->official_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Official::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Official_descriptor_;
  metadata.reflection = Official_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace OfficialConfig

// @@protoc_insertion_point(global_scope)
