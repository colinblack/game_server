// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigFriendlyTree.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ConfigFriendlyTree {

namespace {

const ::google::protobuf::Descriptor* FriendlyTreeCPP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FriendlyTreeCPP_reflection_ = NULL;
const ::google::protobuf::Descriptor* FriendlyTreeCfg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FriendlyTreeCfg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigFriendlyTree_2eproto() {
  protobuf_AddDesc_ConfigFriendlyTree_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigFriendlyTree.proto");
  GOOGLE_CHECK(file != NULL);
  FriendlyTreeCPP_descriptor_ = file->message_type(0);
  static const int FriendlyTreeCPP_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, watertreereward_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, rewardtreereward_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, wateredpersonmax_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, treecdtime_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, friendlyvaluemax_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, unlocklevel_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, regrowthcdtime_),
  };
  FriendlyTreeCPP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FriendlyTreeCPP_descriptor_,
      FriendlyTreeCPP::default_instance_,
      FriendlyTreeCPP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCPP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FriendlyTreeCPP));
  FriendlyTreeCfg_descriptor_ = file->message_type(1);
  static const int FriendlyTreeCfg_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCfg, friendlytree_),
  };
  FriendlyTreeCfg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FriendlyTreeCfg_descriptor_,
      FriendlyTreeCfg::default_instance_,
      FriendlyTreeCfg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCfg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FriendlyTreeCfg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FriendlyTreeCfg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigFriendlyTree_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FriendlyTreeCPP_descriptor_, &FriendlyTreeCPP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FriendlyTreeCfg_descriptor_, &FriendlyTreeCfg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigFriendlyTree_2eproto() {
  delete FriendlyTreeCPP::default_instance_;
  delete FriendlyTreeCPP_reflection_;
  delete FriendlyTreeCfg::default_instance_;
  delete FriendlyTreeCfg_reflection_;
}

void protobuf_AddDesc_ConfigFriendlyTree_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030ConfigFriendlyTree.proto\022\022ConfigFriend"
    "lyTree\"\271\001\n\017FriendlyTreeCPP\022\027\n\017waterTreeR"
    "eward\030\001 \002(\r\022\030\n\020rewardTreeReward\030\002 \002(\r\022\030\n"
    "\020wateredPersonMax\030\003 \002(\r\022\022\n\ntreeCdTime\030\004 "
    "\002(\r\022\030\n\020friendlyValueMax\030\005 \002(\r\022\023\n\013unlockL"
    "evel\030\006 \002(\r\022\026\n\016regrowthCDTime\030\007 \002(\r\"L\n\017Fr"
    "iendlyTreeCfg\0229\n\014friendlytree\030\001 \002(\0132#.Co"
    "nfigFriendlyTree.FriendlyTreeCPP", 312);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigFriendlyTree.proto", &protobuf_RegisterTypes);
  FriendlyTreeCPP::default_instance_ = new FriendlyTreeCPP();
  FriendlyTreeCfg::default_instance_ = new FriendlyTreeCfg();
  FriendlyTreeCPP::default_instance_->InitAsDefaultInstance();
  FriendlyTreeCfg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigFriendlyTree_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigFriendlyTree_2eproto {
  StaticDescriptorInitializer_ConfigFriendlyTree_2eproto() {
    protobuf_AddDesc_ConfigFriendlyTree_2eproto();
  }
} static_descriptor_initializer_ConfigFriendlyTree_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int FriendlyTreeCPP::kWaterTreeRewardFieldNumber;
const int FriendlyTreeCPP::kRewardTreeRewardFieldNumber;
const int FriendlyTreeCPP::kWateredPersonMaxFieldNumber;
const int FriendlyTreeCPP::kTreeCdTimeFieldNumber;
const int FriendlyTreeCPP::kFriendlyValueMaxFieldNumber;
const int FriendlyTreeCPP::kUnlockLevelFieldNumber;
const int FriendlyTreeCPP::kRegrowthCDTimeFieldNumber;
#endif  // !_MSC_VER

FriendlyTreeCPP::FriendlyTreeCPP()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FriendlyTreeCPP::InitAsDefaultInstance() {
}

FriendlyTreeCPP::FriendlyTreeCPP(const FriendlyTreeCPP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FriendlyTreeCPP::SharedCtor() {
  _cached_size_ = 0;
  watertreereward_ = 0u;
  rewardtreereward_ = 0u;
  wateredpersonmax_ = 0u;
  treecdtime_ = 0u;
  friendlyvaluemax_ = 0u;
  unlocklevel_ = 0u;
  regrowthcdtime_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendlyTreeCPP::~FriendlyTreeCPP() {
  SharedDtor();
}

void FriendlyTreeCPP::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FriendlyTreeCPP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FriendlyTreeCPP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FriendlyTreeCPP_descriptor_;
}

const FriendlyTreeCPP& FriendlyTreeCPP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigFriendlyTree_2eproto();  return *default_instance_;
}

