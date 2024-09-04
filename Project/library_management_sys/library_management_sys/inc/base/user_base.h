// * 文件：user_base.h
// * 作者：麦天乐
// * 介绍：声明 User 类。
#include <string>
#ifndef LMS_BASE_USER_BASE_H_
#define LMS_BASE_USER_BASE_H_
namespace library_management_sys {
// 集成用户信息并提供公有访问接口。
// 示例：
//    User test_user;
class User {
 public:
  // 更改成员 name_，并调用一次 updateInfo()。
  void setName(const std::wstring& user_name);
  // 根据 name_ 的值更新 User 实例中的成员。
  void updateInfo();
  void setPermission(bool user_permission) { permission_ = user_permission; }
  // 在成员 history_ 的末尾加上新历史记录。
  // 第一个参数是行为标记，第二个参数是用户名称。
  void appendHistory(const std::wstring& declaration, const std::wstring& name);
  // 清空 User 实例的成员。
  void clear();
  // 保存用户信息到文件中，参数为旧用户名称和希望修改的密码（不修改不填），成功返回真。
  bool saveUser(const std::wstring& old_name,
                const std::wstring& password_request = L"") const;
  // 新增用户文件夹，参数为希望修改的密码，成功返回真。
  bool addUser(const std::wstring& password_request) const;
  std::wstring getName() const { return name_; }
  bool checkPermission() const { return permission_; }
  std::wstring getHistory() const { return history_; }

 protected:
  // 记录用户名称
  std::wstring name_;
  // 记录用户是否拥有更改信息的权限。
  // 此项为真则允许读写信息，此项为假则信息为只读。
  bool permission_ = false;
  // 记录用户历史
  std::wstring history_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_USER_BASE_H_