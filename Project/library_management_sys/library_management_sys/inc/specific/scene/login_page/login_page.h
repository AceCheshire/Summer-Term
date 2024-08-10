// * License: Apache 2.0
// * File: login_page.h
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Declare class LoginPage.
#include <iostream>
#include <windows.h>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_
#define LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_
namespace library_management_sys {
// File name that is used to load LoginPage.
constexpr char kLoginPageDataSource[] = "res/login_page_data.txt";
// Guidance text that point out the position for ID / name.
constexpr char kLoginAdminNameText[] = "Admin_ID_/_name: ";
// Guidance text that point out the position for ID / name.
constexpr char kLoginAdminPasswordText[] = "Admin_password:";
// It means how far the input column will appear from the guidance like "Name:
// ".
constexpr COORD kInputOffset = {20, 0};

// Used to shape the norm of login pages.
// Example:
//    PageUnitEx test_unit_ex;
//    LoginPage test_login_page(test_unit_ex);
class LoginPage : public Scene {
 public:
  LoginPage(PageUnitEx& pageunit_list_head);  // Constructor.
  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();
  // Works when client is inputting text of name or password.
  // Example:
  //    while (is_inputting_login_info_) text_scene.inputLoginInfo();
  void inputInfo();
  bool getMouseInputState() { return true; }
  bool getKeyboardInputState() { return true; }

 private:
  // Used to record client's input of name.
  std::string admin_name_request_ = {};
  // Used to record client's unput of password.
  std::string admin_password_request_ = {};
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_