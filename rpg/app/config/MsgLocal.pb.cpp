// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MsgLocal.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MsgLocal.pb.h"

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

namespace MsgLocal {

namespace {

const ::google::protobuf::Descriptor* TreasureHuntRecord_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TreasureHuntRecord_reflection_ = NULL;
const ::google::protobuf::Descriptor* TreasureHuntRecords_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TreasureHuntRecords_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MsgLocal_2eproto() {
  protobuf_AddDesc_MsgLocal_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MsgLocal.proto");
  GOOGLE_CHECK(file != NULL);
  TreasureHuntRecord_descriptor_ = file->message_type(0);
  static const int TreasureHuntRecord_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, treasureid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, playerid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, career_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, careerlevel_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, drawdt_),
  };
  TreasureHuntRecord_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TreasureHuntRecord_descriptor_,
      TreasureHuntRecord::default_instance_,
      TreasureHuntRecord_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecord, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TreasureHuntRecord));
  TreasureHuntRecords_descriptor_ = file->message_type(1);
  static const int TreasureHuntRecords_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecords, records_),
  };
  TreasureHuntRecords_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TreasureHuntRecords_descriptor_,
      TreasureHuntRecords::default_instance_,
      TreasureHuntRecords_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecords, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TreasureHuntRecords, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TreasureHuntRecords));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MsgLocal_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TreasureHuntRecord_descriptor_, &TreasureHuntRecord::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TreasureHuntRecords_descriptor_, &TreasureHuntRecords::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MsgLocal_2eproto() {
  delete TreasureHuntRecord::default_instance_;
  delete TreasureHuntRecord_reflection_;
  delete TreasureHuntRecords::default_instance_;
  delete TreasureHuntRecords_reflection_;
}

void protobuf_AddDesc_MsgLocal_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016MsgLocal.proto\022\010MsgLocal\"\246\001\n\022TreasureH"
    "untRecord\022\n\n\002id\030\001 \002(\005\022\014\n\004type\030\002 \002(\005\022\022\n\nt"
    "reasureId\030\003 \002(\005\022\020\n\010playerId\030\004 \002(\005\022\014\n\004nam"
    "e\030\005 \002(\t\022\016\n\006career\030\006 \002(\005\022\r\n\005level\030\007 \002(\005\022\023"
    "\n\013careerLevel\030\010 \002(\005\022\016\n\006drawDt\030\t \002(\005\"D\n\023T"
    "reasureHuntRecords\022-\n\007records\030\001 \003(\0132\034.Ms"
    "gLocal.TreasureHuntRecord", 265);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MsgLocal.proto", &protobuf_RegisterTypes);
  TreasureHuntRecord::default_instance_ = new TreasureHuntRecord();
  TreasureHuntRecords::default_instance_ = new TreasureHuntRecords();
  TreasureHuntRecord::default_instance_->InitAsDefaultInstance();
  TreasureHuntRecords::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MsgLocal_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MsgLocal_2eproto {
  StaticDescriptorInitializer_MsgLocal_2eproto() {
    protobuf_AddDesc_MsgLocal_2eproto();
  }
} static_descriptor_initializer_MsgLocal_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TreasureHuntRecord::kIdFieldNumber;
const int TreasureHuntRecord::kTypeFieldNumber;
const int TreasureHuntRecord::kTreasureIdFieldNumber;
const int TreasureHuntRecord::kPlayerIdFieldNumber;
const int TreasureHuntRecord::kNameFieldNumber;
const int TreasureHuntRecord::kCareerFieldNumber;
const int TreasureHuntRecord::kLevelFieldNumber;
const int TreasureHuntRecord::kCareerLevelFieldNumber;
const int TreasureHuntRecord::kDrawDtFieldNumber;
#endif  // !_MSC_VER

TreasureHuntRecord::TreasureHuntRecord()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MsgLocal.TreasureHuntRecord)
}

void TreasureHuntRecord::InitAsDefaultInstance() {
}

TreasureHuntRecord::TreasureHuntRecord(const TreasureHuntRecord& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MsgLocal.TreasureHuntRecord)
}

void TreasureHuntRecord::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  id_ = 0;
  type_ = 0;
  treasureid_ = 0;
  playerid_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  career_ = 0;
  level_ = 0;
  careerlevel_ = 0;
  drawdt_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TreasureHuntRecord::~TreasureHuntRecord() {
  // @@protoc_insertion_point(destructor:MsgLocal.TreasureHuntRecord)
  SharedDtor();
}

