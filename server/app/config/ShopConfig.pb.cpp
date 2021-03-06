// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ShopConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ShopConfig.pb.h"

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

namespace ShopConfig {

namespace {

const ::google::protobuf::Descriptor* LimitShopItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LimitShopItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* LimitShopItems_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LimitShopItems_reflection_ = NULL;
const ::google::protobuf::Descriptor* LimitShop_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LimitShop_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ShopConfig_2eproto() {
  protobuf_AddDesc_ShopConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ShopConfig.proto");
  GOOGLE_CHECK(file != NULL);
  LimitShopItem_descriptor_ = file->message_type(0);
  static const int LimitShopItem_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, equip_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, price_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, limit_cnt_),
  };
  LimitShopItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LimitShopItem_descriptor_,
      LimitShopItem::default_instance_,
      LimitShopItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LimitShopItem));
  LimitShopItems_descriptor_ = file->message_type(1);
  static const int LimitShopItems_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItems, open_day_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItems, items_),
  };
  LimitShopItems_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LimitShopItems_descriptor_,
      LimitShopItems::default_instance_,
      LimitShopItems_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItems, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShopItems, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LimitShopItems));
  LimitShop_descriptor_ = file->message_type(2);
  static const int LimitShop_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShop, limit_shop_),
  };
  LimitShop_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LimitShop_descriptor_,
      LimitShop::default_instance_,
      LimitShop_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShop, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LimitShop, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LimitShop));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ShopConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LimitShopItem_descriptor_, &LimitShopItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LimitShopItems_descriptor_, &LimitShopItems::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LimitShop_descriptor_, &LimitShop::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ShopConfig_2eproto() {
  delete LimitShopItem::default_instance_;
  delete LimitShopItem_reflection_;
  delete LimitShopItems::default_instance_;
  delete LimitShopItems_reflection_;
  delete LimitShop::default_instance_;
  delete LimitShop_reflection_;
}

void protobuf_AddDesc_ShopConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020ShopConfig.proto\022\nShopConfig\"O\n\rLimitS"
    "hopItem\022\n\n\002id\030\001 \002(\r\022\020\n\010equip_id\030\002 \002(\r\022\r\n"
    "\005price\030\003 \002(\r\022\021\n\tlimit_cnt\030\004 \002(\r\"L\n\016Limit"
    "ShopItems\022\020\n\010open_day\030\001 \002(\r\022(\n\005items\030\002 \003"
    "(\0132\031.ShopConfig.LimitShopItem\";\n\tLimitSh"
    "op\022.\n\nlimit_shop\030\001 \003(\0132\032.ShopConfig.Limi"
    "tShopItems", 250);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ShopConfig.proto", &protobuf_RegisterTypes);
  LimitShopItem::default_instance_ = new LimitShopItem();
  LimitShopItems::default_instance_ = new LimitShopItems();
  LimitShop::default_instance_ = new LimitShop();
  LimitShopItem::default_instance_->InitAsDefaultInstance();
  LimitShopItems::default_instance_->InitAsDefaultInstance();
  LimitShop::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ShopConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ShopConfig_2eproto {
  StaticDescriptorInitializer_ShopConfig_2eproto() {
    protobuf_AddDesc_ShopConfig_2eproto();
  }
} static_descriptor_initializer_ShopConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int LimitShopItem::kIdFieldNumber;
const int LimitShopItem::kEquipIdFieldNumber;
const int LimitShopItem::kPriceFieldNumber;
const int LimitShopItem::kLimitCntFieldNumber;
#endif  // !_MSC_VER

LimitShopItem::LimitShopItem()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ShopConfig.LimitShopItem)
}

void LimitShopItem::InitAsDefaultInstance() {
}

LimitShopItem::LimitShopItem(const LimitShopItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ShopConfig.LimitShopItem)
}

void LimitShopItem::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  equip_id_ = 0u;
  price_ = 0u;
  limit_cnt_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LimitShopItem::~LimitShopItem() {
  // @@protoc_insertion_point(destructor:ShopConfig.LimitShopItem)
  SharedDtor();
}

void LimitShopItem::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LimitShopItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LimitShopItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LimitShopItem_descriptor_;
}

const LimitShopItem& LimitShopItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ShopConfig_2eproto();
  return *default_instance_;
}

