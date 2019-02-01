// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigItem.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ConfigItem {

namespace {

const ::google::protobuf::Descriptor* PropItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PropItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* Items_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Items_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigItem_2eproto() {
  protobuf_AddDesc_ConfigItem_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigItem.proto");
  GOOGLE_CHECK(file != NULL);
  PropItem_descriptor_ = file->message_type(0);
  static const int PropItem_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, limitnum_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, dimond_cost_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, value_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, factor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, turn_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, heroid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, seq_),
  };
  PropItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      PropItem_descriptor_,
      PropItem::default_instance_,
      PropItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(PropItem));
  Items_descriptor_ = file->message_type(1);
  static const int Items_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Items, itemes_),
  };
  Items_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Items_descriptor_,
      Items::default_instance_,
      Items_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Items, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Items, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Items));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigItem_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    PropItem_descriptor_, &PropItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Items_descriptor_, &Items::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigItem_2eproto() {
  delete PropItem::default_instance_;
  delete PropItem_reflection_;
  delete Items::default_instance_;
  delete Items_reflection_;
}

void protobuf_AddDesc_ConfigItem_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CommonGiftConfig::protobuf_AddDesc_CommonGiftConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020ConfigItem.proto\022\nConfigItem\032\026CommonGi"
    "ftConfig.proto\"\271\001\n\010PropItem\022\n\n\002id\030\001 \002(\r\022"
    "\014\n\004type\030\002 \002(\r\022\020\n\010limitnum\030\003 \002(\r\0227\n\013dimon"
    "d_cost\030\004 \001(\0132\".CommonGiftConfig.CommonMo"
    "difyItem\022\r\n\005value\030\005 \001(\r\022\016\n\006factor\030\006 \001(\001\022"
    "\014\n\004turn\030\007 \001(\r\022\016\n\006heroid\030\010 \001(\r\022\013\n\003seq\030\t \001"
    "(\r\"-\n\005Items\022$\n\006itemes\030\001 \003(\0132\024.ConfigItem"
    ".PropItem", 289);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigItem.proto", &protobuf_RegisterTypes);
  PropItem::default_instance_ = new PropItem();
  Items::default_instance_ = new Items();
  PropItem::default_instance_->InitAsDefaultInstance();
  Items::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigItem_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigItem_2eproto {
  StaticDescriptorInitializer_ConfigItem_2eproto() {
    protobuf_AddDesc_ConfigItem_2eproto();
  }
} static_descriptor_initializer_ConfigItem_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int PropItem::kIdFieldNumber;
const int PropItem::kTypeFieldNumber;
const int PropItem::kLimitnumFieldNumber;
const int PropItem::kDimondCostFieldNumber;
const int PropItem::kValueFieldNumber;
const int PropItem::kFactorFieldNumber;
const int PropItem::kTurnFieldNumber;
const int PropItem::kHeroidFieldNumber;
const int PropItem::kSeqFieldNumber;
#endif  // !_MSC_VER

PropItem::PropItem()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void PropItem::InitAsDefaultInstance() {
  dimond_cost_ = const_cast< ::CommonGiftConfig::CommonModifyItem*>(&::CommonGiftConfig::CommonModifyItem::default_instance());
}

PropItem::PropItem(const PropItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void PropItem::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  type_ = 0u;
  limitnum_ = 0u;
  dimond_cost_ = NULL;
  value_ = 0u;
  factor_ = 0;
  turn_ = 0u;
  heroid_ = 0u;
  seq_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PropItem::~PropItem() {
  SharedDtor();
}

void PropItem::SharedDtor() {
  if (this != default_instance_) {
    delete dimond_cost_;
  }
}

void PropItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PropItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PropItem_descriptor_;
}

const PropItem& PropItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigItem_2eproto();  return *default_instance_;
}

PropItem* PropItem::default_instance_ = NULL;

PropItem* PropItem::New() const {
  return new PropItem;
}

void PropItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0u;
    type_ = 0u;
    limitnum_ = 0u;
    if (has_dimond_cost()) {
      if (dimond_cost_ != NULL) dimond_cost_->::CommonGiftConfig::CommonModifyItem::Clear();
    }
    value_ = 0u;
    factor_ = 0;
    turn_ = 0u;
    heroid_ = 0u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    seq_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool PropItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }
      
      // required uint32 type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_limitnum;
        break;
      }
      
      // required uint32 limitnum = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_limitnum:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &limitnum_)));
          set_has_limitnum();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_dimond_cost;
        break;
      }
      
      // optional .CommonGiftConfig.CommonModifyItem dimond_cost = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dimond_cost:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_dimond_cost()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_value;
        break;
      }
      
      // optional uint32 value = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_value:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &value_)));
          set_has_value();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(49)) goto parse_factor;
        break;
      }
      
      // optional double factor = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_factor:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &factor_)));
          set_has_factor();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_turn;
        break;
      }
      
      // optional uint32 turn = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_turn:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &turn_)));
          set_has_turn();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_heroid;
        break;
      }
      
      // optional uint32 heroid = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_heroid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &heroid_)));
          set_has_heroid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_seq;
        break;
      }
      
      // optional uint32 seq = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_seq:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &seq_)));
          set_has_seq();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void PropItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }
  
  // required uint32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->type(), output);
  }
  
  // required uint32 limitnum = 3;
  if (has_limitnum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->limitnum(), output);
  }
  
  // optional .CommonGiftConfig.CommonModifyItem dimond_cost = 4;
  if (has_dimond_cost()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->dimond_cost(), output);
  }
  
  // optional uint32 value = 5;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->value(), output);
  }
  
  // optional double factor = 6;
  if (has_factor()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->factor(), output);
  }
  
  // optional uint32 turn = 7;
  if (has_turn()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->turn(), output);
  }
  
  // optional uint32 heroid = 8;
  if (has_heroid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->heroid(), output);
  }
  
  // optional uint32 seq = 9;
  if (has_seq()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->seq(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* PropItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }
  
  // required uint32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->type(), target);
  }
  
  // required uint32 limitnum = 3;
  if (has_limitnum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->limitnum(), target);
  }
  
  // optional .CommonGiftConfig.CommonModifyItem dimond_cost = 4;
  if (has_dimond_cost()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->dimond_cost(), target);
  }
  
  // optional uint32 value = 5;
  if (has_value()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->value(), target);
  }
  
  // optional double factor = 6;
  if (has_factor()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->factor(), target);
  }
  
  // optional uint32 turn = 7;
  if (has_turn()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->turn(), target);
  }
  
  // optional uint32 heroid = 8;
  if (has_heroid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->heroid(), target);
  }
  
  // optional uint32 seq = 9;
  if (has_seq()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->seq(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int PropItem::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }
    
    // required uint32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }
    
    // required uint32 limitnum = 3;
    if (has_limitnum()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->limitnum());
    }
    
    // optional .CommonGiftConfig.CommonModifyItem dimond_cost = 4;
    if (has_dimond_cost()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->dimond_cost());
    }
    
    // optional uint32 value = 5;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->value());
    }
    
    // optional double factor = 6;
    if (has_factor()) {
      total_size += 1 + 8;
    }
    
    // optional uint32 turn = 7;
    if (has_turn()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->turn());
    }
    
    // optional uint32 heroid = 8;
    if (has_heroid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->heroid());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional uint32 seq = 9;
    if (has_seq()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->seq());
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

void PropItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const PropItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PropItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PropItem::MergeFrom(const PropItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_limitnum()) {
      set_limitnum(from.limitnum());
    }
    if (from.has_dimond_cost()) {
      mutable_dimond_cost()->::CommonGiftConfig::CommonModifyItem::MergeFrom(from.dimond_cost());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
    if (from.has_factor()) {
      set_factor(from.factor());
    }
    if (from.has_turn()) {
      set_turn(from.turn());
    }
    if (from.has_heroid()) {
      set_heroid(from.heroid());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_seq()) {
      set_seq(from.seq());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void PropItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PropItem::CopyFrom(const PropItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PropItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  if (has_dimond_cost()) {
    if (!this->dimond_cost().IsInitialized()) return false;
  }
  return true;
}

void PropItem::Swap(PropItem* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(limitnum_, other->limitnum_);
    std::swap(dimond_cost_, other->dimond_cost_);
    std::swap(value_, other->value_);
    std::swap(factor_, other->factor_);
    std::swap(turn_, other->turn_);
    std::swap(heroid_, other->heroid_);
    std::swap(seq_, other->seq_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata PropItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PropItem_descriptor_;
  metadata.reflection = PropItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Items::kItemesFieldNumber;
#endif  // !_MSC_VER

Items::Items()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Items::InitAsDefaultInstance() {
}

Items::Items(const Items& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Items::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Items::~Items() {
  SharedDtor();
}

void Items::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Items::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Items::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Items_descriptor_;
}

const Items& Items::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigItem_2eproto();  return *default_instance_;
}

Items* Items::default_instance_ = NULL;

Items* Items::New() const {
  return new Items;
}

void Items::Clear() {
  itemes_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Items::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ConfigItem.PropItem itemes = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_itemes:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_itemes()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_itemes;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Items::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ConfigItem.PropItem itemes = 1;
  for (int i = 0; i < this->itemes_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->itemes(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Items::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ConfigItem.PropItem itemes = 1;
  for (int i = 0; i < this->itemes_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->itemes(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Items::ByteSize() const {
  int total_size = 0;
  
  // repeated .ConfigItem.PropItem itemes = 1;
  total_size += 1 * this->itemes_size();
  for (int i = 0; i < this->itemes_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->itemes(i));
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

void Items::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Items* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Items*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Items::MergeFrom(const Items& from) {
  GOOGLE_CHECK_NE(&from, this);
  itemes_.MergeFrom(from.itemes_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Items::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Items::CopyFrom(const Items& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Items::IsInitialized() const {
  
  for (int i = 0; i < itemes_size(); i++) {
    if (!this->itemes(i).IsInitialized()) return false;
  }
  return true;
}

void Items::Swap(Items* other) {
  if (other != this) {
    itemes_.Swap(&other->itemes_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Items::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Items_descriptor_;
  metadata.reflection = Items_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigItem

// @@protoc_insertion_point(global_scope)