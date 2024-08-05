#include"error_base.h"
#include"login_page_sp.h"
#include<iostream>
#include<windows.h>
using namespace std;

LoginPage::LoginPage(Mouse* attached_mouse, Scene* prev_scene,
                     PageUnitEx* pageunit_list_head)
    : GeneralScene(attached_mouse, prev_scene, pageunit_list_head) {}

bool LoginPage::prepareScene() {
  try {
    while (true) {
      layoutText();
      inputLoginInfo();
    }
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: class LoginPage | function prepareScene | err_num " << err_num
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    return false;
  }
  return true;
}

void LoginPage::inputLoginInfo() {
  if (!is_inputting_login_info_) {
    waitInput(true, false);
    if (KEY_DOWN(VK_INSERT)) is_inputting_login_info_ = true;
  } else {
    Page tmp_page;
    COORD tmp_coord_for_name_input =
        pageunit_list_head_->findByText(kLoginAdminNameText)->getPageUnit().pos;
    COORD tmp_coord_for_password_input =
        pageunit_list_head_->findByText(kLoginAdminPasswordText)
            ->getPageUnit()
            .pos;
    tmp_coord_for_name_input.X += kInputOffset.X;
    tmp_coord_for_name_input.Y += kInputOffset.Y;
    tmp_coord_for_password_input.X += kInputOffset.X;
    tmp_coord_for_password_input.Y += kInputOffset.Y;
    tmp_page.returnDefault();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             tmp_coord_for_name_input);
    for (int i = 0; i < admin_name_request_.length(); i++) cout << " ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             tmp_coord_for_name_input);
    tmp_page.hideCursor(false);
    cin >> admin_name_request_;
    tmp_page.hideCursor(true);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             tmp_coord_for_password_input);
    for (int i = 0; i < admin_password_request_.length(); i++) cout << " ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             tmp_coord_for_password_input);
    tmp_page.hideCursor(false);
    cin >> admin_password_request_;
    tmp_page.hideCursor(true);
    is_inputting_login_info_ = false;
  }
}