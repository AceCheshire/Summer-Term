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
      waitInput(true, false);
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