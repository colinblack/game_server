// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GroupBuyingConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GroupBuyingConfig.pb.h"

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

namespace GroupBuyingConfig {

namespace {

const ::google::protobuf::Descriptor* CountPrice_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CountPrice_reflection_ = NULL;
const ::google::protobuf::Descriptor* GroupBuyingItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GroupBuyingItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* GroupBuyingItemsCfg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GroupBuyingItemsCfg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_GroupBuyingConfig_2eproto() {
  protobuf_AddDesc_GroupBuyingConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "GroupBuyingConfig.proto");
  GOOGLE_CHECK(file != NULL);
  CountPrice_descriptor_ = file->message_type(0);
  static const int CountPrice_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CountPrice, count_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CountPrice, price_),
  };
  CountPrice_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CountPrice_descriptor_,
      CountPrice::default_instance_,
      CountPrice_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CountPrice, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CountPrice, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CountPrice));
  GroupBuyingItem_descriptor_ = file->message_type(1);
  static const int GroupBuyingItem_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, oriprice_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, reward_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, people_),
  };
  GroupBuyingItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GroupBuyingItem_descriptor_,
      GroupBuyingItem::default_instance_,
      GroupBuyingItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GroupBuyingItem));
  GroupBuyingItemsCfg_descriptor_ = file->message_type(2);
  static const int GroupBuyingItemsCfg_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItemsCfg, tuangou_),
  };
  GroupBuyingItemsCfg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GroupBuyingItemsCfg_descriptor_,
      GroupBuyingItemsCfg::default_instance_,
      GroupBuyingItemsCfg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItemsCfg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GroupBuyingItemsCfg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GroupBuyingItemsCfg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_GroupBuyingConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CountPrice_descriptor_, &CountPrice::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GroupBuyingItem_descriptor_, &GroupBuyingItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GroupBuyingItemsCfg_descriptor_, &GroupBuyingItemsCfg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_GroupBuyingConfig_2eproto() {
  delete CountPrice::default_instance_;
  delete CountPrice_reflection_;
  delete GroupBuyingItem::default_instance_;
  delete GroupBuyingItem_reflection_;
  delete GroupBuyingItemsCfg::default_instance_;
  delete GroupBuyingItemsCfg_reflection_;
}

void protobuf_AddDesc_GroupBuyingConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::RewardConfig::protobuf_AddDesc_RewardConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027GroupBuyingConfig.proto\022\021GroupBuyingCo"
    "nfig\032\022RewardConfig.proto\"*\n\nCountPrice\022\r"
    "\n\005count\030\001 \002(\r\022\r\n\005price\030\002 \002(\r\"\213\001\n\017GroupBu"
    "yingItem\022\n\n\002id\030\001 \002(\r\022\020\n\010oriprice\030\002 \002(\r\022+"
    "\n\006reward\030\003 \002(\0132\033.RewardConfig.RewardItem"
    "Cfg\022-\n\006people\030\004 \003(\0132\035.GroupBuyingConfig."
    "CountPrice\"J\n\023GroupBuyingItemsCfg\0223\n\007tua"
    "ngou\030\001 \003(\0132\".GroupBuyingConfig.GroupBuyi"
    "ngItem", 326);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "GroupBuyingConfig.proto", &protobuf_RegisterTypes);
  CountPrice::default_instance_ = new CountPrice();
  GroupBuyingItem::default_instance_ = new GroupBuyingItem();
  GroupBuyingItemsCfg::default_instance_ = new GroupBuyingItemsCfg();
  CountPrice::default_instance_->InitAsDefaultInstance();
  GroupBuyingItem::default_instance_->InitAsDefaultInstance();
  GroupBuyingItemsCfg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GroupBuyingConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GroupBuyingConfig_2eproto {
  StaticDescriptorInitializer_GroupBuyingConfig_2eproto() {
    protobuf_AddDesc_GroupBuyingConfig_2eproto();
  }
} static_descriptor_initializer_GroupBuyingConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int CountPrice::kCountFieldNumber;
const int CountPrice::kPriceFieldNumber;
#endif  // !_MSC_VER

CountPrice::CountPrice()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:GroupBuyingConfig.CountPrice)
}

void CountPrice::InitAsDefaultInstance() {
}

CountPrice::CountPrice(const CountPrice& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:GroupBuyingConfig.CountPrice)
}

void CountPrice::SharedCtor() {
  _cached_size_ = 0;
  count_ = 0u;
  price_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CountPrice::~CountPrice() {
  // @@protoc_insertion_point(destructor:GroupBuyingConfig.CountPrice)
  SharedDtor();
}

void CountPrice::SharedDtor() {
  if (this != default_instance_) {
  }
}

void CountPrice::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CountPrice::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CountPrice_descriptor_;
}

const CountPrice& CountPrice::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GroupBuyingConfig_2eproto();
  return *default_instance_;
}

CountPrice* CountPrice::default_instance_ = NULL;

