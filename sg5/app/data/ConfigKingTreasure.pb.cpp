// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigKingTreasure.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigKingTreasure.pb.h"

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

namespace ConfigKingTreasure {

namespace {

const ::google::protobuf::Descriptor* TreasureBox_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TreasureBox_reflection_ = NULL;
const ::google::protobuf::Descriptor* KingTreasure_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  KingTreasure_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigKingTreasure_2eproto() {
  protobuf_AddDesc_ConfigKingTreasure_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigKingTreasure.proto");
  GOOGLE_CHECK(file != NULL);
  TreasureBox_descriptor_ = file->message_type(0);
  static const int TreasureBox_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, weight_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, collect_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, limit_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, reward_),
  };
  TreasureBox_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TreasureBox_descriptor_,
      TreasureBox::default_instance_,
      TreasureBox_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureBox, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TreasureBox));
  KingTreasure_descriptor_ = file->message_type(1);
  static const int KingTreasure_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(KingTreasure, king_treasures_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(KingTreasure, cost_),
  };
  KingTreasure_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      KingTreasure_descriptor_,
      KingTreasure::default_instance_,
      KingTreasure_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(KingTreasure, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(KingTreasure, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(KingTreasure));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigKingTreasure_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TreasureBox_descriptor_, &TreasureBox::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    KingTreasure_descriptor_, &KingTreasure::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigKingTreasure_2eproto() {
  delete TreasureBox::default_instance_;
  delete TreasureBox_reflection_;
  delete KingTreasure::default_instance_;
  delete KingTreasure_reflection_;
}

void protobuf_AddDesc_ConfigKingTreasure_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::RewardConfig::protobuf_AddDesc_RewardConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030ConfigKingTreasure.proto\022\022ConfigKingTr"
    "easure\032\022RewardConfig.proto\"v\n\013TreasureBo"
    "x\022\n\n\002id\030\001 \002(\r\022\016\n\006weight\030\002 \002(\r\022\017\n\007collect"
    "\030\003 \002(\r\022\r\n\005limit\030\004 \002(\r\022+\n\006reward\030\005 \002(\0132\033."
    "RewardConfig.RewardItemCfg\"U\n\014KingTreasu"
    "re\0227\n\016king_treasures\030\001 \003(\0132\037.ConfigKingT"
    "reasure.TreasureBox\022\014\n\004cost\030\002 \002(\r", 273);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigKingTreasure.proto", &protobuf_RegisterTypes);
  TreasureBox::default_instance_ = new TreasureBox();
  KingTreasure::default_instance_ = new KingTreasure();
  TreasureBox::default_instance_->InitAsDefaultInstance();
  KingTreasure::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigKingTreasure_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigKingTreasure_2eproto {
  StaticDescriptorInitializer_ConfigKingTreasure_2eproto() {
    protobuf_AddDesc_ConfigKingTreasure_2eproto();
  }
} static_descriptor_initializer_ConfigKingTreasure_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TreasureBox::kIdFieldNumber;
const int TreasureBox::kWeightFieldNumber;
const int TreasureBox::kCollectFieldNumber;
const int TreasureBox::kLimitFieldNumber;
const int TreasureBox::kRewardFieldNumber;
#endif  // !_MSC_VER

TreasureBox::TreasureBox()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ConfigKingTreasure.TreasureBox)
}

void TreasureBox::InitAsDefaultInstance() {
  reward_ = const_cast< ::RewardConfig::RewardItemCfg*>(&::RewardConfig::RewardItemCfg::default_instance());
}

TreasureBox::TreasureBox(const TreasureBox& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ConfigKingTreasure.TreasureBox)
}

void TreasureBox::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  weight_ = 0u;
  collect_ = 0u;
  limit_ = 0u;
  reward_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TreasureBox::~TreasureBox() {
  // @@protoc_insertion_point(destructor:ConfigKingTreasure.TreasureBox)
  SharedDtor();
}

void TreasureBox::SharedDtor() {
  if (this != default_instance_) {
    delete reward_;
  }
}

void TreasureBox::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TreasureBox::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TreasureBox_descriptor_;
}

const TreasureBox& TreasureBox::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigKingTreasure_2eproto();
  return *default_instance_;
}

TreasureBox* TreasureBox::default_instance_ = NULL;

TreasureBox* TreasureBox::New() const {
  return new TreasureBox;
}

void TreasureBox::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TreasureBox*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(id_, limit_);
    if (has_reward()) {
      if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TreasureBox::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ConfigKingTreasure.TreasureBox)
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
        if (input->ExpectTag(16)) goto parse_weight;
        break;
      }

      // required uint32 weight = 2;
      case 2: {
        if (tag == 16) {
         parse_weight:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &weight_)));
          set_has_weight();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_collect;
        break;
      }

      // required uint32 collect = 3;
      case 3: {
        if (tag == 24) {
         parse_collect:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &collect_)));
          set_has_collect();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_limit;
        break;
      }

      // required uint32 limit = 4;
      case 4: {
        if (tag == 32) {
         parse_limit:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &limit_)));
          set_has_limit();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_reward;
        break;
      }

      // required .RewardConfig.RewardItemCfg reward = 5;
      case 5: {
        if (tag == 42) {
         parse_reward:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_reward()));
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
  // @@protoc_insertion_point(parse_success:ConfigKingTreasure.TreasureBox)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ConfigKingTreasure.TreasureBox)
  return false;
#undef DO_
}

void TreasureBox::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ConfigKingTreasure.TreasureBox)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required uint32 weight = 2;
  if (has_weight()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->weight(), output);
  }

  // required uint32 collect = 3;
  if (has_collect()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->collect(), output);
  }

  // required uint32 limit = 4;
  if (has_limit()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->limit(), output);
  }

  // required .RewardConfig.RewardItemCfg reward = 5;
  if (has_reward()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->reward(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ConfigKingTreasure.TreasureBox)
}

