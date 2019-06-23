// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SellComponentConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "SellComponentConfig.pb.h"

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

namespace SellComponentConfig {

namespace {

const ::google::protobuf::Descriptor* GoodInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GoodInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* SellComponent_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SellComponent_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_SellComponentConfig_2eproto() {
  protobuf_AddDesc_SellComponentConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "SellComponentConfig.proto");
  GOOGLE_CHECK(file != NULL);
  GoodInfo_descriptor_ = file->message_type(0);
  static const int GoodInfo_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GoodInfo, price_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GoodInfo, times_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GoodInfo, goods_),
  };
  GoodInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GoodInfo_descriptor_,
      GoodInfo::default_instance_,
      GoodInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GoodInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GoodInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GoodInfo));
  SellComponent_descriptor_ = file->message_type(1);
  static const int SellComponent_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SellComponent, goodsall_),
  };
  SellComponent_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SellComponent_descriptor_,
      SellComponent::default_instance_,
      SellComponent_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SellComponent, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SellComponent, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SellComponent));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_SellComponentConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GoodInfo_descriptor_, &GoodInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SellComponent_descriptor_, &SellComponent::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_SellComponentConfig_2eproto() {
  delete GoodInfo::default_instance_;
  delete GoodInfo_reflection_;
  delete SellComponent::default_instance_;
  delete SellComponent_reflection_;
}

void protobuf_AddDesc_SellComponentConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::RewardConfig::protobuf_AddDesc_RewardConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031SellComponentConfig.proto\022\023SellCompone"
    "ntConfig\032\022RewardConfig.proto\"M\n\010GoodInfo"
    "\022\r\n\005price\030\001 \002(\r\022\r\n\005times\030\002 \002(\r\022#\n\005goods\030"
    "\003 \003(\0132\024.RewardConfig.Reward\"@\n\rSellCompo"
    "nent\022/\n\010goodsall\030\001 \003(\0132\035.SellComponentCo"
    "nfig.GoodInfo", 213);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "SellComponentConfig.proto", &protobuf_RegisterTypes);
  GoodInfo::default_instance_ = new GoodInfo();
  SellComponent::default_instance_ = new SellComponent();
  GoodInfo::default_instance_->InitAsDefaultInstance();
  SellComponent::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_SellComponentConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_SellComponentConfig_2eproto {
  StaticDescriptorInitializer_SellComponentConfig_2eproto() {
    protobuf_AddDesc_SellComponentConfig_2eproto();
  }
} static_descriptor_initializer_SellComponentConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int GoodInfo::kPriceFieldNumber;
const int GoodInfo::kTimesFieldNumber;
const int GoodInfo::kGoodsFieldNumber;
#endif  // !_MSC_VER

GoodInfo::GoodInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SellComponentConfig.GoodInfo)
}

void GoodInfo::InitAsDefaultInstance() {
}

GoodInfo::GoodInfo(const GoodInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:SellComponentConfig.GoodInfo)
}

void GoodInfo::SharedCtor() {
  _cached_size_ = 0;
  price_ = 0u;
  times_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GoodInfo::~GoodInfo() {
  // @@protoc_insertion_point(destructor:SellComponentConfig.GoodInfo)
  SharedDtor();
}

void GoodInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GoodInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GoodInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GoodInfo_descriptor_;
}

const GoodInfo& GoodInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_SellComponentConfig_2eproto();
  return *default_instance_;
}

GoodInfo* GoodInfo::default_instance_ = NULL;

GoodInfo* GoodInfo::New() const {
  return new GoodInfo;
}

void GoodInfo::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<GoodInfo*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(price_, times_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  goods_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GoodInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SellComponentConfig.GoodInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 price = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &price_)));
          set_has_price();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_times;
        break;
      }

      // required uint32 times = 2;
      case 2: {
        if (tag == 16) {
         parse_times:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &times_)));
          set_has_times();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_goods;
        break;
      }

      // repeated .RewardConfig.Reward goods = 3;
      case 3: {
        if (tag == 26) {
         parse_goods:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_goods()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_goods;
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
  // @@protoc_insertion_point(parse_success:SellComponentConfig.GoodInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SellComponentConfig.GoodInfo)
  return false;
#undef DO_
}

void GoodInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SellComponentConfig.GoodInfo)
  // required uint32 price = 1;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->price(), output);
  }

  // required uint32 times = 2;
  if (has_times()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->times(), output);
  }

  // repeated .RewardConfig.Reward goods = 3;
  for (int i = 0; i < this->goods_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->goods(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SellComponentConfig.GoodInfo)
}

