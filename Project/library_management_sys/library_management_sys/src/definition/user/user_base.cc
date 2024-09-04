// * 文件：user_base.cc
// * 作者：麦天乐
// * 介绍：定义 User 类。
#include "inc/base/user_base.h"

#include <fstream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/reader_base.h"
namespace library_management_sys {
void User::setName(const std::wstring& user_name) {
  name_ = user_name;
  updateInfo();  // 考虑到信息发生变更，因而调用
}

void User::updateInfo() {
  std::wstring tmp_permission;
  Reader::readFileLine(kUserHistoryPath(name_), 1, history_);
  Reader::readFileLine(kUserPermissionPath(name_), 1, tmp_permission);
  permission_ = _wtoi(tmp_permission.c_str());
}

void User::appendHistory(const std::wstring& declaration,
                         const std::wstring& name) {
  time_t second;
  time(&second);
  tm time;
  localtime_s(&time, &second);
  history_ += L" " + declaration;  // 行为标记
  history_ += L" " + name;         // 图书名称
  history_ += L" " + std::to_wstring(time.tm_year + 1900) + L"/" +
              std::to_wstring(time.tm_mon + 1) + L"/" +
              std::to_wstring(time.tm_mday) + L"-" +
              std::to_wstring(time.tm_hour) + L":" +
              std::to_wstring(time.tm_min) + L":" +
              std::to_wstring(time.tm_sec);  // 时间戳
}

void User::clear() {
  name_.clear();
  history_.clear();
  permission_ = false;
}

bool User::saveUser(const std::wstring& old_name,
                    const std::wstring& password_request) const {
  if (!old_name.length() || !name_.length()) {  // 检查函数参数
    return false;
  } else {
    if (name_ != old_name) {  // 修改用户名称
      // 检查用户名称是否规范
      std::wifstream file(kUserPasswordPath(old_name));
      if (file.is_open()) {
        file.close();
      } else {
        return false;
      }
      file.open(kUserPasswordPath(name_));
      if (file.is_open()) return false;
      // 若符合规范。更改用户文件夹名称
      Reader::deleteDirectory(kUserFolderPath(old_name));
      Reader::deleteFileLine(search_page::kUserDataSource, old_name);
      this->addUser(L"asdfghjkl");
    }
    // 更改用户文件的信息
    bool ret = true;
    if (password_request.length())  // 检查密码参数，非空则修改密码
      ret = ret && Reader::changeFileLine(kUserPasswordPath(name_), 1,
                                          password_request);
    ret = ret && Reader::changeFileLine(kUserPermissionPath(name_), 1,
                                        std::to_wstring(permission_));
    ret = ret && Reader::changeFileLine(kUserHistoryPath(name_), 1, history_);
    return ret;
  }
}

bool User::addUser(const std::wstring& password_request) const {
  if (!password_request.length() || !name_.length()) return false;  // 检查参数
  // 检查用户名称是否规范
  std::wifstream input_file(kUserPasswordPath(name_));
  if (input_file.is_open()) {
    input_file.close();
    return false;
  }
  // 创建文件
  Reader::createDirectory(kUserFolderPath(name_));
  Reader::createFile(kUserPermissionPath(name_));
  Reader::createFile(kUserHistoryPath(name_));
  Reader::createFile(kUserPasswordPath(name_));
  // 将信息写入文件
  bool ret = true;
  ret = ret && Reader::appendLine(kUserPermissionPath(name_),
                                  std::to_wstring(permission_));
  ret = ret && Reader::appendLine(kUserHistoryPath(name_), history_);
  ret = ret && Reader::appendLine(kUserPasswordPath(name_), password_request);
  if (ret) ret = ret && Reader::appendLine(search_page::kUserDataSource, name_);
  return ret;
}
}  // namespace library_management_sys