void TreasureHuntRecord::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void TreasureHuntRecord::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TreasureHuntRecord::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TreasureHuntRecord_descriptor_;
}

const TreasureHuntRecord& TreasureHuntRecord::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MsgLocal_2eproto();
  return *default_instance_;
}

TreasureHuntRecord* TreasureHuntRecord::default_instance_ = NULL;

TreasureHuntRecord* TreasureHuntRecord::New() const {
  return new TreasureHuntRecord;
}

void TreasureHuntRecord::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TreasureHuntRecord*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(id_, playerid_);
    ZR_(career_, careerlevel_);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
  }
  drawdt_ = 0;

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TreasureHuntRecord::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MsgLocal.TreasureHuntRecord)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }

      // required int32 type = 2;
      case 2: {
        if (tag == 16) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_treasureId;
        break;
      }

      // required int32 treasureId = 3;
      case 3: {
        if (tag == 24) {
         parse_treasureId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &treasureid_)));
          set_has_treasureid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_playerId;
        break;
      }

      // required int32 playerId = 4;
      case 4: {
        if (tag == 32) {
         parse_playerId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &playerid_)));
          set_has_playerid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_name;
        break;
      }

      // required string name = 5;
      case 5: {
        if (tag == 42) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_career;
        break;
      }

      // required int32 career = 6;
      case 6: {
        if (tag == 48) {
         parse_career:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &career_)));
          set_has_career();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_level;
        break;
      }

      // required int32 level = 7;
      case 7: {
        if (tag == 56) {
         parse_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &level_)));
          set_has_level();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_careerLevel;
        break;
      }

      // required int32 careerLevel = 8;
      case 8: {
        if (tag == 64) {
         parse_careerLevel:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &careerlevel_)));
          set_has_careerlevel();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_drawDt;
        break;
      }

      // required int32 drawDt = 9;
      case 9: {
        if (tag == 72) {
         parse_drawDt:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &drawdt_)));
          set_has_drawdt();
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
  // @@protoc_insertion_point(parse_success:MsgLocal.TreasureHuntRecord)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MsgLocal.TreasureHuntRecord)
  return false;
#undef DO_
}

void TreasureHuntRecord::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MsgLocal.TreasureHuntRecord)
  // required int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }

  // required int32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->type(), output);
  }

  // required int32 treasureId = 3;
  if (has_treasureid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->treasureid(), output);
  }

  // required int32 playerId = 4;
  if (has_playerid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->playerid(), output);
  }

  // required string name = 5;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->name(), output);
  }

  // required int32 career = 6;
  if (has_career()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->career(), output);
  }

  // required int32 level = 7;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->level(), output);
  }

  // required int32 careerLevel = 8;
  if (has_careerlevel()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->careerlevel(), output);
  }

  // required int32 drawDt = 9;
  if (has_drawdt()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->drawdt(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MsgLocal.TreasureHuntRecord)
}

::google::protobuf::uint8* TreasureHuntRecord::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MsgLocal.TreasureHuntRecord)
  // required int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }

  // required int32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->type(), target);
  }

  // required int32 treasureId = 3;
  if (has_treasureid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->treasureid(), target);
  }

  // required int32 playerId = 4;
  if (has_playerid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->playerid(), target);
  }

  // required string name = 5;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->name(), target);
  }

  // required int32 career = 6;
  if (has_career()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->career(), target);
  }

  // required int32 level = 7;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->level(), target);
  }

  // required int32 careerLevel = 8;
  if (has_careerlevel()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->careerlevel(), target);
  }

  // required int32 drawDt = 9;
  if (has_drawdt()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->drawdt(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MsgLocal.TreasureHuntRecord)
  return target;
}

int TreasureHuntRecord::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

    // required int32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }

    // required int32 treasureId = 3;
    if (has_treasureid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->treasureid());
    }

    // required int32 playerId = 4;
    if (has_playerid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->playerid());
    }

    // required string name = 5;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // required int32 career = 6;
    if (has_career()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->career());
    }

    // required int32 level = 7;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->level());
    }

    // required int32 careerLevel = 8;
    if (has_careerlevel()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->careerlevel());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required int32 drawDt = 9;
    if (has_drawdt()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->drawdt());
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

