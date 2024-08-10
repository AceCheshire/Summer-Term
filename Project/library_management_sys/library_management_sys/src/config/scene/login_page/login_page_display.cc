// * License: Apache 2.0
// * File: login_page_display.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class LoginPage.
#include"inc/specific/scene/login_page/login_page.h"

#include<iostream>
#include<windows.h>

#include"inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
LoginPage::LoginPage(PageUnitEx& pageunit_list_head)
    : Scene(pageunit_list_head) {}

bool LoginPage::prepareScene() {
  try {
    layoutText();
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: class LoginPage | function prepareScene | err_num "
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
      pageunit_list_head_->findByText(kLoginAdminNameText)->getPageUnit().pos;
  COORD tmp_coord_for_password_input =
      pageunit_list_head_->findByText(kLoginAdminPasswordText)
          ->getPageUnit()
          .pos;
  // Calculate where the input column should be
  tmp_coord_for_name_input.X += kInputOffset.X;
  tmp_coord_for_name_input.Y += kInputOffset.Y;
  tmp_coord_for_password_input.X += kInputOffset.X;
  tmp_coord_for_password_input.Y += kInputOffset.Y;
  // Clean last input of name
  tmp_page.returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  for (int i = 0; i < admin_name_request_.length(); i++) std::cout << " ";
  // Move the cursor to the beginning, display the cursor and client inputs
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  tmp_page.hideCursor(false);
  std::cin >> admin_name_request_;
  tmp_page.hideCursor(true);
  // Clean last input of password
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  for (int i = 0; i < admin_password_request_.length(); i++) std::cout << " ";
  // Move, display and input like the above part of code
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  tmp_page.hideCursor(false);
  std::cin >> admin_password_request_;
  tmp_page.hideCursor(true);
}
}  // namespace library_management_sys