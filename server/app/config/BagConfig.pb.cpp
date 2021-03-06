// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BagConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "BagConfig.pb.h"

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

namespace BagConfig {

namespace {

const ::google::protobuf::Descriptor* Costs_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Costs_reflection_ = NULL;
const ::google::protobuf::Descriptor* BagCosts_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BagCosts_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_BagConfig_2eproto() {
  protobuf_AddDesc_BagConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "BagConfig.proto");
  GOOGLE_CHECK(file != NULL);
  Costs_descriptor_ = file->message_type(0);
  static const int Costs_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Costs, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Costs, price_),
  };
  Costs_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Costs_descriptor_,
      Costs::default_instance_,
      Costs_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Costs, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Costs, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Costs));
  BagCosts_descriptor_ = file->message_type(1);
  static const int BagCosts_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BagCosts, init_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BagCosts, max_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BagCosts, costs_),
  };
  BagCosts_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BagCosts_descriptor_,
      BagCosts::default_instance_,
      BagCosts_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BagCosts, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BagCosts, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BagCosts));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_BagConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Costs_descriptor_, &Costs::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BagCosts_descriptor_, &BagCosts::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_BagConfig_2eproto() {
  delete Costs::default_instance_;
  delete Costs_reflection_;
  delete BagCosts::default_instance_;
  delete BagCosts_reflection_;
}

void protobuf_AddDesc_BagConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017BagConfig.proto\022\tBagConfig\"\"\n\005Costs\022\n\n"
    "\002id\030\001 \002(\r\022\r\n\005price\030\002 \002(\r\"F\n\010BagCosts\022\014\n\004"
    "init\030\001 \002(\r\022\013\n\003max\030\002 \002(\r\022\037\n\005costs\030\003 \003(\0132\020"
    ".BagConfig.Costs", 136);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "BagConfig.proto", &protobuf_RegisterTypes);
  Costs::default_instance_ = new Costs();
  BagCosts::default_instance_ = new BagCosts();
  Costs::default_instance_->InitAsDefaultInstance();
  BagCosts::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_BagConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_BagConfig_2eproto {
  StaticDescriptorInitializer_BagConfig_2eproto() {
    protobuf_AddDesc_BagConfig_2eproto();
  }
} static_descriptor_initializer_BagConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Costs::kIdFieldNumber;
const int Costs::kPriceFieldNumber;
#endif  // !_MSC_VER

Costs::Costs()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:BagConfig.Costs)
}

void Costs::InitAsDefaultInstance() {
}

Costs::Costs(const Costs& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:BagConfig.Costs)
}

void Costs::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  price_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Costs::~Costs() {
  // @@protoc_insertion_point(destructor:BagConfig.Costs)
  SharedDtor();
}

void Costs::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Costs::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Costs::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Costs_descriptor_;
}

const Costs& Costs::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_BagConfig_2eproto();
  return *default_instance_;
}

Costs* Costs::default_instance_ = NULL;

Costs* Costs::New() const {
  return new Costs;
}

void Costs::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Costs*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, price_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Costs::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:BagConfig.Costs)
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
        if (input->ExpectTag(16)) goto parse_price;
        break;
      }

      // required uint32 price = 2;
      case 2: {
        if (tag == 16) {
         parse_price:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &price_)));
          set_has_price();
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
  // @@protoc_insertion_point(parse_success:BagConfig.Costs)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:BagConfig.Costs)
  return false;
#undef DO_
}

void Costs::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:BagConfig.Costs)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 price = 2;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->price(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:BagConfig.Costs)
}

::google::protobuf::uint8* Costs::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:BagConfig.Costs)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 price = 2;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->price(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:BagConfig.Costs)
  return target;
}

int Costs::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 price = 2;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->price());
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

void Costs::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Costs* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Costs*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Costs::MergeFrom(const Costs& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Costs::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Costs::CopyFrom(const Costs& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Costs::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Costs::Swap(Costs* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(price_, other->price_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Costs::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Costs_descriptor_;
  metadata.reflection = Costs_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int BagCosts::kInitFieldNumber;
const int BagCosts::kMaxFieldNumber;
const int BagCosts::kCostsFieldNumber;
#endif  // !_MSC_VER

BagCosts::BagCosts()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:BagConfig.BagCosts)
}

void BagCosts::InitAsDefaultInstance() {
}

BagCosts::BagCosts(const BagCosts& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:BagConfig.BagCosts)
}

void BagCosts::SharedCtor() {
  _cached_size_ = 0;
  init_ = 0u;
  max_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BagCosts::~BagCosts() {
  // @@protoc_insertion_point(destructor:BagConfig.BagCosts)
  SharedDtor();
}

void BagCosts::SharedDtor() {
  if (this != default_instance_) {
  }
}

void BagCosts::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BagCosts::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BagCosts_descriptor_;
}

const BagCosts& BagCosts::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_BagConfig_2eproto();
  return *default_instance_;
}

BagCosts* BagCosts::default_instance_ = NULL;

BagCosts* BagCosts::New() const {
  return new BagCosts;
}

void BagCosts::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<BagCosts*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(init_, max_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  costs_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BagCosts::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:BagConfig.BagCosts)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 init = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &init_)));
          set_has_init();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_max;
        break;
      }

      // required uint32 max = 2;
      case 2: {
        if (tag == 16) {
         parse_max:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &max_)));
          set_has_max();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_costs;
        break;
      }

      // repeated .BagConfig.Costs costs = 3;
      case 3: {
        if (tag == 26) {
         parse_costs:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_costs()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_costs;
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
  // @@protoc_insertion_point(parse_success:BagConfig.BagCosts)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:BagConfig.BagCosts)
  return false;
#undef DO_
}

void BagCosts::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:BagConfig.BagCosts)
  // required uint32 init = 1;
  if (has_init()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->init(), output);
  }

  // required uint32 max = 2;
  if (has_max()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->max(), output);
  }

  // repeated .BagConfig.Costs costs = 3;
  for (int i = 0; i < this->costs_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->costs(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:BagConfig.BagCosts)
}

::google::protobuf::uint8* BagCosts::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:BagConfig.BagCosts)
  // required uint32 init = 1;
  if (has_init()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->init(), target);
  }

  // required uint32 max = 2;
  if (has_max()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->max(), target);
  }

  // repeated .BagConfig.Costs costs = 3;
  for (int i = 0; i < this->costs_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->costs(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:BagConfig.BagCosts)
  return target;
}

int BagCosts::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 init = 1;
    if (has_init()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->init());
    }

    // required uint32 max = 2;
    if (has_max()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->max());
    }

  }
  // repeated .BagConfig.Costs costs = 3;
  total_size += 1 * this->costs_size();
  for (int i = 0; i < this->costs_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->costs(i));
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

void BagCosts::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BagCosts* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BagCosts*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BagCosts::MergeFrom(const BagCosts& from) {
  GOOGLE_CHECK_NE(&from, this);
  costs_.MergeFrom(from.costs_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_init()) {
      set_init(from.init());
    }
    if (from.has_max()) {
      set_max(from.max());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BagCosts::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BagCosts::CopyFrom(const BagCosts& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BagCosts::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->costs())) return false;
  return true;
}

void BagCosts::Swap(BagCosts* other) {
  if (other != this) {
    std::swap(init_, other->init_);
    std::swap(max_, other->max_);
    costs_.Swap(&other->costs_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BagCosts::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BagCosts_descriptor_;
  metadata.reflection = BagCosts_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace BagConfig

// @@protoc_insertion_point(global_scope)