::google::protobuf::uint8* TreasureBox::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ConfigKingTreasure.TreasureBox)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required uint32 weight = 2;
  if (has_weight()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->weight(), target);
  }

  // required uint32 collect = 3;
  if (has_collect()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->collect(), target);
  }

  // required uint32 limit = 4;
  if (has_limit()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->limit(), target);
  }

  // required .RewardConfig.RewardItemCfg reward = 5;
  if (has_reward()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->reward(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ConfigKingTreasure.TreasureBox)
  return target;
}

int TreasureBox::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required uint32 weight = 2;
    if (has_weight()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->weight());
    }

    // required uint32 collect = 3;
    if (has_collect()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->collect());
    }

    // required uint32 limit = 4;
    if (has_limit()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->limit());
    }

    // required .RewardConfig.RewardItemCfg reward = 5;
    if (has_reward()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->reward());
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

void TreasureBox::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TreasureBox* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TreasureBox*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TreasureBox::MergeFrom(const TreasureBox& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_weight()) {
      set_weight(from.weight());
    }
    if (from.has_collect()) {
      set_collect(from.collect());
    }
    if (from.has_limit()) {
      set_limit(from.limit());
    }
    if (from.has_reward()) {
      mutable_reward()->::RewardConfig::RewardItemCfg::MergeFrom(from.reward());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TreasureBox::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TreasureBox::CopyFrom(const TreasureBox& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TreasureBox::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  if (has_reward()) {
    if (!this->reward().IsInitialized()) return false;
  }
  return true;
}

void TreasureBox::Swap(TreasureBox* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(weight_, other->weight_);
    std::swap(collect_, other->collect_);
    std::swap(limit_, other->limit_);
    std::swap(reward_, other->reward_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TreasureBox::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TreasureBox_descriptor_;
  metadata.reflection = TreasureBox_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int KingTreasure::kKingTreasuresFieldNumber;
const int KingTreasure::kCostFieldNumber;
#endif  // !_MSC_VER

KingTreasure::KingTreasure()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ConfigKingTreasure.KingTreasure)
}

void KingTreasure::InitAsDefaultInstance() {
}

KingTreasure::KingTreasure(const KingTreasure& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ConfigKingTreasure.KingTreasure)
}

void KingTreasure::SharedCtor() {
  _cached_size_ = 0;
  cost_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

KingTreasure::~KingTreasure() {
  // @@protoc_insertion_point(destructor:ConfigKingTreasure.KingTreasure)
  SharedDtor();
}

void KingTreasure::SharedDtor() {
  if (this != default_instance_) {
  }
}

void KingTreasure::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* KingTreasure::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return KingTreasure_descriptor_;
}

const KingTreasure& KingTreasure::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigKingTreasure_2eproto();
  return *default_instance_;
}

KingTreasure* KingTreasure::default_instance_ = NULL;

KingTreasure* KingTreasure::New() const {
  return new KingTreasure;
}

void KingTreasure::Clear() {
  cost_ = 0u;
  king_treasures_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool KingTreasure::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ConfigKingTreasure.KingTreasure)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ConfigKingTreasure.TreasureBox king_treasures = 1;
      case 1: {
        if (tag == 10) {
         parse_king_treasures:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_king_treasures()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_king_treasures;
        if (input->ExpectTag(16)) goto parse_cost;
        break;
      }

      // required uint32 cost = 2;
      case 2: {
        if (tag == 16) {
         parse_cost:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cost_)));
          set_has_cost();
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
  // @@protoc_insertion_point(parse_success:ConfigKingTreasure.KingTreasure)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ConfigKingTreasure.KingTreasure)
  return false;
#undef DO_
}

void KingTreasure::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ConfigKingTreasure.KingTreasure)
  // repeated .ConfigKingTreasure.TreasureBox king_treasures = 1;
  for (int i = 0; i < this->king_treasures_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->king_treasures(i), output);
  }

  // required uint32 cost = 2;
  if (has_cost()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->cost(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ConfigKingTreasure.KingTreasure)
}

::google::protobuf::uint8* KingTreasure::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ConfigKingTreasure.KingTreasure)
  // repeated .ConfigKingTreasure.TreasureBox king_treasures = 1;
  for (int i = 0; i < this->king_treasures_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->king_treasures(i), target);
  }

  // required uint32 cost = 2;
  if (has_cost()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->cost(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ConfigKingTreasure.KingTreasure)
  return target;
}

int KingTreasure::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required uint32 cost = 2;
    if (has_cost()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cost());
    }

  }
  // repeated .ConfigKingTreasure.TreasureBox king_treasures = 1;
  total_size += 1 * this->king_treasures_size();
  for (int i = 0; i < this->king_treasures_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->king_treasures(i));
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

void KingTreasure::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const KingTreasure* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const KingTreasure*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void KingTreasure::MergeFrom(const KingTreasure& from) {
  GOOGLE_CHECK_NE(&from, this);
  king_treasures_.MergeFrom(from.king_treasures_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_cost()) {
      set_cost(from.cost());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void KingTreasure::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KingTreasure::CopyFrom(const KingTreasure& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KingTreasure::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->king_treasures())) return false;
  return true;
}

void KingTreasure::Swap(KingTreasure* other) {
  if (other != this) {
    king_treasures_.Swap(&other->king_treasures_);
    std::swap(cost_, other->cost_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata KingTreasure::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = KingTreasure_descriptor_;
  metadata.reflection = KingTreasure_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigKingTreasure

// @@protoc_insertion_point(global_scope)
