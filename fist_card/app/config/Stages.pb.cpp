// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Stages.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Stages {

namespace {

const ::google::protobuf::Descriptor* Dragon_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Dragon_reflection_ = NULL;
const ::google::protobuf::Descriptor* AllStage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AllStage_reflection_ = NULL;
const ::google::protobuf::Descriptor* StagesInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StagesInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Stages_2eproto() {
  protobuf_AddDesc_Stages_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Stages.proto");
  GOOGLE_CHECK(file != NULL);
  Dragon_descriptor_ = file->message_type(0);
  static const int Dragon_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Dragon, heroid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Dragon, idx_),
  };
  Dragon_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Dragon_descriptor_,
      Dragon::default_instance_,
      Dragon_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Dragon, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Dragon, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Dragon));
  AllStage_descriptor_ = file->message_type(1);
  static const int AllStage_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, npcid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, cards_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, rewards_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, heroexp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, dropcards_),
  };
  AllStage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AllStage_descriptor_,
      AllStage::default_instance_,
      AllStage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AllStage, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AllStage));
  StagesInfo_descriptor_ = file->message_type(2);
  static const int StagesInfo_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StagesInfo, stage_),
  };
  StagesInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StagesInfo_descriptor_,
      StagesInfo::default_instance_,
      StagesInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StagesInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StagesInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StagesInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Stages_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Dragon_descriptor_, &Dragon::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AllStage_descriptor_, &AllStage::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StagesInfo_descriptor_, &StagesInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Stages_2eproto() {
  delete Dragon::default_instance_;
  delete Dragon_reflection_;
  delete AllStage::default_instance_;
  delete AllStage_reflection_;
  delete StagesInfo::default_instance_;
  delete StagesInfo_reflection_;
}

void protobuf_AddDesc_Stages_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CommonGiftConfig::protobuf_AddDesc_CommonGiftConfig_2eproto();
  ::Cards::protobuf_AddDesc_Cards_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014Stages.proto\022\006Stages\032\026CommonGiftConfig"
    ".proto\032\013Cards.proto\"%\n\006Dragon\022\016\n\006heroid\030"
    "\001 \002(\r\022\013\n\003idx\030\002 \002(\r\"\266\001\n\010AllStage\022\n\n\002id\030\001 "
    "\002(\r\022\r\n\005level\030\002 \002(\r\022\r\n\005npcId\030\003 \003(\r\022\032\n\005car"
    "ds\030\004 \003(\0132\013.Cards.Card\0223\n\007rewards\030\005 \002(\0132\""
    ".CommonGiftConfig.CommonModifyItem\022\017\n\007he"
    "roExp\030\006 \002(\r\022\036\n\tdropCards\030\007 \003(\0132\013.Cards.C"
    "ard\"-\n\nStagesInfo\022\037\n\005stage\030\001 \003(\0132\020.Stage"
    "s.AllStage", 330);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Stages.proto", &protobuf_RegisterTypes);
  Dragon::default_instance_ = new Dragon();
  AllStage::default_instance_ = new AllStage();
  StagesInfo::default_instance_ = new StagesInfo();
  Dragon::default_instance_->InitAsDefaultInstance();
  AllStage::default_instance_->InitAsDefaultInstance();
  StagesInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Stages_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Stages_2eproto {
  StaticDescriptorInitializer_Stages_2eproto() {
    protobuf_AddDesc_Stages_2eproto();
  }
} static_descriptor_initializer_Stages_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Dragon::kHeroidFieldNumber;
const int Dragon::kIdxFieldNumber;
#endif  // !_MSC_VER

Dragon::Dragon()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Dragon::InitAsDefaultInstance() {
}

Dragon::Dragon(const Dragon& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Dragon::SharedCtor() {
  _cached_size_ = 0;
  heroid_ = 0u;
  idx_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Dragon::~Dragon() {
  SharedDtor();
}

void Dragon::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Dragon::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Dragon::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Dragon_descriptor_;
}

const Dragon& Dragon::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Stages_2eproto();  return *default_instance_;
}

Dragon* Dragon::default_instance_ = NULL;

Dragon* Dragon::New() const {
  return new Dragon;
}

void Dragon::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    heroid_ = 0u;
    idx_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Dragon::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 heroid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &heroid_)));
          set_has_heroid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_idx;
        break;
      }
      
      // required uint32 idx = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_idx:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &idx_)));
          set_has_idx();
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