CountPrice* CountPrice::New() const {
  return new CountPrice;
}

void CountPrice::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<CountPrice*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(count_, price_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CountPrice::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:GroupBuyingConfig.CountPrice)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 count = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &count_)));
          set_has_count();
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
  // @@protoc_insertion_point(parse_success:GroupBuyingConfig.CountPrice)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:GroupBuyingConfig.CountPrice)
  return false;
#undef DO_
}

void CountPrice::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:GroupBuyingConfig.CountPrice)
  // required uint32 count = 1;
  if (has_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->count(), output);
  }

  // required uint32 price = 2;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->price(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:GroupBuyingConfig.CountPrice)
}

::google::protobuf::uint8* CountPrice::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:GroupBuyingConfig.CountPrice)
  // required uint32 count = 1;
  if (has_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->count(), target);
  }

  // required uint32 price = 2;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->price(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:GroupBuyingConfig.CountPrice)
  return target;
}

int CountPrice::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 count = 1;
    if (has_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->count());
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

void CountPrice::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CountPrice* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CountPrice*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CountPrice::MergeFrom(const CountPrice& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_count()) {
      set_count(from.count());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CountPrice::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CountPrice::CopyFrom(const CountPrice& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CountPrice::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void CountPrice::Swap(CountPrice* other) {
  if (other != this) {
    std::swap(count_, other->count_);
    std::swap(price_, other->price_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CountPrice::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CountPrice_descriptor_;
  metadata.reflection = CountPrice_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GroupBuyingItem::kIdFieldNumber;
const int GroupBuyingItem::kOripriceFieldNumber;
const int GroupBuyingItem::kRewardFieldNumber;
const int GroupBuyingItem::kPeopleFieldNumber;
#endif  // !_MSC_VER

GroupBuyingItem::GroupBuyingItem()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:GroupBuyingConfig.GroupBuyingItem)
}

void GroupBuyingItem::InitAsDefaultInstance() {
  reward_ = const_cast< ::RewardConfig::RewardItemCfg*>(&::RewardConfig::RewardItemCfg::default_instance());
}

GroupBuyingItem::GroupBuyingItem(const GroupBuyingItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:GroupBuyingConfig.GroupBuyingItem)
}

void GroupBuyingItem::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  oriprice_ = 0u;
  reward_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GroupBuyingItem::~GroupBuyingItem() {
  // @@protoc_insertion_point(destructor:GroupBuyingConfig.GroupBuyingItem)
  SharedDtor();
}

void GroupBuyingItem::SharedDtor() {
  if (this != default_instance_) {
    delete reward_;
  }
}

void GroupBuyingItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GroupBuyingItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GroupBuyingItem_descriptor_;
}

const GroupBuyingItem& GroupBuyingItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GroupBuyingConfig_2eproto();
  return *default_instance_;
}

GroupBuyingItem* GroupBuyingItem::default_instance_ = NULL;

GroupBuyingItem* GroupBuyingItem::New() const {
  return new GroupBuyingItem;
}

void GroupBuyingItem::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<GroupBuyingItem*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(id_, oriprice_);
    if (has_reward()) {
      if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  people_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GroupBuyingItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:GroupBuyingConfig.GroupBuyingItem)
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
        if (input->ExpectTag(16)) goto parse_oriprice;
        break;
      }

      // required uint32 oriprice = 2;
      case 2: {
        if (tag == 16) {
         parse_oriprice:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &oriprice_)));
          set_has_oriprice();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_reward;
        break;
      }

      // required .RewardConfig.RewardItemCfg reward = 3;
      case 3: {
        if (tag == 26) {
         parse_reward:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_reward()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_people;
        break;
      }

      // repeated .GroupBuyingConfig.CountPrice people = 4;
      case 4: {
        if (tag == 34) {
         parse_people:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_people()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_people;
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
  // @@protoc_insertion_point(parse_success:GroupBuyingConfig.GroupBuyingItem)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:GroupBuyingConfig.GroupBuyingItem)
  return false;
#undef DO_
}

void GroupBuyingItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:GroupBuyingConfig.GroupBuyingItem)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 oriprice = 2;
  if (has_oriprice()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->oriprice(), output);
  }

  // required .RewardConfig.RewardItemCfg reward = 3;
  if (has_reward()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->reward(), output);
  }

  // repeated .GroupBuyingConfig.CountPrice people = 4;
  for (int i = 0; i < this->people_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->people(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:GroupBuyingConfig.GroupBuyingItem)
}

::google::protobuf::uint8* GroupBuyingItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:GroupBuyingConfig.GroupBuyingItem)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 oriprice = 2;
  if (has_oriprice()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->oriprice(), target);
  }

  // required .RewardConfig.RewardItemCfg reward = 3;
  if (has_reward()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->reward(), target);
  }

  // repeated .GroupBuyingConfig.CountPrice people = 4;
  for (int i = 0; i < this->people_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->people(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:GroupBuyingConfig.GroupBuyingItem)
  return target;
}

int GroupBuyingItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 oriprice = 2;
    if (has_oriprice()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->oriprice());
    }

    // required .RewardConfig.RewardItemCfg reward = 3;
    if (has_reward()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->reward());
    }

  }
  // repeated .GroupBuyingConfig.CountPrice people = 4;
  total_size += 1 * this->people_size();
  for (int i = 0; i < this->people_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->people(i));
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

void GroupBuyingItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GroupBuyingItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GroupBuyingItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GroupBuyingItem::MergeFrom(const GroupBuyingItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  people_.MergeFrom(from.people_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_oriprice()) {
      set_oriprice(from.oriprice());
    }
    if (from.has_reward()) {
      mutable_reward()->::RewardConfig::RewardItemCfg::MergeFrom(from.reward());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GroupBuyingItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GroupBuyingItem::CopyFrom(const GroupBuyingItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GroupBuyingItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (has_reward()) {
    if (!this->reward().IsInitialized()) return false;
  }
  if (!::google::protobuf::internal::AllAreInitialized(this->people())) return false;
  return true;
}

void GroupBuyingItem::Swap(GroupBuyingItem* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(oriprice_, other->oriprice_);
    std::swap(reward_, other->reward_);
    people_.Swap(&other->people_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GroupBuyingItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GroupBuyingItem_descriptor_;
  metadata.reflection = GroupBuyingItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GroupBuyingItemsCfg::kTuangouFieldNumber;
#endif  // !_MSC_VER

GroupBuyingItemsCfg::GroupBuyingItemsCfg()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:GroupBuyingConfig.GroupBuyingItemsCfg)
}

void GroupBuyingItemsCfg::InitAsDefaultInstance() {
}

GroupBuyingItemsCfg::GroupBuyingItemsCfg(const GroupBuyingItemsCfg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:GroupBuyingConfig.GroupBuyingItemsCfg)
}

void GroupBuyingItemsCfg::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GroupBuyingItemsCfg::~GroupBuyingItemsCfg() {
  // @@protoc_insertion_point(destructor:GroupBuyingConfig.GroupBuyingItemsCfg)
  SharedDtor();
}

void GroupBuyingItemsCfg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GroupBuyingItemsCfg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GroupBuyingItemsCfg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GroupBuyingItemsCfg_descriptor_;
}

const GroupBuyingItemsCfg& GroupBuyingItemsCfg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GroupBuyingConfig_2eproto();
  return *default_instance_;
}

GroupBuyingItemsCfg* GroupBuyingItemsCfg::default_instance_ = NULL;

GroupBuyingItemsCfg* GroupBuyingItemsCfg::New() const {
  return new GroupBuyingItemsCfg;
}

void GroupBuyingItemsCfg::Clear() {
  tuangou_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GroupBuyingItemsCfg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:GroupBuyingConfig.GroupBuyingItemsCfg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
      case 1: {
        if (tag == 10) {
         parse_tuangou:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_tuangou()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_tuangou;
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
  // @@protoc_insertion_point(parse_success:GroupBuyingConfig.GroupBuyingItemsCfg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:GroupBuyingConfig.GroupBuyingItemsCfg)
  return false;
#undef DO_
}

void GroupBuyingItemsCfg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:GroupBuyingConfig.GroupBuyingItemsCfg)
  // repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
  for (int i = 0; i < this->tuangou_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->tuangou(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:GroupBuyingConfig.GroupBuyingItemsCfg)
}

::google::protobuf::uint8* GroupBuyingItemsCfg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:GroupBuyingConfig.GroupBuyingItemsCfg)
  // repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
  for (int i = 0; i < this->tuangou_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->tuangou(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:GroupBuyingConfig.GroupBuyingItemsCfg)
  return target;
}

int GroupBuyingItemsCfg::ByteSize() const {
  int total_size = 0;

  // repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
  total_size += 1 * this->tuangou_size();
  for (int i = 0; i < this->tuangou_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->tuangou(i));
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

void GroupBuyingItemsCfg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GroupBuyingItemsCfg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GroupBuyingItemsCfg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GroupBuyingItemsCfg::MergeFrom(const GroupBuyingItemsCfg& from) {
  GOOGLE_CHECK_NE(&from, this);
  tuangou_.MergeFrom(from.tuangou_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GroupBuyingItemsCfg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GroupBuyingItemsCfg::CopyFrom(const GroupBuyingItemsCfg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GroupBuyingItemsCfg::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->tuangou())) return false;
  return true;
}

void GroupBuyingItemsCfg::Swap(GroupBuyingItemsCfg* other) {
  if (other != this) {
    tuangou_.Swap(&other->tuangou_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GroupBuyingItemsCfg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GroupBuyingItemsCfg_descriptor_;
  metadata.reflection = GroupBuyingItemsCfg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace GroupBuyingConfig

// @@protoc_insertion_point(global_scope)