LimitShopItem* LimitShopItem::default_instance_ = NULL;

LimitShopItem* LimitShopItem::New() const {
  return new LimitShopItem;
}

void LimitShopItem::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<LimitShopItem*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, limit_cnt_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LimitShopItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ShopConfig.LimitShopItem)
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
        if (input->ExpectTag(16)) goto parse_equip_id;
        break;
      }

      // required uint32 equip_id = 2;
      case 2: {
        if (tag == 16) {
         parse_equip_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &equip_id_)));
          set_has_equip_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_price;
        break;
      }

      // required uint32 price = 3;
      case 3: {
        if (tag == 24) {
         parse_price:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &price_)));
          set_has_price();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_limit_cnt;
        break;
      }

      // required uint32 limit_cnt = 4;
      case 4: {
        if (tag == 32) {
         parse_limit_cnt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &limit_cnt_)));
          set_has_limit_cnt();
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
  // @@protoc_insertion_point(parse_success:ShopConfig.LimitShopItem)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ShopConfig.LimitShopItem)
  return false;
#undef DO_
}

void LimitShopItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ShopConfig.LimitShopItem)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 equip_id = 2;
  if (has_equip_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->equip_id(), output);
  }

  // required uint32 price = 3;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->price(), output);
  }

  // required uint32 limit_cnt = 4;
  if (has_limit_cnt()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->limit_cnt(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ShopConfig.LimitShopItem)
}

::google::protobuf::uint8* LimitShopItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ShopConfig.LimitShopItem)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 equip_id = 2;
  if (has_equip_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->equip_id(), target);
  }

  // required uint32 price = 3;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->price(), target);
  }

  // required uint32 limit_cnt = 4;
  if (has_limit_cnt()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->limit_cnt(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ShopConfig.LimitShopItem)
  return target;
}

int LimitShopItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 equip_id = 2;
    if (has_equip_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->equip_id());
    }

    // required uint32 price = 3;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->price());
    }

    // required uint32 limit_cnt = 4;
    if (has_limit_cnt()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->limit_cnt());
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

void LimitShopItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LimitShopItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LimitShopItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LimitShopItem::MergeFrom(const LimitShopItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_equip_id()) {
      set_equip_id(from.equip_id());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
    if (from.has_limit_cnt()) {
      set_limit_cnt(from.limit_cnt());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LimitShopItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LimitShopItem::CopyFrom(const LimitShopItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LimitShopItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void LimitShopItem::Swap(LimitShopItem* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(equip_id_, other->equip_id_);
    std::swap(price_, other->price_);
    std::swap(limit_cnt_, other->limit_cnt_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LimitShopItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LimitShopItem_descriptor_;
  metadata.reflection = LimitShopItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LimitShopItems::kOpenDayFieldNumber;
const int LimitShopItems::kItemsFieldNumber;
#endif  // !_MSC_VER

LimitShopItems::LimitShopItems()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ShopConfig.LimitShopItems)
}

void LimitShopItems::InitAsDefaultInstance() {
}

LimitShopItems::LimitShopItems(const LimitShopItems& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ShopConfig.LimitShopItems)
}

void LimitShopItems::SharedCtor() {
  _cached_size_ = 0;
  open_day_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LimitShopItems::~LimitShopItems() {
  // @@protoc_insertion_point(destructor:ShopConfig.LimitShopItems)
  SharedDtor();
}

void LimitShopItems::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LimitShopItems::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LimitShopItems::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LimitShopItems_descriptor_;
}

const LimitShopItems& LimitShopItems::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ShopConfig_2eproto();
  return *default_instance_;
}

LimitShopItems* LimitShopItems::default_instance_ = NULL;

LimitShopItems* LimitShopItems::New() const {
  return new LimitShopItems;
}

void LimitShopItems::Clear() {
  open_day_ = 0u;
  items_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LimitShopItems::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ShopConfig.LimitShopItems)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 open_day = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &open_day_)));
          set_has_open_day();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_items;
        break;
      }

      // repeated .ShopConfig.LimitShopItem items = 2;
      case 2: {
        if (tag == 18) {
         parse_items:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_items()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_items;
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
  // @@protoc_insertion_point(parse_success:ShopConfig.LimitShopItems)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ShopConfig.LimitShopItems)
  return false;
#undef DO_
}

void LimitShopItems::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ShopConfig.LimitShopItems)
  // required uint32 open_day = 1;
  if (has_open_day()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->open_day(), output);
  }

  // repeated .ShopConfig.LimitShopItem items = 2;
  for (int i = 0; i < this->items_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->items(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ShopConfig.LimitShopItems)
}

