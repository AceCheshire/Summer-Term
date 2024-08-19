// * License: Apache 2.0
// * File: login_page.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class LoginPage.
#include "inc/inheritance/scene/login_page/login_page.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
LoginPage::LoginPage(PageUnitEx& pageunit_list_head, User& current_user)
    : Scene(pageunit_list_head), current_user_(&current_user) {}

bool LoginPage::prepareScene() {
  try {
    layoutText();
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: class LoginPage | function prepareScene | err_num "
              << err_num << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color
    return false;
  }
  return true;
}

void LoginPage::inputInfo() {
  Page tmp_page;  // temp Page for interface
  // Find where the guidance text is by checking Scene member
  // pageunit_list_head_
  COORD tmp_coord_for_name_input =
      pageunit_list_head_->findByText(login_page::kNameText)->getPageUnit().pos;
  COORD tmp_coord_for_password_input =
      pageunit_list_head_->findByText(login_page::kPasswordText)
          ->getPageUnit()
          .pos;
  // Calculate where the input column should be
  tmp_coord_for_name_input.X += login_page::kInputOffset.X;
  tmp_coord_for_name_input.Y += login_page::kInputOffset.Y;
  tmp_coord_for_password_input.X += login_page::kInputOffset.X;
  tmp_coord_for_password_input.Y += login_page::kInputOffset.Y;
  // Clean last input of name
  tmp_page.returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  std::wcout.imbue(std::locale("chs"));
  for (int i = 0; i < name_request_.length(); i++) std::wcout << " ";
  // Move the cursor to the beginning, display the cursor and client inputs
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  tmp_page.hideCursor(false);
  name_request_ = inputLine(false);  // Like std::cin
  tmp_page.hideCursor(true);
  // Clean last input of password
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  std::wcout.imbue(std::locale("chs"));
  for (int i = 0; i < password_request_.length(); i++) std::wcout << " ";
  // Move, display and input like the above part of code
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  tmp_page.hideCursor(false);
  password_request_ = inputLine(false, '*');  // Like std::cin, fill '*'
  tmp_page.hideCursor(true);
}

bool LoginPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // Cancel checkLink()
  Reader tmp_reader;                 // temp Reader for interface
  Page tmp_page;                     // temp Page for interface
  if (tmp_reader.readForLogin(name_request_, password_request_)) {
    current_user_->setName(name_request_);
    return true;
  } else {
    // Find where the guidance text is by checking Scene member
    // pageunit_list_head_
    COORD tmp_coord_for_name_input =
        pageunit_list_head_->findByText(login_page::kNameText)
            ->getPageUnit()
            .pos;
    COORD tmp_coord_for_password_input =
        pageunit_list_head_->findByText(login_page::kPasswordText)
            ->getPageUnit()
            .pos;
    // Calculate where the end of input column should be
    tmp_coord_for_name_input.X -= (short)std::wcslen(login_page::kErrorText);
    tmp_coord_for_password_input.X -=
        (short)std::wcslen(login_page::kErrorText);
    // Display the error message
    tmp_page.pointPaint(tmp_coord_for_name_input, FOREGROUND_RED,
                        std::wstring(login_page::kErrorText));
    tmp_page.pointPaint(tmp_coord_for_password_input, FOREGROUND_RED,
                        std::wstring(login_page::kErrorText));
    return false;
  }
}
}  // namespace library_management_sys