void Dragon::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 heroid = 1;
  if (has_heroid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->heroid(), output);
  }
  
  // required uint32 idx = 2;
  if (has_idx()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->idx(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Dragon::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 heroid = 1;
  if (has_heroid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->heroid(), target);
  }
  
  // required uint32 idx = 2;
  if (has_idx()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->idx(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Dragon::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 heroid = 1;
    if (has_heroid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->heroid());
    }
    
    // required uint32 idx = 2;
    if (has_idx()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->idx());
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

void Dragon::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Dragon* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Dragon*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Dragon::MergeFrom(const Dragon& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_heroid()) {
      set_heroid(from.heroid());
    }
    if (from.has_idx()) {
      set_idx(from.idx());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Dragon::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Dragon::CopyFrom(const Dragon& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Dragon::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void Dragon::Swap(Dragon* other) {
  if (other != this) {
    std::swap(heroid_, other->heroid_);
    std::swap(idx_, other->idx_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Dragon::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Dragon_descriptor_;
  metadata.reflection = Dragon_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AllStage::kIdFieldNumber;
const int AllStage::kLevelFieldNumber;
const int AllStage::kNpcIdFieldNumber;
const int AllStage::kCardsFieldNumber;
const int AllStage::kRewardsFieldNumber;
const int AllStage::kHeroExpFieldNumber;
const int AllStage::kDropCardsFieldNumber;
#endif  // !_MSC_VER

AllStage::AllStage()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AllStage::InitAsDefaultInstance() {
  rewards_ = const_cast< ::CommonGiftConfig::CommonModifyItem*>(&::CommonGiftConfig::CommonModifyItem::default_instance());
}

AllStage::AllStage(const AllStage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AllStage::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  level_ = 0u;
  rewards_ = NULL;
  heroexp_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AllStage::~AllStage() {
  SharedDtor();
}

void AllStage::SharedDtor() {
  if (this != default_instance_) {
    delete rewards_;
  }
}

void AllStage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AllStage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AllStage_descriptor_;
}

const AllStage& AllStage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Stages_2eproto();  return *default_instance_;
}

AllStage* AllStage::default_instance_ = NULL;

AllStage* AllStage::New() const {
  return new AllStage;
}

void AllStage::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0u;
    level_ = 0u;
    if (has_rewards()) {
      if (rewards_ != NULL) rewards_->::CommonGiftConfig::CommonModifyItem::Clear();
    }
    heroexp_ = 0u;
  }
  npcid_.Clear();
  cards_.Clear();
  dropcards_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AllStage::MergePartialFromCodedStream(
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
        if (input->ExpectTag(16)) goto parse_level;
        break;
      }
      
      // required uint32 level = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
          set_has_level();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_npcId;
        break;
      }
      
      // repeated uint32 npcId = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_npcId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 24, input, this->mutable_npcid())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_npcid())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_npcId;
        if (input->ExpectTag(34)) goto parse_cards;
        break;
      }
      
      // repeated .Cards.Card cards = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_cards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_cards()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_cards;
        if (input->ExpectTag(42)) goto parse_rewards;
        break;
      }
      
      // required .CommonGiftConfig.CommonModifyItem rewards = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_rewards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_rewards()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_heroExp;
        break;
      }
      
      // required uint32 heroExp = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_heroExp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &heroexp_)));
          set_has_heroexp();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_dropCards;
        break;
      }
      
      // repeated .Cards.Card dropCards = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dropCards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_dropcards()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_dropCards;
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

