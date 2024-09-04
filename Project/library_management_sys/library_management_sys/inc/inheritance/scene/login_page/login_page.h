// * 文件：login_page.h
// * 作者：麦天乐
// * 介绍：声明 LoginPage 类。
#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_
#define LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_
namespace library_management_sys {
// 规定了应用登录页面的范式。示例：
//    PageUnitEx test_unit_ex;
//    LoginPage test_login_page(test_unit_ex);
class LoginPage : public SharedScene {
 public:
  LoginPage(PageUnitEx& pageunit_list_head);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  // 在用户输入名称和密码文本时被执行。示例：
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // 如果名称与密码匹配，返回真，并更新共享的当前登录用户信息.
  // 如果不匹配，返回假，显示错误信息。
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入

 private:
  // 用于记录用户输入的名称
  std::wstring name_request_ = {};
  // 用于记录用户输入的密码
  std::wstring password_request_ = {};
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_