// * License: Apache 2.0
// * File: login_page.h
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Declare class LoginPage.
#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_
#define LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_
namespace library_management_sys {
namespace login_page {
// File name that is used to load LoginPage.
constexpr wchar_t kPageDataSource[] = L"res/login_page_data.dat";

// Guidance text that point out the position for ID / name.
constexpr wchar_t kNameText[] = L"ID / name:";

// Guidance text that point out the position for password.
constexpr wchar_t kPasswordText[] = L"Password:";

// Error output text that displayed when wrong input occurs.
constexpr wchar_t kErrorText[] = L"(wrong?)";

// How far the input column will appear from the guidance like "Name:".
constexpr COORD kInputOffset = {11, 0};
}  // namespace login_page

// Used to shape the norm of login pages.
// Example:
//    PageUnitEx test_unit_ex;
//    LoginPage test_login_page(test_unit_ex);
class LoginPage : public Scene {
 public:
  LoginPage(PageUnitEx& pageunit_list_head, User& current_user);  // Constructor.

  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();

  // Works when client is inputting text of name or password.
  // Example:
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();

  // Returns true if name and password is matched and updates current_user_.
  // Displays "(wrong?)" if not matched.
  bool checkLink(unsigned short check_mode);

  bool getMouseInputState() { return true; }

  bool getKeyboardInputState() { return true; }

 private:
  // Used to record client's input of name.
  std::wstring name_request_ = {};

  // Used to record client's unput of password.
  std::wstring password_request_ = {};

  // Used to write current user info.
  User* current_user_;
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_