::google::protobuf::uint8* GoodInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:SellComponentConfig.GoodInfo)
  // required uint32 price = 1;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->price(), target);
  }

  // required uint32 times = 2;
  if (has_times()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->times(), target);
  }

  // repeated .RewardConfig.Reward goods = 3;
  for (int i = 0; i < this->goods_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->goods(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SellComponentConfig.GoodInfo)
  return target;
}

int GoodInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 price = 1;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->price());
    }

    // required uint32 times = 2;
    if (has_times()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->times());
    }

  }
  // repeated .RewardConfig.Reward goods = 3;
  total_size += 1 * this->goods_size();
  for (int i = 0; i < this->goods_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->goods(i));
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

void GoodInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GoodInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GoodInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GoodInfo::MergeFrom(const GoodInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  goods_.MergeFrom(from.goods_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_price()) {
      set_price(from.price());
    }
    if (from.has_times()) {
      set_times(from.times());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GoodInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GoodInfo::CopyFrom(const GoodInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GoodInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->goods())) return false;
  return true;
}

void GoodInfo::Swap(GoodInfo* other) {
  if (other != this) {
    std::swap(price_, other->price_);
    std::swap(times_, other->times_);
    goods_.Swap(&other->goods_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GoodInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GoodInfo_descriptor_;
  metadata.reflection = GoodInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SellComponent::kGoodsallFieldNumber;
#endif  // !_MSC_VER

SellComponent::SellComponent()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SellComponentConfig.SellComponent)
}

void SellComponent::InitAsDefaultInstance() {
}

SellComponent::SellComponent(const SellComponent& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:SellComponentConfig.SellComponent)
}

void SellComponent::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SellComponent::~SellComponent() {
  // @@protoc_insertion_point(destructor:SellComponentConfig.SellComponent)
  SharedDtor();
}

void SellComponent::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SellComponent::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SellComponent::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SellComponent_descriptor_;
}

const SellComponent& SellComponent::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_SellComponentConfig_2eproto();
  return *default_instance_;
}

SellComponent* SellComponent::default_instance_ = NULL;

SellComponent* SellComponent::New() const {
  return new SellComponent;
}

void SellComponent::Clear() {
  goodsall_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SellComponent::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SellComponentConfig.SellComponent)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .SellComponentConfig.GoodInfo goodsall = 1;
      case 1: {
        if (tag == 10) {
         parse_goodsall:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_goodsall()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_goodsall;
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
  // @@protoc_insertion_point(parse_success:SellComponentConfig.SellComponent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SellComponentConfig.SellComponent)
  return false;
#undef DO_
}

void SellComponent::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SellComponentConfig.SellComponent)
  // repeated .SellComponentConfig.GoodInfo goodsall = 1;
  for (int i = 0; i < this->goodsall_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->goodsall(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SellComponentConfig.SellComponent)
}

::google::protobuf::uint8* SellComponent::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:SellComponentConfig.SellComponent)
  // repeated .SellComponentConfig.GoodInfo goodsall = 1;
  for (int i = 0; i < this->goodsall_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->goodsall(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SellComponentConfig.SellComponent)
  return target;
}

int SellComponent::ByteSize() const {
  int total_size = 0;

  // repeated .SellComponentConfig.GoodInfo goodsall = 1;
  total_size += 1 * this->goodsall_size();
  for (int i = 0; i < this->goodsall_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->goodsall(i));
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

void SellComponent::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SellComponent* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SellComponent*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SellComponent::MergeFrom(const SellComponent& from) {
  GOOGLE_CHECK_NE(&from, this);
  goodsall_.MergeFrom(from.goodsall_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SellComponent::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SellComponent::CopyFrom(const SellComponent& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SellComponent::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->goodsall())) return false;
  return true;
}

void SellComponent::Swap(SellComponent* other) {
  if (other != this) {
    goodsall_.Swap(&other->goodsall_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SellComponent::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SellComponent_descriptor_;
  metadata.reflection = SellComponent_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace SellComponentConfig

// @@protoc_insertion_point(global_scope)