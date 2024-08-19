// * License: Apache 2.0
// * File: user_base.h
// * Author: Mai Tianle
// * Date: 2024-08-13
// * Description: Declare class User.
#include <string>
#ifndef LMS_BASE_USER_BASE_H_
#define LMS_BASE_USER_BASE_H_
// Path that records user's password.
#define kUserPermissionPath(USER_NAME) L"res/user/" + USER_NAME + L"/permission.dat"

// Path that records user's tag.
#define kUserTagPath(USER_NAME) L"res/user/" + USER_NAME + L"/tag.dat"
namespace library_management_sys {
namespace user {
// Used to limit the precision of user description.
constexpr int kMaxTagNum = 8;

enum Order {
  // It means the order of tag name in tag.dat.
  kTagOffset = 1,

  // It means the order of tag value in tag.dat.
  kValueOffset
};
}  // namespace user

// Coordinates information about user and provides public
// interfaces to access it.
// Example:
//    User test_user;
class User {
 public:
  // Changes name_ and call updateInfo().
  void setName(const std::wstring& user_name);

  // Updates data in User instance by name_.
  // Used after setName().
  void updateInfo();

  void setPermission(bool user_permission) {
    permission_ = user_permission;
  }

  // Clears the members.
  void clear();

  std::wstring getName() const { return name_; }

  bool checkPermission() const { return permission_; }

  // Returns printable string for display.
  std::wstring getTag() const;
 protected:
  std::wstring name_;

  // Records whether user has permission to change the info.
  // True means read and write, and false means read only.
  bool permission_ = false;

  /*std::wstring viewing_history;*/

  // Tags that describe a user.
  std::wstring tag_[user::kMaxTagNum] = {};

  // The values relevant to the tags.
  short tag_value_[user::kMaxTagNum] = {};
};
}  // namespace library_management_sys
#endif  // LMS_BASE_USER_BASE_H_
