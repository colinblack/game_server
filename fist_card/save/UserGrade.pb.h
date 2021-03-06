// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserGrade.proto

#ifndef PROTOBUF_UserGrade_2eproto__INCLUDED
#define PROTOBUF_UserGrade_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace UserGrade {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UserGrade_2eproto();
void protobuf_AssignDesc_UserGrade_2eproto();
void protobuf_ShutdownFile_UserGrade_2eproto();

class User;
class Grade;

// ===================================================================

class User : public ::google::protobuf::Message {
 public:
  User();
  virtual ~User();
  
  User(const User& from);
  
  inline User& operator=(const User& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const User& default_instance();
  
  void Swap(User* other);
  
  // implements Message ----------------------------------------------
  
  User* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const User& from);
  void MergeFrom(const User& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 uid = 1;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 1;
  inline ::google::protobuf::uint32 uid() const;
  inline void set_uid(::google::protobuf::uint32 value);
  
  // required uint32 grade = 2;
  inline bool has_grade() const;
  inline void clear_grade();
  static const int kGradeFieldNumber = 2;
  inline ::google::protobuf::uint32 grade() const;
  inline void set_grade(::google::protobuf::uint32 value);
  
  // required uint32 score = 3;
  inline bool has_score() const;
  inline void clear_score();
  static const int kScoreFieldNumber = 3;
  inline ::google::protobuf::uint32 score() const;
  inline void set_score(::google::protobuf::uint32 value);
  
  // required uint32 dailyScore = 4;
  inline bool has_dailyscore() const;
  inline void clear_dailyscore();
  static const int kDailyScoreFieldNumber = 4;
  inline ::google::protobuf::uint32 dailyscore() const;
  inline void set_dailyscore(::google::protobuf::uint32 value);
  
  // required uint32 win = 5;
  inline bool has_win() const;
  inline void clear_win();
  static const int kWinFieldNumber = 5;
  inline ::google::protobuf::uint32 win() const;
  inline void set_win(::google::protobuf::uint32 value);
  
  // repeated bool winRecord = 6;
  inline int winrecord_size() const;
  inline void clear_winrecord();
  static const int kWinRecordFieldNumber = 6;
  inline bool winrecord(int index) const;
  inline void set_winrecord(int index, bool value);
  inline void add_winrecord(bool value);
  inline const ::google::protobuf::RepeatedField< bool >&
      winrecord() const;
  inline ::google::protobuf::RepeatedField< bool >*
      mutable_winrecord();
  
  // required uint32 dailyRewardTs = 7;
  inline bool has_dailyrewardts() const;
  inline void clear_dailyrewardts();
  static const int kDailyRewardTsFieldNumber = 7;
  inline ::google::protobuf::uint32 dailyrewardts() const;
  inline void set_dailyrewardts(::google::protobuf::uint32 value);
  
  // required uint32 refreshCnt = 8;
  inline bool has_refreshcnt() const;
  inline void clear_refreshcnt();
  static const int kRefreshCntFieldNumber = 8;
  inline ::google::protobuf::uint32 refreshcnt() const;
  inline void set_refreshcnt(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:UserGrade.User)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_grade();
  inline void clear_has_grade();
  inline void set_has_score();
  inline void clear_has_score();
  inline void set_has_dailyscore();
  inline void clear_has_dailyscore();
  inline void set_has_win();
  inline void clear_has_win();
  inline void set_has_dailyrewardts();
  inline void clear_has_dailyrewardts();
  inline void set_has_refreshcnt();
  inline void clear_has_refreshcnt();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 grade_;
  ::google::protobuf::uint32 score_;
  ::google::protobuf::uint32 dailyscore_;
  ::google::protobuf::RepeatedField< bool > winrecord_;
  ::google::protobuf::uint32 win_;
  ::google::protobuf::uint32 dailyrewardts_;
  ::google::protobuf::uint32 refreshcnt_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserGrade_2eproto();
  friend void protobuf_AssignDesc_UserGrade_2eproto();
  friend void protobuf_ShutdownFile_UserGrade_2eproto();
  
  void InitAsDefaultInstance();
  static User* default_instance_;
};
// -------------------------------------------------------------------

class Grade : public ::google::protobuf::Message {
 public:
  Grade();
  virtual ~Grade();
  
  Grade(const Grade& from);
  
