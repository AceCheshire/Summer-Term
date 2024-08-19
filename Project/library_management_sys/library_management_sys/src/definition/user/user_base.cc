// * License: Apache 2.0
// * File: user_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-14
// * Description: Define class User.
#include "inc/base/user_base.h"

#include <string>

#include "inc/base/reader_base.h"
namespace library_management_sys {
void User::setName(const std::wstring& user_name) {
  name_ = user_name;
  updateInfo();  // Call it considering info fluctuation
}

void User::updateInfo() {
  Reader tmp_reader;             // temp Reader for interface
  std::wstring tmp_value_string;  // Argument of readFileLine
  // Update tag (Alternately read tags and values)
  for (int i = 0; i < user::kMaxTagNum; i++) {
    if (tmp_reader.readFileLine(kUserTagPath(name_), 2 * i + user::kTagOffset,
                                tmp_value_string))
      tag_value_[i] = _wtoi(tmp_value_string.c_str());
    if (tmp_reader.readFileLine(kUserTagPath(name_),
                                2 * i + user::kValueOffset, tmp_value_string)) {
      tag_value_[i] = _wtoi(tmp_value_string.c_str());
    }
  }
  // Update permission
  tmp_reader.readFileLine(kUserPermissionPath(name_), 1, tmp_value_string);
  permission_ = _wtoi(tmp_value_string.c_str());
}

void User::clear() {
  // Clear name_
  while (name_.length()) name_.pop_back();
  // Clear tag_ & tag_value_
  for (int i = 0; i < user::kMaxTagNum; i++) {
    while (tag_[i].length()) tag_[i].pop_back();
    tag_value_[i] = 0;
  }
  permission_ = false;  // Clear permission_
}

std::wstring User::getTag() const {
  std::wstring ret;
  for (int i = 0; i < user::kMaxTagNum; i++) {
    ret += tag_[i] + L" ";
  }
  return ret;
}
}  // namespace library_management_sys