void TreasureHuntRecord::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TreasureHuntRecord* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TreasureHuntRecord*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TreasureHuntRecord::MergeFrom(const TreasureHuntRecord& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_treasureid()) {
      set_treasureid(from.treasureid());
    }
    if (from.has_playerid()) {
      set_playerid(from.playerid());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_career()) {
      set_career(from.career());
    }
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_careerlevel()) {
      set_careerlevel(from.careerlevel());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_drawdt()) {
      set_drawdt(from.drawdt());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TreasureHuntRecord::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TreasureHuntRecord::CopyFrom(const TreasureHuntRecord& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TreasureHuntRecord::IsInitialized() const {
  if ((_has_bits_[0] & 0x000001ff) != 0x000001ff) return false;

  return true;
}

void TreasureHuntRecord::Swap(TreasureHuntRecord* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(treasureid_, other->treasureid_);
    std::swap(playerid_, other->playerid_);
    std::swap(name_, other->name_);
    std::swap(career_, other->career_);
    std::swap(level_, other->level_);
    std::swap(careerlevel_, other->careerlevel_);
    std::swap(drawdt_, other->drawdt_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TreasureHuntRecord::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TreasureHuntRecord_descriptor_;
  metadata.reflection = TreasureHuntRecord_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TreasureHuntRecords::kRecordsFieldNumber;
#endif  // !_MSC_VER

TreasureHuntRecords::TreasureHuntRecords()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MsgLocal.TreasureHuntRecords)
}

void TreasureHuntRecords::InitAsDefaultInstance() {
}

TreasureHuntRecords::TreasureHuntRecords(const TreasureHuntRecords& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MsgLocal.TreasureHuntRecords)
}

void TreasureHuntRecords::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TreasureHuntRecords::~TreasureHuntRecords() {
  // @@protoc_insertion_point(destructor:MsgLocal.TreasureHuntRecords)
  SharedDtor();
}

void TreasureHuntRecords::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TreasureHuntRecords::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TreasureHuntRecords::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TreasureHuntRecords_descriptor_;
}

const TreasureHuntRecords& TreasureHuntRecords::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MsgLocal_2eproto();
  return *default_instance_;
}

TreasureHuntRecords* TreasureHuntRecords::default_instance_ = NULL;

TreasureHuntRecords* TreasureHuntRecords::New() const {
  return new TreasureHuntRecords;
}

void TreasureHuntRecords::Clear() {
  records_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TreasureHuntRecords::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MsgLocal.TreasureHuntRecords)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .MsgLocal.TreasureHuntRecord records = 1;
      case 1: {
        if (tag == 10) {
         parse_records:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_records()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_records;
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
  // @@protoc_insertion_point(parse_success:MsgLocal.TreasureHuntRecords)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MsgLocal.TreasureHuntRecords)
  return false;
#undef DO_
}

void TreasureHuntRecords::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MsgLocal.TreasureHuntRecords)
  // repeated .MsgLocal.TreasureHuntRecord records = 1;
  for (int i = 0; i < this->records_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->records(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MsgLocal.TreasureHuntRecords)
}

::google::protobuf::uint8* TreasureHuntRecords::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MsgLocal.TreasureHuntRecords)
  // repeated .MsgLocal.TreasureHuntRecord records = 1;
  for (int i = 0; i < this->records_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->records(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MsgLocal.TreasureHuntRecords)
  return target;
}

int TreasureHuntRecords::ByteSize() const {
  int total_size = 0;

  // repeated .MsgLocal.TreasureHuntRecord records = 1;
  total_size += 1 * this->records_size();
  for (int i = 0; i < this->records_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->records(i));
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

void TreasureHuntRecords::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TreasureHuntRecords* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TreasureHuntRecords*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TreasureHuntRecords::MergeFrom(const TreasureHuntRecords& from) {
  GOOGLE_CHECK_NE(&from, this);
  records_.MergeFrom(from.records_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TreasureHuntRecords::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TreasureHuntRecords::CopyFrom(const TreasureHuntRecords& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TreasureHuntRecords::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->records())) return false;
  return true;
}

void TreasureHuntRecords::Swap(TreasureHuntRecords* other) {
  if (other != this) {
    records_.Swap(&other->records_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TreasureHuntRecords::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TreasureHuntRecords_descriptor_;
  metadata.reflection = TreasureHuntRecords_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace MsgLocal

// @@protoc_insertion_point(global_scope)