  inline Grade& operator=(const Grade& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Grade& default_instance();
  
  void Swap(Grade* other);
  
  // implements Message ----------------------------------------------
  
  Grade* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Grade& from);
  void MergeFrom(const Grade& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated .UserGrade.User users = 1;
  inline int users_size() const;
  inline void clear_users();
  static const int kUsersFieldNumber = 1;
  inline const ::UserGrade::User& users(int index) const;
  inline ::UserGrade::User* mutable_users(int index);
  inline ::UserGrade::User* add_users();
  inline const ::google::protobuf::RepeatedPtrField< ::UserGrade::User >&
      users() const;
  inline ::google::protobuf::RepeatedPtrField< ::UserGrade::User >*
      mutable_users();
  
  // @@protoc_insertion_point(class_scope:UserGrade.Grade)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::UserGrade::User > users_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserGrade_2eproto();
  friend void protobuf_AssignDesc_UserGrade_2eproto();
  friend void protobuf_ShutdownFile_UserGrade_2eproto();
  
  void InitAsDefaultInstance();
  static Grade* default_instance_;
};
// ===================================================================


// ===================================================================

// User

// required uint32 uid = 1;
inline bool User::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void User::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void User::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void User::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 User::uid() const {
  return uid_;
}
inline void User::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
}

// required uint32 grade = 2;
inline bool User::has_grade() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void User::set_has_grade() {
  _has_bits_[0] |= 0x00000002u;
}
inline void User::clear_has_grade() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void User::clear_grade() {
  grade_ = 0u;
  clear_has_grade();
}
inline ::google::protobuf::uint32 User::grade() const {
  return grade_;
}
inline void User::set_grade(::google::protobuf::uint32 value) {
  set_has_grade();
  grade_ = value;
}

// required uint32 score = 3;
inline bool User::has_score() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void User::set_has_score() {
  _has_bits_[0] |= 0x00000004u;
}
inline void User::clear_has_score() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void User::clear_score() {
  score_ = 0u;
  clear_has_score();
}
inline ::google::protobuf::uint32 User::score() const {
  return score_;
}
inline void User::set_score(::google::protobuf::uint32 value) {
  set_has_score();
  score_ = value;
}

// required uint32 dailyScore = 4;
inline bool User::has_dailyscore() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void User::set_has_dailyscore() {
  _has_bits_[0] |= 0x00000008u;
}
inline void User::clear_has_dailyscore() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void User::clear_dailyscore() {
  dailyscore_ = 0u;
  clear_has_dailyscore();
}
inline ::google::protobuf::uint32 User::dailyscore() const {
  return dailyscore_;
}
inline void User::set_dailyscore(::google::protobuf::uint32 value) {
  set_has_dailyscore();
  dailyscore_ = value;
}

// required uint32 win = 5;
inline bool User::has_win() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void User::set_has_win() {
  _has_bits_[0] |= 0x00000010u;
}
inline void User::clear_has_win() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void User::clear_win() {
  win_ = 0u;
  clear_has_win();
}
inline ::google::protobuf::uint32 User::win() const {
  return win_;
}
inline void User::set_win(::google::protobuf::uint32 value) {
  set_has_win();
  win_ = value;
}

// repeated bool winRecord = 6;
inline int User::winrecord_size() const {
  return winrecord_.size();
}
inline void User::clear_winrecord() {
  winrecord_.Clear();
}
inline bool User::winrecord(int index) const {
  return winrecord_.Get(index);
}
inline void User::set_winrecord(int index, bool value) {
  winrecord_.Set(index, value);
}
inline void User::add_winrecord(bool value) {
  winrecord_.Add(value);
}
inline const ::google::protobuf::RepeatedField< bool >&
User::winrecord() const {
  return winrecord_;
}
inline ::google::protobuf::RepeatedField< bool >*
User::mutable_winrecord() {
  return &winrecord_;
}

// required uint32 dailyRewardTs = 7;
inline bool User::has_dailyrewardts() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void User::set_has_dailyrewardts() {
  _has_bits_[0] |= 0x00000040u;
}
inline void User::clear_has_dailyrewardts() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void User::clear_dailyrewardts() {
  dailyrewardts_ = 0u;
  clear_has_dailyrewardts();
}
inline ::google::protobuf::uint32 User::dailyrewardts() const {
  return dailyrewardts_;
}
inline void User::set_dailyrewardts(::google::protobuf::uint32 value) {
  set_has_dailyrewardts();
  dailyrewardts_ = value;
}

// required uint32 refreshCnt = 8;
inline bool User::has_refreshcnt() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void User::set_has_refreshcnt() {
  _has_bits_[0] |= 0x00000080u;
}
inline void User::clear_has_refreshcnt() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void User::clear_refreshcnt() {
  refreshcnt_ = 0u;
  clear_has_refreshcnt();
}
inline ::google::protobuf::uint32 User::refreshcnt() const {
  return refreshcnt_;
}
inline void User::set_refreshcnt(::google::protobuf::uint32 value) {
  set_has_refreshcnt();
  refreshcnt_ = value;
}

// -------------------------------------------------------------------

// Grade

// repeated .UserGrade.User users = 1;
inline int Grade::users_size() const {
  return users_.size();
}
inline void Grade::clear_users() {
  users_.Clear();
}
inline const ::UserGrade::User& Grade::users(int index) const {
  return users_.Get(index);
}
inline ::UserGrade::User* Grade::mutable_users(int index) {
  return users_.Mutable(index);
}
inline ::UserGrade::User* Grade::add_users() {
  return users_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::UserGrade::User >&
Grade::users() const {
  return users_;
}
inline ::google::protobuf::RepeatedPtrField< ::UserGrade::User >*
Grade::mutable_users() {
  return &users_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace UserGrade

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UserGrade_2eproto__INCLUDED