::google::protobuf::uint8* LimitShopItems::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ShopConfig.LimitShopItems)
  // required uint32 open_day = 1;
  if (has_open_day()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->open_day(), target);
  }

  // repeated .ShopConfig.LimitShopItem items = 2;
  for (int i = 0; i < this->items_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->items(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ShopConfig.LimitShopItems)
  return target;
}

int LimitShopItems::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 open_day = 1;
    if (has_open_day()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->open_day());
    }

  }
  // repeated .ShopConfig.LimitShopItem items = 2;
  total_size += 1 * this->items_size();
  for (int i = 0; i < this->items_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->items(i));
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

void LimitShopItems::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LimitShopItems* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LimitShopItems*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LimitShopItems::MergeFrom(const LimitShopItems& from) {
  GOOGLE_CHECK_NE(&from, this);
  items_.MergeFrom(from.items_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_open_day()) {
      set_open_day(from.open_day());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LimitShopItems::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LimitShopItems::CopyFrom(const LimitShopItems& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LimitShopItems::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->items())) return false;
  return true;
}

void LimitShopItems::Swap(LimitShopItems* other) {
  if (other != this) {
    std::swap(open_day_, other->open_day_);
    items_.Swap(&other->items_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LimitShopItems::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LimitShopItems_descriptor_;
  metadata.reflection = LimitShopItems_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LimitShop::kLimitShopFieldNumber;
#endif  // !_MSC_VER

LimitShop::LimitShop()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ShopConfig.LimitShop)
}

void LimitShop::InitAsDefaultInstance() {
}

LimitShop::LimitShop(const LimitShop& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ShopConfig.LimitShop)
}

void LimitShop::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LimitShop::~LimitShop() {
  // @@protoc_insertion_point(destructor:ShopConfig.LimitShop)
  SharedDtor();
}

void LimitShop::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LimitShop::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LimitShop::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LimitShop_descriptor_;
}

const LimitShop& LimitShop::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ShopConfig_2eproto();
  return *default_instance_;
}

LimitShop* LimitShop::default_instance_ = NULL;

LimitShop* LimitShop::New() const {
  return new LimitShop;
}

void LimitShop::Clear() {
  limit_shop_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LimitShop::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ShopConfig.LimitShop)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ShopConfig.LimitShopItems limit_shop = 1;
      case 1: {
        if (tag == 10) {
         parse_limit_shop:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_limit_shop()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_limit_shop;
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
  // @@protoc_insertion_point(parse_success:ShopConfig.LimitShop)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ShopConfig.LimitShop)
  return false;
#undef DO_
}

void LimitShop::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ShopConfig.LimitShop)
  // repeated .ShopConfig.LimitShopItems limit_shop = 1;
  for (int i = 0; i < this->limit_shop_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->limit_shop(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ShopConfig.LimitShop)
}

::google::protobuf::uint8* LimitShop::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ShopConfig.LimitShop)
  // repeated .ShopConfig.LimitShopItems limit_shop = 1;
  for (int i = 0; i < this->limit_shop_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->limit_shop(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ShopConfig.LimitShop)
  return target;
}

int LimitShop::ByteSize() const {
  int total_size = 0;

  // repeated .ShopConfig.LimitShopItems limit_shop = 1;
  total_size += 1 * this->limit_shop_size();
  for (int i = 0; i < this->limit_shop_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->limit_shop(i));
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

void LimitShop::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LimitShop* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LimitShop*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LimitShop::MergeFrom(const LimitShop& from) {
  GOOGLE_CHECK_NE(&from, this);
  limit_shop_.MergeFrom(from.limit_shop_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LimitShop::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LimitShop::CopyFrom(const LimitShop& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LimitShop::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->limit_shop())) return false;
  return true;
}

void LimitShop::Swap(LimitShop* other) {
  if (other != this) {
    limit_shop_.Swap(&other->limit_shop_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LimitShop::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LimitShop_descriptor_;
  metadata.reflection = LimitShop_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ShopConfig

// @@protoc_insertion_point(global_scope)
