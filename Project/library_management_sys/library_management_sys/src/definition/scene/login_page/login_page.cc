// * 文件：login_page.cc
// * 作者：麦天乐
// * 介绍：定义 LoginPage 类。
#include "inc/inheritance/scene/login_page/login_page.h"

#include <iostream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
LoginPage::LoginPage(PageUnitEx& pageunit_list_head)
    : SharedScene(pageunit_list_head) {}

bool LoginPage::prepareScene() {
  layoutText();
  // 数据成员复位
  name_request_.clear();
  password_request_.clear();
  current_user_.clear();
  searching_book_.clear();
  searching_user_.clear();
  shared_task_ = 0;
  return true;
}

void LoginPage::inputInfo() {
  // 提示语定位
  COORD tmp_coord_for_name_input =
      (*pageunit_list_head_)[login_page::kNameText].pos_;
  COORD tmp_coord_for_password_input =
      (*pageunit_list_head_)[login_page::kPasswordText].pos_;
  // 计算输入框坐标
  tmp_coord_for_name_input.X += login_page::kInputOffset.X;
  tmp_coord_for_name_input.Y += login_page::kInputOffset.Y;
  tmp_coord_for_password_input.X += login_page::kInputOffset.X;
  tmp_coord_for_password_input.Y += login_page::kInputOffset.Y;
  // 清除上次输入的名称
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  for (int i = 0; i < name_request_.length(); i++) std::wcout << " ";
  // 移动光标并显示，此时接收用户输入
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  Page::hideCursor(false);
  name_request_ = inputLine(false, true, true, true, false);
  Page::hideCursor(true);
  // 清除上次输入的密码
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  for (int i = 0; i < password_request_.length(); i++) std::wcout << " ";
  // 移动光标并显示，此时接收用户输入
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  Page::hideCursor(false);
  password_request_ = inputLine(false, true, true, true, false, L'*');
  Page::hideCursor(true);
}

bool LoginPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // 无需 checkLink()
  if (Reader::readForLogin(name_request_, password_request_)) {  // 成功
    current_user_.setName(name_request_);
    return true;
  } else {
    // 提示词定位
    COORD tmp_for_name = (*pageunit_list_head_)[login_page::kNameText].pos_;
    COORD tmp_for_password =
        (*pageunit_list_head_)[login_page::kPasswordText].pos_;
    // 计算显示位置
    tmp_for_name.X -= (short)std::wcslen(login_page::kErrorText);
    tmp_for_password.X -= (short)std::wcslen(login_page::kErrorText);
    // 显示错误信息
    Page::pointPaint(tmp_for_name, FOREGROUND_RED,
                     std::wstring(login_page::kErrorText));
    Page::pointPaint(tmp_for_password, FOREGROUND_RED,
                     std::wstring(login_page::kErrorText));
    return false;
  }
}
}  // namespace library_management_sys