void AllStage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }
  
  // required uint32 level = 2;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->level(), output);
  }
  
  // repeated uint32 npcId = 3;
  for (int i = 0; i < this->npcid_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      3, this->npcid(i), output);
  }
  
  // repeated .Cards.Card cards = 4;
  for (int i = 0; i < this->cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->cards(i), output);
  }
  
  // required .CommonGiftConfig.CommonModifyItem rewards = 5;
  if (has_rewards()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->rewards(), output);
  }
  
  // required uint32 heroExp = 6;
  if (has_heroexp()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->heroexp(), output);
  }
  
  // repeated .Cards.Card dropCards = 7;
  for (int i = 0; i < this->dropcards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      7, this->dropcards(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AllStage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }
  
  // required uint32 level = 2;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->level(), target);
  }
  
  // repeated uint32 npcId = 3;
  for (int i = 0; i < this->npcid_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(3, this->npcid(i), target);
  }
  
  // repeated .Cards.Card cards = 4;
  for (int i = 0; i < this->cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->cards(i), target);
  }
  
  // required .CommonGiftConfig.CommonModifyItem rewards = 5;
  if (has_rewards()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->rewards(), target);
  }
  
  // required uint32 heroExp = 6;
  if (has_heroexp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->heroexp(), target);
  }
  
  // repeated .Cards.Card dropCards = 7;
  for (int i = 0; i < this->dropcards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        7, this->dropcards(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AllStage::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }
    
    // required uint32 level = 2;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }
    
    // required .CommonGiftConfig.CommonModifyItem rewards = 5;
    if (has_rewards()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->rewards());
    }
    
    // required uint32 heroExp = 6;
    if (has_heroexp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->heroexp());
    }
    
  }
  // repeated uint32 npcId = 3;
  {
    int data_size = 0;
    for (int i = 0; i < this->npcid_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->npcid(i));
    }
    total_size += 1 * this->npcid_size() + data_size;
  }
  
  // repeated .Cards.Card cards = 4;
  total_size += 1 * this->cards_size();
  for (int i = 0; i < this->cards_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->cards(i));
  }
  
  // repeated .Cards.Card dropCards = 7;
  total_size += 1 * this->dropcards_size();
  for (int i = 0; i < this->dropcards_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->dropcards(i));
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

void AllStage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AllStage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AllStage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AllStage::MergeFrom(const AllStage& from) {
  GOOGLE_CHECK_NE(&from, this);
  npcid_.MergeFrom(from.npcid_);
  cards_.MergeFrom(from.cards_);
  dropcards_.MergeFrom(from.dropcards_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_rewards()) {
      mutable_rewards()->::CommonGiftConfig::CommonModifyItem::MergeFrom(from.rewards());
    }
    if (from.has_heroexp()) {
      set_heroexp(from.heroexp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AllStage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AllStage::CopyFrom(const AllStage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AllStage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000033) != 0x00000033) return false;
  
  for (int i = 0; i < cards_size(); i++) {
    if (!this->cards(i).IsInitialized()) return false;
  }
  if (has_rewards()) {
    if (!this->rewards().IsInitialized()) return false;
  }
  for (int i = 0; i < dropcards_size(); i++) {
    if (!this->dropcards(i).IsInitialized()) return false;
  }
  return true;
}

void AllStage::Swap(AllStage* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(level_, other->level_);
    npcid_.Swap(&other->npcid_);
    cards_.Swap(&other->cards_);
    std::swap(rewards_, other->rewards_);
    std::swap(heroexp_, other->heroexp_);
    dropcards_.Swap(&other->dropcards_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AllStage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AllStage_descriptor_;
  metadata.reflection = AllStage_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int StagesInfo::kStageFieldNumber;
#endif  // !_MSC_VER

StagesInfo::StagesInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StagesInfo::InitAsDefaultInstance() {
}

StagesInfo::StagesInfo(const StagesInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StagesInfo::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StagesInfo::~StagesInfo() {
  SharedDtor();
}

void StagesInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StagesInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StagesInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StagesInfo_descriptor_;
}

const StagesInfo& StagesInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Stages_2eproto();  return *default_instance_;
}

StagesInfo* StagesInfo::default_instance_ = NULL;

StagesInfo* StagesInfo::New() const {
  return new StagesInfo;
}

void StagesInfo::Clear() {
  stage_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StagesInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Stages.AllStage stage = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_stage:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_stage()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_stage;
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

void StagesInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .Stages.AllStage stage = 1;
  for (int i = 0; i < this->stage_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->stage(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StagesInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .Stages.AllStage stage = 1;
  for (int i = 0; i < this->stage_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->stage(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StagesInfo::ByteSize() const {
  int total_size = 0;
  
  // repeated .Stages.AllStage stage = 1;
  total_size += 1 * this->stage_size();
  for (int i = 0; i < this->stage_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->stage(i));
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

void StagesInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StagesInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StagesInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StagesInfo::MergeFrom(const StagesInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  stage_.MergeFrom(from.stage_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StagesInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StagesInfo::CopyFrom(const StagesInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StagesInfo::IsInitialized() const {
  
  for (int i = 0; i < stage_size(); i++) {
    if (!this->stage(i).IsInitialized()) return false;
  }
  return true;
}

void StagesInfo::Swap(StagesInfo* other) {
  if (other != this) {
    stage_.Swap(&other->stage_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata StagesInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StagesInfo_descriptor_;
  metadata.reflection = StagesInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Stages

// @@protoc_insertion_point(global_scope)