FriendlyTreeCPP* FriendlyTreeCPP::default_instance_ = NULL;

FriendlyTreeCPP* FriendlyTreeCPP::New() const {
  return new FriendlyTreeCPP;
}

void FriendlyTreeCPP::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    watertreereward_ = 0u;
    rewardtreereward_ = 0u;
    wateredpersonmax_ = 0u;
    treecdtime_ = 0u;
    friendlyvaluemax_ = 0u;
    unlocklevel_ = 0u;
    regrowthcdtime_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FriendlyTreeCPP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 waterTreeReward = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &watertreereward_)));
          set_has_watertreereward();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_rewardTreeReward;
        break;
      }
      
      // required uint32 rewardTreeReward = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_rewardTreeReward:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rewardtreereward_)));
          set_has_rewardtreereward();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_wateredPersonMax;
        break;
      }
      
      // required uint32 wateredPersonMax = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_wateredPersonMax:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &wateredpersonmax_)));
          set_has_wateredpersonmax();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_treeCdTime;
        break;
      }
      
      // required uint32 treeCdTime = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_treeCdTime:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &treecdtime_)));
          set_has_treecdtime();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_friendlyValueMax;
        break;
      }
      
      // required uint32 friendlyValueMax = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_friendlyValueMax:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &friendlyvaluemax_)));
          set_has_friendlyvaluemax();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_unlockLevel;
        break;
      }
      
      // required uint32 unlockLevel = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_unlockLevel:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &unlocklevel_)));
          set_has_unlocklevel();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_regrowthCDTime;
        break;
      }
      
      // required uint32 regrowthCDTime = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_regrowthCDTime:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &regrowthcdtime_)));
          set_has_regrowthcdtime();
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

void FriendlyTreeCPP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 waterTreeReward = 1;
  if (has_watertreereward()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->watertreereward(), output);
  }
  
  // required uint32 rewardTreeReward = 2;
  if (has_rewardtreereward()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->rewardtreereward(), output);
  }
  
  // required uint32 wateredPersonMax = 3;
  if (has_wateredpersonmax()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->wateredpersonmax(), output);
  }
  
  // required uint32 treeCdTime = 4;
  if (has_treecdtime()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->treecdtime(), output);
  }
  
  // required uint32 friendlyValueMax = 5;
  if (has_friendlyvaluemax()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->friendlyvaluemax(), output);
  }
  
  // required uint32 unlockLevel = 6;
  if (has_unlocklevel()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->unlocklevel(), output);
  }
  
  // required uint32 regrowthCDTime = 7;
  if (has_regrowthcdtime()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->regrowthcdtime(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FriendlyTreeCPP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 waterTreeReward = 1;
  if (has_watertreereward()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->watertreereward(), target);
  }
  
  // required uint32 rewardTreeReward = 2;
  if (has_rewardtreereward()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->rewardtreereward(), target);
  }
  
  // required uint32 wateredPersonMax = 3;
  if (has_wateredpersonmax()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->wateredpersonmax(), target);
  }
  
  // required uint32 treeCdTime = 4;
  if (has_treecdtime()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->treecdtime(), target);
  }
  
  // required uint32 friendlyValueMax = 5;
  if (has_friendlyvaluemax()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->friendlyvaluemax(), target);
  }
  
  // required uint32 unlockLevel = 6;
  if (has_unlocklevel()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->unlocklevel(), target);
  }
  
  // required uint32 regrowthCDTime = 7;
  if (has_regrowthcdtime()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->regrowthcdtime(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FriendlyTreeCPP::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 waterTreeReward = 1;
    if (has_watertreereward()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->watertreereward());
    }
    
    // required uint32 rewardTreeReward = 2;
    if (has_rewardtreereward()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->rewardtreereward());
    }
    
    // required uint32 wateredPersonMax = 3;
    if (has_wateredpersonmax()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->wateredpersonmax());
    }
    
    // required uint32 treeCdTime = 4;
    if (has_treecdtime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->treecdtime());
    }
    
    // required uint32 friendlyValueMax = 5;
    if (has_friendlyvaluemax()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->friendlyvaluemax());
    }
    
    // required uint32 unlockLevel = 6;
    if (has_unlocklevel()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->unlocklevel());
    }
    
    // required uint32 regrowthCDTime = 7;
    if (has_regrowthcdtime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->regrowthcdtime());
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

