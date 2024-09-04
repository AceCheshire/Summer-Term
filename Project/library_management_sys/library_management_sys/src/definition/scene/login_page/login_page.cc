// * �ļ���login_page.cc
// * ���ߣ�������
// * ���ܣ����� LoginPage �ࡣ
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
  // ���ݳ�Ա��λ
  name_request_.clear();
  password_request_.clear();
  current_user_.clear();
  searching_book_.clear();
  searching_user_.clear();
  shared_task_ = 0;
  return true;
}

void LoginPage::inputInfo() {
  // ��ʾ�ﶨλ
  COORD tmp_coord_for_name_input =
      (*pageunit_list_head_)[login_page::kNameText].pos_;
  COORD tmp_coord_for_password_input =
      (*pageunit_list_head_)[login_page::kPasswordText].pos_;
  // �������������
  tmp_coord_for_name_input.X += login_page::kInputOffset.X;
  tmp_coord_for_name_input.Y += login_page::kInputOffset.Y;
  tmp_coord_for_password_input.X += login_page::kInputOffset.X;
  tmp_coord_for_password_input.Y += login_page::kInputOffset.Y;
  // ����ϴ����������
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  for (int i = 0; i < name_request_.length(); i++) std::wcout << " ";
  // �ƶ���겢��ʾ����ʱ�����û�����
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_name_input);
  Page::hideCursor(false);
  name_request_ = inputLine(false, true, true, true, false);
  Page::hideCursor(true);
  // ����ϴ����������
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  for (int i = 0; i < password_request_.length(); i++) std::wcout << " ";
  // �ƶ���겢��ʾ����ʱ�����û�����
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_password_input);
  Page::hideCursor(false);
  password_request_ = inputLine(false, true, true, true, false, L'*');
  Page::hideCursor(true);
}

bool LoginPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // ���� checkLink()
  if (Reader::readForLogin(name_request_, password_request_)) {  // �ɹ�
    current_user_.setName(name_request_);
    return true;
  } else {
    // ��ʾ�ʶ�λ
    COORD tmp_for_name = (*pageunit_list_head_)[login_page::kNameText].pos_;
    COORD tmp_for_password =
        (*pageunit_list_head_)[login_page::kPasswordText].pos_;
    // ������ʾλ��
    tmp_for_name.X -= (short)std::wcslen(login_page::kErrorText);
    tmp_for_password.X -= (short)std::wcslen(login_page::kErrorText);
    // ��ʾ������Ϣ
    Page::pointPaint(tmp_for_name, FOREGROUND_RED,
                     std::wstring(login_page::kErrorText));
    Page::pointPaint(tmp_for_password, FOREGROUND_RED,
                     std::wstring(login_page::kErrorText));
    return false;
  }
}
}  // namespace library_management_sys