void FriendlyTreeCPP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FriendlyTreeCPP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FriendlyTreeCPP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FriendlyTreeCPP::MergeFrom(const FriendlyTreeCPP& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_watertreereward()) {
      set_watertreereward(from.watertreereward());
    }
    if (from.has_rewardtreereward()) {
      set_rewardtreereward(from.rewardtreereward());
    }
    if (from.has_wateredpersonmax()) {
      set_wateredpersonmax(from.wateredpersonmax());
    }
    if (from.has_treecdtime()) {
      set_treecdtime(from.treecdtime());
    }
    if (from.has_friendlyvaluemax()) {
      set_friendlyvaluemax(from.friendlyvaluemax());
    }
    if (from.has_unlocklevel()) {
      set_unlocklevel(from.unlocklevel());
    }
    if (from.has_regrowthcdtime()) {
      set_regrowthcdtime(from.regrowthcdtime());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FriendlyTreeCPP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FriendlyTreeCPP::CopyFrom(const FriendlyTreeCPP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendlyTreeCPP::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000007f) != 0x0000007f) return false;
  
  return true;
}

void FriendlyTreeCPP::Swap(FriendlyTreeCPP* other) {
  if (other != this) {
    std::swap(watertreereward_, other->watertreereward_);
    std::swap(rewardtreereward_, other->rewardtreereward_);
    std::swap(wateredpersonmax_, other->wateredpersonmax_);
    std::swap(treecdtime_, other->treecdtime_);
    std::swap(friendlyvaluemax_, other->friendlyvaluemax_);
    std::swap(unlocklevel_, other->unlocklevel_);
    std::swap(regrowthcdtime_, other->regrowthcdtime_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FriendlyTreeCPP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FriendlyTreeCPP_descriptor_;
  metadata.reflection = FriendlyTreeCPP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int FriendlyTreeCfg::kFriendlytreeFieldNumber;
#endif  // !_MSC_VER

FriendlyTreeCfg::FriendlyTreeCfg()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FriendlyTreeCfg::InitAsDefaultInstance() {
  friendlytree_ = const_cast< ::ConfigFriendlyTree::FriendlyTreeCPP*>(&::ConfigFriendlyTree::FriendlyTreeCPP::default_instance());
}

FriendlyTreeCfg::FriendlyTreeCfg(const FriendlyTreeCfg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FriendlyTreeCfg::SharedCtor() {
  _cached_size_ = 0;
  friendlytree_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendlyTreeCfg::~FriendlyTreeCfg() {
  SharedDtor();
}

void FriendlyTreeCfg::SharedDtor() {
  if (this != default_instance_) {
    delete friendlytree_;
  }
}

void FriendlyTreeCfg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FriendlyTreeCfg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FriendlyTreeCfg_descriptor_;
}

const FriendlyTreeCfg& FriendlyTreeCfg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigFriendlyTree_2eproto();  return *default_instance_;
}

FriendlyTreeCfg* FriendlyTreeCfg::default_instance_ = NULL;

FriendlyTreeCfg* FriendlyTreeCfg::New() const {
  return new FriendlyTreeCfg;
}

void FriendlyTreeCfg::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_friendlytree()) {
      if (friendlytree_ != NULL) friendlytree_->::ConfigFriendlyTree::FriendlyTreeCPP::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FriendlyTreeCfg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ConfigFriendlyTree.FriendlyTreeCPP friendlytree = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_friendlytree()));
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

void FriendlyTreeCfg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .ConfigFriendlyTree.FriendlyTreeCPP friendlytree = 1;
  if (has_friendlytree()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->friendlytree(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FriendlyTreeCfg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .ConfigFriendlyTree.FriendlyTreeCPP friendlytree = 1;
  if (has_friendlytree()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->friendlytree(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FriendlyTreeCfg::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ConfigFriendlyTree.FriendlyTreeCPP friendlytree = 1;
    if (has_friendlytree()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->friendlytree());
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

void FriendlyTreeCfg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FriendlyTreeCfg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FriendlyTreeCfg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FriendlyTreeCfg::MergeFrom(const FriendlyTreeCfg& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_friendlytree()) {
      mutable_friendlytree()->::ConfigFriendlyTree::FriendlyTreeCPP::MergeFrom(from.friendlytree());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FriendlyTreeCfg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FriendlyTreeCfg::CopyFrom(const FriendlyTreeCfg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendlyTreeCfg::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  if (has_friendlytree()) {
    if (!this->friendlytree().IsInitialized()) return false;
  }
  return true;
}

void FriendlyTreeCfg::Swap(FriendlyTreeCfg* other) {
  if (other != this) {
    std::swap(friendlytree_, other->friendlytree_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FriendlyTreeCfg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FriendlyTreeCfg_descriptor_;
  metadata.reflection = FriendlyTreeCfg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigFriendlyTree

// @@protoc_insertion_point(global_scope)
